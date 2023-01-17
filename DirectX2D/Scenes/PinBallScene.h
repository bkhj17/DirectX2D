#pragma once
#include "Scene.h"
class PinBallScene :
    public Scene
{
public:
    PinBallScene();
    ~PinBallScene();

    // Scene��(��) ���� ��ӵ�
    virtual void Update() override;
    virtual void Render() override;
    virtual void PostRender() override;
private:
    void Collision();

private:
    Quad* background;

    Bat* leftBat;
    Bat* rightBat;

    Ball* ball;
};

