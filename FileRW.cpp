#include "FileRW.h"
#include <fstream>
#include <string>
#include <cstring>
#include "BitDeal.h"

//考虑用此函数写头数据，因为这个函数要使用多次
//问题在于：写入的时候总比在函数往外多写入几个字节。
void FileRW::write_headData2(std::ofstream& fout, const char* a,const char* tofile)
{
	fout.seekp(0);
	fout.write(a, sizeof(a));
	fout.write((char*)&leaveBitNum, sizeof(leaveBitNum));
	Tree.getAlphaTable().writeHdataToFile(tofile, sizeof(a) + sizeof(leaveBitNum));
}

FileRW::FileRW(const char* filename)
{
	if (!initFileRW(filename))
		exit(-2);
}

bool FileRW::initFileRW(const char* filename)
{
	this->filename = filename;

	//1为原码文件，2为压缩后文件，3为译码文件，0为未操作文件。
	//怎么分辨文件，是个问题，可能会存在大量的bug,现暂时采用名字后缀和文件头数据的双重方式确认
	std::ifstream fin(filename, std::ios::in | std::ios::binary);
	if (!fin.is_open()) return false;

	char a[4] = { 0 };
	fin.read(a, sizeof(a));
	std::string namestr(filename);
	namestr = namestr.substr(namestr.length() - 3, 3);
	std::string headstr(a);
	if (headstr == namestr) {
		if (headstr == "cpr")
			fileType = 2;
		else if (headstr == "dee")
			fileType = 3;
		else false;
	}
	else if (namestr == "txt" || namestr == "bmp")
		fileType = 1;
	else {
		return false;
	}

	if (fileType == 1) {
		Tree.initHTree(*(new alphaTable(filename, false)));
		leaveBitNum = initLeaveBitNum(filename);
		if (leaveBitNum == -1) return false;
	}
	else if (fileType == 2 || fileType == 3) {
		fin.read((char*)&leaveBitNum, sizeof(leaveBitNum));
		Tree.initHTree(*(new alphaTable(filename, true, sizeof(a) + sizeof(leaveBitNum))));
	}
	else {
		fin.close();
		return false;
	}

	alphaTable ALP = Tree.getAlphaTable();
	beginInx = sizeof("cpr") +
		sizeof(leaveBitNum) +
		sizeof(ALP.getAlpNum()) +
		ALP.getAlpNum() * (sizeof(ALP.alpTab[0].ch) + sizeof(ALP.alpTab[0].fre));

	fin.close();
	return true;
}

int FileRW::initLeaveBitNum(const char* filename)
{
	if (fileType != 1) return -1;

	std::ifstream fin(filename, std::ios::in | std::ios::binary);
	if (!fin.is_open()) return -1;

	char ch;
	int sum_bit = 0;
	while (fin.read(&ch, sizeof(char))) {
		std::string code = this->Tree.Ch_2_01Str(ch);
		sum_bit += code.length();
	}

	fin.close();

	return (sum_bit % sizeof(char));
}

bool FileRW::codeF2decodF(const char* tofile)
{
	if (fileType != 1) return false;

	std::ofstream fout(tofile, std::ios::out|std::ios::binary);
	if (!fout.is_open()) return false;
	char a[4] = "dee";
	fout.write(a, sizeof(a));
	fout.write((char*)&leaveBitNum, sizeof(leaveBitNum));
	Tree.getAlphaTable().writeHdataToFile(tofile, sizeof(a) + sizeof(leaveBitNum));
	//write_headData2(fout, "dee", tofile);
	fout.seekp(beginInx);

	std::ifstream fin(filename, std::ios::in|std::ios::binary);
	if(!fin.is_open())	return false;

	char ch;
	while (fin.get(ch)) {
		std::string code = Tree.Ch_2_01Str(ch);
		for (const auto& it : code) {
			fout.put(it);
		}
	}

	fin.close();
	fout.close();
	return true;
}

bool FileRW::decodF2comF(const char* tofile)
{
	if (fileType != 3) return false;

	std::ofstream fout(tofile, std::ios::out | std::ios::binary);
	if (!fout.is_open()) return false;

	char a[4] = "cpr";
	fout.write(a,sizeof(a));
	fout.write((char*)&leaveBitNum, sizeof(leaveBitNum));
	Tree.getAlphaTable().writeHdataToFile(tofile, sizeof(a) + sizeof(leaveBitNum));
	fout.seekp(beginInx);

	std::ifstream fin(filename, std::ios::out | std::ios::binary);
	if (!fin.is_open()) return false;
	fin.seekg(beginInx);

	BitDeal BD;
	char bit;
	char value;
	int index = 1;
	while (fin.read(&bit, sizeof(bit))) {
		BD.setBit(value, index, bit - '0');
		if (index++ == 8) {
			fout.write(&value, sizeof(value));
			index = 1;
		}
	}
	if (index != 1) {
		fout.write(&value, sizeof(value));
	}

	fin.close();
	fout.close();
	return true;
}

