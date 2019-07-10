#include "pch.h"
#include "GameBoard.h"


GameBoard::GameBoard()
{
	int i, j;

	//���� ���� �ʱ�ȭ
	for (i = 0; i < MAX_VER_SIZE; i++)
	{
		mv_wstrBoard[i] = WALL;
		for (j = 0; j < MAX_HOR_SIZE; j++)
		{
			mv_wstrBoard[i] += EMPTY;
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
}


GameBoard::~GameBoard()
{
}

std::wstring* GameBoard::GetBoard()
{
	return mv_wstrBoard;
}

std::wstring * GameBoard::GetUI()
{
	return mv_wstrUI;
}
