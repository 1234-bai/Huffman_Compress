#pragma once


#include "HuffmanTree.h" 

class FileRW
{
public:
	HuffmanTree Tree;
    char* filename;
	int leaveBitNum;

	unsigned fileType;
	unsigned beginInx;

private:
	void write_headData2(std::ofstream& fout, const char* fileType,const char* tofile);

public:

	FileRW(const char* filename = "\0");


	bool initFileRW(const char* filename);

	int initLeaveBitNum(const char* filename);


	bool codeF2decodF(const char* tofile);


	bool decodF2comF(const char* tofile);


	bool comF2decodF(const char* tofile);


	bool decodF2codeF(const char* tofile);

	bool codeF2comF(const char* tofile);
	bool codeF2comF(const char* tofile,bool deleteDecodeFile);


	bool comF2codF(const char* tofile);
	bool comF2codF(const char* tofile, bool deleteDecodeFile);

	HuffmanTree getTree();
};

