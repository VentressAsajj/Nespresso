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
   * 
   * Lo valores usados para el sensor RGB son:
   * CFG1_MODE_RGB | CFG1_375LUX, CFG2_IR_ADJUST_LOW, CFG3_NO_INT
   * CONFIG1: colores que recoge el sensor. 
   * CFG1_MODE_RGB: Activamos los tres colores RGB
   * CFG1_16BIT: más precisión
   * CFG1_375LUX: Rango de intensidad de la luz, usar este para entornos oscuros.
   *              CFG1_10KLUX para los claros
   * CFG2_IR_ADJUST_LOW: filtrado IR, calibrar.
   * CFG3_NO_INT: No interrupciones.
   */

 /*
  * Probrema a la hora de detectar colores similares. Por diseño de la "caja" donde
  * van los sensores y el arduino, no hay espacio para meter otro led. Se puede hacer
  * otro agujero o retocar el diseño3D, (pereza, va a ser que no!)
  * Soluciones aportadas por la comunidad:
  * 
  *   @javierfpanadero: Sumar los colores y ver la diferencia que hay entre ellos.
  *   @Nicky69es: Hacer dos lecturas, una con el led encendido y otra con el led
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
const long interval = 2000;
//const long interval = 4000;
//const long interval = 6000;
bool detect = 0;
int thresh;
int threshGreen;
int threshBlue;  

int red;
int green;
int blue;

 
/*
 * Cambio de led, ponemos uno con más chica y tenemos
 * un espectro más grande.
 * Toma de datos iniciales sin capsulas
 * R: 2700-2900 G: 4888-5043 B: 3580-3652
 */
int kazaar[3]          = {2400,4800,3800};  //
int arpeggio[3]        = {2600,4700,4000};  //
int capriccio[3]       = {2700,5300,3950};  //
int roma[3]            = {3000,5200,3800};  //
int ristretto[3]       = {2350,4500,3500};  //
int indriya[3]         = {3800,6800,4500};  //
int livanto[3]         = {5300,7300,4100};  //
int dharkan[3]         = {2800,5600,4450};  //
int rosabaya[3]        = {7200,10800,7000}; //
int volutto[3]         = {8100,11600,5500}; //
int dulsao[3]          = {10800,16100,8600};//
int cosi[3]            = {6400,9600,6200};  //
int linizio_lungo[3]   = {9900,11200,5300}; //
int bukeela_lungo[3]   = {9850,12300,6900}; //
int fortissio_lungo[3] = {3300,6800,5000};  //
int vivalto_lungo[3]   = {4300,8400,8100};  //
int envivo_lungo[3]    = {5700,6800,4200};  //


/* Configure */
void setup() {

  /* Inicializacion del monitor serie para control de errores y demas */
  Serial.begin(115200);
  Serial.println("Iniciando programa");
  // led 9/A0 es el blanco
  //pinMode(pinLed,OUTPUT); // si es analogico esto sobra
  
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
    RGB_Sensor.config(CFG1_MODE_RGB | CFG1_16BIT | CFG1_375LUX, CFG2_IR_ADJUST_HIGH, CFG3_NO_INT);
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
   
  if (blue <= 1) {
    ledState = HIGH;
    analogWrite(pinLed,255);
    detect = 1;
  }
  
  if (currentMillis - previousMillis >= interval && ledState == HIGH) {
    // guardamos la ultima vez que parpadeo el led
    previousMillis = currentMillis;
    analogWrite(pinLed,0);
    detect = 0;
    serlcd.clear();
    serlcd.setPosition(1,0);
    int valor = analogRead(pinLed);
    Serial.print("Valor led ");
    Serial.println(valor); // max 327? menor 4-17
    if( valor < 50 ){
      serlcd.print("No hay capsulas");
    }
    serlcd.setBrightness(0);
  }
  /* leemos valores del sensor, 16bits integers*/
  red   = RGB_Sensor.readRed();
  green = RGB_Sensor.readGreen();
  blue  = RGB_Sensor.readBlue();
  
/*
 * rango de medicion en el caso de tener problemas   
 * con capsulas de colores similares
 * 
  if( blue > 1000 ){
    thresh = 25;
    threshGreen = 25;
    threshBlue = 200;
  }else if(green > 1000){
    thresh = 25;
    threshGreen = 200;
    threshBlue = 25;
  }else{
    thresh = 20;
    threshGreen = 20;
    threshBlue = 20;
  }
*/
  thresh = 200;
  if (detect) {
    detectarCapsulas();
    delay(100);
  }
}

void detectarCapsulas(){

  
  /* comentar cuando ya se tenga los valores RGB para cada cafe*/
  /* Serial.println(red, DEC|HEX) */
  
  Serial.print(" R: "); Serial.print(red,  DEC);
  Serial.print(" G: "); Serial.print(green,DEC);
  Serial.print(" B: "); Serial.print(blue, DEC);
  Serial.println();
  //Serial.print(" R: "); Serial.print(red,  HEX);
  //Serial.print(" G: "); Serial.print(green,HEX);
  //Serial.print(" B: "); Serial.print(blue, HEX);
  //Serial.println();
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
    serlcd.print("Espresso 25-40ml");
    serlcd.setPosition(2,0);
    serlcd.print("intenso");
    delay(1000);
    serlcd.clear();
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
    serlcd.print("Espresso 25-40ml");
    serlcd.setPosition(2,0);
    serlcd.print("intenso");
    delay(1000);
    serlcd.clear();
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
    serlcd.print("Espresso 25-40ml");
    serlcd.setPosition(2,0);
    serlcd.print("intenso, cremoso");
    delay(1000);
    serlcd.clear();
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
    serlcd.print("Espresso 25-40ml");
    serlcd.setPosition(2,0);
    serlcd.print("intenso");
    delay(1000);
    serlcd.clear();
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
    serlcd.print("Espresso 25-40ml");
    serlcd.setPosition(2,0);
    serlcd.print("intenso");
    delay(1000);
    serlcd.clear();
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
    serlcd.print("Espresso 25-40ml");
    serlcd.setPosition(2,0);
    serlcd.print("intenso");
    delay(1000);
    serlcd.clear();
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
  }
}
/* 
void incrementaBrillo(){
  
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

}
*/



