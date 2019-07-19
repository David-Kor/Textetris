#include "pch.h"
#include "GameBoard.h"

/* private �Լ� */

//�� ����� �����ϸ� ���� ����� ��Ʈ���ϰ� ��
void GameBoard::CreateNextBlock()
{
	//���� ����� nullptr�� �ƴϸ� �޸𸮿��� ����
	if (curBlk != nullptr)
	{
		delete curBlk;
	}
	//���� ����� nullptr�� �ƴϸ� ��ǥ�� ����
	if (nxtBlk != nullptr)
	{
		nxtBlk->PositionUpdate();
	}
	//���� ���� ����� ���� ������� ����
	curBlk = nxtBlk;

	//���� ���� �� ��� ����
	nxtBlk = new Blocks();
	//����� ����� ��ġ
	nxtBlk->SetXPositionToCenter(MAX_HOR_SIZE);
}

//curBlk�� ��ǥ�� ���̺� ���� �õ� �� ��� ��ȯ -> �ε��� ���(-2), ��� ��ħ(-1), �ΰ� ����(0), ����(1 �̻�)
short GameBoard::UpdateBlockToBoard()
{
	if (curBlk == nullptr) { return NULL_REFERENCE; }

	//����� ��ġ�� ���� ��ȯ
	//Y��ǥ�� ���� ���� �ִ� ��ϸ� �浹�˻�
	if (curBlk->posMainBlk.Y >= 0) {
		if (mv_ucBoardTable[curBlk->posMainBlk.Y][curBlk->posMainBlk.X] > 0) {
			return CRASH_BLOCK;
		}
	}
	if (curBlk->posSubBlk1.Y >= 0) {
		if (mv_ucBoardTable[curBlk->posSubBlk1.Y][curBlk->posSubBlk1.X] > 0) {
			return CRASH_BLOCK;
		}
	}
	if (curBlk->posSubBlk2.Y >= 0) {
		if (mv_ucBoardTable[curBlk->posSubBlk2.Y][curBlk->posSubBlk2.X] > 0) {
			return CRASH_BLOCK;
		}
	}
	if (curBlk->posSubBlk3.Y >= 0) {
		if (mv_ucBoardTable[curBlk->posSubBlk3.Y][curBlk->posSubBlk3.X] > 0) {
			return CRASH_BLOCK;
		}
	}
	
	//����� ���� ������ ������ ���� ��ȯ
	if (curBlk->posMainBlk.Y >= MAX_VER_SIZE || curBlk->posMainBlk.X < 0 || curBlk->posMainBlk.X >= MAX_HOR_SIZE ||
		curBlk->posSubBlk1.Y >= MAX_VER_SIZE || curBlk->posSubBlk1.X < 0 || curBlk->posSubBlk1.X >= MAX_HOR_SIZE ||
		curBlk->posSubBlk2.Y >= MAX_VER_SIZE || curBlk->posSubBlk2.X < 0 || curBlk->posSubBlk2.X >= MAX_HOR_SIZE ||
		curBlk->posSubBlk3.Y >= MAX_VER_SIZE || curBlk->posSubBlk3.X < 0 || curBlk->posSubBlk3.X >= MAX_HOR_SIZE)
	{
		return OUT_OF_INDEX;
	}

	//���� ���庸�� ������ ��ǥ(Y < 0)�� ����
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

	//���� ��ȯ
	return SUCCESS;
}

//���̺��� ������ ��µ� UI�� ����
void GameBoard::UpdateBoardToUI()
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

	//�ӽ÷� �س���
	CreateNextBlock();
	CreateNextBlock();
	UpdateBlockToBoard();
	UpdateBoardToUI();
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
void GameBoard::BlockRotate()
{
	if (curBlk == nullptr) { return; }
	
	//���̺��� ȸ���ϱ� ���� �ڸ����� 0���� �ʱ�ȭ
	mv_ucBoardTable[curBlk->posMainBlk.Y][curBlk->posMainBlk.X] = 0;
	mv_ucBoardTable[curBlk->posSubBlk1.Y][curBlk->posSubBlk1.X] = 0;
	mv_ucBoardTable[curBlk->posSubBlk2.Y][curBlk->posSubBlk2.X] = 0;
	mv_ucBoardTable[curBlk->posSubBlk3.Y][curBlk->posSubBlk3.X] = 0;
	//ȸ��
	curBlk->Rotate(1);
	//���� �õ�
	if (UpdateBlockToBoard() <= 0)
	{
		//���� �� ȸ�� ���
		curBlk->Rotate(-1);
		UpdateBlockToBoard();
	}
	//���UI�� ����
	UpdateBoardToUI();
}

