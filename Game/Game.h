#pragma once
#include "sound/SoundSource.h"

#include "Level3DRender/LevelRender.h"

class Player;
class BackGround;
class GameCamera;


class Game : public IGameObject
{
public:
	Game();
	~Game();
	void Update();
	void Render(RenderContext& rc);	
	Player* m_player;
	Vector3 m_starPosition;
	GameCamera* m_gameCamera;
	BackGround* m_backGround;
	SoundSource* m_BGM;
	FontRender m_fontRender;
	FontRender m_timeRender;
	FontRender m_starRender;
	FontRender m_endRender;
	float m_time = 60.0f;
};

