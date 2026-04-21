#pragma once
#include <SFML\Graphics.hpp>
#include "Node.hpp"
#include <algorithm>
#include <queue>
#include <math.h>
#include <unordered_map>
#include <list>
using namespace sf;

//template<typename T, typename priority_t>
//struct PriorityQueue {
//    typedef std::pair<priority_t, T> PQElement;
//    std::priority_queue<PQElement, std::vector<PQElement>,
//        std::greater<PQElement>> elements;
//
//    inline bool empty() const {
//        return elements.empty();
//    }
//
//    inline void put(T item, priority_t priority) {
//        elements.emplace(priority, item);
//    }
//
//    T get() {
//        T best_item = elements.top().second;
//        elements.pop();
//        return best_item;
//    }
//};

struct GridLocation
{
    int x, y;
};

class Tilemap
{
public:
    Tilemap(std::vector<Wall> walls)
    {
        tileMap.resize(mapSize, std::vector<RectangleShape>());

        sNodes = new sNode[mapSize * mapSize2];

        for (int i = 0; i < mapSize; i++)
        {
            tileMap[i].resize(mapSize, RectangleShape());
            for (int j = 0; j < mapSize2; j++)
            {
                tileMap[i][j].setSize(Vector2f(gridSizeF, gridSizeF));
                tileMap[i][j].setFillColor(Color::Black);
                tileMap[i][j].setOutlineThickness(1.f);
                tileMap[i][j].setOutlineColor(Color::White);
                tileMap[i][j].setPosition(i * gridSizeF, j * gridSizeF);

                Node n1(tileMap[i][j].getPosition().x, tileMap[i][j].getPosition().y, NULL);
                nodes.push_back(n1);

                sNodes[j * mapSize + i].xPos = i * gridSizeF;
                sNodes[j * mapSize + i].yPos = j * gridSizeF;
                sNodes[j * mapSize + i].gCost = 99999.f;
                sNodes[j * mapSize + i].fCost = 99999.f;
                sNodes[j * mapSize + i].isValid = true;
                sNodes[j * mapSize + i].parent = nullptr;
                sNodes[j * mapSize + i].visited = false;

               
            }
        }
        end.setFillColor(Color::Cyan);
        end.setSize(Vector2f(25.f, 25.f));
        end.setPosition(50.f, 50.f);

        start.setFillColor(Color::Yellow);
        start.setSize(Vector2f(25.f, 25.f));
        start.setPosition(900.f, 50.f); //900, 50

 /*       std::cout << "added start" << std::endl;*/
        //StartAndGoal(start, end);

        /*std::cout << "Start position: " << start.getPosition().x << ", " << start.getPosition().y << std::endl;
        std::cout << "End position: " << end.getPosition().x << ", " << end.getPosition().y << std::endl;*/

        //sNodes = new sNode[mapSize * mapSize2];

        for (int i = 0; i < nodes.size(); i++)
        {
            //std::cout << "for loop" << std::endl;
            nodes[i].id = i;
            nodes[i].hValue = nodes[i].Heuristic(end.getPosition(), nodes[i].nodeShape.getPosition());
            for (int j = 0; j < walls.size(); j++)
            {
                if (nodes[i].nodeShape.getPosition() == walls[j].wallShape.getPosition())
                {
                    nodes[i].isValid = false;
                }
                
            }
            //std::cout << "ID: " << nodes[i].id << " xPos: " << nodes[i].xPos << " yPos: " << nodes[i].yPos << std::endl;

            /*sNodes[i].x = nodes[i].xPos;
            sNodes[i].y = nodes[i].yPos;
            sNodes[i].hCost = nodes[i].hValue;
            sNodes[i].gCost = nodes[i].gValue;
            sNodes[i].isValid = nodes[i].isValid;
            sNodes[i].parent = nullptr;
            sNodes[i].visited = false;*/

            /*sNodeVector[i]->x = nodes[i].xPos;
            sNodeVector[i]->y = nodes[i].yPos;
            sNodeVector[i]->hCost = nodes[i].hValue;
            sNodeVector[i]->gCost = nodes[i].gValue;
            sNodeVector[i]->fCost = 999999.f;
            sNodeVector[i]->isValid = nodes[i].isValid;
            sNodeVector[i]->parent = nullptr;
            sNodeVector[i]->visited = false;*/
        }

        for (int i = 0; i < mapSize * mapSize2; i++)
        {
            for (int j = 0; j < walls.size(); j++)
            {
                if (sNodes[i].xPos == walls[j].wallShape.getPosition().x && 
                    sNodes[i].yPos == walls[j].wallShape.getPosition().y)
                {
                    sNodes[i].isValid = false;
                }

            }

            //std::cout << "SNode position: " << sNodes[i].xPos << ", " << sNodes[i].yPos << std::endl;

            if (sNodes[i].xPos == start.getPosition().x && sNodes[i].yPos == start.getPosition().y)
            {
                sNodeStart = &sNodes[i];
            }

            if (sNodes[i].xPos == end.getPosition().x && sNodes[i].yPos == end.getPosition().y)
            {
                sNodeEnd = &sNodes[i];
            }

            /*if (nodes[i].xPos == start.getPosition().x && nodes[i].yPos == start.getPosition().y)
            {
                sNodeStart = &sNodes[i];
                std::cout << "start[i] position: " << nodes[i].xPos << ", " << nodes[i].yPos << std::endl;
                std::cout << "sNodeStart position: " << sNodeStart->xPos << ", " << sNodeStart->yPos << std::endl;
            }

            if (nodes[i].xPos == end.getPosition().x && nodes[i].yPos == end.getPosition().y)
            {
                sNodeEnd = &sNodes[i];
                std::cout << "end[i] position: " << nodes[i].xPos << ", " << nodes[i].yPos << std::endl;
                std::cout << "sNodeEnd position: " << sNodeEnd->xPos << ", " << sNodeEnd->yPos << std::endl;
            }*/
        }

        //sNodeStart->xPos = start.getPosition().x;
        //sNodeStart->yPos = start.getPosition().y;
        //sNodeEnd->xPos = end.getPosition().x;
        //sNodeEnd->yPos = end.getPosition().y;

        for (int i = 0; i < mapSize; i++)
        {
            for (int j = 0; j < mapSize2; j++)
            {
                /*if(sNodes[j * mapSize + i].xPos == start.getPosition().x && sNodes[j * mapSize + i].yPos == start.getPosition().y)
                    sNodeStart = &sNodes[j*mapSize + i];
                if (sNodes[j * mapSize + i].xPos == end.getPosition().x && sNodes[j * mapSize + i].yPos == end.getPosition().y)
                    sNodeEnd = &sNodes[j * mapSize + i];*/
                if (j > 0)
                    sNodes[j * mapSize + i].neighbours.push_back(&sNodes[(j - 1) * mapSize + (i + 0)]);
                if (j < mapSize2 - 1)
                    sNodes[j * mapSize + i].neighbours.push_back(&sNodes[(j + 1) * mapSize + (i + 0)]);
                if (i > 0)
                    sNodes[j * mapSize + i].neighbours.push_back(&sNodes[(j + 0) * mapSize + (i - 1)]);
                if (i < mapSize - 1)
                    sNodes[j * mapSize + i].neighbours.push_back(&sNodes[(j + 0) * mapSize + (i + 1)]);
            }
        }
        

       
      
        //std::cout << "Nodes: " <<  nodes.size() << std::endl;
        //sNodeWay.push_back(sNodeEnd);
       
        //Astar();
        
        Astar();
        DrawWayBack();

        std::reverse(sNodeWay.begin(), sNodeWay.end());

        //for (int i = 0; i < closedsNode.size(); i++)
        //{
        //    sNodeShape.setFillColor(Color::Red);
        //    sNodeShape.setSize(Vector2f(25.f, 25.f));
        //    sNodeShape.setPosition(closedsNode[i]->xPos, closedsNode[i]->yPos);
        //    sNodeWay.push_back(sNodeShape);
        //}
        //BreadthFirst();

        //for (int i = 0; i < openList.size(); i++)
        //{
        //    if (openList[i].nodeShape.getPosition() == end.getPosition())
        //    {
        //        way.push_back(openList[i]);
        //        openList.erase(openList.begin() + i);
        //    }
        //}

        //for (int i = 0; i < way.size(); i++)
        //{
        //    WayBack();
        //    //std::cout << "Way id: " << way[i].id << std::endl;
        //}

        //std::reverse(way.begin(), way.end());


    }



