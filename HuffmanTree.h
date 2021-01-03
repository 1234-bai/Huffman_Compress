#pragma once


#include "alphaTable.h"
#include "HNode.h"
#include <string.h>
#include <unordered_map>
#include <queue>

class HuffmanTree
{
private:

	alphaTable alT;

	HNode *HTree;

	std::string *HCode;

	//unsigned hash[270];
	std::unordered_map<char, int>hash;


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

