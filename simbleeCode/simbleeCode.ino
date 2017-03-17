/*
The sketch demonstrates how to do continuous Bluetooth Low Energy 4
Advertisement with the Simblee.
*/

/*
 * Copyright (c) 2015 RF Digital Corp. All Rights Reserved.
 *
 * The source code contained in this file and all intellectual property embodied in
 * or covering the source code is the property of RF Digital Corp. or its licensors.
 * Your right to use this source code and intellectual property is non-transferable,
 * non-sub licensable, revocable, and subject to terms and conditions of the
 * SIMBLEE SOFTWARE LICENSE AGREEMENT.
 * http://www.simblee.com/licenses/SimbleeSoftwareLicenseAgreement.txt
 *
 * THE SOURCE CODE IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND.
 *
 * This heading must NOT be removed from this file.
 */

#include <SimbleeBLE.h>

// pin 3 on the RGB shield is the green led
int ad_led = 0;
int conn_led = 1;
int run_led = 2;
int motor = 6;
int pulse=1100;
bool runMotor = false;

bool connection = false;

void setup() {
  // ad_led indicates that the arduino is advertising
  // conn_led indicates the arduino is connected to the laptop
  // motor pin is eponymous
  pinMode(ad_led, OUTPUT);
  pinMode(conn_led, OUTPUT);
  pinMode(run_led, OUTPUT);
  pinMode(motor, OUTPUT);
  
  // this defines which name the arduino has when we see it in bluetooth
  SimbleeBLE.deviceName = "VALTR";

  // start the BLE stack
  SimbleeBLE.begin();

  delay(5000);
  // arm the ESC
  arm_ESC();
}


void loop() {
  if (runMotor) {
    digitalWrite(run_led, HIGH);
    run_ESC(pulse);
  } else {
    digitalWrite(run_led, LOW);
  }
}


void arm_ESC() {
for (int arm_time = 0; arm_time < 500; arm_time++)
  {
  digitalWrite(motor,HIGH);
  delayMicroseconds(1100);
  digitalWrite(motor,LOW);
  delay(20-(pulse/1000));
  delayMicroseconds(1100);
  digitalWrite(motor, LOW);
  delay(20 - (pulse / 1000));
  }
}


void run_ESC(int pulse) {
  // run the ESC at pulse
  digitalWrite(motor,HIGH);
  delayMicroseconds(pulse);
  digitalWrite(motor,LOW);
  delay(20-pulse/1000);
}

void SimbleeBLE_onAdvertisement(bool start)
{
  // turn the green led on if we start advertisement, and turn it
  // off if we stop advertisement

  if (start)
    digitalWrite(ad_led, HIGH);
  else
    digitalWrite(ad_led, LOW);
}


void SimbleeBLE_onConnect() {
  digitalWrite(conn_led, HIGH);
}


void SimbleeBLE_onDisconnect() {
  digitalWrite(conn_led, LOW);
}


void SimbleeBLE_onReceive(char *data, int len) {
  const char *recvData = data;
  int sendVal = map((int)data[1],0,255,1100,2000);
  
  SimbleeBLE.sendInt(sendVal);
  if (sendVal == 1100) {
    runMotor = false;
    arm_ESC();
  } else if (sendVal < 2001) {
    runMotor = true;
    pulse = sendVal;
  } else {
    runMotor = false;
  }
}

