#include "stdafx.h"
#include "Star.h"
#include "Player.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"

Star::Star()
{
	//���f���̓ǂݍ��݁B
	m_modelRender.Init("Assets/modelData/star.tkm");
	//�v���C���[�̃I�u�W�F�N�g��T���Ď����Ă���B
	m_player = FindGO<Player>("player");

	//�����폜����Ƃ��̉���ǂݍ��ށB
	g_soundEngine->ResistWaveFileBank(2, "Assets/sound/StarGet.wav");
}

Star::~Star()
{

}

void Star::Update()
{
	//��]�����B
	Rotation();

	//�ړ������B
	Move();

	//�G�`������̍X�V�����B
	m_modelRender.Update();

	//�v���C���[���灙�Ɍ����x�N�g�����v�Z�B
	Vector3 diff = m_player->m_position - m_position;
	//�x�N�g���̒�����120.0f��菬����������B
	if (diff.Length() <= 150.0f)
	{
		//���ʉ����Đ��B
		SoundSource* se = NewGO<SoundSource>(4);
		se->Init(2);
		se->SetVolume(3.5f);
		se->Play(false);
		//�J�E���g��+1����B
		m_player->m_starCount += 1;
		//���̍폜�B
		DeleteGO(this);
	}
	m_time -= g_gameTime->GetFrameDeltaTime();
	int sec = (int)m_time;
	if (m_player->m_position.y >= 1200.0f && m_player->m_position.z <= -3250.0f||m_time<0)
	{
		DeleteGO(this);
	}
}

void Star::Move()
{
	//�G�`������ɍ��W��������B
	m_modelRender.SetPosition(m_position);
}

void Star::Rotation()
{
	//��]�����Z����B
	m_rotation.AddRotationDegY(2.0f);

	//�G�`������ɉ�]��������B
	m_modelRender.SetRotation(m_rotation);
}

void Star::Render(RenderContext& rc)
{
	//�`�悷��B
	m_modelRender.Draw(rc);
}