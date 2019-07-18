#include "pch.h"
#include "Blocks.h"

Blocks::Blocks()
{
	//�õ� ����
	srand((unsigned int)time(NULL));
	//���� ��� Ÿ��
	type = BlockType(rand() % 7);
	sRotateCnt = 0;
	posMainBlk.X = 0;
	posMainBlk.Y = 0;
}

Blocks::~Blocks()
{
}

//MainBlk�� �������� SubBlk���� ��ǥ�� ����
void Blocks::PositionUpdate()
{
	switch (type)
	{
		//������ ���
	case BlockType::I:
		switch (sRotateCnt % 2)	//ȸ�� ���� ����� 2���� ����
		{
		case 0: {
			//1�� ���
			posSubBlk1.X = posMainBlk.X - 1;
			posSubBlk1.Y = posMainBlk.Y;
			//2�� ���
			posSubBlk2.X = posMainBlk.X + 1;
			posSubBlk2.Y = posMainBlk.Y;
			//3�� ���
			posSubBlk3.X = posMainBlk.X + 2;
			posSubBlk3.Y = posMainBlk.Y;
			break; }

		case 1: {
			//1�� ���
			posSubBlk3.X = posMainBlk.X;
			posSubBlk3.Y = posMainBlk.Y + 1;
			//2�� ���
			posSubBlk2.X = posMainBlk.X;
			posSubBlk2.Y = posMainBlk.Y - 1;
			//3�� ���
			posSubBlk3.X = posMainBlk.X;
			posSubBlk3.Y = posMainBlk.Y - 2;
			break; }
		}
		break;

		//������ ���
	case BlockType::O:
		posSubBlk1.X = posMainBlk.X + 1;
		posSubBlk1.Y = posMainBlk.Y;
		posSubBlk2.X = posMainBlk.X;
		posSubBlk2.Y = posMainBlk.Y + 1;
		posSubBlk2.X = posMainBlk.X + 1;
		posSubBlk2.Y = posMainBlk.Y + 1;
		break;

		//������ ���
	case BlockType::T:
		switch (sRotateCnt)
		{
		case 0: {
			//1�� ���
			posSubBlk1.X = posMainBlk.X + 1;
			posSubBlk1.Y = posMainBlk.Y;
			//2�� ���
			posSubBlk2.X = posMainBlk.X - 1;
			posSubBlk2.Y = posMainBlk.Y;
			//3�� ���
			posSubBlk3.X = posMainBlk.X;
			posSubBlk3.Y = posMainBlk.Y - 1;
			break; }

		case 1: {
			//1�� ���
			posSubBlk1.X = posMainBlk.X;
			posSubBlk1.Y = posMainBlk.Y + 1;
			//2�� ���
			posSubBlk2.X = posMainBlk.X;
			posSubBlk2.Y = posMainBlk.Y - 1;
			//3�� ���
			posSubBlk3.X = posMainBlk.X - 1;
			posSubBlk3.Y = posMainBlk.Y;
			break; }

		case 2: {
			//1�� ���
			posSubBlk1.X = posMainBlk.X - 1;
			posSubBlk1.Y = posMainBlk.Y;
			//2�� ���
			posSubBlk2.X = posMainBlk.X + 1;
			posSubBlk2.Y = posMainBlk.Y;
			//3�� ���
			posSubBlk3.X = posMainBlk.X;
			posSubBlk3.Y = posMainBlk.Y - 1;
			break; }

		case 3: {
			//1�� ���
			posSubBlk1.X = posMainBlk.X;
			posSubBlk1.Y = posMainBlk.Y - 1;
			//2�� ���
			posSubBlk2.X = posMainBlk.X;
			posSubBlk2.Y = posMainBlk.Y + 1;
			//3�� ���
			posSubBlk3.X = posMainBlk.X + 1;
			posSubBlk3.Y = posMainBlk.Y;
			break; }
		}
		break;

		//������ ���
	case BlockType::L:
		switch (sRotateCnt)
		{
		case 0: {
			//1�� ���
			posSubBlk1.X = posMainBlk.X + 1;
			posSubBlk1.Y = posMainBlk.Y;
			//2�� ���
			posSubBlk2.X = posMainBlk.X + 2;
			posSubBlk2.Y = posMainBlk.Y;
			//3�� ���
			posSubBlk3.X = posMainBlk.X;
			posSubBlk3.Y = posMainBlk.Y + 1;
			break; }

		case 1: {
			//1�� ���
			posSubBlk1.X = posMainBlk.X;
			posSubBlk1.Y = posMainBlk.Y - 1;
			//2�� ���
			posSubBlk2.X = posMainBlk.X;
			posSubBlk2.Y = posMainBlk.Y - 2;
			//3�� ���
			posSubBlk3.X = posMainBlk.X + 1;
			posSubBlk3.Y = posMainBlk.Y;
			break; }

		case 2: {
			//1�� ���
			posSubBlk1.X = posMainBlk.X - 1;
			posSubBlk1.Y = posMainBlk.Y;
			//2�� ���
			posSubBlk2.X = posMainBlk.X - 2;
			posSubBlk2.Y = posMainBlk.Y;
			//3�� ���
			posSubBlk3.X = posMainBlk.X;
			posSubBlk3.Y = posMainBlk.Y - 1;
			break; }

		case 3: {
			//1�� ���
			posSubBlk1.X = posMainBlk.X;
			posSubBlk1.Y = posMainBlk.Y + 1;
			//2�� ���
			posSubBlk2.X = posMainBlk.X;
			posSubBlk2.Y = posMainBlk.Y + 2;
			//3�� ���
			posSubBlk3.X = posMainBlk.X - 1;
			posSubBlk3.Y = posMainBlk.Y;
			break; }
		}
		break;

		//������ ���
	case BlockType::J:
		switch (sRotateCnt)
		{
		case 0: {
			//1�� ���
			posSubBlk1.X = posMainBlk.X - 1;
			posSubBlk1.Y = posMainBlk.Y;
			//2�� ���
			posSubBlk2.X = posMainBlk.X - 2;
			posSubBlk2.Y = posMainBlk.Y;
			//3�� ���
			posSubBlk3.X = posMainBlk.X;
			posSubBlk3.Y = posMainBlk.Y + 1;
			break; }

		case 1: {
			//1�� ���
			posSubBlk1.X = posMainBlk.X;
			posSubBlk1.Y = posMainBlk.Y - 1;
			//2�� ���
			posSubBlk2.X = posMainBlk.X;
			posSubBlk2.Y = posMainBlk.Y - 2;
			//3�� ���
			posSubBlk3.X = posMainBlk.X - 1;
			posSubBlk3.Y = posMainBlk.Y;
			break; }

		case 2: {
			//1�� ���
			posSubBlk1.X = posMainBlk.X + 1;
			posSubBlk1.Y = posMainBlk.Y;
			//2�� ���
			posSubBlk2.X = posMainBlk.X + 2;
			posSubBlk2.Y = posMainBlk.Y;
			//3�� ���
			posSubBlk3.X = posMainBlk.X;
			posSubBlk3.Y = posMainBlk.Y - 1;
			break; }

		case 3: {
			//1�� ���
			posSubBlk1.X = posMainBlk.X;
			posSubBlk1.Y = posMainBlk.Y + 1;
			//2�� ���
			posSubBlk2.X = posMainBlk.X;
			posSubBlk2.Y = posMainBlk.Y + 2;
			//3�� ���
			posSubBlk3.X = posMainBlk.X + 1;
			posSubBlk3.Y = posMainBlk.Y;
			break; }
		}
		break;

		//������ ���
	case BlockType::Z:
		switch (sRotateCnt % 2)		//ȸ�� ���� ����� 2���� ����
		{
		case 0: {
			//1�� ���
			posSubBlk1.X = posMainBlk.X - 1;
			posSubBlk1.Y = posMainBlk.Y;
			//2�� ���
			posSubBlk2.X = posMainBlk.X;
			posSubBlk2.Y = posMainBlk.Y + 1;
			//3�� ���
			posSubBlk3.X = posMainBlk.X + 1;
			posSubBlk3.Y = posMainBlk.Y + 1;
			break; }

		case 1: {
			//1�� ���
			posSubBlk1.X = posMainBlk.X;
			posSubBlk1.Y = posMainBlk.Y + 1;
			//2�� ���
			posSubBlk2.X = posMainBlk.X + 1;
			posSubBlk2.Y = posMainBlk.Y;
			//3�� ���
			posSubBlk3.X = posMainBlk.X + 1;
			posSubBlk3.Y = posMainBlk.Y - 1;
			break; }
		}
		break;

		//5 ���� ���
	case BlockType::S:
		switch (sRotateCnt % 2)		//ȸ�� ���� ����� 2���� ����
		{
		case 0: {
			//1�� ���
			posSubBlk1.X = posMainBlk.X + 1;
			posSubBlk1.Y = posMainBlk.Y;
			//2�� ���
			posSubBlk2.X = posMainBlk.X;
			posSubBlk2.Y = posMainBlk.Y + 1;
			//3�� ���
			posSubBlk3.X = posMainBlk.X - 1;
			posSubBlk3.Y = posMainBlk.Y + 1;
			break; }

		case 1: {
			//1�� ���
			posSubBlk1.X = posMainBlk.X;
			posSubBlk1.Y = posMainBlk.Y + 1;
			//2�� ���
			posSubBlk2.X = posMainBlk.X - 1;
			posSubBlk2.Y = posMainBlk.Y;
			//3�� ���
			posSubBlk3.X = posMainBlk.X - 1;
			posSubBlk3.Y = posMainBlk.Y - 1;
			break; }
		}
		break;
	}

}

