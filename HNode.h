#pragma once

#include <iostream>

/*哈夫曼树结点类*/
class HNode
{

public:

	unsigned weight;	//权重

	unsigned lch, rch;	//左右孩子结点

	unsigned par;	//双亲结点

public:

	//构造函数，利用初始化函数构造
	HNode(unsigned wei = 0, unsigned l = 0, unsigned r = 0, unsigned par = 0);

	//初始化函数
	bool initHNode(unsigned wei = 0, unsigned l = 0, unsigned r = 0, unsigned par = 0);

	//运算符重载
	bool operator< (const HNode& other);

	//输出流重载，用于控制台后序测试
	friend std::ostream& operator<< (std::ostream& out, const HNode &node);
};

