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
	int size;	//������С
	int address;//������ʼ��ַ
	bool state;	//1Ϊ�ѷ��䣬0Ϊδ����
	int jobId;	//������Ӧ����ҵ��
};

void printMem(deque<area> &m) 
{
	cout << "��ǰ�ڴ����������£�" << endl;
	cout << "*************************************************************************" << endl;
	cout << "* ��ҵ��\t" << "�ռ��С��kb��\t" << "����״̬\t" << "��ʼ��ַ��kb��\t*" << endl;
	for (auto it = m.begin(); it != m.end(); ++it) {
		cout << "* " << it->jobId << "\t\t" << it->size << "\t\t" << (it->state ? "�ѷ���" : "δ����") << "\t\t" << it->address << "\t\t*" << endl;
	}
	cout << "*************************************************************************" << endl;
}

int main(void)
{
	int cirnum = 0;
	char sign;//��������
	bool judge = false;//�ж��ڴ��Ƿ����ɹ�
	bool judge2 = false;//�ж�Ҫɾ���������Ƿ����
	deque<area> mem;
	deque<area>::iterator iter;//��ǰ������	
	deque<area>::iterator fiter;//ָ��ǰ��������ǰһ���ĵ�����
	deque<area>::iterator biter;//ָ��ǰ�������ĺ�һ���ĵ�����
	int jobId;
	int size;
	mem.push_back(area(MEMRYSIZE, 0, false, -1));//����ֵ
	printMem(mem);
	cout << "�������Ӧ��ĸѡ���ܣ�" << endl;
	cout << "�ռ����루A/a)  �ռ��ͷţ�R/r��  �˳���Q/q��" << endl;
	while (true) {
		while (cin >> sign) 
		{
			switch (sign) 
			{
			case 'A':
			case 'a':
				do 
				{
					cout << "��������ҵ�ţ��磺0��1��2.........����";

					while (cin >> jobId) 
					{
						if (jobId >= 0)
							break;
						else 
						{
							cout << "����������������룺" << endl;
							cout << "��������ҵ�ţ��磺0��1��2.........����";
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
						cout << "���������ҵ���Ѵ��ڣ����������룡" << endl;
						cin.clear();
						cin.ignore(1024, '\n');
						continue;
					}
				} while (true);
				cout << "��������ҵ��Ҫ���ڴ��С��kb����";
				cin >> size;
				while (size <= 0) 
				{
					cout << "����������������룺" << endl;
					cout << "��������ҵ��Ҫ���ڴ��С��kb����";
					cin >> size;
				}
				iter = mem.begin();
				while (iter != mem.end()) 
				{
					if (iter->size > size&&iter->state == false)//���ҵ��ĵ�һ������������Ҫ�ڴ�
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
					else if (iter->size == size&&iter->state == false)//�����
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
					cout << "�ڴ����ʧ�ܣ�" << endl;
				judge = false;
				cirnum = 0;
				cout << "�������Ӧ��ĸѡ���ܣ�" << endl;
				cout << "�ռ����루A/a)  �ռ��ͷţ�R/r��  �˳���Q/q��" << endl;
				break;
			case 'R':
			case 'r':
				do {
					cout << "������Ҫ������ҵ�ţ�";
					while (cin >> jobId)
					{
						if (jobId >= 0)
							break;
						else 
						{
							cout << "����������������룺" << endl;
							cout << "��������ҵ�ţ��磺0��1��2.........����";
						}
					}
					for (iter = mem.begin(); iter != mem.end(); iter++) 
					{
						if (jobId == iter->jobId) 
						{
							judge2 = true;//�ж�Ҫɾ���������Ƿ����
						}
					}
					if (judge2 == true)
						break;
					else {
						cout << "���������ҵ�Ų����ڣ����������룡" << endl;
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
					cout << "�ڴ����ʧ�ܣ�" << endl;
				judge = false;
				cirnum = 0;
				cout << "�������Ӧ��ĸѡ���ܣ�" << endl;
				cout << "�ռ����루A/a)  �ռ��ͷţ�R/r��  �˳���Q/q��" << endl;
				break;
			case 'Q':
			case 'q':
				return 0;
			default:
				cirnum++;
				if (cirnum == 1) {
					cout << "���벻�Ϸ���������ѡ��" << endl;
					cout << "�ռ����루A/a)  �ռ��ͷţ�R/r��  �˳���Q/q��" << endl;
				}
				else
					break;
				
			}


		}
		return 0;
	}
}