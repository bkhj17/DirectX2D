#pragma once

class Scene0118 : public Scene
{
public:
	Scene0118();
	~Scene0118();

	// Scene��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

private:
	class Robot0118* robot;
	class Dummy0118* dummy;
};

