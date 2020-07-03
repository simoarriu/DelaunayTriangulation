#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <cg3/geometry/2d/point2d.h>
#include <iostream>

class NodeDag;


class Triangle
{
    public:
        Triangle();
        Triangle(cg3::Point2Dd* A, cg3::Point2Dd* B, cg3::Point2Dd* C);
        Triangle(Triangle& t);
        ~Triangle();


        //Getter points triangle
        cg3::Point2Dd* getA();
        cg3::Point2Dd* getB();
        cg3::Point2Dd* getC();

        //Setter points triangle
        void setA(cg3::Point2Dd* A);
        void setB(cg3::Point2Dd* B);
        void setC(cg3::Point2Dd* C);

        //Getter dag node
        NodeDag* getNodeDag();

        //Setter dag node
        void setNodeDag(NodeDag* node_Dag);

        //return the third point of the triangle given 2 points
        cg3::Point2Dd* getMissingPoint(const cg3::Point2Dd& p1, const cg3::Point2Dd& p2);

        //Compare "this" triangle to another one given as parameter
        bool equalsTo(Triangle& t);

        //Get and set for the adjacents of the triangles
        Triangle* getAdj1();
        Triangle* getAdj2();
        Triangle* getAdj3();

        void setAdj1(Triangle* t);
        void setAdj2(Triangle* t);
        void setAdj3(Triangle* t);

        //Get and set for the state of the triangle
        void setRemoveTriangle(bool b);
        bool getRemoveTriangle();


    private:
        cg3::Point2Dd* A; //Pointer to the first point of the triangle
        cg3::Point2Dd* B; //Pointer to the second point of the triangle
        cg3::Point2Dd* C; //Pointer to the third point of the triangle

        //boolean used to know if a triangle must be considered or not when
        //it's necessary to draw the triangulation or if we need to check the triangulation
        bool removeTriangle = false;

        //Pointers related to the adjecents of a triangle: a triangle can have
        //at most three adjacents
        Triangle* adj1 = nullptr;
        Triangle* adj2 = nullptr;
        Triangle* adj3 = nullptr;

        NodeDag* node_Dag = nullptr; //Pointer to the related node of the triangle




};

#endif // TRIANGLE_H
