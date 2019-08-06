#include "pch.h"
#include "GameBoard.h"


/* private �Լ� */

//�� ����� �����ϸ� ���� ����� ��Ʈ���ϰ� ��
void GameBoard::v_CreateNextBlock()
{
	if (m_isGameOver) { return; }

	AddScore(SCORE_BLOCK_DROP);

	//���� ����� nullptr�� �ƴϸ� �޸𸮿��� ����
	if (curBlk != nullptr)
	{
		delete curBlk;
		curBlk = nullptr;
	}
	//���� ����� nullptr�� �ƴϸ� ��ǥ�� ���� �� ���� ������� ����
	if (nxtBlk != nullptr)
	{
		curBlk = nxtBlk;	//���� ���� ����� ���� ������� ����
		nxtBlk = nullptr;
		//��� ���ſ� �����ϸ� ���� ����
		if (v_UpdateBlockToBoard() != SUCCESS)
		{
			//������ �� ���
			if (curBlk->posMainBlk.Y >= 0) { mv_unBoardTable[curBlk->posMainBlk.Y][curBlk->posMainBlk.X] = 2; }
			if (curBlk->posSubBlk1.Y >= 0) { mv_unBoardTable[curBlk->posSubBlk1.Y][curBlk->posSubBlk1.X] = 2; }
			if (curBlk->posSubBlk2.Y >= 0) { mv_unBoardTable[curBlk->posSubBlk2.Y][curBlk->posSubBlk2.X] = 2; }
			if (curBlk->posSubBlk3.Y >= 0) { mv_unBoardTable[curBlk->posSubBlk3.Y][curBlk->posSubBlk3.X] = 2; }
			v_UpdateBoardToUI();
			//���� ������� true
			m_isGameOver = true;
			return;
		}
	}

	nxtBlk = new Blocks();	//���� ���� �� ��� ����
	nxtBlk->SetXPositionToCenter(MAX_HOR_SIZE);	//����� ����� ��ġ
	nxtBlk->PositionUpdate();

	//���� ���� ����� UI�� ���
	for (int i = 0; i < 4; i++)
	{
		//�������� �ʱ�ȭ
		mv_wstrUI[NXT_BLK_LINE_1][12 + i] = L'��';
		mv_wstrUI[NXT_BLK_LINE_2][12 + i] = L'��';
	}
	mv_wstrUI[nxtBlk->posMainBlk.Y + NXT_BLK_Y_HANDLE][nxtBlk->posMainBlk.X + NXT_BLK_X_HANDLE] = L'��';
	mv_wstrUI[nxtBlk->posSubBlk1.Y + NXT_BLK_Y_HANDLE][nxtBlk->posSubBlk1.X + NXT_BLK_X_HANDLE] = L'��';
	mv_wstrUI[nxtBlk->posSubBlk2.Y + NXT_BLK_Y_HANDLE][nxtBlk->posSubBlk2.X + NXT_BLK_X_HANDLE] = L'��';
	mv_wstrUI[nxtBlk->posSubBlk3.Y + NXT_BLK_Y_HANDLE][nxtBlk->posSubBlk3.X + NXT_BLK_X_HANDLE] = L'��';
}

