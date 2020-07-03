#include "dag.h"
#include <utils/delaunay_checker.h>
#include <cg3/geometry/2d/utils2d.h>


Dag::Dag()
{

}


//return the vector of pointers with the nodes
std::vector<NodeDag*> Dag::getNodes()
{
    return nodesDag;
}

//Getter last and first node of the vector
NodeDag* Dag::getBack()
{
    return this->nodesDag.back();
}

NodeDag* Dag::getFront()
{
    return this->nodesDag.front();
}

//create and push on the vector a new node based on the triangle t, set the node of the dag
//to the triangle t and set also the first/second/third child of the current node
void Dag::addToDag(Triangle* t, NodeDag& currentNode)
{
    this->createAndAddNode(t);
    t->setNodeDag(this->getBack());

    if(currentNode.getFirstChild()==nullptr)
        currentNode.setFirstChild(this->getBack());
    else if (currentNode.getSecondChild()==nullptr)
        currentNode.setSecondChild(this->getBack());
    else if (currentNode.getThirdChild()==nullptr)
        currentNode.setThirdChild(this->getBack());
}

//The same of the previous method, but in this case we consider the current node and
//the adjacent node (edge flip case) and the two nodes have the same child
//(we check only first and second child because in the edge flip case the nodes
//have 2 childrens, not 3)
void Dag::addToDagAfterFlip(Triangle* t, NodeDag& currentNode,NodeDag& adjNode)
{
    this->createAndAddNode(t);
    t->setNodeDag(this->getBack());

    if(currentNode.getFirstChild()==nullptr)
        currentNode.setFirstChild(this->getBack());
    else if (currentNode.getSecondChild()==nullptr)
        currentNode.setSecondChild(this->getBack());

    if(adjNode.getFirstChild()==nullptr)
        adjNode.setFirstChild(this->getBack());
    else if (adjNode.getSecondChild()==nullptr)
        adjNode.setSecondChild(this->getBack());
}

//Given a pointer to the node (in each call, at the firt time nodeDag is the root of the dag, that is the first
//element in the vector) and a point, this method return a pointer to the node where the point lies.
NodeDag* Dag::findNode(NodeDag* nodeDag, const cg3::Point2Dd& p)
{
    //Pointer to the triangle of the node
    Triangle* triangle;

   //Check the first child of the node
    if(nodeDag->getFirstChild()!=nullptr)
    {
        //we need to check if the point is inside the triangle related to this node
        triangle = nodeDag->getFirstChildTriangle();

        //Check if the point lies in this triangles
        if(cg3::isPointLyingInTriangle(*triangle->getA(),*triangle->getB(),*triangle->getC(),p,true))
        {
            //The point lies in this triangle, so we re-call findNode given as parameter the first child and the point
            nodeDag = findNode(nodeDag->getFirstChild(),p);

        }
    }

     //Same checks but at the second child
    if(nodeDag->getSecondChild()!=nullptr)
    {

        triangle = nodeDag->getSecondChildTriangle();

        //if the point lies in this triangle, we re-call findNode given as parameter the second child and the point
        if(cg3::isPointLyingInTriangle(*triangle->getA(),*triangle->getB(),*triangle->getC(),p,true))
            nodeDag = findNode(nodeDag->getSecondChild(),p);
    }

    //Same checks but at the third child
    if(nodeDag->getThirdChild()!=nullptr)
    {

        triangle = nodeDag->getThirdChildTriangle();

        //if the point lies in this triangle, we re-call findNode given as parameter the third child and the point
        if(cg3::isPointLyingInTriangle(*triangle->getA(),*triangle->getB(),*triangle->getC(),p,true))
            nodeDag = findNode(nodeDag->getThirdChild(),p);
    }

    //We return the node when all the three pointers to the node are == nullptr, so we have reach
    //the leaf and we return the related node, containing the point in input
    return nodeDag;

}


//Create the pointer node from the triangle t and add it to the vector
void Dag::createAndAddNode(Triangle* t)
{
    NodeDag* node = new NodeDag(t);
    nodesDag.push_back(node);
}

//Clear the vector
void Dag::clearNodes()
{
    nodesDag.clear();
}

//Delete the pointers from the vector
void Dag::deletePointersNodes()
{
    for(it_n=nodesDag.begin(); it_n != nodesDag.end(); it_n++)
        delete (*it_n);
}
