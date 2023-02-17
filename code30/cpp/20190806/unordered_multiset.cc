 ///
 /// @file    unordered_multiset.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-08-06 15:26:18
 ///
 
#include <math.h>
#include <iostream>
#include <unordered_set>
using std::cout;
using std::endl;
using std::unordered_multiset;

template <class Container>
void display(const Container & c)
{
	for(auto & elem : c) {
		cout << elem << " ";
	}
	cout << endl;
}

void test0()
{
	//unordered_multiset元素是无序的
	//内部不能存放关键字相同的元素
	int array[10] = {8, 7, 1, 2, 5, 9, 0, 8, 7, 3}; 
	unordered_multiset<int> numbers(array, array + 10);
	display(numbers);

	auto it = numbers.begin();
	cout << *it << endl;
	++it;//前向访问迭代器, 只能向前遍历，不能向后
	cout << *it << endl;
	//--it;//error
	
	auto it2 = numbers.find(9);
	if(it2 != numbers.end()) {
		cout << *it2 << endl;
	} else {
		cout << "查找元素失败" << endl;
	}
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

	~Point() {	cout << "~Point()" << endl;	}

	int getx() const {	return _ix;	}
	int gety() const {	return _iy;	}

	friend std::ostream & operator<<(std::ostream & os, const Point & rhs);
	friend bool operator==(const Point & lhs, const Point & rhs);
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

bool operator==(const Point & lhs, const Point & rhs)
{
	return (lhs._ix == rhs._ix  && lhs._iy == rhs._iy);
}

struct Comparator
{
	bool operator()(const Point & lhs, const Point & rhs) const
	{
		return lhs.getDistance() < rhs.getDistance();
	}
};

namespace std
{
template <>
struct hash<Point>
{
	size_t operator()(const Point & pt) const
	{
		return (pt.getx() * pt.getx() - 1) ^ 
			   (pt.gety() * pt.gety() - 1);
	}
};

}//end of namespace std


//函数对象
struct PointHasher
{
	size_t operator()(const Point & pt) const
	{
		return (pt.getx() * pt.getx() - 1) ^ 
			   (pt.gety() * pt.gety() - 1);
	}
};

struct PointEqual
{
	bool operator()(const Point & lhs, const Point & rhs) const
	{
		return lhs.getx() == rhs.getx() && 
			   lhs.gety() == rhs.gety();
	}
};

void test3()
{
	//unordered_multiset<Point> points {
	unordered_multiset<Point, PointHasher, PointEqual> points {
		Point(5, 6),
		Point(2, 3),
		Point(1, 2),
		Point(2, 2),
		Point(2, 2),
		Point(4, 3),
		Point(7, 8)
	};

	display(points);

	auto  ret = points.equal_range(Point(2, 2));
	while(ret.first != ret.second) {
		cout << *ret.first << " ";
		++ret.first;
	}
	cout << endl;
}

int main(void)
{
	//test0();
	test3();
	return 0;
}
