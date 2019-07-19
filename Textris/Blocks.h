#ifndef _BLOCKS_CLASS
#define _BLOCKS_CLASS

class Blocks
{
private:
	struct Position
	{
		short X;
		short Y;
	};

	short sRotateCnt;

public:
	enum BlockType { I, O, T, L, J, Z, S };
	BlockType type;
	Position posMainBlk;
	Position posSubBlk1;
	Position posSubBlk2;
	Position posSubBlk3;

	Blocks();
	~Blocks();

	void SetXPositionToCenter(const short sMaxHorSize);
	void PositionUpdate();
	void Move(const short& sDirType);
	void Rotate(const short& sDirection);
	short GetMinX();
	short GetMaxX();
	short GetMaxY();
};

#endif