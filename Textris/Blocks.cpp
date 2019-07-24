#include "pch.h"
#include "Blocks.h"

//������
Blocks::Blocks()
{
	//���� ��� Ÿ��
	nBlockType = BlockType(rand() % 7);
	mv_nRotateCnt = 0;
	posMainBlk.X = 0;
	posMainBlk.Y = 0;
}

//�Ҹ���
Blocks::~Blocks()
{
}

//��� ��ü�� X�� ����� ������ ��ġ
void Blocks::SetXPositionToCenter(const int& nMaxHorSize)
{
	switch (nBlockType)
	{
	case BlockType::I:
	case BlockType::O:
	case BlockType::S:
		if (nMaxHorSize % 2 == 0) {	//size�� ¦��
			posMainBlk.X = nMaxHorSize / 2;
		}
		else {		//size�� Ȧ��
			posMainBlk.X = (nMaxHorSize + 1) / 2;
		}
		break;

	case BlockType::T:
		if (nMaxHorSize % 2 == 0) {	//size�� ¦��
			posMainBlk.X = nMaxHorSize / 2;
		}
		else {		//size�� Ȧ��
			posMainBlk.X = (nMaxHorSize - 1) / 2;
		}
		break;

	case BlockType::L:
		if (nMaxHorSize % 2 == 0) {	//size�� ¦��
			posMainBlk.X = (nMaxHorSize / 2) + 1;
		}
		else {		//size�� Ȧ��
			posMainBlk.X = (nMaxHorSize + 1) / 2;
		}
		break;

	case BlockType::J:
		if (nMaxHorSize % 2 == 0) {	//size�� ¦��
			posMainBlk.X = (nMaxHorSize / 2) - 1;
		}
		else {		//size�� Ȧ��
			posMainBlk.X = ((nMaxHorSize - 1) / 2) - 1;
		}
		break;
	case BlockType::Z:
		if (nMaxHorSize % 2 == 0) {	//size�� ¦��
			posMainBlk.X = (nMaxHorSize / 2) - 1;
		}
		else {		//size�� Ȧ��
			posMainBlk.X = (nMaxHorSize - 1) / 2;
		}
		break;
	}
}

