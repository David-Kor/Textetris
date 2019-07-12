#include "pch.h"
#include "GameBoard.h"

//�� ����� �����ϸ� ���� ����� ��Ʈ���ϰ� ��
void GameBoard::CreateNextBlock()
{
	//���� ���� ����� ���� ������� ����
	curBlk = nxtBlk;

	if (curBlk != nullptr)
	{
		curBlk->posMainBlk.Y++;
	}

	//���� ���� �� ��� ����
	nxtBlk = new Blocks();
	nxtBlk->rotateCnt = 0;
	//���κ�� ��ǥ ����
	nxtBlk->posMainBlk.X = MAX_HOR_SIZE / 2;
	nxtBlk->posMainBlk.Y = 0;
	nxtBlk->type = (BlockType)(rand() % 7);		//���� Ÿ�� ����
	UpdateBlock(nxtBlk);
}

//����� MainBlk ��ġ�� ���� SubBlk��ġ�� ����. ���� �� �������·� �ǵ��ư�. �������� ��ȯ
bool GameBoard::UpdateBlock(Blocks* blk)
{
	if (blk == nullptr) {
		return false;
	}

	Blocks blkPreState = *blk;

	//������ ��ǥ ����
	switch (blk->type)
	{
		//������ ���
	case BlockType::I:
		switch (blk->rotateCnt % 2)	//ȸ�� ���� ����� 2���� ����
		{
		case 0: {
			//1�� ���
			blk->posSubBlk1.X = blk->posMainBlk.X - 1;
			blk->posSubBlk1.Y = blk->posMainBlk.Y;
			//2�� ���
			blk->posSubBlk2.X = blk->posMainBlk.X + 1;
			blk->posSubBlk2.Y = blk->posMainBlk.Y;
			//3�� ���
			blk->posSubBlk3.X = blk->posMainBlk.X + 2;
			blk->posSubBlk3.Y = blk->posMainBlk.Y;
			break; }

		case 1: {
			//1�� ���
			blk->posSubBlk1.X = blk->posMainBlk.X;
			blk->posSubBlk1.Y = blk->posMainBlk.Y + 1;
			//2�� ���
			blk->posSubBlk2.X = blk->posMainBlk.X;
			blk->posSubBlk2.Y = blk->posMainBlk.Y - 1;
			//3�� ���
			blk->posSubBlk3.X = blk->posMainBlk.X;
			blk->posSubBlk3.Y = blk->posMainBlk.Y - 2;
			break; }
		}
		break;

		//������ ���
	case BlockType::O:
		blk->posSubBlk1.X = blk->posMainBlk.X + 1;
		blk->posSubBlk1.Y = blk->posMainBlk.Y;
		blk->posSubBlk2.X = blk->posMainBlk.X;
		blk->posSubBlk2.Y = blk->posMainBlk.Y + 1;
		blk->posSubBlk2.X = blk->posMainBlk.X + 1;
		blk->posSubBlk2.Y = blk->posMainBlk.Y + 1;
		break;

		//������ ���
	case BlockType::T:
		switch (blk->rotateCnt)
		{
		case 0: {
			//1�� ���
			blk->posSubBlk1.X = blk->posMainBlk.X + 1;
			blk->posSubBlk1.Y = blk->posMainBlk.Y;
			//2�� ���
			blk->posSubBlk2.X = blk->posMainBlk.X - 1;
			blk->posSubBlk2.Y = blk->posMainBlk.Y;
			//3�� ���
			blk->posSubBlk3.X = blk->posMainBlk.X;
			blk->posSubBlk3.Y = blk->posMainBlk.Y - 1;
			break; }

		case 1: {
			//1�� ���
			blk->posSubBlk1.X = blk->posMainBlk.X;
			blk->posSubBlk1.Y = blk->posMainBlk.Y + 1;
			//2�� ���
			blk->posSubBlk2.X = blk->posMainBlk.X;
			blk->posSubBlk2.Y = blk->posMainBlk.Y - 1;
			//3�� ���
			blk->posSubBlk3.X = blk->posMainBlk.X - 1;
			blk->posSubBlk3.Y = blk->posMainBlk.Y;
			break; }

		case 2: {
			//1�� ���
			blk->posSubBlk1.X = blk->posMainBlk.X - 1;
			blk->posSubBlk1.Y = blk->posMainBlk.Y;
			//2�� ���
			blk->posSubBlk2.X = blk->posMainBlk.X + 1;
			blk->posSubBlk2.Y = blk->posMainBlk.Y;
			//3�� ���
			blk->posSubBlk3.X = blk->posMainBlk.X;
			blk->posSubBlk3.Y = blk->posMainBlk.Y - 1;
			break; }

		case 3: {
			//1�� ���
			blk->posSubBlk1.X = blk->posMainBlk.X;
			blk->posSubBlk1.Y = blk->posMainBlk.Y - 1;
			//2�� ���
			blk->posSubBlk2.X = blk->posMainBlk.X;
			blk->posSubBlk2.Y = blk->posMainBlk.Y + 1;
			//3�� ���
			blk->posSubBlk3.X = blk->posMainBlk.X + 1;
			blk->posSubBlk3.Y = blk->posMainBlk.Y;
			break; }
		}
		break;

		//������ ���
	case BlockType::L:
		switch (blk->rotateCnt)
		{
		case 0: {
			//1�� ���
			blk->posSubBlk1.X = blk->posMainBlk.X + 1;
			blk->posSubBlk1.Y = blk->posMainBlk.Y;
			//2�� ���
			blk->posSubBlk2.X = blk->posMainBlk.X + 2;
			blk->posSubBlk2.Y = blk->posMainBlk.Y;
			//3�� ���
			blk->posSubBlk3.X = blk->posMainBlk.X;
			blk->posSubBlk3.Y = blk->posMainBlk.Y + 1;
			break; }

		case 1: {
			//1�� ���
			blk->posSubBlk1.X = blk->posMainBlk.X;
			blk->posSubBlk1.Y = blk->posMainBlk.Y - 1;
			//2�� ���
			blk->posSubBlk2.X = blk->posMainBlk.X;
			blk->posSubBlk2.Y = blk->posMainBlk.Y - 2;
			//3�� ���
			blk->posSubBlk3.X = blk->posMainBlk.X + 1;
			blk->posSubBlk3.Y = blk->posMainBlk.Y;
			break; }

		case 2: {
			//1�� ���
			blk->posSubBlk1.X = blk->posMainBlk.X - 1;
			blk->posSubBlk1.Y = blk->posMainBlk.Y;
			//2�� ���
			blk->posSubBlk2.X = blk->posMainBlk.X - 2;
			blk->posSubBlk2.Y = blk->posMainBlk.Y;
			//3�� ���
			blk->posSubBlk3.X = blk->posMainBlk.X;
			blk->posSubBlk3.Y = blk->posMainBlk.Y - 1;
			break; }

		case 3: {
			//1�� ���
			blk->posSubBlk1.X = blk->posMainBlk.X;
			blk->posSubBlk1.Y = blk->posMainBlk.Y + 1;
			//2�� ���
			blk->posSubBlk2.X = blk->posMainBlk.X;
			blk->posSubBlk2.Y = blk->posMainBlk.Y + 2;
			//3�� ���
			blk->posSubBlk3.X = blk->posMainBlk.X - 1;
			blk->posSubBlk3.Y = blk->posMainBlk.Y;
			break; }
		}
		break;

		//������ ���
	case BlockType::J:
		switch (blk->rotateCnt)
		{
		case 0: {
			//1�� ���
			blk->posSubBlk1.X = blk->posMainBlk.X - 1;
			blk->posSubBlk1.Y = blk->posMainBlk.Y;
			//2�� ���
			blk->posSubBlk2.X = blk->posMainBlk.X - 2;
			blk->posSubBlk2.Y = blk->posMainBlk.Y;
			//3�� ���
			blk->posSubBlk3.X = blk->posMainBlk.X;
			blk->posSubBlk3.Y = blk->posMainBlk.Y + 1;
			break; }

		case 1: {
			//1�� ���
			blk->posSubBlk1.X = blk->posMainBlk.X;
			blk->posSubBlk1.Y = blk->posMainBlk.Y - 1;
			//2�� ���
			blk->posSubBlk2.X = blk->posMainBlk.X;
			blk->posSubBlk2.Y = blk->posMainBlk.Y - 2;
			//3�� ���
			blk->posSubBlk3.X = blk->posMainBlk.X - 1;
			blk->posSubBlk3.Y = blk->posMainBlk.Y;
			break; }

		case 2: {
			//1�� ���
			blk->posSubBlk1.X = blk->posMainBlk.X + 1;
			blk->posSubBlk1.Y = blk->posMainBlk.Y;
			//2�� ���
			blk->posSubBlk2.X = blk->posMainBlk.X + 2;
			blk->posSubBlk2.Y = blk->posMainBlk.Y;
			//3�� ���
			blk->posSubBlk3.X = blk->posMainBlk.X;
			blk->posSubBlk3.Y = blk->posMainBlk.Y - 1;
			break; }

		case 3: {
			//1�� ���
			blk->posSubBlk1.X = blk->posMainBlk.X;
			blk->posSubBlk1.Y = blk->posMainBlk.Y + 1;
			//2�� ���
			blk->posSubBlk2.X = blk->posMainBlk.X;
			blk->posSubBlk2.Y = blk->posMainBlk.Y + 2;
			//3�� ���
			blk->posSubBlk3.X = blk->posMainBlk.X + 1;
			blk->posSubBlk3.Y = blk->posMainBlk.Y;
			break; }
		}
		break;

		//������ ���
	case BlockType::Z:
		switch (blk->rotateCnt % 2)		//ȸ�� ���� ����� 2���� ����
		{
		case 0: {
			//1�� ���
			blk->posSubBlk1.X = blk->posMainBlk.X - 1;
			blk->posSubBlk1.Y = blk->posMainBlk.Y;
			//2�� ���
			blk->posSubBlk2.X = blk->posMainBlk.X;
			blk->posSubBlk2.Y = blk->posMainBlk.Y + 1;
			//3�� ���
			blk->posSubBlk3.X = blk->posMainBlk.X + 1;
			blk->posSubBlk3.Y = blk->posMainBlk.Y + 1;
			break; }

		case 1: {
			//1�� ���
			blk->posSubBlk1.X = blk->posMainBlk.X;
			blk->posSubBlk1.Y = blk->posMainBlk.Y + 1;
			//2�� ���
			blk->posSubBlk2.X = blk->posMainBlk.X + 1;
			blk->posSubBlk2.Y = blk->posMainBlk.Y;
			//3�� ���
			blk->posSubBlk3.X = blk->posMainBlk.X + 1;
			blk->posSubBlk3.Y = blk->posMainBlk.Y - 1;
			break; }
		}
		break;

		//5 ���� ���
	case BlockType::S:
		switch (blk->rotateCnt % 2)		//ȸ�� ���� ����� 2���� ����
		{
		case 0: {
			//1�� ���
			blk->posSubBlk1.X = blk->posMainBlk.X + 1;
			blk->posSubBlk1.Y = blk->posMainBlk.Y;
			//2�� ���
			blk->posSubBlk2.X = blk->posMainBlk.X;
			blk->posSubBlk2.Y = blk->posMainBlk.Y + 1;
			//3�� ���
			blk->posSubBlk3.X = blk->posMainBlk.X - 1;
			blk->posSubBlk3.Y = blk->posMainBlk.Y + 1;
			break; }

		case 1: {
			//1�� ���
			blk->posSubBlk1.X = blk->posMainBlk.X;
			blk->posSubBlk1.Y = blk->posMainBlk.Y + 1;
			//2�� ���
			blk->posSubBlk2.X = blk->posMainBlk.X - 1;
			blk->posSubBlk2.Y = blk->posMainBlk.Y;
			//3�� ���
			blk->posSubBlk3.X = blk->posMainBlk.X - 1;
			blk->posSubBlk3.Y = blk->posMainBlk.Y - 1;
			break; }
		}
		break;
	}

	//�迭�� ������� �˻��Ͽ� �����
	//unsigned���̶� 0���� ���� �� ����(����÷ο�� �ִ밪�� ������ ��)
	if (blk->posSubBlk1.X >= MAX_HOR_SIZE)
	{
		blk->posSubBlk1.X = blkPreState.posSubBlk1.X;
		blk->posSubBlk1.Y = blkPreState.posSubBlk1.Y;
		blk->posSubBlk2.X = blkPreState.posSubBlk2.X;
		blk->posSubBlk2.Y = blkPreState.posSubBlk2.Y;
		blk->posSubBlk3.X = blkPreState.posSubBlk3.X;
		blk->posSubBlk3.Y = blkPreState.posSubBlk3.Y;
		return false;
	}
	else if (blk->posSubBlk2.X >= MAX_HOR_SIZE)
	{
		blk->posSubBlk1.X = blkPreState.posSubBlk1.X;
		blk->posSubBlk1.Y = blkPreState.posSubBlk1.Y;
		blk->posSubBlk2.X = blkPreState.posSubBlk2.X;
		blk->posSubBlk2.Y = blkPreState.posSubBlk2.Y;
		blk->posSubBlk3.X = blkPreState.posSubBlk3.X;
		blk->posSubBlk3.Y = blkPreState.posSubBlk3.Y;
		return false;
	}
	else if (blk->posSubBlk3.X >= MAX_HOR_SIZE)
	{
		blk->posSubBlk1.X = blkPreState.posSubBlk1.X;
		blk->posSubBlk1.Y = blkPreState.posSubBlk1.Y;
		blk->posSubBlk2.X = blkPreState.posSubBlk2.X;
		blk->posSubBlk2.Y = blkPreState.posSubBlk2.Y;
		blk->posSubBlk3.X = blkPreState.posSubBlk3.X;
		blk->posSubBlk3.Y = blkPreState.posSubBlk3.Y;
		return false;
	}
	else if ((blk->posSubBlk1.Y >= MAX_VER_SIZE + MARGIN_BOARD)
		&& blk->posMainBlk.Y > MARGIN_BOARD)	//������ �Ʒ� ������ ��� ��쿡��(���� ���� ���� ����)
	{
		blk->posSubBlk1.X = blkPreState.posSubBlk1.X;
		blk->posSubBlk1.Y = blkPreState.posSubBlk1.Y;
		blk->posSubBlk2.X = blkPreState.posSubBlk2.X;
		blk->posSubBlk2.Y = blkPreState.posSubBlk2.Y;
		blk->posSubBlk3.X = blkPreState.posSubBlk3.X;
		blk->posSubBlk3.Y = blkPreState.posSubBlk3.Y;
		return false;
	}

	//��ġ�� �κ��� ������ �����
	if (mv_ucBoardTable[blk->posSubBlk1.X][blk->posSubBlk1.Y] != 0)
	{
		blk->posSubBlk1.X = blkPreState.posSubBlk1.X;
		blk->posSubBlk1.Y = blkPreState.posSubBlk1.Y;
		blk->posSubBlk2.X = blkPreState.posSubBlk2.X;
		blk->posSubBlk2.Y = blkPreState.posSubBlk2.Y;
		blk->posSubBlk3.X = blkPreState.posSubBlk3.X;
		blk->posSubBlk3.Y = blkPreState.posSubBlk3.Y;
		return false;
	}
	else if (mv_ucBoardTable[blk->posSubBlk2.X][blk->posSubBlk2.Y] != 0)
	{
		blk->posSubBlk1.X = blkPreState.posSubBlk1.X;
		blk->posSubBlk1.Y = blkPreState.posSubBlk1.Y;
		blk->posSubBlk2.X = blkPreState.posSubBlk2.X;
		blk->posSubBlk2.Y = blkPreState.posSubBlk2.Y;
		blk->posSubBlk3.X = blkPreState.posSubBlk3.X;
		blk->posSubBlk3.Y = blkPreState.posSubBlk3.Y;
		return false;
	}
	else if (mv_ucBoardTable[blk->posSubBlk3.X][blk->posSubBlk3.Y] != 0)
	{
		blk->posSubBlk1.X = blkPreState.posSubBlk1.X;
		blk->posSubBlk1.Y = blkPreState.posSubBlk1.Y;
		blk->posSubBlk2.X = blkPreState.posSubBlk2.X;
		blk->posSubBlk2.Y = blkPreState.posSubBlk2.Y;
		blk->posSubBlk3.X = blkPreState.posSubBlk3.X;
		blk->posSubBlk3.Y = blkPreState.posSubBlk3.Y;
		return false;
	}

	return true;
}

