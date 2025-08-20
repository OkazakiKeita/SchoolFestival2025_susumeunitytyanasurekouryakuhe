#include "stdafx.h"
#include "Player.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"
#include "GameClear.h"
#include "Game.h"

Player::Player()
{
	//�����ʒu�B
	m_position.x = 0.0f;
	m_position.y = -800.0f;
	m_position.z =4500.0f;
	m_rotation.SetRotationY(3.14159f);

	/*m_position.x = 0.0f;
	m_position.y = 1000.0f;
	m_position.z = -2450.0f;
	m_rotation.SetRotationY(3.14159f);*/

	//�A�j���[�V�����N���b�v�����[�h����B
	m_animationClips[enAnimationClip_Idle].Load("Assets/animData/idle.tka");
	m_animationClips[enAnimationClip_Idle].SetLoopFlag(true);
	m_animationClips[enAnimationClip_Walk].Load("Assets/animData/walk.tka");
	m_animationClips[enAnimationClip_Walk].SetLoopFlag(true);
	m_animationClips[enAnimationClip_Jump].Load("Assets/animData/jump.tka");
	m_animationClips[enAnimationClip_Jump].SetLoopFlag(false);
	//���j�e�B�����̃��f����ǂݍ��ށB
	m_modelRender.Init("Assets/modelData/unityChan.tkm", m_animationClips, enAnimationClip_Num, enModelUpAxisY);

	//�L�����R��������������B
	m_characterController.Init(25.0f,75.0f,m_position);

	//�����̌��ʉ��B
	g_soundEngine->ResistWaveFileBank(3, "Assets/sound/warp.wav");

	m_modelRender.SetRotation(m_rotation);
}

Player::~Player()
{

}

//�X�V�����B
void Player::Update()
{
	//�ړ������B
	Move();

	//��]�����B
	Rotation();

	//�X�e�[�g�Ǘ��B
	ManageState();

	//�A�j���[�V�����̍Đ��B
	PlayAnimation();

	//�G�`������̍X�V�����B
	m_modelRender.Update();
}

void Player::Move()
{
	//xz�̈ړ����x��0.0f�ɂ���B
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;

	//���X�e�B�b�N�̓��͗ʂ��擾�B
	Vector3 stickL;
	stickL.x = g_pad[0]->GetLStickXF();
	stickL.y = g_pad[0]->GetLStickYF();

	//�J�����̑O�����ƉE�����̃x�N�g���������Ă���B
	Vector3 forward = g_camera3D->GetForward();
	Vector3 right = g_camera3D->GetRight();
	//y�����ɂ͈ړ������Ȃ��B
	forward.y = 0.0f;
	right.y = 0.0f;

	//���X�e�B�b�N�̓��͗ʂ�300.0f����Z�B
	right *= stickL.x * 400.0f;
	forward *= stickL.y * 400.0f;

	//�ړ����x�ɏ�L�Ōv�Z�����x�N�g�������Z����B
	m_moveSpeed += right + forward;

	//�n�ʂɒ����Ă�����B
	if (m_characterController.IsOnGround())
	{
		//�d�͂��Ȃ����B
		m_moveSpeed.y = 0.0f;
		//A�{�^���������ꂽ��B
		if (g_pad[0]->IsTrigger(enButtonA))
		{
			//�W�����v������B
			m_moveSpeed.y = 800.0f;
		}
	}
	//�n�ʂɕt���Ă��Ȃ�������B
	else
	{
		//�d�͂𔭐�������B
		m_moveSpeed.y -= 30.0f;
	}
	

	//�L�����N�^�[�R���g���[���[���g���č��W���ړ�������B
	m_position = m_characterController.Execute(m_moveSpeed, 1.0f / 60.0f);

	//�`�F�b�N�|�C���g����藎�������炻�̏ꏊ�ɖ߂�悤�ɂ���B
	Vector3 initialposition = Vector3(0.0f, -800.0f, 4500.0f);
	Vector3 checkpoint1 = Vector3(0.0f, -280.0f, 3350.0f);
	Vector3 checkpoint2 = Vector3(100.0f, 150.0f, 2000.0f);
	Vector3 checkpoint3 = Vector3(0.0f, 40.0f, -450.0f);
	Vector3 checkpoint4 = Vector3(0.0f, 400.0f, -1850.0f);
	Vector3 checkpoint5 = Vector3(0.0f, 1000.0f, -2450.0f);
	Vector3 gool = Vector3(0.0f, 1200.0f, 3250.0f);
	if (m_position.y < -930.0f && m_position.z>3300.0f)
	{
		SoundSource* se = NewGO<SoundSource>(3);
		se->Init(3);
		se->SetVolume(3.5f);
		se->Play(false);

		m_position = initialposition;
		m_moveSpeed = Vector3::Zero;
		m_characterController.SetPosition(m_position);
	}
	if (m_position.y<-930.0f&&m_position.z>2000.0f)
	{
		SoundSource* se = NewGO<SoundSource>(3);
		se->Init(3);
		se->SetVolume(3.5f);
		se->Play(false);

		m_position = checkpoint1;
		m_moveSpeed = Vector3::Zero;
		m_characterController.SetPosition(m_position);
	}
	if (m_position.y < -930.0f && m_position.z>-450.0f)
	{
		SoundSource* se = NewGO<SoundSource>(3);
		se->Init(3);
		se->SetVolume(3.5f);
		se->Play(false);

		m_position = checkpoint2;
		m_moveSpeed = Vector3::Zero;
		m_characterController.SetPosition(m_position);
	}
	if (m_position.y < -930.0f && m_position.z>-1850.0f)
	{
		SoundSource* se = NewGO<SoundSource>(3);
		se->Init(3);
		se->SetVolume(3.5f);
		se->Play(false);

		m_position = checkpoint3;
		m_moveSpeed = Vector3::Zero;
		m_characterController.SetPosition(m_position);
	}
	if (m_position.y < -930.0f && m_position.z>-2450.0f)
	{
		SoundSource* se = NewGO<SoundSource>(3);
		se->Init(3);
		se->SetVolume(3.5f);
		se->Play(false);

		m_position = checkpoint4;
		m_moveSpeed = Vector3::Zero;
		m_characterController.SetPosition(m_position);
	}
	if (m_position.y < -930.0f && m_position.z>-3500.0f)
	{
		SoundSource* se = NewGO<SoundSource>(3);
		se->Init(3);
		se->SetVolume(3.5f);
		se->Play(false);

		m_position = checkpoint5;
		m_moveSpeed = Vector3::Zero;
		m_characterController.SetPosition(m_position);
	}
	
	//�G�`������ɍ��W��������B
	m_modelRender.SetPosition(m_position);
}

