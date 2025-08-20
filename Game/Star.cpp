#include "stdafx.h"
#include "Star.h"
#include "Player.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"

Star::Star()
{
	//モデルの読み込み。
	m_modelRender.Init("Assets/modelData/star.tkm");
	//プレイヤーのオブジェクトを探して持ってくる。
	m_player = FindGO<Player>("player");

	//☆を削除するときの音を読み込む。
	g_soundEngine->ResistWaveFileBank(2, "Assets/sound/StarGet.wav");
}

Star::~Star()
{

}

void Star::Update()
{
	//回転処理。
	Rotation();

	//移動処理。
	Move();

	//絵描きさんの更新処理。
	m_modelRender.Update();

	//プレイヤーから☆に向くベクトルを計算。
	Vector3 diff = m_player->m_position - m_position;
	//ベクトルの長さが120.0fより小さかったら。
	if (diff.Length() <= 150.0f)
	{
		//効果音を再生。
		SoundSource* se = NewGO<SoundSource>(4);
		se->Init(2);
		se->SetVolume(3.5f);
		se->Play(false);
		//カウントを+1する。
		m_player->m_starCount += 1;
		//☆の削除。
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
	//絵描きさんに座標を教える。
	m_modelRender.SetPosition(m_position);
}

void Star::Rotation()
{
	//回転を加算する。
	m_rotation.AddRotationDegY(2.0f);

	//絵描きさんに回転を教える。
	m_modelRender.SetRotation(m_rotation);
}

void Star::Render(RenderContext& rc)
{
	//描画する。
	m_modelRender.Draw(rc);
}