    void Neighbours(int id, std::vector<Node> nodes)
    {
        for (int i = 0; i < nodes.size(); i++)
        {
            if (nodes[i].id == id)
            {
                for (int j = 0; j < nodes.size(); j++)
                {
                    if (nodes[i].xPos == nodes[j].xPos + 25.f && nodes[i].yPos == nodes[j].yPos && nodes[i].xPos)
                    {
                        neighbours.push_back(nodes[j]);
                    }
                    else if (nodes[i].xPos == nodes[j].xPos - 25.f && nodes[i].yPos == nodes[j].yPos)
                    {
                        neighbours.push_back(nodes[j]);
                    }
                    else if (nodes[i].xPos == nodes[j].xPos && nodes[i].yPos == nodes[j].yPos + 25.f)
                    {
                        neighbours.push_back(nodes[j]);
                    }
                    else if (nodes[i].xPos == nodes[j].xPos && nodes[i].yPos == nodes[j].yPos - 25.f)
                    {
                        neighbours.push_back(nodes[j]);
                    }
                }
                
            }
        }

    }

    void UpdateNodes()
    {
        //std::cout << "updating nodes" << std::endl;
        /*for (int i = 0; i < nodes.size(); i++)
        {
            std::cout << "testing" << std::endl;
            for (int j = 0; j < neighbours.size(); i++)
            {
                std::cout << "testing2" << std::endl;
                if (nodes[i].id == neighbours[j].id)
                {
                    std::cout << "testing3" << std::endl;
                    nodes[i].gValue = neighbours[j].gValue;
                    nodes[i].fValue = neighbours[j].fValue;
                    nodes[i].parentid = neighbours[j].parentid;
                }
            }
        }*/
        //for (int i = 0; i < neighbours.size(); i++)
        //{
        //    std::cout << neighbours[i].id << std::endl;
        //}
        

        for (int i = 0; i < neighbours.size(); i++)
        {
            //std::cout << "testing " << neighbours.size() << std::endl;
            for (int j = 0; j < nodes.size(); j++)
            {
                //std::cout << "testing2 " << nodes.size() << std::endl;
                if (neighbours[i].id == nodes[j].id)
                {
                    //std::cout << "testing3" << std::endl;
                    nodes[j].gValue = neighbours[i].gValue;
                    nodes[j].fValue = neighbours[i].fValue;
                    nodes[j].parentid = neighbours[i].parentid;
                    nodes[j].isVisited = true;
                }
            }
        }
    }


