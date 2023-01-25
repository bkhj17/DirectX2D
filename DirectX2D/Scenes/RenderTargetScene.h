#pragma once
class RenderTargetScene : public Scene
{
public:
    RenderTargetScene();
    ~RenderTargetScene();

    // Scene��(��) ���� ��ӵ�
    virtual void Update() override;

    virtual void PreRender() override;
    virtual void Render() override;
    virtual void PostRender() override;
private:
    Quad* bg;
    Plane* plane;

    RenderTarget* renderTarget;
    vector<Quad*> renderTextures;

    IntValueBuffer* intValueBuffer;
    FloatValueBuffer* floatValueBuffer;
};

