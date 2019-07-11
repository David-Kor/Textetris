#ifndef _GAMEBOARD_CLASS
#define _GAMEBOARD_CLASS

class GameBoard
{
private:
	enum BoardType { BLOCK = L'��', EMPTY = L'��', WALL = L'��' };
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

	unsigned char mv_ucBoardTable[10][22];	//������ ���α��� x ������ ���α���+����
	std::wstring mv_wstrBoard[20];
	std::wstring mv_wstrUI[23];

	Blocks* curBlk;
	Blocks* nxtBlk;

	void CreateNextBlock();
	bool UpdateBlock(Blocks* blk);

public:
	//������ ���α���
	const short MAX_VER_SIZE = 20;
	//������ ���α���
	const short MAX_HOR_SIZE = 10;
	//��ü UI ���� ��
	const short MAX_UI_LINE = 23;
	//������ �ʴ� ����
	const short MARGIN_BOARD = 2;

	GameBoard();
	~GameBoard();

	std::wstring* GetBoard();
	std::wstring* GetUI();
	void RotateBlock();
	void MoveBlock(unsigned char ucDirection);
	void DropBlock();
};

#endif