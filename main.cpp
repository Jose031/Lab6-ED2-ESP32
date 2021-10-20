//********************************************************************************
// Universidad del Valle de Guatemala
// BE3015: Electrnónica Digital 2
// José David Méndez 19380
// Laboratorio 6
//********************************************************************************

//**********************************************************************************************************************
// Librerías
//**********************************************************************************************************************
#include <Arduino.h>
#include <LiquidCrystal.h> // Librería que contiene la cofiguración completa de la pantalla LCD
//**********************************************************************************************************************
// Defincion de Pines
//**********************************************************************************************************************
#define d4 18
#define d5 5
#define d6 4
#define d7 2
#define en 19
#define rs 21
#define pot1 34

//**********************************************************************************************************************
// Prototipo de Funciones
//**********************************************************************************************************************
void voltaje1(void); // Función para la impresión del voltaje del potenciometro 1
void voltaje2(void); // Función para la impresión del voltaje del potenciometro 2
void UPC(void);      // Función para la impresión del contador en la LCD
//**********************************************************************************************************************
// Variables Globales
//**********************************************************************************************************************
LiquidCrystal LCD(rs, en, d4, d5, d6, d7); // Variables definidas en la librería
uint8_t decenas, unidades, decimal;
uint8_t decenas1, unidades1, decimal1;
uint8_t centenas, decenas2, unidades2;
String contador = "";
int voltaje = 0;
String voltajeB = "";
//**********************************************************************************************************************
// Configuracion
//**********************************************************************************************************************
void setup()
{
  // Velocidad a la que trabaja la comunicación serial
  Serial.begin(115200);
  Serial2.begin(115200);
  // Se establece que la LCD utilizada es de 16x2
  LCD.begin(16, 2);
}
//**********************************************************************************************************************
// LOOP
//**********************************************************************************************************************
void loop()
{
  analogReadResolution(8);//Funcion que hace que los valores de ADC entren como un byte
  // Llamado de funciones
  voltaje1();

  if (Serial2.available() > 0) // Condición que permite verficar si hay bytes disponibles en el buffer de registro
  {
    voltajeB = Serial2.readStringUntil('\n'); //Leer el valor enviado por la tiva c cuando detecta un enter 
    contador = Serial2.readStringUntil('\n');
   
  }
  voltaje2();
  UPC();
  delay(250);
}
//**********************************************************************************************************************
// Fuinciones
//**********************************************************************************************************************
void voltaje1(void) // Voltaje potenciometro 1
{
  // Conversión de señal ADC a miliVoltios

  voltaje = analogRead(pot1);

  // Operación para obtener unidades y decimales del voltaje del Potenciometro 1
  int vol = voltaje;
  decenas = vol / 100.0;
  vol = vol - decenas * 100.0;
  unidades = vol / 10.0;
  vol = vol - unidades * 10.0;
  decimal = vol;

  // Impresión del voltaje del potenciometro 1 en la LCD con su respectiva posición
  LCD.clear();
  LCD.print("Rojo:");
  LCD.setCursor(1, 0);
  LCD.print(decenas);
  LCD.print(unidades);
  LCD.print(decimal);
  Serial2.println(analogRead(pot1));
}

void voltaje2(void) // Voltaje potenciometro 2
{
  // Conversión de señal ADC a miliVoltios

     // Operación para obtener unidades y decimales del voltaje del Potenciometro 2
    int vol1 = voltajeB.toInt();
    decenas1 = vol1 / 100.0;
    vol1 = vol1 - decenas1 * 100.0;
    unidades1 = vol1 / 10.0;
    vol1 = vol1 - unidades1 * 10.0;
    decimal1 = vol1;
  
    // Impresión del voltaje del potenciometro 2 en la LCD con su respectiva posición
    LCD.setCursor(0, 6);
    LCD.print("Ver:");
    LCD.setCursor(1, 6);
    LCD.print(decenas1);
    LCD.print(unidades1);
    LCD.print(decimal1);
    Serial.println(voltajeB); //forma de enviar la sel valor ADC a la tiva, esto mediante texto
    
}
void UPC(void) // Valor contador
{
      // Operación para obtener centenas, decenas y unidades del valor del contador
    int cont = contador.toInt();
    centenas = cont / 100.0;
    cont = cont - centenas * 100.0;
    decenas2 = cont / 10.0;
    cont = cont - decenas2 * 10.0;
    unidades2 = cont;

   // Impresión del valor del contador en la pantalla LCD
    LCD.setCursor(0, 11);
    LCD.print("Azul:");
    LCD.setCursor(1, 11);
    LCD.print(centenas);
    LCD.print(decenas2);
    LCD.print(unidades2);
    Serial.println(contador);
  
}
