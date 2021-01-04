//#pragma warning(disable:6385 6386 26451)

#include "FileRW.h"
#include <fstream>
#include <string>
#include <cstring>
#include "BitDeal.h"

#define chn 4

//获得文件名后缀的小函数（非类成员函数，只是这个文件的小函数）
std::string getFileType(std::string namestr, char ch = '.')
{
    int len = namestr.length();
    int indx = namestr.rfind(ch) + 1;
    if (indx < 0 || indx >= len) return std::string("\0");
    len -= indx;
    return namestr.substr(indx, len);
}

//向文件中写入头数据
void FileRW::write_headData2(std::ofstream& fout, const char* a,const char* tofile)
{
    int step = strlen(a) + 1;
    fout.write(a, step);

    int num = oriType.length();
    fout.write((char*)&num, sizeof(num));
    char *b = new char[num + 1];
    for (int i = 0; i < num; ++i)
        b[i] = oriType[i];
    b[num] = '\0';
    fout.write(b, num + 1);

    fout.write((char*)&leaveBitNum, sizeof(leaveBitNum));
    Tree.getAlphaTable().writeHdataToFile(tofile, step + sizeof(num) + num+1 + sizeof(leaveBitNum));
}

//文件初始化
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
    //源文件文件名的初始化
    int len = strlen(filename);
    this->filename = new char[len+1];
    for(int i = 0; i < len && filename[i]; ++i){
        this->filename[i] = filename[i];
    }
    this->filename[len] = '\0';

    std::ifstream fin(filename, std::ios::in | std::ios::binary);
    if (!fin.is_open()) return false;

    //从文件名获得文件类型
    std::string namestr(filename);
    namestr = getFileType(namestr);

    //从文件内容获得文件类型
    char a[chn] = { 0 };
    fin.read(a, sizeof(a));
    std::string headstr(a);

    if (headstr == namestr) {
        thisType = headstr;
        if (headstr == "cpr")
            fileType = 2;
        else if (headstr == "dee")
            fileType = 3;
        else return false;
    }
    //else if (namestr == "txt" || namestr == "bmp")
      //  fileType = 1;
    else {
        thisType = namestr;
        fileType = 1;
        //return false;
    }

    //根据不同的文件类别进行不同的文件操作（树的初始化之类）
    if (fileType == 1) {
        Tree.initHTree(*(new alphaTable(filename)));
        //源码文件的原始文件类型就是自己
        oriType = thisType;
        leaveBitNum = initLeaveBitNum(filename);
        if (leaveBitNum == -1) return false;
    }
    else if (fileType == 2 || fileType == 3) {
        //获取头数据中的源文件类型
        int num = 0;
        fin.read((char*)&num, sizeof(num));
        char* b = new char[num + 1];
        fin.read(b, num + 1);
        oriType = std::string(b);
        //读取剩余字节数，并读取建立字母表的内容，并建树
        fin.read((char*)&leaveBitNum, sizeof(leaveBitNum));
        Tree.initHTree(*(new alphaTable(filename, true, sizeof(a) + sizeof(num) + num+1 + sizeof(leaveBitNum))));
    }
    else {
        fin.close();
        return false;
    }

    alphaTable ALP = Tree.getAlphaTable();
    beginInx = sizeof("cpr") + sizeof(int) + oriType.length()+1 +
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

bool FileRW::to_codeF(const char* filePath)
{
    if (fileType == 1) return false;

    //从filename中提取出文件真正的名字(不包括路径)
    std::string truename(filename);
    truename = getFileType(truename,'/');
    if (truename == "\0") {
        truename = getFileType(std::string(filename), '\\');
    }
    //if (truename == "\0")
      //  return false;
    //改变名字后缀
    int num = truename.rfind('.') + 1;
    if (num < 0 || num >= (int)truename.length()) return false;
    truename = std::string(filePath) + std::string("/") + truename.substr(0, num) + oriType;

    if (thisType == "dee") {
        if (!decodF2codeF(truename.c_str())) return false;
    }
    else if (thisType == "cpr") {
        if (!comF2codF(truename.c_str())) return false;
    }
    else return false;
    return true;
}

bool FileRW::codeF2decodF(const char* tofile)
{
    if (fileType != 1) return false;

    std::ofstream fout(tofile, std::ios::out|std::ios::binary);
    if (!fout.is_open()) return false;

    write_headData2(fout, "dee", tofile);
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

    write_headData2(fout, "cpr", tofile);
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

    write_headData2(fout, "dee", tofile);
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

    write_headData2(fout, "cpr", tofile);
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
