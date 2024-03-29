﻿/*	프로젝트	: Textris(텍스트리스) -> 텍스트 + 테트리스  /// (19.07.22) 이름 변경 : Textetris(텍스테트리스)
 *	제작자	: 백다윗
 *	개발시작	: 2019.07.03
 *	개발환경	: VisualStudio Community 2017 -> (19.07.16) VisualStudio Community 2019로 변경
 *	대상OS	: Windows
 *	설명		: 윈도우즈 CMD 콘솔 창(DOS)을 이용한 텍스트 기반의 테트리스 게임
 *	조작키	: 키보드 방향키(↑, ↓, ←, →) / 스페이스 바 / 엔터 / ESC키
 */
#include "pch.h"

#define	SINGLE_GAME	1
#define	MULTI_GAME	2
#define	QUIT_GAME		3

#define	MAX_WORD		80
#define	MAX_LINE			25
#define	MN_1_LINE		10
#define	MN_2_LINE		12
#define	MN_3_LINE		14

//통신 타입
#define	T_HOST		0
#define	T_CLIENT		1

#define MY_PORT		43014

#define	FPS	60		//초당 프레임 수
#define	AUTO_DOWN_DELAY		1.5f	//블록이 자동으로 내려가는 기본 시간(단위 : 초)
#define	CURRENT_VERSION	1.0		//현재 개발 버전

using namespace std;

//전역 변수들
Input g_Input;	//키 입력 담당 클래스
Renderer g_Renderer(MAX_WORD, MAX_LINE);		//콘솔화면 출력 담당 클래스
GameBoard* g_pGameBoard = nullptr;			//게임 데이터 담당 클래스
wstring g_wstrMainMenu[MAX_LINE] =		//메인메뉴에 출력될 문자열
{
/*1*/		L"　",
/*2*/		L"　　　　■■■ ■■■ ■　　　■ ■■■ ■■■　 ■■■  ■■■",
/*3*/		L"　　　　　■　 ■　　 　■　■　 　■　 ■　　■ 　■　 ■",
/*4*/		L"　　　　　■　 ■■■ 　　■　　 　■　 ■■■　 　■　  ■■■",
/*5*/		L"　　　　　■　 ■　　 　■　■　 　■　 ■　　■ 　■　 　　　■",
/*6*/		L"　　　　　■　 ■■■ ■　　　■ 　■　 ■　　■ ■■■  ■■■",
/*7*/		L"　",
/*8*/		L"■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■",
/*9*/		L"■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■",
/*10*/		L"■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■",
/*11*/		L"■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■",
/*12*/		L"■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■",
/*13*/		L"■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■",
/*14*/		L"■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■",
/*15*/		L"■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■",
/*16*/		L"■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■",
/*17*/		L"■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■",
/*18*/		L"■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■",
/*19*/		L"■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■",
/*20*/		L"　",
/*21*/		L"　",
/*22*/		L"　",
/*23*/		L"　",
/*24*/		L"　",
/*25*/		L"　"
};
bool g_isGameOver = false;		//게임 종료 여부


//함수 들
void InitializeSgGm();		//1인 게임 초기화
void UpdateSgGm(const float fDeltaTime, const float fTime);		//1인 게임 진행
void RenderSgGm();		//1인 게임 출력
void FinalizeSgGm();		//1인 게임 종료 작업
void SingleGameMain();	//1인 게임 main
void InitializeMltGm();
void UpdateMltGm(const float fDeltaTime, const float fTime);		//
void RenderMltGm();		//
void FinalizeMltGm();		//
int MultiMenuSelect();
string InputIPAddr();
void MultiGameMain();
wstring* ReplaceString(wstring* str, const wstring& from, const wstring& to);		//문자열 검색 및 치환
unsigned int MainMenuPrint(int nMoveDirect);		//메인 화면 출력

