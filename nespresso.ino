/* 
 * Nespresso
 * sacado de https://www.instructables.com/id/DIY-Nespresso-Capsule-Detector/
 * con modificaciones porque no funcionaba
 * @nuria_pp
 * https://github.com/VentressAsajj/Nespresso
 */
  /*  Funcion millis()
   *  Devuelve el numero de milisegundos desde que el arduino se ha reseteado.
   * Ojo cuando llega a los 50 dias se resetea.
  */
  /*
   * Las interrupciones se activan si se recibe un valor superior 
   * o inferior a los umbrales alto, 0xFFFF o bajo 0x0000. Son las 
   * mas altas o bajas que se pueden dar.
   * Podemos configurar CFG3_INT_PRST1 para que se dispare la interrupcion
   * cuando se detecte una vez, o CFG3_INT_PRST8 si se detecta ocho veces, 
   * el sensor deberá tener ocho lecturas consecutivas, con 8 lecturas se
   * evitan falsos positivos. Los valores para PRST pueden ser 1,2,4 u 8.
   */

 /*
  * Probrema a la hora de detectar colores similares. Por diseño de la "caja" donde
  * van los sensores y el arduino, no hay espacio para meter otro led. Se puede hacer
  * otro agujero o retocar el diseño3D, (pereza, va a ser que no!)
  * Soluciones aportadas por la comunidad:
  * 
  *   @javierfpanadero: Sumar los colores y ver la diferencia que hay entre ellos.
  *   @@Nicky69es: Hacer dos lecturas, una con el led encendido y otra con el led
  *   con memor intensidad. En una de las dos dará diferente. Eso espero :D
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

/*
 * Definicion de constantes o variables
 */
int ledState = LOW;
const int pinLed = 9;

unsigned long previousMillis = 0;
//const long interval = 4000;
const long interval = 6000;
bool detect = 0;
int capsulasDetectadas = 0;
int thresh;  

int red;
int green;
int blue;

/*
 * Valores RGB iniciales sin detectar capsula:
 *    R:2181 G:3897 B:2707
*/
 
int kazaar[3]          = {1720,4920,3600};    //****
int arpeggio[3]        = {1800,4400,3450};    //****
int ristretto[3]       = {1530,4220,2655};    //**
int capriccio[3]       = {2080,5500,3240};    //***
int roma[3]            = {2300,5650,3660};    //**
int indriya[3]         = {3770,9010,4800};    //*
int rosabaya[3]        = {9380,21170,12250};  //*
int volutto[3]         = {9470,17800,6430};   //*
int dulsao[3]          = {12700,28950,14000}; //
int livanto[3]         = {4410,7580,3450};    //**
int cosi[3]            = {6650,15100,8310};   //**
int dharkan[3]         = {2290,6845,4730};    //***
int linizio_lungo[3]   = {9950,14570,4770};   //***
int bukeela_lungo[3]   = {12150,22240,10100};  //
int fortissio_lungo[3] = {2725,8800,5790};    //**
int vivalto_lungo[3]   = {4410,16590,16350};  //*
int envivo_lungo[3]    = {5250,7850,3750};    //***

/* Configure */
void setup() {

  /* Inicializacion del monitor serie para control de errores y demas */
  Serial.begin(115200);
  Serial.println("Iniciando programa");
  // led 9/A0 es el blanco
  pinMode(pinLed,OUTPUT);
  
  serlcdNSS.begin(9600); 
  serlcd.begin();   
  serlcd.setPosition(1,0);
  serlcd.print("Buenos dias nena"); 
  serlcd.setPosition(2,0);
  serlcd.print("estas estupenda");  
  delay(2000);
  /* Detectando sensor RGB */    
  if (RGB_Sensor.init()){
    Serial.println("Inicializacion correcta del sensor RGB");
    RGB_Sensor.config(CFG1_MODE_RGB | CFG1_375LUX, CFG2_IR_ADJUST_LOW, CFG3_NO_INT);
  }  
  else {
    Serial.println("Error iniciando sensor RGB");
    serlcd.clear();
    serlcd.setPosition(1,0);
    serlcd.print("Error sensor RGB"); 
    delay(4000);
  }
}

