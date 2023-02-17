 ///
 /// @file    set.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-08-06 10:10:31
 ///

#include <math.h>

#include <iostream>
#include <set>
#include <string>
using std::cout;
using std::endl;
using std::set;
using std::string;

template <class Container>
void display(const Container & c)
{
	//typename Container::value_type;

	typename Container::const_iterator cit = c.begin();
	while(cit != c.end()) {
		cout << *cit << " ";
		++cit;
	}
	cout << endl;
}

void test0()
{
	set<int> numbers;
	cout << "numbers' size = " << numbers.size() << endl;

	numbers.insert(1);
	numbers.insert(2);
	numbers.insert(3);
	display(numbers);
}

void test1()
{

	//set默认情况下是按照升序方式进行排列
	//set中不能存放关键字相同的元素
	//
	//相关数据结构: 跳表（skip-list）
	//
	//底层实现: 采用红黑树(rb-tree) ==> 近似平衡二叉树(AVL)
	//			==> 查找一个元素的时间复杂度为O(logN) ==> 二分查找
	//
	//特点:
	//	1. 节点不是红色就是黑色
	//	2. 根节点是黑色的
	//	3. 叶子节点都是黑色的
	//	4. 不能有连续的两个节点是红色的
	//	5. 从根节点到任意一个节点路径上的黑色节点数目是相同的
	//
	int arr[10] = {3, 6, 1, 2, 6, 5, 7, 9, 8, 3};
	set<int> numbers(arr, arr + 10);
	display(numbers);

	//set不支持下标访问运算符
	//numbers[0];//error
	set<int>::iterator it = numbers.begin();
	cout << "*it = " << *it << endl;
	//*it = 10;//放入set中的元素无法进行修改，都是只读的
	numbers.erase(it);//可以删除
	display(numbers);

	//添加元素:
	std::pair<set<int>::iterator, bool> ret = numbers.insert(2);
	if(ret.second) {
		cout << "添加元素成功!" << endl;
		cout << *ret.first << endl;
	} else {
		cout << "set中已有相同元素,添加失败" << endl;
		cout << *ret.first << endl;
	}

	//set容器可以用来进行去重
	

	//查找元素:
	if(numbers.count(2)) {
		cout << "查找元素成功！" << endl;
	} else {
		cout << "set没有该元素" << endl;
	}

	auto it2 = numbers.find(3);
	if(it2 == numbers.end()) {
		cout << "set没有该元素" << endl;
	} else {
		cout << "查找元素成功！" << endl;
		cout << "*it2 = " << *it2 << endl;
	}
}

void test2()
{
	std::pair<int, string> p(1, "深圳");
	cout << p.first << " --> " << p.second << endl;
}

class Point
{
public:
	Point(int ix, int iy)
	: _ix(ix)
	, _iy(iy)
	{	cout << "Point(int,int)" << endl;}

	double getDistance() const
	{
		return sqrt(_ix * _ix + _iy * _iy);
	}

	friend std::ostream & operator<<(std::ostream & os, const Point & rhs);
private:
	int _ix;
	int _iy;
};


std::ostream & operator<<(std::ostream & os, const Point & rhs)
{
	os << "(" << rhs._ix
	   << "," << rhs._iy
	   << ")";
	return os;
}

bool operator<(const Point & lhs, const Point & rhs)
{
	return lhs.getDistance() < rhs.getDistance();
}

bool operator>(const Point & lhs, const Point & rhs)
{
	return lhs.getDistance() > rhs.getDistance();
}
struct Comparator
{
	bool operator()(const Point & lhs, const Point & rhs) const
	{
		return lhs.getDistance() < rhs.getDistance();
	}
};


void test3()
{

	set<Point, std::greater<Point>> numbers{
	//set<Point, Comparator> numbers{
		Point(1, 2),
		Point(2, 5),
		Point(-2, 10),
		Point(2, 2),
		Point(2, 2),
		Point(3, 2),
	};
	display(numbers);

	set<Point>::iterator it = numbers.begin();
	cout << "*it = " << *it << endl;
	//numbers.erase(it);//可以删除
	display(numbers);

	//添加元素:
	auto ret = numbers.insert(Point(11, 12));
	if(ret.second) {
		cout << "添加元素成功!" << endl;
		cout << *ret.first << endl;
	} else {
		cout << "set中已有相同元素,添加失败" << endl;
		cout << *ret.first << endl;
	}

	//set容器可以用来进行去重
	

#if 1
	//查找元素:
	if(numbers.count(Point(11, 12))) {
		cout << "查找元素成功！" << endl;
	} else {
		cout << "set没有该元素" << endl;
	}

	auto it2 = numbers.find(Point(11, 12));
	if(it2 == numbers.end()) {
		cout << "set没有该元素" << endl;
	} else {
		cout << "查找元素成功！" << endl;
		cout << "*it2 = " << *it2 << endl;
	}
#endif

}
 
int main(void)
{
	//test0();
	//test1();
	//test2();
	test3();

	return 0;
}
