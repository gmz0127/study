#include <iostream>
using namespace std;

// 0~100�ں���7����7�ı���ʱ��ӡ�����ӣ��������ִ�ӡ
int main_3()
{
	for (int i = 0; i <= 100; i++)
	{
		if (i != 100 && i != 0)
		{
			if (i % 10 == 7 || i / 10 == 7 || i % 7 == 0)
			{
				cout << "������\n";
			}
			else {
				cout << i << endl;
			}
		}
		else {
			cout << i << endl;
		}
	}
	system("pause");
	return 0;
}