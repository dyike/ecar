#include <Servo.h>       //调用舵机函数库
#include <SoftwareSerial.h>
Servo myservo;     //创建一个舵机对象
SoftwareSerial BLE_Shield(2,3);   //RX|TX
void setup() {
  // put your setup code here, to run once:
  BLE_Shield.begin(9600); 
  myservo.attach(7);    //定义数字引脚7为舵机控制引脚
  myservo.write(0);  //初始化舵机的位置
}

void loop() {
  // put your main code here, to run repeatedly:
  if (BLE_Shield.available()) {
    myservo.write(BLE_Shield.read());  // Write position to servo
  } 
}
