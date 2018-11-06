#include <iostream>
using namespace std;

#define MAXPROCESS 25	//��������
#define MAXRESOURCE 25	//�����Դ����

int Max[MAXPROCESS][MAXRESOURCE];			//����������
int Allocation[MAXPROCESS][MAXRESOURCE];	//�������
int Need[MAXPROCESS][MAXRESOURCE];			//����������
int Available[MAXPROCESS];					//��������Դ����
int Request[MAXPROCESS][MAXRESOURCE];		//�������
bool Finish[MAXPROCESS];					//��ʾϵͳ�Ƿ����㹻��Դ�����ĳ����ʹ���������
int Sequence[MAXPROCESS];					//��ȫ����


bool Safe(int m, int n);
void printTable(int m, int n);

int main(void)
{
	int m;//m������
	int n;//n����Դ
	int i, j;
	int curp;//����������Դ�Ľ��̺�
	bool sign;
	char judge;
	cout << "��������̵���Ŀ��";
	cin >> m;
	cout << "��������Դ�����ࣺ";
	cin >> n;
	cout << "����������������Max��" << endl;
	for (i = 0; i < m; i++)
		for (j = 0; j < n; j++)
			cin >> Max[i][j];
	cout << "�������ѷ������Allocation��" << endl;
	for (i = 0; i<m; i++)
		for (j = 0; j < n; j++) {
			cin >> Allocation[i][j];
			Need[i][j] = Max[i][j] - Allocation[i][j];//���need����Ҫ��ʾ�������������������Դ����ʾ����
			if (Need[i][j] < 0) {
				cout << "��" << i + 1 << "�Ž����ѷ���ĵ�" << j + 1 << "����Դ��Ŀ����������������У�" << endl;
				j--;
				continue;
			}
		}
	cout << "�������������Դ����Available��" << endl;
	for (i = 0; i < n; i++)
		cin >> Available[i];
	cout << "������Դ��������£�" << endl;
	printTable(m, n);
	while (true) {
		sign = true;
		cout << "������Ҫ������Դ�Ľ��̺ţ�";
		cin >> curp;
		curp--;
		cout << "������ý������������Դ����Ŀ������������" << endl;
		for (j = 0; j < n; j++)
			cin >> Request[curp][j];
		//���

		for (j = 0; j < n; j++) {
			if (Request[curp][j] > Need[curp][j]) {
				cout << "�ý���������Դ��Ŀ�����������������ֵ�����������룡" << endl;;
				sign = false;
				break;
			}
			if (Request[curp][j] > Available[j]) {
				cout << "ϵͳ�����㹻��Դ����ý��̵�����" << endl;
				sign = false;
				break;
			}
		}
		if (sign == false)
			continue;
		//�����û���⣬���԰Ѹý����������Դ�������
		cout << "���԰Ѹý����������Դ�������..." << endl;
		for (j = 0; j < n; j++) {
			Available[j] -= Request[curp][j];
			Allocation[curp][j] += Request[curp][j];
			Need[curp][j] -= Request[curp][j];
		}
		//ִ�а�ȫ���㷨
		cout << "ִ�а�ȫ���㷨..." << endl;
		if (Safe(m, n)) {
			cout << "��ʽ����Դ������ý��̣��˴η������" << endl;
			cout << "������Դ��������£�" << endl;
			printTable(m, n);
		}
		else {
			cout << "�÷������ϣ��ָ�ԭ������Դ����״̬" << endl;
			for (j = 0; j < n; j++) {
				Available[j] += Request[curp][j];
				Allocation[curp][j] -= Request[curp][j];
				Need[curp][j] += Request[curp][j];
			}
			cout << "������Դ��������£�" << endl;
			printTable(m, n);
		}
		cout << "�ٴ��������������Y/y���˳�������Q/q��" << endl;
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
				cout << "��ȫ����Ϊ��" << endl;
				for (i = 0; i < (seq - 1); i++) {
					cout << "P" << Sequence[i] + 1;
					cout << "-->";
				}
				cout << "P" << Sequence[i] + 1 << endl;
				return true;
			}
		}
	}
	cout << "����ȫ" << endl;
	return false;
}

void printTable(int m, int n)
{
	cout << "����������Max��" << endl;
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

	cout << "�������Allocation��" << endl;
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

	cout << "�������Need��" << endl;
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

	cout << "��������Դ����Available��" << endl;
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

