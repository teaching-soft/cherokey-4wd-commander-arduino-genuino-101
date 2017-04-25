#define CCW HIGH
#define CW  LOW

const int pin_m1_m3_enable = 5; // Board Pin 5 connected to D5 M1/M3 Enable-PWM Speed Control
const int pin_m2_m4_enable = 6; // Board Pin 6 connected to D6 M2/M4 Enable-PWM Speed Control

const int pin_m1_m3_direction = 4;  // Board Pin 4 connected to D4 M1/M3 Direction Control
                                    // D4 HIGH M1/M3 CCW  D4 LOW M1/M3 CW

const int pin_m2_m4_direction = 7;  // Board PIN 7 connected to D7 M2/M4 Direction Control
                                    // D7 HIGH M2/M4 CCW  D7 LOW M2/M4 CW
/*
int forward_speed = 100;
int backward_speed = 100;
int turn_right_speed = 250;
int turn_left_speed = 50;
int max_speed = 255;
int scount = 1000;
int ns=2;
*/
// Bot moves forward
void botFW(int left_speed,int right_speed);
//  Motor Stop
void botStop(void);
//  Bot moves backward
void botBW(int left_speed,int right_speed);
//  Bot turns left
void botLeft(int left_speed,int right_speed);
//  Bot Turn Right
void botRight(int left_speed,int right_speed);
