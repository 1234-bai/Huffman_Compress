#pragma once
#include <string>

/*字母结构体组成*/
typedef struct Alpha{

	char ch;	//字符

	unsigned fre;	//当前字符出现频率

	Alpha(char ch = 0, unsigned fre = 0):ch(ch),fre(fre) {}

	bool operator < (const Alpha& other) {
		if (fre != other.fre) return fre < other.fre;
		return ch < other.ch;
	}

}Alpha;
