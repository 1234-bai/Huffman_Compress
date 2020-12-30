#pragma warning(disable:6385 6386 26451)

#include "HuffmanTree.h"
#include <queue>
#include <iostream>
#include <utility>
#include <climits>

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
	HTree = new HNode[2*alT.alpNum + 1U];
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
    std::cout << "\n**************buildTree sucess**************\n" << std::endl;
	nowPtr = 2 * alT.alpNum - 1;
	if (!buildCode()) return false;
	std::cout << "\n**************buildCode sucess**************\n" << std::endl;
	return true;
}



void HuffmanTree::Select(std::queue<std::pair<HNode, int> >& fir, std::queue<std::pair<HNode, int> >& sec,
    unsigned& min_inx_1, unsigned& min_inx_2, int num)
{//进入此函数，不可能两个队列同时为空
	if (fir.empty() && sec.empty()) exit(-1);

	//传进来的权重值肯定是大于0的
	//初始化每个权重都为最大值
	int min_weight_1 = INF, min_weight_2 = INF;
	min_inx_1 = min_inx_2 = 0;

	if (!fir.empty()) {
		min_weight_1 = fir.front().first.weight;
		min_inx_1 = fir.front().second;
	}
	if (!sec.empty()) {
		min_weight_2 = sec.front().first.weight;
		min_inx_2 = sec.front().second;
	}
	if (min_weight_1 <= min_weight_2) {
		fir.pop();
		int weight = INF;
		if (!fir.empty()) weight = fir.front().first.weight;
		if (weight <= min_weight_2) {
			min_weight_2 = weight;
			min_inx_2 = fir.front().second;
			fir.pop();
		}
	}
	else {
		sec.pop();
		int weight = INF;
		if (!fir.empty()) weight = sec.front().first.weight;
		if (weight <= min_weight_1) {
			min_weight_1 = min_weight_2; min_weight_2 = weight;
			min_inx_1 = min_inx_2; min_inx_2 = sec.front().second;
			sec.pop();
		}
	}

	sec.push(std::make_pair( HNode(min_weight_1 + min_weight_2, min_inx_1, min_inx_2),
			num) );
}

bool HuffmanTree::buildTree()
{
        //根据字母表建立队列fir
        std::queue<std::pair<HNode, int> > fir;
        std::queue<std::pair<HNode, int> > sec;
        for (unsigned i = 1; i <= alT.alpNum; ++i) {
            fir.push(std::make_pair(HTree[i], i));
        }

        unsigned min1, min2;
        unsigned n = alT.alpNum;
        if (alT.alpNum < 1) { std::cout << "\n字母个数少" << std::endl; return false; };
		if (alT.alpNum == 1) return true;

        int num = alT.alpNum + 1;
        while (!(fir.empty() && sec.size()==1)) {
            Select(fir, sec, min1, min2, num);
			if(!sec.empty()) HTree[num] = sec.back().first;
            num++;
        }

    return true;
}

bool HuffmanTree::buildCode()
{//O(n)：遍历二叉树的时间复杂度，函数待测试
	if (alT.alpNum == 1) {
		HCode[1] = "0";
		return true;
	}
	std::string str = "\0";
	unsigned root = 2 * alT.alpNum - 1;
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
			str.pop_back();
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
    for (unsigned i = 1; i <= alT.alpNum; ++i)
        std::cout << i<<"：" << HCode[i] << std::endl;
}


