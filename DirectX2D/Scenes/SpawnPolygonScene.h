#pragma once

class SpawnPolygonScene :
    public Scene
{
public:
    SpawnPolygonScene();
    ~SpawnPolygonScene();
    // Scene��(��) ���� ��ӵ�
    virtual void Update() override;
    virtual void Render() override;
    virtual void PostRender() override;

    void Spawn();
private:
    float spawnTime = 0.0f;

    vector<SpawnPolygon*> polygons;
};