bool FileRW::comF2decodF(const char* tofile)
{
	if (fileType != 2) return false;

	std::ofstream fout(tofile, std::ios::out | std::ios::binary);
	if (!fout.is_open()) return false;

	char a[4] = "dee";
	fout.write(a, sizeof(a));
	fout.write((char*)&leaveBitNum, sizeof(leaveBitNum));
	Tree.getAlphaTable().writeHdataToFile(tofile, sizeof(a) + sizeof(leaveBitNum));
	fout.seekp(beginInx);


	std::ifstream fin(filename, std::ios::in | std::ios::binary);
	if (!fin.is_open()) return false;
	fin.seekg(beginInx);

	BitDeal BD;
	char ch;
	//bitnum的含义:取ch的第几位
	int bitnum = 9;
	unsigned num;
	while (!fin.eof() || (bitnum <= ((int)sizeof(char)*8 - leaveBitNum))) {
		if (bitnum > 8) {
			fin.read(&ch, sizeof(char));
			bitnum = 1;
		}
		num = BD.getBit(ch, bitnum++);
		char c = num + '0';
		fout.write(&c, sizeof(c));
	}

	fin.close();
	fout.close();
	return true;
}

bool FileRW::decodF2codeF(const char* tofile)
{
	if (fileType != 3) return false;

	std::ofstream fout(tofile, std::ios::out | std::ios::binary);
	if (!fout.is_open()) return false;

	std::ifstream fin(filename, std::ios::out | std::ios::binary);
	if (!fin.is_open()) return false;
	fin.seekg(beginInx);

	char ch;
	while (fin.read(&ch,sizeof(ch))) {
		int inx = Tree.getChInx(ch-'0');
		if (inx != -1) {
			fout.write(&Tree.getAlphaTable().alpTab[inx].ch, sizeof(char));
		}
	}

	fin.close();
	fout.close();
	return true;
}


bool FileRW::codeF2comF(const char* tofile)
{ //在哪计算剩余bit数????,换句话说，压缩文件里leaveBitNum放在哪？，需要将整个文件都读过，才能知道leavebitnum。
  //先把剩余字节数放在文件后缀之后。
	if (fileType != 1) return false;

	std::ofstream fout(tofile, std::ios::out | std::ios::binary);
	if (!fout.is_open()) return false;

	char a[4] = "cpr";
	fout.write(a, sizeof(a));
	fout.write((char*)&leaveBitNum, sizeof(leaveBitNum));
	Tree.getAlphaTable().writeHdataToFile(tofile, sizeof(a) + sizeof(leaveBitNum));
	fout.seekp(beginInx);

	std::ifstream fin(filename, std::ios::in | std::ios::binary);
	if (!fin.is_open()) return false;

	//编码并压缩过程
	BitDeal BD;
	char ch;
	char value;
	int bitnum = 1;
	while (fin.read(&ch,sizeof(char))) {
		std::string code = this->Tree.Ch_2_01Str(ch);
		for (const auto& it : code) {
			//将第bitnum位转化成it;
			BD.setBit(value, bitnum, it - '0');
			if (bitnum++ == 8) {
				fout.write(&value, sizeof(value));
				bitnum = 1;
			}
		}
		if (fin.eof()) {
			if (bitnum != 1) leaveBitNum = 0;
			else {
				fout.write(&value, sizeof(value));
				leaveBitNum = 9 - bitnum;
			}
			break;
		}
	}

	fin.close();
	fout.close();
	return true;
}

bool FileRW::codeF2comF(const char* tofile, bool deleteDecodeFile)
{
	std::string decfilename = std::string(filename).substr(0,std::strlen(filename)-3) + std::string("dec");
	if(!codeF2decodF(decfilename.c_str())) return false;
	if (!decodF2comF(tofile)) return false;
	if (deleteDecodeFile) {
		return remove(decfilename.c_str());
	}
	return true;
}

bool FileRW::comF2codF(const char* tofile)
{
	if (fileType != 2) return false;

	std::ofstream fout(tofile, std::ios::out | std::ios::binary);
	if (!fout.is_open()) return false;
	std::ifstream fin(filename, std::ios::in | std::ios::binary);
	if (!fin.is_open()) return false;
	alphaTable &ALP = Tree.getAlphaTable();
	fin.seekg(beginInx);

	BitDeal BD;
	char ch;
	//bitnum的含义:取ch的第几位
	int bitnum = 9;
	int num;
	while (!fin.eof() || (bitnum <= (int)sizeof(char)*8 - leaveBitNum)) {
		if (bitnum > 8) {
			fin.read(&ch, sizeof(char));
			bitnum = 1;
		}
		num = BD.getBit(ch, bitnum++);
		int inx = Tree.getChInx(num);
		if (inx != -1) {
			fout.write(&Tree.getAlphaTable().alpTab[inx].ch, sizeof(char));
		}
	}
	//剩余字符也考虑了，但是没有调试，就看怎么从哈夫曼树里获得字符了
	/*根据哈夫曼树回溯,找到那个字符*/
	/*思路是哈夫曼树类获得一个字符串，然后返回一个结果，返回对应的字符，或异类字符（？？？）
	* 如果是将文件名给树类的话，就不如开始的时候就直接把文件给树类（即取消文件类的操作）
	* 如果是将树的指针传出来的话，那么相当于解码在树外进行，对树的封装性就失败了。
	*/
	fin.close();
	fout.close();
	return true;
}

bool FileRW::comF2codF(const char* tofile, bool deleteDecodeFile)
{
	std::string decfilename = std::string(filename).substr(0,strlen(filename)-3) + std::string("dec");
	if (!comF2decodF(decfilename.c_str())) return false;
	if (!decodF2codeF(tofile)) return false;
	if (deleteDecodeFile) {
		return remove(decfilename.c_str());
	};
	return true;
}

HuffmanTree FileRW::getTree()
{
	return Tree;
}
