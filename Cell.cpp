#include "Cell.h"

Cell::Cell(CellType aT, float ACS)
{
	CellSize = ACS;
	Type = aT;

	isRevealed = false;
	isMarked = false;

	Shape = sf::RectangleShape(sf::Vector2f(CellSize, CellSize));
	Shape.setOrigin(sf::Vector2f(CellSize / 2, CellSize / 2));
}

Cell::~Cell()
{
}

void Cell::Reveal(sf::Texture* TextVect)
{
	if (isMarked)
		return;

	if (!isRevealed)
	{
		isRevealed = true;
		this->SetTexture(TextVect + 2 + int(Type));
	}
}

void Cell::SetTexture(sf::Texture* Texture)
{
	Shape.setTexture(Texture);
}

void Cell::Mark(sf::Texture* TextVect)
{
	if (isRevealed)
		return;

	if (isMarked)
	{
		isMarked = false;
		this->SetTexture(TextVect + 0);
	}

	else
	{
		isMarked = true;
		this->SetTexture(TextVect + 1);
	}
}

void Cell::SetType(CellType TP)
{
	Type = TP;
}

void Cell::Draw(sf::RenderWindow &window)
{
	window.draw(this->Shape);
}

void Cell::SetPosition(sf::Vector2f Pos)
{
	Shape.setPosition(Pos);
}

sf::RectangleShape Cell::getShape()
{
	return Shape;
}

void Cell::SetColor(sf::Color col)
{
	Shape.setFillColor(col);
}

int Cell::getStatus()
{
	if (isRevealed)
		return 2;

	if (isMarked)
		return 1;

	return 0;
}

CellType Cell::getType()
{
	return Type;
}