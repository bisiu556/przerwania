const byte pinCzujnika1 = 2;
const byte pinCzujnika2 = 3;

const byte ledCzerwony1 = 7;
const byte ledZielony1  = 8;

const byte ledCzerwony2 = 13;
const byte ledZielony2  = 12;

volatile bool ruch1Wykryty = false;
volatile bool ruch2Wykryty = false;

int stan = 0;
unsigned long poprzedniCzas = 0;

void setup() {
  pinMode(ledCzerwony1, OUTPUT);
  pinMode(ledZielony1, OUTPUT);
  pinMode(ledCzerwony2, OUTPUT);
  pinMode(ledZielony2, OUTPUT);

  pinMode(pinCzujnika1, INPUT);
  pinMode(pinCzujnika2, INPUT);

  attachInterrupt(digitalPinToInterrupt(pinCzujnika1), czujka1, RISING);
  attachInterrupt(digitalPinToInterrupt(pinCzujnika2), czujka2, RISING);

  ustawObaCzerwone();
}

void loop() {
  unsigned long aktualnyCzas = millis();

  switch (stan) {
    case 0:
      if (ruch1Wykryty) {
        ruch1Wykryty = false;
        digitalWrite(ledCzerwony2, HIGH);
        digitalWrite(ledZielony2, LOW);
        digitalWrite(ledCzerwony1, LOW);
        digitalWrite(ledZielony1, HIGH);
        stan = 1;
      } 
      else if (ruch2Wykryty) {
        ruch2Wykryty = false;
        digitalWrite(ledCzerwony1, HIGH);
        digitalWrite(ledZielony1, LOW);
        digitalWrite(ledCzerwony2, LOW);
        digitalWrite(ledZielony2, HIGH);
        stan = 4;
      }
      break;

    case 1:
      if (digitalRead(pinCzujnika1) == LOW) {
        poprzedniCzas = aktualnyCzas;
        stan = 2;
      }
      break;

    case 2:
      if (digitalRead(pinCzujnika1) == HIGH) {
        stan = 1;
      } else if (aktualnyCzas - poprzedniCzas >= 5000) {
        ustawObaCzerwone();
        poprzedniCzas = aktualnyCzas;
        stan = 3;
      }
      break;

    case 3:
      if (aktualnyCzas - poprzedniCzas >= 2000) {
        stan = 0;
      }
      break;

    case 4:
      if (digitalRead(pinCzujnika2) == LOW) {
        poprzedniCzas = aktualnyCzas;
        stan = 5;
      }
      break;

    case 5:
      if (digitalRead(pinCzujnika2) == HIGH) {
        stan = 4;
      } else if (aktualnyCzas - poprzedniCzas >= 5000) {
        ustawObaCzerwone();
        poprzedniCzas = aktualnyCzas;
        stan = 6;
      }
      break;

    case 6:
      if (aktualnyCzas - poprzedniCzas >= 2000) {
        stan = 0;
      }
      break;
  }
}

void czujka1() {
  ruch1Wykryty = true;
}

void czujka2() {
  ruch2Wykryty = true;
}

void ustawObaCzerwone() {
  digitalWrite(ledCzerwony1, HIGH);
  digitalWrite(ledZielony1, LOW);
  digitalWrite(ledCzerwony2, HIGH);
  digitalWrite(ledZielony2, LOW);
}