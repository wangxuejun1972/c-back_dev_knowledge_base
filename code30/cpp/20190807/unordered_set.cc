 ///
 /// @file    unordered_set.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-08-06 15:26:18
 ///
 
#include <math.h>
#include <iostream>
#include <unordered_set>
using std::cout;
using std::endl;
using std::unordered_set;

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
	//unordered_set元素是无序的
	//内部不能存放关键字相同的元素
	int array[10] = {8, 7, 1, 2, 5, 9, 0, 8, 7, 3}; 
	unordered_set<int> numbers(array, array + 10);
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
	//unordered_set<Point> points {
#if 0
	unordered_set<Point, PointHasher, PointEqual> points {
		Point(5, 6),
		Point(2, 3),
		Point(1, 2),
		Point(2, 2),
		Point(2, 2),
		Point(4, 3),
		Point(7, 8),
		Point(7, 9),
		Point(7, 10),
		Point(8, 10),
		Point(8, 11)
	};
#endif
	//bucket(桶，槽)的数量要是元素数量的2倍，这样可以减小rehash的次数
	unordered_set<Point, PointHasher, PointEqual> points(100);

	points.insert(Point(11, 12));
	points.insert(Point(12, 13));
	//points.insert(Point(13, 13));
	cout << points.load_factor() << endl;
	cout << points.max_load_factor() << endl;
	cout << points.size() << endl;
	cout << points.bucket_count() << endl;

	display(points);
}

int main(void)
{
	//test0();
	test3();
	return 0;
}
