unsigned long currentTime = 0;
const int ledPins[] = { 8, 9, 10, 11};
int nbLed = sizeof(ledPins) / sizeof(ledPins[0]);
int pinButton = 2;           
int potentiometerValue = 0;  
int potentiometerValueConverted = 0;
int nbBar = 20;

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < nbLed; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
  pinMode(pinButton, INPUT_PULLUP);
  Serial.println("Setup completed");
}

void loop() {
  currentTime = millis();
  potentiometerValue = analogRead(A1);
  button(currentTime, potentiometerValue);
  setLed(potentiometerValue);
}

void button(int currentTime, int potentiometerValue) {
  static int etatPrecedent = HIGH;
  static int etat = HIGH;
  const int delai = 50;
  static unsigned long dernierChangement = 0;

  int etatPresent = digitalRead(pinButton);

  if (etatPresent != etatPrecedent) {
    dernierChangement = millis();
  }

  if ((millis() - dernierChangement) > delai && etatPresent != etat) { 
    etat = etatPresent;
    if (etat == LOW) {  
      progressionBar(potentiometerValue);
    }
  }
  etatPrecedent = etatPresent; // Mise à jour pour la prochaine itération
}

void progressionBar(int potentiometerValue) {
   potentiometerValue = map (potentiometerValue, 0, 1023, 0, 100);
   potentiometerValueConverted = map (potentiometerValue, 0, 100, 0, nbBar);

   Serial.print(potentiometerValue);
   Serial.print("% [");

   for (int i = 0; i < nbBar; i++) {
     if ( i < potentiometerValueConverted) {
        Serial.print('@');
      } else {
        Serial.print('.');
      }
   }
   Serial.println(']');
}

void setLed(int potentiometerValue) { 
  int indexLed = map (potentiometerValue, 0, 1023, 0, nbLed);
  if (indexLed == nbLed) {
    indexLed--;
  }
  for (int i = 0; i < nbLed; i++) {
    if (i == indexLed) {
      digitalWrite(ledPins[i], HIGH);
    }
    else {
      digitalWrite(ledPins[i], LOW);
    }
  }
}