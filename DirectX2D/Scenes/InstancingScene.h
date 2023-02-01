#pragma once

class InstancingScene : public Scene
{
private:
	UINT SIZE = 2000;

	struct InstanceData {
		Matrix transform;

		Vector2 maxFrame;
		Vector2 curFrame;
	};

public:
	InstancingScene();
	~InstancingScene();

	// Scene��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

private:
	//vector<Quad*> quads;

	Quad* quad;

	vector<InstanceData> instances;
	VertexBuffer* instanceBuffer;
};

