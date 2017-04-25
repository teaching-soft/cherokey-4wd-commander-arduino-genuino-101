// Bot moves forward
void botFW(int left_speed,int right_speed) {

  analogWrite (pin_m2_m4_enable,left_speed);
  digitalWrite(pin_m1_m3_direction,CCW);
  analogWrite (pin_m1_m3_enable,right_speed);
  digitalWrite(pin_m2_m4_direction,CW);
}
void botBW(int left_speed,int right_speed){
  analogWrite (pin_m2_m4_enable,left_speed);
  digitalWrite(pin_m2_m4_direction,CCW);
  analogWrite (pin_m1_m3_enable,right_speed);
  digitalWrite(pin_m1_m3_direction,CW);
}

void botLeft(int left_speed,int right_speed) {
  analogWrite (pin_m2_m4_enable,left_speed);
  digitalWrite(pin_m2_m4_direction,CCW);
  analogWrite (pin_m1_m3_enable,right_speed);
  digitalWrite(pin_m1_m3_direction,CW);
}
void botRight(int left_speed,int right_speed)
{
  analogWrite (pin_m2_m4_enable,left_speed);
  digitalWrite(pin_m2_m4_direction,CCW);
  analogWrite (pin_m1_m3_enable,right_speed);
  digitalWrite(pin_m1_m3_direction,CW);

}
void botStop() {
  digitalWrite(pin_m2_m4_enable,0);
  digitalWrite(pin_m1_m3_direction,CW);
  digitalWrite(pin_m1_m3_enable,0);
  digitalWrite(pin_m2_m4_direction,CW);
}


