#ifndef _WHEELPART_HPP_
#define _WHEELPART_HPP_

#include "mbed.h"
#include "math.h"

#include <MbedHardwareSerial.hpp>
#include <SerialBridge.hpp>
#include <cstdio>

#include "Control.hpp"

class chem {
private:
  float x, y, r;
  float d, da;
  float a, b;

  int dir1, dir2;
  float pwm1, pwm2;

  const float PI = 3.1415926535;

public:
  // コンストラクタ
  chem(){};

  //メンバ関数
  void angle(float _x, float _y) {
    x = _x;
    y = _y;

    if (atan2(y, x) < 0)
      d = PI + fabs((fabs(atan2(y, x)) - PI));
    else
      d = atan2(y, x);

    d = d * (180 / PI);
  }

  void lol()
  {
    if (90 > d && d >= 0.0) {

      dir1 = 0;
      dir2 = 1;
      da = d / 90;

      r = fabs(sqrt(x * x + y * y));
      if (r > 1)
        r = 0.98;
      pwm1 = r * da;
      pwm2 = r;
    }

    if (180 > d && d >= 90.0) {

      dir1 = 0;
      dir2 = 1;

      da = fabs(d - 180.0) / 90;

      r = fabs(sqrt(x * x + y * y));
      if (r > 1)
        r = 0.98;
      pwm1 = r;
      pwm2 = r * da;
    }

    if (270 > d && d >= 180.0) {

      dir1 = 1;
      dir2 = 0;

      da = (d - 180.0) / 90;

      r = fabs(sqrt(x * x + y * y));
      if (r > 1)
        r = 0.98;
      pwm1 = r;
      pwm2 = r * da;
    }

    if (360 > d && d >= 270.0) {

      dir1 = 1;
      dir2 = 0;

      da = fabs(d - 360.0) / 90;

      r = fabs(sqrt(x * x + y * y));
      if (r > 1)
        r = 0.98;
      pwm1 = r * da;
      pwm2 = r;
    }

    // wait_us(30000);
    // printf("%f\n\r",r);
    // printf("%f\n\r",d);
    // printf("%f\n\r",da);
    // wait(0.5);
  }

    float getPwm(int c)
        {
            if(c == 0)
                return pwm1;
            else if(c == 1)
                return pwm2;
            else {
                puts("Error : getMoterInfo");
                return 0;
            }
        }
    
     int getDir(int e)
        {
            if(e == 0)
                return dir1;
            else if(e == 1)
                return dir2;
            else {
                puts("Error : getMoterInfo");
                return -1;
            }
            
        }
};

#endif