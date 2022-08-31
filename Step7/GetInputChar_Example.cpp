#include <iostream>
#include <conio.h>//	_kbhit()需要
//	_getche()	获取输入字符，并回显
//	_getch()	获取输入字符，不回显
using namespace std;
/// <summary>
/// 获取键盘输入的示例
/// </summary>
/// <returns></returns>
int main()
{
	while (true){
		if (_kbhit())//非阻塞获取用户输入
		{
			char cTake = _getch();
			switch (cTake)
			{
			case 'w':
			case 'W':
				cout << "你按下了W键!" << endl;
				break;
			case 's':
			case 'S':
				cout << "你按下了S键!" << endl;
			case 'a':
			case 'A':
				cout << "你按下了A键!" << endl;
			case 'd':
			case 'D':
				cout << "你按下了D键!" << endl;
			default:
				break;
			}
		}
	}
	return 0;
}