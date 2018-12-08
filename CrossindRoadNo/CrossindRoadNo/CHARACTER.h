#pragma once
class CHARACTER
{
private:
	int local_time;
	int type;

public:
	CHARACTER();
	~CHARACTER();

	//�⺻ �����ӿ�ũ
	void init();
	void reset();
	void draw();	
	void update();
	void keyboard();

	void draw_body();
	void draw_leg();
};