//메인 메뉴
int main()
{
	//시드 변경
	srand((unsigned int)time(NULL));
	setlocale(LC_ALL, "");	//유니코드 문자열 출력을 위한 locale설정
	unsigned int uiSelected = MainMenuPrint(0);

	while (true)
	{
		if (g_Input.IsAnyKeyDown())
		{
			switch (g_Input.GetInputKey())
			{
			case Input::UP:
				uiSelected = MainMenuPrint(-1);
				break;
			case Input::DOWN:
				uiSelected = MainMenuPrint(1);
				break;
			case Input::ENTER:
				switch (uiSelected)
				{
				case SINGLE_GAME:
					SingleGameMain();
					break;
				case MULTI_GAME:
					MultiGameMain();
					break;
				case QUIT_GAME:	//종료
					return 0;
				}
				break;
			}
		}
	}

	return -1;
}

//1인 게임 초기화
void InitializeSgGm()
{
	g_isGameOver = false;

	//출력버퍼 2개 초기화
	g_Renderer.ResetBuffer();
	g_Renderer.Rendering();
	g_Renderer.ResetBuffer();

	//전역 포인터 변수 초기화
	g_pGameBoard = new GameBoard();
	//게임보드 초기 화면 출력
	RenderSgGm();
	//1초 후 게임 시작
	Sleep(1000);
}

//1인 게임 진행
void UpdateSgGm(const float fDeltaTime, const float fTime)
{
	//타이머 변수
	static float fDwnTimer = 0;
	//블록이 자동으로 내려가는 시간
	float fDwnSpeed = AUTO_DOWN_DELAY + 0.5f;

	//30초부터 스피드가 점점 빨라짐
	if (fTime > 30)
	{
		fDwnSpeed = AUTO_DOWN_DELAY / (0.5f + 0.0083f * fTime);	//약 1/120 수준
		//최대 스피드 제한
		if (fDwnSpeed <= 0.25f)
		{
			fDwnSpeed = 0.25f;
		}
	}

	//타이머 작동
	fDwnTimer += fDeltaTime;

	g_pGameBoard->SetTime(fTime);
	//최대 속도 제한
	if (fDwnSpeed < 0.1f) { fDwnSpeed = 0.1f; }
	//일정 시간마다 자동으로 블록을 아래로 내림
	if (fDwnTimer >= fDwnSpeed)
	{
		fDwnTimer -= fDwnSpeed;
		g_pGameBoard->BlockDown();
	}

	if (g_Input.IsAnyKeyDown())
	{
		switch (g_Input.GetInputKey())
		{
		case Input::UP:
			g_pGameBoard->BlockRotate();
			break;
		case Input::DOWN:
			g_pGameBoard->BlockDown();
			fDwnTimer = 0;	//강제로 아래로 내리면 타이머 초기화
			break;
		case Input::LEFT:
			g_pGameBoard->BlockHorMove(-1);
			break;
		case Input::RIGHT:
			g_pGameBoard->BlockHorMove(1);
			break;
		case Input::SPACE:
			g_pGameBoard->DropBlock();
			fDwnTimer = 0;	//강제로 아래로 내리면 타이머 초기화
			break;
		}
	}

	if (g_pGameBoard->m_isGameOver)
	{
		g_isGameOver = true;
	}
}

//1인 게임 출력
void RenderSgGm()
{
	g_Renderer.UpdateBuffer(g_pGameBoard->GetUI(), g_pGameBoard->MAX_UI_LINE);
	g_Renderer.Rendering();
}

//1인 게임 종료 작업
void FinalizeSgGm()
{
	int i;
	int nLine = g_pGameBoard->MAX_VER_SIZE, nWord = g_pGameBoard->MAX_HOR_SIZE;
	wstring* pwstrUI = g_pGameBoard->GetUI();

	RenderSgGm();

 	for (i = nLine; i >= 0; i--)
	{
		ReplaceString(&pwstrUI[i], L"　", L"■");
		g_Renderer.UpdateBuffer(pwstrUI, nLine);
		g_Renderer.Rendering();
		Sleep(100);
	}
	//게임 보드 메모리 할당 해제
	delete g_pGameBoard;
	g_pGameBoard = nullptr;
	g_isGameOver = false;
	//출력 버퍼 초기화
	g_Renderer.ResetBuffer();
	g_Renderer.Rendering();
	g_Renderer.ResetBuffer();
	MainMenuPrint(0);
}

