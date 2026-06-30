#include "GENG1201_Project.h"

// ------------------ LINE FOLLOW SETTINGS ------------------
unsigned long lostTime = 0;
bool searching = false;

// ------------------ HALLWAY SCAN SETTINGS ------------------
unsigned long lastScanTime = 0;

int SPEED_HALLWAY = 60;
int SPEED_LINE    = 90;
int SPEED_TURN    = 75;

int CENTER_TOL = 3;
int TURN_TIME  = 120;

// Ultrasonic servo 1 angles
int ANGLE_CENTER = 90;
int ANGLE_RIGHT  = 0;
int ANGLE_LEFT   = 180;

// White line thresholds (WHITE = LOWER)
int TH_M = 240;
int TH_L = 52;
int TH_R = 52;

// signal pin to other board
int SIGNAL_PIN = 11;

// Modes
enum Mode { HALLWAY, LINE_FOLLOW, STOP_DONE };
Mode mode = HALLWAY;

// Read ultrasonic distance
int readDistanceCM() {
  readUltrasonicSensor(get_Distance);
  return (int)get_Distance;
}

void setup() {
  Init();

  // ultrasonic servo center
  servoControl(ANGLE_CENTER);

  // keep signal pin inactive at startup
  pinMode(SIGNAL_PIN, INPUT);

  lastScanTime = millis();
  pinMode(SIGNAL_PIN, OUTPUT);
  digitalWrite(SIGNAL_PIN, LOW);


}

void loop() {
  int L = infraRed_L();
  int M = infraRed_M();
  int R = infraRed_R();

  bool Mw = (M <= TH_M);
  bool Lw = (L <= TH_L);
  bool Rw = (R <= TH_R);

  // ------------------ MODE 1: HALLWAY ------------------
  if (mode == HALLWAY) {

    // if line found, switch to line following
    if (Mw || Lw || Rw) {
      move(stop_it, 0);
      delay(120);
      searching = false;
      servoControl(ANGLE_CENTER);
      mode = LINE_FOLLOW;
      return;
    }

    // move forward while searching for line
    move(Forward, SPEED_HALLWAY);

    // every 2 seconds check walls and center robot
    if (millis() - lastScanTime >= 2000) {
      lastScanTime = millis();

      // look right
      servoControl(ANGLE_RIGHT);
      delay(250);
      int dR = readDistanceCM();

      // look left
      servoControl(ANGLE_LEFT);
      delay(250);
      int dL = readDistanceCM();

      // back to center
      servoControl(ANGLE_CENTER);
      delay(120);

      // correction
      if (dR - dL > CENTER_TOL) {
        move(Right, SPEED_TURN);
        delay(TURN_TIME);
        move(Forward, SPEED_HALLWAY);
      }
      else if (dL - dR > CENTER_TOL) {
        move(Left, SPEED_TURN);
        delay(TURN_TIME);
        move(Forward, SPEED_HALLWAY);
      }
    }

    delay(5);
    return;
  }

  // ------------------ MODE 2: LINE FOLLOW ------------------
  if (mode == LINE_FOLLOW) {

    L = infraRed_L();
    M = infraRed_M();
    R = infraRed_R();

    Mw = (M <= TH_M);
    Lw = (L <= TH_L);
    Rw = (R <= TH_R);

    // line found
    if (Mw || Lw || Rw) {
      searching = false;

      if (Mw) {
        move(Forward, SPEED_LINE);
      }
      else if (Rw) {
        move(Right, SPEED_LINE);
      }
      else if (Lw) {
        move(Left, SPEED_LINE);
      }
    }

    // line lost
    else {
      if (!searching) {
        searching = true;
        lostTime = millis();
      }

      // keep moving a little to confirm line really ended
      if (millis() - lostTime < 2000) {
        move(Forward, 70);
      }
      else {
        // final stop
        move(stop_it, 0);

        // NOW send signal to the other board
        mode = STOP_DONE;
      }
    }

    delay(5);
    return;
  }

  // ------------------ MODE 3: STOP ------------------
  
  if (mode == STOP_DONE) {
    move(stop_it, 0);
    // keep signal HIGH forever
    digitalWrite(SIGNAL_PIN, HIGH);
  }

}