    //void Update(sf::RenderWindow& window)
    //{
    //    mousePosScreen = Mouse::getPosition();
    //    mousePosWindow2 = Mouse::getPosition(window);
    //    //window.setView(view);
    //    mousePosView = window.mapPixelToCoords(mousePosWindow2);
    //    if (mousePosView.x >= 0.f)
    //        mousePosGrid.x = mousePosView.x / gridSizeU;
    //    if (mousePosView.y >= 0.f)
    //        mousePosGrid.y = mousePosView.y / gridSizeU;

    //    //tileSelector.setPosition(mousePosGrid.x * gridSizeF, mousePosGrid.y * gridSizeF);
    //}

    //void DrawTilemap(sf::RenderWindow& window)
    void DrawTilemap(sf::RenderWindow& window)
    {
        for (int i = 0; i < mapSize; i++)
        {
            for (int j = 0; j < mapSize; j++)
            {
                window.draw(tileMap[i][j]);
            }
        }

        window.draw(start);
        window.draw(end);
        //window.draw(tileSelector&);
    }

    void StartAndGoal(RectangleShape start, RectangleShape goal)
    {
        for (int i = 0; i < nodes.size(); i++)
        {
            if (goal.getPosition() == nodes[i].nodeShape.getPosition())
            {
                goalNode = nodes[i];
            }

            if (start.getPosition() == nodes[i].nodeShape.getPosition())
            {
                nodes[i].parentid = 0;
                //nodes[i].gValue = 99999999.f;
                nodes[i].hValue = nodes[i].Heuristic(goal.getPosition(), start.getPosition());//distance(goalNode);
                startNode = nodes[i];
                //std::cout << "Node id: " << nodes[i].id << std::endl;

                openList.push_back(startNode);
                notTested.push_back(startNode);
                //nodes.erase(nodes.begin() + i);
            }
        }

    }


