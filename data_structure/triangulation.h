#ifndef TRIANGULATION_H
#define TRIANGULATION_H

#include <cg3/geometry/2d/point2d.h>
#include <data_structure/triangle.h>
#include <data_structure/dag.h>


class Triangulation
{
    public:
        Triangulation();

        //Get the vector of pointers of triangles
        std::vector<Triangle*> getTriangles() const;

        //Get the vector of pointers of points
        std::vector<cg3::Point2Dd*> getPoints();

        //Add pointer of point and triangle to the related vectors
        void addPoint(cg3::Point2Dd* point);
        void addPoint(const cg3::Point2Dd& point);
        void addTriangle(Triangle* t);

        //clear the two vectors
        void clearPoints();
        void clearTriangles();

        //Return the triangle and the point from the vectors given an index
        Triangle* getTriangleAt(unsigned long i);
        cg3::Point2Dd* getPointAt(unsigned long i);

        //Get the size of the vector
        unsigned long getTrianglesSize();

        //Get the last triangle and the last point of the vector
        Triangle* getBack();
        cg3::Point2Dd* getBackP();

        //Get the first and last iterators for the vector of triangles
        std::vector<Triangle*>::iterator getBeginT();
        std::vector<Triangle*>::iterator getEndT();

        //Get the first and last iterators for the vector of points
        std::vector<cg3::Point2Dd*>::iterator getBeginP();
        std::vector<cg3::Point2Dd*>::iterator getEndP();

        //Delete the pointers of the two vectors
        void deletePointersPoints();
        void deletePointersTriangles();

        //Create the triangle and add it to the vector of triangles
        void addToTriangulation(cg3::Point2Dd* A, cg3::Point2Dd* B, cg3::Point2Dd* C);

        //Methods used to manage the adjacency
        static void removePointerAdjacent(Triangle& t);
        static void updateAdjacent(Triangle& current_T, Triangle* t);
        static void updateAdjacentEdgeFlip(Triangle& current_T, Triangle* t, Triangle& adj_T);
        static void manageAdjacent(Triangle* t1, Triangle* t2, Triangle* t3, Triangle& current_T);
        static void deletePointer(Triangle& t, Triangle& t_adj);
        static void updateAdj(Triangle* t_adj,Triangle* t);
        static bool isAdjacent(Triangle& t1, Triangle& t2);
        static void updateEdgeFlipCurrentT(Triangle* adj_current_T, Triangle* t, Triangle& adj_T,Triangle& current_T,bool flag);
        static Triangle* findAdjacent(const cg3::Point2Dd& pi, const cg3::Point2Dd& pj, Triangle& t);


    private:
        //Vector of pointers of points
        std::vector<cg3::Point2Dd*> points;

        // vector of poiners Triangles of the triangulation
        std::vector<Triangle*> triangles;

        //Iterators for the vectors of points and triangles
        std::vector<cg3::Point2Dd*>::iterator it_p;
        std::vector<Triangle*>::iterator it_t;



};

#endif // TRIANGULATION_H
