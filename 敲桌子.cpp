#include <iostream>
using namespace std;

// 0~100内含有7或者7的倍数时打印敲桌子，其他数字打印
int main_3()
{
	for (int i = 0; i <= 100; i++)
	{
		if (i != 100 && i != 0)
		{
			if (i % 10 == 7 || i / 10 == 7 || i % 7 == 0)
			{
				cout << "敲桌子\n";
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