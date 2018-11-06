#include <iostream>
using namespace std;

#define MAXPROCESS 25	//最大进程数
#define MAXRESOURCE 25	//最大资源种类

int Max[MAXPROCESS][MAXRESOURCE];			//最大需求矩阵
int Allocation[MAXPROCESS][MAXRESOURCE];	//分配矩阵
int Need[MAXPROCESS][MAXRESOURCE];			//最大需求矩阵
int Available[MAXPROCESS];					//可利用资源向量
int Request[MAXPROCESS][MAXRESOURCE];		//请求矩阵
bool Finish[MAXPROCESS];					//表示系统是否有足够资源分配给某进程使其运行完成
int Sequence[MAXPROCESS];					//安全序列


bool Safe(int m, int n);
void printTable(int m, int n);

int main(void)
{
	int m;//m个进程
	int n;//n个资源
	int i, j;
	int curp;//正在申请资源的进程号
	bool sign;
	char judge;
	cout << "请输入进程的数目：";
	cin >> m;
	cout << "请输入资源的种类：";
	cin >> n;
	cout << "请输入最大需求矩阵Max：" << endl;
	for (i = 0; i < m; i++)
		for (j = 0; j < n; j++)
			cin >> Max[i][j];
	cout << "请输入已分配矩阵Allocation：" << endl;
	for (i = 0; i<m; i++)
		for (j = 0; j < n; j++) {
			cin >> Allocation[i][j];
			Need[i][j] = Max[i][j] - Allocation[i][j];//这个need矩阵要显示出来，并且最好整个资源表显示出来
			if (Need[i][j] < 0) {
				cout << "第" << i + 1 << "号进程已分配的第" << j + 1 << "种资源数目错误，请重新输入该行：" << endl;
				j--;
				continue;
			}
		}
	cout << "请输入可利用资源向量Available：" << endl;
	for (i = 0; i < n; i++)
		cin >> Available[i];
	cout << "现在资源分配表如下：" << endl;
	printTable(m, n);
	while (true) {
		sign = true;
		cout << "请输入要申请资源的进程号：";
		cin >> curp;
		curp--;
		cout << "请输入该进程所需各类资源的数目的请求向量：" << endl;
		for (j = 0; j < n; j++)
			cin >> Request[curp][j];
		//检查

		for (j = 0; j < n; j++) {
			if (Request[curp][j] > Need[curp][j]) {
				cout << "该进程所需资源数目超过它所宣布的最大值，请重新输入！" << endl;;
				sign = false;
				break;
			}
			if (Request[curp][j] > Available[j]) {
				cout << "系统中无足够资源满足该进程的申请" << endl;
				sign = false;
				break;
			}
		}
		if (sign == false)
			continue;
		//若检查没问题，尝试把该进程申请的资源分配给它
		cout << "尝试把该进程申请的资源分配给它..." << endl;
		for (j = 0; j < n; j++) {
			Available[j] -= Request[curp][j];
			Allocation[curp][j] += Request[curp][j];
			Need[curp][j] -= Request[curp][j];
		}
		//执行安全性算法
		cout << "执行安全性算法..." << endl;
		if (Safe(m, n)) {
			cout << "正式将资源分配给该进程，此次分配完成" << endl;
			cout << "现在资源分配表如下：" << endl;
			printTable(m, n);
		}
		else {
			cout << "该分配作废，恢复原来的资源分配状态" << endl;
			for (j = 0; j < n; j++) {
				Available[j] += Request[curp][j];
				Allocation[curp][j] -= Request[curp][j];
				Need[curp][j] += Request[curp][j];
			}
			cout << "现在资源分配表如下：" << endl;
			printTable(m, n);
		}
		cout << "再次请求分配请输入Y/y，退出请输入Q/q：" << endl;
		cin >> judge;
		if (judge == 'Y' || judge == 'y')
			continue;
		else
			break;
	}
	return 0;
}

bool Safe(int m, int n) {
	int i, j;
	int seq = 0;
	int Work[MAXRESOURCE];
	for (i = 0; i < n; i++)
		Work[i] = Available[i];
	for (i = 0; i < m; i++)
		Finish[i] = false;
	for (i = 0; i < m; i++)
	{
		if (Finish[i] == true)
			continue;
		else {
			for (j = 0; j < n; j++) {
				if (Need[i][j] > Work[j])
					break;
			}
			if (j == n) {
				Finish[i] = true;
				for (int k = 0; k < n; k++)
					Work[k] += Allocation[i][k];
				Sequence[seq] = i;
				seq++;
				i = -1;
			}
			else {
				continue;
			}
			if (seq == m) {
				cout << "安全序列为：" << endl;
				for (i = 0; i < (seq - 1); i++) {
					cout << "P" << Sequence[i] + 1;
					cout << "-->";
				}
				cout << "P" << Sequence[i] + 1 << endl;
				return true;
			}
		}
	}
	cout << "不安全" << endl;
	return false;
}

void printTable(int m, int n)
{
	cout << "最大需求矩阵Max：" << endl;
	cout << "****************************" << endl;
	cout << "*";
	for (int j = 0; j < n; j++)
		cout << "\tR" << j + 1;
	cout << " *";
	cout << endl;
	for (int i = 0; i < m; i++) {
		cout << "* P" << i + 1;
		for (int j = 0; j < n; j++)
			cout << "\t" << Max[i][j];
		cout << "  *" << endl;
	}
	cout << "****************************" << endl;

	cout << "分配矩阵Allocation：" << endl;
	cout << "****************************" << endl;
	cout << "*";
	for (int j = 0; j < n; j++)
		cout << "\tR" << j + 1;
	cout << " *";
	cout << endl;
	for (int i = 0; i < m; i++) {
		cout << "* P" << i + 1;
		for (int j = 0; j < n; j++)
			cout << "\t" << Allocation[i][j];
		cout << "  *" << endl;
	}
	cout << "****************************" << endl;

	cout << "需求矩阵Need：" << endl;
	cout << "****************************" << endl;
	cout << "*";
	for (int j = 0; j < n; j++)
		cout << "\tR" << j + 1;
	cout << " *";
	cout << endl;
	for (int i = 0; i < m; i++) {
		cout << "* P" << i + 1;
		for (int j = 0; j < n; j++)
			cout << "\t" << Need[i][j];
		cout << "  *" << endl;
	}
	cout << "****************************" << endl;

	cout << "可利用资源向量Available：" << endl;
	cout << "****************************" << endl;
	cout << "*";
	for (int j = 0; j < n; j++)
		cout << "\tR" << j + 1;
	cout << " *";
	cout << endl;
	for (int i = 0; i < 1; i++) {
		cout << "*";
		for (int j = 0; j < n; j++)
			cout << "\t" << Available[j];
		cout << "  *" << endl;
	}
	cout << "****************************" << endl;

}

