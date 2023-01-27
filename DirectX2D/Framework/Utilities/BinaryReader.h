#pragma once
class BinaryReader
{
public:
	BinaryReader(string filePath);
	BinaryReader(wstring filePath);
	~BinaryReader();

	int Int();
	UINT UInt();
	float Float();
	string String();
	wstring WString();

	void Byte(void** data, UINT dataSize);

	bool IsFailed() { return file == INVALID_HANDLE_VALUE;	}
private:
	HANDLE file = nullptr;
	DWORD size = 0;
};

