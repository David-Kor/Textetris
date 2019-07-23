#ifndef _GAMEBOARD_CLASS
#define _GAMEBOARD_CLASS

#include "Blocks.h"

class GameBoard
{
private:
	enum BoardType { BLOCK = L'��', EMPTY = L'��', WALL = L'��' };

	unsigned int mv_unBoardTable[20][10];	//������ ���α��� x ������ ���α���
	std::wstring mv_wstrUI[23];	//UI �ؽ�Ʈ
	Blocks* curBlk;		//���� ��Ʈ�� ���� ���
	Blocks* nxtBlk;		//���� ���� ���

	const int OUT_OF_INDEX = -2;
	const int CRASH_BLOCK = -1;
	const int NULL_REFERENCE = 0;
	const int SUCCESS = 1;

	void CreateNextBlock();
	int UpdateBlockToBoard();
	void UpdateBoardToUI();

public:
	//������ ���α���
	const int MAX_VER_SIZE = 20;
	//������ ���α���
	const int MAX_HOR_SIZE = 10;
	//��ü UI ���� ��
	const int MAX_UI_LINE = 23;
	bool isGameOver;

	//������
	GameBoard();
	//�Ҹ���
	~GameBoard();

	std::wstring* GetUI();
	void BlockRotate();
	void BlockHorMove(int nDirection);
	void BlockDown();
	void DropBlock();
};

#endif