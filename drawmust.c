#define AmotorPin 2
#define BmotorPin 3
#define CmotorPin 4
#define DmotorPin 5


// SHOW INITIAL POSITION
int A_angle = 170;   /*clawopen=80   clawshut= 170  */
int B_angle = 80; /*max=150(claw equal to the horizon) min=45*/
int C_angle = 170; /*max angle=180(claw highest), min angle=95*/
int D_angle = 90;  /*leftmost=180     rightmost=25   mid=112      */
int val;



#include <Servo.h>

Servo Amotor;
Servo Cmotor;
Servo Bmotor;
Servo Dmotor;
String comdata = "";


void setup()
{
  Amotor.attach(AmotorPin);
  Amotor.write(A_angle);
  delay(150);
  Cmotor.attach(CmotorPin);
  Cmotor.write(C_angle);
  delay(150);
  Bmotor.attach(BmotorPin);
  Bmotor.write(B_angle);
  delay(150);
  Dmotor.attach(DmotorPin);
  Dmotor.write(D_angle);
  Serial.begin(9600); //initial serial communiction and set board rat 9600

}







// x is the POSITION in the radius, and y is rotation angle of the arm
//    70<x<120   25(most right)<y<180(most right) mid=112°
void movetopoint(int x, int y)

{
  motormove(2,x,x);
  motormove(3,x+30,x+30);
  motormove(4,y,y);
}



// move the meArm to draw a line form (x,y) to (xx,yy)
void drawline(int x, int y, int xx, int yy) {

  movetopoint(x, y);

  if (xx > x) {
    float dy = (float)(yy - y) / (xx - x);
    for (int i = x; i < xx; i++) {
       movetopoint(i, y + dy * (i - x));
    }
  }
  else if (xx < x) {
    float dy = (float)(yy - y) / (xx - x);
    for (int i = x; i > xx; i--) {
      movetopoint(i, y + dy * (i - x));
    }
  }
  else {
    if(y<yy){
      for(int i=y;i<yy;i++){
        movetopoint(x,i);
      }
    }
    else{
      for(int i=y;i>yy;i--){
        movetopoint(x,i);
      }
    }

  }

}


// let the pen up DO REMEMBER make the  Z rotation at last.
void penup(int s)
{
motormove(3, s+30 ,C_angle);
motormove(2, s , B_angle);

}


//let the pen down, DO REMEMBER make the Z rotation at first.
void pensdown(  int t, int p, int q )
{
  motormove(4, p , q);
  motormove(2, B_angle , t);
  motormove(3, C_angle, t+30);
}



// move servo form st angle to ed angle
void motormove(int motor, int st, int ed) {
  if (st < ed) {
    switch (motor) {
      case 1:
        for (int i = st; i <= ed; i++) {
          Amotor.write(i);
          delay(20);
        }
        break;
      case 2:
        for (int i = st; i <= ed; i++) {
          Bmotor.write(i);
          delay(20);
        }
        break;
      case 3:
        for (int i = st; i <= ed; i++) {
          Cmotor.write(i);
          delay(20);
        }
        break;
      case 4:
        for (int i = st; i <= ed; i++) {
          Dmotor.write(i);
          delay(20);
        }
        break;
    }
  }
  else {
    switch (motor) {
      case 1:
        for (int i = st; i >= ed; i--) {
          Amotor.write(i);
          delay(20);
        }
        break;
      case 2:
        for (int i = st; i >= ed; i--) {
          Bmotor.write(i);
          delay(20);
        }
        break;
      case 3:
        for (int i = st; i >= ed; i--) {
          Cmotor.write(i);
          delay(20);
        }
        break;
      case 4:
        for (int i = st; i >= ed; i--) {
          Dmotor.write(i);
          delay(20);
        }
        break;
    }
  }
}




