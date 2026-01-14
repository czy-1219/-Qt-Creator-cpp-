#include "workerthread.h"
#include <QMutex>
#include <QWaitCondition>// 多线程同步
#include "pathplanner.h"
#include "dispatchsystem.h"
#include "order.h"
WorkerThread::WorkerThread(QObject *parent)//父子对象机制自动管理内存
    : QThread(parent)
    , m_taskType(None)
    , m_order(nullptr)
{
}

WorkerThread::~WorkerThread()
{
    // 停止线程
    m_mutex.lock();//加锁
    m_taskType = None;//设置为无任务
    m_condition.wakeOne();//唤醒
    m_mutex.unlock();//解锁
    wait();
}

void WorkerThread::planpath(int startX, int startY, int endX, int endY)
{
    m_mutex.lock();
    m_taskType = PathPlanning;
    m_startX = startX;
    m_startY = startY;
    m_endX = endX;
    m_endY = endY;
    m_condition.wakeOne();
    m_mutex.unlock();
    
    if (!isRunning()) {
        start();
    }
}

void WorkerThread::dispatchorder(void *order)
{
    m_mutex.lock();
    m_taskType = DispatchOrder;
    m_order = order;
    m_condition.wakeOne();
    m_mutex.unlock();
    
    if (!isRunning()) {
        start();
    }
}

void WorkerThread::run()//run() 是 QThread 的核心虚函数，也是子线程的唯一执行入口：
{
    while (true) {//线程无限循环
        m_mutex.lock();  // 枷锁等待任务
        while (m_taskType == None) {
            m_condition.wait(&m_mutex);
        }//调用 wait 的瞬间，自动释放锁 + 线程进入休眠阻塞状态，
        
        TaskType taskType = m_taskType;
        int startX = m_startX;
        int startY = m_startY;
        int endX = m_endX;
        int endY = m_endY;
        void *order = m_order;//成员变量拷贝到局部变量，保证线程安全
        // 重置任务类型
        m_taskType = None;     //已经读取完当前的任务
        m_mutex.unlock();//解锁可以读取下一个任务
        if (taskType == PathPlanning) {
            // 执行路径规划
            QList<QPair<int, int>> path = PathPlanner::instance()->planpath(startX, startY, endX, endY);
            emit pathPlanned(path);//发射跨线程信号，将规划好的路径传递给主线程
        }
        else if (taskType == DispatchOrder) {
            // 执行派车
            Order *orderObj = static_cast<Order *>(order);
            DispatchSystem::instance()->dispatchorder(orderObj);
            // 注意：派车系统会通过信号通知结果，这里不需要直接返回
        }
    }
}
