#pragma once
class Game;
class Player;
class Star:public IGameObject
{
public:
	Star();
	~Star();
	//�X�V�����B
	void Update();
	//�`�揈���B
	void Render(RenderContext& rc);
	//��]����
	void Rotation();
	//�ړ������B
	void Move();

	//�����o�ϐ��B
	ModelRender m_modelRender;	//���f�������_�[�B
	Vector3 m_position;	//���W�B
	Quaternion m_rotation;	//�N�H�[�^�j�I���B
	Player* m_player;	//�v���C���[�B
	int m_star = 9;
	float m_time = 60.0f;
};

