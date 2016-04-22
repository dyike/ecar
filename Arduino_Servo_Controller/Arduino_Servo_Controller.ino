// Arduino Bluetooth LE Servo Controlled by iOS
#include <Servo.h>
#include <SoftwareSerial.h>

int LED = 13;   //大多数LED使用在pin 13
SoftwareSerial BLE_Shield(4,5);  //将原先的0—>RX,1->TX,换到4->RX,5->TX
Servo myservo;    // 创建一个servo对象来控制servo
void setup() {
  pinMode(LED,OUTPUT);  //set pin as an output
  digitalWrite(LED,HIGH);  //Turn on LED(is set to HIGH voltage)

  myservo.attach(9);   //将servo对象放在pin 9
  myservo.write(0);     //初始化servo的位置
  BLE_Shield.begin(9600);//Setup the serial port at 9600 bps. This is the BLE Shield default baud rate.
  
}

void loop() {
  delay(500);
  digitalWrite(LED,LOW);
  delay(500);
  digitalWrite(LED,HIGH);
  if (BLE_Shield.available()){
    myservo.write(BLE_Shield.read());//读出servo的位置
  }



  
}
