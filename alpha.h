#pragma once
#include <string>
//��ĸ�ṹ��

typedef struct Alpha{

	//��ʾ�ַ�
	char ch;
	//�ַ�����Ƶ��
	unsigned fre;

	//���캯��
	Alpha(char ch = 0, unsigned fre = 0):ch(ch),fre(fre) {}

	//��С�ȽϹ����������Ϊ�˺�����������Ľ���
	bool operator < (const Alpha& other) {
		if (fre != other.fre) return fre < other.fre;
		return ch < other.ch;
	}

}Alpha;