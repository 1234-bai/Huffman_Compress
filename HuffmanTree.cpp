//#pragma warning(disable:6385 6386)

#include "HuffmanTree.h"
#include <queue>
#include <iostream>

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
	HTree = new HNode[alT.alpNum + 1];
	if (!HTree) return false;
	HCode = new std::string[alT.alpNum + 1];
	if (!HCode) return false;
	this->alT.sortAlpTab();
	for (unsigned i = 1; i <= alT.alpNum; ++i) {
		Alpha temp = alT.alpTab[i];
		hash[temp.ch] = i;
		HTree[i].initHNode((unsigned)temp.fre);
	}
    
	if (!buildTree()) return false;
	nowPtr = 2 * alT.alpNum - 1;
	if (!buildCode()) return false;

	return true;
}

void HuffmanTree::Select(std::queue<Alpha>& fir, std::queue<Alpha>& sec, unsigned& min_1, unsigned& min_2) {
    //在函数调用前判断好fir只有0或1个元素的情况，使得进入该函数的fir至少含有两个以上结点
    //
    Alpha fir_top = fir.front();
    fir.pop();

    Alpha fir_next = fir.front();
    fir.pop();
    //将这两个元素压入sec中,在sec中记录这两个元素
    sec.push(fir_top);
    sec.push(fir_next);
    Alpha sec_top = fir_top;
    Alpha sec_next = fir_next;

    //对1、2初始化后，开始建树
        //如果fir为空，比较sec的两个元素
    if (fir.empty()) {
        min_1 = hash[sec.front().ch];
        sec.pop();
        min_2 = hash[sec.front().ch];
        sec.pop();
    }
    else {
        fir_top = fir.front();
        fir.pop();
        //如果fir出一次就空，比较fir_top和sec_top即可
        if (fir.empty()) {
            sec_top = sec.front();
            sec.pop();
            min_1 = fir_top.fre < sec_top.fre ? hash[fir_top.ch] : hash[sec_top.ch];
            min_2 = fir_top.fre >= sec_top.fre ? hash[fir_top.ch] : hash[sec_top.ch];
        }
        //如果fir有至少两个元素，sec只有一个元素，比较fir_top和sec_top,
        //如果fir_top>sec_top,则min_1为sec_top、min_2为fir_top
        //否则比较fir_top+fir_next和fir_top+sec_top大小
        else {
            sec_top = sec.front();
            sec.pop();
            if (sec.empty()) {
                if (fir_top.fre > sec_top.fre) {
                    min_1 = hash[sec_top.ch];
                    min_2 = hash[fir_top.ch];
                }
                else {
                    if (fir_top.fre + fir_next.fre < fir_top.fre + sec_top.fre) {
                        min_1 = hash[fir_top.ch];
                        min_2 = hash[fir_next.ch];
                    }
                    else {
                        min_1 = hash[fir_top.ch];
                        min_2 = hash[sec_top.ch];
                    }
                }
            }
            //如果fir和sec都有两个及以上元素，进行各种情况比较
            else {
                //三种情况：
                //队列fir中的队首和第二位合并--con_1
                //队列sec中的队首和第二位合并--con_2
                //队列fir中的队首和sec中的队首合并--con_3
                unsigned con_1 = fir_top.fre + fir_next.fre;
                unsigned con_2 = fir_top.fre + sec_top.fre;
                unsigned con_3 = sec_top.fre + sec_next.fre;

                if (con_1 <= con_2 && con_1 <= con_3) {
                    min_1 = hash[fir_top.ch];
                    min_2 = hash[fir_next.ch];
                }
                else if (con_2 <= con_1 && con_2 <= con_3) {
                    min_1 = hash[fir_top.ch];
                    min_2 = hash[sec_top.ch];
                }
                else if (con_3 <= con_2 && con_3 <= con_1) {
                    min_1 = hash[sec_top.ch];
                    min_2 = hash[sec_next.ch];
                }
            }
        }
    }

}

bool HuffmanTree::buildTree()
{
        //根据字母表建立队列fir
        std::queue<Alpha> fir;
        std::queue<Alpha> sec;
        for (unsigned i = 1; i <= alT.alpNum; ++i) {
            fir.push(alT.alpTab[i]);
        }

        unsigned min1, min2;
        unsigned n = alT.alpNum;
        if (alT.alpNum < 1) { std::cout << "\n字母个数少" << std::endl; exit(0); };
		if (alT.alpNum == 1) return true;

        int num = alT.alpNum + 1;
        while (!(fir.empty() && sec.size()==1)) {
            Select(fir, sec, min1, min2);
            HTree[min1].par = num; HTree[min2].par = num;
            HTree[num].lch = min1; HTree[num].rch = min2;
            HTree[num].weight = HTree[min1].weight + HTree[min2].weight;
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
    for (unsigned i = 0; i < alT.alpNum; ++i)
        std::cout << HCode[i] << std::endl;
}


