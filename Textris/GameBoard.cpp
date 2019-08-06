#include "pch.h"
#include "GameBoard.h"


/* private 함수 */

//새 블록을 생성하며 다음 블록을 컨트롤하게 함
void GameBoard::v_CreateNextBlock()
{
	if (m_isGameOver) { return; }

	AddScore(SCORE_BLOCK_DROP);

	//현재 블록이 nullptr가 아니면 메모리에서 삭제
	if (curBlk != nullptr)
	{
		delete curBlk;
		curBlk = nullptr;
	}
	//다음 블록이 nullptr가 아니면 좌표를 갱신 후 현재 블록으로 지정
	if (nxtBlk != nullptr)
	{
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
	nxtBlk->PositionUpdate();

	//다음 나올 블록을 UI에 출력
	for (int i = 0; i < 4; i++)
	{
		//공백으로 초기화
		mv_wstrUI[NXT_BLK_LINE_1][12 + i] = L'　';
		mv_wstrUI[NXT_BLK_LINE_2][12 + i] = L'　';
	}
	mv_wstrUI[nxtBlk->posMainBlk.Y + NXT_BLK_Y_HANDLE][nxtBlk->posMainBlk.X + NXT_BLK_X_HANDLE] = L'■';
	mv_wstrUI[nxtBlk->posSubBlk1.Y + NXT_BLK_Y_HANDLE][nxtBlk->posSubBlk1.X + NXT_BLK_X_HANDLE] = L'■';
	mv_wstrUI[nxtBlk->posSubBlk2.Y + NXT_BLK_Y_HANDLE][nxtBlk->posSubBlk2.X + NXT_BLK_X_HANDLE] = L'■';
	mv_wstrUI[nxtBlk->posSubBlk3.Y + NXT_BLK_Y_HANDLE][nxtBlk->posSubBlk3.X + NXT_BLK_X_HANDLE] = L'■';
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

	AddScore(SCORE_LINE_CLEAR * nCount);
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
	}

	//다음 나올 블록UI의 공간
	mv_wstrUI[NXT_BLK_LINE_1-1]	+= L"▣▣▣▣▣";
	mv_wstrUI[NXT_BLK_LINE_1]	+= L"　　　　▣";
	mv_wstrUI[NXT_BLK_LINE_2]	+= L"　　　　▣";
	mv_wstrUI[NXT_BLK_LINE_2+1]	+= L"▣▣▣▣▣";

	//아래 벽UI
	for (j = 0; j <= MAX_HOR_SIZE; j++)
	{
		//보드 아래 벽
		mv_wstrUI[MAX_VER_SIZE] += WALL;
		//시간,점수 UI 아래 벽
		mv_wstrUI[MAX_UI_LINE - 1] += WALL;
	}

	//시간 및 점수 UI
	mv_wstrUI[MAX_VER_SIZE + 1] += L"　시간　";
	mv_wstrUI[MAX_VER_SIZE + 2] += L"　점수　";

	curBlk = nullptr;
	nxtBlk = nullptr;
	//nxt블록과 cur블록 생성
	v_CreateNextBlock();
	v_CreateNextBlock();
	v_UpdateBlockToBoard();
	v_UpdateBoardToUI();

	//점수,시간 UI 초기화
	mv_nScore = 0;
	mv_fTime = 0.0f;
	AddScore(0);
	SetTime(mv_fTime);
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
	int result = v_UpdateBlockToBoard();

	//게임 보드 밖으로 넘어가는 실패인 경우
	if (result == OUT_OF_INDEX)
	{
		//블록이 왼쪽 끝을 넘었다면
		if (curBlk->GetMinX() < 0)
		{
			//오른쪽 한 칸만 이동 시도
			curBlk->Move(2);
			result = v_UpdateBlockToBoard();
			//실패 시 한 번 더 시도
			if (result != SUCCESS)
			{
				//오른쪽 한 칸 더 이동 시도
				curBlk->Move(2);
				result = v_UpdateBlockToBoard();
				//이번에도 실패 시 모든 이동 및 회전 취소
				if (result != SUCCESS)
				{
					curBlk->Move(1);
					curBlk->Move(1);
					curBlk->Rotate(-1);
				}
			}
		}
		//블록이 오른쪽 끝을 넘었다면
		else if (curBlk->GetMaxX() >= MAX_HOR_SIZE)
		{
			//왼쪽 한 칸만 이동 시도
			curBlk->Move(1);
			result = v_UpdateBlockToBoard();
			//실패 시 한 번 더 시도
			if (result != SUCCESS)
			{
				//왼쪽 한 칸 더 이동 시도
				curBlk->Move(1);
				result = v_UpdateBlockToBoard();
				//이번에도 실패 시 모든 이동 및 회전 취소
				if (result != SUCCESS)
				{
					curBlk->Move(2);
					curBlk->Move(2);
					curBlk->Rotate(-1);
				}
			}
		}
		//블록이 아래쪽 끝을 넘었다면
		else
		{
			//회전 취소
			curBlk->Rotate(-1);
			v_UpdateBlockToBoard();
		}
	}
	//블록과 충돌하는 실패인 경우
	else if (result == CRASH_BLOCK)
	{
		//왼쪽 한 칸만 이동 시도
		curBlk->Move(1);
		result = v_UpdateBlockToBoard();

		//성공 시 적용
		if (result == SUCCESS)
		{
			v_UpdateBoardToUI();
			return;
		}
		//실패 시 왼쪽 두 칸째 이동 시도
		else
		{
			curBlk->Move(1);
			result = v_UpdateBlockToBoard();

			//성공 시 적용
			if (result == SUCCESS)
			{
				v_UpdateBoardToUI();
				return;
			}
			//실패 시 왼쪽 이동 취소
			else
			{
				curBlk->Move(2);
				curBlk->Move(2);
			}
		}

		//왼쪽이 실패 시 오른쪽 시도
		curBlk->Move(2);
		result = v_UpdateBlockToBoard();

		if (result == SUCCESS)
		{
			v_UpdateBoardToUI();
			return;
		}
		//실패 시 오른쪽 두 칸째 이동 시도
		else
		{
			curBlk->Move(2);
			result = v_UpdateBlockToBoard();
			if (result == SUCCESS)
			{
				v_UpdateBoardToUI();
				return;
			}
			//실패 시 오른쪽 이동 취소
			else
			{
				curBlk->Move(1);
				curBlk->Move(1);
			}
		}

		//회전 취소
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

void GameBoard::SetTime(float fSec)
{
	static std::wstring wstrTimeUI = mv_wstrUI[MAX_VER_SIZE + 1];
	//소수점 첫째자리 아래로 버림
	fSec = (int)(fSec * 10) / 10.0f;

	//0.1초단위로 시간 UI갱신
	if (mv_fTime != fSec)
	{
		mv_fTime = fSec;
		wchar_t wstrTime[8] = { NULL, };
		std::swprintf(wstrTime, sizeof(wstrTime) / sizeof(wchar_t), L"%.1f", fSec);		//소수점 1자리까지 적용

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

	//현재 점수를 wstring형으로 전환
	wchar_t wstrScore[11] = { 0, };
	std::swprintf(wstrScore, sizeof(wstrScore) / sizeof(wchar_t), L"%010u", mv_nScore);
	mv_wstrUI[MAX_VER_SIZE + 2] = wstrScoreUI + wstrScore;
}

int GameBoard::GetScore()
{
	return mv_nScore;
}