void GameBoard::UpdateBoardTable(Blocks* blk, bool isDropped)
{
	if ((blk->posMainBlk.Y == 0)	//���� ���� ��� ��(y=0)�� ���� �� �� ��ü ����
		|| (blk == nullptr)) {			//null���̸� ����
		return;
	}
	
	int i, j;
	for (i = 0; i < MAX_HOR_SIZE; i++)
	{
		for (j = 0; j < MAX_VER_SIZE; j++)
		{
			//���̺��� �ش��ڸ��� 2���� ������ 0���� �ʱ�ȭ
			if (mv_ucBoardTable[i][j] < 2) {
				mv_ucBoardTable[i][j] = 0;
			}
		}
	}

	//����� ���̺����� ���� (���� ��Ʈ������ ����� 1, ��Ʈ���� ���� �������� 2)
	unsigned char ucDropValue = (isDropped) ? 1 : 0;

	if (blk->posMainBlk.Y >= MARGIN_BOARD) {
		mv_ucBoardTable[blk->posMainBlk.X][blk->posMainBlk.Y] = 1 + ucDropValue;
	}
	if (blk->posSubBlk1.Y >= MARGIN_BOARD) {
		mv_ucBoardTable[blk->posSubBlk1.X][blk->posSubBlk1.Y] = 1 + ucDropValue;
	}
	if (blk->posSubBlk2.Y >= MARGIN_BOARD) {
		mv_ucBoardTable[blk->posSubBlk2.X][blk->posSubBlk2.Y] = 1 + ucDropValue;
	}
	if (blk->posSubBlk3.Y >= MARGIN_BOARD) {
		mv_ucBoardTable[blk->posSubBlk3.X][blk->posSubBlk3.Y] = 1 + ucDropValue;
	}
}

