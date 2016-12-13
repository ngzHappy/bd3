#include <cassert>
#include <QtCore>
#include <QtBasicLibrary.hpp>
#include "TestSingleThreadPool.hpp"

TestSingleThreadPool::TestSingleThreadPool(){

    {
        auto aThreadPool = QSingleThreadPool::currentQSingleThreadPool().lock();
        auto bThreadPool = QSingleThreadPool::qAppQSingleThreadPool();
            assert( aThreadPool != nullptr );
            assert( aThreadPool == bThreadPool );
            aThreadPool->run([](){
            qDebug()<<QThread::currentThread()<<"qapp thread pool test";
        });
    }

}

TestSingleThreadPool::~TestSingleThreadPool(){
}

void TestSingleThreadPool::test1() {
    QSingleThreadPool aThreadPool;
    
    aThreadPool.runLambda([lock=aThreadPool.lock()]() {
        if(lock)
        qDebug()<<QThread::currentThread()<<0<<" test 1";
    });
    
    aThreadPool.runLambda([lock=aThreadPool.lock()]() {
        if(lock)
        qDebug()<<QThread::currentThread()<<1<<" test 1";
    });
    
    aThreadPool.runLambda([lock=aThreadPool.lock()]() {
        if(lock)
        qDebug()<<QThread::currentThread()<<2<<" test 1";
    });

    aThreadPool.runLambda([lock=aThreadPool.lock()]() {
        if(lock)
        qDebug()<<QThread::currentThread()<<3<<" test 1";
    });

}

void TestSingleThreadPool::test2() {

    QSingleThreadPool bThreadPool;
    auto callBackPool = QSingleThreadPool::currentQSingleThreadPool();
    assert( callBackPool.lock() );

    bThreadPool.runLambda([callBackPool,lock=bThreadPool.lock()]() {
        auto && callBack=QSingleThreadPool::lockWithQApp(callBackPool);
        if (callBack) {
            callBack->run([]() {qDebug()<<"call back"; });
        }
    });

}

