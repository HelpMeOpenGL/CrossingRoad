#pragma once
#define KEY_FRONT 0
#define KEY_BACK 1
#define KEY_RIGHT 2
#define KEY_LEFT 3

#define STATE_IDLE 0
#define STATE_MOVE 1
#define STATE_DAMAGE 2

#define ITEM_STURN 1 //스턴
#define ITEM_MOVE 2 //텔레포트
#define ITEM_FOG 3 //안개

struct DIRECTION {
	double x, y, z;
};

struct S_DUST {
	DIRECTION location;
	int speed;
};

class CHARACTER{
private:
	int local_time;
	int type;
	int key[4];
	int state;
	bool time_ping;
	int map[MAP_SIZE_X][MAP_SIZE_Y];
	int item;
	bool key_lock;
	int item_timer;
	bool b_item_fog;
	POINT location;
	int dir;
	int body_color[3];
<<<<<<< HEAD
	int jump_timer;
	int jump_height;

=======
	float idle_LR_T;
	float idle_UD_T;
	bool idle_LR;
	bool idle_UD;
>>>>>>> eaf0783d1ccb1dd07e127024a709816a6b054288
public:
	CHARACTER();
	~CHARACTER();

	//기본 프레임워크
	void init();
	void reset();
	void draw();	
	void update();
	void keyboard(unsigned char);

	//캐릭터 드로우 관련
	void draw_body();
	void draw_leg();
	void animation();
	

	void idle_draw();
	void idle_update();
	void jump_draw();
	void jump_update();

	void load_map(int(*input)[MAP_SIZE_Y]);

	int use_item();
	void hit_item(int);
	//키보드 키 세팅
	void KeySetting(unsigned char, unsigned char, unsigned char, unsigned char);
	void SetBodyColor(int, int, int);

};

