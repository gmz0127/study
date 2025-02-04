#include <iostream>
#include <string>
using namespace std;

// 宏变量
#define hong_var 100


int main_0()
{

	cout << "hello world" << endl;

	// 单行注释

	/*
		多行注释
	*/

	// 变量（给内存空间的命名，方便管理内存）：变量类型 变量名 = 变量初始值;
	int a = 10;
	cout << "a = " << a << endl;

	// 常量
	const int const_var = 20;
	cout << "const_var = " << const_var << endl;
	cout << "宏变量hong_var = " << hong_var << endl;

	// sizeof关键字
	cout << "int大小：" << sizeof(int) << endl;

	// 浮点型
	float f1 = 3.14f;
	double d1 = 3.14;

	// 字符型（只能使用单引号）
	// 字符型变量并不是吧字符存在内存里，而是把对应的ASCII存在内存中
	char ch = 'a';
	// 字符变量对应的ASCII值
	cout << ch <<"对应的ASCII："<< (int)ch << endl;


	//转义字符
	cout << "换行\n";
	//制表符：下一个单词对其，整齐输出数据
	cout << "TAB\t" << endl;
	cout << "\\" << endl;

	//字符串型
	//c语言风格  char 变量名[] = "字符串"		要用双引号括起来
	char c_str[] = "c_string";
	cout << "c风格" << c_str << endl;
	//C++风格   string 变量名 = "字符串"
	// 要包含头文件string
	string cpp_str = "cpp_string";
	cout << cpp_str << endl;

	//布尔类型 占一个字节
	bool bool_num = true;
	cout << bool_num << endl;	// 1


	//数据的输入输出
	//输入 cin >> 变量名		输出 cout << ...;	endl表示换行
	int num;
	cout << "请给num赋值：";
	cin >> num;
	


	// 算数运算符
	cout <<"整除10 / 3 =" << 10 / 3 << endl;
	// 注意：两个小数无法做取模运算
	cout << "取模（取余）10 % 3 = "<< 10 % 3 << endl;

	int g,m;
	g = 2;
	m = 2;
	cout << "g = 2\t++g = " << ++g <<"\tg = " << g <<endl;
	cout << "m = 2\tm++ = " << m++ << "\tm = "<<m<< endl;
	// 前置递增：先进行++运算再对变量赋值，后置递增，先赋值再对其++


	// 赋值运算符
	// a *= 2  相当于 a = a*2 其他一样   a %= 3  相当于 a = a% 3
	cout << "g *= 2 ,g = " << (g *= 2) <<endl;

	// 逻辑运算符
	cout << "1 && 0 = " << (1 && 0) << endl;
	cout << "1 || 0 = " << (1 || 0) << endl;
	cout << "!1 = " << !1 << endl;

	// 三目运算符 
	/*
		表达式1 ？ 表达式2 ： 表达式3
		表达式1为真，则执行表达式2并返回表达式2的结果
		表达式1为加，则执行表达式3并返回表达式3的结果
	*/
	int three;
	three = (1 < 3) ? 4 : 5;
	cout << "three = (1 < 3) ? 4 : 5;则three = " << three << endl;
	// 三目运算中返回的是变量
	int q= 1, e = 2;
	(q < e ? q : e) = 100;
	cout << "q = " << q << "\te = " << e << endl;



	system("pause");
	
	return 0;
}