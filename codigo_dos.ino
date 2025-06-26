/* ----------------------------
Puente H L293D
Arduino   L293D
-------   -----
7         10
8         15
9         7
11        2
Motor1
+         3
-         6
Motor2
+         11
-         14
GND       4-5-12-13
Vcc       1-8-9-16
-------------------------------
Sensor Ultrasónico HC-SR04
Arduino     HC-SR04
-------     -------
Vcc         Vcc
A5          TRIG
A4          ECHO
GND         GND
-------------------------------
Servo motor
Arduino     Servo
-------     -----
3           Señal
Vcc         Vcc
GND         GND
------------------------------*/

#include <Servo.h>  // librería de control del servo
Servo myservo;      // crea un objeto tipo servo

int Echo = A4;  
int Trigger = A5; 
#define EN_A 5
#define EN_B 6
#define IN_1 7
#define IN_2 8
#define IN_3 9
#define IN_4 11
//---------------------------------------------------
// Configuración de la Red Neuronal y otras variables
//---------------------------------------------------
int i, j;                           // Índices generales
const int NeuronasEntrada = 3;      
const int NeuronasOcultas = 4;      
const int NeuronasSalida = 4;    
double Acumulador;               
double Hidden[NeuronasOcultas];  
double Output[NeuronasSalida];   
float PesosCapasOcultas[3][4] = {{-0.9608686636205825, 1.8370320805355191, -0.327032849199386, 0.9090423712571561}, {5.063068026758557, -0.002833394097320586, 1.0690058904547441, -4.895785865954065}, {1.7485102310007927, -0.11695137101612507, -0.06802754529913706, 1.6281772126411767}};
float PesosCapaSalida[4][4] = {{0.3835132845103735, 0.39273673709362084, 2.1189162089220335, -1.8451031231006507}, {1.7619732426322716, 1.600968363838172, 1.60029389166239, 1.75731052960782}, {0.06198805454565617, -1.2944100686479805, -1.165113745476507, -1.0661947972903463}, {2.1021751119421412, -2.2732348606412502, -0.43270873696748174, -0.8445690774481365}};
unsigned long Milisegundos = 0;  
const long Intervalos = 25;      
int posicion_servo = 90;         
bool direccion_giro = true;      
const long giro_min = 30;        
const long giro_max = 150;       
double Distancia_Max = 50.0;     
int Incremento = 9;              
int Ejecuta_Accion = 1;          
int multiplicador = 1000/Intervalos; 
const int Velocidad = 100;           
// -----------------------------------
// Función para desactivar los motores
// -----------------------------------
void stop() 
  {
    digitalWrite(EN_A, LOW);        // Desactiva el motor A
    digitalWrite(EN_B, LOW);        // Desactiva el motor B
    Serial.println("Stop!");
  } 
// -------------------------------------------------
// Función para calcular la distancia en Centímetros
// -------------------------------------------------
int Test_distancia() 
  {
    digitalWrite(Trigger, LOW);
    delayMicroseconds(2);
    digitalWrite(Trigger, HIGH);
    delayMicroseconds(20);
    digitalWrite(Trigger, LOW);
    float FDistancia = pulseIn(Echo, HIGH);
    FDistancia= FDistancia / 58;
    return (int)FDistancia;
  }
//-------------------------
// Función de configuración
//-------------------------
void setup() 
  {
    myservo.attach(3);  // Conexión del servo en el pin 3 del Arduino
    Serial.begin(9600);
    pinMode(Echo, INPUT);
    pinMode(Trigger, OUTPUT);
    pinMode(IN_1, OUTPUT);
    pinMode(IN_2, OUTPUT);
    pinMode(IN_3, OUTPUT);
    pinMode(IN_4, OUTPUT);
    pinMode(EN_A, OUTPUT);
    pinMode(EN_B, OUTPUT);
    stop();
    myservo.write(90);  // Posición inicial del servo en el centro
    delay(500); 
  } 
//------------------
// Función Principal
//------------------
void loop() 
  {
   unsigned long currentMillis = millis();
    if (currentMillis - Milisegundos >= Intervalos) 
      {
       Milisegundos = currentMillis;
       if (posicion_servo<=giro_min || posicion_servo>=giro_max)
         {
          direccion_giro=!direccion_giro; // cambio de sentido
          posicion_servo = constrain(posicion_servo, giro_min, giro_max);
         }
       if(direccion_giro)
          posicion_servo=posicion_servo+Incremento;
       else
          posicion_servo=posicion_servo-Incremento;
       if(Ejecuta_Accion>0)
         {
          Ejecuta_Accion=Ejecuta_Accion-1;
         }
       else
         {
          Navegar();      
         }
      myservo.write(posicion_servo);    
      }
  }
