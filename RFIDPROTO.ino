#include <Servo.h>

#define TRUE  1
#define FALSE 0

#define LOCKED 90
#define ORIGIN 0
#define UNLOCKED -90

Servo lockservo;  // create servo object to control a servo
                // a maximum of eight servo objects can be created
 
int pos = 0;    // variable to store the servo position
int rfidInPin = 7;
int doorLimit = 5;
int toggleButton = 3;
int ledPin = 11;


void toggle(boolean * value);


int val = 0;



boolean lockState = false;
boolean inoutState = false;

boolean doorState = false;
boolean doorStateLast = false;

boolean modeButton = false;
boolean modeButtonLast = false;

boolean rfidIn   = false;

boolean beenLocked = false;
boolean beenUnlocked = false;

void setup()
{
  lockservo.attach(9);  // attaches the servo on pin 9 to the servo object
  pinMode(rfidInPin, INPUT_PULLUP);
  pinMode(toggleButton, INPUT_PULLUP);
  pinMode(doorLimit, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}
 
 
void loop()
{
    doorState = !digitalRead(doorLimit);
    modeButton = !digitalRead(toggleButton);
    rfidIn     = !digitalRead(rfidInPin);

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

    
    /* Set status LED */
    if(inoutState == true)  
        digitalWrite(ledPin, HIGH);
    else
        digitalWrite(ledPin, LOW);


    /* FSM STUFF */
    if( inoutState == true )
    {   
        lockservo.write(ORIGIN);

        if(lockState == true)
        {
            lockservo.write(UNLOCKED);
            lockservo.write(ORIGIN);
        }
        //If you're inside the room
    }


    //OUT
    else
    {   
        /* If the door goes from open to closed */
        if( doorState == true && doorStateLast == false)
        {   
            if(lockState == false)
            {
                Serial.write(">>>Locking deadbolt\n");
                lockservo.write(LOCKED);
                lockState = true;
            }
        }

        // if( doorState == true && doorStateLast == false)
        // {
        //     Serial.write(">>>Locking deadbolt!\n");
        // }

        if( rfidIn == true)
        {
            if(lockState == true)
            {
                Serial.write(">>>Unlocking deadbolt\n");
                lockservo.write(UNLOCKED);
                lockservo.write(ORIGIN);
                lockState == false;
            }
        }

        lockservo.write(ORIGIN);
        //If you want the door to be locked
    }




    modeButtonLast = modeButton;
    doorStateLast = doorState;
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