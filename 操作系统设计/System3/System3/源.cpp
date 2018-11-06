#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <deque>

using namespace std;

#define MAX 64
#define ROW 8
#define COL 8
#define RECORDPERTRACK 4

int bitmap[ROW][COL];

struct phyA {
	int pillar;
	int track;
	int record;
};
typedef struct phyA phyAddr;
class task {
public:
	task() {}
	task(int a, int b) :id(a), size(b) {}
	bool request() {
		int k = size;
		for (int i = 0; i < ROW; i++) {
			for (int j = 0; j < COL; j++) {
				if (bitmap[i][j] == 0) {
					bitmap[i][j] = 1;
					k--;
					addr[size - k - 1].pillar = i;
					addr[size - k - 1].track = j / RECORDPERTRACK;
					addr[size - k - 1].record = j%RECORDPERTRACK;
					if (k == 0)
						return true;
				}
			}
		}
	}
	bool printAdd() {

		for (int k = 0; k < size; k++) {
			cout << "���䵽�ĵ�" << k + 1 << "����̿ռ�Ϊ��" << endl;
			cout << "����ţ�" << addr[k].pillar << "\t";
			cout << "�ŵ��ţ�" << addr[k].track << "\t";
			cout << "�����¼�ţ�" << addr[k].record << "\t";
			cout << endl;
		}
		return true;
	}
	void restore() {
		int i, j;
		for (int k = 0; k < size; k++) {
			i = addr[k].pillar;
			j = addr[k].track*RECORDPERTRACK + addr[k].record;
			bitmap[i][j] = 0;
			cout << "�黹�ĵ�" << k + 1 << "����̿ռ�Ϊ��" << endl;
			cout << "�ֽں�" << i << "\t";
			cout << "λ��" << j << "\t";
			cout << endl;
		}

	}
public:
	int id;
	int size;
	phyAddr addr[MAX];
};
int getFreeBlock() {
	int free = 0;
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			if (bitmap[i][j] == 0)
				free++;
		}
	}
	return free;
}
void printMap(int r, int c) {
	cout << "λʾͼ���£�" << endl;
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			cout << bitmap[i][j] << "\t";
		}
		cout << endl;
	}

}

int main(void)
{
	int freeBlock;
	char sign;
	int tId;
	int size;
	bool judge = false;
	deque<task> pro;
	deque<task>::iterator iter;
	//��ʾλʾͼ
	cout << "��ʼλʾͼ���£�" << endl;
	printMap(ROW, COL);
	cout << "�������Ӧ��ĸѡ���ܣ�" << endl;
	cout << "�ռ����루A/a)  �ռ��ͷţ�R/r��  �˳���Q/q��" << endl;
	while (cin >> sign) {
		switch (sign) {
		case 'A':
		case 'a':
			do {
				cout << "��������ҵ�ţ�";
				cin >> tId;
				for (iter = pro.begin(); iter != pro.end(); iter++) {
					if (tId == iter->id) {
						cout << "���������ҵ���Ѵ��ڣ����������룡" << endl;
						continue;
					}
				}
			} while (false);
			cout << "��������ҵ��Ҫ���ڴ��С��kb����";
			cin >> size;
			freeBlock = getFreeBlock();
			if (size <= freeBlock) {
				pro.push_back(task(tId, size));
				iter = pro.end();
				iter--;
				iter->request();
				iter->printAdd();
			}
			else {
				cout << "�ڴ����ʧ�ܣ�" << endl;
				break;
			}
			printMap(ROW, COL);
			//��ʾλʾͼ
			break;
		case 'R':
		case 'r':
			do {
				cout << "������Ҫ������ҵ�ţ�";
				cin >> tId;
				for (iter = pro.begin(); iter != pro.end(); iter++) {
					if (tId == iter->id) {
						judge = true;
						break;
					}
				}
				if (judge == true) {
					break;
				}
				else
					cout << "���������ҵ�Ų����ڣ����������룡" << endl;
			} while (true);
			judge = false;
			iter->restore();
			//pro.erase(iter);

			//��ʾλʾͼ
			printMap(ROW, COL);
			break;
		case 'Q':
		case 'q':
			return 0;
		}
		cout << "�������Ӧ��ĸѡ���ܣ�" << endl;
		cout << "�ռ����루A/a)  �ռ��ͷţ�R/r��  �˳���Q/q��" << endl;
	}
}