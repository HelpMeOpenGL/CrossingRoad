#pragma once
#define KEY_FRONT 0
#define KEY_BACK 1
#define KEY_RIGHT 2
#define KEY_LEFT 3

#define STATE_IDLE 0
#define STATE_MOVE 1
#define STATE_DAMAGE 2

#define ITEM_STURN 1 //����
#define ITEM_MOVE 2 //�ڷ���Ʈ
#define ITEM_FOG 3 //�Ȱ�


class CHARACTER{
private:
	int local_time;
	int type;
	int key[4];
	int key_item;
	int state;
	bool time_ping;
	int map[MAP_SIZE_X][MAP_SIZE_Y];
	int item;
	bool key_lock;
	int item_timer;
	int item_timer2;
	bool b_item_fog;
	POINT location;
	int dir;
	int body_color[3];
	CAR car_data[CAR_NUM];
	POINT other_location;

	bool jump_b;
	int jump_timer;
	int jump_height;

	bool move_b;
	float move_timer;
	POINT move_tmp;//�̰Ŵ� �̵��ϴ� ũ�� ����
	double moveTmp;//0~1���� �޼ҵ� ������ ����



	float idle_LR_T;
	float idle_UD_T;
	bool idle_LR;
	bool idle_UD;

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
	

	void idle_draw();
	void idle_update();
	void call_jump();
	void call_move();
	
	void sturn_draw();
	

	void load_map(int(*input)[MAP_SIZE_Y]);

	POINT get_location();
	void load_location(POINT);

	void update_map_obj(CAR*);

	bool check_itemkey(int);

	int use_item();
	void hit_item(int);
	void get_item(int);
	//Ű���� Ű ����
	void KeySetting(unsigned char, unsigned char, unsigned char, unsigned char);
	void keySetting_item(unsigned char);
	void SetBodyColor(int, int, int);
	void Setlocaiton(int, int);
	void load_Camera(float);
};

