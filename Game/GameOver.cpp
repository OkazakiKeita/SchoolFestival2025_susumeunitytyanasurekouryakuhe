#include "stdafx.h"
#include "GameOver.h"
#include "Title.h"

GameOver::GameOver()
{
	//ゲームオーバー画像を読み込む。
	m_GameOver.Init("Assets/sprite/GameOver.dds", 1920.0f, 1080.0f);
}

GameOver::~GameOver()
{

}

//更新処理。
void GameOver::Update()
{
	//Aボタンが押されたら。
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		//タイトルのオブジェクトを作る。
		NewGO<Title>(0, "title");
		//削除。
		DeleteGO(this);
	}
}

//描画処理。
void GameOver::Render(RenderContext& rc)
{
	m_GameOver.Draw(rc);
}
