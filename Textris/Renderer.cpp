#include "pch.h"
#include "Renderer.h"

Renderer::Renderer(const short sMaxWord, const short sMaxLine) :mv_sMAXWORD(sMaxWord), mv_sMAXLINE(sMaxLine)
{
	/*���� ����*/
	COORD size = { mv_sMAXWORD, mv_sMAXLINE }; //������ ũ�� ���� ����ä
	SMALL_RECT rect; //â ũ�� ���� ����ü
	rect.Left = 0;
	rect.Right = mv_sMAXWORD - 1;
	rect.Top = 0;
	rect.Bottom = mv_sMAXLINE - 1;

	//ù��° ���� ����
	mv_hBuffer[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE,
		0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL); //���� ����
	SetConsoleScreenBufferSize(mv_hBuffer[0], size); //�ܼ� ������ ũ�� ����
	SetConsoleWindowInfo(mv_hBuffer[0], TRUE, &rect); //�ܼ� â�� ũ�� ����

	//�ι�° ���� ����
	mv_hBuffer[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE,
		0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL); //���� ����
	SetConsoleScreenBufferSize(mv_hBuffer[1], size); //�ܼ� ������ ũ�� ����
	SetConsoleWindowInfo(mv_hBuffer[1], TRUE, &rect); //�ܼ� â�� ũ�� ����
	
	//ù��° ���۸� ����
	mv_nScreenIndex = 0;
}


Renderer::~Renderer()
{
	//���� ����
	{
		CloseHandle(mv_hBuffer[0]);
		CloseHandle(mv_hBuffer[1]);
	}
}

//���� ���� (Ŀ����ġ 0,0)
void Renderer::UpdateBuffer(const std::wstring *pwStr, const size_t &count)
{
	DWORD dw;   //��ǥ�� �����ϱ� ���� ����ä�� ����.
	COORD CursorPosition = { 0, 0 };    //��ǥ ����

	SetConsoleCursorPosition(mv_hBuffer[mv_nScreenIndex], CursorPosition);    //��ǥ �̵�

	for (size_t i = 0; i < count; i++, CursorPosition.Y++)
	{
		SetConsoleCursorPosition(mv_hBuffer[mv_nScreenIndex], CursorPosition);    //��ǥ �̵�
		WriteConsoleW(mv_hBuffer[mv_nScreenIndex], pwStr[i].c_str(), pwStr[i].length(), &dw, NULL);		//���ۿ� ��
	}
}

//Ŀ����ġ ����
void Renderer::UpdateBuffer(const std::wstring *pwStr, const size_t &count, const short cursorX)
{
	DWORD dw;   //��ǥ�� �����ϱ� ���� ����ä�� ����.
	COORD CursorPosition = { cursorX, 0 };    //��ǥ ����

	SetConsoleCursorPosition(mv_hBuffer[mv_nScreenIndex], CursorPosition);    //��ǥ �̵�
	
	for (size_t i = 0; i < count; i++, CursorPosition.Y++)
	{
		SetConsoleCursorPosition(mv_hBuffer[mv_nScreenIndex], CursorPosition);    //��ǥ �̵�
		WriteConsoleW(mv_hBuffer[mv_nScreenIndex], pwStr[i].c_str(), pwStr[i].length(), &dw, NULL);		//���ۿ� ��
	}
}

//���� ��ȯ(Flipping)
void Renderer::Rendering()
{
	SetConsoleActiveScreenBuffer(mv_hBuffer[mv_nScreenIndex]);    //������ ���� ���
	mv_nScreenIndex = !mv_nScreenIndex;   //���� ���� ����
}

//���� ���� �����(�������� ä��)
void Renderer::ResetBuffer()
{
	COORD Coor = { 0, 0 };	//���� ��ǥ
	DWORD dw;
	FillConsoleOutputCharacter(mv_hBuffer[mv_nScreenIndex], L'��', mv_sMAXWORD * mv_sMAXLINE, Coor, &dw);	//���ۿ� ��� ������ �������� ä��
}