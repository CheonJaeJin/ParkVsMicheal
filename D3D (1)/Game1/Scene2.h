#pragma once

class Scene2 : public Scene
{
private:
	// 신관희
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


	// 카메라
	Camera* Cam;
	Camera* Cam2;


	// 천재진
	class Game_ui* game_ui;
	class Game_ui* game_ui2;

	// 김두호
	SwimmingPool* pool;

	// 수업관련
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
	virtual void Release() override; //해제
	virtual void Update() override;
	virtual void LateUpdate() override;//갱신
	virtual void Render() override;
	virtual void PreRender() override;
	virtual void ResizeScreen() override;
};

