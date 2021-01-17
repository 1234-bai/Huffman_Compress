#pragma once

#include "HuffmanTree.h" 

/*文件读写类*/
class FileRW
{
public:
	HuffmanTree Tree;	//由文件建立的哈夫曼树类

	//当前文件类，文件的文件名（路径）
    char* filename;

	int leaveBitNum;

	//当前文件类型（后缀名）
	std::string thisType;
	//原码文件类型（后缀名）
	std::string oriType;

	//当前文件类别，表示是原码文件，还是译码文件，还是压缩后文件
	unsigned fileType;

	//读写文件时，01编码（压缩码）的起始位置。
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

	//获得建类所使用的的哈弗曼树，用于后序控制台函数测试
	HuffmanTree getTree();
};

