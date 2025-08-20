#include "stdafx.h"
#include "Title.h"
#include "Game.h"


Title::Title()
{
	//画像を読み込む。
	m_spriteRender.Init("Assets/sprite/title.dds", 1920.0f, 1080.0f);
	//文字出力。
	m_startRender.SetText(L"Aボタンでスタート");
	m_startRender.SetPosition({ 100.0f,-300.0f,0.0f });
	m_startRender.SetColor(g_vec4Black);
}

Title::~Title()
{

}

void Title::Update()
{
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		NewGO<Game>(0,"game");
		DeleteGO(this);
	}
}

void Title::Render(RenderContext& rc)
{
	//画像を描画する。
	m_spriteRender.Draw(rc);
	m_startRender.Draw(rc);
}