//������ ������ ����, �ƴϸ� ������ �̵�
void GameBoard::BlockHorMove(short sDirection)
{
	if (curBlk == nullptr) { return; }

	//���̺��� �̵��ϱ� ���� �ڸ����� 0���� �ʱ�ȭ
	mv_ucBoardTable[curBlk->posMainBlk.Y][curBlk->posMainBlk.X] = 0;
	mv_ucBoardTable[curBlk->posSubBlk1.Y][curBlk->posSubBlk1.X] = 0;
	mv_ucBoardTable[curBlk->posSubBlk2.Y][curBlk->posSubBlk2.X] = 0;
	mv_ucBoardTable[curBlk->posSubBlk3.Y][curBlk->posSubBlk3.X] = 0;
	//���� �̵�
	if (sDirection < 0)
	{
		curBlk->Move(1);
		//���� �õ�
		if (UpdateBlockToBoard() <= 0)
		{
			//���� �� �̵� ���
			curBlk->Move(2);
			UpdateBlockToBoard();
		}
	}
	//������ �̵�
	else
	{
		curBlk->Move(2);
		//���� �õ�
		if (UpdateBlockToBoard() <= 0)
		{
			//���� �� �̵� ���
			curBlk->Move(1);
			UpdateBlockToBoard();
		}
	}
	//��� UI�� ����
	UpdateBoardToUI();
}

void GameBoard::BlockDown(int a=0)
{
	if (curBlk == nullptr) { return; }

	short sResult;
	//���̺��� �̵��ϱ� ���� �ڸ����� 0���� �ʱ�ȭ
	mv_ucBoardTable[curBlk->posMainBlk.Y][curBlk->posMainBlk.X] = 0;
	mv_ucBoardTable[curBlk->posSubBlk1.Y][curBlk->posSubBlk1.X] = 0;
	mv_ucBoardTable[curBlk->posSubBlk2.Y][curBlk->posSubBlk2.X] = 0;
	mv_ucBoardTable[curBlk->posSubBlk3.Y][curBlk->posSubBlk3.X] = 0;
	//�� ĭ �Ʒ��� �̵�
	curBlk->Move(-1 * a);
	//���� �õ�
	sResult = UpdateBlockToBoard();
	//���� �� �̵� ���
	if (sResult <= 0)
	{
		curBlk->Move(0);
		//null�� ������ ���� ���а� �ƴ� ���(����� ���̻� ������ �� ���� ���)
		if (sResult != NULL_REFERENCE)
		{
			//��ϵ��� ��ǥ�� ���� ��ϰ�(2)�� ����
			mv_ucBoardTable[curBlk->posMainBlk.Y][curBlk->posMainBlk.X] = 2;
			mv_ucBoardTable[curBlk->posSubBlk1.Y][curBlk->posSubBlk1.X] = 2;
			mv_ucBoardTable[curBlk->posSubBlk2.Y][curBlk->posSubBlk2.X] = 2;
			mv_ucBoardTable[curBlk->posSubBlk3.Y][curBlk->posSubBlk3.X] = 2;
			//�� ��� ����
			CreateNextBlock();
		}
		UpdateBlockToBoard();
	}
	//��� UI�� ����
	UpdateBoardToUI();
}

//����� �� �ر��� �ѹ��� ����
void GameBoard::DropBlock()
{
	if (curBlk == nullptr) { return; }

	short sResult;
	//���̺��� �̵��ϱ� ���� �ڸ����� 0���� �ʱ�ȭ
	mv_ucBoardTable[curBlk->posMainBlk.Y][curBlk->posMainBlk.X] = 0;
	mv_ucBoardTable[curBlk->posSubBlk1.Y][curBlk->posSubBlk1.X] = 0;
	mv_ucBoardTable[curBlk->posSubBlk2.Y][curBlk->posSubBlk2.X] = 0;
	mv_ucBoardTable[curBlk->posSubBlk3.Y][curBlk->posSubBlk3.X] = 0;
	//�� ĭ �Ʒ��� �̵�
	curBlk->Move(-1);
	//���� �õ�
	sResult = UpdateBlockToBoard();
	//���� �� �̵� ���
	if (sResult <= 0)
	{
		curBlk->Move(0);
		//null�� ������ ���� ���а� �ƴ� ���(����� ���̻� ������ �� ���� ���)
		if (sResult != NULL_REFERENCE)
		{
			//��ϵ��� ��ǥ�� ���� ��ϰ�(2)�� ����
			mv_ucBoardTable[curBlk->posMainBlk.Y][curBlk->posMainBlk.X] = 2;
			mv_ucBoardTable[curBlk->posSubBlk1.Y][curBlk->posSubBlk1.X] = 2;
			mv_ucBoardTable[curBlk->posSubBlk2.Y][curBlk->posSubBlk2.X] = 2;
			mv_ucBoardTable[curBlk->posSubBlk3.Y][curBlk->posSubBlk3.X] = 2;
			//�� ��� ����
			CreateNextBlock();
		}
		UpdateBlockToBoard();
	}
	//��� UI�� ����
	UpdateBoardToUI();
}