//curBlk�� ��ǥ�� ���̺� ���� �õ� �� ��� ��ȯ -> �ε��� ���(-2), ��� ��ħ(-1), �ΰ� ����(0), ����(1 �̻�)
int GameBoard::v_UpdateBlockToBoard()
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
void GameBoard::v_UpdateBoardToUI()
{
	if (m_isGameOver) { return; }

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

//������ ������ �˻��Ͽ� ����
void GameBoard::v_CheckFullLine()
{
	int i, j;
	int nBlkCnt = 0, nLnCnt = 0;
	for (i = 0; i < MAX_VER_SIZE; i++)
	{
		nBlkCnt = 0;
		for (j = 0; j < MAX_HOR_SIZE; j++)
		{
			if (mv_unBoardTable[i][j] == 2) { nBlkCnt++; }		//�� �ٿ� ����� �� ������ ��
		}
		//i�� ������ ������ �����̸�
		if (nBlkCnt >= MAX_HOR_SIZE)
		{
			nLnCnt++;	//���� ī��Ʈ �߰�
		}
		//i�� ������ ���������� �ʰ� ���� ī��Ʈ�� 1�̻��̸�
		else if (nLnCnt > 0)
		{
			v_DeleteLine(i - 1, nLnCnt);	//i������ �������� ���� ī��Ʈ��ŭ ����
			nLnCnt = 0;
		}
	}

	//���� �Ʒ����κ��� ������ ���
	if (nLnCnt > 0)
	{
		v_DeleteLine(MAX_VER_SIZE - 1, nLnCnt);
	}
}

//���̺� �� ����� ���� �� ���� �����Լ�
void GameBoard::v_DeleteLine(int nLine, int nCount)
{
	int i, j;
	//���� 1~nLine
	for (i = nLine; i >= nCount; i--)
	{
		for (j = 0; j < MAX_HOR_SIZE; j++)
		{
			//i�� ������ ������ i-nCount������ �������� �ٲ�
			mv_unBoardTable[i][j] = mv_unBoardTable[i - nCount][j];
		}
	}

	//0~nCount���� �ʱ�ȭ
	for (i = 0; i < nCount; i++)
	{
		for (j = 0; j < MAX_HOR_SIZE; j++)
		{
			mv_unBoardTable[i][j] = 0;
		}
	}

	AddScore(SCORE_LINE_CLEAR * nCount);
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
	}

	//���� ���� ���UI�� ����
	mv_wstrUI[NXT_BLK_LINE_1-1]	+= L"�ââââ�";
	mv_wstrUI[NXT_BLK_LINE_1]	+= L"����������";
	mv_wstrUI[NXT_BLK_LINE_2]	+= L"����������";
	mv_wstrUI[NXT_BLK_LINE_2+1]	+= L"�ââââ�";

	//�Ʒ� ��UI
	for (j = 0; j <= MAX_HOR_SIZE; j++)
	{
		//���� �Ʒ� ��
		mv_wstrUI[MAX_VER_SIZE] += WALL;
		//�ð�,���� UI �Ʒ� ��
		mv_wstrUI[MAX_UI_LINE - 1] += WALL;
	}

	//�ð� �� ���� UI
	mv_wstrUI[MAX_VER_SIZE + 1] += L"���ð���";
	mv_wstrUI[MAX_VER_SIZE + 2] += L"��������";

	curBlk = nullptr;
	nxtBlk = nullptr;
	//nxt��ϰ� cur��� ����
	v_CreateNextBlock();
	v_CreateNextBlock();
	v_UpdateBlockToBoard();
	v_UpdateBoardToUI();

	//����,�ð� UI �ʱ�ȭ
	mv_nScore = 0;
	mv_fTime = 0.0f;
	AddScore(0);
	SetTime(mv_fTime);
}

//�Ҹ���
GameBoard::~GameBoard()
{
	delete curBlk;
	delete nxtBlk;
	curBlk = nullptr;
	nxtBlk = nullptr;
}

std::wstring* GameBoard::GetUI()
{
	return mv_wstrUI;
}

