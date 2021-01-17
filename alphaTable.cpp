#pragma warning(disable:6385 6386 26451)

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

//读取原码文件获得字母表
bool alphaTable::getAlpTab_File(const char* filename)
{
	//利用STL建立字符同字符出现频率的映射
	std::unordered_map<char, int>hash;

	//打开原码文件
	std::ifstream fin(filename, std::ios::in | std::ios::binary);
	if (!fin.is_open()) return false;

	//读取字符，建立字母表
	char ch;
	while (!fin.eof()) {
		fin.read(&ch, sizeof(ch));
		if (hash[ch] == 0) {
			alpNum++;
			//若字母种类超出字母表大小，则扩展
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

//读取头数据获得字母表
bool alphaTable::getAlpTab_Hdata(const char* filename, int indx)
{
	//打开目标文件
	std::ifstream fin(filename, std::ios::in | std::ios::binary);
	if(!fin.is_open()) return false;

	//定位到读取头数据位置
	fin.seekg(indx);
	fin.read((char*)&alpNum, sizeof(alpNum));
	//扩展大小
	if (alpNum > SIZE-1) {
		alpTab = new Alpha[alpNum + Size];
	}
	//读取字符种类和对应频率
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
		std::cout << ":"<<alpTab[i].fre << ' ';
	}
	std::cout << std::endl;
}
