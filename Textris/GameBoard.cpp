#include "pch.h"
#include "GameBoard.h"

/* private 함수 */

//새 블록을 생성하며 다음 블록을 컨트롤하게 함
//DONE
void GameBoard::CreateNextBlock()
{
	//다음 나올 블록을 현재 블록으로 지정
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

	//다음 나올 새 블록 생성
	nxtBlk = new Blocks();
	//메인블록을 가운데에 배치
	nxtBlk->posMainBlk.X = MAX_HOR_SIZE / 2;
}

//테이블의 내용을 출력될 UI에 적용
void GameBoard::UpdateBoard()
{
	int i, j;
	for (i = 0; i < MAX_VER_SIZE; i++)
	{
		for (j = 0; j < MAX_HOR_SIZE; j++)
		{
			//테이블 값이 0이면 빈 칸
			if (mv_ucBoardTable[i][j] == 0) { mv_wstrUI[i][j + 1] = EMPTY; }
			//0이 아니면 블록(■)
			else { mv_wstrUI[i][j + 1] = BLOCK; }
		}
	}
}

/* public 함수 */

//생성자
//DONE
GameBoard::GameBoard()
{
	int i, j;

	//게임 보드 초기화
	for (i = 0; i < MAX_VER_SIZE; i++)
	{
		for (j = 0; j < MAX_HOR_SIZE; j++)
		{
			mv_ucBoardTable[i][j] = 0;
		}
	}

	//UI초기화
	for (i = 0; i < MAX_UI_LINE; i++)
	{
		//보드 좌측 벽
		mv_wstrUI[i] = WALL;
		//보드 내용
		if (i < MAX_VER_SIZE)
		{
			for (j = 0; j < MAX_HOR_SIZE; j++)
			{
				mv_wstrUI[i] += EMPTY;
			}
			//보드 우측 벽
			mv_wstrUI[i] += WALL;
		}
		//보드 아래 벽
		else if (i == MAX_VER_SIZE)
		{
			for (j = 0; j <= MAX_HOR_SIZE; j++)
			{
				mv_wstrUI[i] += WALL; 
			}
		}
		else if (i == MAX_VER_SIZE + 1)
		{
			mv_wstrUI[i] += L"　시간　0";
		}

		else if (i == MAX_VER_SIZE + 2)
		{
			mv_wstrUI[i] += L"　점수　0";
		}
	}

	curBlk = nullptr;
	nxtBlk = nullptr;

	CreateNextBlock();
	CreateNextBlock();
	UpdateBoard();
}

//소멸자
GameBoard::~GameBoard()
{
	delete curBlk;
	delete nxtBlk;
}

std::wstring * GameBoard::GetUI()
{
	return mv_wstrUI;
}

//블록 회전
void GameBoard::RotateBlock()
{
}

//방향이 양수면 오른쪽, 음수면 왼쪽, 0이면 아래 이동
void GameBoard::MoveBlock(short sDirection)
{
}

//블록을 맨 밑까지 한번에 내림
void GameBoard::DropBlock()
{
}
