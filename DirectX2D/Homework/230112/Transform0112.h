#pragma once
class Transform0112
{
public:
	Transform0112();
	~Transform0112();


	Vector2 pos = {};				//��ǥ
	Vector2 scale = { 1.0f, 1.0f };	//����
	float angle = 0.0f;				//ȸ��

	Matrix GetWorldMatrix();
	void Set();
private:
	MatrixBuffer* worldBuffer;
};

