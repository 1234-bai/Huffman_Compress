#pragma once

//哈夫曼树类

#include "alphaTable.h"
#include "HNode.h"
#include <string.h>
#include <unordered_map>
#include <queue>

class HuffmanTree
{
private:
	//字母表
	alphaTable alT;
	//哈夫曼树表
	HNode *HTree;
	//哈夫曼编码表
	std::string *HCode;
	//哈希数组，建立字符同字母表，树表，编码表下标（三个表同一下标，表示同一字符）的映射
	//unsigned hash[270];
	std::unordered_map<char, int>hash;

	//指向树表的下标，表示索引的过程。根据01字符找对应的字符是用的到
	int nowPtr;

public:

	HuffmanTree(alphaTable& alT);
	HuffmanTree();

	bool initHTree(alphaTable& alT);

	void Select(std::queue<std::pair<HNode, int> >& fir, std::queue<std::pair<HNode, int> >& sec,
		unsigned& min_inx_1, unsigned& min_inx_2, int num);
	bool buildTree();

	bool buildCode();

	//unsigned char Str01_2_Ch(std::string str01);

	HNode* getTree();

	std::string Ch_2_01Str(char ch);

	alphaTable& getAlphaTable();

	int getChInx(unsigned num);

	void print();
};

