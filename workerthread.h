#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H

#include <QThread>//多线程
#include <QObject>
#include <QMutex>//
#include <QWaitCondition>
#include <QList>         // 信号中用到的QList
#include <QPair>         // 信号中用到的QPair
class WorkerThread : public QThread
{
    Q_OBJECT
public:
    explicit WorkerThread(QObject *parent = nullptr);
    ~WorkerThread() override;

    // 路径规划任务
    void planpath(int startX, int startY, int endX, int endY);
    // 派车任务
    void dispatchorder(void *order);

signals:
    // 路径规划完成信号
    void pathPlanned(const QList<QPair<int, int>> &path);
    // 派车完成信号
    void orderDispatched(void *order, void *driver);

protected:
    void run() override;

private:
    enum TaskType {
        None,
        PathPlanning,
        DispatchOrder
    };

    TaskType m_taskType;
    int m_startX;
    int m_startY;
    int m_endX;
    int m_endY;
    void *m_order;
    
    QMutex m_mutex;
    QWaitCondition m_condition;
};

#endif // WORKERTHREAD_H
