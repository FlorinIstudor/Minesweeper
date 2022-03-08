#include "Board.h"

Board::Board(sf::Vector2i aSize, sf::Texture* TextVect, int ANB)
{
	Size = aSize;

	firstClick = true;

	isFinished = false;

	nbOfBombs = ANB;

	remainingCells = Size.x * Size.y - nbOfBombs;

	Map = new Cell[Size.x * Size.y];

	TEXTURES = TextVect;

	sizeOfCell = Map->getShape().getSize().x;

	int rand_x;

	for (int i = 0; i < Size.x * Size.y; i++)
	{
		(Map + i)->SetType(CellType::Empty);
		(Map + i)->SetTexture(TextVect);
	}

}

void Board::GenerateBoard(int index)
{
	int rand_x;
	int cor = 1;

	for (int i = 0; i < Size.x * Size.y; i++)
	{
		rand_x = rand() % 100;

		if (i == index)
		{
			cor = 0;
		}

		if ((rand_x >= 100 * nbOfBombs / (Size.x * Size.y - i - cor)) || i == index)
		{
			(Map + i)->SetType(CellType::Empty);
		}

		else
		{
			(Map + i)->SetType(CellType::Bomb);
			nbOfBombs--;
		}
	}

	int surrBombs;

	//MIDDLE

	for (int i = 1; i < Size.x - 1; i++)
	{
		for (int j = 1; j < Size.y - 1; j++)
		{
			if ((Map + i * Size.y + j)->getType() != CellType::Bomb)
			{
				surrBombs = 0;
				for (int k = 0; k < 3; k++)
				{
					if ((Map + (i - 1) * Size.y + j - 1 + k)->getType() == CellType::Bomb)
						surrBombs++;

					if ((Map + (i + 1) * Size.y + j - 1 + k)->getType() == CellType::Bomb)
						surrBombs++;
				}

				if ((Map + i * Size.y + j - 1)->getType() == CellType::Bomb)
					surrBombs++;

				if ((Map + i * Size.y + j + 1)->getType() == CellType::Bomb)
					surrBombs++;

				(Map + i * Size.y + j)->SetType(CellType(surrBombs));
			}
		}
	}

	//UPMOST AND LOWERMOST LINES

	for (int j = 1; j < Size.y - 1; j++)
	{
		if ((Map + j)->getType() != CellType::Bomb)
		{
			surrBombs = 0;

			if ((Map + j - 1)->getType() == CellType::Bomb)
				surrBombs++;

			if ((Map + j + 1)->getType() == CellType::Bomb)
				surrBombs++;

			for (int k = 0; k < 3; k++)
			{
				if ((Map + Size.y + j - 1 + k)->getType() == CellType::Bomb)
					surrBombs++;
			}

			(Map + j)->SetType(CellType(surrBombs));
		}

		if ((Map + (Size.x - 1) * Size.y + j)->getType() != CellType::Bomb)
		{
			surrBombs = 0;

			if ((Map + (Size.x - 1) * Size.y + j - 1)->getType() == CellType::Bomb)
				surrBombs++;

			if ((Map + (Size.x - 1) * Size.y + j + 1)->getType() == CellType::Bomb)
				surrBombs++;

			for (int k = 0; k < 3; k++)
			{
				if ((Map + (Size.x - 2) * Size.y + j - 1 + k)->getType() == CellType::Bomb)
					surrBombs++;
			}

			(Map + (Size.x - 1) * Size.y + j)->SetType(CellType(surrBombs));
		}
	}

	//LEFTMOST AND RIGHTMOST COLUMNS

	for (int i = 1; i < Size.x - 1; i++)
	{
		if ((Map + Size.y * i)->getType() != CellType::Bomb)
		{
			surrBombs = 0;

			if ((Map + Size.y * (i - 1))->getType() == CellType::Bomb)
				surrBombs++;

			if ((Map + Size.y * (i + 1))->getType() == CellType::Bomb)
				surrBombs++;

			for (int k = 0; k < 3; k++)
			{
				if ((Map + (i - 1 + k) * Size.y + 1)->getType() == CellType::Bomb)
					surrBombs++;
			}

			(Map + Size.y * i)->SetType(CellType(surrBombs));
		}

		if ((Map + Size.y * (i + 1) - 1)->getType() != CellType::Bomb)
		{
			surrBombs = 0;

			if ((Map + Size.y * i - 1)->getType() == CellType::Bomb)
				surrBombs++;

			if ((Map + Size.y * (i + 2) - 1)->getType() == CellType::Bomb)
				surrBombs++;

			for (int k = 0; k < 3; k++)
			{
				if ((Map + Size.y * (i + k) - 2)->getType() == CellType::Bomb)
					surrBombs++;
			}

			(Map + Size.y * (i + 1) - 1)->SetType(CellType(surrBombs));
		}
	}

	//CORNERS

	if ((Map)->getType() != CellType::Bomb)
	{
		surrBombs = 0;

		if ((Map + 1)->getType() == CellType::Bomb)
			surrBombs++;
		if ((Map + Size.y)->getType() == CellType::Bomb)
			surrBombs++;
		if ((Map + Size.y + 1)->getType() == CellType::Bomb)
			surrBombs++;

		(Map)->SetType(CellType(surrBombs));
	}

	if ((Map + Size.y - 1)->getType() != CellType::Bomb)
	{
		surrBombs = 0;

		if ((Map + Size.y - 2)->getType() == CellType::Bomb)
			surrBombs++;
		if ((Map + 2 * Size.y - 1)->getType() == CellType::Bomb)
			surrBombs++;
		if ((Map + 2 * Size.y - 2)->getType() == CellType::Bomb)
			surrBombs++;

		(Map + Size.y - 1)->SetType(CellType(surrBombs));
	}

	if ((Map + (Size.x - 1) * Size.y)->getType() != CellType::Bomb)
	{
		surrBombs = 0;

		if ((Map + (Size.x - 1) * Size.y + 1)->getType() == CellType::Bomb)
			surrBombs++;
		if ((Map + (Size.x - 2) * Size.y + 1)->getType() == CellType::Bomb)
			surrBombs++;
		if ((Map + (Size.x - 2) * Size.y)->getType() == CellType::Bomb)
			surrBombs++;

		(Map + (Size.x - 1) * Size.y)->SetType(CellType(surrBombs));
	}

	if ((Map + Size.x * Size.y - 1)->getType() != CellType::Bomb)
	{
		surrBombs = 0;

		if ((Map + Size.x * Size.y - 2)->getType() == CellType::Bomb)
			surrBombs++;
		if ((Map + (Size.x - 1) * Size.y - 1)->getType() == CellType::Bomb)
			surrBombs++;
		if ((Map + (Size.x - 1) * Size.y - 2)->getType() == CellType::Bomb)
			surrBombs++;

		(Map + Size.y * Size.x - 1)->SetType(CellType(surrBombs));
	}
}

