#ifndef _GAMEBOARD_CLASS
#define _GAMEBOARD_CLASS

#include "Blocks.h"

class GameBoard
{
private:
	enum BoardType { BLOCK = L'■', EMPTY = L'　', WALL = L'▣' };

	unsigned int mv_unBoardTable[20][10];	//보드판 세로길이 x 보드판 가로길이
	std::wstring mv_wstrUI[23];	//UI 텍스트
	Blocks* curBlk;		//현재 컨트롤 중인 블록
	Blocks* nxtBlk;		//다음 나올 블록

	const int OUT_OF_INDEX = -2;
	const int CRASH_BLOCK = -1;
	const int NULL_REFERENCE = 0;
	const int SUCCESS = 1;

	void CreateNextBlock();
	int UpdateBlockToBoard();
	void UpdateBoardToUI();

public:
	//보드판 세로길이
	const int MAX_VER_SIZE = 20;
	//보드판 가로길이
	const int MAX_HOR_SIZE = 10;
	//전체 UI 라인 수
	const int MAX_UI_LINE = 23;
	bool isGameOver;

	//생성자
	GameBoard();
	//소멸자
	~GameBoard();

	std::wstring* GetUI();
	void BlockRotate();
	void BlockHorMove(int nDirection);
	void BlockDown();
	void DropBlock();
};

#endif