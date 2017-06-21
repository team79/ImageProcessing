// Huffman.cpp : 实现文件
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
// CHuffman 对话框

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


// CHuffman 消息处理程序
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

	// TODO:  在此添加额外的初始化
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
	// 异常: OCX 属性页应返回 FALSE
}
