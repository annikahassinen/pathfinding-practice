#pragma once
#include <SFML\Graphics.hpp>
#include <cstdlib>
#include <vector>
using namespace sf;

struct sNode
{
    bool isValid = false;
    bool visited = false;
    float gCost = 0;
    float hCost = 0;
    float fCost = 0;
    float xPos = 0;
    float yPos = 0;
    std::vector<sNode*> neighbours;
    sNode* parent = NULL;
};

class Node
{
public:
    Node()
    {

    }
    Node(int x, int y, Node *parent)
    {
        xPos = x;
        yPos = y;
        id = 0;
        gValue = 9999999;
        hValue = 9999999;
        isVisited = false;

        nodeShape.setSize(Vector2f(size, size));
        nodeShape.setFillColor(Color::Yellow);
        nodeShape.setPosition(Vector2f(x, y));
    }


    float size = 25.f;
    int xPos = 0;
    int yPos = 0;
    int gValue = 0;
    int hValue = 0;
    float fValue = 0; // = gValue + hValue;
    RectangleShape nodeShape;
    //Node parent;
    int id = 0;
    int parentid = 0;

    bool isValid = true;
    bool isVisited = false;

    float GetF() { return gValue + hValue; }

    Node* parent = NULL;

    //std::vector<Node> nodes;


    void CalculateValue()
    {

    }

    /*float distance(Node goalNode)
    {
        float x = (float)(fabs(this->xPos - goalNode.xPos));
        float y = (float)(fabs(this->yPos - goalNode.yPos));

        return x + y;
    }*/

    inline double Heuristic(Vector2f(firstPos), Vector2f(secondPos))
    {
        //return std::abs(xPos - yPos);
        return std::abs(firstPos.x - secondPos.x) + std::abs(firstPos.y - secondPos.y);
    }

   /* friend bool operator<(const Node a, const Node b)
    {
        return a.fValue > b.fValue;
    }*/
    
};
