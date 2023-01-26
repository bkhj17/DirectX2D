#pragma once

class TileScene : public Scene
{
private:
	const float SAMPLE_SIZE = 50.0f;

public:
	TileScene();
	~TileScene();

	// Scene��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

private:
	void ClickSampleBtn(void* sampleBtn);

	void CreateSample();

private:
	vector<Button*> sampleBtns;
	EditTileMap* editTileMap;

	Quad* selectSample = nullptr;
};

