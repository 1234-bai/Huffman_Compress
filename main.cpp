#include <iostream>
#include "alphaTable.h"
#include <locale>
#include "BitDeal.h"
#include "HuffmanTree.h"

using namespace std;

int main()
{
	int m;
	std::cout << "请输入选择检测的子程序代号:" << endl;
	while (std::cin >> m) {
		if (m == 1) {
			alphaTable al("1234.txt");
			al.print();
			al.writeHdataToFile("3456.txt");
			alphaTable a2("3456.txt", true);
			a2.print();
		}
		else if (m == 2) {
			BitDeal BD;
			char a = 3;
			for (int i = 8; i >= 1; --i)
				std::cout << BD.getBit(a, i);
			std::cout << "\n请输入要修改的位，和修改后的01串:";
			int bitnum = 1, v = 0;
			cin >> bitnum >> v;
			BD.setBit(a, bitnum, v);
			for (int i = 8; i >= 1; --i)
				std::cout << BD.getBit(a, i);
			cout << '\n' << a << endl;
		}
		else if (m == 3) {
			alphaTable al("1234.txt");
			al.print();
			HuffmanTree tree(al);
			tree.print();
			char ch;
			cin >> ch;
			cout << tree.Ch_2_01Str(ch) << endl;
		}
	}
	return 0;
}