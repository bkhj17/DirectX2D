#pragma once
class TutorialScene : public Scene
{
public:
	TutorialScene();
	~TutorialScene();

	// Scene��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

	void SpawnRect();

private:
	vector<class SpawnPolygon*> polygons;

	float spawnTime, spawnRate; 
};

