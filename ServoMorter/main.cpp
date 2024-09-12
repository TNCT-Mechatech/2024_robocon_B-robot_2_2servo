#include "BufferedSerial.h"
#include "SCServo.h"
#include "mbed.h"
#include "wheelpart.hpp"
#include <cstdio>

#include <MbedHardwareSerial.hpp>
#include <SerialBridge.hpp>

#define SERIALBRIDGE_TX A0
#define SERIALBRIDGE_RX A1

#define SERIAL_TX D10
#define SERIAL_RX D2

DigitalOut LED(PA_5);

SerialDev *dev = new MbedHardwareSerial(
    new BufferedSerial(SERIALBRIDGE_TX, SERIALBRIDGE_RX, 115200));
SerialBridge serial(dev, 1024);

Control msg;

//  1000000bpsで通信を行う
BufferedSerial bserial(SERIAL_TX, SERIAL_RX, 1000000);
//  STSシリーズの場合は、SMS_STSを使う
SMS_STS st;
// wheelpartのclass定義
chem servo;

// main() runs in its own thread in the OS
int main() {

    int goalA, goalB;
  //   printf("initialize program\n\r");

  //  宣言したBufferedSerialをSMS_STSへ登録
  st.pSerial = &bserial;
  wait_us(1000 * 1000);

  while (true) {

    serial.update();

    if (msg.was_updated()) {

      servo.angle(static_cast<float>(msg.data.x) / 100,
                  static_cast<float>(msg.data.y) / 100);

      servo.lol();

      if(servo.getPwm(0) > 0.35)
        goalA = 100;

      if(servo.getPwm(1) > 0.35)
        goalB = 100;

      st.WritePosEx(10, goalA, 3400 * servo.getPwm(0), 50);
      st.WritePosEx(11, goalB, 3400 * servo.getPwm(1), 50);

      LED = !LED;

      wait_us(30 * 1000);
    }
    // printf("send Write signal\n\r");

    // //  回転指示(詳しくはクラスの中身みてください)
    // st.WritePosEx(10, 4095, 3400, 50);
    // //舵机(ID1)以最高速度V=3400步/秒，加速度A=50(50*100步/秒^2)，运行至P1=4095位置

    // wait_us(1000 * 1000 * 2);

    // st.WritePosEx(11, 0, 3400, 50);
    // //舵机(ID1)以最高速度V=3400步/秒，加速度A=50(50*100步/秒^2)，运行至P0=0位置
    // wait_us(1000 * 1000 * 2);
  }
}
