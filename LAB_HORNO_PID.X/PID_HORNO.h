#ifndef __PID_HORNO
#define __PID_HORNO

#include <xc.h>
/*DEFINICION DE  MACROS*/
#define VIN_MAX             5
#define VIN_MIN             0
/************DEFINICION DE VARIABLES GLOBALES******/
extern float K1;
extern float K2;
extern float K3;

extern float e;
extern float e_1;
extern float e_2;
extern float v;
extern float v_1;
/*************DEFINICION DE PROTOTIPO DE FUNCIONES*/
void PID_Init(float Kp,float Ki,float Kd,float Ts);

float PID(float error);

void Oven_control(float uk);

#endif