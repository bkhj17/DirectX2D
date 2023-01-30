#pragma once

class TankScene : public Scene
{
public:
	TankScene();
	~TankScene();

	virtual void Update() override;
	// Scene��(��) ���� ��ӵ�
	virtual void Render() override;
	virtual void PostRender() override;

private:
	GameTileMap* gameTileMap;
	AStar* astar;
	Tank* tank;
};