    void BreadthFirst() //int index)
    {
        for (int j = 0; j < openList.size(); j++)
        {
            for (int i = 0; i < nodes.size(); i++)
            {

                if (nodes[i].xPos == openList[j].xPos - 25 && nodes[i].yPos == openList[j].yPos)
                {
                    if (nodes[i].isValid)
                    {
                        nodes[i].parentid = openList[j].id;
                        nodes[i].gValue = openList[j].gValue + 1;
                        openList.push_back(nodes[i]);
                        nodes.erase(nodes.begin() + i);
                        current = openList.back();
                    }
                }
                else if (nodes[i].xPos == openList[j].xPos + 25 && nodes[i].yPos == openList[j].yPos)
                {
                    if (nodes[i].isValid)
                    {
                        nodes[i].parentid = openList[j].id;
                        nodes[i].gValue = openList[j].gValue + 1;
                        openList.push_back(nodes[i]);
                        nodes.erase(nodes.begin() + i);
                        current = openList.back();
                    }
                }
                else if (nodes[i].xPos == openList[j].xPos && nodes[i].yPos == openList[j].yPos + 25)
                {
                    if (nodes[i].isValid)
                    {
                        nodes[i].parentid = openList[j].id;
                        nodes[i].gValue = openList[j].gValue + 1;
                        openList.push_back(nodes[i]);
                        nodes.erase(nodes.begin() + i);
                        current = openList.back();
                    }
                }
                else if (nodes[i].xPos == openList[j].xPos && nodes[i].yPos == openList[j].yPos - 25)
                {
                    if (nodes[i].isValid)
                    {
                        nodes[i].parentid = openList[j].id;
                        nodes[i].gValue = openList[j].gValue + 1;
                        openList.push_back(nodes[i]);
                        nodes.erase(nodes.begin() + i);
                        current = openList.back();
                    }
                }

            }

            if (current.id == goalNode.id)
            {
                break;
            }
        }
    }

    void DrawWayBack()
    {
        if (sNodeEnd != nullptr)
        {
            sNode* p = sNodeEnd;
            while (p->parent != nullptr)
            {
                sNodeShape.setFillColor(Color::Yellow);
                sNodeShape.setSize(Vector2f(25.f, 25.f));
                sNodeShape.setPosition(p->xPos, p->yPos);
                sNodeWay.push_back(sNodeShape);
                //std::cout << "WayBack position: " << p->xPos << ", " << p->yPos << std::endl;

                p = p->parent;
            }
        }
    }

    void WayBack()
    {
        //Node current;

        for (int i = 0; i < openList.size(); i++)
        {
            /*if (openList[i].nodeShape.getPosition() == end.getPosition())
            {
                way.push_back(openList[i]);
                openList.erase(openList.begin() + i);
            }*/

            for (int j = 0; j < way.size(); j++)
            {
                if (openList[i].id == way[j].parentid)
                {
                    std::cout << "WayBack position: " << openList[i].xPos << ", " << openList[i].yPos << std::endl;
                    way.push_back(openList[i]);
                    openList.erase(openList.begin() + i);
                    
                }
            }


        }


    }

