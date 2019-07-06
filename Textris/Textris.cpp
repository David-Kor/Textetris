#include "pch.h"
#define	SINGLE_GAME	1
#define	MULTI_GAME	2
#define	QUIT_GAME		3

using namespace std;

Input g_Input;

//초기화
void InitializeSgGm()
{
	system("cls");
	//GameBoard();
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
string* ReplaceFirstString(string* str, const string &from, const string &to)
{
	size_t szPos = 0;

	if ((szPos = str->find(from, szPos)) != string::npos)
	{
		str->replace(szPos, from.length(), to);
	}
	return str;
}


//메인 화면 출력
unsigned char MainMenuPrint(const char cMoveDirect)
{
	static unsigned char ucSelected = 1;

	system("cls");
	string strMnSingle = "■　　　▷　1.　혼자하기　　　　　　　　　　　　　　　　　　　　　　　■";
	string strMnMulti = "■　　　▷　2.　같이하기　　　　　　　　　　　　　　　　　　　　　　　■";
	string strMnQuit = "■　　　▷　3.　끝내기　　　　　　　　　　　　　　　　　　　　　　　　■";

	size_t szPos = 0;
	string strNoSelected = "▷";
	string strSelected = "▶";

	//범위 제한
	ucSelected += cMoveDirect;
	if (ucSelected == 0) { ucSelected = 3; }
	else if (ucSelected == 4) { ucSelected = 1; }

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

	cout << endl;
	cout << "　　　　■■■ ■■■ ■　　　■ ■■■ ■■■　 ■■■  ■■■" << endl;
	cout << "　　　　　■　 ■　　 　■　■　 　■　 ■　　■ 　■　 ■" << endl;
	cout << "　　　　　■　 ■■■ 　　■　　 　■　 ■■■　 　■　  ■■■" << endl;
	cout << "　　　　　■　 ■　　 　■　■　 　■　 ■　　■ 　■　 　　　■" << endl;
	cout << "　　　　　■　 ■■■ ■　　　■ 　■　 ■　　■ ■■■  ■■■" << endl;
	cout << endl;
	cout << "■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■" << endl;
	cout << "■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■" << endl;
	cout << "■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■" << endl;
	cout << "■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■" << endl;
	cout << strMnSingle << endl;
	cout << "■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■" << endl;
	cout << strMnMulti << endl;
	cout << "■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■" << endl;
	cout << strMnQuit << endl;
	cout << "■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■" << endl;
	cout << "■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■" << endl;
	cout << "■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■" << endl;
	cout << "■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■" << endl;

	return ucSelected;
}


int main()
{
	setlocale(LC_ALL, "");	//유니코드 문자열 출력을 위한 locale설정
	unsigned char ucSelected = MainMenuPrint(0);
	int i;

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