#include "Framework.h"
#include "Ball0116.h"
#include "Bar0116.h"
#include "Area0116.h"
#include "Block0116.h"

Ball0116::Ball0116(float radius)
	: Quad(Vector2(radius * 2, radius * 2), {}), radius(radius)
{
	SetTexture(L"Textures/Shooting/cursor.png");

	collider = new CircleCollider(radius);
	collider->SetParent(this);
}

Ball0116::~Ball0116()
{
	delete collider;
}

void Ball0116::Update()
{
	ApplyGravity();
	
	if (direction.Length() > speedLimit) {
		direction = direction.GetNormalized() * speedLimit;
	}
	
	Move();

	__super::Update();
	collider->UpdateWorld();
}

void Ball0116::Render()
{
	__super::Render();
	collider->Render();
}

void Ball0116::BarCollision(Bar0116* bar)
{
	//OBB
	if (collider->IsCollision(bar->GetCollider())) {
		//�ݻ纤�� ���� 
		//P = �Ի纤��, n = ��������
		//=> R = P + n * 2 * Dot(-P, n)
		direction = bar->Up() * 2 * Dot(direction * -1.0f, bar->Up());
		Pos() += bar->Up() * radius;			//radius�� �ϸ� �����浹 �Ͼ 
	}
}

void Ball0116::AreaCollision(Area0116* area)
{
	auto leftTop = area->LeftTop();
	auto rightBottom = area->RightBottom();

	if (Pos().x - collider->Radius() < leftTop.x) {
		Pos().x = leftTop.x + collider->Radius();
		direction.x *= -1.0f;
	}

	if (Pos().x + collider->Radius() > rightBottom.x) {
		Pos().x = rightBottom.x - collider->Radius();
		direction.x *= -1.0f;
	}

	if(Pos().y + collider->Radius() > leftTop.y) {
		Pos().y = leftTop.y - collider->Radius();
		direction.y *= -1.0f;
	}
}

void Ball0116::BlockCollision(Block0116* block)
{
	//AABB
	if (collider->IsCollision(block->GetCollider())) {
		block->Break();

		auto rectCollider = (RectCollider*)block->GetCollider();
		float l = rectCollider->L();
		float r = rectCollider->R();
		float t = rectCollider->T();
		float b = rectCollider->B();

		float back = radius + 5.0f;

		if (Pos().y < b && Pos().y + radius > b) {
			//�Ʒ�����
			Pos().y = b - back;
			direction.y *= -1.0f;
		}
		if (Pos().y > t && Pos().y - radius < t) {
			//������
			Pos().y = t + back;
			direction.y *= -1.0f;
		}
		if (Pos().x < l && Pos().x + radius > l) {
			//���ʿ���
			Pos().x = l - back;
			direction.x *= -1.0f;
		}
		if (Pos().x > r && Pos().y - radius < r) {
			//�����ʿ���
			Pos().x = r + back;
			direction.x *= -1.0f;
		}
	}
}

void Ball0116::ApplyGravity()
{
	direction.y -= 9.8f * DELTA;
}

void Ball0116::Move()
{
	Pos() += direction * DELTA;
}