void drawmust()
{


  motormove(4,D_angle,175);
  motormove(3,C_angle,110);
  motormove(2,B_angle,80);

//M
  drawline(80,175,100,170);
  drawline(100,170,80,165);
  drawline(80,165,100,160);
  drawline(100,160,80,155);

  penup(80);
  pensdown(100,155,145);
  //U
  drawline(100,145,80,145 );
  drawline(80,145,80,125);
  drawline(80,125,100,125);

  penup(100);
  pensdown(100,125,95);
//S
  movetopoint(100,95);
  drawline(100,95,100,115);
  drawline(100,115,90,115);
  drawline(90,115,90,95);
  drawline(90,95,80,95 );
  drawline(80,95,80,115);

  penup(80);
  pensdown(100,115,85);


// T

  drawline(100,85,100,65);

  penup(100);
  pensdown(100,65,75);


  drawline(100,75,80,75);

  penup(80);

}

//width 15 height 20
// "A"
void DrawA( int arraya ){

int positiona = (170- (17 * (arraya-1)));

motormove(4,(positiona+2),positiona);// gap between words is 2
motormove(2,B_angle,100);
motormove(3,C_angle,130);

drawline(100,positiona,120,(positiona-7));
drawline(120,(positiona-7),100,(positiona-15));

penup(100);
pensdown(108,(positiona-15),(positiona));

drawline(108,(positiona-2),108,(positiona-13));

penup(108);

}



// "B"
void DrawB( int arrayb ){

int positionb = (170- (17 * (arrayb-1)));

motormove(4,(positionb+2),positionb);// gap between words is 2
motormove(2,B_angle,100);
motormove(3,C_angle,130);

drawline(100,positionb,120,positionb);
drawline(120,positionb,120,positionb-13);
drawline(120,positionb-10,115,positionb-15);//  side line
drawline(115,positionb-15,105,positionb-15);
drawline(105,positionb-15,100,positionb-10);//side line
drawline(100,positionb-10,100,positionb+3);

penup(100);
pensdown(110,positionb,positionb);

drawline(110,positionb,110,positionb-16);

penup(110);

}



// "C"
void DrawC ( int arrayc ){

int positionc = (170- (17 * (arrayc-1)));

motormove(4,(positionc+2),positionc-15);// gap between words is 2
motormove(2,B_angle,100);
motormove(3,C_angle,130);

drawline(100,positionc-15,100,positionc);
drawline(100,positionc,120,positionc);
drawline(120,positionc,120,positionc-15);

penup(120);
}



//"D"
void DrawD ( int arrayd ){

  int positiond = (170- (17 * (arrayd-1)));

  motormove(4,(positiond+2),positiond);// gap between words is 2
  motormove(2,B_angle,100);
  motormove(3,C_angle,130);


  drawline(100,positiond,120,positiond);
  drawline(120,positiond,120,positiond-13);
  drawline(120,positiond-10,115,positiond-15);//  side line
  drawline(115,positiond-15,105,positiond-15);
  drawline(105,positiond-15,100,positiond-10);//side line
  drawline(100,positiond-10,100,positiond);

  penup(100);

}

void  DrawE ( int arraye) {

  int positione=(170- (17 * (arraye-1)));

  motormove(4,(positione+2),positione);
  motormove(2,B_angle,100);
  motormove(3,C_angle,130);

  drawline(100,positione,120,positione);
  drawline(120,positione,120,positione-15);

  penup(120);
  pensdown(110,positione-15,positione);

  drawline(110,positione,110,positione-15);

  penup(110);
  pensdown(100,positione-15,positione);

  drawline(100,positione,100,positione-15);

  penup(100);

}

void DrawF ( int arrayf ) {

  int positionf = (170- (17 * (arrayf-1)));

  motormove(4,(positionf+2),positionf);
  motormove(2,B_angle,100);
  motormove(3,C_angle,130);

  drawline(100,positionf,120,positionf);
  drawline(120,positionf,120,positionf-15);

  penup(120);
  pensdown(110,positionf-15,positionf);

  drawline(110,positionf,110,positionf-15);

  penup(110);

}


