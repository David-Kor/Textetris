#ifndef _GAMEBOARD_CLASS
#define _GAMEBOARD_CLASS

#include "Blocks.h"

class GameBoard
{
private:
	std::wstring mv_wstrUI[23];	//UI �ؽ�Ʈ
	Blocks* curBlk;		//���� ��Ʈ�� ���� ���
	Blocks* nxtBlk;		//���� ���� ���
	unsigned int mv_unBoardTable[20][10];	//������ ���α��� x ������ ���α���

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
	enum BoardType { BLOCK = L'��', EMPTY = L'��', WALL = L'��' };
	//������ ���α���
	const int MAX_VER_SIZE = 20;
	//������ ���α���
	const int MAX_HOR_SIZE = 10;
	//��ü UI ���� ��
	const int MAX_UI_LINE = 23;

	//����� ������ ������ �� ȹ���ϴ� ����
	const int SCORE_BLOCK_DROP = 10;
	//������ �� ä���� �� 1���δ� ȹ���ϴ� ����
	const int SCORE_LINE_CLEAR = 50;
	bool m_isGameOver;

	//������
	GameBoard();
	//�Ҹ���
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