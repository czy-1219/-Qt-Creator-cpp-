#include "pathplanner.h"
#include "mapdata.h"
#include <cmath>
PathPlanner *PathPlanner::m_instance = nullptr;

PathPlanner::PathPlanner(QObject *parent)
    : QObject(parent)
{
}

PathPlanner::~PathPlanner()
{
}

PathPlanner *PathPlanner::instance()
{
    if (!m_instance) {
        m_instance = new PathPlanner();
    }
    return m_instance;
}

QList<QPair<int, int>> PathPlanner::planpath(int startX, int startY, int endX, int endY)
{// 网格路径规划
    QList<QPair<int, int>> path;
    // 添加起点
    path.append(qMakePair(startX, startY));
    int currentGridX = startX;
    int currentGridY = startY;
    // 沿x轴移动
    while (currentGridX != endX) {
        if (currentGridX < endX) {
            currentGridX++;
        } else {
            currentGridX--;
        }
        // 直接添加网格坐标到路径
        path.append(qMakePair(currentGridX, currentGridY));
    }
    // 沿y轴移动
    while (currentGridY != endY) {
        if (currentGridY < endY) {
            currentGridY++;
        } else {
            currentGridY--;
        }
        
        // 直接添加网格坐标到路径
        path.append(qMakePair(currentGridX, currentGridY));
    }
    path.append(qMakePair(endX, endY));
    
    return path;
}

QList<QPair<int, int>> PathPlanner::smoothpath(const QList<QPair<int, int>> &path)
{
    // 简单的路径平滑，移除共线点，只保留起点与终点，拐点
    if (path.size() < 3) {
        return path;
    }

    QList<QPair<int, int>> smoothPath;
    smoothPath.append(path[0]);

    for (int i = 1; i < path.size() - 1; ++i) {
        const QPair<int, int> &prev = path[i - 1];
        const QPair<int, int> &curr = path[i];
        const QPair<int, int> &next = path[i + 1];
        // 计算向量
        int dx1 = curr.first - prev.first;
        int dy1 = curr.second - prev.second;
        int dx2 = next.first - curr.first;
        int dy2 = next.second - curr.second;

        // 如果三个点共线，跳过当前点
        if (dx1 * dy2 != dx2 * dy1) {
            smoothPath.append(curr);
        }
    }

    smoothPath.append(path.last());
    return smoothPath;
}

double PathPlanner::calculateheuristic(int currentNode, int endNode) const
{//Astar算法
    MapData *mapData = MapData::instance();
    QPair<int, int> currentCoords = mapData->getnodecoordinates(currentNode);
    QPair<int, int> endCoords = mapData->getnodecoordinates(endNode);
    // 使用曼哈顿距离作为启发函数（适用于网格地图）
    return mapData->calculatedistance(currentCoords.first, currentCoords.second, 
                                     endCoords.first, endCoords.second);
}

QList<int> PathPlanner::reconstructpath(const std::unordered_map<int, int> &cameFrom, int startNode, int endNode) const
{//将Astar算法得到的结果反向回溯
    QList<int> path;
    int current = endNode;

    while (current != startNode) {
        path.prepend(current);
        auto it = cameFrom.find(current);
        if (it == cameFrom.end()) {
            return QList<int>(); // 路径不完整
        }
        current = it->second;
    }
    return path;
}
