#include <iostream>
#include <string>
using namespace std;

// �����
#define hong_var 100


int main_0()
{

	cout << "hello world" << endl;

	// ����ע��

	/*
		����ע��
	*/

	// ���������ڴ�ռ����������������ڴ棩���������� ������ = ������ʼֵ;
	int a = 10;
	cout << "a = " << a << endl;

	// ����
	const int const_var = 20;
	cout << "const_var = " << const_var << endl;
	cout << "�����hong_var = " << hong_var << endl;

	// sizeof�ؼ���
	cout << "int��С��" << sizeof(int) << endl;

	// ������
	float f1 = 3.14f;
	double d1 = 3.14;

	// �ַ��ͣ�ֻ��ʹ�õ����ţ�
	// �ַ��ͱ��������ǰ��ַ������ڴ�����ǰѶ�Ӧ��ASCII�����ڴ���
	char ch = 'a';
	// �ַ�������Ӧ��ASCIIֵ
	cout << ch <<"��Ӧ��ASCII��"<< (int)ch << endl;


	//ת���ַ�
	cout << "����\n";
	//�Ʊ������һ�����ʶ��䣬�����������
	cout << "TAB\t" << endl;
	cout << "\\" << endl;

	//�ַ�����
	//c���Է��  char ������[] = "�ַ���"		Ҫ��˫����������
	char c_str[] = "c_string";
	cout << "c���" << c_str << endl;
	//C++���   string ������ = "�ַ���"
	// Ҫ����ͷ�ļ�string
	string cpp_str = "cpp_string";
	cout << cpp_str << endl;

	//�������� ռһ���ֽ�
	bool bool_num = true;
	cout << bool_num << endl;	// 1


	//���ݵ��������
	//���� cin >> ������		��� cout << ...;	endl��ʾ����
	int num;
	cout << "���num��ֵ��";
	cin >> num;
	


	// ���������
	cout <<"����10 / 3 =" << 10 / 3 << endl;
	// ע�⣺����С���޷���ȡģ����
	cout << "ȡģ��ȡ�ࣩ10 % 3 = "<< 10 % 3 << endl;

	int g,m;
	g = 2;
	m = 2;
	cout << "g = 2\t++g = " << ++g <<"\tg = " << g <<endl;
	cout << "m = 2\tm++ = " << m++ << "\tm = "<<m<< endl;
	// ǰ�õ������Ƚ���++�����ٶԱ�����ֵ�����õ������ȸ�ֵ�ٶ���++


	// ��ֵ�����
	// a *= 2  �൱�� a = a*2 ����һ��   a %= 3  �൱�� a = a% 3
	cout << "g *= 2 ,g = " << (g *= 2) <<endl;

	// �߼������
	cout << "1 && 0 = " << (1 && 0) << endl;
	cout << "1 || 0 = " << (1 || 0) << endl;
	cout << "!1 = " << !1 << endl;

	// ��Ŀ����� 
	/*
		���ʽ1 �� ���ʽ2 �� ���ʽ3
		���ʽ1Ϊ�棬��ִ�б��ʽ2�����ر��ʽ2�Ľ��
		���ʽ1Ϊ�ӣ���ִ�б��ʽ3�����ر��ʽ3�Ľ��
	*/
	int three;
	three = (1 < 3) ? 4 : 5;
	cout << "three = (1 < 3) ? 4 : 5;��three = " << three << endl;
	// ��Ŀ�����з��ص��Ǳ���
	int q= 1, e = 2;
	(q < e ? q : e) = 100;
	cout << "q = " << q << "\te = " << e << endl;



	system("pause");
	
	return 0;
}