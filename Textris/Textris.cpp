/*	프로젝트	: Textris(텍스트리스) -> 텍스트 + 테트리스
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

using namespace std;

//전역 변수들
Input g_Input;	//키 입력 담당 클래스
Renderer g_Renderer(MAX_WORD, MAX_LINE);		//콘솔화면 출력 담당 클래스
GameBoard g_GameBoard;
wstring g_wstrMainMenu[MAX_LINE] = {		//메인메뉴에 출력될 문자열
/*1*/		L"　　　　■■■ ■■■ ■　　　■ ■■■ ■■■　 ■■■  ■■■",
/*2*/		L"　　　　　■　 ■　　 　■　■　 　■　 ■　　■ 　■　 ■",
/*3*/		L"　　　　　■　 ■■■ 　　■　　 　■　 ■■■　 　■　  ■■■",
/*4*/		L"　　　　　■　 ■　　 　■　■　 　■　 ■　　■ 　■　 　　　■",
/*5*/		L"　　　　　■　 ■■■ ■　　　■ 　■　 ■　　■ ■■■  ■■■",
/*6*/		L"　",
/*7*/		L"■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■",
/*8*/		L"■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■",
/*9*/		L"■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■",
/*10*/		L"■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■",
/*11*/		L"■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■",
/*12*/		L"■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■",
/*13*/		L"■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■",
/*14*/		L"■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■",
/*15*/		L"■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■",
/*16*/		L"■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■",
/*17*/		L"■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■",
/*18*/		L"■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■",
/*19*/		L"",
/*20*/		L"",
/*21*/		L"",
/*22*/		L"",
/*23*/		L"",
/*24*/		L"",
/*25*/		L""
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//초기화
void InitializeSgGm()
{
	//출력버퍼 초기화
	g_Renderer.ResetBuffer();
	g_Renderer.Rendering();
	g_Renderer.ResetBuffer();

	wstring* pwstrUI = g_GameBoard.GetUI();

	//g_GameBoard.MoveBlock(0);
	g_Renderer.UpdateBuffer(pwstrUI, g_GameBoard.MAX_UI_LINE);
	g_Renderer.UpdateBuffer(pwstrUI, g_GameBoard.MAX_UI_LINE, 26);
	g_Renderer.UpdateBuffer(pwstrUI, g_GameBoard.MAX_UI_LINE, 52);
	g_Renderer.Rendering();
}

//게임 진행
void UpdateSgGm()
{
}

//1인게임 main함수
void SingleGameMain()
{
	InitializeSgGm();
}

//문자열 내에 from 문자열을 찾아 to로 바꿈
wstring* ReplaceFirstString(wstring* str, const wstring &from, const wstring &to)
{
	size_t szPos = 0;

	if ((szPos = str->find(from, szPos)) != wstring::npos)
	{
		str->replace(szPos, from.length(), to);
	}
	return str;
}


//메인 화면 출력
unsigned char MainMenuPrint(const char cMoveDirect)
{
	static unsigned char ucSelected = 1;

	static wstring strMnSingle = L"■　　　▷　1.　혼자하기　　　　　　　　　　　　　　　　　　　　　　　■\n";
	static wstring strMnMulti = L"■　　　▷　2.　같이하기　　　　　　　　　　　　　　　　　　　　　　　■\n";
	static wstring strMnQuit = L"■　　　▷　3.　끝내기　　　　　　　　　　　　　　　　　　　　　　　　■\n";

	size_t szPos = 0;
	static const wstring strNoSelected = L"▷"; //비선택 메뉴 표시
	static const wstring strSelected = L"▶";		//선택된 메뉴 표시

	//범위 제한
	ucSelected += cMoveDirect;
	if (ucSelected == 0) { ucSelected = 3; }
	else if (ucSelected == 4) { ucSelected = 1; }

	//현재 선택한 메뉴 : ▶ 표시
	//나머지 메뉴 : ▷ 표시
	switch (ucSelected)
	{
	case 1:
		ReplaceFirstString(&strMnSingle, strNoSelected, strSelected);
		ReplaceFirstString(&strMnMulti, strSelected, strNoSelected);
		ReplaceFirstString(&strMnQuit, strSelected, strNoSelected);
		break;

	case 2:
		ReplaceFirstString(&strMnMulti, strNoSelected, strSelected);
		ReplaceFirstString(&strMnSingle, strSelected, strNoSelected);
		ReplaceFirstString(&strMnQuit, strSelected, strNoSelected);
		break;
	case 3:
		ReplaceFirstString(&strMnQuit, strNoSelected, strSelected);
		ReplaceFirstString(&strMnSingle, strSelected, strNoSelected);
		ReplaceFirstString(&strMnMulti, strSelected, strNoSelected);
		break;
	}

	g_wstrMainMenu[MN_1_LINE] = strMnSingle;
	g_wstrMainMenu[MN_2_LINE] = strMnMulti;
	g_wstrMainMenu[MN_3_LINE] = strMnQuit;	

	g_Renderer.UpdateBuffer(g_wstrMainMenu, MAX_LINE);
	g_Renderer.Rendering();

	return ucSelected;
}


int main()
{
	setlocale(LC_ALL, "");	//유니코드 문자열 출력을 위한 locale설정
	unsigned char ucSelected = MainMenuPrint(0);

	while (true)
	{
		if (g_Input.IsAnyKeyDown())
		{
			switch (g_Input.GetInputKey())
			{
			case Input::UP:
				ucSelected = MainMenuPrint(-1);
				break;
			case Input::DOWN:
				ucSelected = MainMenuPrint(1);
				break;
			case Input::ENTER:
			case Input::SPACE:
				switch (ucSelected)
				{
				case SINGLE_GAME:
					SingleGameMain();
					break;
				case MULTI_GAME:
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