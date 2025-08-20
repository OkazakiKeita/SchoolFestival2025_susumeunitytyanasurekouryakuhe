#pragma once
class Game;

class GameClear :public IGameObject
{
public:
	GameClear();
	~GameClear();
	//更新処理。
	void Update();
	void Initialize(float clearTime, int starCount);
	//描画処理。
	void Render(RenderContext& rc);

	SpriteRender m_spriteRender;	//スプライトレンダー。
	float m_clearTime = 0.0f;
	int m_starCount = 0;
	FontRender m_fontRender;
};

