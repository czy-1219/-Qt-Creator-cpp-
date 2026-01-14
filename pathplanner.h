#ifndef PATHPLANNER_H
#define PATHPLANNER_H

#include <QObject>
#include <QList>
#include <QPair>
#include <unordered_map>//cpp标准库，无序哈希表容器，键值对存储，基于哈希表实现

class PathPlanner : public QObject
{
    Q_OBJECT
public:
    struct NodeRecord {
        int nodeId;
        double g; // 从起点到当前节点的实际代价
        double h; // 当前节点到终点的预估代价
        double f; // f = g + h
        int parentId;

        NodeRecord(int nodeId = -1, double g = 0.0, double h = 0.0, int parentId = -1)
            : nodeId(nodeId), g(g), h(h), f(g + h), parentId(parentId) {}

        // 用于优先队列排序，f值小的优先
        bool operator>(const NodeRecord &other) const {
            return f > other.f;
        }
    };

    static PathPlanner *instance();

    QList<QPair<int, int>> planpath(int startX, int startY, int endX, int endY);
    QList<QPair<int, int>> smoothpath(const QList<QPair<int, int>> &path);

private:
    PathPlanner(QObject *parent = nullptr);
    ~PathPlanner() override;

    static PathPlanner *m_instance;
    double calculateheuristic(int currentNode, int endNode) const;
    QList<int> reconstructpath(const std::unordered_map<int, int> &cameFrom, int startNode, int endNode) const;
};

#endif // PATHPLANNER_H
