#include <iostream>
using namespace std;

int main_2()
{
	int num = 100;
	int three, medi, low;
	do {
		three = num / 100;
		medi = (num / 10) % 10;
		low = num % 10;
		if (pow(three, 3) + pow(medi, 3) + pow(low, 3) == num) (cout << num << endl);
		num++;

	} while (num <= 999);

	system("pause");
	return 0;

}