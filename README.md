# Nespresso Arduino Pro Mini
Este proyecto es una copia del publicado en https://www.instructables.com/id/DIY-Nespresso-Capsule-Detector/ <p>
Hecho para pasar el tiempo y porque cuando tienes las capsulas sueltas al final no sabes la intensidad del café. Sinceramente la razón principal es la primera. :D Enjoy! <p>
Nota: Sacrilegio usar leche con el café.

# Material usado 
* Arduino Pro Mini 328 - 5V/16MHz
* Serial Enabled 16x2 LCD - White on Black 5V
* SparkFun RGB Light Sensor - ISL29125
* Logic Level Converter Bi-Directional SparkFun
* SparkFun FTDI Basic Breakout - 5V
* DC Barrel Jack Adapter
* LD1117 voltage regulator 3.3v
* Capacitor Ceramic 0.1uF
* Electrolytic Decoupling Capacitor - 10uF/25V
* cablecitos y demás...


# Modificación circuito
Se realiza modificación del circuito con respecto al que planteaban los de Instructables, puesto que se producía un corto.
Se sube la foto del circuito, cicuito.jpg.
<p>
<img src="circuito.jpg" />


# Conexiones
## LCD 2x16
    GDN LCD --> GND Arduino<p>
    Vcc LCD --> Vcc Arduino <p>
    RX  LCD --> Pin 2 Arduino <p>

### Sensor RGB ISL29125 
    GND (azul) SensorRGB      --> GND Arduino<p>
    Vcc (rojo) SensorRGB 3.3v --> LV de LogicLevelConverter LV<p>
    SDA (verde) SensorRGB     --> LV2 de LogicLevelConverter<p>
    SDL (amarillo) SensorRGB  --> LV1 de LogicLevelConverter<p>
Nota: Los colores indicados en esta parte no coinciden con la imagen.
## LCD y SensorRGB en caja impresa en 3D
Es muy importante que el color de la impresión sea negra para que no deje pasar la luz. Usar filamento translúcido.
<img src="IMG_0287.jpg" />
<img src="IMG_0288.jpg" />
