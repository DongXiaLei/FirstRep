#include <iostream>
#include <list>
#include <string>
#include <deque>
#define MEMRYSIZE 128
using namespace std;

class area 
{
public:
	area(int a, int b, bool c, int d) : size(a), address(b), state(c), jobId(d) {};
public:
	int size;	//分区大小
	int address;//分区起始地址
	bool state;	//1为已分配，0为未分配
	int jobId;	//分区对应的作业号
};

void printMem(deque<area> &m) 
{
	cout << "当前内存分配情况如下：" << endl;
	cout << "*************************************************************************" << endl;
	cout << "* 作业号\t" << "空间大小（kb）\t" << "工作状态\t" << "起始地址（kb）\t*" << endl;
	for (auto it = m.begin(); it != m.end(); ++it) {
		cout << "* " << it->jobId << "\t\t" << it->size << "\t\t" << (it->state ? "已分配" : "未分配") << "\t\t" << it->address << "\t\t*" << endl;
	}
	cout << "*************************************************************************" << endl;
}

int main(void)
{
	int cirnum = 0;
	char sign;//接受命令
	bool judge = false;//判断内存是否分配成功
	bool judge2 = false;//判断要删除的任务是否存在
	deque<area> mem;
	deque<area>::iterator iter;//当前迭代器	
	deque<area>::iterator fiter;//指向当前迭代器的前一个的迭代器
	deque<area>::iterator biter;//指向当前迭代器的后一个的迭代器
	int jobId;
	int size;
	mem.push_back(area(MEMRYSIZE, 0, false, -1));//赋初值
	printMem(mem);
	cout << "请输入对应字母选择功能：" << endl;
	cout << "空间申请（A/a)  空间释放（R/r）  退出（Q/q）" << endl;
	while (true) {
		while (cin >> sign) 
		{
			switch (sign) 
			{
			case 'A':
			case 'a':
				do 
				{
					cout << "请输入作业号（如：0、1、2.........）：";

					while (cin >> jobId) 
					{
						if (jobId >= 0)
							break;
						else 
						{
							cout << "输入错误，请重新输入：" << endl;
							cout << "请输入作业号（如：0、1、2.........）：";
							continue;
						}
					}

					for (iter = mem.begin(); iter != mem.end(); iter++) 
					{
						if (jobId == iter->jobId) 
						{
							break;
						}
					}
					if (iter == mem.end())
						break;
					else 
					{
						cout << "您输入的作业号已存在，请重新输入！" << endl;
						cin.clear();
						cin.ignore(1024, '\n');
						continue;
					}
				} while (true);
				cout << "请输入作业需要的内存大小（kb）：";
				cin >> size;
				while (size <= 0) 
				{
					cout << "输入错误，请重新输入：" << endl;
					cout << "请输入作业需要的内存大小（kb）：";
					cin >> size;
				}
				iter = mem.begin();
				while (iter != mem.end()) 
				{
					if (iter->size > size&&iter->state == false)//若找到的第一个分区大于需要内存
					{
						int s = iter->size - size;
						int a = iter->address + size;
						iter->jobId = jobId;
						iter->size = size;
						iter->state = true;
						iter++;
						mem.insert(iter, area(s, a, false, -1));
						judge = true;
						break;
					}
					else if (iter->size == size&&iter->state == false)//若相等
					{
						iter->jobId = jobId;
						iter->state = true;
						judge = true;
						break;
					}
					else
						iter++;
				}
				if (judge == true)
					printMem(mem);
				else
					cout << "内存分配失败！" << endl;
				judge = false;
				cirnum = 0;
				cout << "请输入对应字母选择功能：" << endl;
				cout << "空间申请（A/a)  空间释放（R/r）  退出（Q/q）" << endl;
				break;
			case 'R':
			case 'r':
				do {
					cout << "请输入要回收作业号：";
					while (cin >> jobId)
					{
						if (jobId >= 0)
							break;
						else 
						{
							cout << "输入错误，请重新输入：" << endl;
							cout << "请输入作业号（如：0、1、2.........）：";
						}
					}
					for (iter = mem.begin(); iter != mem.end(); iter++) 
					{
						if (jobId == iter->jobId) 
						{
							judge2 = true;//判断要删除的任务是否存在
						}
					}
					if (judge2 == true)
						break;
					else {
						cout << "您输入的作业号不存在，请重新输入！" << endl;
						continue;
					}
				} while (true);
				judge2 = false;
				iter = mem.begin();
				while (iter != mem.end()) 
				{
					if (iter->jobId == jobId) 
					{
						fiter = iter - 1;
						biter = iter + 1;
						if (iter == mem.begin()) 
						{
							if (biter->state == false) 
							{
								size = biter->size + iter->size;
								iter->size = size;
								iter->state = false;
								iter->jobId = -1;
								iter++;
								mem.erase(iter);
							}
							else
							{
								iter->state = false;
								iter->jobId = -1;
							}
							judge = true;
							break;
						}
						if (biter == mem.end())
						{
							if (fiter->state == false)
							{
								size = fiter->size + iter->size;
								fiter->size = size;
								mem.erase(iter);
							}
							else 
							{
								iter->state = false;
								iter->jobId = -1;
							}
							judge = true;
							break;
						}
						if (fiter->state == false && biter->state == false) 
						{
							size = fiter->size + iter->size + biter->size;
							fiter->size = size;
							iter = mem.erase(iter);
							mem.erase(iter);
						}
						else if (fiter->state == false) 
						{
							size = fiter->size + iter->size;
							fiter->size = size;
							mem.erase(iter);
						}
						else if (biter->state == false) 
						{
							size = biter->size + iter->size;
							iter->size = size;
							iter->state = false;
							iter->jobId = -1;
							iter++;
							mem.erase(iter);
						}
						else 
						{
							iter->state = false;
							iter->jobId = -1;
						}
						judge = true;
						break;
					}
					else 
					{
						iter++;
					}
				}
				if (judge == true)
					printMem(mem);
				else
					cout << "内存回收失败！" << endl;
				judge = false;
				cirnum = 0;
				cout << "请输入对应字母选择功能：" << endl;
				cout << "空间申请（A/a)  空间释放（R/r）  退出（Q/q）" << endl;
				break;
			case 'Q':
			case 'q':
				return 0;
			default:
				cirnum++;
				if (cirnum == 1) {
					cout << "输入不合法，请重新选择：" << endl;
					cout << "空间申请（A/a)  空间释放（R/r）  退出（Q/q）" << endl;
				}
				else
					break;
				
			}


		}
		return 0;
	}
}