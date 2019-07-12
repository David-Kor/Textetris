#include "pch.h"
#include "GameBoard.h"

//새 블록을 생성하며 다음 블록을 컨트롤하게 함
void GameBoard::CreateNextBlock()
{
	//다음 나올 블록을 현재 블록으로 지정
	curBlk = nxtBlk;

	if (curBlk != nullptr)
	{
		curBlk->posMainBlk.Y++;
	}

	//다음 나올 새 블록 생성
	nxtBlk = new Blocks();
	nxtBlk->rotateCnt = 0;
	//메인블록 좌표 지정
	nxtBlk->posMainBlk.X = MAX_HOR_SIZE / 2;
	nxtBlk->posMainBlk.Y = 0;
	nxtBlk->type = (BlockType)(rand() % 7);		//랜덤 타입 지정
	UpdateBlock(nxtBlk);
}

//블록의 MainBlk 위치에 따라 SubBlk위치를 갱신. 실패 시 이전상태로 되돌아감. 성공여부 반환
bool GameBoard::UpdateBlock(Blocks* blk)
{
	if (blk == nullptr) {
		return false;
	}

	Blocks blkPreState = *blk;

	//서브블록 좌표 지정
	switch (blk->type)
	{
		//ㅣ자형 블록
	case BlockType::I:
		switch (blk->rotateCnt % 2)	//회전 가능 모양이 2개만 존재
		{
		case 0: {
			//1번 블록
			blk->posSubBlk1.X = blk->posMainBlk.X - 1;
			blk->posSubBlk1.Y = blk->posMainBlk.Y;
			//2번 블록
			blk->posSubBlk2.X = blk->posMainBlk.X + 1;
			blk->posSubBlk2.Y = blk->posMainBlk.Y;
			//3번 블록
			blk->posSubBlk3.X = blk->posMainBlk.X + 2;
			blk->posSubBlk3.Y = blk->posMainBlk.Y;
			break; }

		case 1: {
			//1번 블록
			blk->posSubBlk1.X = blk->posMainBlk.X;
			blk->posSubBlk1.Y = blk->posMainBlk.Y + 1;
			//2번 블록
			blk->posSubBlk2.X = blk->posMainBlk.X;
			blk->posSubBlk2.Y = blk->posMainBlk.Y - 1;
			//3번 블록
			blk->posSubBlk3.X = blk->posMainBlk.X;
			blk->posSubBlk3.Y = blk->posMainBlk.Y - 2;
			break; }
		}
		break;

		//ㅁ자형 블록
	case BlockType::O:
		blk->posSubBlk1.X = blk->posMainBlk.X + 1;
		blk->posSubBlk1.Y = blk->posMainBlk.Y;
		blk->posSubBlk2.X = blk->posMainBlk.X;
		blk->posSubBlk2.Y = blk->posMainBlk.Y + 1;
		blk->posSubBlk2.X = blk->posMainBlk.X + 1;
		blk->posSubBlk2.Y = blk->posMainBlk.Y + 1;
		break;

		//ㅗ자형 블록
	case BlockType::T:
		switch (blk->rotateCnt)
		{
		case 0: {
			//1번 블록
			blk->posSubBlk1.X = blk->posMainBlk.X + 1;
			blk->posSubBlk1.Y = blk->posMainBlk.Y;
			//2번 블록
			blk->posSubBlk2.X = blk->posMainBlk.X - 1;
			blk->posSubBlk2.Y = blk->posMainBlk.Y;
			//3번 블록
			blk->posSubBlk3.X = blk->posMainBlk.X;
			blk->posSubBlk3.Y = blk->posMainBlk.Y - 1;
			break; }

		case 1: {
			//1번 블록
			blk->posSubBlk1.X = blk->posMainBlk.X;
			blk->posSubBlk1.Y = blk->posMainBlk.Y + 1;
			//2번 블록
			blk->posSubBlk2.X = blk->posMainBlk.X;
			blk->posSubBlk2.Y = blk->posMainBlk.Y - 1;
			//3번 블록
			blk->posSubBlk3.X = blk->posMainBlk.X - 1;
			blk->posSubBlk3.Y = blk->posMainBlk.Y;
			break; }

		case 2: {
			//1번 블록
			blk->posSubBlk1.X = blk->posMainBlk.X - 1;
			blk->posSubBlk1.Y = blk->posMainBlk.Y;
			//2번 블록
			blk->posSubBlk2.X = blk->posMainBlk.X + 1;
			blk->posSubBlk2.Y = blk->posMainBlk.Y;
			//3번 블록
			blk->posSubBlk3.X = blk->posMainBlk.X;
			blk->posSubBlk3.Y = blk->posMainBlk.Y - 1;
			break; }

		case 3: {
			//1번 블록
			blk->posSubBlk1.X = blk->posMainBlk.X;
			blk->posSubBlk1.Y = blk->posMainBlk.Y - 1;
			//2번 블록
			blk->posSubBlk2.X = blk->posMainBlk.X;
			blk->posSubBlk2.Y = blk->posMainBlk.Y + 1;
			//3번 블록
			blk->posSubBlk3.X = blk->posMainBlk.X + 1;
			blk->posSubBlk3.Y = blk->posMainBlk.Y;
			break; }
		}
		break;

		//ㄴ자형 블록
	case BlockType::L:
		switch (blk->rotateCnt)
		{
		case 0: {
			//1번 블록
			blk->posSubBlk1.X = blk->posMainBlk.X + 1;
			blk->posSubBlk1.Y = blk->posMainBlk.Y;
			//2번 블록
			blk->posSubBlk2.X = blk->posMainBlk.X + 2;
			blk->posSubBlk2.Y = blk->posMainBlk.Y;
			//3번 블록
			blk->posSubBlk3.X = blk->posMainBlk.X;
			blk->posSubBlk3.Y = blk->posMainBlk.Y + 1;
			break; }

		case 1: {
			//1번 블록
			blk->posSubBlk1.X = blk->posMainBlk.X;
			blk->posSubBlk1.Y = blk->posMainBlk.Y - 1;
			//2번 블록
			blk->posSubBlk2.X = blk->posMainBlk.X;
			blk->posSubBlk2.Y = blk->posMainBlk.Y - 2;
			//3번 블록
			blk->posSubBlk3.X = blk->posMainBlk.X + 1;
			blk->posSubBlk3.Y = blk->posMainBlk.Y;
			break; }

		case 2: {
			//1번 블록
			blk->posSubBlk1.X = blk->posMainBlk.X - 1;
			blk->posSubBlk1.Y = blk->posMainBlk.Y;
			//2번 블록
			blk->posSubBlk2.X = blk->posMainBlk.X - 2;
			blk->posSubBlk2.Y = blk->posMainBlk.Y;
			//3번 블록
			blk->posSubBlk3.X = blk->posMainBlk.X;
			blk->posSubBlk3.Y = blk->posMainBlk.Y - 1;
			break; }

		case 3: {
			//1번 블록
			blk->posSubBlk1.X = blk->posMainBlk.X;
			blk->posSubBlk1.Y = blk->posMainBlk.Y + 1;
			//2번 블록
			blk->posSubBlk2.X = blk->posMainBlk.X;
			blk->posSubBlk2.Y = blk->posMainBlk.Y + 2;
			//3번 블록
			blk->posSubBlk3.X = blk->posMainBlk.X - 1;
			blk->posSubBlk3.Y = blk->posMainBlk.Y;
			break; }
		}
		break;

		//ㄱ자형 블록
	case BlockType::J:
		switch (blk->rotateCnt)
		{
		case 0: {
			//1번 블록
			blk->posSubBlk1.X = blk->posMainBlk.X - 1;
			blk->posSubBlk1.Y = blk->posMainBlk.Y;
			//2번 블록
			blk->posSubBlk2.X = blk->posMainBlk.X - 2;
			blk->posSubBlk2.Y = blk->posMainBlk.Y;
			//3번 블록
			blk->posSubBlk3.X = blk->posMainBlk.X;
			blk->posSubBlk3.Y = blk->posMainBlk.Y + 1;
			break; }

		case 1: {
			//1번 블록
			blk->posSubBlk1.X = blk->posMainBlk.X;
			blk->posSubBlk1.Y = blk->posMainBlk.Y - 1;
			//2번 블록
			blk->posSubBlk2.X = blk->posMainBlk.X;
			blk->posSubBlk2.Y = blk->posMainBlk.Y - 2;
			//3번 블록
			blk->posSubBlk3.X = blk->posMainBlk.X - 1;
			blk->posSubBlk3.Y = blk->posMainBlk.Y;
			break; }

		case 2: {
			//1번 블록
			blk->posSubBlk1.X = blk->posMainBlk.X + 1;
			blk->posSubBlk1.Y = blk->posMainBlk.Y;
			//2번 블록
			blk->posSubBlk2.X = blk->posMainBlk.X + 2;
			blk->posSubBlk2.Y = blk->posMainBlk.Y;
			//3번 블록
			blk->posSubBlk3.X = blk->posMainBlk.X;
			blk->posSubBlk3.Y = blk->posMainBlk.Y - 1;
			break; }

		case 3: {
			//1번 블록
			blk->posSubBlk1.X = blk->posMainBlk.X;
			blk->posSubBlk1.Y = blk->posMainBlk.Y + 1;
			//2번 블록
			blk->posSubBlk2.X = blk->posMainBlk.X;
			blk->posSubBlk2.Y = blk->posMainBlk.Y + 2;
			//3번 블록
			blk->posSubBlk3.X = blk->posMainBlk.X + 1;
			blk->posSubBlk3.Y = blk->posMainBlk.Y;
			break; }
		}
		break;

		//ㄹ자형 블록
	case BlockType::Z:
		switch (blk->rotateCnt % 2)		//회전 가능 모양이 2개만 존재
		{
		case 0: {
			//1번 블록
			blk->posSubBlk1.X = blk->posMainBlk.X - 1;
			blk->posSubBlk1.Y = blk->posMainBlk.Y;
			//2번 블록
			blk->posSubBlk2.X = blk->posMainBlk.X;
			blk->posSubBlk2.Y = blk->posMainBlk.Y + 1;
			//3번 블록
			blk->posSubBlk3.X = blk->posMainBlk.X + 1;
			blk->posSubBlk3.Y = blk->posMainBlk.Y + 1;
			break; }

		case 1: {
			//1번 블록
			blk->posSubBlk1.X = blk->posMainBlk.X;
			blk->posSubBlk1.Y = blk->posMainBlk.Y + 1;
			//2번 블록
			blk->posSubBlk2.X = blk->posMainBlk.X + 1;
			blk->posSubBlk2.Y = blk->posMainBlk.Y;
			//3번 블록
			blk->posSubBlk3.X = blk->posMainBlk.X + 1;
			blk->posSubBlk3.Y = blk->posMainBlk.Y - 1;
			break; }
		}
		break;

		//5 자형 블록
	case BlockType::S:
		switch (blk->rotateCnt % 2)		//회전 가능 모양이 2개만 존재
		{
		case 0: {
			//1번 블록
			blk->posSubBlk1.X = blk->posMainBlk.X + 1;
			blk->posSubBlk1.Y = blk->posMainBlk.Y;
			//2번 블록
			blk->posSubBlk2.X = blk->posMainBlk.X;
			blk->posSubBlk2.Y = blk->posMainBlk.Y + 1;
			//3번 블록
			blk->posSubBlk3.X = blk->posMainBlk.X - 1;
			blk->posSubBlk3.Y = blk->posMainBlk.Y + 1;
			break; }

		case 1: {
			//1번 블록
			blk->posSubBlk1.X = blk->posMainBlk.X;
			blk->posSubBlk1.Y = blk->posMainBlk.Y + 1;
			//2번 블록
			blk->posSubBlk2.X = blk->posMainBlk.X - 1;
			blk->posSubBlk2.Y = blk->posMainBlk.Y;
			//3번 블록
			blk->posSubBlk3.X = blk->posMainBlk.X - 1;
			blk->posSubBlk3.Y = blk->posMainBlk.Y - 1;
			break; }
		}
		break;
	}

	//배열을 벗어나는지 검사하여 취소함
	//unsigned형이라 0보다 작을 수 없음(언더플로우로 최대값을 가지게 됨)
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
		&& blk->posMainBlk.Y > MARGIN_BOARD)	//보드판 아래 범위를 벗어날 경우에만(위쪽 범위 밖은 무시)
	{
		blk->posSubBlk1.X = blkPreState.posSubBlk1.X;
		blk->posSubBlk1.Y = blkPreState.posSubBlk1.Y;
		blk->posSubBlk2.X = blkPreState.posSubBlk2.X;
		blk->posSubBlk2.Y = blkPreState.posSubBlk2.Y;
		blk->posSubBlk3.X = blkPreState.posSubBlk3.X;
		blk->posSubBlk3.Y = blkPreState.posSubBlk3.Y;
		return false;
	}

	//곂치는 부분이 있으면 취소함
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
	if ((blk->posMainBlk.Y == 0)	//메인 블럭이 대기 중(y=0)에 있을 때 블럭 전체 무시
		|| (blk == nullptr)) {			//null값이면 무시
		return;
	}
	
	int i, j;
	for (i = 0; i < MAX_HOR_SIZE; i++)
	{
		for (j = 0; j < MAX_VER_SIZE; j++)
		{
			//테이블의 해당자리가 2보다 작으면 0으로 초기화
			if (mv_ucBoardTable[i][j] < 2) {
				mv_ucBoardTable[i][j] = 0;
			}
		}
	}

	//블록을 테이블위에 구현 (현재 컨트롤중인 블록은 1, 컨트롤이 끝난 잔재블록은 2)
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
	//시드 변경
	srand((unsigned int)time(NULL));

	//게임 보드 초기화
	for (i = 0; i < MAX_VER_SIZE; i++)
	{
		mv_wstrBoard[i] = WALL;
		for (j = 0; j < MAX_HOR_SIZE; j++)
		{
			mv_wstrBoard[i] += EMPTY;
			mv_ucBoardTable[j][i] = 0;
		}
	}

	//UI초기화
	for (i = 0; i < MAX_UI_LINE; i++)
	{
		//보드 우측 벽
		mv_wstrUI[i] = WALL;
		//보드 아래 벽
		if (i == MAX_VER_SIZE) {
			for (j = 0; j <= MAX_HOR_SIZE; j++)
			{
				mv_wstrUI[i] += WALL;
			}
		}
		else if (i == MAX_VER_SIZE+1) {
			mv_wstrUI[i] += L"　시간　0";
		}

		else if (i == MAX_VER_SIZE+2) {
			mv_wstrUI[i] += L"　점수　0";
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

//블록 회전
void GameBoard::RotateBlock()
{
	curBlk->rotateCnt++;
	if (UpdateBlock(curBlk) == false)
	{
		curBlk->rotateCnt--;
	}
}

//방향이 양수면 오른쪽, 음수면 왼쪽, 0이면 아래 이동
void GameBoard::MoveBlock(int nDirection)
{
	if (nDirection > 0)
	{
		//메인 블록이 우측 범위를 벗어나지 않는 경우
		if (curBlk->posMainBlk.X + 1 < MAX_HOR_SIZE) {
			curBlk->posMainBlk.X++;
			if (UpdateBlock(curBlk) == false) {
				curBlk->posMainBlk.X--;
			}
		}
	}
	else if (nDirection < 0)
	{
		//메인 블록이 좌측 범위를 벗어나지 않는 경우
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
			//아래 이동이 실패하면 블록이 끝까지 이동한 것
			if (UpdateBlock(curBlk) == false) {
				curBlk->posMainBlk.Y--;
				CreateNextBlock();		//새로운 블록을 생성해 현재 블록을 바꿈
			}
		}
	}
}

//블록을 맨 밑까지 한번에 내림
void GameBoard::DropBlock()
{
	while (UpdateBlock(curBlk))
	{
		curBlk->posMainBlk.Y++;
	}
	curBlk->posMainBlk.Y--;
	CreateNextBlock();
}
