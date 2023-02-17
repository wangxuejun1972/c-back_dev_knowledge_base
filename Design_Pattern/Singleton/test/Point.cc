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
	explicit //必须要显式调用构造函数, 禁止隐式转换
	Point(int ix = 0, int iy = 0)
	: _ix(ix)
	, _iy(iy)
	{
		cout << "Point(int, int)" << endl;
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

protected://对其派生类开放权限
		  //在类之外不能直接访问
	int _ix;

private:
	int _iy;
};
