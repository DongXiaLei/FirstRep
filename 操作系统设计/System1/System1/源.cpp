#include <iostream>
#include <string>
#include <deque>
#include <algorithm>
#include <Windows.h>

using namespace std;
/*
实验数据：

AAA 5 5
BBB 4 4
CCC 3 3
DDD 2 2
EEE 1 1

*/
class process 
{
public:
	process() {}
	process(string s, int t, int p) :id(s), asktime(t), pri(p) {}
	void run() 
	{	//进程执行
		if (asktime == 0)
			state = 'E';
		else
			asktime--;
	}
	bool check() 
	{	//检查进程状态
		if (state == 'E')
			return true;
		else
			return false;
	}
public:
	string id;		//进程名
	int asktime;	//要求运行时间
	int pri;		//优先数
	char state;		//两种状态：E代表结束，R代表就绪
};


bool isPriGreater(const process &pro1, const process &pro2)
{
	return pro1.pri > pro2.pri;
}

//这个会导致迭代器失效
void checkIter(deque<process>::iterator &it, deque<process> &pro) 
{
	if (it->asktime != 0) 
	{
		;
	}
	else 
	{
		it->state = 'E';
		pro.erase(it);
	}
}

void runFir(deque<process> &p)
{
	auto it = p.begin();
	it->pri--;
	it->asktime--;
}

int main(void)
{
	deque<process> pro;
	deque<process> proR;
	deque<process>::iterator it;
	string s;
	int t;
	int p;
	int num = 0;
	//cout << "******处理器调度算法模拟******" << endl;
	cout << "请依次输入系统中5个进程的信息" << endl << endl;
	//输入
	for (int i = 0; i < 5; i++) {
		cout << "请输入" << (i + 1) << "号进程名：";
		cin >> s;
		cout << "请输入进程要求运行时间：";
		cin >> t;
		cout << "请输入进程优先数：";
		cin >> p;
		pro.push_back(process(s, t, p));
		cout << endl;
	}
	//初始进程队列排序
	sort(pro.begin(), pro.end(), isPriGreater);
	proR = pro;
	cout << "输入进程队列：" << endl;
	cout << "****************************" << endl;
	cout << "排列顺序" << "\t进程ID" << "\t\t剩余运行时间" << "\t优先级" << endl;
	it = proR.begin();
	for (unsigned i = 0; i < proR.size(); i++) {
		cout << (i + 1) << "-->" << "\t\t" << it->id << "\t\t"
			<< it->asktime << "\t\t" << it->pri << endl;
		it++;
	}
	cout << "**********************" << endl;

	//当就绪队列不为空时
	while (!proR.empty()) 
	{
		//运行队首进程
		runFir(proR);
		//迭代器指向队首进程
		it = proR.begin();
		cout << "正在运行程序：";
		cout << "\t\t进程";
		cout << it->id << endl;
		cout << "运行中......." << endl;
		Sleep( 1000);
		//该次运行结束
		//检查队首进程要求运行时间是否为0
		checkIter(proR.begin(), proR);
		//就绪队列排序
		sort(proR.begin(), proR.end(), isPriGreater);
		//打印就绪队列
		cout << "第" << num + 1 << "次运行结束后就绪队列：" << endl;
		num++;
		cout << "****************************" << endl;
		cout << "排列顺序" << "\t进程ID" << "\t\t剩余运行时间" << "\t优先级" << endl;
		it = proR.begin();
		for (unsigned i = 0; i < proR.size(); i++) {
			cout << (i + 1) << "-->" << "\t\t" << it->id << "\t\t"
				<< it->asktime << "\t\t" << it->pri << endl;
			it++;
		}
		cout << "**********************" << endl;
	}
	cout << "就绪队列为空，结束..." << endl;

	return 0;
}