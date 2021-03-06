//Down Sensors
#define D1 33
#define D2 35 //52
#define D3 37 //50
#define D4 39 //48
#define D5 41 //46

#define D6 32
#define D7 34 //52
#define D8 36 //50
#define D9 38 //48
#define D10 40 //46
//DS1 facing problem

//DS2 ==D5
//DS3 == D4
//DS4==D3
//DS5==D2

//Side Sensors
#define S1 22
#define S2 24
#define S3 26
#define S4 28
#define S5 30
#define S6 23
#define S7 25
#define S8 27
#define S9 29
#define S10 31
//ds1== error
//ds2 = s2
//ds3 = s3
//ds4 = s4
//ds5 = s5

// direction Pins
#define dirFL 6 //FR=RR in manualBot config // change RR to FR in autoBot
#define dirFR 11 //FL=FR in manualBot config
#define dirRR 5//RR=RL in manualBot config
#define dirRL 8 //RL=FL in manualBot config
// pwm Pins
#define pwmFL 7
#define pwmFR 10
#define pwmRR 4
#define pwmRL 9

#define GREEN 1
#define WHITE 0
#define dw(a,b) digitalWrite(a,b)
#define aw(a,b) analogWrite(a,b)

//color sensor pins
#define COLOR0 4
#define COLOR1 5
#define COLOR2 6
#define COLOR3 7
#define sensorOut 8
#define TZ1COLOR 'w'  //for white
#define TZ2COLOR 'b'  //for black
#define TZ3COLOR 'g'  // for golden
#define ColorTrig 12
#define ColorEcho 11

int speedValue = 90;
int slowspeed = 90;


void diagonal()
{
  aw(pwmFR, speedValue);
  aw(pwmFL, 0);
  aw(pwmRL,  0);
  aw(pwmRR,  speedValue);
  Serial.println("diagonal");
  dw(dirFR, 1);
  dw(dirRR, 0);


}
void forward() {
  aw(pwmFR, 110);
  aw(pwmFL, speedValue);
  aw(pwmRR, speedValue);
  aw(pwmRL, speedValue);
  Serial.println("forward");

  dw(dirFR, 1);
  dw(dirFL, 0);
  dw(dirRL, 0);
  dw(dirRR, 1);
}
void backward() {
  aw(pwmFR, 110);
  aw(pwmFL, speedValue);
  aw(pwmRR, speedValue);
  aw(pwmRL, speedValue);
  Serial.println("backward");
  dw(dirFR, 0);
  dw(dirFL, 1);
  dw(dirRL, 1);
  dw(dirRR, 0);
}
void left() {
  aw(pwmFR, 110);
  aw(pwmFL, speedValue);
  aw(pwmRR, speedValue);
  aw(pwmRL, speedValue);
  Serial.println("left");
  dw(dirFR, 0);
  dw(dirFL, 0);
  dw(dirRL, 0);
  dw(dirRR, 0);
}
void right() {
  aw(pwmFR, 110);
  aw(pwmFL, speedValue);
  aw(pwmRR, speedValue);
  aw(pwmRL, speedValue);
  Serial.println("right");
  dw(dirFR, 1);
  dw(dirFL, 1);
  dw(dirRL, 1);
  dw(dirRR, 1);
}
void stopall() {
  aw(pwmFR, 0);
  aw(pwmFL, 0);
  aw(pwmRR, 0);
  aw(pwmRL, 0);
  Serial.println("stop");
}