//��� ȸ��
void GameBoard::BlockRotate()
{
	if (curBlk == nullptr || m_isGameOver) { return; }
	
	//���̺��� ȸ���ϱ� ���� �ڸ����� 0���� �ʱ�ȭ
	if (curBlk->posMainBlk.Y >= 0) { mv_unBoardTable[curBlk->posMainBlk.Y][curBlk->posMainBlk.X] = 0; }
	if (curBlk->posSubBlk1.Y >= 0) { mv_unBoardTable[curBlk->posSubBlk1.Y][curBlk->posSubBlk1.X] = 0; }
	if (curBlk->posSubBlk2.Y >= 0) { mv_unBoardTable[curBlk->posSubBlk2.Y][curBlk->posSubBlk2.X] = 0; }
	if (curBlk->posSubBlk3.Y >= 0) { mv_unBoardTable[curBlk->posSubBlk3.Y][curBlk->posSubBlk3.X] = 0; }
	
	//ȸ��
	curBlk->Rotate(1);
	//���� �õ�
	int result = v_UpdateBlockToBoard();

	//���� ���� ������ �Ѿ�� ������ ���
	if (result == OUT_OF_INDEX)
	{
		//����� ���� ���� �Ѿ��ٸ�
		if (curBlk->GetMinX() < 0)
		{
			//������ �� ĭ�� �̵� �õ�
			curBlk->Move(2);
			result = v_UpdateBlockToBoard();
			//���� �� �� �� �� �õ�
			if (result != SUCCESS)
			{
				//������ �� ĭ �� �̵� �õ�
				curBlk->Move(2);
				result = v_UpdateBlockToBoard();
				//�̹����� ���� �� ��� �̵� �� ȸ�� ���
				if (result != SUCCESS)
				{
					curBlk->Move(1);
					curBlk->Move(1);
					curBlk->Rotate(-1);
				}
			}
		}
		//����� ������ ���� �Ѿ��ٸ�
		else if (curBlk->GetMaxX() >= MAX_HOR_SIZE)
		{
			//���� �� ĭ�� �̵� �õ�
			curBlk->Move(1);
			result = v_UpdateBlockToBoard();
			//���� �� �� �� �� �õ�
			if (result != SUCCESS)
			{
				//���� �� ĭ �� �̵� �õ�
				curBlk->Move(1);
				result = v_UpdateBlockToBoard();
				//�̹����� ���� �� ��� �̵� �� ȸ�� ���
				if (result != SUCCESS)
				{
					curBlk->Move(2);
					curBlk->Move(2);
					curBlk->Rotate(-1);
				}
			}
		}
		//����� �Ʒ��� ���� �Ѿ��ٸ�
		else
		{
			//ȸ�� ���
			curBlk->Rotate(-1);
			v_UpdateBlockToBoard();
		}
	}
	//��ϰ� �浹�ϴ� ������ ���
	else if (result == CRASH_BLOCK)
	{
		//���� �� ĭ�� �̵� �õ�
		curBlk->Move(1);
		result = v_UpdateBlockToBoard();

		//���� �� ����
		if (result == SUCCESS)
		{
			v_UpdateBoardToUI();
			return;
		}
		//���� �� ���� �� ĭ° �̵� �õ�
		else
		{
			curBlk->Move(1);
			result = v_UpdateBlockToBoard();

			//���� �� ����
			if (result == SUCCESS)
			{
				v_UpdateBoardToUI();
				return;
			}
			//���� �� ���� �̵� ���
			else
			{
				curBlk->Move(2);
				curBlk->Move(2);
			}
		}

		//������ ���� �� ������ �õ�
		curBlk->Move(2);
		result = v_UpdateBlockToBoard();

		if (result == SUCCESS)
		{
			v_UpdateBoardToUI();
			return;
		}
		//���� �� ������ �� ĭ° �̵� �õ�
		else
		{
			curBlk->Move(2);
			result = v_UpdateBlockToBoard();
			if (result == SUCCESS)
			{
				v_UpdateBoardToUI();
				return;
			}
			//���� �� ������ �̵� ���
			else
			{
				curBlk->Move(1);
				curBlk->Move(1);
			}
		}

		//ȸ�� ���
		curBlk->Rotate(-1);
		v_UpdateBlockToBoard();
	}
	
	//���UI�� ����
	v_UpdateBoardToUI();
}

//������ ������ ����, �ƴϸ� ������ �̵�
void GameBoard::BlockHorMove(int nDirection)
{
	if (curBlk == nullptr || m_isGameOver) { return; }

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
		if (v_UpdateBlockToBoard() <= 0)
		{
			//���� �� �̵� ���
			curBlk->Move(2);
			v_UpdateBlockToBoard();
		}
	}
	//������ �̵�
	else
	{
		curBlk->Move(2);
		//���� �õ�
		if (v_UpdateBlockToBoard() <= 0)
		{
			//���� �� �̵� ���
			curBlk->Move(1);
			v_UpdateBlockToBoard();
		}
	}
	//��� UI�� ����
	v_UpdateBoardToUI();
}

