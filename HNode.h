#pragma once

#include <iostream>



class HNode
{

public:

	unsigned weight;

	unsigned lch, rch;

	unsigned par;

public:

	HNode(unsigned wei = 0, unsigned l = 0, unsigned r = 0, unsigned par = 0);


	bool initHNode(unsigned wei = 0, unsigned l = 0, unsigned r = 0, unsigned par = 0);


	HNode mergeHNode(const HNode& other,unsigned l = 0,unsigned r = 0,unsigned par = 0);


	bool operator< (const HNode& other);


	friend std::ostream& operator<< (std::ostream& out, const HNode &node);
};

