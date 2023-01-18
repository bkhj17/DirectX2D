#pragma once
class Action
{
protected:
	const float GRAVITY = 980.0f;
	const float FLOOR_HEIGHT = 200.0f;
	const float MOVE_SPEED = 100.0f;
public:
	Action(string path, string file, bool isLoop, float speed = 1.0f);
	virtual ~Action();

	virtual void Update();
	virtual void Render();

	virtual void Start();
	virtual void End() {}

	void SetEvent(Event event) { this->event = event; }

	bool IsPlaying() { return clip->IsPlay(); }
private:
	void LoadClip(string path, string file, bool isLoop, float speed);

protected:
	Clip* clip;

	Event event;
};

