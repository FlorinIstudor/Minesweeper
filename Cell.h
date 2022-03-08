#pragma once

#include "Utilities.h"

class Cell
{
protected:

	bool isRevealed;

	float alfa;

	bool isMarked;

	float CellSize;

	CellType Type;

	sf::RectangleShape Shape;

public:

	Cell(CellType aT = CellType::Empty, float ACS = 40.f);

	~Cell();

	void Reveal(sf::Texture* TextVect);

	void SetTexture(sf::Texture* Texture);

	void Mark(sf::Texture* TextVect);

	void SetPosition(sf::Vector2f Pos);

	void SetType(CellType TP);

	void Draw(sf::RenderWindow &window);

	void SetColor(sf::Color col);

	CellType getType();

	int getStatus();

	sf::RectangleShape getShape();
};