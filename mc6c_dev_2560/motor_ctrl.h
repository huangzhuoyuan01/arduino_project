#ifndef _MOTOR_CTRL_H_
#define _MOTOR_CTRL_H_

class Motor {
public:
  int Motor_A_Pin;
  int Motor_B_Pin;
  int Motor_PWM_Pin;
  Motor(int Motor_A, int Motor_B, int Motor_PWM)    //Encoder Motor pin
  {
    Motor_A_Pin = Motor_A;
    Motor_B_Pin = Motor_B;
    Motor_PWM_Pin = Motor_PWM;
  }
  
  void init(void);
  void run(int speed);
  void stop(void);
};

void Motor::init(void)
{
  pinMode(Motor_A_Pin, OUTPUT);
  pinMode(Motor_B_Pin, OUTPUT);
  pinMode(Motor_PWM_Pin, OUTPUT);
}

void Motor::stop()
{
   digitalWrite(Motor_A_Pin,LOW);
   digitalWrite(Motor_B_Pin,LOW);
   analogWrite(Motor_PWM_Pin,0);
}

void Motor::run(int speed)
{
    if(speed > 0)
    {
        digitalWrite(Motor_A_Pin,HIGH);
        digitalWrite(Motor_B_Pin,LOW);
        if(speed > 250)speed = 250;
        analogWrite(Motor_PWM_Pin,speed);
    }
   else
   {
        digitalWrite(Motor_A_Pin,LOW);
        digitalWrite(Motor_B_Pin,HIGH);
        if(speed < -250)speed = -250;
        analogWrite(Motor_PWM_Pin,speed * (-1));
    }
}

#endif


