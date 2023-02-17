 ///
 /// @file    Student.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-07-25 10:53:24
 ///
 
#include <stdlib.h>
#include <string.h>

#include <iostream>
using std::cout;
using std::endl;


class Student
{
public:
	Student(int id, const char * name)
	: _id(id)
	, _name(new char[strlen(name) + 1]())
	{
		cout << "Student(int,const char*)" << endl;
		strcpy(_name, name);
	}

	void destroy()
	{
		//this->~Student();
		if(this)
			delete this;
	}

	void * operator new(size_t sz)
	{
		cout << "void * operator new(size_t)" << endl;
		void * ret = malloc(sz);
		return ret;
	}
	
	void operator delete(void * p)
	{
		cout << "void operator delete(void *)" << endl;
		free(p);
	}

private:
	~Student()
	{
		cout << "~Student()" << endl;
		if(_name) {
			delete [] _name;
			_name = nullptr;
		}
	}


public:
	void print() const
	{
		cout << "id: " << _id << endl
			 << "name:" << _name << endl;
	}

private:
	int _id;
	char * _name;
};

//需求: 一个类只能创建出堆对象, 不能创建栈对象
//解决方案: 只需要将析构函数放在私有区域
 
int main(void)
{
	//Student s1(101, "Rose");//error
	//s1.print();

	Student * pstu = new Student(100, "Jackie");
	pstu->print();

	//delete pstu;//error
	pstu->destroy();
 
	return 0;
}
