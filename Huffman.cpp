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
#include <queue>
#include <map>
#include <cmath>
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
	std::vector<std::string> code;
	int sum;
	bool operator<(Node b) const{
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
			if(temp == "")	continue;
			mp[temp]++;
		}
	}
	std::priority_queue<Node> q;
	for( std::map<std::string, int>::iterator it = mp.begin(); it != mp.end(); it++ ){
		Node temp;
		temp.s.clear();
		temp.code.clear();
		temp.s.push_back(it->first);
		if(mp.size()==1){
			temp.code.push_back("0");
		}else{
			temp.code.push_back("");
		}
		temp.sum = it->second;
		q.push(temp);
	}
	while( q.size() > 1 ){
		Node temp = q.top();
		q.pop();
		Node t;
		t.s.clear();
		t.code.clear();
		for( int i = 0; i < temp.s.size(); i++ ){
			t.s.push_back(temp.s[i]);
			t.code.push_back(temp.code[i]+"1");
		}
		t.sum = temp.sum;
		temp = q.top();
		q.pop();
		for( int i = 0; i < temp.s.size(); i++ ){
			t.s.push_back(temp.s[i]);
			t.code.push_back(temp.code[i]+"0");
		}
		t.sum += temp.sum;
		q.push(t);
	}
	Node ans = q.top();
	CString display = "";
	CString temp;
	temp.Format("%-15s\t%-15s\t%-15s\n","字符","编码","概率");
	display += temp;
	float entropy = 0;
	float aver_len = 0;
	for( int i = 0; i < ans.s.size(); i++ ){
		reverse(ans.code[i].begin(),ans.code[i].end());
		temp.Format("%-15s\t%-15s\t%-15.3f\n",ans.s[i].c_str(),ans.code[i].c_str(),(float)mp[ans.s[i]]/ans.sum);
		display += temp;
		entropy += -((float)mp[ans.s[i]]/ans.sum) * std::log((float)mp[ans.s[i]]/ans.sum) / std::log(2.0);
		aver_len += ans.code[i].size() * ((float)mp[ans.s[i]]/ans.sum);
	}
	display += "\n\n";
	temp.Format("%-10s\t\t\t%-10.3f\n","熵",entropy);
	display += temp;
	temp.Format("%-10s\t\t%-10.3f\n","平均码长",aver_len);
	display += temp;
	temp.Format("%-10s\t\t%-10.3f\n","编码效率",entropy / aver_len);
	display += temp;
	GetDlgItem(IDC_STATIC)->SetWindowTextA(display);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
