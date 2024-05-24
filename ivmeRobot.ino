#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10); // CE, CSN pinleri
const byte address[6] = "00001";

// Motor pinlerini tanımla
const int motor1IleriPin = 2;
const int motor1GeriPin = 3;
const int motor2IleriPin = 4;
const int motor2GeriPin = 5;

// LED pinini tanımla
const int ledPinSag = 7;
const int ledPinSol = 8;

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(1, address);
  radio.setPALevel(RF24_PA_LOW);
  radio.startListening();

  // Motor pinlerini çıkış olarak ayarla
  pinMode(motor1IleriPin, OUTPUT);
  pinMode(motor1GeriPin, OUTPUT);
  pinMode(motor2IleriPin, OUTPUT);
  pinMode(motor2GeriPin, OUTPUT);

  // LED pinini çıkış olarak ayarla
  pinMode(ledPinSag, OUTPUT);
  pinMode(ledPinSol, OUTPUT);
}

void loop() {
  
if (radio.available()) {
    float x, y, z;
    radio.read(&x, sizeof(x));
    radio.read(&y, sizeof(y));
    radio.read(&z, sizeof(z));

    // Gelen verileri seri monitöre yazdır
    Serial.print("X: "); Serial.print(x); Serial.print("  ");
    Serial.print("Y: "); Serial.print(y); Serial.print("  ");
    Serial.print("Z: "); Serial.print(z); Serial.println("");

    // Aracın hareketini kontrol et
    if (y < -3) {
      Serial.println("İleri Hareket");
      motorIleri();
    } else if (y > 3) {
      Serial.println("Geri Hareket");
      motorGeri();
    } else if (x > 3) {
      Serial.println("Sola Hareket");
      motorSola();
    } else if (x < -3) {
      Serial.println("Sağa Hareket");
      motorSaga();
    } else {
      stop();
    }

    delay(1000); // Veri alma aralığını belirle
  }
}

// Sola hareket fonksiyonu
void motorSola() {
  digitalWrite(motor1IleriPin, HIGH);
  digitalWrite(motor1GeriPin, LOW);
  digitalWrite(motor2IleriPin, HIGH);
  digitalWrite(motor2GeriPin, LOW);
  digitalWrite(ledPinSag, LOW);
  digitalWrite(ledPinSol, HIGH);
}

// Saga hareket fonksiyonu
void motorSaga() {
  digitalWrite(motor1IleriPin, LOW);
  digitalWrite(motor1GeriPin, HIGH);
  digitalWrite(motor2IleriPin, LOW);
  digitalWrite(motor2GeriPin, HIGH);
  digitalWrite(ledPinSag, HIGH);
  digitalWrite(ledPinSol, LOW);
}

// İleri hareket fonksiyonu
void motorIleri() {
  digitalWrite(motor1IleriPin, HIGH);
  digitalWrite(motor1GeriPin, LOW);
  digitalWrite(motor2IleriPin, LOW);
  digitalWrite(motor2GeriPin, HIGH);
  digitalWrite(ledPinSag, HIGH);
  digitalWrite(ledPinSol, HIGH);
}

// Geri hareket fonksiyonu
void motorGeri() {
  digitalWrite(motor1IleriPin, LOW);
  digitalWrite(motor1GeriPin, HIGH);
  digitalWrite(motor2IleriPin, HIGH);
  digitalWrite(motor2GeriPin, LOW);
  digitalWrite(ledPinSag, LOW);
  digitalWrite(ledPinSol, LOW);
}

// Durma fonksiyonu
void stop() {
  digitalWrite(motor1IleriPin, LOW);
  digitalWrite(motor1GeriPin, LOW);
  digitalWrite(motor2IleriPin, LOW);
  digitalWrite(motor2GeriPin, LOW);
  digitalWrite(ledPinSag, LOW);
  digitalWrite(ledPinSol, LOW);
}