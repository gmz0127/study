#include <iostream>
using namespace std;

int main()
{
	// 选择结构
	//单行选择
	if (1 < 2)(cout << "单行选择条件满足，执行该语句\n");

	// 多行
	
	if (1 < 2) {
		cout << "第一条选择条件满足，执行该语句\n";
	}
	else {
		cout << "第一条选择条件不满足，执行该语句\n";
	}
	//多条件
	if (2 > 3) {
		cout << "第一条选择条件满足，执行该语句\n";
	}
	else if(2<4){
		cout << "第二条选择条件满足，执行该语句\n";
	}
	else {
		cout << "选择条件都不满足，执行该语句\n";
	}


	// switch语句
	int a;
	cout << "请输入在1~4内a的值：";
	cin >> a;
	switch (a) {
	case 1:
		cout << "case 1\n";
		break;
	case 2:
		cout << "case 2\n";
		break;
	case 3:
		cout << "case 3\n";
		break;
	case 4:
		cout << "case 4\n";
		break;
	default:
		cout << "输入的值不在1~4内\n";
	}

	// while循环语句
	int num = 0;
	int count = 0;
	cout << "while语句打印1~10:\n";
	while (num <= 10)
	{
		cout << num << endl;
		num++;
		count++;
	}
	cout << "while语句一共执行了" << count << "次\n";

	// do while循环语句，先执行do内的语句，再去判断条件是否成立
	num = 0;
	count = 0;
	do {
		num++;
		count++;
	} while (num == 1);
	cout << "do while语句一共执行了" << count << "次\n";

	/*
	for(起始表达式；条件表达式；末尾循环体){循环主体；}
	最先运行的是起始表达式，且只运行一次，然后再去运行条件表达式，满足则进行循环主体，最后运行末尾循环体。然后再去判断条件，直到不满足条件退出循环
	*/
	// 打印1~10
	cout << "for语句打印1~10:\n";
	for (int i = 0; i <= 10; i++)
	{
		cout << i << endl;
	}

	cout << "跳转语句goto,标记为FLAG\n";

	cout << "1\n";
	cout << "2\n";
	goto FLAG;

	cout << "3\n";
	cout << "4\n";

	FLAG:
	cout << "5\n";
	cout << "6\n";

	system("pause");
	return 0;
}