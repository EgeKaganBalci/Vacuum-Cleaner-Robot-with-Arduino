#include <SoftPWM.h>

// Pin tanımlamaları
const int trigPin1 = 3;
const int echoPin1 = 5;
const int trigPin2 = 6;
const int echoPin2 = 9;
const int trigPin3 = 10;
const int echoPin3 = 11;
int irpin = 2;

const int ena = 0; // D0
const int enb = 1; // D1

long duration1, duration2, duration3;
int distanceleft, distancefront, distanceright;
int a = 0;

void setup() {
  pinMode(trigPin1, OUTPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(echoPin2, INPUT);
  pinMode(echoPin3, INPUT);
  pinMode(irpin, INPUT);
  pinMode(4, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(12, OUTPUT);

  SoftPWMBegin();
  SoftPWMSet(ena, 80); // Sabit hız
  SoftPWMSet(enb, 80);

  randomSeed(analogRead(A0)); // Rastgelelik için
}

void loop() {
  // Mesafeleri oku
  digitalWrite(trigPin1, LOW); delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH); delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  duration1 = pulseIn(echoPin1, HIGH);
  distanceleft = duration1 * 0.034 / 2;

  digitalWrite(trigPin2, LOW); delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH); delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  duration2 = pulseIn(echoPin2, HIGH);
  distancefront = duration2 * 0.034 / 2;

  digitalWrite(trigPin3, LOW); delayMicroseconds(2);
  digitalWrite(trigPin3, HIGH); delayMicroseconds(10);
  digitalWrite(trigPin3, LOW);
  duration3 = pulseIn(echoPin3, HIGH);
  distanceright = duration3 * 0.034 / 2;

  int s = digitalRead(irpin);

  // Engel varsa geri git
  if (s == HIGH) {
    digitalWrite(4, LOW); digitalWrite(7, HIGH); // geri sol
    digitalWrite(8, LOW); digitalWrite(12, HIGH); // geri sağ
    delay(1000);
    a = 1;
  }

  // Tüm yönler boşsa veya sadece sol-sağ doluysa düz git
  if ((a == 0 && s == LOW && distancefront > 20 && distanceleft <= 20 && distanceright <= 20) ||
      (a == 0 && s == LOW && distancefront > 20 && distanceleft > 20 && distanceright > 20)) {
    digitalWrite(4, HIGH); digitalWrite(7, LOW);
    digitalWrite(8, HIGH); digitalWrite(12, LOW);
  }

  // Ön ve sol doluysa sağa dön
  else if ((s == LOW && distancefront <= 20 && distanceleft <= 20 && distanceright > 20) ||
           (s == LOW && distancefront > 20 && distanceleft <= 20 && distanceright > 20)) {
    stopAndWait();
    digitalWrite(4, HIGH); digitalWrite(7, LOW);
    digitalWrite(8, LOW); digitalWrite(12, HIGH); // sağa dönüş
    delay(500);
  }

  // Ön ve sağ doluysa sola dön
  else if ((s == LOW && distancefront <= 20 && distanceright <= 20 && distanceleft > 20) ||
           (s == LOW && distancefront > 20 && distanceright <= 20 && distanceleft > 20)) {
    stopAndWait();
    digitalWrite(4, LOW); digitalWrite(7, HIGH);
    digitalWrite(8, HIGH); digitalWrite(12, LOW); // sola dönüş
    delay(500);
  }

  // Her yön doluysa geri git
  else if (s == LOW && distancefront <= 20 && distanceleft <= 20 && distanceright <= 20) {
    stopAndWait();
    digitalWrite(4, LOW); digitalWrite(7, HIGH);
    digitalWrite(8, LOW); digitalWrite(12, HIGH); // geri
    delay(800);
  }

  // Ön dolu, sağ ve sol boş → rastgele yön seç
  else if (s == LOW && distancefront <= 20 && distanceleft > 20 && distanceright > 20) {
    stopAndWait();
    if (random(0, 2) == 0) {
      // sola dön
      digitalWrite(4, LOW); digitalWrite(7, HIGH);
      digitalWrite(8, HIGH); digitalWrite(12, LOW);
    } else {
      // sağa dön
      digitalWrite(4, HIGH); digitalWrite(7, LOW);
      digitalWrite(8, LOW); digitalWrite(12, HIGH);
    }
    delay(500);
  }

  a = 0; // Engel geçince sıfırla
}

void stopAndWait() {
  digitalWrite(4, LOW);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
  digitalWrite(12, LOW);
  delay(500); // Bekleme süresi
}