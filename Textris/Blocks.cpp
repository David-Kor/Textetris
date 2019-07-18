#include "pch.h"
#include "Blocks.h"

Blocks::Blocks()
{
	//시드 변경
	srand((unsigned int)time(NULL));
	//랜덤 블록 타입
	type = BlockType(rand() % 7);
	sRotateCnt = 0;
	posMainBlk.X = 0;
	posMainBlk.Y = 0;
}

Blocks::~Blocks()
{
}

//MainBlk을 기준으로 SubBlk들의 좌표를 설정
void Blocks::PositionUpdate()
{
	switch (type)
	{
		//ㅣ자형 블록
	case BlockType::I:
		switch (sRotateCnt % 2)	//회전 가능 모양이 2개만 존재
		{
		case 0: {
			//1번 블록
			posSubBlk1.X = posMainBlk.X - 1;
			posSubBlk1.Y = posMainBlk.Y;
			//2번 블록
			posSubBlk2.X = posMainBlk.X + 1;
			posSubBlk2.Y = posMainBlk.Y;
			//3번 블록
			posSubBlk3.X = posMainBlk.X + 2;
			posSubBlk3.Y = posMainBlk.Y;
			break; }

		case 1: {
			//1번 블록
			posSubBlk3.X = posMainBlk.X;
			posSubBlk3.Y = posMainBlk.Y + 1;
			//2번 블록
			posSubBlk2.X = posMainBlk.X;
			posSubBlk2.Y = posMainBlk.Y - 1;
			//3번 블록
			posSubBlk3.X = posMainBlk.X;
			posSubBlk3.Y = posMainBlk.Y - 2;
			break; }
		}
		break;

		//ㅁ자형 블록
	case BlockType::O:
		posSubBlk1.X = posMainBlk.X + 1;
		posSubBlk1.Y = posMainBlk.Y;
		posSubBlk2.X = posMainBlk.X;
		posSubBlk2.Y = posMainBlk.Y + 1;
		posSubBlk2.X = posMainBlk.X + 1;
		posSubBlk2.Y = posMainBlk.Y + 1;
		break;

		//ㅗ자형 블록
	case BlockType::T:
		switch (sRotateCnt)
		{
		case 0: {
			//1번 블록
			posSubBlk1.X = posMainBlk.X + 1;
			posSubBlk1.Y = posMainBlk.Y;
			//2번 블록
			posSubBlk2.X = posMainBlk.X - 1;
			posSubBlk2.Y = posMainBlk.Y;
			//3번 블록
			posSubBlk3.X = posMainBlk.X;
			posSubBlk3.Y = posMainBlk.Y - 1;
			break; }

		case 1: {
			//1번 블록
			posSubBlk1.X = posMainBlk.X;
			posSubBlk1.Y = posMainBlk.Y + 1;
			//2번 블록
			posSubBlk2.X = posMainBlk.X;
			posSubBlk2.Y = posMainBlk.Y - 1;
			//3번 블록
			posSubBlk3.X = posMainBlk.X - 1;
			posSubBlk3.Y = posMainBlk.Y;
			break; }

		case 2: {
			//1번 블록
			posSubBlk1.X = posMainBlk.X - 1;
			posSubBlk1.Y = posMainBlk.Y;
			//2번 블록
			posSubBlk2.X = posMainBlk.X + 1;
			posSubBlk2.Y = posMainBlk.Y;
			//3번 블록
			posSubBlk3.X = posMainBlk.X;
			posSubBlk3.Y = posMainBlk.Y - 1;
			break; }

		case 3: {
			//1번 블록
			posSubBlk1.X = posMainBlk.X;
			posSubBlk1.Y = posMainBlk.Y - 1;
			//2번 블록
			posSubBlk2.X = posMainBlk.X;
			posSubBlk2.Y = posMainBlk.Y + 1;
			//3번 블록
			posSubBlk3.X = posMainBlk.X + 1;
			posSubBlk3.Y = posMainBlk.Y;
			break; }
		}
		break;

		//ㄴ자형 블록
	case BlockType::L:
		switch (sRotateCnt)
		{
		case 0: {
			//1번 블록
			posSubBlk1.X = posMainBlk.X + 1;
			posSubBlk1.Y = posMainBlk.Y;
			//2번 블록
			posSubBlk2.X = posMainBlk.X + 2;
			posSubBlk2.Y = posMainBlk.Y;
			//3번 블록
			posSubBlk3.X = posMainBlk.X;
			posSubBlk3.Y = posMainBlk.Y + 1;
			break; }

		case 1: {
			//1번 블록
			posSubBlk1.X = posMainBlk.X;
			posSubBlk1.Y = posMainBlk.Y - 1;
			//2번 블록
			posSubBlk2.X = posMainBlk.X;
			posSubBlk2.Y = posMainBlk.Y - 2;
			//3번 블록
			posSubBlk3.X = posMainBlk.X + 1;
			posSubBlk3.Y = posMainBlk.Y;
			break; }

		case 2: {
			//1번 블록
			posSubBlk1.X = posMainBlk.X - 1;
			posSubBlk1.Y = posMainBlk.Y;
			//2번 블록
			posSubBlk2.X = posMainBlk.X - 2;
			posSubBlk2.Y = posMainBlk.Y;
			//3번 블록
			posSubBlk3.X = posMainBlk.X;
			posSubBlk3.Y = posMainBlk.Y - 1;
			break; }

		case 3: {
			//1번 블록
			posSubBlk1.X = posMainBlk.X;
			posSubBlk1.Y = posMainBlk.Y + 1;
			//2번 블록
			posSubBlk2.X = posMainBlk.X;
			posSubBlk2.Y = posMainBlk.Y + 2;
			//3번 블록
			posSubBlk3.X = posMainBlk.X - 1;
			posSubBlk3.Y = posMainBlk.Y;
			break; }
		}
		break;

		//ㄱ자형 블록
	case BlockType::J:
		switch (sRotateCnt)
		{
		case 0: {
			//1번 블록
			posSubBlk1.X = posMainBlk.X - 1;
			posSubBlk1.Y = posMainBlk.Y;
			//2번 블록
			posSubBlk2.X = posMainBlk.X - 2;
			posSubBlk2.Y = posMainBlk.Y;
			//3번 블록
			posSubBlk3.X = posMainBlk.X;
			posSubBlk3.Y = posMainBlk.Y + 1;
			break; }

		case 1: {
			//1번 블록
			posSubBlk1.X = posMainBlk.X;
			posSubBlk1.Y = posMainBlk.Y - 1;
			//2번 블록
			posSubBlk2.X = posMainBlk.X;
			posSubBlk2.Y = posMainBlk.Y - 2;
			//3번 블록
			posSubBlk3.X = posMainBlk.X - 1;
			posSubBlk3.Y = posMainBlk.Y;
			break; }

		case 2: {
			//1번 블록
			posSubBlk1.X = posMainBlk.X + 1;
			posSubBlk1.Y = posMainBlk.Y;
			//2번 블록
			posSubBlk2.X = posMainBlk.X + 2;
			posSubBlk2.Y = posMainBlk.Y;
			//3번 블록
			posSubBlk3.X = posMainBlk.X;
			posSubBlk3.Y = posMainBlk.Y - 1;
			break; }

		case 3: {
			//1번 블록
			posSubBlk1.X = posMainBlk.X;
			posSubBlk1.Y = posMainBlk.Y + 1;
			//2번 블록
			posSubBlk2.X = posMainBlk.X;
			posSubBlk2.Y = posMainBlk.Y + 2;
			//3번 블록
			posSubBlk3.X = posMainBlk.X + 1;
			posSubBlk3.Y = posMainBlk.Y;
			break; }
		}
		break;

		//ㄹ자형 블록
	case BlockType::Z:
		switch (sRotateCnt % 2)		//회전 가능 모양이 2개만 존재
		{
		case 0: {
			//1번 블록
			posSubBlk1.X = posMainBlk.X - 1;
			posSubBlk1.Y = posMainBlk.Y;
			//2번 블록
			posSubBlk2.X = posMainBlk.X;
			posSubBlk2.Y = posMainBlk.Y + 1;
			//3번 블록
			posSubBlk3.X = posMainBlk.X + 1;
			posSubBlk3.Y = posMainBlk.Y + 1;
			break; }

		case 1: {
			//1번 블록
			posSubBlk1.X = posMainBlk.X;
			posSubBlk1.Y = posMainBlk.Y + 1;
			//2번 블록
			posSubBlk2.X = posMainBlk.X + 1;
			posSubBlk2.Y = posMainBlk.Y;
			//3번 블록
			posSubBlk3.X = posMainBlk.X + 1;
			posSubBlk3.Y = posMainBlk.Y - 1;
			break; }
		}
		break;

		//5 자형 블록
	case BlockType::S:
		switch (sRotateCnt % 2)		//회전 가능 모양이 2개만 존재
		{
		case 0: {
			//1번 블록
			posSubBlk1.X = posMainBlk.X + 1;
			posSubBlk1.Y = posMainBlk.Y;
			//2번 블록
			posSubBlk2.X = posMainBlk.X;
			posSubBlk2.Y = posMainBlk.Y + 1;
			//3번 블록
			posSubBlk3.X = posMainBlk.X - 1;
			posSubBlk3.Y = posMainBlk.Y + 1;
			break; }

		case 1: {
			//1번 블록
			posSubBlk1.X = posMainBlk.X;
			posSubBlk1.Y = posMainBlk.Y + 1;
			//2번 블록
			posSubBlk2.X = posMainBlk.X - 1;
			posSubBlk2.Y = posMainBlk.Y;
			//3번 블록
			posSubBlk3.X = posMainBlk.X - 1;
			posSubBlk3.Y = posMainBlk.Y - 1;
			break; }
		}
		break;
	}

}