    //testing A*
    void AstarTest()
    {
        //notTested.push_back(startNode);
        //current = startNode;
        //std::cout << "Not tested size " << notTested.size() << std::endl;

        while (!notTested.empty())
        {
            //sort by fValue, lowest first
            notTested.sort([](const Node lhs, const Node rhs) {return lhs.fValue < rhs.fValue;});
            //std::cout << "sorting" << std::endl;

            //get rid of processed nodes
            while (!notTested.empty() && notTested.front().isVisited)
                notTested.pop_front();

            if (notTested.empty())
                break;

            current = notTested.front();
            current.isVisited = true; 
            
            //std::cout << "startnode visited " << startNode.isVisited << std::endl;
            //check neighbours
            //for auto nodeNeighbour : nodeCurrent->vecNeighbours
            Neighbours(current.id, nodes);

            std::cout << "Current id: " << current.id << " bool " << current.isVisited << 
                " vector size: " << notTested.size() << " neighbours " << neighbours.size() << std::endl;

            //for (int i = 0; i < neighbours.size(); i++)
            while(!neighbours.empty())
            {
                //std::cout << "going through neigbours" << std::endl;
                //if the neighbout is not visited and is not an obstacle, add it to the list
                if (!neighbours.front().isVisited && neighbours.front().isValid)
                {
                    notTested.push_back(neighbours.front());
                    //neighbours.erase(neighbours.begin());
                }


                //calculate neighbours potential lowest parent distance
                float fPossiblyLower = current.gValue + current.Heuristic(neighbours.front().nodeShape.getPosition(), current.nodeShape.getPosition());
                
                //if this path is lower than neighbour's current, update the neigbour
                if (fPossiblyLower < neighbours.front().gValue)
                {
                    std::cout << "better value" << std::endl;
                    neighbours.front().parentid = current.id;
                    neighbours.front().gValue = fPossiblyLower;

                    neighbours.front().isVisited = true;

                    //update neighbours score
                    neighbours.front().fValue = neighbours.front().gValue + neighbours.front().Heuristic(goalNode.nodeShape.getPosition(), neighbours.front().nodeShape.getPosition());
                    //UpdateNodes();
                }
                UpdateNodes();
                neighbours.erase(neighbours.begin());

            }

            
        }


    }
    inline double Heuristic(Vector2f(firstPos), Vector2f(secondPos))
    {
        //return std::abs(xPos - yPos);
        return std::abs(firstPos.x - secondPos.x) + std::abs(firstPos.y - secondPos.y);
    }


    void Astar()
    {
        auto distance = [](sNode* a, sNode* b)
        {
            return std::abs(a->xPos - b->xPos) + std::abs(a->yPos - b->yPos);
            //return sqrtf((a->xPos - b->xPos) * (a->xPos - b->xPos) + (a->yPos - b->yPos) * (a->yPos - b->yPos));
        };

        sNode* nodeCurrent = sNodeStart;
        sNodeStart->gCost = 0.f;
        //sNodeStart->fCost = Heuristic(Vector2f(sNodeStart->xPos, sNodeStart->yPos), Vector2f(sNodeEnd->xPos, sNodeEnd->yPos));
        sNodeStart->fCost = distance(sNodeStart, sNodeEnd);

        std::list<sNode*> sNodeNotTested;
        sNodeNotTested.push_back(sNodeStart);

        //std::cout << "Not tested size " << sNodeNotTested.size() << std::endl;

        while (!sNodeNotTested.empty() && nodeCurrent != sNodeEnd)
        {
            //sort by fValue, lowest first
            sNodeNotTested.sort([](const sNode* lhs, const sNode* rhs) {return lhs->fCost < rhs->fCost;});
            //std::cout << "sorting" << std::endl;

            //get rid of processed nodes
            while (!sNodeNotTested.empty() && sNodeNotTested.front()->visited)
            {
                closedsNode.push_back(sNodeNotTested.front());
                sNodeNotTested.pop_front();
            }


            if (sNodeNotTested.empty())
                break;

            nodeCurrent = sNodeNotTested.front();
            nodeCurrent->visited = true;

            /*if (nodeCurrent == sNodeEnd)
                break;*/

            //std::cout << "startnode visited " << startNode.isVisited << std::endl;
            //check neighbours
            for (auto nodeNeighbour : nodeCurrent->neighbours)
            {
                //if neighbour not visited and not an obstacle, add to list
                if (!nodeNeighbour->visited && nodeNeighbour->isValid)
                    sNodeNotTested.push_back(nodeNeighbour);

                //calculate neighbour's potentially lower cost
                //float possiblyLowerCost = current->gCost + Heuristic(nodeNeighbour->xPos, nodeNeighbour->yPos, current->xPos, current->yPos);
                //float possiblyLowerCost = nodeCurrent->gCost + Heuristic(Vector2f(nodeCurrent->xPos, nodeCurrent->yPos), Vector2f(nodeNeighbour->xPos, nodeNeighbour->yPos));
                float possiblyLowerCost = nodeCurrent->gCost + distance(nodeCurrent, sNodeEnd);

                //if this path is lower distance that neighbour's current, update this node as path
                if (possiblyLowerCost < nodeNeighbour->fCost)
                {
                    nodeNeighbour->parent = nodeCurrent;
                    nodeNeighbour->gCost = possiblyLowerCost;

                    //update neighbour's score
                    //nodeNeighbour->fCost = nodeNeighbour->gCost + Heuristic(nodeEnd->xPos, nodeEnd->yPos, nodeNeighbour->xPos, nodeNeighbour->yPos);
                    //nodeNeighbour->fCost = nodeNeighbour->gCost + Heuristic(Vector2f(nodeNeighbour->xPos, nodeNeighbour->yPos), Vector2f(sNodeEnd->xPos, sNodeEnd->yPos));
                    nodeNeighbour->fCost = nodeNeighbour->gCost + distance(nodeNeighbour, sNodeEnd);
                }
            }
            

        }
    }


