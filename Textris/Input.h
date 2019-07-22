#ifndef _INPUT_CLASS
#define _INPUT_CLASS

class Input
{
public:
	enum KeyList { ESC, ENTER, SPACE, UP, DOWN, LEFT, RIGHT, ANOTHER };
	Input();
	~Input();

	bool IsAnyKeyDown();
	Input::KeyList GetInputKey();
};

#endif