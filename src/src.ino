#include <ECE3.h>
#include "Corrections.hpp"

#define DEBUG 0
#define NUM_SENSORS 8

// Global Variables
int sensor_mins[NUM_SENSORS] = {826, 686, 640, 709, 686, 663, 756, 663};
int sensor_max[NUM_SENSORS] = {1674, 1814, 1860, 1791, 1814, 1837, 1744, 1300};
int fusion_weights[NUM_SENSORS] = {-15, -14, -12, -8, 8, 12, 14, 15};
uint16_t sensor_values[NUM_SENSORS];
float normalized_sensor_values[NUM_SENSORS];
float error = 0; 
float prev_error = 0;
float derivative = 0;
int turn_state = 0;
bool onCrossPiece = false;
bool turnedAround = false;
int crossPieceCounter = 0; 
int left_speed = BASE_SPEED;
int right_speed = BASE_SPEED;
float kp = 0.03f;
float kd = 0.05f;

void setup() {
  // put your setup code here, to run once:
    ECE3_Init();
    Serial.begin(9600);

    pinMode(41, OUTPUT);
    pinMode(57, OUTPUT);
    digitalWrite(left_nslp_pin, HIGH);
    digitalWrite(right_nslp_pin, HIGH);
    digitalWrite(left_dir_pin, LOW);
    digitalWrite(right_dir_pin, LOW);
    delay(2000);
}

void getNormalizedSensorValues(){
    ECE3_read_IR(sensor_values);

     for (int i = 0; i < NUM_SENSORS; i++){
         if (sensor_mins[i] > sensor_values[i]) normalized_sensor_values[i] = 0;
         else normalized_sensor_values[i] = sensor_values[i] - sensor_mins[i];
     }
     for (int i = 0; i < NUM_SENSORS; i++) normalized_sensor_values[i] = (normalized_sensor_values[i] / sensor_max[i]) * 1000;
}

void fuseSensors(){
    error = 0;
    for(int i = 0; i < NUM_SENSORS; i++){
        error += normalized_sensor_values[i] * fusion_weights[i];
    }
    error /= 8;
}

void log_normalized_fused_sensors(){
        for(int i = 0; i < NUM_SENSORS; i++){
            Serial.print((int)normalized_sensor_values[i]);
            Serial.print(" ");
        }
            Serial.print(error);
            Serial.print("\n");
}



void loop() {
    // put your main code here, to run repeatedly:
    getNormalizedSensorValues();
    fuseSensors();

    derivative = math::Derivative();

    int n = SensorsOverThreshold(700, normalized_sensor_values);
    if (n >= 6 && !onCrossPiece)crossPieceCounter++;
    else if (n < 6 && onCrossPiece)onCrossPiece = false;
    if (crossPieceCounter == 2){
        onCrossPiece = true;
        turn_state++;
        crossPieceCounter = 0;
        digitalWrite(41, HIGH);
        moveAcrossCrossPiece(100);
    }else digitalWrite(41, LOW);
    if (turn_state == 3 && !turnedAround){
        digitalWrite(57, HIGH);
        turn_around();
        turnedAround = true;
    }else if (turn_state == 6){
        digitalWrite(left_nslp_pin, LOW);
        digitalWrite(right_nslp_pin, LOW);
    }

    float correction = kp * error + kd * derivative;
    make_correction((int)correction);

    if (DEBUG) log_normalized_fused_sensors();

    prev_error = error;
}
