#pragma once

#include "alphaTable.h"
#include "HNode.h"
#include <string.h>
#include <unordered_map>
#include <queue>

/*哈夫曼树类*/
class HuffmanTree
{
private:
	/*哈夫曼树类*/
	alphaTable alT;		//建树的字母表

	HNode *HTree;	//有哈夫曼结点类组成的静态链表，存储建好的哈夫曼二叉树

	std::string *HCode;		//哈夫曼编码表，存储每个字符对应的01编码

	//unsigned hash[270];
	std::unordered_map<char, int>hash;		//利用stl建立的字符同在树表索引的映射关系

	int nowPtr;		//当前指针，解码过程中用到，指向当前正在查找的结点的索引

public:

	//构造函数
	HuffmanTree(alphaTable& alT);
	HuffmanTree();

	//初始化函数
	bool initHTree(alphaTable& alT);

	//挑选结点函数，以及建树函数
	void Select(std::queue<std::pair<HNode, int> >& fir, std::queue<std::pair<HNode, int> >& sec,
		unsigned& min_inx_1, unsigned& min_inx_2, int num);
	bool buildTree();

	//哈夫曼编码表建立函数
	bool buildCode();

	//获得建立的树表，用于后序控制台测试
	HNode* getTree();

	//获得相应字符对应的01编码
	std::string Ch_2_01Str(char ch);

	//获得建树用字母表，用于后序测试，以及文件头数据的写入
	alphaTable& getAlphaTable();

	//根据输入的01数字，进行当前指向结点（nowPtr）移动。
	//获得当前指向结点的索引，若为叶子结点则返回索引，否则返回-1
	int getChInx(unsigned num);

	//树打印函数，用于后序控制台测试
	void print();
};