//������ ������ ����, ����� ������, 0�̸� �Ʒ���
void Blocks::Move(short sDirection)
{
	//���� �̵�
	if (sDirection < 0)
	{
		posMainBlk.X--;
		PositionUpdate();
	}
	//������ �̵�
	else if (sDirection > 0)
	{
		posMainBlk.X--;
		PositionUpdate();
	}
	//�Ʒ��� �̵�
	else
	{
		posMainBlk.Y++;
		PositionUpdate();
	}
}

//ȸ��
void Blocks::Roate()
{
	//range : 0~4
	sRotateCnt = (sRotateCnt + 1) % 4;
	PositionUpdate();
}

//4���� ����� X��ǥ �ּҰ��� ��ȯ
short Blocks::GetMinX()
{
	short sMin = posMainBlk.X;

	if (sMin > posSubBlk1.X) { sMin = posSubBlk1.X; }
	if (sMin > posSubBlk2.X) { sMin = posSubBlk2.X; }
	if (sMin > posSubBlk3.X) { sMin = posSubBlk3.X; }

	return sMin;
}

//4���� ����� X��ǥ �ִ밪�� ��ȯ
short Blocks::GetMaxX()
{
	short sMax = posMainBlk.X;

	if (sMax < posSubBlk1.X) { sMax = posSubBlk1.X; }
	if (sMax < posSubBlk2.X) { sMax = posSubBlk2.X; }
	if (sMax < posSubBlk3.X) { sMax = posSubBlk3.X; }

	return sMax;
}

//4���� ����� Y��ǥ �ִ밪�� ��ȯ
short Blocks::GetMaxY()
{
	short sMax = posMainBlk.Y;

	if (sMax < posSubBlk1.Y) { sMax = posSubBlk1.Y; }
	if (sMax < posSubBlk2.Y) { sMax = posSubBlk2.Y; }
	if (sMax < posSubBlk3.Y) { sMax = posSubBlk3.Y; }

	return sMax;
}