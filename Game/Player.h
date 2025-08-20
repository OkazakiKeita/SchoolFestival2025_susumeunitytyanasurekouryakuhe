#pragma once

//�v���C���[�N���X�B
class Player:public IGameObject
{
public:
	Player();
	~Player();
	//�X�V�����B
	void Update();
	//�`�揈���B
	void Render(RenderContext& rc);
	//�ړ������B
	void Move();
	//��]�����B
	void Rotation();
	//�X�e�[�g�Ǘ��B
	void ManageState();
	//�A�j���[�V�����̍Đ��B
	void PlayAnimation();

	//�����o�ϐ��B
	ModelRender m_modelRender;	//���f�������_�[�B
	Vector3 m_position;			//���W�B
	enum EnAnimationClip {		//�A�j���[�V�����B
		enAnimationClip_Idle,
		enAnimationClip_Walk,
		enAnimationClip_Jump,
		enAnimationClip_Num,
	};
	AnimationClip m_animationClips[enAnimationClip_Num];	//�A�j���[�V�����N���b�v�B
	CharacterController m_characterController;	//�L�����N�^�[�R���g���[���[�B
	Vector3 m_moveSpeed;	//�ړ����x�B
	Quaternion m_rotation;	//�N�H�[�^�j�I���B
	int m_playerState = 0;	//�v���C���[�̃X�e�[�g�i��ԁj��\���ϐ��B
	int m_starCount = 0;	//�W�߂����̐����J�E���g����B
};
