#pragma once

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