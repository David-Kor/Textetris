#include "pch.h"
#include "GameBoard.h"


/* private �Լ� */

//�� ����� �����ϸ� ���� ����� ��Ʈ���ϰ� ��
void GameBoard::CreateNextBlock()
{
	if (isGameOver) { return; }

	//���� ����� nullptr�� �ƴϸ� �޸𸮿��� ����
	if (curBlk != nullptr)
	{
		delete curBlk;
		curBlk = nullptr;
	}
	//���� ����� nullptr�� �ƴϸ� ��ǥ�� ���� �� ���� ������� ����
	if (nxtBlk != nullptr)
	{
		nxtBlk->PositionUpdate();
		curBlk = nxtBlk;	//���� ���� ����� ���� ������� ����
		nxtBlk = nullptr;
		//��� ���ſ� �����ϸ� ���� ����
		if (UpdateBlockToBoard() != SUCCESS)
		{
			isGameOver = true;
			return;
		}
	}

	nxtBlk = new Blocks();	//���� ���� �� ��� ����
	nxtBlk->SetXPositionToCenter(MAX_HOR_SIZE);	//����� ����� ��ġ
}

//curBlk�� ��ǥ�� ���̺� ���� �õ� �� ��� ��ȯ -> �ε��� ���(-2), ��� ��ħ(-1), �ΰ� ����(0), ����(1 �̻�)
int GameBoard::UpdateBlockToBoard()
{
	if (curBlk == nullptr) { return NULL_REFERENCE; }

	//����� ���� ������ ������ ���� ��ȯ
	if (curBlk->GetMaxY() >= MAX_VER_SIZE ||
		curBlk->GetMaxX() >= MAX_HOR_SIZE ||
		curBlk->GetMinX() < 0)
	{
		return OUT_OF_INDEX;
	}

	//����� ��ġ�� ���� ��ȯ
	//Y��ǥ�� ���� ���� �ִ� ��ϸ� �浹�˻�
	if (curBlk->posMainBlk.Y >= 0)
	{
		if (mv_unBoardTable[curBlk->posMainBlk.Y][curBlk->posMainBlk.X] != 0) { return CRASH_BLOCK; }
	}
	if (curBlk->posSubBlk1.Y >= 0)
	{
		if (mv_unBoardTable[curBlk->posSubBlk1.Y][curBlk->posSubBlk1.X] != 0) { return CRASH_BLOCK; }
	}
	if (curBlk->posSubBlk2.Y >= 0)
	{
		if (mv_unBoardTable[curBlk->posSubBlk2.Y][curBlk->posSubBlk2.X] != 0) { return CRASH_BLOCK; }
	}
	if (curBlk->posSubBlk3.Y >= 0)
	{
		if (mv_unBoardTable[curBlk->posSubBlk3.Y][curBlk->posSubBlk3.X] != 0) { return CRASH_BLOCK; }
	}

	//���� ���庸�� ������ ��ǥ(Y < 0)�� ����
	if (curBlk->posMainBlk.Y >= 0) { mv_unBoardTable[curBlk->posMainBlk.Y][curBlk->posMainBlk.X] = 1; }
	if (curBlk->posSubBlk1.Y >= 0) { mv_unBoardTable[curBlk->posSubBlk1.Y][curBlk->posSubBlk1.X] = 1; }
	if (curBlk->posSubBlk2.Y >= 0) { mv_unBoardTable[curBlk->posSubBlk2.Y][curBlk->posSubBlk2.X] = 1; }
	if (curBlk->posSubBlk3.Y >= 0) { mv_unBoardTable[curBlk->posSubBlk3.Y][curBlk->posSubBlk3.X] = 1; }

	//���� ��ȯ
	return SUCCESS;
}

