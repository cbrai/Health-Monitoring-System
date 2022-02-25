// ---------------------------------------------------------------- //
// Arduino Ultrasoninc Sensor HC-SR04
// Re-writed by Arbi Abdul Jabbaar
// Using Arduino IDE 1.8.7
// Using HC-SR04 Module
// Tested on 17 September 2019
// ---------------------------------------------------------------- //
#include <Wire.h> //including the wire library that enables I2C communication  
#include <Adafruit_SSD1306.h> //including the library necessary for work with OLED display
 
#define SCREEN_WIDTH 128 //defining the display width, in pixels 
#define SCREEN_HEIGHT 32 //defining the display height, in pixels 
#define echoPin 2 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 3
#define buzz 12//attach pin D3 Arduino to pin Trig of HC-SR04

//Our OLED display library constructor, in order to have access to the functions that control the display 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire);

// defines variables
long duration; // variable for the duration of sound wave travel
float distance;
float dist_feet;// variable for the distance measurement

void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT);
  pinMode(buzz, OUTPUT);
  Serial.begin(9600); // // Serial Communication is starting with 9600 of baudrate speed
  Serial.println("Ultrasonic Sensor HC-SR04 Test"); // print some text in Serial Monitor
  Serial.println("with Arduino UNO R3");
  Serial.begin(9600);//Serial communication initialization ( speed 9600 baud)
 //OLED display library initialization
 // SSD1306_SWITCHCAPVCC = generates the voltage for the display(7-9 V) from the 3.3V voltage that it has from the voltage regulator
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // 0x3C address for the 128x32 display
 //if the initialization is not successful on the Serial monitor we receive an error message 
  Serial.println(F("SSD1306 allocation failed"));
  for(;;); //an infinite loop, if the initialization is unsuccessful, for the program to stop performing
  }
}
void loop() {
  // Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  dist_feet = distance/30.48;
  // Displays the distance on the Serial Monitor
  Serial.print(" Distance: ");
  Serial.print(distance);
  Serial.print(" cm");
  Serial.print("\n");
  Serial.print("Distance(feet): ");
  Serial.print(dist_feet);
  Serial.print(" feet");
  delay(500);
  display.clearDisplay();//function for deleting everything off the display
  display.setTextSize(1.5);//function for setting the text size 
  display.setTextColor(WHITE);//function for setting the color of the text (our display can only contain one color) 
  display.setCursor(0,0);//function for setting the cursor (0-128,0-32) on the display where we want to start printing the text 
  display.print("Distance: ");//function for displaying the text we deliver 
  display.print(distance);//displays temperature 
  display.print(" cm");//displaying the space and cm, in order to know that the temperature is measured in degrees Celsius 
  display.setCursor(0,10);
  display.print("Distance(ft): ");
  display.print(dist_feet);
  display.println(" ft");
  if(dist_feet<=3){
    display.setCursor(0,20);// 
    display.print("       Danger");
    siren();
  }
  else
  {
    digitalWrite(buzz, LOW);
  }
  display.display();//displaying the full text that we have previously sent to the buffer of the display
  delay(1000);//1 second pause in order for the values not to change constantly 
 }
void siren() { //This function produces the 3rd siren (AMBULANCE sound).tone(buzz,440,200);
delay(300);
for(int i=3;i<=6;i++)
digitalWrite(i,HIGH);
noTone(buzz);
tone(buzz,494,500);
delay(300);
for(int i=3;i<=6;i++)
{ digitalWrite(i,LOW);
digitalWrite(i+6,HIGH); }
noTone(buzz);
tone(buzz,523,300);
delay(200);
digitalWrite(7,HIGH);
delay(50);
digitalWrite(8,HIGH);
delay(50);
noTone(buzz);
}
