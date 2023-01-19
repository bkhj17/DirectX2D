#pragma once

class NinjaRun : public Action
{
public:
    NinjaRun(Transform* target);
    NinjaRun(Transform* target, string path, string file);
    ~NinjaRun() = default;

    virtual void Update() override;

private:
    void Control();

private:
    Transform* target;
    float velocity = 0.0f;        
};