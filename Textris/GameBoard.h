#ifndef _GAMEBOARD_CLASS
#define _GAMEBOARD_CLASS

#include "Blocks.h"

class GameBoard
{
private:
	enum BoardType { BLOCK = L'��', EMPTY = L'��', WALL = L'��' };

	unsigned char mv_ucBoardTable[20][10];	//������ ���α��� x ������ ���α���
	std::wstring mv_wstrUI[23];
	Blocks* curBlk;		//���� ��Ʈ�� ���� ���
	Blocks* nxtBlk;		//���� ���� ���

	const short OUT_OF_INDEX = -2;
	const short CRASH_BLOCK = -1;
	const short NULL_REFERENCE = 0;
	const short SUCCESS = 1;

	void CreateNextBlock();
	short UpdateBlockToBoard();
	void UpdateBoardToUI();

public:
	//������ ���α���
	const short MAX_VER_SIZE = 20;
	//������ ���α���
	const short MAX_HOR_SIZE = 10;
	//��ü UI ���� ��
	const short MAX_UI_LINE = 23;

	//������
	GameBoard();
	//�Ҹ���
	~GameBoard();

	std::wstring* GetUI();
	void BlockRotate();
	void BlockHorMove(short sDirection);
	void BlockDown();
	void DropBlock();
};

#endif