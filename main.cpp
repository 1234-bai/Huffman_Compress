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
	}
	return 0;
}

void alphaTable_test()
{
	alphaTable al("1234.txt");
	al.print();
	al.writeHdataToFile("3456.txt");
	alphaTable a2("3456.txt", true);
	a2.print();
}

void BitDeal_test()
{
	BitDeal BD;
	char a = 3;
	for (int i = 8; i >= 1; --i)
		std::cout << BD.getBit(a, i);
	std::cout << "\n请输入要改变的位和对应的改变值:\n";
	int bitnum = 1, v = 0;
	while (cin >> bitnum >> v) {
		if (bitnum < 0 || bitnum > 8) break;
		if (v != 0 && v != 1) break;
		BD.setBit(a, bitnum, v);
		for (int i = 8; i >= 1; --i)
			std::cout << BD.getBit(a, i);
		cout << '\n' << a << endl;
	}
}

void HuffmanTree_test()
{
	HuffmanTree tree(*new alphaTable("1234.txt"));
	tree.print();
	char ch;
	while (cin >> ch) {
		if (ch == '#') break;
		cout << tree.Ch_2_01Str(ch) << endl;
	}
}

void FileRW_codeF_decodF_test()
{//txt和dee的相互转换没有问题
	FileRW file2("1234.txt");
	file2.codeF2decodF("1234.dee");
	cout << file2.beginInx << endl;
	cout << file2.leaveBitNum << endl;
	//file2.getTree().getAlphaTable().print();
	FileRW file("1234.dee");
	file.decodF2codeF("1234_fromdee.txt");
	cout << file.beginInx << endl;
	cout << file.leaveBitNum << endl;
	//file.getTree().getAlphaTable().print();
}

void FileRW_decodF_comF_test()
{//dee在向cpr转换时会出问题
	FileRW file("1234.dee");
	file.decodF2comF("1234dee2cpr.cpr");
	cout << file.beginInx << endl;
	cout << file.leaveBitNum << endl;
	//file.getTree().getAlphaTable().print();
	FileRW file2("1234dee2cpr.cpr");
	//file2.getTree().getAlphaTable().print();
	cout << file2.beginInx << endl;
	cout << file2.leaveBitNum << endl;
	file2.comF2decodF("1234_fromcpr.dee");
}

void FileRW_codeF_comF_test()
{
	FileRW file("1234.pdf");
	file.codeF2comF("1234.cpr");
	cout << file.beginInx << endl;
	cout << file.leaveBitNum << endl;
	//file.getTree().getAlphaTable().print();
	FileRW file2("1234.cpr");
	cout << file2.beginInx << endl;
	cout << file2.leaveBitNum << endl;
	//file2.getTree().getAlphaTable().print();
	file2.comF2codF("1234_fromcpr.pdf");
}
