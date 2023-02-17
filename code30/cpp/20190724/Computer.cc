 ///
 /// @file    Computer.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-07-23 11:44:54
 ///
 
#include <string.h>
#include <iostream>
using std::cout;
using std::endl;

class Computer
{
public:
	Computer(const char * brand, double price)
	: _brand(new char[strlen(brand)+ 1]())
	, _price(price)
	{
		strcpy(_brand, brand);
		cout << "Computer(const char*, float)" << endl;
		_totalPrice += _price;
	}

	Computer(const Computer & rhs)
	: _brand(new char[strlen(rhs._brand) + 1]()) //深拷贝
	, _price(rhs._price)
	{
		cout << "Computer(const Computer &)" << endl;
		strcpy(_brand, rhs._brand);
	}

	Computer & operator=(const Computer & rhs)
	{
		if(this != &rhs) {//自复制
			cout << "Computer & operator=(const Computer &)" << endl;
			delete [] _brand;//回收左操作申请的空间

			//再进行深拷贝
			_brand = new char[strlen(rhs._brand) + 1]();
			strcpy(_brand, rhs._brand);
			_price = rhs._price;
		}
		return *this;
	}

	void print();

	//静态成员函数, 没有隐含的this指针
	//
	//不能直接访问非静态的数据成员和成员函数
	//
	//只能访问静态数据成员和静态成员函数
	//
	static void printTotalPrice()
	{
		//cout << "brand:" << _brand << endl; //error
		//this->print();//error
		cout << "totalprice:" << _totalPrice << endl;
	}


	~Computer()
	{
		if(_brand)
			delete [] _brand;
		cout << "~Computer()" << endl;
	}

private:
	char * _brand;
	double _price;
	static double _totalPrice;//位于全局静态区
	//被类的所有对象共享
};

//静态数据成员的初始化，必须要放在类之外进行
double Computer::_totalPrice = 0.0;

inline void Computer::print()
{
	cout << "brand:" << _brand << endl
		 << "price:" << _price << endl;
}

int test0(void)
{
	//自定义类类型
	cout << "sizeof(Computer) = " << sizeof(Computer) << endl;
	Computer pc("Thinkpad", 8888);
	cout <<  "pc = ";
	pc.print();
	//pc.printTotalPrice();
	Computer::printTotalPrice();//静态成员函数可以直接用类名调用
	cout << endl;

	Computer pc2("Xiaomi", 7500);
	pc2.print();
	//pc2.printTotalPrice();
	Computer::printTotalPrice();//静态成员函数可以直接用类名调用
	return 0;
}

int main(void)
{
	test0();

	return 0;
}
