#include "pch.h"
#include "Renderer.h"

Renderer::Renderer(const short sMaxWord, const short sMaxLine) :mv_sMAXWORD(sMaxWord), mv_sMAXLINE(sMaxLine)
{
	/*버퍼 생성*/
	COORD size = { mv_sMAXWORD, mv_sMAXLINE }; //버퍼의 크기 관련 구조채
	SMALL_RECT rect; //창 크기 관련 구조체
	rect.Left = 0;
	rect.Right = mv_sMAXWORD - 1;
	rect.Top = 0;
	rect.Bottom = mv_sMAXLINE - 1;

	//첫번째 버퍼 생성
	mv_hBuffer[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE,
		0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL); //버퍼 생성
	SetConsoleScreenBufferSize(mv_hBuffer[0], size); //콘솔 버퍼의 크기 설정
	SetConsoleWindowInfo(mv_hBuffer[0], TRUE, &rect); //콘솔 창의 크기 설정

	//두번째 버퍼 생성
	mv_hBuffer[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE,
		0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL); //버퍼 생성
	SetConsoleScreenBufferSize(mv_hBuffer[1], size); //콘솔 버퍼의 크기 설정
	SetConsoleWindowInfo(mv_hBuffer[1], TRUE, &rect); //콘솔 창의 크기 설정
	
	//첫번째 버퍼를 선택
	mv_nScreenIndex = 0;
}


Renderer::~Renderer()
{
	//버퍼 해제
	{
		CloseHandle(mv_hBuffer[0]);
		CloseHandle(mv_hBuffer[1]);
	}
}

//버퍼 쓰기 (커서위치 0,0)
void Renderer::UpdateBuffer(const std::wstring *pwStr, const size_t &count)
{
	DWORD dw;   //좌표를 저장하기 위한 구조채를 선언.
	COORD CursorPosition = { 0, 0 };    //좌표 설정

	SetConsoleCursorPosition(mv_hBuffer[mv_nScreenIndex], CursorPosition);    //좌표 이동

	for (size_t i = 0; i < count; i++, CursorPosition.Y++)
	{
		SetConsoleCursorPosition(mv_hBuffer[mv_nScreenIndex], CursorPosition);    //좌표 이동
		WriteConsoleW(mv_hBuffer[mv_nScreenIndex], pwStr[i].c_str(), pwStr[i].length(), &dw, NULL);		//버퍼에 씀
	}
}

//커서위치 지정
void Renderer::UpdateBuffer(const std::wstring *pwStr, const size_t &count, const short cursorX)
{
	DWORD dw;   //좌표를 저장하기 위한 구조채를 선언.
	COORD CursorPosition = { cursorX, 0 };    //좌표 설정

	SetConsoleCursorPosition(mv_hBuffer[mv_nScreenIndex], CursorPosition);    //좌표 이동
	
	for (size_t i = 0; i < count; i++, CursorPosition.Y++)
	{
		SetConsoleCursorPosition(mv_hBuffer[mv_nScreenIndex], CursorPosition);    //좌표 이동
		WriteConsoleW(mv_hBuffer[mv_nScreenIndex], pwStr[i].c_str(), pwStr[i].length(), &dw, NULL);		//버퍼에 씀
	}
}

//버퍼 전환(Flipping)
void Renderer::Rendering()
{
	SetConsoleActiveScreenBuffer(mv_hBuffer[mv_nScreenIndex]);    //버퍼의 내용 출력
	mv_nScreenIndex = !mv_nScreenIndex;   //다음 버퍼 선택
}

//버퍼 문자 지우기(공백으로 채움)
void Renderer::ResetBuffer()
{
	COORD Coor = { 0, 0 };	//시작 좌표
	DWORD dw;
	FillConsoleOutputCharacter(mv_hBuffer[mv_nScreenIndex], L'　', mv_sMAXWORD * mv_sMAXLINE, Coor, &dw);	//버퍼에 모든 내용을 공백으로 채움
}