#pragma once

/*位操作函数类*/
class BitDeal
{
public:
	//获得对应位的值
	unsigned getBit(char& c, int i) {
		return (c >> (i-1)) & 1;
	}
	//改变对应位的值
	void setBit(char& c, int i, int v) {
		if (v)
			c |= (1 << (i-1));
		else
			c &= ~(1 << (i-1));
	}
};