//1인 게임 main
void SingleGameMain()
{
	float fPrevTime = 0;	//한 프레임 실행 이전 시간 (T)
	float fCurTime = clock() * 0.001f;	//한 프레임 실행 이후 시간 (T')	 [ 단위 : 초(s) ]
	float time = 0;			//게임 내 경과 시간 (CPU 사정에 따라 실제 경과 시간과 다름)
	float acc = 0;			//누산용 변수
	float fFrameTime;		//실제 ΔT (한 프레임 처리에 걸린 시간)
	const float MAX_DELTA_TIME = 1.5f / FPS;	//최대 ΔT
	const float DELTA_TIME = 1.0f / FPS;			//기본 ΔT (지정 프레임 시간)

	//게임 초기화
	InitializeSgGm();

	//프레임
	while (true)
	{
		fPrevTime = fCurTime;			//이전 시각 (T)
		fCurTime = clock() * 0.001f;		//현재 시각 (T')
		fFrameTime = fCurTime - fPrevTime;		//한 프레임당 걸린 시간 (ΔT = T' - T)

		//최대 ΔT 제한
		if (fFrameTime > MAX_DELTA_TIME)
		{
			fFrameTime = MAX_DELTA_TIME;
		}
		//누산 변수에 ΔT 저장
		acc += fFrameTime;
		
		//지정한 기본 ΔT보다 오래 걸린 경우 지연시간을 포함하여 계산
		//누산 결과가 ΔT보다 짧은 경우 연산하지 않음
		while (acc >= DELTA_TIME)
		{
			UpdateSgGm(acc, time);	//게임 데이터 갱신
			acc -= DELTA_TIME;		//기본 ΔT만큼 빼서 지연시간을 누적 저장
			time += DELTA_TIME;	//게임 내 경과시간
		}

		//출력
		RenderSgGm();

		if (g_isGameOver) { break; }
	}

	//게임 종료
	FinalizeSgGm();
}

void InitializeMltGm()
{
}

void UpdateMltGm(const float fDeltaTime, const float fTime)
{
}

void RenderMltGm()
{
}

void FinalizeMltGm()
{
}

int MultiMenuSelect()
{
	int nSelectNum = 0;
	wstring wstrMsg[] =
	{
		L"같이하기는 1:1 대결(2인)만 지원합니다.",
		L"▶ 방 만들기 - 상대방의 참여를 기다립니다.",
		L"▷ 참여하기 - 상대의 IP를 입력하여 방에 참여합니다.",
		L"▷ 취소 - 메인 화면으로 돌아갑니다."
	};

	/* 메뉴 출력 부분 */
	//초기 메뉴 출력
	g_Renderer.ResetBuffer();
	g_Renderer.Rendering();
	g_Renderer.ResetBuffer();
	g_Renderer.UpdateBuffer(wstrMsg, 4);
	g_Renderer.Rendering();

	while (true)
	{
		if (g_Input.IsAnyKeyDown())
		{
			switch (g_Input.GetInputKey())
			{
			case Input::DOWN:	//아래 키를 입력
				nSelectNum = (nSelectNum + 1) % 3;
				break;

			case Input::UP:	//위 키를 입력
				((nSelectNum - 1) < 0) ? (nSelectNum = 2) : (nSelectNum--);
				break;
			case Input::ENTER:
			case Input::SPACE:
				return nSelectNum;
				break;
			}	//switch문 끝


			if (nSelectNum == 0)
			{
				ReplaceString(&wstrMsg[1], L"▷", L"▶");
				ReplaceString(&wstrMsg[2], L"▶", L"▷");
				ReplaceString(&wstrMsg[3], L"▶", L"▷");
			}
			else if (nSelectNum == 1)
			{
				ReplaceString(&wstrMsg[1], L"▶", L"▷");
				ReplaceString(&wstrMsg[2], L"▷", L"▶");
				ReplaceString(&wstrMsg[3], L"▶", L"▷");
			}
			else
			{
				ReplaceString(&wstrMsg[1], L"▶", L"▷");
				ReplaceString(&wstrMsg[2], L"▶", L"▷");
				ReplaceString(&wstrMsg[3], L"▷", L"▶");
			}
			//출력
			g_Renderer.UpdateBuffer(wstrMsg, 4);
			g_Renderer.Rendering();
		}
	}
}

