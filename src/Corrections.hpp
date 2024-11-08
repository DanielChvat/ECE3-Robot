#pragma once

#define LEFT 0
#define RIGHT 1
#define BASE_SPEED 20
#define MAX_CORRECTION 2120
#define MIN_CORRECTION -2041
#define left_nslp_pin 31
#define left_dir_pin 29
#define left_pwm_pin 40
#define right_nslp_pin 11
#define right_dir_pin  30
#define right_pwm_pin 39

void make_correction(int correction){
    if (correction > -500 && correction < 500){
        digitalWrite(left_dir_pin, LOW);
        digitalWrite(right_dir_pin, LOW);
    }else if (correction > 0){
        digitalWrite(left_dir_pin, HIGH);
        digitalWrite(right_dir_pin, LOW);
    }else{
        digitalWrite(left_dir_pin, LOW);
        digitalWrite(right_dir_pin, HIGH);
    }

    if (correction < 0) correction = -correction;

    analogWrite(left_pwm_pin, BASE_SPEED + correction);
    analogWrite(right_pwm_pin, BASE_SPEED + correction);
}


