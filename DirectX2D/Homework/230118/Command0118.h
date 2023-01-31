#pragma once
class Command0118 : public Singleton<Command0118>
{
	//Ŀ�ǵ� �Է���ġ
	//�Է¿� ���� Ŀ�ǵ忡 ���� ��ȣ�� ��ȯ

private:
	friend class Singleton;
	Command0118();
	~Command0118();
public:

	void SetCommand(string sign, vector<UINT>& keys);
	
	void InputCommand(UINT in);

	void PostRender();

	string LastCommand() { return lastCommand; }
	void ClearInputs() { tail = headClips; lastCommand = ""; }
private:
	float waitTime = 0.0f;

private:
	int InputsNum();
	string CheckCommand();


	int headClips = 0;
	int tail = 0;
	vector<UINT> inputs;	//�˻縦 ���� ��ŧ�� ť


private:

	string lastCommand = "";
	unordered_map<string, vector<UINT>> commands;
};

