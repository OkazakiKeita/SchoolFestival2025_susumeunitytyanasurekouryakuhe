#include "stdafx.h"
#include "GameClear.h"
#include "Title.h"
#include "Game.h"
#include "Star.h"
#include "GameCamera.h"

GameClear::GameClear()
{
	//ゲームクリア画面を読み込む。
	m_spriteRender.Init("Assets/sprite/Gameclear.dds", 1920.0f, 1080.0f);
	//wchar_t infoText[256];
	//swprintf_s(infoText, 256, L" %d秒\n %d/9", (int)m_clearTime, m_starCount);

	//m_fontRender.SetText(infoText);
	//m_fontRender.SetPosition({ -300.0f, -200.0f, 0.0f }); // 好きな位置に
	//m_fontRender.SetColor(g_vec4White);
}
GameClear::~GameClear()
{

}

//更新処理。
void GameClear::Update()
{
	if(g_pad[0]->IsTrigger(enButtonA))
	{
		DeleteGO(this);
		NewGO<Title>(0, "title");
	}
}

void GameClear::Initialize(float clearTime, int starCount)
{
	wchar_t infoText[256];
	swprintf_s(infoText, 256, L" %d/9\n\n %d秒", starCount, (int)clearTime);

	m_fontRender.SetText(infoText);
	m_fontRender.SetPosition({ 380.0f, 0.0f, 0.0f }); // 好きな位置に
	m_fontRender.SetColor(g_vec4Black);
	m_fontRender.SetScale(2.0f);
}

//描画処理。
void GameClear::Render(RenderContext& rc)
{
	m_spriteRender.Draw(rc);
	m_fontRender.Draw(rc);
}