void DrawG( int arrayg) {

  int positiong =  (170- (17 * (arrayg-1)));

motormove(4,(positiong+2),positiong-15);
motormove(2,B_angle,120);
motormove(3,C_angle,150);

drawline(120,positiong-15,120,positiong);
drawline(120,positiong,100,positiong);
drawline(100,positiong,100,positiong-15);
drawline(100,positiong-15,110,positiong-15);
drawline(110,positiong-15,110,positiong-7);

penup(110);

}


void DrawH(int arrayH) {

  int positionh = (170- (17 * (arrayH-1)));

  motormove(4,(positionh+2),positionh);
  motormove(2,B_angle,120);
  motormove(3,C_angle,150);

  drawline(120,positionh,100,positionh);

  penup(100);
  pensdown(120,positionh,positionh-15);

 drawline(120,positionh-15,100,positionh-15);

 penup(100);
 pensdown(110,positionh-15,positionh);

 drawline(110,positionh,110,positionh-17);

 penup(110);

}



void DrawI(int arrayI) {
  int positioni = (170- (17 * (arrayI-1)));

  motormove(4,(positioni+2),positioni-8);
  motormove(2,B_angle,120);
  motormove(3,C_angle,150);


  drawline(120,positioni-8,100,positioni-8);

  penup(100);
  pensdown(120,positioni-8,positioni);

  drawline(120,positioni,120,positioni-15);

  penup(120);
  pensdown(100,positioni-15,positioni);

  drawline(100,positioni,100,positioni-15);

  penup(100);

  }


void DrawJ(int arrayJ) {
  int positionj = (170- (17 * (arrayJ-1)));

  motormove(4,(positionj+2),positionj-8);
  motormove(2,B_angle,120);
  motormove(3,C_angle,150);

  drawline(120,positionj-8,100,positionj-8);
  drawline(100,positionj-8,100,positionj);
  drawline(100,positionj,105,positionj);

  penup(100);
  pensdown(120,positionj,positionj-6);

  drawline(120,positionj-6,120,positionj-14);

  penup(120);

}


void DrawK(int arrayK) {
  int positionk =(170- (17 * (arrayK-1)));

  motormove(4,(positionk+2),positionk);
  motormove(2,B_angle,120);
  motormove(3,C_angle,150);


  drawline(120,positionk,100,positionk);

  penup(100);
  pensdown(120,positionk,positionk-15);

  drawline(120,positionk-15,110,positionk+2);
  drawline(110,positionk+2,100,positionk-15);

  penup(100);
}


void DrawL(int arrayL) {
  int positionl = (170- (17 * (arrayL-1)));

  motormove(4,(positionl+2),positionl);
  motormove(3,C_angle,150);
  motormove(2,B_angle,120);

  drawline(120,positionl,100,positionl);
  drawline(100,positionl,100,positionl-15);

  penup(100);
}


void DrawM(int arrayM) {
  int positionm = (170- (17 * (arrayM-1)));

  motormove(4,(positionm+2),positionm);
  motormove(2,B_angle,100);
  motormove(3,C_angle,130);

 drawline(100,positionm,120,positionm-5);
 drawline(120,positionm-5,100,positionm-8);
 drawline(100,positionm-8,120,positionm-10);
 drawline(120,positionm-10,100,positionm-15);

 penup(100);

}




void DrawN(int arrayN){

  int positionn = (170- (17 * (arrayN-1)));

  motormove(4,(positionn+2),positionn);
  motormove(2,B_angle,100);
  motormove(3,C_angle,130);

  drawline(100,positionn,120,positionn);
  drawline(120,positionn,100,positionn-15);
  drawline(100,positionn-15,120,positionn-15);

  penup(120);

}


void DrawO(int arrayO) {


  int positiono = (170- (17 * (arrayO-1)));

  motormove(4,(positiono+2),positiono);
  motormove(2,B_angle,100);
  motormove(3,C_angle,130);

  drawline(100,positiono,120,positiono);
  drawline(120,positiono,120,positiono-15);
  drawline(120,positiono-15,100,positiono-15);
  drawline(100,positiono-15,100,positiono+1);

  penup(100);

}


