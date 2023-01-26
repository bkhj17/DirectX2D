#pragma once

// ��Ʋ ��Ƽ

class Scene0126 : public Scene
{
public:
	Scene0126();
	~Scene0126();

	// Scene��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

private:
	void LoadMap(wstring file);


private:
	UINT width = 0, height = 0;

	vector<Quad*> bgTiles;

	vector<class Object0126*> objects;

	Vector2 offset = { 80.0f, 80.0f };
};

