#ifndef DELAUNAYTRIANGULATIONALGORITHM_H
#define DELAUNAYTRIANGULATIONALGORITHM_H

#include <data_structure/triangle.h>
#include <data_structure/nodedag.h>
#include <utils/delaunay_checker.h>
#include <data_structure/triangulation.h>
#include <QFrame>

namespace cg3
{

class DelaunayTriangulationAlgorithm
{
    public:
        DelaunayTriangulationAlgorithm();    

        // Set the bounding triangle that will contains all the other points of the triangulation
        // The points are const because their value cannot change
        void boundingTriangle(const Point2Dd& p1, const Point2Dd& p2, const Point2Dd& p3);

        //Get the vector of triangles
        std::vector<Triangle*> getTriangles();

        //insert the point in input into the triangulation
        void fillTriangulation(const Point2Dd& input_point);

        //Clear the data structures used and delete the pointers
        void clearTriangulation();

        //Get the vector of points for the validation
        std::vector<cg3::Point2Dd> getPoints();

        //Get the matrix for the validation
        cg3::Array2D<unsigned int> getTrianglesValidation();

    private:

        //Triangulation composed by two vector: points and triangles
        Triangulation triangulation;

        //Dag composed by the vector of nodes
        Dag dag;

        //Map used to validate the triangulation: each pair is composed by a point and its index
        //in the vector of points
        std::map<Point2Dd,unsigned int> index_point;

        //Iterators used for the vector of triangles and points
        std::vector<Triangle*>::iterator it;
        std::vector<Point2Dd*>::iterator it_p;


};


}



#endif // DELAUNAYTRIANGULATIONALGORITHM_H
