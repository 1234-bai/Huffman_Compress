#pragma once



#include "alpha.h"
#include <string>

class alphaTable
{
public:

	Alpha* alpTab;

	unsigned alpNum;
	unsigned SIZE;
public:


	alphaTable(const char* filename = "\0", bool isComFile = false, int indx = 0);

	bool init(const char* filename = "\0", bool isComFile = false, int indx = 0);


	bool getAlpTab_File(const char* filename);


	unsigned getAlpNum();


	bool sortAlpTab();


	bool writeHdataToFile(const char* filename,int indx = 0);


	bool getAlpTab_Hdata(const char* filename,int indx = 0);

	void print();
};

