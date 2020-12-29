#pragma once
#include <string>
//字母结构体

typedef struct Alpha{

	//表示字符
	char ch;
	//字符出现频率
	unsigned fre;

	//构造函数
	Alpha(char ch = 0, unsigned fre = 0):ch(ch),fre(fre) {}

	//大小比较规则的设立，为了后续排序操作的进行
	bool operator < (const Alpha& other) {
		if (fre != other.fre) return fre < other.fre;
		return ch < other.ch;
	}

}Alpha;