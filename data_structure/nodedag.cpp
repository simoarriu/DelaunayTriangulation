#include "nodedag.h"
#include <data_structure/triangle.h>

NodeDag::NodeDag()
{

}
//Constructor
NodeDag::NodeDag(Triangle* triangle)
{
    this->triangle=triangle;
}
//Destructor
NodeDag::~NodeDag()
{

}
//Copy Constructor
NodeDag::NodeDag(NodeDag& node)
{
    this->triangle=node.getTriangle();
}

//Getter and Setter Triangle

Triangle* NodeDag::getTriangle()
{
    return this->triangle;
}

void NodeDag::setTriangle(Triangle* triangle)
{
    this->triangle=triangle;
}

//Getter and Setter children

NodeDag* NodeDag::getFirstChild()
{
    return this->firstChild;
}

NodeDag* NodeDag::getSecondChild()
{
    return this->secondChild;
}

NodeDag* NodeDag::getThirdChild()
{
    return this->thirdChild;
}


void NodeDag::setFirstChild(NodeDag* firstChild)
{
    this->firstChild=firstChild;
}

void NodeDag::setSecondChild(NodeDag* secondChild)
{
    this->secondChild=secondChild;
}

void NodeDag::setThirdChild(NodeDag* thirdChild)
{
    this->thirdChild=thirdChild;
}

Triangle* NodeDag::getFirstChildTriangle()
{
    return this->getFirstChild()->getTriangle();
}
Triangle* NodeDag::getSecondChildTriangle()
{
    return this->getSecondChild()->getTriangle();
}
Triangle* NodeDag::getThirdChildTriangle()
{
    return this->getThirdChild()->getTriangle();
}
