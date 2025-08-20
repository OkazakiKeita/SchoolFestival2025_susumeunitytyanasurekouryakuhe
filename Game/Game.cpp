#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "GameCamera.h"
#include "BackGround.h"
#include "Star.h"
#include "sound/SoundEngine.h"
#include "GameClear.h"
#include "GameOver.h"
#include "Title.h"

Game::Game()
{
	//プレイヤーオブジェクトを作る。
	m_player = NewGO<Player>(0, "player");

	//ゲームカメラのオブジェクトを作る。
	m_gameCamera = NewGO<GameCamera>(0, "gamecamera");

	//背景のオブジェクトを作る。
	m_backGround = NewGO<BackGround>(0, "BackGround");

	//Starクラスのオブジェクトを作る。
	Star*star1 = NewGO<Star>(0, "star");
	star1->m_position = { 0.0f,-280.0f,3350.0f };

	Star* star2 = NewGO<Star>(0, "star");
	star2->m_position = { 707.0f,150.0f,2500.0f };

	Star* star3 = NewGO<Star>(0, "star");
	star3->m_position = { 100.0f,150.0f,2000.0f };

	Star* star4 = NewGO<Star>(0, "star");
	star4->m_position = { 0.0f,-600.0f,100.0f };

	Star* star5 = NewGO<Star>(0, "star");
	star5->m_position = { 0.0f,40.0f,-450.0f };

	Star* star6 = NewGO<Star>(0, "star");
	star6->m_position = { 0.0f,400.0f,-1850.0f };

	Star* star7 = NewGO<Star>(0, "star");
	star7->m_position = { 0.0f,1000.0f,-2450.0f };

	Star* star8 = NewGO<Star>(0, "star");
	star8->m_position = { 350.0f,1200.0f,-2550.0f };

	Star* star9 = NewGO<Star>(0, "star");
	star9->m_position = { -350.0f,1200.0f,-2550.0f };

	//文字の出力
	m_fontRender.SetText(L"Aボタンでジャンプ");
	m_fontRender.SetPosition({ -200.0f,-450.0f,0.0f });
	m_fontRender.SetColor(g_vec4White);

	//BGM読み込み。
	g_soundEngine->ResistWaveFileBank(1, "Assets/sound/BGM.wav");
	//BGMを再生。
	m_BGM = NewGO<SoundSource>(1);
	m_BGM->Init(1);
	m_BGM->Play(true);
}

Game::~Game()
{
	//プレイヤーの削除。
	DeleteGO(m_player);
	//ゲームカメラの削除。
	DeleteGO(m_gameCamera);
	//背景の削除。
	DeleteGO(m_backGround);
	//BGMの削除。
	DeleteGO(m_BGM);
}

void Game::Update()
{
	m_time -= g_gameTime->GetFrameDeltaTime();
	int sec = (int)m_time;

	//wchar_tは日本語や多言語に対応させる。
	//制限時間。
	wchar_t text[256];
	swprintf_s(text, 256, L"残り:%03d秒", sec);
	m_timeRender.SetText(text);
	m_timeRender.SetPosition({ 700.0f,500.0f,0.0f });
	m_timeRender.SetColor(g_vec4Black);

	if (m_time < 0)
	{
		NewGO<GameOver>(0, "gameover");
		DeleteGO(this);
	}

	//とった☆の数。
	char text2[256];
	sprintf_s(text2, sizeof(text2), "Star: %d/9", m_player->m_starCount);
	wchar_t wtext[256];
	//mbstowcsはcharをワイド文字列wcher_tに変換する関数。
	mbstowcs(wtext, text2, 256);
	m_starRender.SetText(wtext);
	m_starRender.SetPosition({ -80.0f, 500.0f, 0.0f }); // 位置は自由に調整
	m_starRender.SetColor(g_vec4Yellow);

	if (m_player->m_position.y >= 1200.0f && m_player->m_position.z <= -3250.0f)
	{
		auto gc = NewGO<GameClear>(0, "gameclear");
		gc->Initialize(m_time, m_player->m_starCount);
		DeleteGO(this);
		return;
	}
}

void Game::Render(RenderContext& rc)
{
	m_fontRender.Draw(rc);
	m_timeRender.Draw(rc);
	m_starRender.Draw(rc);
}
