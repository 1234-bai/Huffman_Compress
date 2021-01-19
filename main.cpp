//随机和人工输入数据模块，未添加。
//考虑在压缩文件中加入源文件格式，方便解压

#include <iostream>
#include "alphaTable.h"
#include <locale>
#include "BitDeal.h"
#include "HuffmanTree.h"
#include "FileRW.h"

using namespace std;

void alphaTable_test();

void BitDeal_test();

void HuffmanTree_test();

void FileRW_codeF_decodF_test();

void FileRW_decodF_comF_test();

void FileRW_codeF_comF_test();

void FileRW_to_codeF_test();

int main()
{
	int m;
	std::cout << "请输入要检测的子程序代号:" << endl;

	while (std::cin >> m) {
		if (m == 1)
			alphaTable_test();
		else if (m == 2)
			BitDeal_test();
		else if (m == 3)
			HuffmanTree_test();
		else if (m == 4)
			FileRW_codeF_decodF_test();
		else if (m == 5)
			FileRW_decodF_comF_test();
		else if (m == 6)
			FileRW_codeF_comF_test();
		else if (m == 7)
			FileRW_to_codeF_test();
	}
	return 0;
}

//“建立字母表”测试函数
void alphaTable_test()
{
	alphaTable al("1234.txt");		//读取文本文件，建立字母表
	std::cout << "根据原文本文件建立的字母表：" << endl;
	al.print();		//打印字母表，观察出现字符
	al.writeHdataToFile("3456.txt");	//检查“头数据写入”函数
	std::cout << "根据头数据建立的字母表：" << endl;
	alphaTable a2("3456.txt", true);	//读取非原码文件，建立字母表
	a2.print();		//打印字母表，同原文本文件比对
}

//位运算函数类测试
void BitDeal_test()
{
	BitDeal BD;
	char a = 3;
	cout << "初始位序列为：";
	for (int i = 8; i >= 1; --i)
		std::cout << BD.getBit(a, i);
	std::cout << "\n请输入要改变的位和对应的改变值:\n";
	int bitnum = 1, v = 0;
	while (cin >> bitnum >> v) {
		if (bitnum < 0 || bitnum > 8) break;
		if (v != 0 && v != 1) break;
		BD.setBit(a, bitnum, v);
		cout << "改变后位序列为：";
		for (int i = 8; i >= 1; --i)
			std::cout << BD.getBit(a, i);
		cout << "\n此字节代表的值为：" << a << endl;
		std::cout << "\n请输入要改变的位和对应的改变值:\n";
	}
}

//哈夫曼树建立函数测试
void HuffmanTree_test()
{
	HuffmanTree tree(*new alphaTable("1234.txt"));	//根据目标文件建立字母表，建立树表，建立编码表
	tree.print();	//将树打印观察结果
	//输入字符，测试编码表建立是否成功，以及测试字符同索引的映射是否建立成功
	char ch;
	std::cout << "请输入字符：";
	while (cin >> ch) {
		if (ch == '#') break;
		cout << tree.Ch_2_01Str(ch) << endl;
		std::cout << "请输入字符：";
	}
}

//文件编码译码函数测试
void FileRW_codeF_decodF_test()
{
	FileRW file2("1234.txt");	//根据原码文件建立字母表，哈夫曼树表以及编码表
	file2.codeF2decodF("1234.dee");		//调用函数
	cout << "根据原码文件建立的相关数据：" << endl;
	cout << "冗余位数：" << file2.leaveBitNum << endl;
	cout << "此文件类型：" << file2.thisType << endl;
	cout << "原码文件类型：" << file2.oriType << endl;
	file2.getTree().getAlphaTable().print();

	FileRW file("1234.dee");	//根据译码文件，建立相关数据
	if (file.decodF2codeF("1234_fromdee.txt")) {//建立成功
		cout << "根据译码文件建立的相关数据：" << endl;
		cout << "冗余位数：" << file.leaveBitNum << endl;
		cout << "此文件类型：" << file.thisType << endl;
		cout << "原码文件类型：" << file.oriType << endl;
		file.getTree().getAlphaTable().print();
	}
}

void FileRW_decodF_comF_test()
{
	FileRW file("1234.dee");
	file.decodF2comF("1234dee2cpr.cpr");
	//cout << file.beginInx << endl;
	cout << file.leaveBitNum << endl;
	cout << file.thisType << endl;
	cout << file.oriType << endl;
	//file.getTree().getAlphaTable().print();
	FileRW file2("1234dee2cpr.cpr");
	//file2.getTree().getAlphaTable().print();
	//cout << file2.beginInx << endl;
	cout << file2.leaveBitNum << endl;
	cout << file2.thisType << endl;
	cout << file2.oriType << endl;
	file2.comF2decodF("1234_fromcpr.dee");
}

void FileRW_codeF_comF_test()
{
	FileRW file("1234.txt");	//根据原码文件建立字母表，哈夫曼树表以及编码表
	file.codeF2comF("1234.cpr");	//调用压缩函数
	cout << "根据原码文件建立的相关数据：" << endl;
	cout << "冗余位数：" << file.leaveBitNum << endl;
	cout << "此文件类型：" << file.thisType << endl;
	cout << "原码文件类型：" << file.oriType << endl;
	file.getTree().getAlphaTable().print();

	FileRW file2("1234.cpr");	//根据压缩文件建立
	cout << "根据压缩文件建立的相关数据：" << endl;
	cout << "冗余位数：" << file2.leaveBitNum << endl;
	cout << "此文件类型：" << file2.thisType << endl;
	cout << "原码文件类型：" << file2.oriType << endl;
	file2.getTree().getAlphaTable().print();
	file2.comF2codF("1234_fromcpr.txt");	//调用解压函数
}

void FileRW_to_codeF_test()
{
	FileRW file("1234.cpr");
	FileRW file2("3456.cpr");
	//cout << file.beginInx << endl;
	cout << file.leaveBitNum << endl;
	cout << file.thisType << endl;
	cout << file.oriType << endl;
	file.to_codeF("D:\\Cplus\\HuffmanCompress\\HuffmanCompress");
	file2.to_codeF("D:\\Cplus\\HuffmanCompress\\HuffmanCompress");
}