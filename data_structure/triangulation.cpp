#include "triangulation.h"
#include <data_structure/dag.h>

Triangulation::Triangulation()
{

}

//get the vector of pointers of triangles
std::vector<Triangle*> Triangulation::getTriangles() const
{
    return this->triangles;
}

//get the vector of pointers of points
std::vector<cg3::Point2Dd*> Triangulation::getPoints()
{
    return this->points;
}

//add the given point to the vector of points
void Triangulation::addPoint(cg3::Point2Dd* point)
{
    this->points.push_back(point);
}

//create the pointer and add it to the vector of points
void Triangulation::addPoint(const cg3::Point2Dd& point)
{
    cg3::Point2Dd* p = new cg3::Point2Dd(point);
    this->points.push_back(p);
}

//add the given triangle to the vector of triangles
void Triangulation::addTriangle(Triangle* t)
{
    this->triangles.push_back(t);
}

//clear the vector of points
void Triangulation::clearPoints()
{
    this->points.clear();
}

//clear the vector of triangles
void Triangulation::clearTriangles()
{
    this->triangles.clear();
}

//delete the pointers in the vector of points
void Triangulation::deletePointersPoints()
{
    for(it_p=points.begin();it_p !=points.end(); it_p++)
        delete *(it_p);
}

//delete the pointers in the vector of triangles
void Triangulation::deletePointersTriangles()
{

    for(it_t=triangles.begin();it_t !=triangles.end(); it_t++)
        delete *(it_t);
}

//get the triangle at a given index
Triangle* Triangulation::getTriangleAt(unsigned long i)
{
    return this->triangles.at(i);
}

//get a point at a given index
cg3::Point2Dd* Triangulation::getPointAt(unsigned long i)
{
    return this->points.at(i);
}

//return the size of the vector of triangles
unsigned long Triangulation::getTrianglesSize()
{
    return this->triangles.size();
}

//create the new triangle with the given points and add it to the vector of triangles
void Triangulation::addToTriangulation(cg3::Point2Dd* A, cg3::Point2Dd* B, cg3::Point2Dd* C)
{
    Triangle* t = new Triangle(A,B,C);
    this->addTriangle(t);
}

//get the last triangle of the vector
Triangle* Triangulation::getBack()
{
    return this->triangles.back();
}

//get the last point of the vector
cg3::Point2Dd* Triangulation::getBackP()
{
    return this->points.back();
}

//get the iterator to the beginning of the vector of triangles
std::vector<Triangle*>::iterator Triangulation::getBeginT()
{
    return this->triangles.begin();
}

//get the iterator to the ending of the vector of triangles
std::vector<Triangle*>::iterator Triangulation::getEndT()
{
    return this->triangles.end();
}

//get the iterator to the beginning of the vector of points
std::vector<cg3::Point2Dd*>::iterator Triangulation::getBeginP()
{
    return this->points.begin();
}

//get the iterator to the ending of the vector of points
std::vector<cg3::Point2Dd*>::iterator Triangulation::getEndP()
{
    return this->points.end();
}

//this method take in input two triangles: t is the "removed" triangle and t_adj is its adjacent
//with this method we want to set at nullptr the pointers to the adjacent of t_adj, if there are some triangles
//equals to t
void Triangulation::deletePointer(Triangle& t, Triangle& t_adj)
{
        //if the triangle t_adj has as adjacent the triangle t, we set this pointer to null

        //Check the first adjacent
        if(t_adj.getAdj1()!=nullptr)
            if(t_adj.getAdj1()->equalsTo(t))
                t_adj.setAdj1(nullptr);

        //Check the second adjacent
        if(t_adj.getAdj2()!=nullptr)
            if(t_adj.getAdj2()->equalsTo(t))
                t_adj.setAdj2(nullptr);

        //Check the third adjacent
        if(t_adj.getAdj3()!=nullptr)
            if(t_adj.getAdj3()->equalsTo(t))
                t_adj.setAdj3(nullptr);

}

//This method take in input a triangle, that is the current triangle in the triangulation
//(the triangle that contains the point in input) and for each adjacent of the triangle, we need to delete
//the pointer to the current triangle, beacuse now this triangle is composed by 3 "sub-triangles" or
//2 "sub-triangles" in case of edge flip
void Triangulation::removePointerAdjacent(Triangle& t)
{
    //delete the pointer to t from each adjacent
    if(t.getAdj1()!=nullptr)
        deletePointer(t,*t.getAdj1());
    if(t.getAdj2()!=nullptr)
        deletePointer(t,*t.getAdj2());
    if(t.getAdj3()!=nullptr)
        deletePointer(t,*t.getAdj3());
}

