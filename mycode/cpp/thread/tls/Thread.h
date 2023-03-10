#pragma once
#include "Nocopyble.h"
#include <pthread.h>
#include <iostream>
#include <functional>
#include <string>
using std::string;
using std::cout;
using std::endl;

namespace wd{
namespace current_thread {
extern __thread const char* threadName;
}

using ThreadCallback = std::function<void()>;

class Thread : Nocopyble {
public:
    Thread(ThreadCallback&& cb, const string& name = string()) 
        : _pthid(0)
          , _isRunning(false) 
          , _cb(std::move(cb)) 
          , _name(name) {}

    ~Thread();
    void start();
    void join();
    string name() const { return _name; }
    static void* threadFunc(void*);
private:
    pthread_t _pthid;
    bool _isRunning;
    ThreadCallback _cb;
    string _name;
};
}