void Board::Draw(sf::RenderWindow& window)
{
	for (int i = 0; i < Size.x * Size.y; i++)
	{
		(Map + i)->Draw(window);
	}
}

void Board::SetPosition(sf::Vector2f Pos)
{
	Position = Pos;

	for (int i = 0; i < Size.x * Size.y; i++)
	{
		(Map + i)->SetPosition(sf::Vector2f(sizeOfCell/2 + (int(i / Size.y)) * sizeOfCell + Pos.x, sizeOfCell / 2 + (i % Size.y) * sizeOfCell + Pos.y));
	}
}

void Board::DB_REVEALALL()
{
	for (int i = 0; i < Size.x* Size.y; i++)
	{
		(Map + i)->Reveal(TEXTURES);
	}
}

void Board::DB_MARKALL()
{
	for (int i = 0; i < Size.x * Size.y; i++)
	{
		(Map + i)->Mark(TEXTURES);
	}
}

void Board::DB_REVEALBYINDEX(int INDEX)
{
	(Map + INDEX)->Reveal(TEXTURES);
}

void Board::DB_UNMARKALL()
{
	for (int i = 0; i < Size.x * Size.y; i++)
	{
		if((Map + i)->getStatus() == 1)
			(Map + i)->Mark(TEXTURES);
	}
}


void Board::Update(sf::RenderWindow& window, sf::Event ev)
{
	if (ev.type == sf::Event::MouseButtonReleased)
	{
		if (GetMouseIndex(window).x >= 0)
		{
			int Index = GetMouseIndex(window).y * Size.y + GetMouseIndex(window).x;

			if (ev.key.code == sf::Mouse::Button::Right)
			{
				(Map + Index)->Mark(TEXTURES);
			}

			if (ev.key.code == sf::Mouse::Button::Left)
			{
				if (firstClick && Index >= 0)
				{
					firstClick = false;

					GenerateBoard(Index);

					OnReveal(Index);

					return;
				}

				if ((Map + Index)->getStatus() == 0)
					OnReveal(Index);
			}

			if (ev.key.code == sf::Mouse::Button::Middle)
			{
				if ((Map + Index)->getStatus() == 2)
				{
					HandlePosition(Index);
				}
			}
		}
	}
}

