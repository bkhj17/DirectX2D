#include "Framework.h"

Ninja::Ninja()    
{
    Pos() = { CENTER_X, CENTER_Y };

    CreateActions();
    actions[curAction]->Start();

    Observer::Get()->AddIntParamEvent("Action", bind(&Ninja::SetAction2, this, placeholders::_1));
}

Ninja::~Ninja()
{
    for (pair<ActionType, Action*> action : actions)
        delete action.second;
}

void Ninja::Update()
{
    Control();

    actions[curAction]->Update();
    UpdateWorld();
}

void Ninja::Render()
{
    SetRender();

    actions[curAction]->Render();
}

void Ninja::Control()
{
    Move();
    Jump();
    Attack();
    Glide();
}

void Ninja::Move()
{
    if (curAction == JUMP_UP || curAction == JUMP_DOWN) return;
    if (curAction == GLIDE) return;
    if (curAction >= ATTACK) return;

    bool isMove = false;

    isMove |= KEY_PRESS(VK_RIGHT);
    isMove |= KEY_PRESS(VK_LEFT);

    isMove ? SetAction(RUN) : SetAction(IDLE);
}

void Ninja::Jump()
{
    if (curAction >= ATTACK) return;
    if (curAction == GLIDE) return;
    if (curAction == JUMP_UP || curAction == JUMP_DOWN) return;

    if (KEY_DOWN(VK_UP))
        SetAction(JUMP_UP);
}

void Ninja::Attack()
{
    if (curAction >= ATTACK) return;
    if (curAction == GLIDE) return;

    if (KEY_DOWN('A'))
    {
        if (curAction == JUMP_UP || curAction == JUMP_DOWN)
        {
            SetAction(JUMP_ATTACK);
        }
        else
        {
            SetAction(ATTACK);
        }
    }
    
    if (KEY_DOWN('S'))
    {
        if (curAction == JUMP_UP || curAction == JUMP_DOWN)
        {
            SetAction(JUMP_THROW);
        }
        else
        {
            SetAction(THROW);
        }
    }
}

void Ninja::Glide()
{
    if (curAction >= ATTACK) return;
    if (curAction == IDLE || curAction == RUN) return;

    if (KEY_DOWN(VK_DOWN))
        SetAction(GLIDE);

    if (KEY_UP(VK_DOWN))
        SetAction(JUMP_DOWN);
}

void Ninja::SetIdle()
{
    SetAction(IDLE);
}

void Ninja::Fall()
{
    SetAction(JUMP_DOWN);
}

void Ninja::Throw()
{
    SetAction(THROW);
}

void Ninja::SetAction(ActionType type)
{
    if (curAction == type) return;

    curAction = type;
    actions[type]->Start();
}

void Ninja::SetAction2(int type)
{
    SetAction(ActionType(type));
}

void Ninja::CreateActions()
{
    actions[IDLE] = new Action("Textures/Ninja/", "Ninja_Idle.xml", true);
    actions[RUN] = new NinjaRun(this);
    actions[JUMP_UP] = new NinjaJumpUp(this);
    actions[JUMP_UP]->SetEvent(bind(&Ninja::Fall, this));
    actions[JUMP_DOWN] = new NinjaJumpDown(this);
    actions[JUMP_DOWN]->SetEvent(bind(&Ninja::SetIdle, this));
    actions[ATTACK] = new NinjaMeleeAttack(this);
    actions[ATTACK]->SetEvent(bind(&Ninja::SetIdle, this));
    actions[JUMP_ATTACK] = new NinjaJumpAttack(this);
    actions[JUMP_ATTACK]->SetEvent(bind(&Ninja::Fall, this));
    actions[THROW] = new NinjaThrow(this);
    actions[THROW]->SetEvent(bind(&Ninja::SetIdle, this));
    actions[GLIDE] = new NinjaGlide(this);    
}