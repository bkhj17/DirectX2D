#pragma once
class Robot0118 : public GameObject
{
protected:
	enum ActionType {
		IDLE = 0, RUN,
		JUMP_UP = 10, JUMP_DOWN,
		MELEE = 20, SHOOT,
		JUMP_MELEE, JUMP_SHOOT,
		SPECIAL_SHOOT
	};
public:
	Robot0118();
	~Robot0118();

	virtual void Update();
	virtual void Render();
protected:
	void CreateActions();
	void CreateCommands();

	void Control();
	void SpecialShoot();

	void Move();
	void Attack();
	void Jump();

	void InputCommand();
	void SetAction(ActionType type);
protected:
	map<ActionType, Action*> actions;
	ActionType curAction = IDLE;
};

