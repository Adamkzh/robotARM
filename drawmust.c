#include <Servo.h>

// === Motor Pins ===
#define AmotorPin 2
#define BmotorPin 3
#define CmotorPin 4
#define DmotorPin 5

// === Initial Angles ===
int A_angle = 170;  // claw shut
int B_angle = 80;   // base angle
int C_angle = 170;  // height
int D_angle = 90;   // rotation

// === Servo objects ===
Servo Amotor, Bmotor, Cmotor, Dmotor;
Servo* motors[] = { &Amotor, &Bmotor, &Cmotor, &Dmotor };
int angles[] = { A_angle, B_angle, C_angle, D_angle };
int pins[] = { AmotorPin, BmotorPin, CmotorPin, DmotorPin };

String comdata = "";

void setup() {
  for (int i = 0; i < 4; i++) {
    motors[i]->attach(pins[i]);
    motors[i]->write(angles[i]);
    delay(150);
  }
  Serial.begin(9600);
}

// === Motor Movement ===
void motormove(int motor, int st, int ed) {
  if (motor < 1 || motor > 4) return;
  int step = (st < ed) ? 1 : -1;
  for (int i = st; i != ed + step; i += step) {
    motors[motor - 1]->write(i);
    delay(20);
  }
}

// === Movement and Drawing Utilities ===
void movetopoint(int x, int y) {
  motormove(2, x, x);
  motormove(3, x + 30, x + 30);
  motormove(4, y, y);
}

void drawline(int x, int y, int xx, int yy) {
  movetopoint(x, y);
  float dy = (float)(yy - y) / ((xx != x) ? (xx - x) : 1);
  if (xx != x) {
    for (int i = x; (xx > x) ? i <= xx : i >= xx; i += (xx > x ? 1 : -1)) {
      movetopoint(i, y + dy * (i - x));
    }
  } else {
    for (int i = y; (yy > y) ? i <= yy : i >= yy; i += (yy > y ? 1 : -1)) {
      movetopoint(x, i);
    }
  }
}

void penup(int s) {
  motormove(3, s + 30, C_angle);
  motormove(2, s, B_angle);
}

void pensdown(int t, int p, int q) {
  motormove(4, p, q);
  motormove(2, B_angle, t);
  motormove(3, C_angle, t + 30);
}

// === Drawing Functions ===
// NOTE: Keep your existing DrawA - DrawZ and drawmust() functions as they are

// === Mapping characters to drawing ===
typedef void (*DrawFunc)(int);
DrawFunc drawFuncs[26] = {
  DrawA, DrawB, DrawC, DrawD, DrawE, DrawF, DrawG,
  DrawH, DrawI, DrawJ, DrawK, DrawL, DrawM, DrawN,
  DrawO, DrawP, DrawQ, DrawR, DrawS, DrawT, DrawU,
  DrawV, DrawW, DrawX, DrawY, DrawZ
};

void drawChar(char ch, int index) {
  if (ch >= 'A' && ch <= 'Z') {
    drawFuncs[ch - 'A'](index);
  } else if (ch == 'm') {
    drawmust();
  }
}

// === Loop ===
void loop() {
  while (Serial.available() > 0) {
    comdata += char(Serial.read());
    delay(2);
  }

  if (comdata.length() > 0) {
    for (int i = 0; i < comdata.length() && i < 8; i++) {
      drawChar(comdata[i], i + 1);
    }
    comdata = "";
  }
}
