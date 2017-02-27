/*

  Fairy Lights - cycle lights one at a time to create a chase effect

  users can choose the number of lights and the timings by configuring this file
  Lights chase when an input is pulled to ground and don't when its not
        
  2017 Shawn Yates
  
  Want to automate this puzzle?  Visit our website to learn how:
  www.cluecontrol.com
  feedback@cluecontrol.com
  
  written and tested with Arduino 1.8.1
 
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

   -------------------
*/

/*
// pin assignments
 * Signal     Pin                
 *            Arduino Uno     
 * ------------------------
 * 0   Serial RX
 * 1   Serial TX
 * 2   GO input         //the lights will go when this is pulled to ground     
 * 3   light 1          //each light needs to be connected to a pin     
 * 4   light 2          //you must connect the lights in order
 * 5   light 3          //you can choose if the lights are active low
 * 6   light 4          //or active  high in the variables section below
 * 7   light 5          //be sure to use current limiting resistors and other
                        //things as required to keep the light and the Arduino
 * 8   light 6          //safe.
 * 9   light 7     
 * 10  light 8
 * 11  light 9
 * 12  light 10
 * 13   light 11
 
 * 14  (A0)     light 12
 * 15  (A1)     light 13
 * 16  (A2)     light 14
 * 17  (A3)     light 15
 * 18  (A4/SDA) light 16
 * 19  (A5/SCK) light 17
 
 
 
 General operation:
 
Setup

Running      
    
             
 
 */
// Settings likely to change/be tweaked

    const byte              HOW_MANY_LIGHTS =    5;        //change this number to say how many lights you have connected, up to 17
    const unsigned long     ON_TIME         =  250;        //how many mS to keep each light turned on (1000mS = 1 second)
    const unsigned long     OFF_TIME        =  250;        //how many mS to pause between one light turning off and the next turning on
    const bool              ACTIVE_HIGH     =   true;      //set to true if the light needs a positive output to turn on.  
                                                           //Set to false if it needs a negative output to turn on
// Most things below this line shouldn't be changed unless you know what you are doing.
// but feel free to read, learn and experimeint.

// Pin Renames

    //no pin renames for the lights, code relies on the sequential pin numbering
    const byte              TRIGGER     =    2;          //when this pin is pulled low, the lights will chase.  

// Other Constants

      const bool            ON = ACTIVE_HIGH;
      const bool            OFF = !ACTIVE_HIGH;
      bool DebounceSW(byte SWx);
//Variables
    unsigned long   NextStep;                         //used to hold the next time something will happen
  


void setup()
{
  
  // serial setup
  Serial.begin(9600);
  Serial.println("Serial interface started");
  
  pinMode(TRIGGER,INPUT_PULLUP);
  for (int x=3; x < 19; x++)
  {
    pinMode(x,OUTPUT);
    digitalWrite(x,OFF);
  }
  
  
}

void loop() 
{

  if (!DebounceSW(TRIGGER)) {return;}  //if trigger is not active, the return sends the code back to
                                        //beginning of loop().  Which means that the code below only
                                        //executes if trigger is active.

  for (int x=0; x<HOW_MANY_LIGHTS; x++) //loop through each light up to HOW_MANY_LIGHTS
  { 
    digitalWrite(x+3,ON);               //turn the light on
    delay(ON_TIME);                     //pause for the ON time
    digitalWrite(x+3,OFF);              //turn the light off
    delay(OFF_TIME);                    //pause for the off time
  }
   

}

bool DebounceSW(byte SWx)
{
  //Read the switch 5 times, 10mS apart.  Return 
  //the value of the majority of the reads.
  //this is to prevent false or erattic triggering
  //caused by the internal mechanical bounce of a switch
  
  byte HighCounts = 0;
  for (int x = 0 ; x <5 ; x++)
  {
    if (!digitalRead(SWx))    //invert the reading due to the use of pullups
    {
      HighCounts++;   
    }
    delay(10);
  }
  return (HighCounts > 2);    //if there are more than 2 hights, return high
}
