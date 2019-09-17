#ifndef _INPUT_CLASS
#define _INPUT_CLASS

class Input
{
public:
	enum KeyList { ESC, BACKSPACE, ENTER, SPACE, UP, DOWN, LEFT, RIGHT, N0, N1, N2, N3, N4, N5, N6, N7, N8, N9, DOT, ANOTHER };
	Input();
	~Input();

	bool IsAnyKeyDown();
	Input::KeyList GetInputKey();
};

#endif