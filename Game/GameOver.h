#pragma once
class GameOver:public IGameObject
{
public:
	GameOver();
	~GameOver();
	//�X�V�����B
	void Update();
	//�`�揈���B
	void Render(RenderContext& rc);

	SpriteRender m_GameOver;	//�X�v���C�g�����_�[�B
};

