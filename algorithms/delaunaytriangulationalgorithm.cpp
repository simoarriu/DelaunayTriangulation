
#include "delaunaytriangulationalgorithm.h"
#include <iostream>
#include <cg3/geometry/2d/utils2d.h>
#include <data_structure/dag.h>
#include <algorithms/legalizeedge.h>

cg3::DelaunayTriangulationAlgorithm::DelaunayTriangulationAlgorithm()
{

}


//This method is used to set the bouding Triangle, composed by the 3 const point
void cg3::DelaunayTriangulationAlgorithm::boundingTriangle(const Point2Dd& p1, const Point2Dd& p2, const Point2Dd& p3)
{
    // Add the points of the bouding triangle to the triangulation
    triangulation.addPoint(p1);
    triangulation.addPoint(p2);
    triangulation.addPoint(p3);

    // Add the bounding triangle to the vector of triangle belonging to the triangulation
    //getPointAt return the point in the vector given an index
    triangulation.addToTriangulation(triangulation.getPointAt(0),triangulation.getPointAt(1),triangulation.getPointAt(2));

    // Add the dag node to the vector of the nodes related to the triangle just created
    dag.createAndAddNode(triangulation.getBack());

    // Set the dag node of the triangle just created
    triangulation.getBack()->setNodeDag(dag.getBack());
}

//Method used to return the vector of pointers of triangles that composed the triangulation
std::vector<Triangle*> cg3::DelaunayTriangulationAlgorithm::getTriangles()
{
    return this->triangulation.getTriangles();
}

//Given a point in input, this method insert the point in the triangulation in an iterative way
void cg3::DelaunayTriangulationAlgorithm::fillTriangulation(const Point2Dd& input_point)
{        
          // Get the pointer to the node of the dag containing the point in input
          // First parameter is the first node of the dag (the root of the dag)
          // Second parameter is the point in input
          NodeDag* currentNode = Dag::findNode(dag.getFront(),input_point);

          // Now we have the triangle where the point lie
          Triangle* currentTriangle = currentNode->getTriangle();

          //check if a point already exists (the input point is equal to at least one vertex of the triangle where it lies)
          //If the point already exists it isn't considered
          if(!((input_point.operator==(*currentTriangle->getA()))||(input_point.operator==(*currentTriangle->getB()))||(input_point.operator==(*currentTriangle->getC()))))
          {
              //Add the point to the vector of pointer of points belonging to the triangulation
              triangulation.addPoint(input_point);

              //The current triangle is set to true, because now this triangles is composed by 3 new triangles, and we don't
              //need to draw this triangle in the triangulation
              currentTriangle->setRemoveTriangle(true);

              //Remove the pointer belonging to this triangle from its adjacents, because now this triangle is no longer
              //belonging to the triangulation, so we need to remove it also in the other adjacents
              Triangulation::removePointerAdjacent(*currentTriangle);

              //Create the 3 new triangles and the related 3 node and add them to the triangulation and to the dag
              triangulation.addToTriangulation(triangulation.getBackP(),currentTriangle->getA(),currentTriangle->getB());
              dag.addToDag(triangulation.getBack(),*currentNode);
              triangulation.addToTriangulation(triangulation.getBackP(),currentTriangle->getB(),currentTriangle->getC());
              dag.addToDag(triangulation.getBack(),*currentNode);
              triangulation.addToTriangulation(triangulation.getBackP(),currentTriangle->getC(),currentTriangle->getA());
              dag.addToDag(triangulation.getBack(),*currentNode);

              //Get the index of the 3 triangles just created from the triangulation
              unsigned long idx_1 = triangulation.getTrianglesSize()-3;
              unsigned long idx_2 = triangulation.getTrianglesSize()-2;
              unsigned long idx_3 = triangulation.getTrianglesSize()-1;

              //Manage the adjacent of the 3 new triangles and with the other adjacent of the current triangle (the parent)
              Triangulation::manageAdjacent(triangulation.getTriangleAt(idx_1),triangulation.getTriangleAt(idx_2),triangulation.getTriangleAt(idx_3),*currentTriangle);
              Triangulation::manageAdjacent(triangulation.getTriangleAt(idx_2),triangulation.getTriangleAt(idx_1),triangulation.getTriangleAt(idx_3),*currentTriangle);
              Triangulation::manageAdjacent(triangulation.getTriangleAt(idx_3),triangulation.getTriangleAt(idx_1),triangulation.getTriangleAt(idx_2),*currentTriangle);

              //Legalize the new edge just created from the three new triangles
              LegalizeEdge::legalizeEdge(triangulation.getTriangleAt(idx_1)->getA(),triangulation.getTriangleAt(idx_1)->getB(),triangulation.getTriangleAt(idx_1)->getC(),*triangulation.getTriangleAt(idx_1),triangulation,dag);
              LegalizeEdge::legalizeEdge(triangulation.getTriangleAt(idx_2)->getA(),triangulation.getTriangleAt(idx_2)->getB(),triangulation.getTriangleAt(idx_2)->getC(),*triangulation.getTriangleAt(idx_2),triangulation,dag);
              LegalizeEdge::legalizeEdge(triangulation.getTriangleAt(idx_3)->getA(),triangulation.getTriangleAt(idx_3)->getB(),triangulation.getTriangleAt(idx_3)->getC(),*triangulation.getTriangleAt(idx_3),triangulation,dag);

          }
}


//Clear the triangulation, the dag and other data structures
void cg3::DelaunayTriangulationAlgorithm::clearTriangulation()
{
    //Delete the pointers in the used vectors
    triangulation.deletePointersPoints();
    triangulation.deletePointersTriangles();
    dag.deletePointersNodes();
    //Clear the vectors
    triangulation.clearPoints();
    triangulation.clearTriangles();
    dag.clearNodes();
    //Clear the map for the validation
    index_point.clear();

}

//Method used to get the vector of points for the validation
std::vector<cg3::Point2Dd> cg3::DelaunayTriangulationAlgorithm::getPoints()
{
    std::vector<Point2Dd> vec_point_validation;
    unsigned int i = 0;

    //Scan the vector of points to fill the index_point map: it is composed by
    //a point and its index in the vector of points
    for(it_p=triangulation.getBeginP();it_p != triangulation.getEndP();it_p++,i++)
    {
        //It's necessary to de-reference the pointers related to the points
        vec_point_validation.push_back(*(*it_p));
        //Insert into the map the pair composed by the current point and its index i
        index_point.insert(std::pair<Point2Dd,unsigned int>(*(*it_p),i));
    }

    //Return the vector of points without pointers
    return vec_point_validation;
}

//Method used to get an array2D for the validation
cg3::Array2D<unsigned int> cg3::DelaunayTriangulationAlgorithm::getTrianglesValidation()
{
    Array2D<unsigned int> triangles_validation;
    triangles_validation.resize(getTriangles().size(),3); //it's necessary to resize also this matrix
    unsigned int i = 0;

    // For each triangle and for the three columns, insert the related index to the three point that composed
    //the triangle, A, B and C
    for(it=triangulation.getBeginT();it != triangulation.getEndT();it++,i++)
    {
        if(!(*it)->getRemoveTriangle())
        {
            //Find the index of the points A,B,C of the current triangle in the map
            triangles_validation(i, 0) = index_point.find(*(*it)->getA())->second;
            triangles_validation(i, 1) = index_point.find(*(*it)->getB())->second;
            triangles_validation(i, 2) = index_point.find(*(*it)->getC())->second;
        }

    }

    //return the matrix
    return triangles_validation;
}
