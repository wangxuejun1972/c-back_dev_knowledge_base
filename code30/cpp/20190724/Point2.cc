 ///
 /// @file    Point.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-07-24 09:49:33
 ///
 
#include <iostream>
using std::cout;
using std::endl;

class Point
{
public:
	//对于const数据成员，只能放在初始化表达式中
	//进行初始化
	explicit
	Point(int ix = 0, int iy = 0)
	: _ix(ix)
	, _iy(iy)
	{
		cout << "Point(int, int)" << endl;
		//_ix = ix;//error
		//_iy = iy;
	}

	void print()
	{
		cout << "(" << _ix
			 << "," << _iy
			 << ")" << endl;
	}

	~Point()
	{
		cout << "~Point()" << endl;
	}

private:
	const int _ix;
	const int _iy;
};
 
int main(void)
{
	Point pt(1, 2);
	pt.~Point();//析构函数是可以显式调用
				//一般情况下不这样做
	//pt._ix = 10;//error
	
	//Point pt2 = 10;//存在隐式转换, 通过构造函数进行
	//cout << "pt2 = ";
	//pt2.print();

	return 0;
}
