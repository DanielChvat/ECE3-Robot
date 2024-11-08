#include <ECE3.h>

#define DEBUG 1
#define NUM_SENSORS 8

int sensor_mins[NUM_SENSORS] = {826, 686, 640, 709, 686, 663, 756, 663};
int sensor_max[NUM_SENSORS] = {1674, 1814, 1860, 1791, 1814, 1837, 1744, 1300};
int fusion_weights[NUM_SENSORS] = {-15, -14, -12, -6, 8, 12, 14, 15};
uint16_t sensor_values[NUM_SENSORS];
float normalized_sensor_values[NUM_SENSORS];
float fused_sensor_value = 0; 

void setup() {
  // put your setup code here, to run once:
    ECE3_Init();
    if (DEBUG){
        Serial.begin(9600);
    }
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
    fused_sensor_value = 0;
    for(int i = 0; i < NUM_SENSORS; i++){
        fused_sensor_value += normalized_sensor_values[i] * fusion_weights[i];
    }
}

void loop() {
    // put your main code here, to run repeatedly:
    getNormalizedSensorValues();
    fuseSensors();

    if (DEBUG){
        for(int i = 0; i < NUM_SENSORS; i++){
            Serial.print((int)normalized_sensor_values[i]);
            Serial.print(" ");
        }
            Serial.print(fused_sensor_value);
            Serial.print("\n");
    }
      
}