void Player::Rotation()
{
	//x��z�̈ړ����x����������i�X�e�B�b�N�̓��͂���������j�B
	if (fabsf(m_moveSpeed.x) >= 0.001f || fabsf(m_moveSpeed.z) >= 0.001f)
	{
		//�L�����N�^�[�̕�����ς���B
		m_rotation.SetRotationYFromDirectionXZ(m_moveSpeed);
		//�G�`������ɉ�]��������B
		m_modelRender.SetRotation(m_rotation);
	}
}

//�X�e�[�g�Ǘ��B
void Player::ManageState()
{
	//�n�ʂɕt���Ă��Ȃ�������B
	if (m_characterController.IsOnGround() == false)
	{
		//�X�e�[�g��1�i�W�����v���j�ɂ���B
		m_playerState = 1;
		//������ManageState�֐��̏������I��点��B
		return;
	}

	//�n�ʂɕt���Ă�����B
	//x��z�̈ړ����x����������i�X�e�B�b�N�̓��͂���������j�B
	if (fabsf(m_moveSpeed.x) >= 0.001f || fabsf(m_moveSpeed.z) >= 0.001f)
	{
		//�X�e�[�g��2�i�����j�ɂ���B
		m_playerState = 2;
	}
	//x��z�̈ړ����x���Ȃ�������i�X�e�B�b�N�̓��͂��Ȃ�������j�B
	else
	{
		//�X�e�[�g��0�i�ҋ@�j�ɂ���B
		m_playerState = 0;
	}
}
void Player::PlayAnimation()
{
	switch(m_playerState) {
		//�v���C���[�X�e�[�g��0�i�ҋ@�j��������B
	case 0:
		//�ҋ@�A�j���[�V�������Đ�����B
		m_modelRender.PlayAnimation(enAnimationClip_Idle);
		break;
		//�v���C���[�X�e�[�g��1�i�W�����v���j��������B
	case 1:
		//�W�����v�A�j���[�V�������Đ�����B
		m_modelRender.PlayAnimation(enAnimationClip_Jump);
		break;
		//�v���C���[�X�e�[�g��2�i�����j��������B
	case 2:
		//�����A�j���[�V�������Đ�����B
		m_modelRender.PlayAnimation(enAnimationClip_Walk);
		break;
	}
}

//�`�揈���B
void Player::Render(RenderContext& rc)
{
	//���j�e�B������`�悷��B
	m_modelRender.Draw(rc);
}