//Set the new adjacent after compute the edge flip usign the following parameters:
//adj_current_T is the adjacent of the triangle that generates the edge flip
//t is the new triangle generated from the edge flip
//adj_T is the adjacent of the triangle that generates the edge flip (one of the fathers)
//current_T is the triangle that generates the edge flip (one of the fathers)
//bool is the parameter used to understand if adj_current_T is one of the adjacents of current_T or adj_T
void Triangulation::updateEdgeFlipCurrentT(Triangle* adj_current_T, Triangle* t, Triangle& adj_T,Triangle& current_T,bool flag)
{
    if(adj_current_T!= nullptr)
    {
        //If the adjecent triangle given in input is adjacent to t (the new tringle from the edge flip) and it
        //is not equal to the current and the adjacent triangle (the two parents of t), we set the adjacents
        if(isAdjacent(*t,*adj_current_T) && !adj_current_T->equalsTo(current_T) && !adj_current_T->equalsTo(adj_T))
        {
            if(flag)
            {
                //we set the third adjacent of t (adj_current_T is the adjacent triangle in the edge flip method)
                t->setAdj3(adj_current_T);
            }
            else
            {
                //we set the second adjacent of t (adj_current_T is the current triangle in the edge flip method)
                t->setAdj2(adj_current_T);
            }


            //If adj_current_T is adjacent to t, so t is adjacent to adj_current_T
            if(adj_current_T->getAdj1()==nullptr)
                adj_current_T->setAdj1(t);
            else if(adj_current_T->getAdj2()==nullptr)
                adj_current_T->setAdj2(t);
            else if(adj_current_T->getAdj3()==nullptr)
                adj_current_T->setAdj3(t);

        }

    }
}

//This method manage the adjacency after compute the edge flip. Given 3 parameters:
//the current triangle of the flip, the new triangle created after the edge flip, and the adjacent triangle
//of the current triangle used for compute the flip, this method manage the adjacency between the new triangle
//and the adjacent of the current and adjacent triangle, because they no longer belong to the triangulation
void Triangulation::updateAdjacentEdgeFlip(Triangle& current_T, Triangle* t, Triangle& adj_T)
{
    //Check the adjacent of the current triangle (bool = false), that is one parent
    updateEdgeFlipCurrentT(current_T.getAdj1(),t,adj_T,current_T,false);
    updateEdgeFlipCurrentT(current_T.getAdj2(),t,adj_T,current_T,false);
    updateEdgeFlipCurrentT(current_T.getAdj3(),t,adj_T,current_T,false);

    //Check the adjacent of the adjacent triangle (bool = true), that is the other parent
    updateEdgeFlipCurrentT(adj_T.getAdj1(),t,adj_T,current_T,true);
    updateEdgeFlipCurrentT(adj_T.getAdj2(),t,adj_T,current_T,true);
    updateEdgeFlipCurrentT(adj_T.getAdj3(),t,adj_T,current_T,true);

}

//Very similar to the previously "updateEdgeFlipCurrentT", but in this case we update the adjacency
//when a point lies inside a triangle, so we take in input t_adj, that is the adjcent of the parent
//(that is no longer belonging to the triangulation) and t, the new triangle created
void Triangulation::updateAdj(Triangle* t_adj, Triangle* t)
{
    if(t_adj!=nullptr)
    {
        //if the two triangles in input are adjacent
        if(isAdjacent(*t,*t_adj))
        {
            //we set the third adjacent of t (the first and the second are its "brothers")
            t->setAdj3(t_adj);

            //if t_adj is adjacent to t, so t is adjacent to t_adj, and we set this
            if(t_adj->getAdj1()==nullptr)
                t_adj->setAdj1(t);
            else if(t_adj->getAdj2()==nullptr)
                t_adj->setAdj2(t);
            else if(t_adj->getAdj3()==nullptr)
                t_adj->setAdj3(t);
        }
    }
}

//We need to check if the adjacents of the current triangle (the current triangle is the parent of t)
//are also adjacent to the new triangle, and update the new adjacency
void Triangulation::updateAdjacent(Triangle& current_T, Triangle* t)
{
    //check if the first adjacent of current_T is adjacent to t
    updateAdj(current_T.getAdj1(),t);
    //check if the second adjacent of current_T is adjacent to t
    updateAdj(current_T.getAdj2(),t);
    //check if the third adjacent of current_T is adjacent to t
    updateAdj(current_T.getAdj3(),t);

}

//Given 3 triangles, that are the 3 triangles created by the point in input that lies inside a triangle,
//this method is used to set the adjacency between this triangles, because these triangles are always adjacent
//between them and also to update the new adjacency of t1, that is one of the adjacents of the parent
void Triangulation::manageAdjacent(Triangle* t1, Triangle* t2, Triangle* t3, Triangle& current_T)
{
    //set the first adjacent (we know this)
    t1->setAdj1(t2);
    //set the second adjacent (we know this)
    t1->setAdj2(t3);

    //it's necessary to update also the adjacency between the triangle t1 just created and the adjacent of
    //the current triangle (the "father" of the 3 triangles, that now is removed from the triangulation)
    updateAdjacent(current_T,t1);
}

