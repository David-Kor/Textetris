#include "pch.h"
#include "GameBoard.h"

/* private �Լ� */

//�� ����� �����ϸ� ���� ����� ��Ʈ���ϰ� ��
//DONE
void GameBoard::CreateNextBlock()
{
	//���� ���� ����� ���� ������� ����
	curBlk = nxtBlk;

	if (curBlk != nullptr)
	{
		curBlk->PositionUpdate();
		if (curBlk->posMainBlk.Y >= 0) {
			mv_ucBoardTable[curBlk->posMainBlk.Y][curBlk->posMainBlk.X] = 1;
		}
		if (curBlk->posSubBlk1.Y >= 0) {
			mv_ucBoardTable[curBlk->posSubBlk1.Y][curBlk->posSubBlk1.X] = 1;
		}
		if (curBlk->posSubBlk2.Y >= 0) {
			mv_ucBoardTable[curBlk->posSubBlk2.Y][curBlk->posSubBlk2.X] = 1;
		}
		if (curBlk->posSubBlk3.Y >= 0) {
			mv_ucBoardTable[curBlk->posSubBlk3.Y][curBlk->posSubBlk3.X] = 1;
		}
	}

	//���� ���� �� ��� ����
	nxtBlk = new Blocks();
	//���κ���� ����� ��ġ
	nxtBlk->posMainBlk.X = MAX_HOR_SIZE / 2;
}

//���̺��� ������ ��µ� UI�� ����
void GameBoard::UpdateBoard()
{
	int i, j;
	for (i = 0; i < MAX_VER_SIZE; i++)
	{
		for (j = 0; j < MAX_HOR_SIZE; j++)
		{
			//���̺� ���� 0�̸� �� ĭ
			if (mv_ucBoardTable[i][j] == 0) { mv_wstrUI[i][j + 1] = EMPTY; }
			//0�� �ƴϸ� ���(��)
			else { mv_wstrUI[i][j + 1] = BLOCK; }
		}
	}
}

/* public �Լ� */

//������
//DONE
GameBoard::GameBoard()
{
	int i, j;

	//���� ���� �ʱ�ȭ
	for (i = 0; i < MAX_VER_SIZE; i++)
	{
		for (j = 0; j < MAX_HOR_SIZE; j++)
		{
			mv_ucBoardTable[i][j] = 0;
		}
	}

	//UI�ʱ�ȭ
	for (i = 0; i < MAX_UI_LINE; i++)
	{
		//���� ���� ��
		mv_wstrUI[i] = WALL;
		//���� ����
		if (i < MAX_VER_SIZE)
		{
			for (j = 0; j < MAX_HOR_SIZE; j++)
			{
				mv_wstrUI[i] += EMPTY;
			}
			//���� ���� ��
			mv_wstrUI[i] += WALL;
		}
		//���� �Ʒ� ��
		else if (i == MAX_VER_SIZE)
		{
			for (j = 0; j <= MAX_HOR_SIZE; j++)
			{
				mv_wstrUI[i] += WALL; 
			}
		}
		else if (i == MAX_VER_SIZE + 1)
		{
			mv_wstrUI[i] += L"���ð���0";
		}

		else if (i == MAX_VER_SIZE + 2)
		{
			mv_wstrUI[i] += L"��������0";
		}
	}

	curBlk = nullptr;
	nxtBlk = nullptr;

	CreateNextBlock();
	CreateNextBlock();
	UpdateBoard();
}

//�Ҹ���
GameBoard::~GameBoard()
{
	delete curBlk;
	delete nxtBlk;
}

std::wstring * GameBoard::GetUI()
{
	return mv_wstrUI;
}

//��� ȸ��
void GameBoard::RotateBlock()
{
}

//������ ����� ������, ������ ����, 0�̸� �Ʒ� �̵�
void GameBoard::MoveBlock(short sDirection)
{
}

//����� �� �ر��� �ѹ��� ����
void GameBoard::DropBlock()
{
}
