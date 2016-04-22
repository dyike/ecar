const byte TrigPin = A2;   //超声波Sig的引脚定义
const byte EchoPin = A3;    //超声波Nc的引脚定义
const int dangerThresh = 100;
float distance;

const byte ENA = 5;   //电机A的使能引脚
const byte ENB = 6;   //电机B的使能引脚
const byte ENC = 6;   //电机C的使能引脚
const byte END = 5;   //电机D的使能引脚
const byte IN1 = 10;  //电机A的正反转引脚
const byte IN2 = 8;   //电机A的正反转引脚
const byte IN3 = 9;   //电机B的正反转引脚
const byte IN4 = 7;   //电机B的正反转引脚
const byte IN5 = 9;   //电机C的正反转引脚
const byte IN6 = 7;   //电机C的正反转引脚
const byte IN7 = 10;  //电机D的正反转引脚
const byte IN8 = 8;   //电机D的正反转引脚

byte dir = 0;     //记录行进状态,0代表前进,1代表后退
byte turnL = 0;
byte turnR = 0;


void stop() {       //电机停止
  analogWrite(ENA,0);   //电机A的PWM输出
  analogWrite(ENB,0);   //电机B的PWM输出
  analogWrite(ENC,0);   //电机C的PWM输出
  analogWrite(END,0);   //电机D的PWM输出
}

void forward() {      //电机转向,前进(四个电机都正传)
  byte speed = 100;       //电机的PWM输出值
  analogWrite(ENA,speed);    //电机A的PWM输出
  digitalWrite(IN1,HIGH);    //
  digitalWrite(IN2,LOW);
  
  analogWrite(ENB,speed);    //电机B的PWM输出
  digitalWrite(IN3,HIGH);    //
  digitalWrite(IN4,LOW);
  
  analogWrite(ENC,speed);    //电机C的PWM输出
  digitalWrite(IN5,HIGH);    //
  digitalWrite(IN6,LOW);

  analogWrite(END,speed);    //电机D的PWM输出
  digitalWrite(IN7,HIGH);    //
  digitalWrite(IN8,LOW);
}

void backward(){        //电机转向,后退(四个电机都转)
  byte speed = 100;//电机的PWM输出值
  analogWrite(ENA,speed);    //电机A的PWM输出
  digitalWrite(IN1,LOW);    //
  digitalWrite(IN2,HIGH);
  
  analogWrite(ENB,speed);    //电机B的PWM输出
  digitalWrite(IN3,LOW);    //
  digitalWrite(IN4,HIGH);
  
  analogWrite(ENC,speed);    //电机C的PWM输出
  digitalWrite(IN5,LOW);    //
  digitalWrite(IN6,HIGH);

  analogWrite(END,speed);    //电机D的PWM输出
  digitalWrite(IN7,LOW);    //
  digitalWrite(IN8,HIGH);
}

void turnLeft(){     //电机转向,左转(电机A,D反转,电机B,C正转)
  byte speed = 150;//电机的PWM输出值
  analogWrite(ENA,speed);    //电机A的PWM输出
  digitalWrite(IN1,LOW);    //
  digitalWrite(IN2,HIGH);
  
  analogWrite(ENB,speed);    //电机B的PWM输出
  digitalWrite(IN3,HIGH);    //
  digitalWrite(IN4,LOW); 
  
  analogWrite(ENC,speed);    //电机C的PWM输出
  digitalWrite(IN5,HIGH);    //
  digitalWrite(IN6,LOW);
  
  analogWrite(END,speed);    //电机D的PWM输出
  digitalWrite(IN7,LOW);    //
  digitalWrite(IN8,HIGH);
}

void turnRight(){     //电机转向,右转(电机A,D正转,电机B,C反转)
  byte speed = 150;//电机的PWM输出值
  analogWrite(ENA,speed);    //电机A的PWM输出
  digitalWrite(IN1,HIGH);    //
  digitalWrite(IN2,LOW);
  
  analogWrite(ENB,speed);    //电机B的PWM输出
  digitalWrite(IN3,LOW);    //
  digitalWrite(IN4,HIGH);
  
  analogWrite(ENC,speed);    //电机C的PWM输出
  digitalWrite(IN5,LOW);    //
  digitalWrite(IN6,HIGH);

  analogWrite(END,speed);    //电机D的PWM输出
  digitalWrite(IN7,HIGH);    //
  digitalWrite(IN8,LOW);
}


void setup() {
  Serial.begin(9600); 
  pinMode(TrigPin, OUTPUT); //触发脚设置成输出
  pinMode(EchoPin, INPUT);  //触发脚设置成输入
  //电机模块的所有引脚全部设置成输出
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  pinMode(IN5,OUTPUT);
  pinMode(IN6,OUTPUT);
  pinMode(IN7,OUTPUT);
  pinMode(IN8,OUTPUT);

}

void loop() {
  digitalWrite(TrigPin, LOW); //低高低电平发一个短时间脉冲去TrigPin 
  delayMicroseconds(2); 
  digitalWrite(TrigPin, HIGH); 
  delayMicroseconds(10); 
  digitalWrite(TrigPin, LOW); 
  distance = pulseIn(EchoPin,HIGH)/58.00;//接受高电平的时间
   distance = distance / 58.00; //将回波时间换算成cm 
  Serial.print(distance); 
  Serial.print("cm"); 
  Serial.println(); 
  delay(1000);
  if(distance > 100) {   
    if(dir != 0) {   //如果目前的行进状态不是前进
      dir = 0;       //设置成行进
      stop();       //暂停电机0.5s
      delay(500);
    } 
  forward();     //前进
  }else{   
    if(dir != 1){
      dir = 1;
      stop();
      delay(500);    //持续0.5秒
    }
    turnLeft();
    
  }
    delay(1000);    //持续1秒
}