//this method return true if the two triangles in input are adjacent, also return false
bool Triangulation::isAdjacent(Triangle& t1, Triangle& t2)
{
    //Check if the triangle t2 is adjacent to t1 on the edge AB

    if( (t1.getA()==t2.getA() && t1.getB()==t2.getB()) || (t1.getA()==t2.getB() && t1.getB()==t2.getA()) ||
        (t1.getA()==t2.getB() && t1.getB()==t2.getC()) || (t1.getA()==t2.getC() && t1.getB()==t2.getB()) ||
        (t1.getA()==t2.getC() && t1.getB()==t2.getA()) || (t1.getA()==t2.getA() && t1.getB()==t2.getC()))
    {
        return true;
    }

    //Check if the triangle t2 is adjacent to t1 on the edge BC

    if( (t1.getB()==t2.getA() && t1.getC()==t2.getB()) || (t1.getB()==t2.getB() && t1.getC()==t2.getA()) ||
        (t1.getB()==t2.getB() && t1.getC()==t2.getC()) || (t1.getB()==t2.getC() && t1.getC()==t2.getB()) ||
        (t1.getB()==t2.getC() && t1.getC()==t2.getA()) || (t1.getB()==t2.getA() && t1.getC()==t2.getC()))
    {
        return true;
    }

    //Check if the triangle t2 is adjacent to t1 on the edge CA

    if( (t1.getC()==t2.getA() && t1.getA()==t2.getB()) || (t1.getC()==t2.getB() && t1.getA()==t2.getA()) ||
        (t1.getC()==t2.getB() && t1.getA()==t2.getC()) || (t1.getC()==t2.getC() && t1.getA()==t2.getB()) ||
        (t1.getC()==t2.getC() && t1.getA()==t2.getA()) || (t1.getC()==t2.getA() && t1.getA()==t2.getC()))
    {
        return true;
    }


    //t1 and t2 are not adjacent
    return false;

}

//Method used to find the adjacent triangle of t, given two points pi and pj.
//This method is used when it's necessary to check if an edge is legal or not
Triangle* Triangulation::findAdjacent(const cg3::Point2Dd& pi, const cg3::Point2Dd& pj, Triangle& t)
{
        //Check the first adjacent of t
        if(t.getAdj1()!=nullptr)
        {
            //Check adjacent for AB-BA
            if( (*t.getAdj1()->getA()==pi && *t.getAdj1()->getB()==pj) || (*t.getAdj1()->getB()==pi && *t.getAdj1()->getA()==pj))
            {
                return t.getAdj1();
            }
            //Check adjacent for BC-CB
            if( (*t.getAdj1()->getB()==pi && *t.getAdj1()->getC()==pj) || (*t.getAdj1()->getC()==pi && *t.getAdj1()->getB()==pj))
            {
                return t.getAdj1();
            }
            //Check adjacent for CA-AC
            if( (*t.getAdj1()->getA()==pi && *t.getAdj1()->getC()==pj) || (*t.getAdj1()->getC()==pi && *t.getAdj1()->getA()==pj))
            {
                return t.getAdj1();
            }
        }

        //Check the second adjacent of t
        if(t.getAdj2()!=nullptr)
        {
            //Check adjacent for AB-BA
            if( (*t.getAdj2()->getA()==pi && *t.getAdj2()->getB()==pj) || (*t.getAdj2()->getB()==pi && *t.getAdj2()->getA()==pj))
            {
                return t.getAdj2();
            }
            //Check adjacent for BC-CB
            if( (*t.getAdj2()->getB()==pi && *t.getAdj2()->getC()==pj) || (*t.getAdj2()->getC()==pi && *t.getAdj2()->getB()==pj))
            {
                return t.getAdj2();
            }
            //Check adjacent for CA-AC
            if( (*t.getAdj2()->getA()==pi && *t.getAdj2()->getC()==pj) || (*t.getAdj2()->getC()==pi && *t.getAdj2()->getA()==pj))
            {
                return t.getAdj2();
            }
        }
        //Check the third adjacent of t
        if(t.getAdj3()!=nullptr)
        {
            //Check adjacent for AB-BA
            if( (*t.getAdj3()->getA()==pi && *t.getAdj3()->getB()==pj) || (*t.getAdj3()->getB()==pi && *t.getAdj3()->getA()==pj))
            {
                return t.getAdj3();
            }
            //Check adjacent for BC-CB
            if( (*t.getAdj3()->getB()==pi && *t.getAdj3()->getC()==pj) || (*t.getAdj3()->getC()==pi && *t.getAdj3()->getB()==pj))
            {
                return t.getAdj3();
            }
            //Check adjacent for CA-AC
            if( (*t.getAdj3()->getA()==pi && *t.getAdj3()->getC()==pj) || (*t.getAdj3()->getC()==pi && *t.getAdj3()->getA()==pj))
            {
                return t.getAdj3();
            }
        }

    // if the adjacents of t doesn't have the same points of pi and pj, t doesn't have useful adjavent, so we return a null pointer

    return nullptr;
}