//방향이 음수면 왼쪽, 양수면 오른쪽, 0이면 아래쪽
void Blocks::Move(short sDirection)
{
	//왼쪽 이동
	if (sDirection < 0)
	{
		posMainBlk.X--;
		PositionUpdate();
	}
	//오른쪽 이동
	else if (sDirection > 0)
	{
		posMainBlk.X--;
		PositionUpdate();
	}
	//아래로 이동
	else
	{
		posMainBlk.Y++;
		PositionUpdate();
	}
}

//회전
void Blocks::Roate()
{
	//range : 0~4
	sRotateCnt = (sRotateCnt + 1) % 4;
	PositionUpdate();
}

//4개의 블록중 X좌표 최소값을 반환
short Blocks::GetMinX()
{
	short sMin = posMainBlk.X;

	if (sMin > posSubBlk1.X) { sMin = posSubBlk1.X; }
	if (sMin > posSubBlk2.X) { sMin = posSubBlk2.X; }
	if (sMin > posSubBlk3.X) { sMin = posSubBlk3.X; }

	return sMin;
}

//4개의 블록중 X좌표 최대값을 반환
short Blocks::GetMaxX()
{
	short sMax = posMainBlk.X;

	if (sMax < posSubBlk1.X) { sMax = posSubBlk1.X; }
	if (sMax < posSubBlk2.X) { sMax = posSubBlk2.X; }
	if (sMax < posSubBlk3.X) { sMax = posSubBlk3.X; }

	return sMax;
}

//4개의 블록중 Y좌표 최대값을 반환
short Blocks::GetMaxY()
{
	short sMax = posMainBlk.Y;

	if (sMax < posSubBlk1.Y) { sMax = posSubBlk1.Y; }
	if (sMax < posSubBlk2.Y) { sMax = posSubBlk2.Y; }
	if (sMax < posSubBlk3.Y) { sMax = posSubBlk3.Y; }

	return sMax;
}