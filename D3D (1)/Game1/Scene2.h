#pragma once

class Scene2 : public Scene
{
private:
	// �Ű���
	Player* player;
	//Player* player2;
	Player2* player2;
	bool isplayer;

	UI* exitbutton;
	UI* pausebutton;
	UI* playbutton;
	UI* cam1pause;
	UI* cam2pause;
	bool ismenu;
	bool isstop;
	int isstoptime;


	// ī�޶�
	Camera* Cam;
	Camera* Cam2;


	// õ����
	class Game_ui* game_ui;
	class Game_ui* game_ui2;

	// ���ȣ
	SwimmingPool* pool;

	// ��������
	Grid*	grid;
	//Actor*  player2;
	Actor*  plane;
	Actor*	dead;
	Vector3 src, dest;
	float   t;
	float   dis;
	float	srcR, destR;
	float   tR;
	float   disR;
	Actor* ui;

public:
	Scene2();
	~Scene2();
	virtual void Init() override;
	virtual void Release() override; //����
	virtual void Update() override;
	virtual void LateUpdate() override;//����
	virtual void Render() override;
	virtual void PreRender() override;
	virtual void ResizeScreen() override;
};

