#ifndef _BLOCKS_CLASS
#define _BLOCKS_CLASS

class Blocks
{
private:
	enum BlockType { I, O, T, L, J, Z, S };
	struct Position
	{
		short X;
		short Y;
	};

	short sRotateCnt;

public:
	BlockType type;
	Position posMainBlk;
	Position posSubBlk1;
	Position posSubBlk2;
	Position posSubBlk3;

	Blocks();
	~Blocks();

	void PositionUpdate();
	void Move(short sDirection);
	void Roate();
	short GetMinX();
	short GetMaxX();
	short GetMaxY();
};

#endif