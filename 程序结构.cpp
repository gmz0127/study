#include <iostream>
using namespace std;

int main()
{
	// ѡ��ṹ
	//����ѡ��
	if (1 < 2)(cout << "����ѡ���������㣬ִ�и����\n");

	// ����
	
	if (1 < 2) {
		cout << "��һ��ѡ���������㣬ִ�и����\n";
	}
	else {
		cout << "��һ��ѡ�����������㣬ִ�и����\n";
	}
	//������
	if (2 > 3) {
		cout << "��һ��ѡ���������㣬ִ�и����\n";
	}
	else if(2<4){
		cout << "�ڶ���ѡ���������㣬ִ�и����\n";
	}
	else {
		cout << "ѡ�������������㣬ִ�и����\n";
	}


	// switch���
	int a;
	cout << "��������1~4��a��ֵ��";
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
		cout << "�����ֵ����1~4��\n";
	}

	// whileѭ�����
	int num = 0;
	int count = 0;
	cout << "while����ӡ1~10:\n";
	while (num <= 10)
	{
		cout << num << endl;
		num++;
		count++;
	}
	cout << "while���һ��ִ����" << count << "��\n";

	// do whileѭ����䣬��ִ��do�ڵ���䣬��ȥ�ж������Ƿ����
	num = 0;
	count = 0;
	do {
		num++;
		count++;
	} while (num == 1);
	cout << "do while���һ��ִ����" << count << "��\n";

	/*
	for(��ʼ���ʽ���������ʽ��ĩβѭ����){ѭ�����壻}
	�������е�����ʼ���ʽ����ֻ����һ�Σ�Ȼ����ȥ�����������ʽ�����������ѭ�����壬�������ĩβѭ���塣Ȼ����ȥ�ж�������ֱ�������������˳�ѭ��
	*/
	// ��ӡ1~10
	cout << "for����ӡ1~10:\n";
	for (int i = 0; i <= 10; i++)
	{
		cout << i << endl;
	}

	cout << "��ת���goto,���ΪFLAG\n";

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