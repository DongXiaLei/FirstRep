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
			cout << "分配到的第" << k + 1 << "块磁盘空间为：" << endl;
			cout << "柱面号：" << addr[k].pillar << "\t";
			cout << "磁道号：" << addr[k].track << "\t";
			cout << "物理记录号：" << addr[k].record << "\t";
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
			cout << "归还的第" << k + 1 << "块磁盘空间为：" << endl;
			cout << "字节号" << i << "\t";
			cout << "位数" << j << "\t";
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
	cout << "位示图如下：" << endl;
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
	//显示位示图
	cout << "初始位示图如下：" << endl;
	printMap(ROW, COL);
	cout << "请输入对应字母选择功能：" << endl;
	cout << "空间申请（A/a)  空间释放（R/r）  退出（Q/q）" << endl;
	while (cin >> sign) {
		switch (sign) {
		case 'A':
		case 'a':
			do {
				cout << "请输入作业号：";
				cin >> tId;
				for (iter = pro.begin(); iter != pro.end(); iter++) {
					if (tId == iter->id) {
						cout << "您输入的作业号已存在，请重新输入！" << endl;
						continue;
					}
				}
			} while (false);
			cout << "请输入作业需要的内存大小（kb）：";
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
				cout << "内存分配失败！" << endl;
				break;
			}
			printMap(ROW, COL);
			//显示位示图
			break;
		case 'R':
		case 'r':
			do {
				cout << "请输入要回收作业号：";
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
					cout << "您输入的作业号不存在，请重新输入！" << endl;
			} while (true);
			judge = false;
			iter->restore();
			//pro.erase(iter);

			//显示位示图
			printMap(ROW, COL);
			break;
		case 'Q':
		case 'q':
			return 0;
		}
		cout << "请输入对应字母选择功能：" << endl;
		cout << "空间申请（A/a)  空间释放（R/r）  退出（Q/q）" << endl;
	}
}