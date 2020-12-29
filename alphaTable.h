#pragma once

//��ĸ����
//δ������⣺�����ַ������⡣��ĸ���С�仯�����⣨���ƹ��캯������

#include "alpha.h"
#include <string>

class alphaTable
{
public:
	//��ĸ��
	Alpha* alpTab;
	//��ĸ���е���ĸ����
	unsigned alpNum;
	unsigned SIZE;
public:

	//���캯���������ж������
	alphaTable(const char* filename = "\0", bool isComFile = false, int indx = 0);

	bool init(const char* filename = "\0", bool isComFile = false, int indx = 0);

	//���ļ������ݻ�ȡ��ĸ��
	bool getAlpTab_File(const char* filename);

	//�����ĸ���е���ĸ����
	unsigned getAlpNum();

	//��ĸ����������Ϊ�˽��ͺ����������е�ʱ�临�Ӷ�
	bool sortAlpTab();

	//����ĸ����Ϣ��ͷ���ݣ�д���ļ���
	bool writeHdataToFile(const char* filename,int indx = 0);

	//���ļ��л�ȡͷ���ݣ���������ĸ��
	bool getAlpTab_Hdata(const char* filename,int indx = 0);

	void print();
};