void DrawP(int arrayP) {


  int positionp = (170- (17 * (arrayP-1)));

  motormove(4,(positionp+2),positionp);
  motormove(2,B_angle,100);
  motormove(3,C_angle,130);

drawline(100,positionp,120,positionp);
drawline(120,positionp,120,positionp-15);
drawline(120,positionp-15,110,positionp-15);
drawline(110,positionp-15,110,positionp);

penup(110);

motormove(4,positionp,positionp-15);  //move to the standerd position

}


void DrawQ(int arrayQ) {

  int positionq = (170- (17 * (arrayQ-1)));

  motormove(4,(positionq+2),positionq);
  motormove(2,B_angle,100);
  motormove(3,C_angle,130);

  drawline(100,positionq,120,positionq);
  drawline(120,positionq,120,positionq-15);
  drawline(120,positionq-15,100,positionq-15);
  drawline(100,positionq-15,100,positionq+1);

  penup(100);
  pensdown(110,positionq+1,positionq-8);

  drawline(105,positionq-8,95,positionq-15);

  penup(95);

  }



void DrawR(int arrayR) {


  int positionr = (170- (17 * (arrayR-1)));

  motormove(4,(positionr+2),positionr);
  motormove(2,B_angle,100);
  motormove(3,C_angle,130);

  drawline(100,positionr,120,positionr);
  drawline(120,positionr,120,positionr-15);
  drawline(120,positionr-15,110,positionr-15);
  drawline(110,positionr-15,110,positionr+2);
  drawline(110,positionr+2,100,positionr-15);

  penup(100);
}



void DrawS(int arrayS) {

  int positions = (170- (17 * (arrayS-1)));

  motormove(4,(positions+2),positions);
  motormove(3,C_angle,130);
  motormove(2,B_angle,100);

  drawline(100,positions,100,positions-15);
  drawline(100,positions-15,110,positions-15);
  drawline(110,positions-15,110,positions);
  drawline(110,positions,120,positions);
  drawline(120,positions,120,positions-15);

  penup(120);

}



void DrawT(int arrayT) {

  int positiont = (170- (17 * (arrayT-1)));

  motormove(4,(positiont+2),positiont);
  motormove(2,B_angle,120);
  motormove(3,C_angle,150);

 drawline(120,positiont,120,positiont-15);

 penup(120);
 pensdown(120,positiont-15,positiont-4);

 drawline(120,positiont-4,100,positiont-4);

 penup(100);

 motormove(4,positiont-4,positiont-15);


}



void DrawU(int arrayU) {

  int positionu =(170- (17 * (arrayU-1)));

  motormove(4,(positionu+2),positionu);
  motormove(2,B_angle,120);
  motormove(3,C_angle,150);

  drawline(120,positionu,100,positionu);
  drawline(100,positionu,100,positionu-15);
  drawline(100,positionu-15,120,positionu-15);

  penup(120);

  }



void DrawV(int arrayV) {

  int positionv = (170- (17 * (arrayV-1)));

  motormove(4,(positionv+2),positionv);
  motormove(2,B_angle,120);
  motormove(3,C_angle,150);


  drawline(120,positionv,100,positionv-8);
  drawline(100,positionv-8,120,positionv-15);

  penup(120);

}



void DrawW(int arrayW) {

  int positionw = (170- (17 * (arrayW-1)));

  motormove(4,(positionw+2),positionw);
  motormove(2,B_angle,120);
  motormove(3,C_angle,150);

  drawline(120,positionw,100,positionw-3);
  drawline(100,positionw-3,120,positionw-8);
  drawline(120,positionw-8,100,positionw-13);
  drawline(100,positionw-13,120,positionw-15);

  penup(120);

}




