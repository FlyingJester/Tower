#pragma once

#include <queue>
#include <mutex> //Someday this will be lockless.

namespace tower{
namespace concurrent{

template<typename T>
class concurrent_queue {
    std::queue<T> _queue;
    std::mutex _mutex;
public:
    concurrent_queue()
      : _queue (std::queue<T> ()){
    }
    ~concurrent_queue() {}
    
    size_t size(){
        _mutex.lock();
        size_t ret = _queue.size();
        _mutex.unlock();
        return ret;
    }
    T pop(void){
        _mutex.lock();
        if(_queue.empty()){
            _mutex.unlock();
            return nullptr;
        }
        T ret = _queue.front();       
        _queue.pop();
        _mutex.unlock();
        return ret;
    }
    void push(T t){ //void tower::concurrent::concurrent_queue<T>::push (T t)
        _mutex.lock();
        _queue.push(t);
        _mutex.unlock();
    }
};

}
}