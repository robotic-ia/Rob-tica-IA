/* 
 ARDUINO   L293D (Puente H)        
 7          10
 8          15
 9          7
 11         2
 5V         1, 9, 16
 GND        4, 5, 12, 13
 
 El motor 1 se conecta a los pines 2 y 7 del Puente H
 El motor 2 se conecta a los pines 10 y 15 del Puente H
 
 La fuente de alimentación de los Motores se conecta a tierra y
 el positivo al pin 8 del puente H. 
 
 Conexión Sensor Ultrasonido HC-SR04
 ARDUINO    Ultrasonido HC-SR04 
 A4           Echo
 A5           Trig
 5V           VCC
 GND          Gnd

 Conexión Servo SG90 opcional
 ARDUINO    Ultrasonido HC-SR04 
 3            Signal
 5V           VCC
 GND          Gnd
 */

 # include <Servo.h>                        // Incluye clase Servo
 Servo servo1;                              // Define a servo1 como objeto tipo Servo

int izqA = 7; 
int izqB = 8; 
int derA = 9; 
int derB = 11; 
int vel = 255;                              // Velocidad de los motores (0-255)

int pecho = A4;                             // define el pin 2 como (pecho) para el Ultrasonido
int ptrig = A5;                             // define el pin 3 como (ptrig) para el Ultrasonido
int duracion, distancia;                    // para Calcular distacia

void setup()  
  { 
    Serial.begin(9600);                     // inicia el puerto serial para comunicacion con el Bluetooth
    pinMode(derA, OUTPUT);
    pinMode(derB, OUTPUT);
    pinMode(izqA, OUTPUT);
    pinMode(izqB, OUTPUT);
  
    pinMode(pecho, INPUT);                  // define el pin 2 como entrada (pecho) 
    pinMode(ptrig,OUTPUT);                  // define el pin 3 como salida  (ptrig) 
    pinMode(13,OUTPUT);
    
    servo1.attach(3,660,1400);
  } 

void loop()  
  { 
    delay (3000);

    digitalWrite(ptrig, HIGH);              // genera el pulso de trigger por 10us
    delay(0.01);
    digitalWrite(ptrig, LOW);
     
    duracion = pulseIn(pecho, HIGH);        // Lee el tiempo del Echo
    distancia = (duracion/2) / 29;          // calcula la distancia en centimetros
    delay(10); 
     
    if (distancia <= 15 && distancia >=2)
      { 
        // si la distancia es menor de 15cm
        digitalWrite(13,HIGH);              // Enciende LED
        
        analogWrite(derB, 0);               // Parar los motores por 200 mili segundos
        analogWrite(izqB, 0); 
        analogWrite(derA, 0);    
        analogWrite(izqA, 0); 
        delay (200);
        
        analogWrite(derB, vel);             // Reversa durante 500 mili segundos
        analogWrite(izqB, vel); 
        delay(500);           
        
        analogWrite(derB, 0);               // Girar durante 600 milisegundos   
        analogWrite(izqB, 0); 
        analogWrite(derA, 0);  
        analogWrite(izqA, vel);  
        delay(600);
        
        digitalWrite(13,LOW);
      }
    else
      { 
        // Si no hay obstaculos se desplaza al frente  
        analogWrite(derB, 0);     
        analogWrite(izqB, 0); 
        analogWrite(derA, vel);  
        analogWrite(izqA, vel); 
      }
    servo1.write(30);                       // Girar servo a 30 grados
    delay(1000);                            // Espera hasta que el servo llegue a la posición

    servo1.write(90);                       // Girar servo a 90 grados
    delay(700);                             // Espera hasta que el servo llegue a la posición

    servo1.write(150);                      // Girar servo a 150 grados
    delay(700);                             // Espera hasta que el servo llegue a la posición
  }
