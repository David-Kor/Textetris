#ifndef _GAMEBOARD_CLASS
#define _GAMEBOARD_CLASS

class GameBoard
{
private:
	int mv_nScore;

	std::wstring mv_wstrBoard[20];
	std::wstring mv_wstrUI[23];

public:
	//보드판 세로길이, 가로길이, 전체 UI 길이
	const short MAX_VER_SIZE = 20, MAX_HOR_SIZE = 10, MAX_UI_LINE = 23;
	enum BoardType { BLOCK = L'■', EMPTY = L'　', WALL = L'▣' };
	struct Blocks
	{
		unsigned char type;
		unsigned char x[4];
		unsigned char y[4];
	};

	GameBoard();
	~GameBoard();

	std::wstring* GetBoard();
	std::wstring* GetUI();
};

#endif