#include "pch.h"
#include "GameBoard.h"


/* private 함수 */

//새 블록을 생성하며 다음 블록을 컨트롤하게 함
void GameBoard::v_CreateNextBlock()
{
	if (m_isGameOver) { return; }

	//현재 블록이 nullptr가 아니면 메모리에서 삭제
	if (curBlk != nullptr)
	{
		delete curBlk;
		curBlk = nullptr;
	}
	//다음 블록이 nullptr가 아니면 좌표를 갱신 후 현재 블록으로 지정
	if (nxtBlk != nullptr)
	{
		nxtBlk->PositionUpdate();
		curBlk = nxtBlk;	//다음 나올 블록을 현재 블록으로 지정
		nxtBlk = nullptr;
		//블록 갱신에 실패하면 게임 종료
		if (v_UpdateBlockToBoard() != SUCCESS)
		{
			//마지막 블럭 출력
			if (curBlk->posMainBlk.Y >= 0) { mv_unBoardTable[curBlk->posMainBlk.Y][curBlk->posMainBlk.X] = 2; }
			if (curBlk->posSubBlk1.Y >= 0) { mv_unBoardTable[curBlk->posSubBlk1.Y][curBlk->posSubBlk1.X] = 2; }
			if (curBlk->posSubBlk2.Y >= 0) { mv_unBoardTable[curBlk->posSubBlk2.Y][curBlk->posSubBlk2.X] = 2; }
			if (curBlk->posSubBlk3.Y >= 0) { mv_unBoardTable[curBlk->posSubBlk3.Y][curBlk->posSubBlk3.X] = 2; }
			v_UpdateBoardToUI();
			//게임 종료상태 true
			m_isGameOver = true;
			return;
		}
	}

	nxtBlk = new Blocks();	//다음 나올 새 블록 생성
	nxtBlk->SetXPositionToCenter(MAX_HOR_SIZE);	//블록을 가운데에 배치
}

//curBlk의 좌표를 테이블에 적용 시도 후 결과 반환 -> 인덱스 벗어남(-2), 블록 곂침(-1), 널값 참조(0), 성공(1 이상)
int GameBoard::v_UpdateBlockToBoard()
{
	if (curBlk == nullptr) { return NULL_REFERENCE; }

	//블록이 보드 밖으로 나가면 실패 반환
	if (curBlk->GetMaxY() >= MAX_VER_SIZE ||
		curBlk->GetMaxX() >= MAX_HOR_SIZE ||
		curBlk->GetMinX() < 0)
	{
		return OUT_OF_INDEX;
	}

	//블록이 곂치면 실패 반환
	//Y좌표가 보드 내에 있는 블록만 충돌검사
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

	//게임 보드보다 위쪽의 좌표(Y < 0)는 무시
	if (curBlk->posMainBlk.Y >= 0) { mv_unBoardTable[curBlk->posMainBlk.Y][curBlk->posMainBlk.X] = 1; }
	if (curBlk->posSubBlk1.Y >= 0) { mv_unBoardTable[curBlk->posSubBlk1.Y][curBlk->posSubBlk1.X] = 1; }
	if (curBlk->posSubBlk2.Y >= 0) { mv_unBoardTable[curBlk->posSubBlk2.Y][curBlk->posSubBlk2.X] = 1; }
	if (curBlk->posSubBlk3.Y >= 0) { mv_unBoardTable[curBlk->posSubBlk3.Y][curBlk->posSubBlk3.X] = 1; }

	//성공 반환
	return SUCCESS;
}

//테이블의 내용을 출력될 UI에 적용
void GameBoard::v_UpdateBoardToUI()
{
	if (m_isGameOver) { return; }

	int i, j;
	for (i = 0; i < MAX_VER_SIZE; i++)
	{
		for (j = 0; j < MAX_HOR_SIZE; j++)
		{
			//테이블 값이 0이면 빈 칸
			if (mv_unBoardTable[i][j] == 0) { mv_wstrUI[i][j + 1] = EMPTY; }
			//0이 아니면 블록(■)
			else { mv_wstrUI[i][j + 1] = BLOCK; }
		}
	}
}

//가득찬 라인을 검사하여 제거
void GameBoard::v_CheckFullLine()
{
	int i, j;
	int nBlkCnt = 0, nLnCnt = 0;
	for (i = 0; i < MAX_VER_SIZE; i++)
	{
		nBlkCnt = 0;
		for (j = 0; j < MAX_HOR_SIZE; j++)
		{
			if (mv_unBoardTable[i][j] == 2) { nBlkCnt++; }		//한 줄에 블록이 몇 개인지 셈
		}
		//i번 라인이 가득찬 라인이면
		if (nBlkCnt >= MAX_HOR_SIZE)
		{
			nLnCnt++;	//라인 카운트 추가
		}
		//i번 라인이 가득차있지 않고 라인 카운트가 1이상이면
		else if (nLnCnt > 0)
		{
			v_DeleteLine(i - 1, nLnCnt);	//i라인의 윗라인을 라인 카운트만큼 제거
			nLnCnt = 0;
		}
	}

	//가장 아랫라인부터 가득찬 경우
	if (nLnCnt > 0)
	{
		v_DeleteLine(MAX_VER_SIZE - 1, nLnCnt);
	}
}

