#ifndef _MC6C_CONTROL_H_
#define _MC6C_CONTROL_H_

class MC6C_Control {
public:
	int CH_Rx;
	int CH_Ry;
	int CH_Lx;
	int CH_Ly;
	int CH_5;
	int CH_6;

	MC6C_Control(int CH_Rx, int CH_Ry, int CH_Lx, int CH_Ly, int CH_5, int CH_6)
	{
		this->CH_Rx = CH_Rx;
		this->CH_Ry = CH_Ry;
		this->CH_Lx = CH_Lx;
		this->CH_Ly = CH_Ly;
		this->CH_5 = CH_5;
		this->CH_6 = CH_6;
	}

	MC6C_Control(int CH_Rx, int CH_Ry, int CH_Lx, int CH_Ly)
	{
		this->CH_Rx = CH_Rx;
		this->CH_Ry = CH_Ry;
		this->CH_Lx = CH_Lx;
		this->CH_Ly = CH_Ly;
	}

	void init(void);
	void Updata_CH_Buf(void);

	int Right_X;
	int Right_Y;
	int Left_X;
	int Left_Y;
	int CH5;
	int CH6;
};

void MC6C_Control::init(void)
{
	pinMode(CH_Rx, INPUT_PULLUP);
	pinMode(CH_Ry, INPUT_PULLUP);
	pinMode(CH_Lx, INPUT_PULLUP);
	pinMode(CH_Ly, INPUT_PULLUP);
	pinMode(CH_5, INPUT_PULLUP);
	pinMode(CH_6, INPUT_PULLUP);
  Serial.println("MC6C init OK!");
}

void MC6C_Control::Updata_CH_Buf()
{
	Right_X = pulseIn(CH_Rx, HIGH, 20000);
	Right_Y = pulseIn(CH_Ry, HIGH, 20000);
	Left_X = pulseIn(CH_Lx, HIGH, 20000);
	Left_Y = pulseIn(CH_Ly, HIGH, 20000);
	CH5 = pulseIn(CH_5, HIGH, 20000);
	CH6 = pulseIn(CH_6, HIGH, 20000);
}

#endif


