#pragma once

class Player;
//�Q�[�����̃J�����𐧌䂷��B
class GameCamera:public IGameObject
{
public:
	GameCamera();
	~GameCamera();
	bool Start();
	void Update();

	Player* m_player;	//�v���C���[�B
	Vector3 m_toCameraPos;	//�����_����x�X�Ɍ������x�N�g���B
};