void DrawX(int arrayX){
  int positionx = (170- (17 * (arrayX-1)));

  motormove(4,(positionx+2),positionx);
  motormove(2,B_angle,120);
  motormove(3,C_angle,150);

   drawline(120,positionx,100,positionx-15);

   penup(100);
   pensdown(100,positionx-15,positionx);

   drawline(100,positionx,120,positionx-15);

   penup(120);

}



void DrawY(int arrayY) {

  int positiony = (170- (17 * (arrayY-1)));

  motormove(4,(positiony+2),positiony);
  motormove(2,B_angle,120);
  motormove(3,C_angle,150);

  drawline(120,positiony,110,positiony-8);
  drawline(110,positiony-8,120,positiony-15);

  penup(120);
  pensdown(120,positiony-15,positiony-7);

  drawline(103,positiony-7,100,positiony-7);

  penup(100);

}


void DrawZ(int arrayZ) {
  int positionz = (170- (17 * (arrayZ-1)));

  motormove(4,(positionz+2),positionz);
  motormove(2,B_angle,120);
  motormove(3,C_angle,150);

  drawline(120,positionz,120,positionz-15);
  drawline(120,positionz-15,100,positionz+3);
  drawline(100,positionz+3,100,positionz-15);

  penup(100);

}


void loop()
{




  while (Serial.available() > 0)
  {
      comdata += char(Serial.read());
      delay(2);
  }


if (comdata.length() > 0)
   {

// first character
     if (-1 != val) {

       if  (comdata[0]=='m')
      {
        drawmust();
      }


       if (comdata[0]== 'A')
      {
         DrawA(1);
      }

      if (comdata[0]== 'B')
     {
      DrawB(1);
     }

     if (comdata[0]== 'C')
    {
     DrawC(1);
    }

    if (comdata[0]== 'D')
    {
    DrawD(1);
    }

    if (comdata[0]== 'E')
    {
    DrawE(1);
    }

    if (comdata[0]== 'F')
    {
    DrawF(1);
    }

    if (comdata[0]== 'G')
    {
    DrawG(1);
    }

    if (comdata[0]== 'H')
    {
    DrawH(1);
    }

    if (comdata[0]== 'I')
    {
    DrawI(1);
    }

    if (comdata[0]== 'J')
    {
    DrawJ(1);
    }

    if (comdata[0]== 'K')
    {
    DrawK(1);
    }

    if (comdata[0]== 'L')
    {
    DrawL(1);
    }

    if (comdata[0]== 'M')
    {
    DrawM(1);
    }

    if (comdata[0]== 'N')
    {
    DrawN(1);
    }

    if (comdata[0]== 'O')
    {
    DrawO(1);
    }

    if (comdata[0]== 'P')
    {
    DrawP(1);
    }

    if (comdata[0]== 'Q')
    {
    DrawQ(1);
    }

    if (comdata[0]== 'R')
    {
    DrawR(1);
    }

    if (comdata[0]== 'S')
    {
    DrawS(1);
    }

    if (comdata[0]== 'T')
    {
    DrawT(1);
    }

    if (comdata[0]== 'U')
    {
    DrawU(1);
    }

    if (comdata[0]== 'V')
    {
    DrawV(1);
    }

    if (comdata[0]== 'W')
    {
    DrawW(1);
    }

    if (comdata[0]== 'X')
    {
    DrawX(1);
    }

    if (comdata[0]== 'Y')
    {
    DrawY(1);
    }

    if (comdata[0]== 'Z')
    {
    DrawZ(1);
    }




// second character
     if (comdata[1]== 'A')
    {
       DrawA(2);
    }

    if (comdata[1]== 'B')
   {
    DrawB(2);
   }

   if (comdata[1]== 'C')
  {
   DrawC(2);
  }

  if (comdata[1]== 'D')
  {
  DrawD(2);
  }

  if (comdata[1]== 'E')
  {
  DrawE(2);
  }

  if (comdata[1]== 'F')
  {
  DrawF(2);
  }

  if (comdata[1]== 'G')
  {
  DrawG(2);
  }

  if (comdata[1]== 'H')
  {
  DrawH(2);
  }

  if (comdata[1]== 'I')
  {
  DrawI(2);
  }

  if (comdata[1]== 'J')
  {
  DrawJ(2);
  }

  if (comdata[1]== 'K')
  {
  DrawK(2);
  }

  if (comdata[1]== 'L')
  {
  DrawL(2);
  }

  if (comdata[1]== 'M')
  {
  DrawM(2);
  }

  if (comdata[1]== 'N')
  {
  DrawN(2);
  }

  if (comdata[1]== 'O')
  {
  DrawO(2);
  }

  if (comdata[1]== 'P')
  {
  DrawP(2);
  }

  if (comdata[1]== 'Q')
  {
  DrawQ(2);
  }

  if (comdata[1]== 'R')
  {
  DrawR(2);
  }

  if (comdata[1]== 'S')
  {
  DrawS(2);
  }

  if (comdata[1]== 'T')
  {
  DrawT(2);
  }

  if (comdata[1]== 'U')
  {
  DrawU(2);
  }

  if (comdata[1]== 'V')
  {
  DrawV(2);
  }

  if (comdata[1]== 'W')
  {
  DrawW(2);
  }

  if (comdata[1]== 'X')
  {
  DrawX(2);
  }

  if (comdata[1]== 'Y')
  {
  DrawY(2);
  }

  if (comdata[1]== 'Z')
  {
  DrawZ(2);
  }


// 3rd character

  if (comdata[2]== 'A')
 {
    DrawA(3);
 }

 if (comdata[2]== 'B')
{
 DrawB(3);
}

if (comdata[2]== 'C')
{
DrawC(3);
}

if (comdata[2]== 'D')
{
DrawD(3);
}

if (comdata[2]== 'E')
{
DrawE(3);
}

if (comdata[2]== 'F')
{
DrawF(3);
}

if (comdata[2]== 'G')
{
DrawG(3);
}

if (comdata[2]== 'H')
{
DrawH(3);
}

if (comdata[2]== 'I')
{
DrawI(3);
}

if (comdata[2]== 'J')
{
DrawJ(3);
}

if (comdata[2]== 'K')
{
DrawK(3);
}

if (comdata[2]== 'L')
{
DrawL(3);
}

if (comdata[2]== 'M')
{
DrawM(3);
}

if (comdata[2]== 'N')
{
DrawN(3);
}

if (comdata[2]== 'O')
{
DrawO(3);
}

if (comdata[2]== 'P')
{
DrawP(3);
}

if (comdata[2]== 'Q')
{
DrawQ(3);
}

if (comdata[2]== 'R')
{
DrawR(3);
}

if (comdata[2]== 'S')
{
DrawS(3);
}

if (comdata[2]== 'T')
{
DrawT(3);
}

if (comdata[2]== 'U')
{
DrawU(3);
}

if (comdata[2]== 'V')
{
DrawV(3);
}

if (comdata[2]== 'W')
{
DrawW(3);
}

if (comdata[2]== 'X')
{
DrawX(3);
}

if (comdata[2]== 'Y')
{
DrawY(3);
}

if (comdata[2]== 'Z')
{
DrawZ(3);
}


//4th character

  if (comdata[3]== 'A')
 {
    DrawA(4);
 }

 if (comdata[3]== 'B')
{
 DrawB(4);
}

if (comdata[3]== 'C')
{
DrawC(4);
}

if (comdata[3]== 'D')
{
DrawD(4);
}

if (comdata[3]== 'E')
{
DrawE(4);
}

if (comdata[3]== 'F')
{
DrawF(4);
}

if (comdata[3]== 'G')
{
DrawG(4);
}

if (comdata[3]== 'H')
{
DrawH(4);
}

if (comdata[3]== 'I')
{
DrawI(4);
}

if (comdata[3]== 'J')
{
DrawJ(4);
}

if (comdata[3]== 'K')
{
DrawK(4);
}

if (comdata[3]== 'L')
{
DrawL(4);
}

if (comdata[3]== 'M')
{
DrawM(4);
}

if (comdata[3]== 'N')
{
DrawN(4);
}

if (comdata[3]== 'O')
{
DrawO(4);
}

if (comdata[3]== 'P')
{
DrawP(4);
}

if (comdata[3]== 'Q')
{
DrawQ(4);
}

if (comdata[3]== 'R')
{
DrawR(4);
}

if (comdata[3]== 'S')
{
DrawS(4);
}

if (comdata[3]== 'T')
{
DrawT(4);
}

if (comdata[3]== 'U')
{
DrawU(4);
}

if (comdata[3]== 'V')
{
DrawV(4);
}

if (comdata[3]== 'W')
{
DrawW(4);
}

if (comdata[3]== 'X')
{
DrawX(4);
}

if (comdata[3]== 'Y')
{
DrawY(4);
}

if (comdata[3]== 'Z')
{
DrawZ(4);
}
// 5 character


if (comdata[4]== 'A')
{
  DrawA(5);
}

if (comdata[4]== 'B')
{
DrawB(5);
}

if (comdata[4]== 'C')
{
DrawC(5);
}

if (comdata[4]== 'D')
{
DrawD(5);
}

if (comdata[4]== 'E')
{
DrawE(5);
}

if (comdata[4]== 'F')
{
DrawF(5);
}

if (comdata[4]== 'G')
{
DrawG(5);
}

if (comdata[4]== 'H')
{
DrawH(5);
}

if (comdata[4]== 'I')
{
DrawI(5);
}

if (comdata[4]== 'J')
{
DrawJ(5);
}

if (comdata[4]== 'K')
{
DrawK(5);
}

if (comdata[4]== 'L')
{
DrawL(5);
}

if (comdata[4]== 'M')
{
DrawM(5);
}

if (comdata[4]== 'N')
{
DrawN(5);
}

if (comdata[4]== 'O')
{
DrawO(5);
}

if (comdata[4]== 'P')
{
DrawP(5);
}

if (comdata[4]== 'Q')
{
DrawQ(5);
}

if (comdata[4]== 'R')
{
DrawR(5);
}

if (comdata[4]== 'S')
{
DrawS(5);
}

if (comdata[4]== 'T')
{
DrawT(5);
}

if (comdata[4]== 'U')
{
DrawU(5);
}

if (comdata[4]== 'V')
{
DrawV(5);
}

if (comdata[4]== 'W')
{
DrawW(5);
}

if (comdata[4]== 'X')
{
DrawX(5);
}

if (comdata[4]== 'Y')
{
DrawY(5);
}

if (comdata[4]== 'Z')
{
DrawZ(5);
}



// 6 character

if (comdata[5]== 'A')
{
  DrawA(6);
}

if (comdata[5]== 'B')
{
DrawB(6);
}

if (comdata[5]== 'C')
{
DrawC(6);
}

if (comdata[5]== 'D')
{
DrawD(6);
}

if (comdata[5]== 'E')
{
DrawE(6);
}

if (comdata[5]== 'F')
{
DrawF(6);
}

if (comdata[5]== 'G')
{
DrawG(6);
}

if (comdata[5]== 'H')
{
DrawH(6);
}

if (comdata[5]== 'I')
{
DrawI(6);
}

if (comdata[5]== 'J')
{
DrawJ(6);
}

if (comdata[5]== 'K')
{
DrawK(6);
}

if (comdata[5]== 'L')
{
DrawL(6);
}

if (comdata[5]== 'M')
{
DrawM(6);
}

if (comdata[5]== 'N')
{
DrawN(6);
}

if (comdata[5]== 'O')
{
DrawO(6);
}

if (comdata[5]== 'P')
{
DrawP(6);
}

if (comdata[5]== 'Q')
{
DrawQ(6);
}

if (comdata[5]== 'R')
{
DrawR(6);
}

if (comdata[5]== 'S')
{
DrawS(6);
}

if (comdata[5]== 'T')
{
DrawT(6);
}

if (comdata[5]== 'U')
{
DrawU(6);
}

if (comdata[5]== 'V')
{
DrawV(6);
}

if (comdata[5]== 'W')
{
DrawW(6);
}

if (comdata[5]== 'X')
{
DrawX(6);
}

if (comdata[5]== 'Y')
{
DrawY(6);
}

if (comdata[5]== 'Z')
{
DrawZ(6);
}



// 7 character

if (comdata[6]== 'A')
{
  DrawA(7);
}

if (comdata[6]== 'B')
{
DrawB(7);
}

if (comdata[6]== 'C')
{
DrawC(7);
}

if (comdata[6]== 'D')
{
DrawD(7);
}

if (comdata[6]== 'E')
{
DrawE(7);
}

if (comdata[6]== 'F')
{
DrawF(7);
}

if (comdata[6]== 'G')
{
DrawG(7);
}

if (comdata[6]== 'H')
{
DrawH(7);
}

if (comdata[6]== 'I')
{
DrawI(7);
}

if (comdata[6]== 'J')
{
DrawJ(7);
}

if (comdata[6]== 'K')
{
DrawK(7);
}

if (comdata[6]== 'L')
{
DrawL(7);
}

if (comdata[6]== 'M')
{
DrawM(7);
}

if (comdata[6]== 'N')
{
DrawN(7);
}

if (comdata[6]== 'O')
{
DrawO(7);
}

if (comdata[6]== 'P')
{
DrawP(7);
}

if (comdata[6]== 'Q')
{
DrawQ(7);
}

if (comdata[6]== 'R')
{
DrawR(7);
}

if (comdata[6]== 'S')
{
DrawS(7);
}

if (comdata[6]== 'T')
{
DrawT(7);
}

if (comdata[6]== 'U')
{
DrawU(7);
}

if (comdata[6]== 'V')
{
DrawV(7);
}

if (comdata[6]== 'W')
{
DrawW(7);
}

if (comdata[6]== 'X')
{
DrawX(7);
}

if (comdata[6]== 'Y')
{
DrawY(7);
}

if (comdata[6]== 'Z')
{
DrawZ(7);
}


// 8 character

if (comdata[7]== 'A')
{
  DrawA(8);
}

if (comdata[7]== 'B')
{
DrawB(8);
}

if (comdata[7]== 'C')
{
DrawC(8);
}

if (comdata[7]== 'D')
{
DrawD(8);
}

if (comdata[7]== 'E')
{
DrawE(8);
}

if (comdata[7]== 'F')
{
DrawF(8);
}

if (comdata[7]== 'G')
{
DrawG(8);
}

if (comdata[7]== 'H')
{
DrawH(8);
}

if (comdata[7]== 'I')
{
DrawI(8);
}

if (comdata[7]== 'J')
{
DrawJ(8);
}

if (comdata[7]== 'K')
{
DrawK(8);
}

if (comdata[7]== 'L')
{
DrawL(8);
}

if (comdata[7]== 'M')
{
DrawM(8);
}

if (comdata[7]== 'N')
{
DrawN(8);
}

if (comdata[7]== 'O')
{
DrawO(8);
}

if (comdata[7]== 'P')
{
DrawP(8);
}

if (comdata[7]== 'Q')
{
DrawQ(8);
}

if (comdata[7]== 'R')
{
DrawR(8);
}

if (comdata[7]== 'S')
{
DrawS(8);
}

if (comdata[7]== 'T')
{
DrawT(8);
}

if (comdata[7]== 'U')
{
DrawU(8);
}

if (comdata[7]== 'V')
{
DrawV(8);
}

if (comdata[7]== 'W')
{
DrawW(8);
}

if (comdata[7]== 'X')
{
DrawX(8);
}

if (comdata[7]== 'Y')
{
DrawY(8);
}

if (comdata[7]== 'Z')
{
DrawZ(8);
}



      comdata = "";
                    }
    }
}