//���̺��� ������ ��µ� UI�� ����
void GameBoard::UpdateBoardToUI()
{
	if (isGameOver) { return; }

	int i, j;
	for (i = 0; i < MAX_VER_SIZE; i++)
	{
		for (j = 0; j < MAX_HOR_SIZE; j++)
		{
			//���̺� ���� 0�̸� �� ĭ
			if (mv_unBoardTable[i][j] == 0) { mv_wstrUI[i][j + 1] = EMPTY; }
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
			mv_unBoardTable[i][j] = 0;
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
	curBlk = nullptr;
	nxtBlk = nullptr;
}

std::wstring * GameBoard::GetUI()
{
	return mv_wstrUI;
}

//��� ȸ��
void GameBoard::BlockRotate()
{
	if (curBlk == nullptr || isGameOver) { return; }
	
	//���̺��� ȸ���ϱ� ���� �ڸ����� 0���� �ʱ�ȭ
	if (curBlk->posMainBlk.Y >= 0) { mv_unBoardTable[curBlk->posMainBlk.Y][curBlk->posMainBlk.X] = 0; }
	if (curBlk->posSubBlk1.Y >= 0) { mv_unBoardTable[curBlk->posSubBlk1.Y][curBlk->posSubBlk1.X] = 0; }
	if (curBlk->posSubBlk2.Y >= 0) { mv_unBoardTable[curBlk->posSubBlk2.Y][curBlk->posSubBlk2.X] = 0; }
	if (curBlk->posSubBlk3.Y >= 0) { mv_unBoardTable[curBlk->posSubBlk3.Y][curBlk->posSubBlk3.X] = 0; }
	//ȸ��
	curBlk->Rotate(1);
	//���� �õ�
	if (UpdateBlockToBoard() != SUCCESS)
	{
		//���� �� ȸ�� ���
		curBlk->Rotate(-1);
		UpdateBlockToBoard();
	}
	//���UI�� ����
	UpdateBoardToUI();
}

//������ ������ ����, �ƴϸ� ������ �̵�
void GameBoard::BlockHorMove(int nDirection)
{
	if (curBlk == nullptr || isGameOver) { return; }

	//���̺��� �̵��ϱ� ���� �ڸ����� 0���� �ʱ�ȭ
	if (curBlk->posMainBlk.Y >= 0) { mv_unBoardTable[curBlk->posMainBlk.Y][curBlk->posMainBlk.X] = 0; }
	if (curBlk->posSubBlk1.Y >= 0) { mv_unBoardTable[curBlk->posSubBlk1.Y][curBlk->posSubBlk1.X] = 0; }
	if (curBlk->posSubBlk2.Y >= 0) { mv_unBoardTable[curBlk->posSubBlk2.Y][curBlk->posSubBlk2.X] = 0; }
	if (curBlk->posSubBlk3.Y >= 0) { mv_unBoardTable[curBlk->posSubBlk3.Y][curBlk->posSubBlk3.X] = 0; }
	//���� �̵�
	if (nDirection < 0)
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

//����� �� ĭ �Ʒ��� ����
void GameBoard::BlockDown()
{
	if (curBlk == nullptr || isGameOver) { return; }

	int sResult;
	//���̺��� �̵��ϱ� ���� �ڸ����� 0���� �ʱ�ȭ
	if (curBlk->posMainBlk.Y >= 0) { mv_unBoardTable[curBlk->posMainBlk.Y][curBlk->posMainBlk.X] = 0; }
	if (curBlk->posSubBlk1.Y >= 0) { mv_unBoardTable[curBlk->posSubBlk1.Y][curBlk->posSubBlk1.X] = 0; }
	if (curBlk->posSubBlk2.Y >= 0) { mv_unBoardTable[curBlk->posSubBlk2.Y][curBlk->posSubBlk2.X] = 0; }
	if (curBlk->posSubBlk3.Y >= 0) { mv_unBoardTable[curBlk->posSubBlk3.Y][curBlk->posSubBlk3.X] = 0; }
	//�� ĭ �Ʒ��� �̵�
	curBlk->Move(-1);
	//���� �õ�
	sResult = UpdateBlockToBoard();
	//���� �� �̵� ���
	if (sResult <= 0)
	{
		curBlk->Move(0);
		UpdateBlockToBoard();
		//null�� ������ ���� ���а� �ƴ� ���(����� ���̻� ������ �� ���� ���)
		if (sResult != NULL_REFERENCE)
		{
			//��ϵ��� ��ǥ�� ���� ��ϰ�(2)�� ����
			if (curBlk->posMainBlk.Y >= 0) { mv_unBoardTable[curBlk->posMainBlk.Y][curBlk->posMainBlk.X] = 2; }
			if (curBlk->posSubBlk1.Y >= 0) { mv_unBoardTable[curBlk->posSubBlk1.Y][curBlk->posSubBlk1.X] = 2; }
			if (curBlk->posSubBlk2.Y >= 0) { mv_unBoardTable[curBlk->posSubBlk2.Y][curBlk->posSubBlk2.X] = 2; }
			if (curBlk->posSubBlk3.Y >= 0) { mv_unBoardTable[curBlk->posSubBlk3.Y][curBlk->posSubBlk3.X] = 2; }
			//�� ��� ����
			CreateNextBlock();
		}
	}
	//��� UI�� ����
	UpdateBoardToUI();
}

//����� �� �ر��� �ѹ��� ����
void GameBoard::DropBlock()
{
	if (curBlk == nullptr || isGameOver) { return; }

	int sResult = SUCCESS;
	
	while (sResult == SUCCESS)
	{
		//���̺��� �̵��ϱ� ���� �ڸ����� 0���� �ʱ�ȭ
		if (curBlk->posMainBlk.Y >= 0) { mv_unBoardTable[curBlk->posMainBlk.Y][curBlk->posMainBlk.X] = 0; }
		if (curBlk->posSubBlk1.Y >= 0) { mv_unBoardTable[curBlk->posSubBlk1.Y][curBlk->posSubBlk1.X] = 0; }
		if (curBlk->posSubBlk2.Y >= 0) { mv_unBoardTable[curBlk->posSubBlk2.Y][curBlk->posSubBlk2.X] = 0; }
		if (curBlk->posSubBlk3.Y >= 0) { mv_unBoardTable[curBlk->posSubBlk3.Y][curBlk->posSubBlk3.X] = 0; }
		//�� ĭ �Ʒ��� �̵�
		curBlk->Move(-1);
		//���� �õ�
		sResult = UpdateBlockToBoard();
		//���� �� �̵� ���
		if (sResult != SUCCESS)
		{
			curBlk->Move(0);
			UpdateBlockToBoard();
			//null�� ������ ���� ���а� �ƴ� ���(����� ���̻� ������ �� ���� ���)
			if (sResult != NULL_REFERENCE)
			{
				//��ϵ��� ��ǥ�� ���� ��ϰ�(2)�� ����
				if (curBlk->posMainBlk.Y >= 0) { mv_unBoardTable[curBlk->posMainBlk.Y][curBlk->posMainBlk.X] = 2; }
				if (curBlk->posSubBlk1.Y >= 0) { mv_unBoardTable[curBlk->posSubBlk1.Y][curBlk->posSubBlk1.X] = 2; }
				if (curBlk->posSubBlk2.Y >= 0) { mv_unBoardTable[curBlk->posSubBlk2.Y][curBlk->posSubBlk2.X] = 2; }
				if (curBlk->posSubBlk3.Y >= 0) { mv_unBoardTable[curBlk->posSubBlk3.Y][curBlk->posSubBlk3.X] = 2; }
				//�� ��� ����
				CreateNextBlock();
			}
		}
	}
	//��� UI�� ����
	UpdateBoardToUI();
}
