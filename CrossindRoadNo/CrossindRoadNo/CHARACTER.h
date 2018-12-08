#pragma once
class CHARACTER
{
private:
	int timer;
	int type;

public:
	CHARACTER();
	~CHARACTER();

	//기본 프레임워크
	void init();
	void reset();
	void draw();	
	void update();
	void keyboard();

	void draw_body();
	void draw_leg();
};

