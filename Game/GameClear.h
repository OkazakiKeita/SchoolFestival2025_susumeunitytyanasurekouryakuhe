#pragma once
class Game;

class GameClear :public IGameObject
{
public:
	GameClear();
	~GameClear();
	//�X�V�����B
	void Update();
	void Initialize(float clearTime, int starCount);
	//�`�揈���B
	void Render(RenderContext& rc);

	SpriteRender m_spriteRender;	//�X�v���C�g�����_�[�B
	float m_clearTime = 0.0f;
	int m_starCount = 0;
	FontRender m_fontRender;
};

