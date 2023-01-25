#include "Framework.h"
#include "CardManager0120.h"
#include "SichuanCard0120.h"
#include "LineRenderer0120.h"
#include "LineManager0120.h"

const Vector2 CardManager0120::DIRECTION[] = {
	{0.0f, 0.0f},
	{-1.0f, 0.0f},
	{1.0f, 0.0f},
	{0.0f, 1.0f},
	{0.0f, -1.0f}
};

CardManager0120::CardManager0120()
{
	LoadTextures();

	cards.resize(POOL_SIZE);
	for (auto& card : cards) {
		card = new SichuanCard0120(CARD_SIZE);
		card->SetEvent(bind(&CardManager0120::SelectCard, this, card));
	}

	LineManager0120::Get();
}

CardManager0120::~CardManager0120()
{
	for (auto card : cards)
		delete card;
}

void CardManager0120::Update()
{
	for (auto card : cards)
		card->Update();
}

void CardManager0120::SelectUpdate()
{
	if (select1 != nullptr && select2 != nullptr) {
		if (Pairing(select1, select2)) {
			if (matchFunc != nullptr)
				matchFunc();
			select1->Kill();
			select2->Kill();
		}

		select1->SetSelected(false);
		select1 = nullptr;
		select2->SetSelected(false);
		select2 = nullptr;
	}
}

void CardManager0120::SelectCard(void* card)
{
	auto* clickedCard = (SichuanCard0120*)card;
	if (clickedCard == nullptr)
		return;

	if (!clickedCard->Active())
		return;

	if (select1 == nullptr) {
		select1 = clickedCard;
		select1->SetSelected(true);
		return;
	}
	else if (select1 == clickedCard) {
		select1->SetSelected(false);
		select1 = nullptr;
		return;
	}
	else if(select2 == nullptr) {
		select2 = clickedCard;
		select2->SetSelected(true);

		return;
	}
}

void CardManager0120::Render()
{
	for (auto card : cards)
		card->Render();
}

void CardManager0120::InitTable(int num)
{
	select1 = nullptr;
	select2 = nullptr;

	num = min(POOL_SIZE, num);
	num = num / 2 * 2;

	vector<int> indices(num);
	for (int i = 0; i < num; i += 2) {
		indices[i] = indices[i + 1] = Random(0, (int)cardTextures.size());
	}

	vector<vector<bool>> table(TABLE_Y, vector<bool>(TABLE_X));
	int nextX = 0, nextY = 0;

	Vector2 center = { CENTER_X, CENTER_Y };

	for (int i = 0; i < indices.size(); i += 2) {
		while (table[nextY][nextX]) {
			if (++nextY >= TABLE_Y) {
				nextX++;
				nextY = 0;
			}
		}

		wstring file = cardTextures[indices[i]];
		cards[i]->Init(indices[i], { CARD_SIZE.x * nextX, CARD_SIZE.y * nextY }, file);
		table[nextY][nextX] = true;
		cards[i]->Pos() += center;

		auto point = SearchSetablePoint(table, nextX, nextY);

		cards[i + 1]->Init(indices[i + 1], CARD_SIZE * Vector2((float)point.first, (float)point.second), file);
		cards[i + 1]->Pos() += center;
	}

	for (int i = indices.size(); i < cards.size(); i++)
		cards[i]->SetActive(false);
}

void CardManager0120::SetMatchFunc(function<void()> event) {
	matchFunc = event; 
}

pair<int, int> CardManager0120::SearchSetablePoint(vector<vector<bool>>& table, int x, int y)
{
	vector<pair<int, int>> points;
	//��ġ ������ ��ġ�� ã�´�
	for (int y = 0; y < table.size(); y++) {
		for (int x = 0; x < table[y].size(); x++) {
			if (!table[y][x])
				points.push_back({ x, y });
		}
	}

	//������ �ִ�
	//���� ��ġ ������ ��ġ��� �� ���ٰ� ���� ������ Ǯ �� ���� ������ �� ���� �ִ�



	//���� �� �ִ� ��ġ�� ����
	if (points.empty())
		return { -1, -1 };

	//ã�� ��ġ�� �� �ϳ��� ��� ����
	auto& select = points[Random(0, (int)points.size())];
	table[select.second][select.first] = true;
	return select;
}

void CardManager0120::LoadTextures()
{
	WIN32_FIND_DATA findData;
	HANDLE handle = FindFirstFile(L"Textures/Cards/*png", &findData);

	bool result = true;
	wstring fileName;
	while (result) {
		fileName = L"Textures/Cards/";
		fileName += findData.cFileName;

		cardTextures.push_back(fileName);

		result = FindNextFile(handle, &findData);
	}
}

bool CardManager0120::Pairing(SichuanCard0120* card1, SichuanCard0120* card2)
{
	//���ʿ� ���� �ʴ�
	if (card1->GetIndex() != card2->GetIndex())
		return false;

	//2������
	//CARD_SIZE ��ŭ�� ���ϸ鼭 üũ
	//������� ��Ʈ��ŭ ���ϸ鼭 �߾�� �� �Ŵ�

	 //���� Ƚ��, ���� ��ġ, ���� ����
	priority_queue<PqNode> q;
	//��ġ, ���� Ƚ��, ���� ��ġ
	map<pair<float, float>, pair<int, Vector2>> mp;

	q.push({ 0, card1->GlobalPos(), Vector2() });

	bool result = false;
	Vector2 arrive = {};
	while (!lineQueue.empty())
		lineQueue.clear();

	while (!q.empty()) {
		int curCurved = q.top().curved;
		Vector2 curDir = q.top().direction;
		Vector2 postPos = q.top().postPos;

		Vector2 curPos = postPos + curDir * CARD_SIZE;
		q.pop();

		//���� �ٱ�
		if (curPos.x < 0 || curPos.x > WIN_WIDTH
			|| curPos.y < 0 || curPos.y > WIN_HEIGHT)
			continue;

		//�ʹ� ������ - �� �ɷ��� ���̽�
		if (curCurved > MAX_CURVE)
			continue;

		//�̹� ã�Ҵ� ����̰� �� ���� ��������
		if (mp.count({ curPos.x, curPos.y }) > 0) {
			if (mp[{curPos.x, curPos.y}].first <= curCurved)
				continue;
		}
		mp[{curPos.x, curPos.y}] = { curCurved, postPos };

		//������?
		if (card2->GetCollider()->IsPointCollision(curPos)) {
			result = true;
			arrive = curPos;
			break;
		}
		//������ ���� ������
		bool pass = true;
		for (auto card : cards) {
			if (!card->Active())
				continue;

			pass &= !card->GetCollider()->IsPointCollision(curPos);
			if (!pass)
				break;
		}

		if (!pass)
			continue;

		bool nonDir = curDir.Length() < FLT_EPSILON;
		for (int i = 1; i < 5; i++) {
			int nextCurved = curCurved + 1;
			if (nonDir || (curDir.x == DIRECTION[i].x && curDir.y == DIRECTION[i].y))
				nextCurved--;

			if (nextCurved > MAX_CURVE)
				continue;

			q.push({ nextCurved, curPos, DIRECTION[i] });
		}
	}

	if (result) {
		lineQueue.push_front(arrive);
		Vector2 tracking = { arrive.x, arrive.y };
		while (mp.find({ tracking.x, tracking.y }) != mp.end()) {
			auto post = mp[{tracking.x, tracking.y}].second;
			if(post == tracking)
				break;

			tracking = post;
			lineQueue.push_front(tracking);
		}

		LineManager0120::Get()->Pop()->Set(lineQueue);
	}

	return result;
}
