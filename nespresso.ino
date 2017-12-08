/* 
 * Nespresso
 * sacado de https://www.instructables.com/id/DIY-Nespresso-Capsule-Detector/
 * con modificaciones porque no funcionama
 * @nuria_pp
 * https://github.com/VentressAsajj/Nespresso
 */
/* Librerias */

/* LCD */
#include "SerLCD.h"
#include <SoftwareSerial.h>

/* RGB */
#include <SparkFunISL29125.h>
/* Para conexion de dispostivos i²C */
#include <Wire.h>

/* Definicion de pines */
#define SERLCD_PIN_RX  2

/* Definicion de variables globales y objetos*/
uint16_t rgbSensorR,rgbSensorG,rgbSensorB;

/* Declaracion objento de sensor RGB */
SFE_ISL29125 rgbSensor;

/* Declaracion del objeto pantalla 16x2 LCD */
SoftwareSerial serlcdNSS(0,SERLCD_PIN_RX);
SerLCD serlcd(serlcdNSS);


int ledState = LOW;
unsigned long previousMillis = 0;
const long interval = 4000;
bool detect = 0;


/* This code sets up the essentials for your circuit to work. It runs firsGt every time your circuit is powered with electricity. */
void setup() {
  // Setup Serial which is useful for debugging
  // Use the Serial Monitor to view printed messages
  Serial.begin(115200);
  Serial.println("start");
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);

  serlcdNSS.begin(9600); 
  serlcd.begin();   
  serlcd.setPosition(1,2);
  serlcd.print("Hola Nuria"); 
  serlcd.setPosition(2,2);
  serlcd.print("dia duro,huh?");  
  delay(5000);
      
  // Initialize the rgbSensor
  bool rgbSensorInitStatus = rgbSensor.init();
  if (rgbSensorInitStatus)
    Serial.println("rgbSensor Init OK!");
  else
    Serial.println("rgbSensor Init Failed! Check your wiring.");
}

