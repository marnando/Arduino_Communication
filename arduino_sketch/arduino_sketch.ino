
// comm variables
const int MAX_CMD_SIZE = 256;
char buffer[MAX_CMD_SIZE]; // buffer for serial commands
char serial_char; // value for each byte read in from serial comms
int serial_count = 0; // current length of command
char *strchr_pointer; // just a pointer to find chars in the cmd string like X, Y, Z, E, etc
boolean comment_mode = false;
// end comm variables

void setup()
{
    Serial.begin(115200);
    //Serial.print("EBB 1.0\n");
    
    clear_buffer();
}

void loop() // input loop, looks for manual input and then checks to see if and serial commands are coming in
{
  get_command(); // check for Gcodes
}

void get_command() // gets commands from serial connection and then calls up subsequent functions to deal with them
{
  if (Serial.available() > 0) // each time we see something
  {
    serial_char = Serial.read(); // read individual byte from serial connection
    
    if (serial_char == '\n' || serial_char == '\r') // end of a command character
    { 
      buffer[serial_count]=0;
      process_commands(buffer, serial_count);
      clear_buffer();
      comment_mode = false; // reset comment mode before each new command is processed
      //Serial.write("process: command");
    }
    else // not end of command
    {
      if (serial_char == ';' || serial_char == '(') // semicolon signifies start of comment
      {
        comment_mode = true;
      }
      
      if (comment_mode != true) // ignore if a comment has started
      {
        buffer[serial_count] = serial_char; // add byte to buffer string
        serial_count++;
        if (serial_count > MAX_CMD_SIZE) // overflow, dump and restart
        {
          clear_buffer();
          Serial.flush();
        }
      }
      else
      {
      }
    }
  }
}

void clear_buffer() // empties command buffer from serial connection
{
  serial_count = 0; // reset buffer placement
}

boolean getValue(char key, char command[], double* value)
{  
  // find key parameter
  strchr_pointer = strchr(buffer, key);
  if (strchr_pointer != NULL) // We found a key value
  {
    *value = (double)strtod(&command[strchr_pointer - command + 1], NULL);
    return true;  
  }
  return false;
}
  
void process_commands(char command[], int command_length) // deals with standardized input from serial connection
{
  if(command_length>0 && command[0] == 'I')
  {
    Serial.print("ID:1\n");
  }
  /*if (command_length>0 && command[0] == 'G') // G code
  {
    //Serial.print("proces G: \n");
    int codenum = (int)strtod(&command[1], NULL);
    
    double tempX = xAxisStepper.getCurrentPosition();
    double tempY = rotationStepper.getCurrentPosition();
    
    double xVal;
    boolean hasXVal = getValue('X', command, &xVal);
    if(hasXVal) xVal*=zoom*1.71/2;                              //this factor is for correction to meet the unicorn coordinates    
    double yVal;
    boolean hasYVal = getValue('Y', command, &yVal);
    if(hasYVal) yVal*=zoom;
    double iVal;
    boolean hasIVal = getValue('I', command, &iVal);
    if(hasIVal) iVal*=zoom;
    double jVal;
    boolean hasJVal = getValue('J', command, &jVal);
    if(hasJVal) jVal*=zoom;
    double rVal;
    boolean hasRVal = getValue('R', command, &rVal);
    if(hasRVal) rVal*=zoom;
    double pVal;
    boolean hasPVal = getValue('P', command, &pVal);
    
    getValue('F', command, &feedrate);

    xVal+=currentOffsetX;
    yVal+=currentOffsetY;
    
    if(absoluteMode)
    {
      if(hasXVal)
        tempX=xVal;
      if(hasYVal)
        tempY=yVal;
    }
    else
    {
      if(hasXVal)
        tempX+=xVal;
      if(hasYVal)
        tempY+=yVal;
    }
    
    switch(codenum)
    {
      case 0: // G0, Rapid positioning
        xAxisStepper.setTargetPosition(tempX);
        rotationStepper.setTargetPosition(tempY);
        commitSteppers(maxFeedrate);
        break;
      case 1: // G1, linear interpolation at specified speed
        xAxisStepper.setTargetPosition(tempX);
        rotationStepper.setTargetPosition(tempY);
        commitSteppers(feedrate);
        break;
      case 2: // G2, Clockwise arc
      case 3: // G3, Counterclockwise arc
        if(hasIVal && hasJVal)
        {
            double centerX=xAxisStepper.getCurrentPosition()+iVal;
            double centerY=rotationStepper.getCurrentPosition()+jVal;
            drawArc(centerX, centerY, tempX, tempY, (codenum==2));
        }
        else if(hasRVal)
        {
          //drawRadius(tempX, tempY, rVal, (codenum==2));
        }
        break;
      case 4: // G4, Delay P ms
        if(hasPVal)
        {
           unsigned long endDelay = millis()+ (unsigned long)pVal;
           while(millis()<endDelay)
           {
              delay(1);
              if(servoEnabled)
                SoftwareServo::refresh();
           }
        }
        break;
      case 21: // G21 metric 
        break;
      case 90: // G90, Absolute Positioning
        absoluteMode = true;
        break;
      case 91: // G91, Incremental Positioning
        absoluteMode = false;
        break;
      case 92: // G92 homing
        break;
    }
  }  
  else if (command_length>0 && command[0] == 'M') // M code
  {
    //Serial.print("proces M:\n");
    double value;
    int codenum = (int)strtod(&command[1], NULL);
    switch(codenum)
    {   
      case 18: // Disable Drives
        xAxisStepper.resetStepper();
        rotationStepper.resetStepper();
        break;

      case 300: // Servo Position
        if(getValue('S', command, &value))
        {
          servoEnabled=true;
          if(value<0.)
            value=0.;
          else if(value>180.)
          {
            value=DEFAULT_PEN_UP_POSITION;
            servo.write((int)value);
            for(int i=0;i<100;i++)
            {
                SoftwareServo::refresh();
                delay(4);
            }           
            servoEnabled=false;
          }
          servo.write((int)value);
        }
        break;
        
      case 400: // Propretary: Reset X-Axis-Stepper settings to new object diameter
        if(getValue('S', command, &value))
        {
          xAxisStepper.resetSteppersForObjectDiameter(value);
          xAxisStepper.setTargetPosition(0.);
          commitSteppers(maxFeedrate);
          delay(2000);
          xAxisStepper.enableStepper(false);
        }
        break;
        
      case 401: // Propretary: Reset Y-Axis-Stepper settings to new object diameter
        if(getValue('S', command, &value))
        {
          rotationStepper.resetSteppersForObjectDiameter(value);
          rotationStepper.setTargetPosition(0.);
          commitSteppers(maxFeedrate);
          delay(2000);
          rotationStepper.enableStepper(false);
        }
        break;
        
     case 402: // Propretary: Reset Y-Axis-Stepper settings to new object diameter
        if(getValue('S', command, &value))
        {
            zoom = value/100;
        }
        break;
*/
    
/*

//done processing commands
if (Serial.available() <= 0) {
Serial.print("ok:");
Serial.println(command);
Serial.print("\n\n");
}*/
  
}

