#pragma once
class CollisionScene : public Scene
{
public:
	CollisionScene();
	~CollisionScene();

	// Scene��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

private:
	//OBB�浹 : ȸ�� �� ��ü�� ������ �浹

	vector<Collider*> colliders;

};