/* This code is the main logic of your circuit. It defines the interaction between the components you selected. After setup, it runs over and over again, in an eternal loop. */
void loop() {
  unsigned long currentMillis = millis();

  if (rgbSensor.readBlue() < 1) {
    ledState = HIGH;
    digitalWrite(8, HIGH);
    digitalWrite(9, HIGH);
    detect = 1;
  }
  if (currentMillis - previousMillis >= interval && ledState == HIGH) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;
    digitalWrite(8, LOW);
    digitalWrite(9, LOW);
    detect = 0;
    serlcd.setBrightness(1);
  }

  int red = rgbSensor.readRed();
  int green = rgbSensor.readGreen();
  int blue = rgbSensor.readBlue();

  int cosi[3] = {229, 389, 329};
  //int dulsao[3] = {142, 253, 191};
  int dulsao[3] = {6, 253, 191};
  int roma[3] = {83, 196, 177};
  int livanto[3] = {188, 299, 187};
  int vivalto_lungo [3] = {134, 294, 449};
  int bukeela_lungo[3] = {330, 452, 319};
  //int kazaar[3] = {60, 165, 180};
  int kazaar[3] = {5, 10, 5};
  int volluto[3] = {263, 421, 248};

  int thresh = 20 ;
  
  Serial.print("Red:");
  Serial.print(rgbSensor.readRed());
  Serial.print("    Green:");
  Serial.print(rgbSensor.readGreen());
  Serial.print("    Blue:");
  Serial.print(rgbSensor.readBlue());
  Serial.println();
  delay(3000);
  
  if (detect) {

    //Cosi
    if (abs(red - cosi[0]) < thresh && abs(green - cosi[1]) < thresh && abs(blue - cosi[2]) < thresh ) {
      Serial.println("Cosi");
      serlcd.setBrightness(28);
      serlcd.clear();
      serlcd.setPosition(1,2);
      serlcd.print("Cosi");
      serlcd.setPosition(2,3);
      serlcd.print("Intensity: 4/10");
      delay(2500);
      serlcd.clear();
      serlcd.setPosition(1,2);
      serlcd.print("Cup Size: 40ml");
      serlcd.setPosition(2,3);
      serlcd.print("Fruity");
      delay(2500);
      serlcd.clear();
    }


    //Dulsao
    if (abs(red - dulsao[0]) < thresh && abs(green - dulsao[1]) < thresh && abs(blue - dulsao[2]) < thresh ) {
      Serial.println("Dulsao");
      serlcd.setBrightness(28);
      serlcd.clear();
      serlcd.setPosition(1,2);
      serlcd.print("Dulsao");
      serlcd.setPosition(2,3);
      serlcd.print("Intensity: 4/10");
      delay(2500);
      serlcd.clear();
      serlcd.setPosition(1,2);
      serlcd.print("Cup Size: 40ml");
      serlcd.setPosition(2,3);
      serlcd.print("Sweet Cereal");
      delay(2500);
      serlcd.clear();
    }

    //Roma
    if (abs(red - roma[0]) < thresh && abs(green - roma[1]) < thresh && abs(blue - roma[2]) < thresh ) {
      Serial.println("Roma");
      serlcd.setBrightness(28);
      serlcd.clear();
      serlcd.setPosition(1,2);
      serlcd.print("Roma");
      serlcd.setPosition(2,3);
      serlcd.print("Intensity: 8/10");
      delay(2500);
      serlcd.clear();
      serlcd.setPosition(1,2);
      serlcd.print("Cup Size: 25ml");
      serlcd.setPosition(2,3);
      serlcd.print("Woody");
      delay(2500);
      serlcd.clear();
    }

    //Livanto

    if (abs(red - livanto[0]) < thresh && abs(green - livanto[1]) < thresh && abs(blue - livanto[2]) < thresh ) {
      Serial.println("Livanto");
      serlcd.setBrightness(28);
      serlcd.clear();
      serlcd.setPosition(1,2);
      serlcd.print("Livanto");
      serlcd.setPosition(2,3);
      serlcd.print("Intensity: 6/10");
      delay(2500);
      serlcd.clear();
      serlcd.setPosition(1,2);
      serlcd.print("Cup Size: 40ml");
      serlcd.setPosition(2,3);
      serlcd.print("Caramel");
      delay(2500);
      serlcd.clear();
    }

    //Vivalto Lungo
    if (abs(red - vivalto_lungo[0]) < thresh && abs(green - vivalto_lungo[1]) < thresh && abs(blue - vivalto_lungo[2]) < thresh ) {
      Serial.println("Vivalto Lungo");
      serlcd.setBrightness(28);
      serlcd.clear();
      serlcd.setPosition(1,2);
      serlcd.print("Vivalto Lungo");
      serlcd.setPosition(2,3);
      serlcd.print("Intensity: 4/10");
      delay(2500);
      serlcd.clear();
      serlcd.setPosition(1,2);
      serlcd.print("Cup Size: 110ml");
      serlcd.setPosition(2,3);
      serlcd.print("Floral,Roasted");
      delay(2500);
      serlcd.clear();
    }

    //Bukeela Lungo
    if (abs(red - bukeela_lungo[0]) < thresh && abs(green - bukeela_lungo[1]) < thresh && abs(blue - bukeela_lungo[2]) < thresh ) {
      Serial.println("Bukeela Lungo");
      serlcd.setBrightness(28);
      serlcd.clear();
      serlcd.setPosition(1,2);
      serlcd.print("Bukeela Lungo");
      serlcd.setPosition(2,3);
      serlcd.print("Intensity: 3/10");
      delay(2500);
      serlcd.clear();
      serlcd.setPosition(1,2);
      serlcd.print("Cup Size: 110ml");
      serlcd.setPosition(2,3);
      serlcd.print("Wild, Floral");
      delay(2500);
      serlcd.clear(); 
    }

    //Kazaar
    if (abs(red - kazaar[0]) < thresh && abs(green - kazaar[1]) < thresh && abs(blue - kazaar[2]) < thresh ) {
      Serial.print("Kazaar");
      serlcd.clear();
      serlcd.setPosition(1,2);
      serlcd.print("Kazaar");
      serlcd.setBrightness(28);
      delay(4000);
      serlcd.clear();
      serlcd.setPosition(1,2);
      serlcd.print("Intensidad 12"); /* mañana con sueño */
      serlcd.setPosition(2,3);
      serlcd.print("mucho sueño");  
      delay(4000);
      serlcd.clear();
    }

    //Volluto
    if (abs(red - volluto[0]) < thresh && abs(green - volluto[1]) < thresh && abs(blue - volluto[2]) < thresh ) {
      Serial.println("Volluto");
      serlcd.setBrightness(28);
      serlcd.clear();
      serlcd.setPosition(1,2);
      serlcd.print("Volluto");
      serlcd.setPosition(2,3);
      serlcd.print("Intensity: 4/10");
      delay(2500);
      serlcd.clear();
      serlcd.setPosition(1,2);
      serlcd.print("Cup Size: 40ml");
      serlcd.setPosition(2,3);
      serlcd.print("Cereal Fruity");
      delay(2500);
      serlcd.clear();
    }
  }
}

