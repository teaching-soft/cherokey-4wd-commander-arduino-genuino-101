/*
  Authors: Mattei, Martini
  Date: April 2017
  Description:
  Cherokey 4WD  wait commands from the bluetoot Low Energy channel and executes them

  Info:
  M1/M3 right wheels, M2/M4 left wheels

*/

#include <CurieBLE.h>

BLEService cherokeyService("19B10000-E8F2-537E-4F6C-D104768A1200"); // BLE Cherokey 4WD (not standard) Service

// BLE Cherokey 4WD command Characteristic - Max 20 bytes long
// Byte 1, in ASCII, direction (Stop/Forward/Backward/Left/Right)
// Bytes 2,3,4, in ASCII, right wheels speed (000-255)
// Bytes 5,6,7, in ASCII, left wheels speed (000-255)
// Bytes 8,9,10,11, in ASCII milli seconds to go (ex.0010)
// Byte 12 = # End of transmission
#define MAX_CHARACTERISTIC_LEN  12
// UUID, properties, maxlen
BLECharacteristic cherokeyCharacteristic("19B10001-E8F2-537E-4F6C-D104768A1200", BLERead | BLEWrite, MAX_CHARACTERISTIC_LEN);

#include "definitions.h"

void execute_cmd(char* cmd);

#define COMMUNICATION_ACTIVE_LED 13

void setup(){
  Serial.begin(9600);
  pinMode(COMMUNICATION_ACTIVE_LED, OUTPUT);
  int i;
  for (i = 4; i <= 7; i++) pinMode(i, OUTPUT);
  digitalWrite(pin_m1_m3_enable, LOW);
  digitalWrite(pin_m2_m4_enable, LOW);

  BLE.begin();

  // set advertised local name and service UUID:
  BLE.setLocalName("ArduinoWithCherokey");
  BLE.setAdvertisedService(cherokeyService);

  // add the characteristic to the service
  cherokeyService.addCharacteristic(cherokeyCharacteristic);

  // add service
  BLE.addService(cherokeyService);

  // set the initial value for the characeristic:
  cherokeyCharacteristic.setValue("");

  // start advertising
  BLE.advertise();
  Serial.println("Setup finished");

}

void loop(){
  
 // listen for BLE peripherals to connect:
  BLEDevice central = BLE.central();

  // if a central is connected to peripheral:
  if (central) {
    Serial.print("Connected to central: ");
    // print the central's MAC address:
    Serial.println(central.address());

    // while the central is still connected to peripheral:
    while (central.connected()) {
      if (cherokeyCharacteristic.written()) {
        digitalWrite(COMMUNICATION_ACTIVE_LED, HIGH);
        // Get the data
        char cmd_line[20];
        strncpy(cmd_line,(char*)cherokeyCharacteristic.value(),MAX_CHARACTERISTIC_LEN);
        cmd_line[MAX_CHARACTERISTIC_LEN] = '\0';
        Serial.print("Data arrived:");
        Serial.println(cmd_line);

        // Execute the command
        execute_cmd(cmd_line);
        digitalWrite(COMMUNICATION_ACTIVE_LED, LOW);
      }
    }
    Serial.print("Disconnected from central: ");
    Serial.println(central.address());
  }


  /*
  botFW(forward_speed,forward_speed);
  delay(ns * scount);
  botBW(backward_speed,backward_speed);
  delay(ns * scount);
  botLeft(turn_left_speed,turn_right_speed);
  delay(ns * scount);
  botRight(turn_right_speed,turn_left_speed);
  delay(ns * scount);
  */
}

void execute_cmd(char *cmd_line){
  char bot_direction, right_wheels_speed[4], left_wheels_speed[4],time_to_go[5],eot;
  int right_wheels_speed_i, left_wheels_speed_i,time_to_go_i;
  bot_direction = cmd_line[0];
  strncpy(right_wheels_speed,&cmd_line[1],3);
  right_wheels_speed[3] = '\0';
  right_wheels_speed_i = atoi(right_wheels_speed);
  
  strncpy(left_wheels_speed,&cmd_line[4],3);
  left_wheels_speed[3] = '\0';
  left_wheels_speed_i = atoi(left_wheels_speed);
  
  strncpy(time_to_go,&cmd_line[7],4);
  time_to_go[4] = '\0';
  time_to_go_i = atoi(time_to_go);
  
  eot = cmd_line[11];

  Serial.print("Direction: ");
  Serial.print(bot_direction);

  Serial.print(" Right weels: ");
  Serial.print(right_wheels_speed_i);

  Serial.print(" Left wheel: ");
  Serial.print( left_wheels_speed_i);

  Serial.print(" Right Time to go: ");
  Serial.print(time_to_go_i);

  Serial.print(" EOT: ");
  Serial.println(eot);

  switch (bot_direction) {
    case 'S':botStop();
      break;
    case 'F':botFW(left_wheels_speed_i,right_wheels_speed_i);
      delay(time_to_go_i);
      botStop();
      break;

    case 'B':botBW(left_wheels_speed_i,right_wheels_speed_i);
      delay(time_to_go_i);
      botStop();
      break;

    case 'L':botLeft(left_wheels_speed_i,right_wheels_speed_i);
      delay(time_to_go_i);
      botStop();
      break;

    case 'R':botRight(left_wheels_speed_i,right_wheels_speed_i);
      delay(time_to_go_i);
      botStop();
      break;
    default: Serial.println("Carattere direzione non valido");
      break;
  }
}




