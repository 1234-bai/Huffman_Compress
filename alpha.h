#pragma once
#include <string>

typedef struct Alpha{

	char ch;

	unsigned fre;


	Alpha(char ch = 0, unsigned fre = 0):ch(ch),fre(fre) {}


	bool operator < (const Alpha& other) {
		if (fre != other.fre) return fre < other.fre;
		return ch < other.ch;
	}

}Alpha;
