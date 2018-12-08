#pragma once
#define KEY_FRONT 0
#define KEY_BACK 1
#define KEY_RIGHT 2
#define KEY_LEFT 3

#define STATE_IDLE 0
#define STATE_MOVE 1
#define STATE_DAMAGE 2

class CHARACTER{

private:
	int local_time;
	int type;
	int key[4];
	int state;
	bool timerPingPong;
public:
	CHARACTER();
	~CHARACTER();

	//�⺻ �����ӿ�ũ
	void init();
	void reset();
	void draw();	
	void update();
	void keyboard(unsigned char);

	//ĳ���� ��ο� ����
	void draw_body();
	void draw_leg();
	void animation();

	//Ű���� Ű ����
	void KeySetting(unsigned char, unsigned char, unsigned char, unsigned char);
	
};