void tz1() {
  bool con = 0, prev = 0;
  int count = 0;
  //we have reached cross above tz1
  Serial.println("------------------Entered TZ1---------------- ");
  //now go to throwing position;
  while (1) {
    prev  = con;
    con = digitalRead(S1) == WHITE && digitalRead(S2) == WHITE && digitalRead(S9) == WHITE && digitalRead(S10) == WHITE;
    if ((prev) != con  && con == HIGH) {
      count++;
    }
    if (count == 2) {
      break;
    }

    if  (digitalRead(S4) == WHITE || digitalRead(S5) == WHITE || digitalRead(S6) == WHITE || digitalRead(S7) == WHITE )
    {
      left();
    }
    else if ((digitalRead(S1) == WHITE || digitalRead(S2) == WHITE || digitalRead(S3) == WHITE) && digitalRead(S10) == GREEN)
    {
      forward();
    }

    else if (digitalRead(S1) == GREEN && (digitalRead(S8) == WHITE || digitalRead(S9) == WHITE || digitalRead(S10) == WHITE  ))
    {
      backward();
    }
  }
  //throwtz1()
  //reached thowing position now go back
  while (1) {
    prev  = con;
    con = digitalRead(S1) == WHITE && digitalRead(S2) == WHITE && digitalRead(S9) == WHITE && digitalRead(S10) == WHITE;
    if (prev != con  && con == HIGH) {
      count++;
    }
    if (count >= 3 && (digitalRead(D4) == WHITE && digitalRead(D5) == WHITE) || (digitalRead(D6) == WHITE && digitalRead(D7) == WHITE)) {
      break;
    }

    if  (digitalRead(S4) == WHITE || digitalRead(S5) == WHITE || digitalRead(S6) == WHITE || digitalRead(S7) == WHITE )
    {
      right();
    }
    else if ((digitalRead(S1) == WHITE || digitalRead(S2) == WHITE || digitalRead(S3) == WHITE) && digitalRead(S10) == GREEN)
    {
      forward();
    }

    else if (digitalRead(S1) == GREEN && (digitalRead(S8) == WHITE || digitalRead(S9) == WHITE || digitalRead(S10) == WHITE  ))
    {
      backward();
    }
  }
  stopall();
}


void tz2()
{
  tz1();
}
void throwShuttle() {
  Serial.write(3);
  aw(34, 230); //turn on motor
}
char detectColor() {
  //red filter
  digitalWrite(COLOR2,LOW);
  digitalWrite(COLOR3,LOW);
 int frequency = pulseIn(sensorOut, LOW);
  delay(100);
//  // Setting Green filtered photodiodes to be read
//  digitalWrite(COLOR2,HIGH);
//  digitalWrite(COLOR3,HIGH);
//  frequency = pulseIn(sensorOut, LOW);
//  // Setting Blue filtered photodiodes to be read
//  digitalWrite(COLOR2,LOW);
//  digitalWrite(COLOR3,HIGH);
//  // Reading the output frequency
//  frequency = pulseIn(sensorOut, LOW);

  if (frequency<150){
    return 'w';
  }
  else if (frequency>400){
    return 'b';
    }
  else if{
    return 'g';
  }
}
bool distanceFromColor(){
  int threshold = 500; //SET THIS VALUE
  digitalWrite(ColorTrig,LOW);
  delayMicroseconds(2);
  digitalWrite(ColorTrig,HIGH);
  delayMicroseconds(10);
  digitalWrite(ColorTrig,LOW);
  duration= pulseIn(ColorEcho,HIGH);
  if (duration < threshold)
  return false;
  else
  {
    return true;
  }
  }
void goToTz2(){
    //TZ1 ended GO TOWARDS TZ2
  while (1) {
    //      TODO: check for all 5 down sensors GREEN condition in while loop
    //     */
    if (digitalRead(D4) == WHITE && digitalRead(D5) == WHITE && digitalRead(D1) == WHITE &&  digitalRead(D2) == WHITE && digitalRead(D3)) {
      continue;
    }

    {
      if (digitalRead(D4) == WHITE || digitalRead(D5) == WHITE || digitalRead(D6) == WHITE ||  digitalRead(D7) == WHITE)

      {
        backward();
      }
      if (digitalRead(S2) == WHITE || digitalRead(S3) == WHITE || digitalRead(S4) == WHITE || digitalRead(S5) == WHITE) {
        break;
      }
      else if ((digitalRead(D1) == GREEN) && (digitalRead(D8) == WHITE || digitalRead(D9) == WHITE || digitalRead(D10) == WHITE))
      {
        right();
      }

      else if ((digitalRead(D1) == WHITE || digitalRead(D2) == WHITE || digitalRead(D3) == WHITE) && digitalRead(D10) == GREEN)
      {
        left();
      }
      else if ((digitalRead(S1) == WHITE && digitalRead(S2) == WHITE && digitalRead(S3) == WHITE && digitalRead(S4) == WHITE && digitalRead(S5) == WHITE) ||
               (digitalRead(D1) == GREEN && digitalRead(D2) == GREEN && digitalRead(D3) == GREEN && digitalRead(D4) == GREEN && digitalRead(D5) == GREEN) &&
               (digitalRead(D6) == GREEN && digitalRead(D7) == GREEN && digitalRead(D8) == GREEN && digitalRead(D9) == GREEN && digitalRead(D10) == GREEN))
      {
        //stopall();
      }
      else {
        backward();
        Serial.println("--------------------");

      }
    }
  }
}