/* principal */
void loop() {
 
  unsigned long currentMillis = millis();
   
  if(capsulasDetectadas > 1){
    Serial.print("Capsulas detectadas ");
    Serial.println(capsulasDetectadas);
    analogWrite(pinLed,25); // 
    detectarCapsulas();
    capsulasDetectadas = 0;
  }

  if (blue <= 1) {
    ledState = HIGH;
    analogWrite(pinLed,255);
    detect = 1;
    capsulasDetectadas = 0;
  }
  
  if (currentMillis - previousMillis >= interval && ledState == HIGH) {
    // guardamos la ultima vez que parpadeo el led
    previousMillis = currentMillis;
    analogWrite(pinLed,0);
    detect = 0;
    serlcd.clear();
    serlcd.setPosition(1,0);
    serlcd.print("No hay capsulas");
    serlcd.setBrightness(0);
    capsulasDetectadas = 0;
  }
  /* leemos valores del sensor, 16bits integers*/
  red   = RGB_Sensor.readRed();
  green = RGB_Sensor.readGreen();
  blue  = RGB_Sensor.readBlue();

  /* rango de medicion */
  thresh = 300;
  if (detect) {
    detectarCapsulas();
  }
}

void detectarCapsulas(){

  
  /* comentar cuando ya se tenga los valores RGB para cada cafe*/
  /* Serial.println(red, DEC|HEX) */
  
  Serial.print("R: ");  Serial.print(red,  DEC);
  Serial.print(" G: "); Serial.print(green,DEC);
  Serial.print(" B: "); Serial.print(blue, DEC);
  Serial.println();
  /* Kazaar */
  if (abs(red - kazaar[0]) < thresh && abs(green - kazaar[1]) < thresh && abs(blue - kazaar[2]) < thresh ) {
    Serial.println("Kazaar");
    serlcd.setBrightness(28);
    serlcd.clear();
    serlcd.setPosition(1,0);
    serlcd.print("kazaar");
    serlcd.setPosition(2,0);
    serlcd.print("Intensidad 12");
    delay(1000);
    serlcd.clear();
    serlcd.setPosition(1,0);
    serlcd.print("Espresso 25ml 40ml");
    serlcd.setPosition(2,0);
    serlcd.print("intenso");
    delay(1000);
    serlcd.clear();
    ++capsulasDetectadas;
  }
  /* Ristretto */
  if (abs(red - ristretto[0]) < thresh && abs(green - ristretto[1]) < thresh && abs(blue - ristretto[2]) < thresh ) {
    Serial.println("Ristretto");
    serlcd.setBrightness(28);
    serlcd.clear();
    serlcd.setPosition(1,0);
    serlcd.print("ristretto");
    serlcd.setPosition(2,0);
    serlcd.print("Intensidad 10");
    delay(1000);
    serlcd.clear();
    serlcd.setPosition(1,0);
    serlcd.print("Espresso 25ml 40ml");
    serlcd.setPosition(2,0);
    serlcd.print("intenso");
    delay(1000);
    serlcd.clear();
    ++capsulasDetectadas;
  }
  /* arpeggio */
  if (abs(red - arpeggio[0]) < thresh && abs(green - arpeggio[1]) < thresh && abs(blue - arpeggio[2]) < thresh ) {
    Serial.println("Arpeggio");
    serlcd.setBrightness(28);
    serlcd.clear();
    serlcd.setPosition(1,0);
    serlcd.print("arpeggio");
    serlcd.setPosition(2,0);
    serlcd.print("Intensidad 9");
    delay(1000);
    serlcd.clear();
    serlcd.setPosition(1,0);
    serlcd.print("Espresso 25ml 40ml");
    serlcd.setPosition(2,0);
    serlcd.print("intenso, cremoso");
    delay(1000);
    serlcd.clear();
    ++capsulasDetectadas;
  }
  /* capriccio */
  if (abs(red - capriccio[0]) < thresh && abs(green - capriccio[1]) < thresh && abs(blue - capriccio[2]) < thresh ) {
    Serial.println("Capriccio");
    serlcd.setBrightness(28);
    serlcd.clear();
    serlcd.setPosition(1,0);
    serlcd.print("Capriccio");
    serlcd.setPosition(2,0);
    serlcd.print("Intensidad 5");
    delay(1000);
    serlcd.clear();
    serlcd.setPosition(1,0);
    serlcd.print("Espresso 40ml");
    serlcd.setPosition(2,0);
    serlcd.print("intenso");
    delay(1000);
    serlcd.clear();
    ++capsulasDetectadas;
  }
  /* roma */
  if (abs(red - roma[0]) < thresh && abs(green - roma[1]) < thresh && abs(blue - roma[2]) < thresh ) {
    Serial.println("Roma");
    serlcd.setBrightness(28);
    serlcd.clear();
    serlcd.setPosition(1,0);
    serlcd.print("roma");
    serlcd.setPosition(2,0);
    serlcd.print("Intensidad 8");
    delay(1000);
    serlcd.clear();
    serlcd.setPosition(1,0);
    serlcd.print("Espresso 25ml 40ml");
    serlcd.setPosition(2,0);
    serlcd.print("intenso");
    delay(1000);
    serlcd.clear();
    ++capsulasDetectadas;
  }
  /* Indriya */
  if (abs(red - indriya[0]) < thresh && abs(green - indriya[1]) < thresh && abs(blue - indriya[2]) < thresh ) {
    Serial.println("Indriya");
    serlcd.setBrightness(28);
    serlcd.clear();
    serlcd.setPosition(1,0);
    serlcd.print("indriya");
    serlcd.setPosition(2,0);
    serlcd.print("Intensidad 10");
    delay(1000);
    serlcd.clear();
    serlcd.setPosition(1,0);
    serlcd.print("Espresso 25ml 40ml");
    serlcd.setPosition(2,0);
    serlcd.print("intenso");
    delay(1000);
    serlcd.clear();
    ++capsulasDetectadas;
  }
  /* Dulsao */
  if (abs(red - dulsao[0]) < thresh && abs(green - dulsao[1]) < thresh && abs(blue - dulsao[2]) < thresh ) {
    Serial.println("Dulsao");
    serlcd.setBrightness(28);
    serlcd.clear();
    serlcd.setPosition(1,0);
    serlcd.print("dulsao");
    serlcd.setPosition(2,0);
    serlcd.print("Intensidad 4");
    delay(1000);
    serlcd.clear();
    serlcd.setPosition(1,0);
    serlcd.print("Espresso 40ml");
    serlcd.setPosition(2,0);
    serlcd.print("equilibrado");
    delay(1000);
    serlcd.clear();
    ++capsulasDetectadas;
  }
  /* rosabaya */
  if (abs(red - rosabaya[0]) < thresh && abs(green - rosabaya[1]) < thresh && abs(blue - rosabaya[2]) < thresh ) {
    Serial.println("Rosabaya");
    serlcd.setBrightness(28);
    serlcd.clear();
    serlcd.setPosition(1,0);
    serlcd.print("rosabaya");
    serlcd.setPosition(2,0);
    serlcd.print("Intensidad 6");
    delay(1000);
    serlcd.clear();
    serlcd.setPosition(1,0);
    serlcd.print("Espresso 40ml");
    serlcd.setPosition(2,0);
    serlcd.print("afrutado");
    delay(1000);
    serlcd.clear();
    ++capsulasDetectadas;
  }
  /* volutto */
  if (abs(red - volutto[0]) < thresh && abs(green - volutto[1]) < thresh && abs(blue - volutto[2]) < thresh ) {
    Serial.println("Volutto");
    serlcd.setBrightness(28);
    serlcd.clear();
    serlcd.setPosition(1,0);
    serlcd.print("volutto");
    serlcd.setPosition(2,0);
    serlcd.print("Intensidad 4");
    delay(1000);
    serlcd.clear();
    serlcd.setPosition(1,0);
    serlcd.print("Espresso 110ml");
    serlcd.setPosition(2,0);
    serlcd.print("equilibrado");
    delay(1000);
    serlcd.clear();
    ++capsulasDetectadas;
  }
  /* vivalto_lungo */
  if (abs(red - vivalto_lungo[0]) < thresh && abs(green - vivalto_lungo[1]) < thresh && abs(blue - vivalto_lungo[2]) < thresh ) {
    Serial.println("Vivalto Lungo");
    serlcd.setBrightness(28);
    serlcd.clear();
    serlcd.setPosition(1,0);
    serlcd.print("vivalto lungo");
    serlcd.setPosition(2,0);
    serlcd.print("Intensidad 4");
    delay(1000);
    serlcd.clear();
    serlcd.setPosition(1,0);
    serlcd.print("Espresso 110ml");
    serlcd.setPosition(2,0);
    serlcd.print("afrutado");
    delay(1000);
    serlcd.clear();
  }
  /* Bukeela Lungo */
  if (abs(red - bukeela_lungo[0]) < thresh && abs(green - bukeela_lungo[1]) < thresh && abs(blue - bukeela_lungo[2]) < thresh ) {
    Serial.println("bukeela lungo");
    serlcd.setBrightness(28);
    serlcd.clear();
    serlcd.setPosition(1,0);
    serlcd.print("bukeela lungo");
    serlcd.setPosition(2,0);
    serlcd.print("Intensidad 3");
    delay(1000);
    serlcd.clear();
    serlcd.setPosition(1,0);
    serlcd.print("Espresso 110ml");
    serlcd.setPosition(2,0);
    serlcd.print("Ethiopia");
    delay(1000);
    serlcd.clear();
    ++capsulasDetectadas;
  }
  /* livanto */
  if (abs(red - livanto[0]) < thresh && abs(green - livanto[1]) < thresh && abs(blue - livanto[2]) < thresh ) {
    Serial.println("livanto");
    serlcd.setBrightness(28);
    serlcd.clear();
    serlcd.setPosition(1,0);
    serlcd.print("livanto");
    serlcd.setPosition(2,0);
    serlcd.print("Intensidad 6");
    delay(1000);
    serlcd.clear();
    serlcd.setPosition(1,0);
    serlcd.print("Espresso 40ml");
    serlcd.setPosition(2,0);
    serlcd.print("caramelizado");
    delay(1000);
    serlcd.clear();
    ++capsulasDetectadas;
  }
  /* cosi */
  if (abs(red - cosi[0]) < thresh && abs(green - cosi[1]) < thresh && abs(blue - cosi[2]) < thresh ) {
    Serial.println("cosi");
    serlcd.setBrightness(28);
    serlcd.clear();
    serlcd.setPosition(1,0);
    serlcd.print("cosi");
    serlcd.setPosition(2,0);
    serlcd.print("Intensidad 4");
    delay(1000);
    serlcd.clear();
    serlcd.setPosition(1,0);
    serlcd.print("Espresso 40ml");
    serlcd.setPosition(2,0);
    serlcd.print("afrutado");
    delay(1000);
    serlcd.clear();
    ++capsulasDetectadas;
  }
  /* dharkan */
  if (abs(red - dharkan[0]) < thresh && abs(green - dharkan[1]) < thresh && abs(blue - dharkan[2]) < thresh ) {
    Serial.println("dharkan");
    serlcd.setBrightness(28);
    serlcd.clear();
    serlcd.setPosition(1,0);
    serlcd.print("dharkan");
    serlcd.setPosition(2,0);
    serlcd.print("Intensidad 11");
    delay(1000);
    serlcd.clear();
    serlcd.setPosition(1,0);
    serlcd.print("Espresso 25ml 40ml");
    serlcd.setPosition(2,0);
    serlcd.print("intenso");
    delay(1000);
    serlcd.clear();
    ++capsulasDetectadas;
  }
  /* fortissio_lungo */
  if (abs(red - fortissio_lungo[0]) < thresh && abs(green - fortissio_lungo[1]) < thresh && abs(blue - fortissio_lungo[2]) < thresh ) {
    Serial.println("fortissio_lugo");
    serlcd.setBrightness(28);
    serlcd.clear();
    serlcd.setPosition(1,0);
    serlcd.print("fortissio lugo");
    serlcd.setPosition(2,0);
    serlcd.print("Intensidad 8");
    delay(1000);
    serlcd.clear();
    serlcd.setPosition(1,0);
    serlcd.print("Espresso 110ml");
    serlcd.setPosition(2,0);
    serlcd.print("intenso");
    delay(1000);
    serlcd.clear();
    ++capsulasDetectadas;
  }
  /* envivo_lungo */
  if (abs(red - envivo_lungo[0]) < thresh && abs(green - envivo_lungo[1]) < thresh && abs(blue - envivo_lungo[2]) < thresh ) {
    Serial.println("envivo_lungo");
    serlcd.setBrightness(28);
    serlcd.clear();
    serlcd.setPosition(1,0);
    serlcd.print("envivo lungo");
    serlcd.setPosition(2,0);
    serlcd.print("Intensidad 9");
    delay(1000);
    serlcd.clear();
    serlcd.setPosition(1,0);
    serlcd.print("Espresso 110ml");
    serlcd.setPosition(2,0);
    serlcd.print("intenso");
    delay(1000);
    serlcd.clear();
    ++capsulasDetectadas;
  }
  /* linizio_lungo */
  if (abs(red - linizio_lungo[0]) < thresh && abs(green - linizio_lungo[1]) < thresh && abs(blue - linizio_lungo[2]) < thresh ) {
    Serial.println("linizio_lungo");
    serlcd.setBrightness(28);
    serlcd.clear();
    serlcd.setPosition(1,0);
    serlcd.print("linizio lungo");
    serlcd.setPosition(2,0);
    serlcd.print("Intensidad 4");
    delay(1000);
    serlcd.clear();
    serlcd.setPosition(1,0);
    serlcd.print("Espresso 110ml");
    serlcd.setPosition(2,0);
    serlcd.print("equilibrado");
    delay(1000);
    serlcd.clear();
    ++capsulasDetectadas;
  }
}

void incrementaBrillo(){
  /*   
  for (int brillo = 0; brillo <= 255; brillo += 5){
    analogWrite(pinLed,brillo);
    serlcd.clear();
    serlcd.setPosition(1,0);
    serlcd.print("brillo");
    serlcd.setPosition(2,0);
    serlcd.print(brillo);
    red   = RGB_Sensor.readRed();
    green = RGB_Sensor.readGreen();
    blue  = RGB_Sensor.readBlue();
    Serial.print("R: ");  Serial.print(red,  DEC);
    Serial.print(" G: "); Serial.print(green,DEC);
    Serial.print(" B: "); Serial.print(blue, DEC);
    Serial.println();
    delay(2000);  
  }
*/
}


