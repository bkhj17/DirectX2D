#pragma once
class UIScene : public Scene
{
public:
    UIScene();
    ~UIScene();

    // Scene��(��) ���� ��ӵ�
    virtual void Update() override;
    virtual void Render() override;
    virtual void PostRender() override;

private:
    GameTileMap* tileMap;
    Isaac* isaac;

};

