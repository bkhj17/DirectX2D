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
	vector<Rect*> rects;

	float spawnTime, spawnRate; 
};

