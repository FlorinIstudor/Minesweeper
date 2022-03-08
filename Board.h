#pragma once
#include "Cell.h"

class Board
{
protected:
	
	sf::Vector2i Size;

	Cell* Map;

	sf::Vector2f Position;

	int nbOfBombs;

	bool firstClick;

	bool isFinished;

	int sizeOfCell;

	int remainingCells;

	sf::Texture* TEXTURES;

public:

	Board(sf::Vector2i aSize, sf::Texture* TextVect, int ANB);

	void Draw(sf::RenderWindow &window);

	void SetPosition(sf::Vector2f Pos);

	void DB_REVEALALL();

	void DB_MARKALL();

	void DB_REVEALBYINDEX(int INDEX);

	void Update(sf::RenderWindow& window, sf::Event ev);

	~Board();

private:

	void DB_UNMARKALL();

	void GenerateBoard(int index);

	void OnReveal(int Index);

	void HandlePosition(int Index);

	sf::Vector2i GetMouseIndex(sf::RenderWindow& window);

};