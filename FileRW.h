#pragma once

//�ļ���д��
/// <summary>
/// ����ԭ���ļ������ĸ��,��������������ֱ�Ӷ��ļ����в�������ñ����ļ���ֱ�ӶԱ����ļ����в�����
/// ���ѹ���ļ����м���̰���ͷ���ݵ�д�롣
/// </summary>

///�������⣺
/// �����ַ��Ľ�������������ļ��Ľ��������

#include "HuffmanTree.h" 

class FileRW
{
public:
	HuffmanTree Tree;
	const char* filename;
	int leaveBitNum;
	//1Ϊԭ���ļ���2Ϊѹ���ļ���3Ϊ�����ļ���0Ϊδ�����ļ���
	unsigned fileType;
	unsigned beginInx;

private:
	void write_headData2(std::ofstream& fout, const char* fileType,const char* tofile);

public:
	//��ʼ�������������ļ�����׺�����ļ�ͷ�������ݻ���ļ����͡��Ӷ������ĸ������
	FileRW(const char* filename = "\0");

	//��ʼ������
	bool initFileRW(const char* filename);

	int initLeaveBitNum(const char* filename);

	//�����ļ���ͷ���ݣ��ļ�����׺��ʣ���ֽ�������ĸ����ĸ�������ַ����࣬
	//Դ���ļ��������ļ�ת��
	bool codeF2decodF(const char* tofile);

	//ѹ���ļ�ͷ���ݣ��ļ�����׺��ʣ���ֽ�������ĸ����ĸ�������ַ�����
	//�����ļ���ѹ���ļ�ת��
	bool decodF2comF(const char* tofile);

	//ѹ���ļ��������ļ�ת��
	bool comF2decodF(const char* tofile);

	//�����ļ���Դ���ļ�ת��
	bool decodF2codeF(const char* tofile);

	//�����м䲻���������ļ���ֱ��ԭ��תѹ���Ĺ��̡�
	//Դ���ļ���ѹ���ļ�ת����Ĭ��ɾ���м���ת�������ļ�
	bool codeF2comF(const char* tofile);
	bool codeF2comF(const char* tofile,bool deleteDecodeFile);

	//�����м䲻���������ļ���ֱ��ѹ��תԭ��Ĺ��̡�
	//ѹ���ļ���Դ���ļ�ת����Ĭ��ɾ���м���ת�������ļ�
	bool comF2codF(const char* tofile);
	bool comF2codF(const char* tofile, bool deleteDecodeFile);

	//���ڻ�ȡ���������Ժ���
	HuffmanTree getTree();
};