//테이블 내 블록이 가득 찬 라인 제거함수
void GameBoard::v_DeleteLine(int nLine, int nCount)
{
	int i, j;
	//범위 1~nLine
	for (i = nLine; i >= nCount; i--)
	{
		for (j = 0; j < MAX_HOR_SIZE; j++)
		{
			//i번 라인의 내용을 i-nCount라인의 내용으로 바꿈
			mv_unBoardTable[i][j] = mv_unBoardTable[i - nCount][j];
		}
	}

	//0~nCount라인 초기화
	for (i = 0; i < nCount; i++)
	{
		for (j = 0; j < MAX_HOR_SIZE; j++)
		{
			mv_unBoardTable[i][j] = 0;
		}
	}
}


/* public 함수 */

//생성자
GameBoard::GameBoard()
{
	int i, j;

	//게임 보드 초기화
	for (i = 0; i < MAX_VER_SIZE; i++)
	{
		for (j = 0; j < MAX_HOR_SIZE; j++)
		{
			mv_unBoardTable[i][j] = 0;
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

	//임시로 해놓음
	v_CreateNextBlock();
	v_CreateNextBlock();
	v_UpdateBlockToBoard();
	v_UpdateBoardToUI();
}

//소멸자
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

//블록 회전
void GameBoard::BlockRotate()
{
	if (curBlk == nullptr || m_isGameOver) { return; }
	
	//테이블에서 회전하기 전의 자리들을 0으로 초기화
	if (curBlk->posMainBlk.Y >= 0) { mv_unBoardTable[curBlk->posMainBlk.Y][curBlk->posMainBlk.X] = 0; }
	if (curBlk->posSubBlk1.Y >= 0) { mv_unBoardTable[curBlk->posSubBlk1.Y][curBlk->posSubBlk1.X] = 0; }
	if (curBlk->posSubBlk2.Y >= 0) { mv_unBoardTable[curBlk->posSubBlk2.Y][curBlk->posSubBlk2.X] = 0; }
	if (curBlk->posSubBlk3.Y >= 0) { mv_unBoardTable[curBlk->posSubBlk3.Y][curBlk->posSubBlk3.X] = 0; }
	//회전
	curBlk->Rotate(1);
	//적용 시도
	if (v_UpdateBlockToBoard() != SUCCESS)
	{
		//실패 시 회전 취소
		curBlk->Rotate(-1);
		v_UpdateBlockToBoard();
	}
	//출력UI에 적용
	v_UpdateBoardToUI();
}

//방향이 음수면 왼쪽, 아니면 오른쪽 이동
void GameBoard::BlockHorMove(int nDirection)
{
	if (curBlk == nullptr || m_isGameOver) { return; }

	//테이블에서 이동하기 전의 자리들을 0으로 초기화
	if (curBlk->posMainBlk.Y >= 0) { mv_unBoardTable[curBlk->posMainBlk.Y][curBlk->posMainBlk.X] = 0; }
	if (curBlk->posSubBlk1.Y >= 0) { mv_unBoardTable[curBlk->posSubBlk1.Y][curBlk->posSubBlk1.X] = 0; }
	if (curBlk->posSubBlk2.Y >= 0) { mv_unBoardTable[curBlk->posSubBlk2.Y][curBlk->posSubBlk2.X] = 0; }
	if (curBlk->posSubBlk3.Y >= 0) { mv_unBoardTable[curBlk->posSubBlk3.Y][curBlk->posSubBlk3.X] = 0; }
	//왼쪽 이동
	if (nDirection < 0)
	{
		curBlk->Move(1);
		//적용 시도
		if (v_UpdateBlockToBoard() <= 0)
		{
			//실패 시 이동 취소
			curBlk->Move(2);
			v_UpdateBlockToBoard();
		}
	}
	//오른쪽 이동
	else
	{
		curBlk->Move(2);
		//적용 시도
		if (v_UpdateBlockToBoard() <= 0)
		{
			//실패 시 이동 취소
			curBlk->Move(1);
			v_UpdateBlockToBoard();
		}
	}
	//출력 UI에 적용
	v_UpdateBoardToUI();
}

//블록을 한 칸 아래로 내림
void GameBoard::BlockDown()
{
	if (curBlk == nullptr || m_isGameOver) { return; }

	int sResult;
	//테이블에서 이동하기 전의 자리들을 0으로 초기화
	if (curBlk->posMainBlk.Y >= 0) { mv_unBoardTable[curBlk->posMainBlk.Y][curBlk->posMainBlk.X] = 0; }
	if (curBlk->posSubBlk1.Y >= 0) { mv_unBoardTable[curBlk->posSubBlk1.Y][curBlk->posSubBlk1.X] = 0; }
	if (curBlk->posSubBlk2.Y >= 0) { mv_unBoardTable[curBlk->posSubBlk2.Y][curBlk->posSubBlk2.X] = 0; }
	if (curBlk->posSubBlk3.Y >= 0) { mv_unBoardTable[curBlk->posSubBlk3.Y][curBlk->posSubBlk3.X] = 0; }
	//한 칸 아래로 이동
	curBlk->Move(-1);
	//적용 시도
	sResult = v_UpdateBlockToBoard();
	//실패 시 이동 취소
	if (sResult <= 0)
	{
		curBlk->Move(0);
		v_UpdateBlockToBoard();
		//null값 참조에 의한 실패가 아닌 경우(블록이 더이상 내려갈 수 없는 경우)
		if (sResult != NULL_REFERENCE)
		{
			//블록들의 좌표에 고정 블록값(2)을 적용
			if (curBlk->posMainBlk.Y >= 0) { mv_unBoardTable[curBlk->posMainBlk.Y][curBlk->posMainBlk.X] = 2; }
			if (curBlk->posSubBlk1.Y >= 0) { mv_unBoardTable[curBlk->posSubBlk1.Y][curBlk->posSubBlk1.X] = 2; }
			if (curBlk->posSubBlk2.Y >= 0) { mv_unBoardTable[curBlk->posSubBlk2.Y][curBlk->posSubBlk2.X] = 2; }
			if (curBlk->posSubBlk3.Y >= 0) { mv_unBoardTable[curBlk->posSubBlk3.Y][curBlk->posSubBlk3.X] = 2; }
			v_CheckFullLine();
			//새 블록 생성
			v_CreateNextBlock();
		}
	}
	//출력 UI에 적용
	v_UpdateBoardToUI();
}

//블록을 맨 밑까지 한번에 내림
void GameBoard::DropBlock()
{
	if (curBlk == nullptr || m_isGameOver) { return; }

	int sResult = SUCCESS;
	
	while (sResult == SUCCESS)
	{
		//테이블에서 이동하기 전의 자리들을 0으로 초기화
		if (curBlk->posMainBlk.Y >= 0) { mv_unBoardTable[curBlk->posMainBlk.Y][curBlk->posMainBlk.X] = 0; }
		if (curBlk->posSubBlk1.Y >= 0) { mv_unBoardTable[curBlk->posSubBlk1.Y][curBlk->posSubBlk1.X] = 0; }
		if (curBlk->posSubBlk2.Y >= 0) { mv_unBoardTable[curBlk->posSubBlk2.Y][curBlk->posSubBlk2.X] = 0; }
		if (curBlk->posSubBlk3.Y >= 0) { mv_unBoardTable[curBlk->posSubBlk3.Y][curBlk->posSubBlk3.X] = 0; }
		//한 칸 아래로 이동
		curBlk->Move(-1);
		//적용 시도
		sResult = v_UpdateBlockToBoard();
		//실패 시 이동 취소
		if (sResult != SUCCESS)
		{
			curBlk->Move(0);
			v_UpdateBlockToBoard();
			//null값 참조에 의한 실패가 아닌 경우(블록이 더이상 내려갈 수 없는 경우)
			if (sResult != NULL_REFERENCE)
			{
				//블록들의 좌표에 고정 블록값(2)을 적용
				if (curBlk->posMainBlk.Y >= 0) { mv_unBoardTable[curBlk->posMainBlk.Y][curBlk->posMainBlk.X] = 2; }
				if (curBlk->posSubBlk1.Y >= 0) { mv_unBoardTable[curBlk->posSubBlk1.Y][curBlk->posSubBlk1.X] = 2; }
				if (curBlk->posSubBlk2.Y >= 0) { mv_unBoardTable[curBlk->posSubBlk2.Y][curBlk->posSubBlk2.X] = 2; }
				if (curBlk->posSubBlk3.Y >= 0) { mv_unBoardTable[curBlk->posSubBlk3.Y][curBlk->posSubBlk3.X] = 2; }
				v_CheckFullLine();
				//새 블록 생성
				v_CreateNextBlock();
			}
		}
	}
	//출력 UI에 적용
	v_UpdateBoardToUI();
}
