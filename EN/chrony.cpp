/*
Name : Chrony for airsoft
Creator : PépéMax
Version : 1.1.0 - EN
*/

#define BUTTON 2
#define SENSOR_1 3
#define SENSOR_2 4
#define EMITTER_1 5
#define EMITTER_2 6

float ball_weight = 0.20; // Ball grammage
float sensor_distance = 0.1; // Distance between two sensors in meters

float ball_time; // Time it takes for the ball to go through the two sensors in seconds
float ball_speed; // Ball speed in m/s
float replica_joule; // Power generated by the replica in J
float replica_fps; // Replica's FPS

float sensor_time_1;
float sensor_time_2;

bool sensor_state_1 = HIGH;
bool sensor_state_2 = HIGH;
bool button_state = HIGH;

void setup() {
  Serial.begin(115200);

  pinMode(BUTTON, INPUT_PULLUP);
  pinMode(SENSOR_1, INPUT_PULLUP);
  pinMode(SENSOR_2, INPUT_PULLUP);
  pinMode(EMITTER_1, OUTPUT);
  pinMode(EMITTER_2, OUTPUT);

  digitalWrite(EMITTER_1, LOW);
  digitalWrite(EMITTER_2, LOW);
}

void loop() {
  sensor_state_1 = digitalRead(SENSOR_1);
  sensor_state_2 = digitalRead(SENSOR_2);
  button_state = digitalRead(BUTTON);

  if (button_state == LOW) {
  
    digitalWrite(EMITTER_1, HIGH);
    digitalWrite(EMITTER_2, HIGH);

    if (sensor_state_1 == LOW) {
      sensor_time_1 = micros();
      Serial.println(sensor_time_1);
    }

    if (sensor_state_2 == LOW) {                                       
      sensor_time_2 = micros();
      Serial.println(sensor_time_2);
    }

    //Calculation

    ball_time = (sensor_time_1 - sensor_time_1)/1000000;
    ball_speed = sensor_distance/ball_time;
    replica_joule = 0.5*(ball_weight/1000)*pow(ball_speed, 2);
    replica_fps = ball_speed/0.3048;

    delay(1000);
    Serial.println(ball_speed, 10);
    Serial.println(replica_joule);
    Serial.println(replica_fps);
  }

  else {
    digitalWrite(EMITTER_1, LOW);
    digitalWrite(EMITTER_2, LOW);
  }
}
