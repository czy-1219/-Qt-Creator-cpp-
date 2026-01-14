#include "mapdata.h"
#include <cmath>

MapData *MapData::m_instance = nullptr;

MapData::MapData(QObject *parent)
    : QObject(parent), m_gridSize(0.01)
{
}

MapData::~MapData()
{
}

MapData *MapData::instance()
{
    if (!m_instance) {
        m_instance = new MapData();
    }
    return m_instance;
}

void MapData::generategridmap(int w, int h, int g)
{
    m_gridSize = g;
    m_nodes.clear();
    m_edges.clear();
    m_adjacencyList.clear();

    // 生成节点
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            m_nodes.append(MapNode(x, y));
        }
    }

    // 生成边
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            int currentNode = y * w + x;//将二位坐标转换为一维的id，id与坐标一一对应
            // 向右连接
            if (x < w - 1) {
                int rightNode = currentNode + 1;
                double distance = 1.0; // 网格距离为1
                m_edges.append(MapEdge(currentNode, rightNode, distance));
                m_edges.append(MapEdge(rightNode, currentNode, distance));
            }
            // 向下连接
            if (y < h - 1) {
                int downNode = currentNode + w;
                double distance = 1.0;
                m_edges.append(MapEdge(currentNode, downNode, distance));
                m_edges.append(MapEdge(downNode, currentNode, distance));
                //双向通行
            }
        }
    }

    // 构建邻接表
    // 邻接表是一种图的表示方法，用于存储节点之间的连接关系
    // 这里使用QMap<int, QList<MapEdge>>结构，键为节点ID，值为该节点的所有出边
    for (const MapEdge &edge : m_edges) {
        // 将每条边添加到起始节点的邻接列表中，邻接表查找提高效率
        m_adjacencyList[edge.fromNode].append(edge);//为每个节点提前存好它的所有邻接边
    }
}

QList<MapNode> MapData::nodes() const
{
    return m_nodes;
}

QList<MapEdge> MapData::edges() const
{
    return m_edges;
}

QMap<int, QList<MapEdge>> MapData::adjacencylist() const
{
    return m_adjacencyList;
}

int MapData::getnearestnode(int x, int y) const
{
    int nearestNode = -1;
    double minDistance = std::numeric_limits<double>::max();//初始化最小距离为「C++ 浮点型的最大值」，保证第一次比较时一定会更新。

    for (int i = 0; i < m_nodes.size(); ++i) {
        double distance = calculatedistance(x, y, m_nodes[i].x, m_nodes[i].y);
        if (distance < minDistance) {
            minDistance = distance;
            nearestNode = i;
        }
    }

    return nearestNode;
}

QPair<int, int> MapData::getnodecoordinates(int nodeId) const
{
    if (nodeId >= 0 && nodeId < m_nodes.size()) {
        return qMakePair(m_nodes[nodeId].x, m_nodes[nodeId].y);
    }
    return qMakePair(0, 0);
}

QList<MapEdge> MapData::getadjacentnodes(int nodeId) const
{
    if (m_adjacencyList.contains(nodeId)) {
        return m_adjacencyList[nodeId];    // 从邻接表中获取指定节点的所有邻接边
    }
    return QList<MapEdge>(); // 如果节点不存在，返回空列表
    //qmakepair创建并返回一个 QPair 类型的对象。
}

double MapData::calculatedistance(int x1, int y1, int x2, int y2) const
{
    // 使用曼哈顿距离
    return std::abs(x1 - x2) + std::abs(y1 - y2);
}

int MapData::calculatemanhattandistance(int nodeId1, int nodeId2) const
{
    if (nodeId1 < 0 || nodeId1 >= m_nodes.size() || nodeId2 < 0 || nodeId2 >= m_nodes.size()) {
        return 0;
    }
    
    const MapNode &node1 = m_nodes[nodeId1];
    const MapNode &node2 = m_nodes[nodeId2];
    
    return std::abs(node1.x - node2.x) + std::abs(node1.y - node2.y);
}
