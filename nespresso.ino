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
  /* declare pins  RGB */
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
  if (RGB_Sensor.init()){
    Serial.println("Inicializacion correcta del sensor RBG");
    //RGB_sensor.config(CFG1_10KLUX, CFG2_IR_ADJUST_HIGH, CFG3_INT_PRST4);
  }  
  else {
    Serial.println("Error iniciando sensor RBG");
    serlcd.clear();
    serlcd.setPosition(1,0);
    serlcd.print("Error sensor RBG"); 
    delay(4000);
  }
}

/* principal */
void loop() {

  
  unsigned long currentMillis = millis(); 

  /* leemos valores del sensor, 16bits integers*/
  unsigned int red   = RGB_Sensor.readRed();
  unsigned int green = RGB_Sensor.readGreen();
  unsigned int blue  = RGB_Sensor.readBlue();
  
  Serial.print("Rojo:  "  ); Serial.print(red,    DEC);
  Serial.print("  Verde: "); Serial.print(green,  DEC);
  Serial.print("  Azul:  "); Serial.println(blue, DEC);
  Serial.println();
  delay(2500);

  if (blue <= 1) {
    //ledState = HIGH;
    ledState = LOW;
    digitalWrite(8, HIGH);
    digitalWrite(9, HIGH);
    detect = 1;
  }
  
  Serial.print("Milisegundos: "); Serial.println(currentMillis);
  Serial.print("currentMillis - previousMillis "); Serial.println(currentMillis - previousMillis);
  Serial.print("Interval ");Serial.print(interval);
  Serial.print("  ledState ");Serial.println(ledState);
  delay(4000);
  
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

  int kazaar[3] = {65, 34, 67};
  int dulsao[3] = {103, 45, 96};
  int bukeela_lungo[3] = {101, 44, 94};
  int linizio_lungo[3] = {72, 33, 64};

  /* intentamos ajustar mas */
  /*int thresh = 20 ;*/
  int thresh = 2;
  
  /* comentar cuando ya se tenga los valores RGB para cada cafe*/
  /* Serial.println(red, DEC|HEX) */
  /*
  Serial.print("Rojo:  "); Serial.print(RGB_Sensor.readRed(),  DEC);
  Serial.print("  Verde: "); Serial.print(RGB_Sensor.readGreen(),DEC);
  Serial.print("  Azul:  "); Serial.println(RGB_Sensor.readBlue(), DEC);
  Serial.println();
  delay(2500);
  */
  /*
  Serial.print("Rojo:" );Serial.println(RGB_Sensor.readRed());
  Serial.print("Verde:");Serial.println(RGB_Sensor.readGreen());
  Serial.print("Azul:" );Serial.println(RGB_Sensor.readBlue());
  Serial.println();
  delay(3000);
  */
  Serial.print("Detectado: ");Serial.println(detect);
  
  if (detect) {
    /* Kazaar */
    if (abs(red - kazaar[0]) < thresh && abs(green - kazaar[1]) < thresh && abs(blue - kazaar[2]) < thresh ) {
      Serial.print("Kazaar");
      serlcd.setBrightness(28);
      serlcd.clear();
      serlcd.setPosition(1,0);
      serlcd.print("Kazaar");
      serlcd.setPosition(2,0);
      serlcd.print("Intensidad: 10");
      delay(3000);
      serlcd.clear();
      serlcd.setPosition(1,0);
      serlcd.print("hoy va a ser");
      serlcd.setPosition(2,0);
      serlcd.print("un dia duro");
      delay(3000);
      serlcd.clear();
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
      delay(3000);
      serlcd.clear();
      serlcd.setPosition(1,0);
      serlcd.print("para tomar eso");
      serlcd.setPosition(2,0);
      serlcd.print("mejor agua");
      delay(3000);
      serlcd.clear();
    }
    /* Bukeela Lungo */
    if (abs(red - bukeela_lungo[0]) < thresh && abs(green - bukeela_lungo[1]) < thresh && abs(blue - bukeela_lungo[2]) < thresh ) {
      Serial.print("Bukeela Lungo");
      serlcd.setBrightness(28);
      serlcd.clear();
      serlcd.setPosition(1,0);
      serlcd.print("Bukeela Lungo");
      serlcd.setPosition(2,0);
      serlcd.print("Intensidad 3");
      delay(3000);
      serlcd.clear();
      serlcd.setPosition(1,0);
      serlcd.print("esto no es cafe");
      serlcd.setPosition(2,0);
      serlcd.print("vete a dormir");
      delay(3000);
      serlcd.clear();
    }
    /* Linizio Lungo */
    if (abs(red - linizio_lungo[0]) < thresh && abs(green - linizio_lungo[1]) < thresh && abs(blue - linizio_lungo[2]) < thresh ) {
      Serial.print("Linizio Lungo");
      serlcd.setBrightness(28);
      serlcd.clear();
      serlcd.setPosition(1,0);
      serlcd.print("Linizio Lungo");
      serlcd.setPosition(2,0);
      serlcd.print("Intensidad 4");
      delay(3000);
      serlcd.clear();
      serlcd.setPosition(1,0);
      serlcd.print("Tipo cafe:");
      serlcd.setPosition(2,0);
      serlcd.print("Arabica");
      delay(3000);
      serlcd.clear();
    }



  }
}

