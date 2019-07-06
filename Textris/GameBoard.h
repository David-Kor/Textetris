#ifndef _GAMEBOARD_CLASS
#define _GAMEBOARD_CLASS

class GameBoard
{
private:
	const int MAX_VER_SIZE = 20, MAX_HOR_SIZE = 10;

	std::wstring mv_strBoard[20];
	std::wstring mv_strMargin[2];

public:
	enum BoardType {BLOCK = L'¡á', EMPTY = L'¡¡'};

	GameBoard();
	~GameBoard();
};

#endif