// -----------------------------------
// Uso de la Red Neuronal ya Entrenada
// -----------------------------------
void Navegar()
  {
    double Test_entrada[] = {0, 0, 0};
    double entrada1=0,entrada2=0;
    //---------------------------------------------
    // Obteneos la distancia del sensor ultrasonico
    //---------------------------------------------
    double Distancia = double(Test_distancia());
    Distancia= double(constrain(Distancia, 0.0, Distancia_Max));
    entrada1= ((-2.0/Distancia_Max)*double(Distancia))+1.0;   // Aplicamos una función lineal para calcular la distancia al obstáculo
    Ejecuta_Accion = ((entrada1 +1) * multiplicador)+1;       // Si está muy cerca incrementamos la espera
    //-----------------------------------------------------------
    // Determina dirección dependiendo del ángulo del servo motor
    //-----------------------------------------------------------
    entrada2 = map(posicion_servo, giro_min, giro_max, -100, 100);
    entrada2 = double(constrain(entrada2, -100.00, 100.00));
    //-------------------------------------------------------
    // Se lama a la red neuronal FeedForward con las entradas
    //-------------------------------------------------------
    Serial.print("Entrada1:");
    Serial.println(entrada1);
    Serial.print("Entrada2:");
    Serial.println(entrada2/100.0);
    Test_entrada[0] = 1.0;
    Test_entrada[1] = entrada1;
    Test_entrada[2] = entrada2/100.0;
    InputToOutput(Test_entrada[0], Test_entrada[1], Test_entrada[2]);
    int Salida1 = round(abs(Output[0]));
    int Salida2 = round(abs(Output[1]));
    int Salida3 = round(abs(Output[2]));
    int Salida4 = round(abs(Output[3]));
    Serial.print("Salida 1:");
    Serial.println(Salida1);
    Serial.print("Salida 2:");
    Serial.println(Salida2);
    Serial.println(Output[1]);
    Serial.print("Salida 3:");
    Serial.println(Salida3);
    Serial.print("Salida 4:");
    Serial.println(Salida4);
    //-----------------------------------------------
    // Mueve motores con la salida de la red neuronal
    //-----------------------------------------------
    int VelAuto = Velocidad;
    if((Salida1+Salida3)==2 || (Salida2+Salida4)==2)
      { 
       VelAuto = Velocidad * 2;
      }
    analogWrite(EN_A, VelAuto);
    analogWrite(EN_B, VelAuto);
    digitalWrite(IN_1, Salida1 * HIGH); 
    digitalWrite(IN_2, Salida2 * HIGH); 
    digitalWrite(IN_3, Salida3 * HIGH);
    digitalWrite(IN_4, Salida4 * HIGH);
  }
//----------------------------
// Función de entrada y salida
//----------------------------
void InputToOutput(double In1, double In2, double In3)
  {
    double Test_entrada[] = {0, 0,0};
    Test_entrada[0] = In1;
    Test_entrada[1] = In2;
    Test_entrada[2] = In3;
    //--------------------------------------------------------
    // Calculo de los pesos de activación de las capas ocultas
    //--------------------------------------------------------
    for ( i = 0 ; i < NeuronasOcultas ; i++ ) 
      {
       Acumulador = 0;
       for ( j = 0 ; j < NeuronasEntrada ; j++ ) 
         {
          Acumulador += Test_entrada[j] * PesosCapasOcultas[j][i];
         }
       Hidden[i] = tanh(Acumulador); // Función tangente
      }
    //-----------------------------------------------------------------
    // Calculo de los pesos de activación y error para la capa de Salida
    //-----------------------------------------------------------------
    for ( i = 0 ; i < NeuronasSalida ; i++ ) 
      {
       Acumulador = 0;
       for ( j = 0 ; j < NeuronasOcultas ; j++ )
         {
          Acumulador += Hidden[j] * PesosCapaSalida[j][i];
         }
       Output[i] = tanh(Acumulador);   // Función tangente
      }
  }
