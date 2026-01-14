#ifndef MAPDATA_H
#define MAPDATA_H

#include <QObject>
#include <QList>
#include <QPair>
#include <QMap>//有序键值对容器，树

class MapNode {
public:
    MapNode(int x, int y) : x(x), y(y) {}
    int x;
    int y;
};

class MapEdge {
public:
    MapEdge(int fromNode, int toNode, double distance) 
        : fromNode(fromNode), toNode(toNode), distance(distance) {}
    int fromNode;
    int toNode;
    double distance;

};

class MapData : public QObject
{
    Q_OBJECT
public:
    static MapData *instance();
    
    void generategridmap(int width, int height, int gridSize = 50);
    QList<MapNode> nodes() const;
    QList<MapEdge> edges() const;
    QMap<int, QList<MapEdge>> adjacencylist() const;

    // 根据网格坐标获取最近的节点
    int getnearestnode(int x, int y) const;
    // 获取节点的网格坐标
    QPair<int, int> getnodecoordinates(int nodeId) const;
    double calculatedistance(int x1, int y1, int x2, int y2) const;
    // 计算两个节点之间的曼哈顿距离,使用于网格
    int calculatemanhattandistance(int nodeId1, int nodeId2) const;
    // 根据节点ID获取邻接节点列表
    QList<MapEdge> getadjacentnodes(int nodeId) const;
private:
    MapData(QObject *parent = nullptr);
    ~MapData() override;

    static MapData *m_instance;
    QList<MapNode> m_nodes;
    QList<MapEdge> m_edges;
    QMap<int, QList<MapEdge>> m_adjacencyList;
    double m_gridSize;
};

#endif // MAPDATA_H