string InputIPAddr()
{
	wstring wstrMsg[2] =
	{
		L"참여할 상대의 IP를 입력해주세요.",
		L""
	};
	g_Renderer.ResetBuffer();
	g_Renderer.UpdateBuffer(wstrMsg, 2);
	g_Renderer.Rendering();
	g_Renderer.ResetBuffer();

	while (true)
	{
		//키 입력
		if (g_Input.IsAnyKeyDown())
		{
			switch (g_Input.GetInputKey())
			{
				//숫자 0~9 , Dot(.)키
			case Input::N0:
				wstrMsg[1] += L'0';
				break;
			case Input::N1:
				wstrMsg[1] += L'1';
				break;
			case Input::N2:
				wstrMsg[1] += L'2';
				break;
			case Input::N3:
				wstrMsg[1] += L'3';
				break;
			case Input::N4:
				wstrMsg[1] += L'4';
				break;
			case Input::N5:
				wstrMsg[1] += L'5';
				break;
			case Input::N6:
				wstrMsg[1] += L'6';
				break;
			case Input::N7:
				wstrMsg[1] += L'7';
				break;
			case Input::N8:
				wstrMsg[1] += L'8';
				break;
			case Input::N9:
				wstrMsg[1] += L'9';
				break;
			case Input::DOT:
				wstrMsg[1] += L'.';
				break;
				
				//문자 한 칸 지우기
			case Input::BACKSPACE:
				if (wstrMsg[1].length() > 0)	//문자열이 비어있지 않으면
				{
					wstrMsg[1].pop_back();	//맨 뒤 글자 지우기
				}
				g_Renderer.ResetBuffer();
				break;
				
				//엔터 입력 시 반환
			case Input::ENTER:
				//wstring to string
				string strIP(wstrMsg[1].begin(), wstrMsg[1].end());
				return strIP;
				break;
			}

			g_Renderer.UpdateBuffer(wstrMsg, 2);
			g_Renderer.Rendering();
		}
	}
}

void MultiGameMain()
{
	int nMyType = MultiMenuSelect();
	SOCKET hSvSock, hSocket;
	SOCKADDR_IN tAddr = { 0, };
	//방 만들기
	if (nMyType == T_HOST)
	{
		SOCKADDR_IN tSvAddr = { 0, };
		hSvSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (hSvSock < 0)
		{
			const wstring wstrErr = L"방 생성 실패 (socket = -1 : 소켓 생성에 실패하였습니다.)";
			g_Renderer.ResetBuffer();
			g_Renderer.UpdateBuffer(&wstrErr, 1);
			g_Renderer.Rendering();
			return;
		}
		tAddr.sin_family = AF_INET;
		tAddr.sin_port = htons(MY_PORT);
		tAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
		bind(hSvSock, (SOCKADDR*)& tSvAddr, sizeof(tSvAddr));
		listen(hSvSock, 1);
		int nAddrSize = sizeof(tSvAddr);
		hSocket = accept(hSvSock, (SOCKADDR*)& tSvAddr, &nAddrSize);
	}
	//방 참여
	else if (nMyType == T_CLIENT)
	{
		string strIP = InputIPAddr();
		hSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (hSocket < 0)
		{
			const wstring wstrErr = L"방 참여 실패 (socket = -1 : 소켓 생성에 실패하였습니다.)";
			g_Renderer.ResetBuffer();
			g_Renderer.UpdateBuffer(&wstrErr, 1);
			g_Renderer.Rendering();
			return;
		}
		tAddr.sin_family = AF_INET;
		tAddr.sin_port = htons(MY_PORT);
		tAddr.sin_addr.S_un.S_addr = inet_pton(PF_INET, strIP.c_str(), nullptr);
		if (connect(hSocket, (SOCKADDR*)& tAddr, sizeof(tAddr)) < 0)
		{
			const wstring wstrErr = L"방 참여 실패 (connect = -1 : 게임이 이미 시작된 방이거나 잘못된 IP주소 입니다.)";
			g_Renderer.ResetBuffer();
			g_Renderer.UpdateBuffer(&wstrErr, 1);
			g_Renderer.Rendering();
			return;
		}
	}
	//취소
	else { return; }
	
	float fPrevTime = 0;	//한 프레임 실행 이전 시간 (T)
	float fCurTime = clock() * 0.001f;	//한 프레임 실행 이후 시간 (T')	 [ 단위 : 초(s) ]
	float time = 0;			//게임 내 경과 시간 (CPU 사정에 따라 실제 경과 시간과 다름)
	float acc = 0;			//누산용 변수
	float fFrameTime;		//실제 ΔT (한 프레임 처리에 걸린 시간)
	const float MAX_DELTA_TIME = 1.5f / FPS;	//최대 ΔT
	const float DELTA_TIME = 1.0f / FPS;			//기본 ΔT (지정 프레임 시간)

	//게임 초기화
	InitializeMltGm();
	return;
	//프레임
	while (true)
	{
		fPrevTime = fCurTime;			//이전 시각 (T)
		fCurTime = clock() * 0.001f;		//현재 시각 (T')
		fFrameTime = fCurTime - fPrevTime;		//한 프레임당 걸린 시간 (ΔT = T' - T)

		//최대 ΔT 제한
		if (fFrameTime > MAX_DELTA_TIME)
		{
			fFrameTime = MAX_DELTA_TIME;
		}
		//누산 변수에 ΔT 저장
		acc += fFrameTime;

		//지정한 기본 ΔT보다 오래 걸린 경우 지연시간을 포함하여 계산
		//누산 결과가 ΔT보다 짧은 경우 연산하지 않음
		while (acc >= DELTA_TIME)
		{
			UpdateMltGm(acc, time);	//게임 데이터 갱신
			acc -= DELTA_TIME;		//기본 ΔT만큼 빼서 지연시간을 누적 저장
			time += DELTA_TIME;	//게임 내 경과시간
		}

		//출력
		RenderMltGm();

		if (g_isGameOver) { break; }
	}

	//게임 종료
	FinalizeMltGm();
}

