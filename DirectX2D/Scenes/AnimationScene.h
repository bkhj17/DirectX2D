#pragma once

class AnimationScene :
    public Scene
{
public:
    AnimationScene();
    ~AnimationScene();

    // Scene��(��) ���� ��ӵ�
    virtual void Update() override;
    virtual void Render() override;
    virtual void PostRender() override;
private:
    Ninja* ninja;

};

