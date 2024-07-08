#include <Arduino.h>
#include "MC6C_Control.h"
#include "motor_ctrl.h"
#include <HardwareSerial.h>
#include <Servo.h>

Servo servo1,servo2;

const int cs_Rx = 1500;    //手柄偏移补偿
const int cs_Ry = 1500;
const int cs_Lx = 1000;
const int cs_Ly = 1500;

#define Ch_1   A6    //Rx (roll)
#define Ch_2   A7    //Ry (pitch)
#define Ch_3   A8    //Lx（thro）
#define Ch_4   A9    //Ly (yaw)
#define Ch_5   A10   //switch_c
#define Ch_6   A11   //预留
#define YAW_SCALE 0.5
#define Motor5_pwm 9

MC6C_Control MC6C(Ch_1,Ch_2,Ch_3,Ch_4,Ch_5,Ch_6);

/*
  M1 \    / M2


  M3 /    \ M4
*/
Motor M1(A4,A5,4), M2(43,42,6);
Motor M3(34,35,11), M4(37,36,7);

void setup() 
{
  int i;
  Serial.begin(9600); //初始化串口
  MC6C.init();        //接收机
  M1.init();          //麦轮
  M2.init();
  M3.init();
  M4.init();
  servo1.attach(2);
  servo2.attach(3);              //角度舵机
  pinMode(Motor5_pwm, OUTPUT);   //电刷子
}

void loop() 
{
  MC6C.Updata_CH_Buf();
  
  MC6C.Right_X = (MC6C.Right_X-cs_Rx);
  MC6C.Right_Y = (MC6C.Right_Y-cs_Ry);
  MC6C.Left_X = (MC6C.Left_X-cs_Lx);
  MC6C.Left_Y = (MC6C.Left_Y-cs_Ly);

  /*
  Serial.print("ch\n");
  Serial.println(MC6C.Right_X);
  Serial.println(MC6C.Right_Y);
  Serial.println(MC6C.Left_X);
  Serial.println(MC6C.Left_Y);
  //Serial.print("ch5\n");
  Serial.println(MC6C.CH5);
  delay(500);
  */
  
  if(MC6C.Right_X > 20 || MC6C.Right_X < -20 || MC6C.Right_Y > 20 || MC6C.Right_Y < -20 || MC6C.Left_Y > 20 || MC6C.Left_Y < -20)
  {
    if(MC6C.Right_X < -1490 && MC6C.Right_Y < -1490 && MC6C.Left_Y < -1490)  //接收机没信号的情况
    {
      M1.stop();
      M2.stop();
      M3.stop();
      M4.stop();
    }
    else
    {
      M1.run(MC6C.Right_Y * cos(0.758) + MC6C.Right_X * cos(0.758) + MC6C.Left_Y * YAW_SCALE);
      M2.run(MC6C.Right_Y * cos(0.758) - MC6C.Right_X * cos(0.758) - MC6C.Left_Y * YAW_SCALE);
      M3.run(MC6C.Right_Y * cos(0.758) - MC6C.Right_X * cos(0.758) + MC6C.Left_Y * YAW_SCALE);
      M4.run(MC6C.Right_Y * cos(0.758) + MC6C.Right_X * cos(0.758) - MC6C.Left_Y * YAW_SCALE);
    }
  }
  else  //遥控信号在中位
  {
    M1.stop();
    M2.stop();
    M3.stop();
    M4.stop();
  }
  
  //角度
  if(MC6C.CH5 < 1100)
  {
    servo2.write(90);
    analogWrite(Motor5_pwm,255);
  }
  else if(MC6C.CH5 > 1800)
  {
    servo2.write(180);
    analogWrite(Motor5_pwm,0);
  }

  //上下
  if(MC6C.Left_X > 10)
  {
    //Serial.print("down\n");
    //Serial.print("ch3\n");
    //Serial.println(MC6C.Left_X);
    //int down_dr = MC6C.Left_X*0.04;
    //Serial.println(down_dr);
    servo1.write(90-(MC6C.Left_X*0.053));
  }
  else 
  {
    //Serial.print("up\n");
    servo1.write(90);
  }
}
 
