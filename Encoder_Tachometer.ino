/* Encoder Library - Basic Example
 * http://www.pjrc.com/teensy/td_libs_Encoder.html
 *
 * This example code is in the public domain.
 */

#include <Encoder.h>

// Change these two numbers to the pins connected to your encoder.
//   Best Performance: both pins have interrupt capability
//   Good Performance: only the first pin has interrupt capability
//   Low Performance:  neither pin has interrupt capability
#define PI 3.1415926535897932384626433832795
Encoder myEnc(2, 4); //Use digital pins 2 and 4 for the encoders "Channel A" and "Channel B" connections. Connect GND and SHIELD to arduinos ground pin. Connect Vin to Arduinos 5V output. 
int remainder = 0;
int rotations = 0;
float RPS = 0.0;
unsigned long Current_Time = 0; 
unsigned long Start_Time = 0; 
float velocity;
float diameter = 122.5; //Diameter of wheel attached to the encoder in mm
float circumference = 2 * PI * diameter;
float buffer[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,}; //Circular buffer array, used to smoothen out the encoder readings. Entries can be removed for a faster but more noisy reading. 
int i = 0; 
float SmoothVelocity;
float BufferAvg;

void setup() {
  Serial.begin(9600);
  Serial.println("Basic Encoder Test:");
  Start_Time = millis();
}

long oldPosition  = -999;

void loop() {
  
  long newPosition = myEnc.read();
  if (newPosition != oldPosition) {
    oldPosition = newPosition;
    remainder = abs(newPosition) % 128; //Calculates the time between 11.25 degree segments, one whole rotation is 4096 ticks. To get a reading once every full rotation, change it to 
    //remainder = abs(newPosition) % 4096;
    if(remainder == 0){
      Current_Time = millis();
      velocity = circumference /(32*(Current_Time - Start_Time)); //Velocity of the conveyor belt in mm/s. To get a reading once every full rotation, change it to 
      //velocity = circumference /(Current_Time - Start_Time)); //For one reading every 180°, set it to 2(Current_Time - Start_Time) and remainder = abs(newPosition) % 2048 and so on for other segment counts
      buffer[i] = velocity;
      i = i + 1; 
      if(i == 19){
        i = 0;
      }
      BufferAvg = 0;
      for(int j = 0; j < 19; j++){
        BufferAvg = buffer[j] + BufferAvg;
      }
      SmoothVelocity = BufferAvg / 20;
      //Serial.print("Velocity =");
      Serial.println(SmoothVelocity);
      //Serial.print(" m/s");
      //Serial.println('\n');
      Start_Time = Current_Time;
    }
  }
  }

