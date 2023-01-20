#pragma once
class PuzzleScene : public Scene
{
public:
    PuzzleScene();
    ~PuzzleScene();

    // Scene��(��) ���� ��ӵ�
    virtual void Update() override;
    virtual void Render() override;
    virtual void PostRender() override;

private:
    void LoadTextures();

private:
    vector<wstring> cardTextures;

    Button* button;
};

