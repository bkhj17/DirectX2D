#pragma once

class AnimTransform0117 : public Transform
{
public:
	AnimTransform0117();
	virtual ~AnimTransform0117();

	void Update();
	void Render();

protected:
	virtual void LoadClips() = 0;
	void LoadClip(int type, string path, string file, bool isLoop, float speed);

	void SetClipEvent();

protected:
	//Ư�� ������ ���� �� �̺�Ʈ �߻�?

	map<int, Clip*> clips;
	Clip* curClip = nullptr;
private:
	VertexShader* vertexShader;
	PixelShader* pixelShader;

	MatrixBuffer* worldBuffer;

};