//����� �� ĭ �Ʒ��� ����
void GameBoard::BlockDown()
{
	if (curBlk == nullptr || m_isGameOver) { return; }

	int sResult;
	//���̺��� �̵��ϱ� ���� �ڸ����� 0���� �ʱ�ȭ
	if (curBlk->posMainBlk.Y >= 0) { mv_unBoardTable[curBlk->posMainBlk.Y][curBlk->posMainBlk.X] = 0; }
	if (curBlk->posSubBlk1.Y >= 0) { mv_unBoardTable[curBlk->posSubBlk1.Y][curBlk->posSubBlk1.X] = 0; }
	if (curBlk->posSubBlk2.Y >= 0) { mv_unBoardTable[curBlk->posSubBlk2.Y][curBlk->posSubBlk2.X] = 0; }
	if (curBlk->posSubBlk3.Y >= 0) { mv_unBoardTable[curBlk->posSubBlk3.Y][curBlk->posSubBlk3.X] = 0; }
	//�� ĭ �Ʒ��� �̵�
	curBlk->Move(-1);
	//���� �õ�
	sResult = v_UpdateBlockToBoard();
	//���� �� �̵� ���
	if (sResult <= 0)
	{
		curBlk->Move(0);
		v_UpdateBlockToBoard();
		//null�� ������ ���� ���а� �ƴ� ���(����� ���̻� ������ �� ���� ���)
		if (sResult != NULL_REFERENCE)
		{
			//��ϵ��� ��ǥ�� ���� ��ϰ�(2)�� ����
			if (curBlk->posMainBlk.Y >= 0) { mv_unBoardTable[curBlk->posMainBlk.Y][curBlk->posMainBlk.X] = 2; }
			if (curBlk->posSubBlk1.Y >= 0) { mv_unBoardTable[curBlk->posSubBlk1.Y][curBlk->posSubBlk1.X] = 2; }
			if (curBlk->posSubBlk2.Y >= 0) { mv_unBoardTable[curBlk->posSubBlk2.Y][curBlk->posSubBlk2.X] = 2; }
			if (curBlk->posSubBlk3.Y >= 0) { mv_unBoardTable[curBlk->posSubBlk3.Y][curBlk->posSubBlk3.X] = 2; }
			v_CheckFullLine();
			//�� ��� ����
			v_CreateNextBlock();
		}
	}
	//��� UI�� ����
	v_UpdateBoardToUI();
}

//����� �� �ر��� �ѹ��� ����
void GameBoard::DropBlock()
{
	if (curBlk == nullptr || m_isGameOver) { return; }

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
		sResult = v_UpdateBlockToBoard();
		//���� �� �̵� ���
		if (sResult != SUCCESS)
		{
			curBlk->Move(0);
			v_UpdateBlockToBoard();
			//null�� ������ ���� ���а� �ƴ� ���(����� ���̻� ������ �� ���� ���)
			if (sResult != NULL_REFERENCE)
			{
				//��ϵ��� ��ǥ�� ���� ��ϰ�(2)�� ����
				if (curBlk->posMainBlk.Y >= 0) { mv_unBoardTable[curBlk->posMainBlk.Y][curBlk->posMainBlk.X] = 2; }
				if (curBlk->posSubBlk1.Y >= 0) { mv_unBoardTable[curBlk->posSubBlk1.Y][curBlk->posSubBlk1.X] = 2; }
				if (curBlk->posSubBlk2.Y >= 0) { mv_unBoardTable[curBlk->posSubBlk2.Y][curBlk->posSubBlk2.X] = 2; }
				if (curBlk->posSubBlk3.Y >= 0) { mv_unBoardTable[curBlk->posSubBlk3.Y][curBlk->posSubBlk3.X] = 2; }
				v_CheckFullLine();
				//�� ��� ����
				v_CreateNextBlock();
			}
		}
	}
	//��� UI�� ����
	v_UpdateBoardToUI();
}

void GameBoard::SetTime(float fSec)
{
	static std::wstring wstrTimeUI = mv_wstrUI[MAX_VER_SIZE + 1];
	//�Ҽ��� ù°�ڸ� �Ʒ��� ����
	fSec = (int)(fSec * 10) / 10.0f;

	//0.1�ʴ����� �ð� UI����
	if (mv_fTime != fSec)
	{
		mv_fTime = fSec;
		wchar_t wstrTime[8] = { NULL, };
		std::swprintf(wstrTime, sizeof(wstrTime) / sizeof(wchar_t), L"%.1f", fSec);		//�Ҽ��� 1�ڸ����� ����

		mv_wstrUI[MAX_VER_SIZE + 1] = wstrTimeUI;
		for (int i = 0; i < 8; i++)
		{
			mv_wstrUI[MAX_VER_SIZE + 1] += wstrTime[i];
			if (wstrTime[i] == NULL) { break; }
		}
	}
}

void GameBoard::AddScore(int nScore)
{
	static std::wstring wstrScoreUI = mv_wstrUI[MAX_VER_SIZE + 2];
	mv_nScore += nScore;

	//���� ������ wstring������ ��ȯ
	wchar_t wstrScore[11] = { 0, };
	std::swprintf(wstrScore, sizeof(wstrScore) / sizeof(wchar_t), L"%010u", mv_nScore);
	mv_wstrUI[MAX_VER_SIZE + 2] = wstrScoreUI + wstrScore;
}

int GameBoard::GetScore()
{
	return mv_nScore;
}
