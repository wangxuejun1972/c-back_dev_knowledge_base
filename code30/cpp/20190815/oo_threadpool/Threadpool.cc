 ///
 /// @file    Threadpool.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-08-15 15:52:56
 ///
 
#include "Threadpool.h"
#include "WorkerThread.h"
#include "Task.h"

#include <unistd.h>

#include <iostream>

using std::cout;
using std::endl;
 

namespace wd
{

Threadpool::Threadpool(size_t threadNum, size_t queSize)
: _threadNum(threadNum)
, _queSize(queSize)
, _taskque(_queSize)
, _isExit(false)
{
	_threads.reserve(_threadNum);//只是开辟空间，没有元素
}

Threadpool::~Threadpool()
{
	if(!_isExit) {
		stop();
	}
}

void Threadpool::start()
{
	for(size_t idx = 0; idx != _threadNum; ++idx) {
		unique_ptr<Thread> thread(new WorkerThread(*this));
		_threads.push_back(std::move(thread));
	}

	for(auto & thread : _threads) {
		thread->start();
	}
}

void Threadpool::addTask(Task * task)
{
	_taskque.push(task);
}


Task * Threadpool::getTask()
{
	return _taskque.pop();
}

//每一个子线程都要完成的任务
void Threadpool::threadFunc()
{
	while(!_isExit) {
		Task * task = getTask();
		if(task)
			task->process();//执行任务
	}
}

void Threadpool::stop()
{
	if(!_isExit) {

		while(!_taskque.empty()) {

			cout << "1111 is empty " << _taskque.empty() << endl;
			//::sleep(1);		
			//::usleep(100000);		
			::usleep(1);		
		}
		//当任务执行的速度太快，在将_isExit设置为true之前，
		//每一个子线程都已经取任务，此时发现_taskque之中
		//没有任务了，所有都会阻塞在_notEmpty的条件变量之上，
		//从而导致每一个子线程无法退出
		cout << "2222" << endl;
		_isExit = true;
		_taskque.wakeup();
		
		cout << "3333" << endl;
		for(auto & thread : _threads)
		{
			thread->join();
		}
	}	
} 

}//end of namespace wd
