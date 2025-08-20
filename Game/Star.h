#pragma once
class Game;
class Player;
class Star:public IGameObject
{
public:
	Star();
	~Star();
	//更新処理。
	void Update();
	//描画処理。
	void Render(RenderContext& rc);
	//回転処理
	void Rotation();
	//移動処理。
	void Move();

	//メンバ変数。
	ModelRender m_modelRender;	//モデルレンダー。
	Vector3 m_position;	//座標。
	Quaternion m_rotation;	//クォータニオン。
	Player* m_player;	//プレイヤー。
	int m_star = 9;
	float m_time = 60.0f;
};

