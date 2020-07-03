#include "triangle.h"
#include <data_structure/nodedag.h>


Triangle::Triangle()
{

}
//Constructor for the triangle class, that take 3 pointers, the 3 vertices of the triangle
Triangle::Triangle(cg3::Point2Dd* A, cg3::Point2Dd* B, cg3::Point2Dd* C)
{
    this->A = A;
    this->B = B;
    this->C = C;

}

//Destructor
Triangle::~Triangle()
{

}

//Copy constructor
Triangle::Triangle(Triangle& t)
{
    this->A = t.getA();
    this->B = t.getB();
    this->C = t.getC();
}


//Getter and Setter of the points

cg3::Point2Dd* Triangle::getA()
{
    return this->A;
}

cg3::Point2Dd* Triangle::getB()
{
    return this->B;
}

cg3::Point2Dd* Triangle::getC()
{
    return this->C;
}

void Triangle::setA(cg3::Point2Dd* A)
{
    this->A = A;
}

void Triangle::setB(cg3::Point2Dd* B)
{
    this->B = B;
}

void Triangle::setC(cg3::Point2Dd* C)
{
    this->C = C;
}

//Get the node of the triangle
NodeDag* Triangle::getNodeDag()
{
    return this->node_Dag;
}

//Set the node of the triangle
void Triangle::setNodeDag(NodeDag *node_Dag)
{
    this->node_Dag = node_Dag;
}

//Given two points p1 and p2, this method return the missing point from the triangle itself
//This method is used in the legalize algorithm
cg3::Point2Dd* Triangle::getMissingPoint(const cg3::Point2Dd& p1, const cg3::Point2Dd& p2)
{
    //If p1 and p2 are equals to AB-BA, return C
    if((*this->getA()==p1 && *this->getB()==p2) || (*this->getA()==p2 && *this->getB()==p1))
    {

        return this->getC();
    }

    //If p1 and p2 are equals to AC-CA, return B
    if((*this->getA()==p1 && *this->getC()==p2) || (*this->getA()==p2 && *this->getC()==p1))
    {

        return this->getB();
    }

    //If p1 and p2 are equals to BC-CB, return A
    if((*this->getB()==p1 && *this->getC()==p2) || (*this->getB()==p2 && *this->getC()==p1))
    {

        return this->getA();
    }

    //Return nullptr otherwise
    return nullptr;
}

//Method used to compare two triangles
bool Triangle::equalsTo(Triangle& t)
{
    if((this->getA()==t.getA()) && (this->getB()==t.getB()) && (this->getC()==t.getC()))
        return true;
    else
        return false;
}

//Getter adjacent triangle
Triangle* Triangle::getAdj1()
{
    return this->adj1;
}
Triangle* Triangle::getAdj2()
{
    return this->adj2;
}
Triangle* Triangle::getAdj3()
{
    return this->adj3;
}

//Setter adjacent triangle
void Triangle::setAdj1(Triangle* t)
{
    this->adj1 = t;
}
void Triangle::setAdj2(Triangle* t)
{
    this->adj2 = t;
}
void Triangle::setAdj3(Triangle* t)
{
    this->adj3 = t;
}

//Set the state of the triangle
void Triangle::setRemoveTriangle(bool b)
{
    this->removeTriangle=b;
}

//Get the state of the triangle
bool Triangle::getRemoveTriangle()
{
    return this->removeTriangle;
}
