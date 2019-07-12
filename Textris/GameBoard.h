#ifndef _GAMEBOARD_CLASS
#define _GAMEBOARD_CLASS

class GameBoard
{
private:
	enum BoardType { BLOCK = L'■', EMPTY = L'　', WALL = L'▣' };
	enum BlockType {I, O, T, L, J, Z, S };

	struct Position
	{
		unsigned char X;
		unsigned char Y;
	};

	struct Blocks
	{
		BlockType type;
		unsigned char rotateCnt;
		Position posMainBlk;
		Position posSubBlk1;
		Position posSubBlk2;
		Position posSubBlk3;
	};

	int mv_nScore;

	unsigned char mv_ucBoardTable[10][20];	//보드판 가로길이 x 보드판 세로길이
	std::wstring mv_wstrBoard[20];
	std::wstring mv_wstrUI[23];

	Blocks* curBlk;
	Blocks* nxtBlk;

	void CreateNextBlock();
	bool UpdateBlock(Blocks* blk);
	void UpdateBoardTable(Blocks* blk, bool isDropped);

public:
	//보드판 세로길이
	const short MAX_VER_SIZE = 20;
	//보드판 가로길이
	const short MAX_HOR_SIZE = 10;
	//전체 UI 라인 수
	const short MAX_UI_LINE = 23;
	//보이지 않는 공간 수 -> 이 수보다 작은 Y값은 보드 화면상에 나타나지 않음
	const short MARGIN_BOARD = 2;

	GameBoard();
	~GameBoard();

	std::wstring* GetBoard();
	std::wstring* GetUI();
	void RotateBlock();
	void MoveBlock(int nDirection);
	void DropBlock();
};

#endif