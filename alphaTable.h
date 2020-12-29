#pragma once

//字母表类
//未解决问题：中文字符的问题。字母表大小变化的问题（复制构造函数）。

#include "alpha.h"
#include <string>

class alphaTable
{
public:
	//字母表
	Alpha* alpTab;
	//字母表中的字母数量
	unsigned alpNum;
	unsigned SIZE;
public:

	//构造函数，可能有多个重载
	alphaTable(const char* filename = "\0", bool isComFile = false, int indx = 0);

	bool init(const char* filename = "\0", bool isComFile = false, int indx = 0);

	//从文件的内容获取字母表
	bool getAlpTab_File(const char* filename);

	//获得字母表中的字母数量
	unsigned getAlpNum();

	//字母表排序函数，为了降低后序建树过程中的时间复杂度
	bool sortAlpTab();

	//将字母表信息（头数据）写到文件里
	bool writeHdataToFile(const char* filename,int indx = 0);

	//从文件中获取头数据，并建立字母表
	bool getAlpTab_Hdata(const char* filename,int indx = 0);

	void print();
};

