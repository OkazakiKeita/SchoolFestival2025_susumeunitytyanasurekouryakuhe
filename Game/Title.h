#pragma once



class Title:public IGameObject
{
public:
	Title();
	~Title();
	//�X�V�����B
	void Update();
	//�`��֐��B
	void Render(RenderContext& rc);
	//�X�v���C�g�����_�[�B
	SpriteRender m_spriteRender;
	FontRender m_startRender;
};

