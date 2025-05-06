const int LEFT_L_IS = 4;
const int LEFT_L_EN = 2;
const int LEFT_L_PWM = 5;
const int LEFT_R_IS = 4;
const int LEFT_R_EN = 2;
const int LEFT_R_PWM = 3;
const int RIGHT_L_IS = 13;
const int RIGHT_L_EN = 12;
const int RIGHT_L_PWM = 6;
const int RIGHT_R_IS = 13;
const int RIGHT_R_EN = 12;
const int RIGHT_R_PWM = 10;
#define trigPin 7
#define echoPin 8
 long t2;
  long t1;
  float pulse_width;
  int cm;
  bool ltrt=true;
void setup() {
  // put your setup code here, to run once:
  pinMode(LEFT_L_IS, OUTPUT);
  digitalWrite(LEFT_L_IS, LOW);
  pinMode(LEFT_L_EN, OUTPUT);
  digitalWrite(LEFT_L_EN, HIGH);
  pinMode(LEFT_L_PWM, OUTPUT);
  pinMode(LEFT_R_IS, OUTPUT);
  digitalWrite(LEFT_R_IS, LOW);
  pinMode(LEFT_R_EN, OUTPUT);
  digitalWrite(LEFT_R_EN, HIGH);
  pinMode(LEFT_R_PWM, OUTPUT);
  pinMode(RIGHT_L_IS, OUTPUT);
  digitalWrite(RIGHT_L_IS, LOW);
  pinMode(RIGHT_L_EN, OUTPUT);
  digitalWrite(RIGHT_L_EN, HIGH);
  pinMode(RIGHT_L_PWM, OUTPUT);
  pinMode(RIGHT_R_IS, OUTPUT);
  digitalWrite(RIGHT_R_IS, LOW);
  pinMode(RIGHT_R_EN, OUTPUT);
  digitalWrite(RIGHT_R_EN, HIGH);
  pinMode(RIGHT_R_PWM, OUTPUT);
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);   
  pinMode(echoPin, INPUT);
  digitalWrite(trigPin,LOW);

}
void forward(int velocity)
{
  analogWrite(LEFT_L_PWM, velocity);
  analogWrite(LEFT_R_PWM, 0);
  analogWrite(RIGHT_L_PWM, velocity);
  analogWrite(RIGHT_R_PWM, 0);
}
void sharp_right(int velocity)
{
  analogWrite(LEFT_L_PWM, velocity);
  analogWrite(LEFT_R_PWM, 0);
  analogWrite(RIGHT_L_PWM, 0);
  analogWrite(RIGHT_R_PWM, int(velocity));
}
void sharp_left(int velocity)
{
  analogWrite(LEFT_L_PWM, 0);
  analogWrite(LEFT_R_PWM, velocity);
  analogWrite(RIGHT_L_PWM, velocity);
  analogWrite(RIGHT_R_PWM, 0);
}
void right(int velocity)
{
  analogWrite(LEFT_L_PWM, velocity);
  analogWrite(LEFT_R_PWM, 0);
  analogWrite(RIGHT_L_PWM, 0);
  analogWrite(RIGHT_R_PWM, 0);
}
void left(int velocity)
{
  analogWrite(LEFT_L_PWM, 0);
  analogWrite(LEFT_R_PWM, 0);
  analogWrite(RIGHT_L_PWM, velocity);
  analogWrite(RIGHT_R_PWM, 0);
}
void back(int velocity)
{
  analogWrite(LEFT_L_PWM, 0);
  analogWrite(LEFT_R_PWM, velocity);
  analogWrite(RIGHT_L_PWM, 0);
  analogWrite(RIGHT_R_PWM, velocity);
}
void brake(int velocity){
  analogWrite(LEFT_L_PWM, 0);
  analogWrite(LEFT_R_PWM, 0);
  analogWrite(RIGHT_L_PWM, 0);
  analogWrite(RIGHT_R_PWM, 0);
}
void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  while (digitalRead(echoPin)==0);
  t1= micros();
  while (digitalRead(echoPin)==1);
  t2=micros();
  pulse_width= t2-t1;
  cm= pulse_width/58.0;
  int s = 250;
  int a = 200;
    if (cm > 50){
   forward(s);
   delay(1000); 
   Serial.print(cm);
  }
  else if (cm >25&& cm<50){
   //brake(s);
   //delay(1000);
   if (ltrt){
   sharp_left(a);
   ltrt = !ltrt;
   }
   else
   {
    sharp_right(s);
    ltrt = !ltrt;
   }
   delay(1000);
   Serial.print(cm);
  }
  else if(cm < 25) {
    brake(s);
    delay(1000);
    Serial.print(cm);
  }
  

}
