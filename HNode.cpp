#include "HNode.h"
#include <iostream>

HNode::HNode(unsigned wei, unsigned l, unsigned r, unsigned pa)
{
	weight = wei;
	lch = l;
	rch = r;
	par = pa;
}

bool HNode::initHNode(unsigned wei, unsigned l, unsigned r, unsigned pa)
{
	weight = wei;
	lch = l;
	rch = r;
	par = pa;
	return true;
}

HNode HNode::mergeHNode(const HNode& other, unsigned l, unsigned r, unsigned par)
{
	return HNode(weight + other.weight, l, r, par);
}

//��ʱ����ô���壬���廹�����ƣ����ң�����֪���ò��õĵ�����Ƚϣ�����������2020.12.19
bool HNode::operator<(const HNode& other)
{
	return weight < other.weight;
}

std::ostream& operator<<(std::ostream& out, const HNode& node)
{
	out << node.weight << ' ' << node.lch << ' ' << node.rch << ' ' << node.par;
	return out;
}
