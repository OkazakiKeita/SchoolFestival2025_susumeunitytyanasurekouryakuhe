#include "stdafx.h"
#include "GameOver.h"
#include "Title.h"

GameOver::GameOver()
{
	//�Q�[���I�[�o�[�摜��ǂݍ��ށB
	m_GameOver.Init("Assets/sprite/GameOver.dds", 1920.0f, 1080.0f);
}

GameOver::~GameOver()
{

}

//�X�V�����B
void GameOver::Update()
{
	//A�{�^���������ꂽ��B
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		//�^�C�g���̃I�u�W�F�N�g�����B
		NewGO<Title>(0, "title");
		//�폜�B
		DeleteGO(this);
	}
}

//�`�揈���B
void GameOver::Render(RenderContext& rc)
{
	m_GameOver.Draw(rc);
}
