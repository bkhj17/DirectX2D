#include "Framework.h"
#include "GameTileMap.h"

GameTileMap::GameTileMap(string file)
{
	Pos() = { 80.0f, 80.0f };
	UpdateWorld();

	Load(file);

}

GameTileMap::~GameTileMap()
{
	for (auto tile : bgTiles)
		delete tile;

	for (auto tile : objTiles)
		delete tile;
}

void GameTileMap::Render()
{
	for (auto tile : bgTiles)
		tile->Render();

	for (auto tile : objTiles)
		tile->Render();
}

void GameTileMap::PushObject(Collider* collider)
{
	for (auto tile : objTiles)
		tile->GetCollider()->PushCollider(collider);
}

void GameTileMap::Load(string file)
{
	BinaryReader* reader = new BinaryReader(file);

	width = reader->UInt();
	height = reader->UInt();

	UINT size = reader->UInt();
	bgTiles.resize(size);

	for (auto& tile : bgTiles) {
		Tile::Data data;
		data.textureFile = reader->WString();
		data.pos.x = reader->Float();
		data.pos.y = reader->Float();
		data.angle = reader->Float();
		data.type = (Tile::Type)reader->Int();

		tile = new Quad(data.textureFile);
		tile->Pos() = data.pos;
		tile->Rot().z = data.angle;
		tile->SetParent(this);
		tile->UpdateWorld();
	}

	size = reader->UInt();
	objTiles.resize(size);
	for (auto& tile : objTiles) {
		Tile::Data data;
		data.textureFile = reader->WString();
		data.pos.x = reader->Float();
		data.pos.y = reader->Float();
		data.angle = reader->Float();
		data.type = (Tile::Type)reader->Int();

		tile = new Tile(data);
		tile->SetParent(this);
		tile->Update();
	}

	delete reader;


	tileSize = bgTiles[0]->GetSize();
}
