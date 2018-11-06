#include <iostream>
#include <string>
#include <deque>
#include <algorithm>
#include <Windows.h>

using namespace std;
/*
ʵ�����ݣ�

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
	{	//����ִ��
		if (asktime == 0)
			state = 'E';
		else
			asktime--;
	}
	bool check() 
	{	//������״̬
		if (state == 'E')
			return true;
		else
			return false;
	}
public:
	string id;		//������
	int asktime;	//Ҫ������ʱ��
	int pri;		//������
	char state;		//����״̬��E���������R�������
};


bool isPriGreater(const process &pro1, const process &pro2)
{
	return pro1.pri > pro2.pri;
}

//����ᵼ�µ�����ʧЧ
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
	//cout << "******�����������㷨ģ��******" << endl;
	cout << "����������ϵͳ��5�����̵���Ϣ" << endl << endl;
	//����
	for (int i = 0; i < 5; i++) {
		cout << "������" << (i + 1) << "�Ž�������";
		cin >> s;
		cout << "���������Ҫ������ʱ�䣺";
		cin >> t;
		cout << "�����������������";
		cin >> p;
		pro.push_back(process(s, t, p));
		cout << endl;
	}
	//��ʼ���̶�������
	sort(pro.begin(), pro.end(), isPriGreater);
	proR = pro;
	cout << "������̶��У�" << endl;
	cout << "****************************" << endl;
	cout << "����˳��" << "\t����ID" << "\t\tʣ������ʱ��" << "\t���ȼ�" << endl;
	it = proR.begin();
	for (unsigned i = 0; i < proR.size(); i++) {
		cout << (i + 1) << "-->" << "\t\t" << it->id << "\t\t"
			<< it->asktime << "\t\t" << it->pri << endl;
		it++;
	}
	cout << "**********************" << endl;

	//���������в�Ϊ��ʱ
	while (!proR.empty()) 
	{
		//���ж��׽���
		runFir(proR);
		//������ָ����׽���
		it = proR.begin();
		cout << "�������г���";
		cout << "\t\t����";
		cout << it->id << endl;
		cout << "������......." << endl;
		Sleep( 1000);
		//�ô����н���
		//�����׽���Ҫ������ʱ���Ƿ�Ϊ0
		checkIter(proR.begin(), proR);
		//������������
		sort(proR.begin(), proR.end(), isPriGreater);
		//��ӡ��������
		cout << "��" << num + 1 << "�����н�����������У�" << endl;
		num++;
		cout << "****************************" << endl;
		cout << "����˳��" << "\t����ID" << "\t\tʣ������ʱ��" << "\t���ȼ�" << endl;
		it = proR.begin();
		for (unsigned i = 0; i < proR.size(); i++) {
			cout << (i + 1) << "-->" << "\t\t" << it->id << "\t\t"
				<< it->asktime << "\t\t" << it->pri << endl;
			it++;
		}
		cout << "**********************" << endl;
	}
	cout << "��������Ϊ�գ�����..." << endl;

	return 0;
}