void setup() {
  pinMode(D1, INPUT);
  pinMode(D2, INPUT);
  pinMode(D3, INPUT);
  pinMode(D4, INPUT);
  pinMode(D5, INPUT);
  pinMode(D6, INPUT);
  pinMode(D7, INPUT);
  pinMode(D8, INPUT);
  pinMode(D9, INPUT);
  pinMode(D10, INPUT);


  pinMode(S1, INPUT);
  pinMode(S2, INPUT);
  pinMode(S3, INPUT);
  pinMode(S4, INPUT);
  pinMode(S5, INPUT);

  pinMode(S6, INPUT);
  pinMode(S7, INPUT);
  pinMode(S8, INPUT);
  pinMode(S9, INPUT);
  pinMode(S10, INPUT);

  pinMode(pwmFR, OUTPUT);
  pinMode(pwmRR, OUTPUT);
  pinMode(pwmFL, OUTPUT);
  pinMode(pwmRL, OUTPUT);
  pinMode(dirFR, OUTPUT);
  pinMode(dirFL, OUTPUT);
  pinMode(dirRR, OUTPUT);
  pinMode(dirRL, OUTPUT);
  pinMode(50, HIGH);

//Color sensor pins
  pinMode(COLOR0, OUTPUT);
  pinMode(COLOR1, OUTPUT);
  pinMode(COLOR2, OUTPUT);
  pinMode(COLOR3, OUTPUT);
  pinMode(sensorOut, INPUT);
  //ultrasonic color
   pinMode(ColorTrig, OUTPUT);
  pinMode(ColorEcho, INPUT);

  // Setting frequency-scaling to 20%
  digitalWrite(COLOR0, HIGH);
  digitalWrite(COLOR1, LOW);
  Serial.begin(9600);

  // while(digitalRead(S1) == WHITE && digitalRead(S2) == WHITE && digitalRead(S3) == WHITE && digitalRead(S4) == WHITE && digitalRead(S5) == WHITE){}

  //  //go diagonal begin
  //    while (1) //everything off then move diagnally full speed
  //  {
  //    diagonal();
  //
  //Serial.print(digitalRead(S1));
  //  Serial.print(digitalRead(S2));
  //  Serial.print(digitalRead(S3));
  //  Serial.print(digitalRead(S4));
  //  Serial.print(digitalRead(S5));
  //  Serial.print(digitalRead(S6));
  //  Serial.print(digitalRead(S7));
  //  Serial.print(digitalRead(S8));
  //  Serial.print(digitalRead(S9));
  //  Serial.println(digitalRead(S10));
  //
  //
  //        Serial.print("      DOwn  ");
  //  Serial.print(digitalRead(D1));
  //  Serial.print(digitalRead(D2));
  //  Serial.print(digitalRead(D3));
  //  Serial.print(digitalRead(D4));
  //  Serial.print(digitalRead(D5));
  //  Serial.print(digitalRead(D6));
  //  Serial.print(digitalRead(D7));
  //  Serial.print(digitalRead(D8));
  //  Serial.print(digitalRead(D9));
  //  Serial.println(digitalRead(D10));
  //
  //
  //
  //    if((digitalRead(D1) == WHITE )&&(digitalRead(D2) == WHITE ))//&& digitalRead(S3) == WHITE)/*digitalRead(S3) == GREEN  || digitalRead(S5) == GREEN )*/
  //    {
  //      Serial.println("should go strainght now");
  //      break;
  //    }
  //  }
  //Line FOllower to GO to tz1
  while (1)
    //      TODO: check for all 5 down sensors GREEN condition in while loop
    //     */

  {

    if  (digitalRead(S6) == WHITE && digitalRead(S7) == WHITE && digitalRead(S8) == WHITE &&  digitalRead(S9) == WHITE && digitalRead(S10) == WHITE) {
      continue;
    }



    if (digitalRead(D4) == WHITE || digitalRead(D5) == WHITE || digitalRead(D6) == WHITE ||  digitalRead(D7) == WHITE)

    {
      backward();
    }
    else if ((digitalRead(D1) == GREEN) && (digitalRead(D8) == WHITE || digitalRead(D9) == WHITE || digitalRead(D10) == WHITE))
    {
      right();
    }

    else if ((digitalRead(D1) == WHITE || digitalRead(D2) == WHITE || digitalRead(D3) == WHITE) && digitalRead(D10) == GREEN)
    {
      left();
    }
    else if ((digitalRead(S1) == WHITE && digitalRead(S2) == WHITE && digitalRead(S3) == WHITE && digitalRead(S4) == WHITE && digitalRead(S5) == WHITE) ||
             (digitalRead(D1) == GREEN && digitalRead(D2) == GREEN && digitalRead(D3) == GREEN && digitalRead(D4) == GREEN && digitalRead(D5) == GREEN) &&
             (digitalRead(D6) == GREEN && digitalRead(D7) == GREEN && digitalRead(D8) == GREEN && digitalRead(D9) == GREEN && digitalRead(D10) == GREEN))
    {
      //stopall();
    }
    //    else{
    //      backward();
    //      Serial.println("--------------------");
    //
    //    }
    if (digitalRead(S2) == WHITE || (digitalRead(S3) == WHITE && digitalRead(S4) == WHITE) || (digitalRead(S10) == WHITE && digitalRead(S9) == WHITE))
    {
      break;
    }
  }
  stopall();
  // TODO: check if it is available
  while(distanceFromColor()){}
   if (detectColor() == TZ1COLOR) {
    tz1();
   }
   
  Serial.println("-------------TZ1 ended-----------------");
  
  
  goToTz2();
}

