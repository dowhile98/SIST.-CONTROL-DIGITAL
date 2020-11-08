#include "PID_HORNO.h"

/*****DEFINICIOND DE VARIABLES GLOBALES*******/
float K1;
float K2;
float K3;

float e;
float e_1;
float e_2;
float v;
float v_1 = 0.625;

/*******DEFINICION DE FUNCIONES*/

void PID_Init(float Kp,float Ki,float Kd,float Ts){
    /*K1 = Kp +(Ki/2)*Ts + Kd/Ts;
    K2 = -Kp +(Ki/2)*Ts - 2*Kd/Ts;
    K3 = Kd/Ts;*/
    K1 = 1.12;
    K2 = -1.097;
    K3 = 0;
    
    T2CONbits.TON = 1;                  //SE INICIALIZA PWM
}
float PID(float error){
    e = error;
    v = v_1 + K1*e + K2*e_1 + K3*e_2;   //c(k) = c(k-1)+K1*e(k)+k2*e(k-1)+k3*e(k-2)
    if(v>VIN_MAX)
        v = VIN_MAX;
    if(v<VIN_MIN)
        v = VIN_MIN;
    e_2 = e_1;
    e_1 = e;
    v_1 = v;
    return v;
}

void Oven_control(float uk){
    float duty = uk*1300.0/5 + 1;
    OC1RS = (uint16_t)duty ;
}
