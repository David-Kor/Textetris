#ifndef _GAMEBOARD_CLASS
#define _GAMEBOARD_CLASS

#include "Blocks.h"

class GameBoard
{
private:
	std::wstring mv_wstrUI[23];	//UI 텍스트
	Blocks* curBlk;		//현재 컨트롤 중인 블록
	Blocks* nxtBlk;		//다음 나올 블록
	unsigned int mv_unBoardTable[20][10];	//보드판 세로길이 x 보드판 가로길이

	int mv_nScore;
	float mv_fTime;

	const int OUT_OF_INDEX = -2;
	const int CRASH_BLOCK = -1;
	const int NULL_REFERENCE = 0;
	const int SUCCESS = 1;

	void v_CreateNextBlock();
	int v_UpdateBlockToBoard();
	void v_UpdateBoardToUI();
	void v_UpdateScoreUI();
	void v_CheckFullLine();
	void v_DeleteLine(int nLine, int nCount);

public:
	enum BoardType { BLOCK = L'■', EMPTY = L'　', WALL = L'▣' };
	//보드판 세로길이
	const int MAX_VER_SIZE = 20;
	//보드판 가로길이
	const int MAX_HOR_SIZE = 10;
	//전체 UI 라인 수
	const int MAX_UI_LINE = 23;

	//블록을 끝까지 내렸을 때 획득하는 점수
	const int SCORE_BLOCK_DROP = 10;
	//라인을 다 채웠을 때 1라인당 획득하는 점수
	const int SCORE_LINE_CLEAR = 50;
	bool m_isGameOver;

	//생성자
	GameBoard();
	//소멸자
	~GameBoard();

	std::wstring* GetUI();
	void BlockRotate();
	void BlockHorMove(int nDirection);
	void BlockDown();
	void DropBlock();
	void SetTime(float fSec);
	void AddScore(int nScore);
	int GetScore();
};

#endif