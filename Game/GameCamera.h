#pragma once

class Player;
//ゲーム中のカメラを制御する。
class GameCamera:public IGameObject
{
public:
	GameCamera();
	~GameCamera();
	bool Start();
	void Update();

	Player* m_player;	//プレイヤー。
	Vector3 m_toCameraPos;	//注視点から支店に向かうベクトル。
};