//MainBlk�� �������� SubBlk���� ��ǥ�� ����
void Blocks::PositionUpdate()
{
	switch (nBlockType)
	{
		//������ ���
	case BlockType::I:
		switch (mv_nRotateCnt % 2)	//ȸ�� ���� ����� 2���� ����
		{
		case 0: {
			//1�� ���
			posSubBlk1.X = posMainBlk.X - 2;
			posSubBlk1.Y = posMainBlk.Y;
			//2�� ���
			posSubBlk2.X = posMainBlk.X - 1;
			posSubBlk2.Y = posMainBlk.Y;
			//3�� ���
			posSubBlk3.X = posMainBlk.X + 1;
			posSubBlk3.Y = posMainBlk.Y;
			break; }

		case 1: {
			//1�� ���
			posSubBlk1.X = posMainBlk.X;
			posSubBlk1.Y = posMainBlk.Y + 1;
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
		//1�� ���
		posSubBlk1.X = posMainBlk.X - 1;
		posSubBlk1.Y = posMainBlk.Y - 1;
		//2�� ���
		posSubBlk2.X = posMainBlk.X;
		posSubBlk2.Y = posMainBlk.Y - 1;
		//3�� ���
		posSubBlk3.X = posMainBlk.X - 1;
		posSubBlk3.Y = posMainBlk.Y;
		break;

		//������ ���
	case BlockType::T:
		switch (mv_nRotateCnt)
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
			posSubBlk3.Y = posMainBlk.Y + 1;
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
		switch (mv_nRotateCnt)
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
			posSubBlk3.Y = posMainBlk.Y - 1;
			break; }

		case 1: {
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

		case 2: {
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

		case 3: {
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
		}
		break;

		//������ ���
	case BlockType::J:
		switch (mv_nRotateCnt)
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
			posSubBlk3.Y = posMainBlk.Y - 1;
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
			posSubBlk1.X = posMainBlk.X - 1;
			posSubBlk1.Y = posMainBlk.Y;
			//2�� ���
			posSubBlk2.X = posMainBlk.X - 2;
			posSubBlk2.Y = posMainBlk.Y;
			//3�� ���
			posSubBlk3.X = posMainBlk.X;
			posSubBlk3.Y = posMainBlk.Y + 1;
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
		switch (mv_nRotateCnt % 2)		//ȸ�� ���� ����� 2���� ����
		{
		case 0: {
			//1�� ���
			posSubBlk1.X = posMainBlk.X;
			posSubBlk1.Y = posMainBlk.Y - 1;
			//2�� ���
			posSubBlk2.X = posMainBlk.X - 1;
			posSubBlk2.Y = posMainBlk.Y - 1;
			//3�� ���
			posSubBlk3.X = posMainBlk.X + 1;
			posSubBlk3.Y = posMainBlk.Y;
			break; }

		case 1: {
			//1�� ���
			posSubBlk1.X = posMainBlk.X + 1;
			posSubBlk1.Y = posMainBlk.Y;
			//2�� ���
			posSubBlk2.X = posMainBlk.X + 1;
			posSubBlk2.Y = posMainBlk.Y - 1;
			//3�� ���
			posSubBlk3.X = posMainBlk.X;
			posSubBlk3.Y = posMainBlk.Y + 1;
			break; }
		}
		break;

		//5 ���� ���
	case BlockType::S:
		switch (mv_nRotateCnt % 2)		//ȸ�� ���� ����� 2���� ����
		{
		case 0: {
			//1�� ���
			posSubBlk1.X = posMainBlk.X;
			posSubBlk1.Y = posMainBlk.Y - 1;
			//2�� ���
			posSubBlk2.X = posMainBlk.X + 1;
			posSubBlk2.Y = posMainBlk.Y - 1;
			//3�� ���
			posSubBlk3.X = posMainBlk.X - 1;
			posSubBlk3.Y = posMainBlk.Y;
			break; }

		case 1: {
			//1�� ���
			posSubBlk1.X = posMainBlk.X - 1;
			posSubBlk1.Y = posMainBlk.Y;
			//2�� ���
			posSubBlk2.X = posMainBlk.X - 1;
			posSubBlk2.Y = posMainBlk.Y - 1;
			//3�� ���
			posSubBlk3.X = posMainBlk.X;
			posSubBlk3.Y = posMainBlk.Y + 1;
			break; }
		}
		break;
	}

}

//�̵� (������ ������ �Ʒ�, 0�̸� ��, 1�̸� ����, 2�̻��̸� ������)
void Blocks::Move(const int& nDirection)
{
	//�Ʒ��� �̵�
	if (nDirection < 0)
	{
		posMainBlk.Y++;
		PositionUpdate();
	}
	//���� �̵�
	else if (nDirection == 0)
	{
		posMainBlk.Y--;
		PositionUpdate();
	}
	//�������� �̵�
	else if(nDirection == 1)
	{
		posMainBlk.X--;
		PositionUpdate();
	}
	//���������� �̵�
	else
	{
		posMainBlk.X++;
		PositionUpdate();
	}
}

//ȸ�� (������ �ð����, �ƴϸ� �ð����)
void Blocks::Rotate(const int& nDirType)
{
	if (nDirType < 0)
	{
		//range : 0~4
		mv_nRotateCnt--;
		if (mv_nRotateCnt < 0) { mv_nRotateCnt = 3; }
	}
	else
	{
		//range : 0~4
		mv_nRotateCnt = (mv_nRotateCnt + 1) % 4;
	}
	PositionUpdate();
}

//4���� ����� X��ǥ �ּҰ��� ��ȯ
int Blocks::GetMinX()
{
	short sMin = posMainBlk.X;

	if (sMin > posSubBlk1.X) { sMin = posSubBlk1.X; }
	if (sMin > posSubBlk2.X) { sMin = posSubBlk2.X; }
	if (sMin > posSubBlk3.X) { sMin = posSubBlk3.X; }

	return sMin;
}

//4���� ����� X��ǥ �ִ밪�� ��ȯ
int Blocks::GetMaxX()
{
	short sMax = posMainBlk.X;

	if (sMax < posSubBlk1.X) { sMax = posSubBlk1.X; }
	if (sMax < posSubBlk2.X) { sMax = posSubBlk2.X; }
	if (sMax < posSubBlk3.X) { sMax = posSubBlk3.X; }

	return sMax;
}

//4���� ����� Y��ǥ �ִ밪�� ��ȯ
int Blocks::GetMaxY()
{
	short sMax = posMainBlk.Y;

	if (sMax < posSubBlk1.Y) { sMax = posSubBlk1.Y; }
	if (sMax < posSubBlk2.Y) { sMax = posSubBlk2.Y; }
	if (sMax < posSubBlk3.Y) { sMax = posSubBlk3.Y; }

	return sMax;
}