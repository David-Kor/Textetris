#ifndef _BLOCKS_CLASS
#define _BLOCKS_CLASS

class Blocks
{
private:
	enum BlockType { I, O, T, L, J, Z, S };
	struct Position
	{
		int X;
		int Y;
	};

	BlockType nBlockType;
	int mv_nRotateCnt;

public:
	Position posMainBlk;
	Position posSubBlk1;
	Position posSubBlk2;
	Position posSubBlk3;

	Blocks();
	~Blocks();

	void SetXPositionToCenter(const int& nMaxHorSize);
	void PositionUpdate();
	void Move(const int& nDirType);
	void Rotate(const int& nDirection);
	int GetMinX();
	int GetMaxX();
	int GetMaxY();
};

#endif