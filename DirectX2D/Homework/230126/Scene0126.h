#pragma once

// ��Ʋ ��Ƽ

class Scene0126 : public Scene
{
private:
	const int MAX_SPAWN_ENEMY = 3;

	enum GameState {
		PLAY,
		CLEAR,
		GAME_OVER
	};
public:
	Scene0126();
	~Scene0126();

	// Scene��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

private:
	void UpdatePlay();

	void EnemySpawn();
	void PlayerSpawn();
	void BreakEnemy();
	void BreakPlayer();
	void Win();
	void GameOver();
private:
	GameState state = PLAY;

	class TileMap0126* gameTileMap;
	Tank* tank;

	vector<class EnemyTank0126*> enemies;
	int enemyNum = 15;
	int spawnEnemy = 0;
	
	float spawnRate = 3.0f;
	float enemySpawnTime = 0.0f;
	float playerSpawnTime = 0.0f;

	Quad* gameOver;
	Quad* gameClear;
};

