#pragma once

#include "alpha.h"
#include <string>

class alphaTable
{
public:
	/*字母表类*/
	Alpha* alpTab;	//指向由字母组成的动态数组首地址
	unsigned alpNum;	//字母数量（种类数）
	unsigned SIZE;	//字母表大小

public:

	//字母表构造函数，调用初始化函数初始化
	alphaTable(const char* filename = "\0", bool isComFile = false, int indx = 0);

	//字母表初始化函数
	bool init(const char* filename = "\0", bool isComFile = false, int indx = 0);

	//从原码文件读取文件建立字母表
	bool getAlpTab_File(const char* filename);

	//获得字母种类数量
	unsigned getAlpNum();

	//字母表排序函数
	bool sortAlpTab();

	//向文件中以二进制形式写入头数据（字母种类数量，各字符种类以及出现频率）
	bool writeHdataToFile(const char* filename,int indx = 0);

	//从译码文件或压缩文件中读取头数据获得字母表信息
	bool getAlpTab_Hdata(const char* filename,int indx = 0);

	//字母表信息打印函数，用于控制台字母表类测试
	void print();
};

