#ifndef _GAMEBOARD_CLASS
#define _GAMEBOARD_CLASS

#include "Blocks.h"

class GameBoard
{
private:
	enum BoardType { BLOCK = L'■', EMPTY = L'　', WALL = L'▣' };

	unsigned char mv_ucBoardTable[20][10];	//보드판 세로길이 x 보드판 가로길이
	std::wstring mv_wstrUI[23];
	Blocks* curBlk;		//현재 컨트롤 중인 블록
	Blocks* nxtBlk;		//다음 나올 블록

	const short OUT_OF_INDEX = -2;
	const short CRASH_BLOCK = -1;
	const short NULL_REFERENCE = 0;
	const short SUCCESS = 1;

	void CreateNextBlock();
	short UpdateBlockToBoard();
	void UpdateBoardToUI();

public:
	//보드판 세로길이
	const short MAX_VER_SIZE = 20;
	//보드판 가로길이
	const short MAX_HOR_SIZE = 10;
	//전체 UI 라인 수
	const short MAX_UI_LINE = 23;

	//생성자
	GameBoard();
	//소멸자
	~GameBoard();

	std::wstring* GetUI();
	void BlockRotate();
	void BlockHorMove(short sDirection);
	void BlockDown();
	void DropBlock();
};

#endif