//Line follower PID code
//Written by Kent
//10/12/2022

//define sensor pins
int IR_left = 5;
int IR_middle = 4;
int IR_right= 3;
int IR_back_left = 12;
int IR_back_right = 2;

//initiate sensor values
int sensor[5]={0,0,0,0,0};

//define motor pins
int rm_front = 8;
int rm_back = 7;
int rm_enable = 6;
int lm_front = 9;
int lm_back = 10;
int lm_enable = 11;

//Initial speed of motor
int initial_motor_speed = 120;
int left_count=0;
int right_count=0;
int cross_count=0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  //sensor input
  pinMode(IR_left,INPUT);
  pinMode(IR_middle,INPUT);
  pinMode(IR_right,INPUT);
  pinMode(IR_back_left,INPUT);
  pinMode(IR_back_right,INPUT);

// right wheel
  pinMode(rm_front, OUTPUT);
  pinMode(rm_back, OUTPUT);
  pinMode(rm_enable, OUTPUT);

// left wheel
  pinMode(lm_front, OUTPUT);
  pinMode(lm_back, OUTPUT);
  pinMode(lm_enable, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
 read_sensor_values(); //get sensor value
 //Serial.println(sensor[4]);

  if(sensor[0]==0 && sensor[1]==1 && sensor[2]==0){
    analogWrite(lm_enable,initial_motor_speed);
    analogWrite(rm_enable,initial_motor_speed);
    forward();
    delay(20);//straight
  }
  else if(sensor[0]==1 && sensor[1]==1 && sensor[2]==0){
    analogWrite(lm_enable,initial_motor_speed*2/4);
    analogWrite(rm_enable,initial_motor_speed);
    forward();
    delay(20);//tilt to right == turn left
    // if (cross_count>=4){
    //   left_count+=1;
    // }
  }
  else if(sensor[0]==1 && sensor[1]==0 && sensor[2]==0){
    analogWrite(lm_enable,initial_motor_speed*1/4);
    analogWrite(rm_enable,initial_motor_speed);
    forward();
    delay(20);//more tilt to right == turn left with speed
    if (cross_count>=5){
      left_count+=1;
    }
  }
  else if(sensor[0]==0 && sensor[1]==1 && sensor[2]==1){
    analogWrite(lm_enable,initial_motor_speed);
    analogWrite(rm_enable,initial_motor_speed*2/4);
    forward();
    delay(20);//tilt to left == turn right
    // if (cross_count>=4){
    //   right_count+=1;
    // }
  }
  else if(sensor[0]==0 && sensor[1]==0 && sensor[2]==1){
    analogWrite(lm_enable,initial_motor_speed);
    analogWrite(rm_enable,initial_motor_speed*1/4);
    forward();
    delay(20);//more tilt to left == turn right
    if (cross_count>=5){
      right_count+=1;
    }
  }
  else if(sensor[0]==1 && sensor[1]==1 && sensor[2]==1 && sensor[3]==0 && sensor[4]==0){
    analogWrite(lm_enable,initial_motor_speed);
    analogWrite(rm_enable,initial_motor_speed);
    forward();
    delay(20);//pass cross line == just go straight
    cross_count+=1;
  }
  else if(sensor[0]==0 && sensor[1]==0 && sensor[2]==0 && left_count>right_count){
    analogWrite(lm_enable,initial_motor_speed); 
    analogWrite(rm_enable,initial_motor_speed);
    sharpturnleft();
    delay(20);
  }
  else if(sensor[0]==0 && sensor[1]==0 && sensor[2]==0 && right_count>left_count){
    analogWrite(lm_enable,initial_motor_speed); 
    analogWrite(rm_enable,initial_motor_speed);
    sharpturnright();
    delay(20);   
  }
   else if(sensor[0]==1 && sensor[1]==1 && sensor[2]==1 && sensor[3]==1 || sensor[4]==1){
    stop(); 

  }
 }
void read_sensor_values()
{
  sensor[0]=digitalRead(IR_left);
  sensor[1]=digitalRead(IR_middle);
  sensor[2]=digitalRead(IR_right);
  sensor[3]=digitalRead(IR_back_left);
  sensor[4]=digitalRead(IR_back_right);
}

void forward (){
  digitalWrite(lm_front, HIGH);
  digitalWrite(lm_back, LOW);
  digitalWrite(rm_front, HIGH);
  digitalWrite(rm_back, LOW);
}
void turnleft(){
  digitalWrite(lm_front, LOW);
  digitalWrite(lm_back, LOW);
  digitalWrite(rm_front, HIGH);
  digitalWrite(rm_back, LOW);
}
void turnright(){
  digitalWrite(lm_front, HIGH);
  digitalWrite(lm_back, LOW);
  digitalWrite(rm_front, LOW);
  digitalWrite(rm_back, LOW);
}
void sharpturnleft (){
  digitalWrite(lm_front, LOW);
  digitalWrite(lm_back, HIGH);
  digitalWrite(rm_front, HIGH);
  digitalWrite(rm_back, LOW);
}
void sharpturnright(){
  digitalWrite(lm_front, HIGH);
  digitalWrite(lm_back, LOW);
  digitalWrite(rm_front, LOW);
  digitalWrite(rm_back, HIGH);
}
void reverse(){
  digitalWrite(lm_front, LOW);
  digitalWrite(lm_back, HIGH);
  digitalWrite(rm_front, LOW);
  digitalWrite(rm_back, HIGH);  
}
void stop(){
  digitalWrite(lm_front, LOW);
  digitalWrite(lm_back, LOW);
  digitalWrite(rm_front, LOW);
  digitalWrite(rm_back, LOW);
}