//str 문자열 내에 from 문자열을 찾아 to로 바꿈
wstring* ReplaceString(wstring* str, const wstring &from, const wstring &to)
{
	size_t szPos = 0;

	while ((szPos = str->find(from, szPos)) != wstring::npos)
	{
		str->replace(szPos, from.length(), to);
	}
	return str;
}

//메인 화면 출력
unsigned int MainMenuPrint(int nMoveDirect)
{
	static unsigned int uiSelected = 1;

	static wstring strMnSingle = L"■　　　▷　1.　혼자하기　　　　　　　　　　　　　　　　　　　　　　　■\n";
	static wstring strMnMulti = L"■　　　▷　2.　같이하기(미구현상태)　　　　　　　　　　　　　　　　　■\n";
	static wstring strMnQuit = L"■　　　▷　3.　끝내기　　　　　　　　　　　　　　　　　　　　　　　　■\n";

	size_t szPos = 0;
	static const wstring strNoSelected = L"▷"; //비선택 메뉴 표시
	static const wstring strSelected = L"▶";		//선택된 메뉴 표시

	//범위 제한
	uiSelected += nMoveDirect;
	if (uiSelected == 0) { uiSelected = 3; }
	else if (uiSelected == 4) { uiSelected = 1; }

	//현재 선택한 메뉴 : ▶ 표시
	//나머지 메뉴 : ▷ 표시
	switch (uiSelected)
	{
	case 1:
		ReplaceString(&strMnSingle, strNoSelected, strSelected);
		ReplaceString(&strMnMulti, strSelected, strNoSelected);
		ReplaceString(&strMnQuit, strSelected, strNoSelected);
		break;

	case 2:
		ReplaceString(&strMnMulti, strNoSelected, strSelected);
		ReplaceString(&strMnSingle, strSelected, strNoSelected);
		ReplaceString(&strMnQuit, strSelected, strNoSelected);
		break;
	case 3:
		ReplaceString(&strMnQuit, strNoSelected, strSelected);
		ReplaceString(&strMnSingle, strSelected, strNoSelected);
		ReplaceString(&strMnMulti, strSelected, strNoSelected);
		break;
	}

	g_wstrMainMenu[MN_1_LINE] = strMnSingle;
	g_wstrMainMenu[MN_2_LINE] = strMnMulti;
	g_wstrMainMenu[MN_3_LINE] = strMnQuit;	

	g_Renderer.UpdateBuffer(g_wstrMainMenu, MAX_LINE);
	g_Renderer.Rendering();

	return uiSelected;
}