GameBoard::GameBoard()
{
	int i, j;
	//�õ� ����
	srand((unsigned int)time(NULL));

	//���� ���� �ʱ�ȭ
	for (i = 0; i < MAX_VER_SIZE; i++)
	{
		mv_wstrBoard[i] = WALL;
		for (j = 0; j < MAX_HOR_SIZE; j++)
		{
			mv_wstrBoard[i] += EMPTY;
			mv_ucBoardTable[j][i] = 0;
		}
	}

	//UI�ʱ�ȭ
	for (i = 0; i < MAX_UI_LINE; i++)
	{
		//���� ���� ��
		mv_wstrUI[i] = WALL;
		//���� �Ʒ� ��
		if (i == MAX_VER_SIZE) {
			for (j = 0; j <= MAX_HOR_SIZE; j++)
			{
				mv_wstrUI[i] += WALL;
			}
		}
		else if (i == MAX_VER_SIZE+1) {
			mv_wstrUI[i] += L"���ð���0";
		}

		else if (i == MAX_VER_SIZE+2) {
			mv_wstrUI[i] += L"��������0";
		}
	}

	curBlk = nullptr;
	nxtBlk = nullptr;
}


GameBoard::~GameBoard()
{
	delete curBlk;
	delete nxtBlk;
}

