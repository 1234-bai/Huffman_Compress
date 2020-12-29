#pragma once

//哈夫曼结点类

class HNode
{
//设为公开权限，可能是因为过程中可能对全部内容进行修改和获得。暂时先这样。
public:
	//结点的权重
	unsigned weight;
	//左右孩子结点
	unsigned lch, rch;
	//双亲结点
	unsigned par;

public:
	//构造函数
	HNode(unsigned wei = 0, unsigned l = 0, unsigned r = 0, unsigned par = 0);

	//初始化函数
	bool initHNode(unsigned wei = 0, unsigned l = 0, unsigned r = 0, unsigned par = 0);

	//结点合并函数
	HNode mergeHNode(const HNode& other,unsigned l = 0,unsigned r = 0,unsigned par = 0);

	//大小比较规则的设定，有利于后序排序的进行。
	bool operator< (const HNode& other);

};

