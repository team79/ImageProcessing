// Huffman.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ImageProcessing.h"
#include "Huffman.h"
#include "afxdialogex.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <map>
#include <algorithm>
// CHuffman �Ի���

IMPLEMENT_DYNAMIC(CHuffman, CDialogEx)

CHuffman::CHuffman(CWnd* pParent /*=NULL*/)
	: CDialogEx(CHuffman::IDD, pParent)
{

}

CHuffman::~CHuffman()
{
}

void CHuffman::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CHuffman, CDialogEx)
END_MESSAGE_MAP()


// CHuffman ��Ϣ�������
struct Node{
	std::vector<std::string> s;
	std::vector<int> i;
	int sum;
	bool operator<(const Node &b){
		return sum > b.sum;
	}
};

BOOL CHuffman::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	std::ifstream  in(filepath);
	std::map<std::string, int> mp;
	mp.clear();
	if(in.is_open()){
		while(!in.eof()){
			std::string temp;
			in >> temp;
			mp[temp]++;
		}
	}
	//for( int i = 0; )	
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