    unsigned gridSizeU = static_cast<unsigned>(gridSizeF);
    //Vector2i mousePosScreen;
    //Vector2u mousePosGrid;
    //RectangleShape tileSelector(Vector2f(50.f, 50.f));

    //std::vector<RectangleShape> valids, invalids;
    RectangleShape valid, invalid, sNodeShape;
    //bool isValid;

    std::vector<Node> nodes;
    std::vector<Node> openList;
    std::vector<Node> closedList;
    std::vector<Node> way;

    Node goalNode, startNode, current;
    const Node* testNode;

    //std::priority_queue<Vector2f, int> frontier;
    //PriorityQueue<Vector2f, int> frontier;
    //PriorityQueue<int, int> testingQueue;
    //std::priority_queue<Node> testingQueue[2];
    //std::priority_queue<Vector2f, int> testQueue;
    //std::unordered_map<Vector2f, Vector2f> map;
    //std::unordered_map<Vector2f, Vector2f> cameFrom;
    //std::queue<Vector2f> frontier;
    //int testNumber = 0;
    //int testingNumber = 24;

    //int id1, id2, id3, id4;
    //Node wanted1, wanted2, wanted3, wanted4;

    /*int array [4] = {wanted1.hValue, wanted2.hValue, wanted3.hValue, wanted4.hValue};*/
    //int array[4] = { 5, 8, 10, 4 };
    //int lowest;

    sNode* sNodes = nullptr;
    std::vector<RectangleShape> testVector;
    std::list<Node*> listNotTested;
    //std::list<sNode*> listNotTestedsNode;
    std::list<Node> notTested;
    std::vector<Node> neighbours;

    Node* currentTest;
    std::vector<Node*> neighboursTest;
    std::vector<sNode*> sNodeNeighbours;
    std::vector<sNode*> sNodeVector;
    //std::list<sNode*> sNodeNotTested;
    //std::vector<sNode> sNodes;

    sNode* sNodeStart = nullptr;
    sNode* sNodeEnd = nullptr;
    std::vector<RectangleShape> sNodeWay;
    std::vector<sNode*> closedsNode;
    
private:
    float gridSizeF = 25.f; //50.f
    
    const int mapSize = 40; //20
    const int mapSize2 = 32;
    std::vector<std::vector<RectangleShape>> tileMap;
    RectangleShape start;
    RectangleShape end;

    //Vector2i mousePosScreen;
    /*Vector2i mousePosWindow2;
    Vector2f mousePosView;*/
    //Vector2u mousePosGrid;

};
