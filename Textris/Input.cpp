#include "pch.h"
#include "Input.h"

Input::Input()
{
}


Input::~Input()
{
}

bool Input::IsAnyKeyDown()
{
	return (bool)_kbhit();
}

//키 입력을 받아 어떤 키를 입력했는지 알려줌
Input::KeyList Input::GetInputKey()
{
	switch (int nInputKeyCode = _getch())
	{
	case 224:		//Arrow Key
		switch (nInputKeyCode = _getch())
		{
		case 72:		//Up
			return KeyList::UP;

		case 80:		//Down
			return KeyList::DOWN;

		case 75:		//Left
			return KeyList::LEFT;

		case 77:		//Right
			return KeyList::RIGHT;

		default:
			return KeyList::ANOTHER;
		}
	case 32:		//Space
		return KeyList::SPACE;

	case 13:		//Enter
		return KeyList::ENTER;

	case 46:
		return KeyList::DOT;

	case 27:
		return KeyList::ESC;

	case 8:
		return KeyList::BACKSPACE;

	case 48:
		return KeyList::N0;

	case 49:
		return KeyList::N1;

	case 50:
		return KeyList::N2;

	case 51:
		return KeyList::N3;

	case 52:
		return KeyList::N4;

	case 53:
		return KeyList::N5;

	case 54:
		return KeyList::N6;

	case 55:
		return KeyList::N7;

	case 56:
		return KeyList::N8;

	case 57:
		return KeyList::N9;

	default:
		return KeyList::ANOTHER;
	}
}
