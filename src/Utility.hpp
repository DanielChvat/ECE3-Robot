#pragma once

#define LEFT 0
#define RIGHT 1
#define left_nslp_pin 31
#define BASE_SPEED 40
#define left_dir_pin 29
#define left_pwm_pin 40
#define right_nslp_pin 11
#define right_dir_pin  30
#define right_pwm_pin 39
#define max_speed 255
#define min_speed -255

extern float prev_error;
extern float error;
namespace math{
    void clamp(int &value, int upper_bound, int lower_bound){
        if (value > upper_bound)value = upper_bound - 1;
        else if (value < lower_bound)value = lower_bound;
    } 

    float Derivative(void){
       return (error - prev_error);
    }
}

int SensorsOverThreshold(int threshold, float sensors[]){
    int n = 0;
    for(int i=0; i < 8; i++){
        if (sensors[i] >= threshold) n++;
    }
    return n;
}

void moveAcrossCrossPiece(int time){
    digitalWrite(left_dir_pin, LOW);
    digitalWrite(right_dir_pin, LOW);
    analogWrite(left_pwm_pin, BASE_SPEED);
    analogWrite(right_pwm_pin, BASE_SPEED);
    delay(time);
}