#pragma once
#include "Utility.hpp"

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

extern int left_speed;
extern int right_speed;

void make_correction(int correction){
    left_speed = BASE_SPEED - correction;
    right_speed = BASE_SPEED + correction;

    math::clamp(left_speed, max_speed, min_speed);
    math::clamp(right_speed, max_speed, min_speed);

    if (left_speed < 0){
        digitalWrite(left_dir_pin, HIGH);
        left_speed = -left_speed;
    }else digitalWrite(left_dir_pin, LOW);
    if (right_speed < 0){
        digitalWrite(right_dir_pin, HIGH);
        right_speed = -right_speed;
    }else digitalWrite(right_dir_pin, LOW);

    analogWrite(left_pwm_pin, left_speed);
    analogWrite(right_pwm_pin, right_speed);
}

void turn_around(){
    digitalWrite(left_dir_pin, HIGH);
    digitalWrite(right_dir_pin, LOW);
    analogWrite(left_pwm_pin, 255);
    analogWrite(right_pwm_pin, 255);
    delay(250);
    moveAcrossCrossPiece(100);
}


