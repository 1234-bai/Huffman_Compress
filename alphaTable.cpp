#pragma warning(disable:6385 6386)

#include "alphaTable.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <map>

#define Size 300

alphaTable::alphaTable(const char* filename, bool isComFile, int indx)
{
	this->SIZE = Size + 1;
	this->alpNum = 0;
	this->alpTab = new Alpha[SIZE];
	if (isComFile) {
		getAlpTab_Hdata(filename, indx);
	}
	else
		getAlpTab_File(filename);
}

bool alphaTable::init(const char* filename, bool isComFile, int indx)
{
	this->SIZE = Size + 1;
	this->alpNum = 0;
	this->alpTab = new Alpha[SIZE];
	if (isComFile) {
		if (!getAlpTab_Hdata(filename, indx))
			return false;
	}
	else
		if (!getAlpTab_File(filename))
			return false;
	return true;
}

bool alphaTable::getAlpTab_File(const char* filename)
{
	//Size过小，会触发程序异常,在print(访问函数)出现异常<解决，是读取数据时的问题>
	//考虑各种越界的问题
	//unsigned hash[257];
	//memset(hash, -1, sizeof(hash));
	std::unordered_map<char, int>hash;
	std::ifstream fin(filename, std::ios::in | std::ios::binary);
	if (!fin.is_open()) return false;
	char ch;
	while (!fin.eof()) {
		fin.read(&ch, sizeof(ch));
		if (hash[ch] == 0) {
			alpNum++;
			//空间不足，开辟另外的空间
			if (alpNum >= SIZE) {
				Alpha* temp = new Alpha[SIZE + Size];
				for (unsigned i = 1; i < SIZE; ++i) {
					temp[i].ch = alpTab[i].ch;
					temp[i].fre = alpTab[i].fre;
				}
				Alpha* m = alpTab; alpTab = temp; delete m;
				SIZE += Size;
			}
			if (alpNum < SIZE) {
				alpTab[alpNum].fre = 1;
				alpTab[alpNum].ch = (ch);
			}
			hash[ch] = alpNum;
			//alpNum++;
		}
		else {
			alpTab[hash[ch]].fre++;
		}
	}
	return true;
}

unsigned alphaTable::getAlpNum()
{
	return this->alpNum;
}

bool alphaTable::sortAlpTab()
{
	std::sort(this->alpTab + 1, this->alpTab + this->alpNum + 1);
	return true;
}

bool alphaTable::writeHdataToFile(const char* filename,int indx)
{
	std::ofstream fout(filename, std::ios::out | std::ios::binary);
	if (!fout.is_open()) return false;
	fout.seekp(indx);
	fout.write((char*)&alpNum,sizeof(alpNum));
	for (unsigned i = 1; i <= alpNum; ++i) {
		fout.write((char*)&alpTab[i].ch, sizeof(char));
		fout.write((char*)&alpTab[i].fre, sizeof(unsigned));
	}
	fout.close();
	return true;
}

bool alphaTable::getAlpTab_Hdata(const char* filename, int indx)
{
	std::ifstream fin(filename, std::ios::in | std::ios::binary);
	if(!fin.is_open()) return false;
	fin.seekg(indx);
	fin.read((char*)&alpNum, sizeof(alpNum));
	if (alpNum > SIZE-1) {
		alpTab = new Alpha[alpNum + Size];
	}
	for (unsigned i = 1; i <= alpNum; ++i) {
		fin.read((char*)&alpTab[i].ch, sizeof(char));
		fin.read((char*)&alpTab[i].fre, sizeof(unsigned));
	}
	fin.close();
	return true;
}

void alphaTable::print()
{
	for (unsigned i = 1; i <= alpNum; ++i) {
		printf("%c", alpTab[i].ch);
		std::cout << "："<<alpTab[i].fre << ' ';
	}
	std::cout << std::endl;
}
