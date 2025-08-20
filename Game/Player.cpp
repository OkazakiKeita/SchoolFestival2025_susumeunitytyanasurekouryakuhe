#include "stdafx.h"
#include "Player.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"
#include "GameClear.h"
#include "Game.h"

Player::Player()
{
	//初期位置。
	m_position.x = 0.0f;
	m_position.y = -800.0f;
	m_position.z =4500.0f;
	m_rotation.SetRotationY(3.14159f);

	/*m_position.x = 0.0f;
	m_position.y = 1000.0f;
	m_position.z = -2450.0f;
	m_rotation.SetRotationY(3.14159f);*/

	//アニメーションクリップをロードする。
	m_animationClips[enAnimationClip_Idle].Load("Assets/animData/idle.tka");
	m_animationClips[enAnimationClip_Idle].SetLoopFlag(true);
	m_animationClips[enAnimationClip_Walk].Load("Assets/animData/walk.tka");
	m_animationClips[enAnimationClip_Walk].SetLoopFlag(true);
	m_animationClips[enAnimationClip_Jump].Load("Assets/animData/jump.tka");
	m_animationClips[enAnimationClip_Jump].SetLoopFlag(false);
	//ユニティちゃんのモデルを読み込む。
	m_modelRender.Init("Assets/modelData/unityChan.tkm", m_animationClips, enAnimationClip_Num, enModelUpAxisY);

	//キャラコンを初期化する。
	m_characterController.Init(25.0f,75.0f,m_position);

	//落下の効果音。
	g_soundEngine->ResistWaveFileBank(3, "Assets/sound/warp.wav");

	m_modelRender.SetRotation(m_rotation);
}

Player::~Player()
{

}

//更新処理。
void Player::Update()
{
	//移動処理。
	Move();

	//回転処理。
	Rotation();

	//ステート管理。
	ManageState();

	//アニメーションの再生。
	PlayAnimation();

	//絵描きさんの更新処理。
	m_modelRender.Update();
}

void Player::Move()
{
	//xzの移動速度を0.0fにする。
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;

	//左スティックの入力量を取得。
	Vector3 stickL;
	stickL.x = g_pad[0]->GetLStickXF();
	stickL.y = g_pad[0]->GetLStickYF();

	//カメラの前方向と右方向のベクトルを持ってくる。
	Vector3 forward = g_camera3D->GetForward();
	Vector3 right = g_camera3D->GetRight();
	//y方向には移動させない。
	forward.y = 0.0f;
	right.y = 0.0f;

	//左スティックの入力量と300.0fを乗算。
	right *= stickL.x * 400.0f;
	forward *= stickL.y * 400.0f;

	//移動速度に上記で計算したベクトルを加算する。
	m_moveSpeed += right + forward;

	//地面に着いていたら。
	if (m_characterController.IsOnGround())
	{
		//重力をなくす。
		m_moveSpeed.y = 0.0f;
		//Aボタンが押されたら。
		if (g_pad[0]->IsTrigger(enButtonA))
		{
			//ジャンプさせる。
			m_moveSpeed.y = 800.0f;
		}
	}
	//地面に付いていなかったら。
	else
	{
		//重力を発生させる。
		m_moveSpeed.y -= 30.0f;
	}
	

	//キャラクターコントローラーを使って座標を移動させる。
	m_position = m_characterController.Execute(m_moveSpeed, 1.0f / 60.0f);

	//チェックポイントを作り落下したらその場所に戻るようにする。
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
	
	//絵描きさんに座標を教える。
	m_modelRender.SetPosition(m_position);
}

void Player::Rotation()
{
	//xかzの移動速度があったら（スティックの入力があったら）。
	if (fabsf(m_moveSpeed.x) >= 0.001f || fabsf(m_moveSpeed.z) >= 0.001f)
	{
		//キャラクターの方向を変える。
		m_rotation.SetRotationYFromDirectionXZ(m_moveSpeed);
		//絵描きさんに回転を教える。
		m_modelRender.SetRotation(m_rotation);
	}
}

//ステート管理。
void Player::ManageState()
{
	//地面に付いていなかったら。
	if (m_characterController.IsOnGround() == false)
	{
		//ステートを1（ジャンプ中）にする。
		m_playerState = 1;
		//ここでManageState関数の処理を終わらせる。
		return;
	}

	//地面に付いていたら。
	//xかzの移動速度があったら（スティックの入力があったら）。
	if (fabsf(m_moveSpeed.x) >= 0.001f || fabsf(m_moveSpeed.z) >= 0.001f)
	{
		//ステートを2（歩き）にする。
		m_playerState = 2;
	}
	//xとzの移動速度がなかったら（スティックの入力がなかったら）。
	else
	{
		//ステートを0（待機）にする。
		m_playerState = 0;
	}
}
void Player::PlayAnimation()
{
	switch(m_playerState) {
		//プレイヤーステートが0（待機）だったら。
	case 0:
		//待機アニメーションを再生する。
		m_modelRender.PlayAnimation(enAnimationClip_Idle);
		break;
		//プレイヤーステートが1（ジャンプ中）だったら。
	case 1:
		//ジャンプアニメーションを再生する。
		m_modelRender.PlayAnimation(enAnimationClip_Jump);
		break;
		//プレイヤーステートが2（歩き）だったら。
	case 2:
		//歩きアニメーションを再生する。
		m_modelRender.PlayAnimation(enAnimationClip_Walk);
		break;
	}
}

//描画処理。
void Player::Render(RenderContext& rc)
{
	//ユニティちゃんを描画する。
	m_modelRender.Draw(rc);
}
