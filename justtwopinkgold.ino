#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>


// GUItool: begin automatically generated code
AudioSynthWaveform       waveform2;      //xy=170,223
AudioSynthWaveform       waveform1;      //xy=180,97
AudioEffectDigitalCombine combine1;       //xy=386,161
AudioMixer4              mixer1;         //xy=566,284
AudioOutputAnalog        dac1;           //xy=743,167
AudioConnection          patchCord1(waveform2, 0, combine1, 1);
AudioConnection          patchCord2(waveform1, 0, combine1, 0);
AudioConnection          patchCord6(combine1, 0, mixer1, 0);
AudioConnection          patchCord7(mixer1, dac1);
// GUItool: end automatically generated code



//start of smoothing wave 1
// Define the number of samples to keep track of. The higher the number, the
// more the readings will be smoothed, but the slower the output will respond to
// the input. Using a constant rather than a normal variable lets us use this
// value to determine the size of the readings array.
const int numReadings = 3;

int readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int total = 0;                  // the running total
int average = 0;                // the average

int inputPin = A0; //currently stretch
int inputPin2 = A1; //second stretch
int inputPin3 = A6; //currently stretch
int inputPin4 = A5; //second stretch

//second pin
const int numReadings2 = 2;

int readings2[numReadings2];      // the readings from the analog input
int readIndex2 = 0;              // the index of the current reading
int total2 = 0;                  // the running total
int average2 = 0;                // the average


void setup() {
  // put your setup code here, to run once:
  AudioMemory(50); // Dynamic memory is allocated to be used exclusively by the Audio library
  waveform1.begin(0.85, 100, WAVEFORM_SINE);
  waveform1.pulseWidth(0.15);
  waveform2.begin(0.85, 100, WAVEFORM_SINE);
  combine1.setCombineMode(AudioEffectDigitalCombine::MODULO);
  

  // initialize serial communication with computer:
  Serial.begin(9600);
  // initialize all the readings to 0:
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }

  // initialize all the  second readings to 0:
  for (int thisReading2 = 0; thisReading2 < numReadings2; thisReading2++) {
    readings2[thisReading2] = 0;
  }

}

void loop() {
  // put your main code here, to run repeatedly:
  // smoothing subtract the last reading:
  total = total - readings[readIndex];
  // read from the sensor:
  readings[readIndex] = analogRead(inputPin);
  // add the reading to the total:
  total = total + readings[readIndex];
  // advance to the next position in the array:
  readIndex = readIndex + 1;

  // if we're at the end of the array...
  if (readIndex >= numReadings) {
    // ...wrap around to the beginning:
    readIndex = 0;
  }

  // calculate the average:
  average = total / numReadings;
  // send it to the computer as ASCII digits
  
  delay(1);        // delay in between reads for stability
   int potValue = average;
   float scaledPot = map(potValue, 400, 1100, -100, 500) ;

   

 
  //turning off volume when scaled pot is lower than 13
 
// waveform1.amplitude(0.8);
  waveform1.frequency(scaledPot);

 //second smoothing
// subtract the last reading:
  total2 = total2 - readings2[readIndex2];
  // read from the sensor:
  readings2[readIndex2] = analogRead(inputPin2);
  // add the reading to the total:
  total2 = total2 + readings2[readIndex2];
  // advance to the next position in the array:
  readIndex2 = readIndex2 + 1;

  // if we're at the end of the array...
  if (readIndex2 >= numReadings2) {
    // ...wrap around to the beginning:
    readIndex2 = 0;
  }

  // calculate the average:
  average2 = total2 / numReadings2;
  // send it to the computer as ASCII digits
  
  delay(1);        // delay in between reads for stability

  int potValue2 = average2;
   float scaledPot2 = map(potValue2, 280, 1100, -50, 900);


   Serial.print("pot before scale:");
   Serial.println(scaledPot2);
  
//Serial.print("POT 2 :");
//Serial.println(potValue2); 
   
waveform2.frequency(scaledPot2);
}
