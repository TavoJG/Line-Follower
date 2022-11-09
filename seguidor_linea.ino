/*
Programa: Robot Seguidor de Linea - Evita Obstaculos
Código de Dominio Público - Basado en código de Humberto Higinio
Canal de Youtube: https://www.youtube.com/user/HHSolis
*/

#include <NewPing.h>

// Motor A - Derecho
int ENA = 10; // ENA conectado al pin digital 10
int IN1 = 4;  // conectado al pin digital 4
int IN2 = 5;  // conectado al pingdigital 5

// Motor B - Izquierdo
int ENB = 9; // ENB conectado al pin digital 9
int IN3 = 6; // conectado al pin digital 6
int IN4 = 7; // conectado al pin digital 7

// Se definen conexiones de los sensores infrarojos a los puertos Analogicos

int RIGHT = 3; // Sensor Derecho conectado al pin digital 3
int LEFT = 2;  // Sensor Izquierdo conectado al pin digital 2

int CAL_PIN = 13; // Pin de calibracion

// Se definen conexiones del Sensor HC-SR04 con Arduino

#define TRIG A1             // PIN TRIGGER conectado al pin analogico A2
#define ECHO A0             // PIN ECHO conectado al pin analogico A3
#define MAX_DISTANCE 100    // Define la Maxima Distancia
#define TRIGGER_DISTANCE 15 // Distancia para empezar a girar
#define LEFT_MOTOR_SPEED 90 // Velocidad de los motores
#define RIGHT_MOTOR_SPEED 60
#define CORRECT_DIRECTION_OFFSET 30 // Offset para corregir dirección
#define TURN_DELAY 500              // Delay para giros
#define FOWARD_DELAY 500            // Delay para rectas

NewPing sonar(TRIG, ECHO, MAX_DISTANCE);

void setup()
{
    Serial.begin(115200);

    // Se inicializan los pines como Entradas o Salidas
    pinMode(ENA, OUTPUT);
    pinMode(ENB, OUTPUT);
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);
    pinMode(RIGHT, INPUT);
    pinMode(LEFT, INPUT);
    pinMode(CAL_PIN, INPUT);

    if (digitalRead(LEFT) == LOW)
    {
        analogWrite(ENA, RIGHT_MOTOR_SPEED);
        analogWrite(ENB, LEFT_MOTOR_SPEED);
    }
    else
    {
        analogWrite(ENA, 0);
        analogWrite(ENB, 0);
    }
}

void loop()
{

    delay(100);
    int distance = sonar.ping_cm();
    if (distance == 0)
    {
        distance = 30;
    }
    if (distance <= TRIGGER_DISTANCE)
    { // Se define la distancia para detectar un obstaculo y las acciones a tomar
        Stop();
        delay(100);
        turnRight();
        delay(TURN_DELAY);
        moveForward();
        delay(FOWARD_DELAY);
        turnLeft();
        delay(TURN_DELAY);
        moveForward();
        delay(FOWARD_DELAY);
        turnLeft();
        delay(TURN_DELAY);
        moveForward();
        delay(FOWARD_DELAY);
        turnRight();
        delay(TURN_DELAY);
    }

    int left_ir = 0;
    left_ir = digitalRead(LEFT);
    int right_ir = 0;
    right_ir = digitalRead(RIGHT);

    if ((right_ir == HIGH && left_ir == HIGH))
    {
        moveForward();
    }
    else if (right_ir == HIGH && left_ir == LOW)
    { // a la derecha de la linea girar a la Izquierda
        turnLeft();
    }
    else if (right_ir == LOW && left_ir == HIGH)
    { // a la izquierda de la linea girar a la Derecha
        turnRight();
    }
    else
    {
        Stop();
    }
}
void Stop()
{ // Detiene los motores
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
}

void turnRight()
{ // Gira a la derecha
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
}

void turnLeft()
{ // Gira a la izquierda
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
}

void moveForward()
{ // Avanza de frente
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
}
