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

//Ű �Է��� �޾� � Ű�� �Է��ߴ��� �˷���
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

	default:
		return KeyList::ANOTHER;
	}
}
