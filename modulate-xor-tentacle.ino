#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>


// GUItool: begin automatically generated code
AudioSynthWaveform       waveform2;      //xy=170,223
AudioSynthWaveform       waveform1;      //xy=180,97
AudioSynthWaveform       waveform4;      //xy=179,382
AudioSynthWaveform       waveform3;      //xy=191,317
AudioEffectDigitalCombine combine2;       //xy=368,366
AudioEffectDigitalCombine combine1;       //xy=386,161
AudioMixer4              mixer1;         //xy=566,284
AudioOutputAnalog        dac1;           //xy=743,167
AudioConnection          patchCord1(waveform2, 0, combine1, 1);
AudioConnection          patchCord2(waveform1, 0, combine1, 0);
AudioConnection          patchCord3(waveform4, 0, combine2, 1);
AudioConnection          patchCord4(waveform3, 0, combine2, 0);
AudioConnection          patchCord5(combine2, 0, mixer1, 1);
AudioConnection          patchCord6(combine1, 0, mixer1, 0);
AudioConnection          patchCord7(mixer1, dac1);
// GUItool: end automatically generated code



//start of smoothing wave 1
// Define the number of samples to keep track of. The higher the number, the
// more the readings will be smoothed, but the slower the output will respond to
// the input. Using a constant rather than a normal variable lets us use this
// value to determine the size of the readings array.
const int numReadings = 2;

int readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int total = 0;                  // the running total
int average = 0;                // the average

int inputPin = A8; //currently stretch
int inputPin2 = A9; //second stretch
int inputPin3 = A2; //currently stretch
int inputPin4 = A3; //second stretch

//second pin
const int numReadings2 = 2;

int readings2[numReadings2];      // the readings from the analog input
int readIndex2 = 0;              // the index of the current reading
int total2 = 0;                  // the running total
int average2 = 0;                // the average

//third pin
const int numReadings3 = 2;

int readings3[numReadings3];      // the readings from the analog input
int readIndex3 = 0;              // the index of the current reading
int total3 = 0;                  // the running total
int average3 = 0;                // the average

//fourth pin
const int numReadings4 = 2;

int readings4[numReadings4];      // the readings from the analog input
int readIndex4 = 0;              // the index of the current reading
int total4 = 0;                  // the running total
int average4 = 0;                // the average

void setup() {
  // put your setup code here, to run once:
  AudioMemory(50); // Dynamic memory is allocated to be used exclusively by the Audio library
  waveform1.begin(0.85, 100, WAVEFORM_TRIANGLE);
  waveform1.pulseWidth(0.15);
  waveform2.begin(0.85, 100, WAVEFORM_TRIANGLE);
  combine1.setCombineMode(AudioEffectDigitalCombine::XOR);
  
  waveform3.begin(0.85, 100, WAVEFORM_SQUARE);
  waveform4.begin(0.85, 100, WAVEFORM_SQUARE);
  combine2.setCombineMode(AudioEffectDigitalCombine::XOR);

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
   // initialize all the third readings to 0:
  for (int thisReading3 = 0; thisReading3 < numReadings3; thisReading3++) {
    readings3[thisReading3] = 0;
  }

  // initialize all the fourth readings to 0:
  for (int thisReading4 = 0; thisReading4 < numReadings4; thisReading4++) {
    readings4[thisReading4] = 0;
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
   float scaledPot = (((float)potValue -940) /80 )* 1000  ;

   
//Serial.print("pot before scale:");
//   Serial.println(potValue);
 
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
   int scaledPotStart2 = potValue2 - 720  ;
   float scaledPot2 = ((float)scaledPotStart2 / 400 ) * 200;

 //third smoothing
// subtract the last reading:
  total3 = total3 - readings3[readIndex3];
  // read from the sensor:
  readings3[readIndex3] = analogRead(inputPin3);
  // add the reading to the total:
  total3 = total3 + readings3[readIndex3];
  // advance to the next position in the array:
  readIndex3 = readIndex3 + 1;

  // if we're at the end of the array...
  if (readIndex3 >= numReadings3) {
    // ...wrap around to the beginning:
    readIndex3 = 0;
  }

  // calculate the average:
  average3 = total3 / numReadings3;
  // send it to the computer as ASCII digits
  
  delay(1);        // delay in between reads for stability

  int potValue3 = average3;
   int scaledPotStart3 = potValue3 - 830  ;
   float scaledPot3 = ((float)scaledPotStart3 / 200 ) * 1200;

 //fourth smoothing
// subtract the last reading:
  total4 = total4 - readings4[readIndex4];
  // read from the sensor:
  readings4[readIndex4] = analogRead(inputPin4);
  // add the reading to the total:
  total4 = total4 + readings4[readIndex4];
  // advance to the next position in the array:
  readIndex4 = readIndex4 + 1;

  // if we're at the end of the array...
  if (readIndex4 >= numReadings4) {
    // ...wrap around to the beginning:
    readIndex4 = 0;
  }

  // calculate the average:
  average4 = total4 / numReadings4;
  // send it to the computer as ASCII digits
  
  delay(1);        // delay in between reads for stability

  int potValue4 = average4;
   int scaledPotStart4 = potValue4 - 720  ;
   float scaledPot4 = ((float)scaledPotStart4 / 400 ) * 200;
   
  
Serial.print("purple TENTACLE :");
Serial.println(scaledPot3); 
   
waveform2.frequency(scaledPot2);
}
