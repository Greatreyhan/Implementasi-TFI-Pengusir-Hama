
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 8); // CE, CSN

#define LED 3
#define TRIG 6
#define ECHO 7

const byte address[6] = "00001";

long duration, distance;

void setup() {
  Serial.begin(9600);
  pinMode(LED,OUTPUT);
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

void loop() {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  duration = pulseIn(ECHO, HIGH);
  distance = duration/58.2;

  char text[10];
  sprintf(text, "%d", distance);
  Serial.println(text);
  if(radio.write(&text, sizeof(text))) digitalWrite(LED,HIGH);
  else digitalWrite(LED,HIGH);
}