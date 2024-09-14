#include <Arduino.h>
#include "Task.h"

void setup() {
    Serial.begin(9600); // Required to receive stability alerts on serial monitor.

    pinMode(12, OUTPUT);
    pinMode(13, OUTPUT);
}

void led1High() {
    Serial.println("1. high OK");
    digitalWrite(13, HIGH);
}

void led2High() {
    Serial.println("2. high OK");
    digitalWrite(12, HIGH);
}

void led1Low() {
    Serial.println("1. low OK");
    digitalWrite(13, LOW);
}

void led2Low() {
    Serial.println("2. low OK");
    digitalWrite(12, LOW);
}

void loop() {
    Task *led1On = new Task("Led 1 On", 1150);
    Task *led1Off = new Task("Led 1 Off", 2000);
    Task *led2On = new Task("Led 2 On", 1150);
    Task *led2Off = new Task("Led 2 Off", 2000);
    
    led1On->Task_start(&led1High);
    led1Off->Task_start(&led1Low);
    led2On->Task_start(&led2High);
    led2Off->Task_start(&led2Low);
    
    /*
    * This section will never be triggered in this example,
    * but it has been included for illustrative purposes
    */
    
    led1On->Task_terminate();
    led1Off->Task_terminate();
    led2On->Task_terminate();
    led2Off->Task_terminate();
}
