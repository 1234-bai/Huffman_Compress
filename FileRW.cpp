#include "FileRW.h"
#include <fstream>
#include <string>
#include <cstring>
#include "BitDeal.h"

//问题一：两种计算剩余bit的方法得到的结果不一样
//问题二：在转换原来的文件的时候，即使是相同的bit数，转换结果也不对
void FileRW::write_headData2(std::ofstream& fout, const char* a,const char* tofile)
{
    fout.seekp(0);
    fout.write(a, sizeof(a));
    fout.write((char*)&leaveBitNum, sizeof(leaveBitNum));
    Tree.getAlphaTable().writeHdataToFile(tofile, sizeof(a) + sizeof(leaveBitNum));
}

FileRW::FileRW(const char* filename)
{
    if(strcmp(filename,"\0") == 0){
        Tree = HuffmanTree();
        leaveBitNum = 0;
        fileType = 0;
        beginInx = 0;
        return;
    }
    else if (!initFileRW(filename)){
        exit(-2);
    }
}

bool FileRW::initFileRW(const char* filename)
{
    int len = strlen(filename);
    this->filename = new char[len+1];
    for(int i = 0; i < len && filename[i]; ++i){
        this->filename[i] = filename[i];
    }
    this->filename[len] = '\0';
    //
    //
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
        else return false;
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
        sum_bit += (int)code.length();
    }

    fin.close();

    sum_bit = sum_bit % (sizeof(char)*8);
    return sum_bit ? 8 - sum_bit : 0 ;
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

    std::ifstream fin(filename, std::ios::in | std::ios::binary);
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
    //bitnum表示要得到的那个字符的下标
    int bitnum = 9;
    unsigned num;
    while (!(fin.peek() == EOF) || (bitnum <= ((int)sizeof(char)*8 - leaveBitNum))) {
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

    std::ifstream fin(filename, std::ios::in | std::ios::binary);
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
{
    if (fileType != 1) return false;

    std::ofstream fout(tofile, std::ios::out | std::ios::binary);
    if (!fout.is_open()) return false;

    std::ifstream fin(filename, std::ios::in | std::ios::binary);
    if (!fin.is_open()) return false;

    char a[4] = "cpr";
    fout.write(a, sizeof(a));
    fout.write((char*)&leaveBitNum, sizeof(leaveBitNum));
    Tree.getAlphaTable().writeHdataToFile(tofile, sizeof(a) + sizeof(leaveBitNum));
    fout.seekp(beginInx);

    //
    BitDeal BD;
    char ch;
    char value;
    int bitnum = 1;
    while (fin.read(&ch,sizeof(char))) {
        std::string code = this->Tree.Ch_2_01Str(ch);
        for (const auto& it : code) {
            //
            BD.setBit(value, bitnum, it - '0');
            if (bitnum >= 8) {
                fout.write(&value, sizeof(value));
                bitnum = 1;
            }
            else bitnum++;
        }
        if (fin.peek() == EOF) {
            if (bitnum == 1) leaveBitNum = 0;
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

    fin.seekg(beginInx);

    BitDeal BD;
    char ch;
    //
    int bitnum = 9;
    int num;
    while ( fin.peek() != EOF || (bitnum <= (int)sizeof(char)*8 - leaveBitNum)) {
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