std::wstring* GameBoard::GetBoard()
{
	return mv_wstrBoard;
}

std::wstring * GameBoard::GetUI()
{
	return mv_wstrUI;
}

//��� ȸ��
void GameBoard::RotateBlock()
{
	curBlk->rotateCnt++;
	if (UpdateBlock(curBlk) == false)
	{
		curBlk->rotateCnt--;
	}
}

//������ ����� ������, ������ ����, 0�̸� �Ʒ� �̵�
void GameBoard::MoveBlock(int nDirection)
{
	if (nDirection > 0)
	{
		//���� ����� ���� ������ ����� �ʴ� ���
		if (curBlk->posMainBlk.X + 1 < MAX_HOR_SIZE) {
			curBlk->posMainBlk.X++;
			if (UpdateBlock(curBlk) == false) {
				curBlk->posMainBlk.X--;
			}
		}
	}
	else if (nDirection < 0)
	{
		//���� ����� ���� ������ ����� �ʴ� ���
		if (curBlk->posMainBlk.X - 1 >= 0) {
			curBlk->posMainBlk.X--;
			if (UpdateBlock(curBlk) == false) {
				curBlk->posMainBlk.X++;
			}
		}
	}
	else
	{
		if (curBlk->posMainBlk.Y + 1 < MAX_VER_SIZE + MARGIN_BOARD) {
			curBlk->posMainBlk.Y++;
			//�Ʒ� �̵��� �����ϸ� ����� ������ �̵��� ��
			if (UpdateBlock(curBlk) == false) {
				curBlk->posMainBlk.Y--;
				CreateNextBlock();		//���ο� ����� ������ ���� ����� �ٲ�
			}
		}
	}
}

//����� �� �ر��� �ѹ��� ����
void GameBoard::DropBlock()
{
	while (UpdateBlock(curBlk))
	{
		curBlk->posMainBlk.Y++;
	}
	curBlk->posMainBlk.Y--;
	CreateNextBlock();
}
