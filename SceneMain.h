#pragma once

#include"player.h"
#include"car.h"

class SceneMain
{
public:
	SceneMain();
	virtual ~SceneMain();

	//初期化処理、終了処理

	void init();
	void end();

	//ゲーム処理
	void update();

	//描画
	void draw();

private:
	//グラフィックハンドル
	int m_hPlayer;
	int m_hCar;
	//プレイヤー
	Player m_player;
	//敵
	Car m_car;

};
