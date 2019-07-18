#ifndef _GAMEBOARD_CLASS
#define _GAMEBOARD_CLASS

#include "Blocks.h"

class GameBoard
{
private:
	enum BoardType { BLOCK = L'■', EMPTY = L'　', WALL = L'▣' };

	unsigned char mv_ucBoardTable[20][10];	//보드판 세로길이 x 보드판 가로길이
	std::wstring mv_wstrUI[23];

	Blocks* curBlk;
	Blocks* nxtBlk;

	void CreateNextBlock();
	void UpdateBoard();

public:
	//보드판 세로길이
	const short MAX_VER_SIZE = 20;
	//보드판 가로길이
	const short MAX_HOR_SIZE = 10;
	//전체 UI 라인 수
	const short MAX_UI_LINE = 23;
	//(삭제예정)보이지 않는 공간 수 -> 이 수보다 작은 Y값은 보드 화면상에 나타나지 않음
	//const short MARGIN_BOARD = 2;

	//생성자
	GameBoard();
	//소멸자
	~GameBoard();

	std::wstring* GetUI();
	void RotateBlock();
	void MoveBlock(short sDirection);
	void DropBlock();
};

#endif