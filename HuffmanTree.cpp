#pragma warning(disable:6385 6386 26451)

#include "HuffmanTree.h"
#include <queue>
#include <iostream>
#include <utility>
#include <climits>
#include <algorithm>

#define INF INT_MAX

HuffmanTree::HuffmanTree(alphaTable& alT)
{
	if (!initHTree(alT))
		exit(0);
}

HuffmanTree::HuffmanTree()
{
	HTree = nullptr;
	HCode = nullptr;
	hash.clear();
	nowPtr = -1;
	alT.init();
}

bool HuffmanTree::initHTree(alphaTable& alT)
{
	if (alT.alpNum < 1) return false;

	this->alT = alT;
	HTree = new HNode[2 * alT.alpNum + 1U];
	if (!HTree) return false;
	HCode = new std::string[alT.alpNum + 1U];
	if (!HCode) return false;
	this->alT.sortAlpTab();

	for (unsigned i = 1; i <= alT.alpNum; ++i) {
		Alpha temp = alT.alpTab[i];
		hash[temp.ch] = i;
		HTree[i].initHNode((unsigned)temp.fre);
	}
	if (!buildTree()) return false;
	//std::cout << "\n**************buildTree sucess**************\n" << std::endl;
	nowPtr = 2 * alT.alpNum - 1;
	if (!buildCode()) return false;
	//std::cout << "\n**************buildCode sucess**************\n" << std::endl;
	return true;
}



void HuffmanTree::Select(std::queue<std::pair<HNode, int> >& fir, std::queue<std::pair<HNode, int> >& sec,
	unsigned& min_inx_1, unsigned& min_inx_2, int num)
{
	if (fir.empty() && sec.empty()) exit(-1);

	//初始化
	int min_weight_1 = INF, min_weight_2 = INF;
	min_inx_1 = min_inx_2 = 0;

	//获得第一个队列的队头结点
	if (!fir.empty()) {
		min_weight_1 = fir.front().first.weight;
		min_inx_1 = fir.front().second;
	}
	//获得第二个队列的队头结点
	if (!sec.empty()) {
		min_weight_2 = sec.front().first.weight;
		min_inx_2 = sec.front().second;
	}

	//如果第一个队列队头结点的权重比第二个小
	if (min_weight_1 <= min_weight_2) {
		//第一个结点肯定是第一个队列队头结点了，出队列
		fir.pop();
		//第二小结点可能是第二个队列队头结点，有可能是第一个队列第二个结点，也就是此刻的一队列队头结点
		int weight = INF;
		if (!fir.empty()) weight = fir.front().first.weight;
		if (weight <= min_weight_2) {
			//第二小的是一队列第二个结点，出队列
			min_weight_2 = weight;
			min_inx_2 = fir.front().second;
			fir.pop();
		}
		else {
			//第二小是二对列队头结点，出队列
			sec.pop();
		}
	}
	else {//如果第二个队列队头结点的权重比第一个小，道理同上
		sec.pop();
		int weight = INF;
		if (!sec.empty()) weight = sec.front().first.weight;
		if (weight <= min_weight_1) {
			//默认min_inx_1为最小的那个，进行交换
			min_weight_1 = min_weight_2; min_weight_2 = weight;
			min_inx_1 = min_inx_2; min_inx_2 = sec.front().second;
			sec.pop();
		}
		else{
			//默认min_inx_1为最小的那个，所以利用STL进行交换
			std::swap(min_weight_1, min_weight_2);
			std::swap(min_inx_1, min_inx_2);
			fir.pop();
		}
	}
	//将最小的两个结点合并后，入二队列
	sec.push(std::make_pair(HNode(min_weight_1 + min_weight_2, min_inx_1, min_inx_2),
		num));
}

bool HuffmanTree::buildTree()
{
	//设置两个初始队列
	std::queue<std::pair<HNode, int> > fir;
	std::queue<std::pair<HNode, int> > sec;
	//将叶子结点按次序入第一个队列
	for (unsigned i = 1; i <= alT.alpNum; ++i) {
		fir.push(std::make_pair(HTree[i], i));
	}

	unsigned min1, min2;	//最小的两个元素在树表中对应的索引
	if (alT.alpNum < 1) { std::cout << "\n字母数量少" << std::endl; return false; };
	if (alT.alpNum == 1) return true;

	int num = alT.alpNum + 1;
	while (!(fir.empty() && sec.size() == 1)) {
		Select(fir, sec, min1, min2, num);	//挑选出两个最小的结点（索引）
		HTree[num] = sec.back().first;
		HTree[min1].par = num; HTree[min2].par = num;	//建立孩子关系
		num++;
	}

	return true;
}

bool HuffmanTree::buildCode()
{
	//只有一个字母，特殊情况特殊考虑
	if (alT.alpNum == 1) {
		HCode[1] = "0";
		return true;
	}

	//非递归遍历二叉树，获得每个叶子结点对应的01编码
	std::string str;
	unsigned root = 2 * (int)alT.alpNum - 1;
	for (unsigned i = 1; i <= root; ++i) {
		HTree[i].weight = 0;
	}
	unsigned p = root;
	while (p) {
		if (HTree[p].weight == 0) {
			HTree[p].weight = 1;
			if (HTree[p].lch != 0) {
				p = HTree[p].lch;
				str.push_back('0');
			}
			else if (HTree[p].rch == 0) {
				HCode[p] = str;
			}
		}
		else if (HTree[p].weight == 1) {
			HTree[p].weight = 2;
			if (HTree[p].rch != 0) {
				p = HTree[p].rch;
				str.push_back('1');
			}
		}
		else {
			HTree[p].weight = 0;
			p = HTree[p].par;
			if (!str.empty()) str.pop_back();
		}
	}

	return true;
}


HNode* HuffmanTree::getTree()
{
	return HTree;
}

std::string HuffmanTree::Ch_2_01Str(char ch)
{
	return HCode[hash[ch]];
}

alphaTable& HuffmanTree::getAlphaTable()
{
	return this->alT;
}

int HuffmanTree::getChInx(unsigned num)
{
	int p = nowPtr;
	if (num)
		p = HTree[p].rch ? HTree[p].rch : p;
	else
		p = HTree[p].lch ? HTree[p].lch : p;
	if (!(HTree[p].lch || HTree[p].rch)) {
		nowPtr = 2 * alT.alpNum - 1;
		return p;
	}
	else nowPtr = p;
	return -1;
}

void HuffmanTree::print()
{
	alT.print();

	//for (unsigned i = 1; i < 2*alT.alpNum; ++i)
	//	std::cout << i << ":" << HTree[i]  << std::endl;

	for (unsigned i = 1; i <= alT.alpNum; ++i)
		std::cout << i  << ":" << HCode[i] << std::endl;
}


