/*
Nom : Chrony pour airsoft
Créateur : PépéMax
Version : 1.0.0
*/

#define BOUTON 2
#define CAPTEUR_1 3
#define CAPTEUR_2 4
#define EMETTEUR_1 5
#define EMETTEUR_2 6

float poids_bille = 0.20; // Grammage de la bille en g
float distance_capteur = 0.1; // Distance des deux capteurs en mètre

float temps_bille; // Temps quer la bille met pour traverser les deux capteurs en seconde
float vitesse_bille; // Vitesse de la bille en m/s
float joule_bille; // Puissance dévellopé par la réplique en J
float fps_bille; // Nombre de FPS de la réplique

float temps_capteur_1;
float temps_capteur_2;

bool etat_capteur_1 = HIGH;
bool etat_capteur_2 = HIGH;
bool etat_bouton = HIGH;

void setup() {
  Serial.begin(115200);

  pinMode(BOUTON, INPUT_PULLUP);
  pinMode(CAPTEUR_1, INPUT_PULLUP);
  pinMode(CAPTEUR_2, INPUT_PULLUP);
  pinMode(EMETTEUR_1, OUTPUT);
  pinMode(EMETTEUR_2, OUTPUT);

  digitalWrite(EMETTEUR_1, LOW);
  digitalWrite(EMETTEUR_2, LOW);
}

void loop() {
  etat_capteur_1 = digitalRead(CAPTEUR_1);
  etat_capteur_2 = digitalRead(CAPTEUR_2);
  etat_bouton = digitalRead(BOUTON);

  if (etat_bouton == LOW) {
    Serial.println("En attente de Tir");

    digitalWrite(EMETTEUR_1, HIGH);
    digitalWrite(EMETTEUR_2, HIGH);

    if (etat_capteur_1 == LOW) {
      temps_capteur_1 = millis();
      Serial.println(temps_capteur_1);
    }

    if (etat_capteur_2 == LOW) {                                       
      temps_capteur_2 = millis();
      Serial.println(temps_capteur_2);
    }

    //Calculs

    temps_bille = (temps_capteur_2 - temps_capteur_1)/1000; // Temps que la bille met pour traverser les deux capteurs en seconde
    vitesse_bille = distance_capteur/temps_bille;
    joule_bille = 0.5*(poids_bille/1000)*pow(vitesse_bille, 2);
    fps_bille = vitesse_bille/0.3048;

    delay(1000);
    Serial.println(vitesse_bille, 10);
    Serial.println(joule_bille);
    Serial.println(fps_bille);
  }

  else {
    digitalWrite(EMETTEUR_1, LOW);
    digitalWrite(EMETTEUR_2, LOW);
  }
}
