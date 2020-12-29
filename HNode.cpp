#include "HNode.h"

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

//暂时先这么定义，定义还不完善，而且，还不知道用不用的到这个比较（哈哈哈哈）2020.12.19
bool HNode::operator<(const HNode& other)
{
	return weight < other.weight;
}

