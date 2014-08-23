// Sweep
// by BARRAGAN <http://barraganstudio.com>
// This example code is in the public domain.


#include <Servo.h>

#define TRUE  1
#define FALSE 0

Servo lockservo;  // create servo object to control a servo
                // a maximum of eight servo objects can be created
 
int pos = 0;    // variable to store the servo position
int rfidInPin = 7;
int doorLimit = 5;
int toggleButton = 3;


void toggle(boolean * value);


int val = 0;



boolean lockState = false;
boolean inoutState = false;

boolean doorClosed = false;
boolean modeButton = false;
boolean modeButtonLast = false;

boolean rfidIn   = false;




void setup()
{
  lockservo.attach(9);  // attaches the servo on pin 9 to the servo object
  pinMode(rfidInPin, INPUT_PULLUP);
  pinMode(toggleButton, INPUT_PULLUP);
  pinMode(doorLimit, INPUT_PULLUP);

  Serial.begin(9600);
}
 
 
void loop()
{
    doorClosed = digitalRead(doorLimit);
    modeButton = !digitalRead(toggleButton);
    rfidIn     = digitalRead(rfidInPin);

    /* Toggle IN or OUT modes */
    if(modeButton == true && modeButtonLast == false )
    {
        inoutState = !inoutState;
        if(inoutState)
        {
            Serial.write("[IN Mode set]\n");
        }
        else
        {
            Serial.write("[OUT Mode set]\n");
        }
    }

    modeButtonLast = modeButton;

    if( inoutState == true )
    {
        //If you're inside the room
    }


    //OUT
    else
    {
        //if()
        //If you want the door to be locked
    }





    //buttonPressed = digitalRead(buttonPin);


    //lastButtonState = buttonPressed;
    

    // if(state)
    // {

    //     myservo.write(90);
    //     // for(pos = 0; pos < 180; pos += 1)  // goes from 0 degrees to 180 degrees
    //     // {                                  // in steps of 1 degree
    //     //   myservo.write(pos);              // tell servo to go to position in variable 'pos'
    //     //   delay(15);                       // waits 15ms for the servo to reach the position
    //     // }
    //     // for(pos = 180; pos>=1; pos-=1)     // goes from 180 degrees to 0 degrees
    //     // {                                
    //     //   myservo.write(pos);              // tell servo to go to position in variable 'pos'
    //     //   delay(15);                       // waits 15ms for the servo to reach the position
    //     // }
    // }
    // else
    // {
    //     myservo.write(0);
    // }
}

void toggle(boolean * value)
{
  if(*value == true)
  {
    *value = false;
  }

  else
  {
    *value = true;
  }
}