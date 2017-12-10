/* 
 * Nespresso
 * sacado de https://www.instructables.com/id/DIY-Nespresso-Capsule-Detector/
 * con modificaciones porque no funcionaba
 * @nuria_pp
 * https://github.com/VentressAsajj/Nespresso
 */
/*
 * 
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
/* pin2 LCD */
#define SERLCD_PIN_RX  2

/* Definicion de variables globales y objetos*/

/* Declaracion objento de sensor RGB */
SFE_ISL29125 RGB_Sensor;

/* Declaracion del objeto pantalla 16x2 LCD */
SoftwareSerial serlcdNSS(0,SERLCD_PIN_RX);
SerLCD serlcd(serlcdNSS);


int ledState = LOW;
unsigned long previousMillis = 0;
const long interval = 4000;
bool detect = 0;


/* Configure */
void setup() {

  /* Inicializacion del monitor serie para control de errores y demas */
  Serial.begin(115200);
  Serial.println("Iniciando programa");
  pinMode(8, OUTPUT); 
  pinMode(9, OUTPUT);

  serlcdNSS.begin(9600); 
  serlcd.begin();   
  serlcd.setPosition(1,0);
  serlcd.print("Buenos dias nena"); 
  serlcd.setPosition(2,0);
  serlcd.print("estas estupenda");  
  delay(4000);
  /* Detectando sensor RGB */    
  if (RGB_Sensor.init())
    Serial.println("Inicializacion correcta del sensor RBG");
  else
    Serial.println("Error iniciando sensor RBG");
    serlcd.setPosition(1,0);
    serlcd.print("Error sensor RBG"); 
    delay(4000);
}

/* principal */
void loop() {
  /* Devuelve el numero de milisegundos desde que el arduino se ha reseteado.
   * Ojo cuando llega a los 50 dias se resetea.
  */
  unsigned long currentMillis = millis(); 
  Serial.println("Milisegundos: ");
  Serial.println(currentMillis);

  /* leemos valores del sensor, 16bits integers*/
  unsigned int red = RGB_Sensor.readRed();
  unsigned int green = RGB_Sensor.readGreen();
  unsigned int blue = RGB_Sensor.readBlue();
  Serial.print("Red: "); Serial.println(red,HEX);
  Serial.print("Green: "); Serial.println(green,HEX);
  Serial.print("Blue: "); Serial.println(blue,HEX);
  Serial.println();
  delay(4000);

  
  if (RGB_Sensor.readBlue() < 1) {
    ledState = HIGH;
    digitalWrite(8, HIGH);
    digitalWrite(9, HIGH);
    detect = 1;
  }
  Serial.println("Detectado: ");
  Serial.print(detect);
  if (currentMillis - previousMillis >= interval && ledState == HIGH) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;
    digitalWrite(8, LOW);
    digitalWrite(9, LOW);
    detect = 0;
    serlcd.setBrightness(1);
  }

  /* Valores RGB para cada cafe */
  /*
  int cosi[3] = {229, 389, 329};
  int dulsao[3] = {142, 253, 191};
  int roma[3] = {83, 196, 177};
  int livanto[3] = {188, 299, 187};
  int vivalto_lungo [3] = {134, 294, 449};
  int bukeela_lungo[3] = {330, 452, 319};
  int kazaar[3] = {60, 165, 180};
  int volluto[3] = {263, 421, 248};
  */

  int cosi[3] = {229, 389, 329};
  int roma[3] = {83, 196, 177};
  int livanto[3] = {188, 299, 187};
  int vivalto_lungo [3] = {134, 294, 449};
  int volluto[3] = {263, 421, 248};
  
  int kazaar[3] = {60, 165, 180};
  int dulsao[3] = {142, 253, 191};
  int bukeela_lungo[3] = {330, 452, 319};
  
  int thresh = 20 ;
  /* comentar cuando ya se tenga los valores RGB para cada cafe*/
  Serial.print("Red:");
  Serial.print(RGB_Sensor.readRed());
  Serial.print("    Green:");
  Serial.print(RGB_Sensor.readGreen());
  Serial.print("    Blue:");
  Serial.print(RGB_Sensor.readBlue());
  Serial.println();
  delay(3000);
  
  detect = 1;
  if (detect) {

    /* Cosi */
    if (abs(red - cosi[0]) < thresh && abs(green - cosi[1]) < thresh && abs(blue - cosi[2]) < thresh ) {
      Serial.println("Cosi");
      serlcd.setBrightness(28);
      serlcd.clear();
      serlcd.setPosition(1,0);
      serlcd.print("Cosi");
      serlcd.setPosition(2,0);
      serlcd.print("Intensidad: 4");
      delay(4000);
    }

    /* Dulsao */
    if (abs(red - dulsao[0]) < thresh && abs(green - dulsao[1]) < thresh && abs(blue - dulsao[2]) < thresh ) {
      Serial.println("Dulsao");
      serlcd.setBrightness(28);
      serlcd.clear();
      serlcd.setPosition(1,0);
      serlcd.print("Dulsao");
      serlcd.setPosition(2,0);
      serlcd.print("Intensidad: 4");
      delay(4000);
    }

    /* Roma */
    if (abs(red - roma[0]) < thresh && abs(green - roma[1]) < thresh && abs(blue - roma[2]) < thresh ) {
      Serial.println("Roma");
      serlcd.setBrightness(28);
      serlcd.clear();
      serlcd.setPosition(1,0);
      serlcd.print("Roma");
      serlcd.setPosition(2,0);
      serlcd.print("Intensidad: 8");
      delay(4000);
    }

    /* Livanto */
    if (abs(red - livanto[0]) < thresh && abs(green - livanto[1]) < thresh && abs(blue - livanto[2]) < thresh ) {
      Serial.println("Livanto");
      serlcd.setBrightness(28);
      serlcd.clear();
      serlcd.setPosition(1,0);
      serlcd.print("Livanto");
      serlcd.setPosition(2,0);
      serlcd.print("Intensidad: 6");
      delay(4000);
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
    }

    /* Kazaar */
    if (abs(red - kazaar[0]) < thresh && abs(green - kazaar[1]) < thresh && abs(blue - kazaar[2]) < thresh ) {
      Serial.print("Kazaar");
      serlcd.setBrightness(28);
      serlcd.clear();
      serlcd.setPosition(1,0);
      serlcd.print("Kazaar");
      serlcd.setPosition(2,0);
      serlcd.print("Intensidad: 10");
      delay(4000);
      serlcd.clear();
      serlcd.setPosition(1,0);
      serlcd.print("Presiento que hoy");
      serlcd.setPosition(2,0);
      serlcd.print("es un dia duro");
      delay(4000);
    }

    /* Volluto */
    if (abs(red - volluto[0]) < thresh && abs(green - volluto[1]) < thresh && abs(blue - volluto[2]) < thresh ) {
      Serial.println("Volluto");
      serlcd.setBrightness(28);
      serlcd.clear();
      serlcd.setPosition(1,0);
      serlcd.print("Volluto");
      serlcd.setPosition(2,0);
      serlcd.print("Intensidad: 4");
      delay(4000);
    }
  }
}