void loop() {
  Serial.print("      IN LOOOP END OF CODE  ");

  // now follow backward line until any one of side sensors is GREEN

  //tz1;



  //  \ 
  //  //going towards tz2
  //  //now follow backward line until any one of side sensors is GREEN
  //  while (digitalRead(S1) == WHITE && digitalRead(S2) == WHITE && digitalRead(S3) == WHITE && digitalRead(S4) == WHITE && digitalRead(S5) == WHITE)
  //    /*
  //       TODO: check for all 5 down sensors GREEN condition in while loop
  //     */
  //  {
  //    if ((digitalRead(D1) == WHITE && digitalRead(D2) == GREEN && digitalRead(D3) == GREEN && digitalRead(D4) == GREEN && digitalRead(D5) == WHITE) ||
  //      (digitalRead(D1) == WHITE && digitalRead(D2) == GREEN && digitalRead(D3) == GREEN && digitalRead(D4) == WHITE && digitalRead(D5) == WHITE) ||
  //      (digitalRead(D1) == WHITE && digitalRead(D2) == WHITE && digitalRead(D3) == GREEN && digitalRead(D4) == GREEN && digitalRead(D5) == WHITE))
  //    {
  //      backward();
  //    }
  //    else if ((digitalRead(D1) == GREEN || digitalRead(D2) == GREEN) && digitalRead(D5) == WHITE)
  //    {
  //      left();
  //    }
  //
  //    else if (digitalRead(D1) == WHITE && (digitalRead(D4) == GREEN || digitalRead(D5) == GREEN))
  //    {
  //      right();
  //    }
  //  }

  //tz2();
}





