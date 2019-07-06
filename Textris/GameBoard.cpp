#include "pch.h"
#include "GameBoard.h"


GameBoard::GameBoard()
{
	for (int i = 0; i < MAX_VER_SIZE; i++)
	{
		mv_strBoard[i] = L"";
		for (int j = 0; j < MAX_HOR_SIZE; j++)
		{
			mv_strBoard[i] += L'¡¡';
		}
	}

	mv_strMargin[0] = L"";
}


GameBoard::~GameBoard()
{
}
