#include <Wire.h>
#include "Adafruit_TCS34725.h"
#include <Adafruit_NeoPixel.h>

#ifdef __AVR__
  #include <avr/power.h>
#endif

// Pick analog outputs, for the UNO these three work well
// use ~560  ohm resistor between Red & Blue, ~1K for green (its brighter)
#define PIN 2         

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      30
#define redpin 3
#define greenpin 5
#define bluepin 8

// for a common anode LED, connect the common pin to +5V
// for common cathode, connect the common to ground

// set to false if using a common cathode LED
#define commonAnode true

// our RGB -> eye-recognized gamma color
byte gammatable[256];
int Red;
int Green;
int Blue;
float red, green, blue;
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_16X);
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
int kras;
int zel;
int siin;
int delayval = 10; // delay for half a second
void otisovka()
    {kras=20;
    zel=10;
    siin=5;
      Serial.println("otrisovka");
      for(int i=0;i<NUMPIXELS;i++){

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(kras,zel,siin)); // Moderately bright green color.

    pixels.show(); // This sends the updated pixel color to the hardware.

    delay(delayval); // Delay for a period of time (in milliseconds).

  }
    }
void setup() {
  Serial.begin(9600);
  //Serial.println("Color View Test!");
    pinMode(12, OUTPUT);
    digitalWrite(12,1);
  /*if (tcs.begin()) {
    //Serial.println("Found sensor");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1); // halt!
  }*/

  // use these three pins to drive an LED
#if defined(ARDUINO_ARCH_ESP32)
  ledcAttachPin(redpin, 1);
  ledcSetup(1, 12000, 8);
  ledcAttachPin(greenpin, 2);
  ledcSetup(2, 12000, 8);
  ledcAttachPin(bluepin, 3);
  ledcSetup(3, 12000, 8);
#else
  pinMode(redpin, OUTPUT);
  pinMode(greenpin, OUTPUT);
  pinMode(bluepin, OUTPUT);
#endif

  // thanks PhilB for this gamma table!
  // it helps convert RGB colors to what humans see
  for (int i=0; i<256; i++) {
    float x = i;
    x /= 255;
    x = pow(x, 2.5);
    x *= 255;

    if (commonAnode) {
      gammatable[i] = 255 - x;
    } else {
      gammatable[i] = x;
    }
    Serial.println(gammatable[i]);
  }
  #if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code

  pixels.begin(); // This initializes the NeoPixel library.

}



void loop() {
  
  tcs.setInterrupt(false);  // turn on LED

  delay(50);  // takes 50ms to read

  tcs.getRGB(&red, &green, &blue);
  
  tcs.setInterrupt(true);  // turn off LED

  Serial.print("R:\t"); Serial.print(int(red)); 
  Serial.print("\tG:\t"); Serial.print(int(green)); 
  Serial.print("\tB:\t"); Serial.println(int(blue));
  Serial.println(255-gammatable[(int)red]);
  Serial.println(255-gammatable[(int)green]);
  Serial.println(255-gammatable[(int)blue]);
 /* if(red>100){red=red+100;
             green=green-50;
             blue=blue-50;}
   if(green>100){green=green+50;}
    if(blue>100){blue=blue+50;}*/
    
  if(red>100||green>100||blue>100){
    Serial.println("vizhu");
    red=255-gammatable[(int)red];
    green=255-gammatable[(int)green];
    blue=255-gammatable[(int)blue];
    if(red>60)//розовый
    {
      Serial.println("Rozoviy");
      kras=60;
      zel=5;
      siin=7;
      otisovka();
    }
    if( green>20 && green<45 && red>15)//;жёлтый
    {
      Serial.println("joltiy");
      kras=23;
      zel=10;
      siin=2;
      otisovka();
    }
     if(red<5 && blue>20)//жёлтый
    {
      Serial.println("Fioletoviy");
      kras=3;
      zel=2;
      siin=40;
      otisovka();
    }
       if( green>20 && green<45 && red<10)//;жёлтый
    {
      Serial.println("zel");
      kras=5;
      zel=20;
      siin=2;
      otisovka();
    }
  delay(300);
  }
//  Serial.print("\t");
//  Serial.print((int)red, HEX); Serial.print((int)green, HEX); Serial.print((int)blue, HEX);
  Serial.print("\n");

//  uint16_t red, green, blue, clear;
//  
//  tcs.setInterrupt(false);  // turn on LED
//
//  delay(60);  // takes 50ms to read
//
//  tcs.getRawData(&red, &green, &blue, &clear);
//  
//  tcs.setInterrupt(true);  // turn off LED
//
//  Serial.print("C:\t"); Serial.print(int(clear)); 
//  Serial.print("R:\t"); Serial.print(int(red)); 
//  Serial.print("\tG:\t"); Serial.print(int(green)); 
//  Serial.print("\tB:\t"); Serial.print(int(blue));
//  Serial.println();
otisovka();
#if defined(ARDUINO_ARCH_ESP32)
  ledcWrite(1, gammatable[(int)red]);
  ledcWrite(2, gammatable[(int)green]);
  ledcWrite(3, gammatable[(int)blue]);
#else
  analogWrite(redpin, gammatable[(int)red]);
  analogWrite(greenpin, gammatable[(int)green]);
  analogWrite(bluepin, gammatable[(int)blue]);
#endif
}