void Board::OnReveal(int Index)
{
	if ((Map + Index)->getStatus() != 0)
		return;

	remainingCells--;

	(Map + Index)->Reveal(TEXTURES);

	if ((Map + Index)->getType() == CellType::Bomb)
	{
		for (int i = 0; i < Size.x * Size.y; i++)
		{
			if ((Map + i)->getType() != CellType::Bomb && (Map + i)->getStatus() == 1)
			{
				(Map + i)->Mark(TEXTURES);
			}
		}
		DB_REVEALALL();

		return;
	}

	if ((Map + Index)->getType() == CellType::Empty)
	{
		HandlePosition(Index);	
	}

	{
		return;
	}
}

void Board::HandlePosition(int Index)
{
	if (Index == 0) // TOP-LEFT CORNER
	{
		OnReveal(1);
		OnReveal(Size.y);
		OnReveal(Size.y + 1);
		return;
	}

	if (Index == Size.y - 1) // BOTTOM-LEFT CORNER
	{
		OnReveal(Size.y - 2);
		OnReveal(2 * Size.y - 1);
		OnReveal(2 * Size.y - 2);
		return;
	}

	if (Index == Size.y * (Size.x - 1)) // TOP-RIGHT CORNER
	{
		OnReveal(Size.y * (Size.x - 2));
		OnReveal(Size.y * (Size.x - 2) + 1);
		OnReveal(Size.y * (Size.x - 1) + 1);
		return;
	}

	if (Index == Size.y * Size.x - 1) // BOTTOM-RIGHT CORNER
	{
		OnReveal(Size.y * Size.x - 2);
		OnReveal(Size.y * (Size.x - 1) - 1);
		OnReveal(Size.y * (Size.x - 1) - 2);
		return;
	}

	if (Index % Size.y == 0) // UPPERSIDE
	{
		OnReveal(Index - Size.y);
		OnReveal(Index + Size.y);
		OnReveal(Index + 1);
		OnReveal(Index - Size.y + 1);
		OnReveal(Index + Size.y + 1);
		return;
	}

	if ((Index + 1) % Size.y == 0) // UNDERSIDE
	{
		OnReveal(Index - 1);
		OnReveal(Index - Size.y);
		OnReveal(Index + Size.y);
		OnReveal(Index - Size.y - 1);
		OnReveal(Index + Size.y - 1);
		return;
	}

	if (Index < Size.y) // LEFTSIDE
	{
		OnReveal(Index - 1);
		OnReveal(Index + 1);
		OnReveal(Index + Size.y - 1);
		OnReveal(Index + Size.y);
		OnReveal(Index + Size.y + 1);
		return;
	}

	if (Index >= (Size.x - 1) * Size.y) // RIGHTSIDE
	{
		OnReveal(Index - 1);
		OnReveal(Index + 1);
		OnReveal(Index - Size.y);
		OnReveal(Index - Size.y - 1);
		OnReveal(Index - Size.y + 1);
		return;
	}

	OnReveal(Index + 1); // MIDDLE
	OnReveal(Index - 1);
	OnReveal(Index - Size.y - 1);
	OnReveal(Index - Size.y);
	OnReveal(Index - Size.y + 1);
	OnReveal(Index + Size.y - 1);
	OnReveal(Index + Size.y);
	OnReveal(Index + Size.y + 1);

	return;
}

sf::Vector2i Board::GetMouseIndex(sf::RenderWindow &window)
{
	if (sf::Mouse::getPosition(window).x < Position.x || sf::Mouse::getPosition(window).y < Position.y ||
		sf::Mouse::getPosition(window).x > Position.x + Size.x * sizeOfCell || sf::Mouse::getPosition(window).y > Position.y + Size.y * sizeOfCell)
		return sf::Vector2i(-1, -1);
	else
	{
		sf::Vector2f ABSpos;
		ABSpos = sf::Vector2f(sf::Mouse::getPosition(window).x - Position.x, sf::Mouse::getPosition(window).y - Position.y);
		return sf::Vector2i(int(ABSpos.y / sizeOfCell), int(ABSpos.x / sizeOfCell));
	}
}

Board::~Board()
{
	delete[] Map;
}
