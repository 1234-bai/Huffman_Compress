#pragma once

#include "HuffmanTree.h" 

class FileRW
{
public:
	HuffmanTree Tree;

	//这个文件类，文件的文件名（路径）
    char* filename;

	int leaveBitNum;

	//这个文件类型（后缀名）
	std::string thisType;
	//原始文件类型（后缀名）
	std::string oriType;

	//这个文件类别，表示是源码文件，还是译码文件，还是压缩后文件
	unsigned fileType;

	unsigned beginInx;

private:

	void write_headData2(std::ofstream& fout, const char* fileType,const char* tofile);

public:

	FileRW(const char* filename = "\0");
	bool initFileRW(const char* filename);
	int initLeaveBitNum(const char* filename);

	//译码文件和压缩文件，自动转化为原格式的文件
	bool to_codeF(const char* filePath);

	//原码文件和译码文件的转换
	bool codeF2decodF(const char* tofile);
	bool decodF2comF(const char* tofile);

	//译码文件和压缩文件的转化
	bool comF2decodF(const char* tofile);
	bool decodF2codeF(const char* tofile);

	//原码文件和压缩文件的转化。（可以是经过中间过程的译码文件转换，即第二个重载）。
	bool codeF2comF(const char* tofile);
	bool codeF2comF(const char* tofile,bool deleteDecodeFile);
	bool comF2codF(const char* tofile);
	bool comF2codF(const char* tofile, bool deleteDecodeFile);

	HuffmanTree getTree();
};

