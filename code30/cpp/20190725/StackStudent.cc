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

	//如果放在全局的位置, 当执行new/delete表达式时，
	//会对所有的类型
#if 0
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
#endif

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

	~Student()
	{
		cout << "~Student()" << endl;
		if(_name) {
			delete [] _name;
			_name = nullptr;
		}
	}


	void print() const
	{
		cout << "id: " << _id << endl
			 << "name:" << _name << endl;
	}


private:
	void * operator new(size_t sz);
	void operator delete(void * p);

private:
	int _id;
	char * _name;
};

//需求: 一个类只能创建出栈对象, 不能创建堆对象
//解决方案: 只需要将operator new放在私有区域
 
int main(void)
{
	Student s1(101, "Rose");
	s1.print();

	//Student * pstu = new Student(100, "Jackie");//error
	//pstu->print();

	//delete pstu;
 
	return 0;
}
