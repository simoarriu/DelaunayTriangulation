#include "legalizeedge.h"
#include <algorithms/delaunaytriangulationalgorithm.h>
#include <data_structure/triangulation.h>


LegalizeEdge::LegalizeEdge()
{

}

//this method is used to legalize the new edge: input point, pi and pj are the points of the triangle t, we have as parameters also
//the triangulation and the dag for some updates
void LegalizeEdge::legalizeEdge(cg3::Point2Dd* input_point, cg3::Point2Dd* pi, cg3::Point2Dd* pj, Triangle& t,Triangulation& triangulation, Dag& dag)
{
    //first, it's necessary to find the adjacent triangle of t, considering the two points pi and pj
    Triangle* adj_Triangle = Triangulation::findAdjacent(*pi,*pj,t);

    //If the triangle t has an adjacent
    if(adj_Triangle!=nullptr)
    {
        // Get the third point pf: point used to check if pipj is an illegal edge or not
        cg3::Point2Dd* pf = adj_Triangle->getMissingPoint(*pi,*pj);

        //if the point pf lies inside the circle built by the input point, pi and pj, so pipj is an illegal edge
        if(DelaunayTriangulation::Checker::isPointLyingInCircle(*input_point,*pi,*pj,*pf,false))
        {
            //We set the triangle t and its adjacent as triangle to "remove", because they now
            //are replaced by their children
            //T and adj_Triangle are the two parents of the two new nodes
            t.setRemoveTriangle(true);
            adj_Triangle->setRemoveTriangle(true);

            //Get the node of the dag belonging to the two triangles
            NodeDag* currentNode = t.getNodeDag();
            NodeDag* adjacentNode = adj_Triangle->getNodeDag();

            //Manage the adjcent to remove the pointer related to t and the adjacent triangle
            Triangulation::removePointerAdjacent(t);
            Triangulation::removePointerAdjacent(*adj_Triangle);

            //Create and add the two new triangles and the two new nodes to the triangulation and the dag
            triangulation.addToTriangulation(input_point,pi,pf);
            dag.addToDagAfterFlip(triangulation.getBack(),*currentNode,*adjacentNode);
            triangulation.addToTriangulation(input_point,pf,pj);
            dag.addToDagAfterFlip(triangulation.getBack(),*currentNode,*adjacentNode);

            //Get the index of the triangles just created from the triangulation
            unsigned long idx_1 = triangulation.getTrianglesSize()-2;
            unsigned long idx_2 = triangulation.getTrianglesSize()-1;

            //The two new triangles created by the edge flip are adjacent between them, so we set this relationship
            triangulation.getTriangleAt(idx_1)->setAdj1(triangulation.getTriangleAt(idx_2));
            triangulation.getTriangleAt(idx_2)->setAdj1(triangulation.getTriangleAt(idx_1));

            //We need to update the adjacent of the new triangles and the previous triangles, because now
            // t and the adjacent don't "exists" in the triangulation
            Triangulation::updateAdjacentEdgeFlip(t,triangulation.getTriangleAt(idx_1),*adj_Triangle);
            Triangulation::updateAdjacentEdgeFlip(t,triangulation.getTriangleAt(idx_2),*adj_Triangle);

            //Legalize the new edge created by the 2 new triangles
            legalizeEdge(triangulation.getTriangleAt(idx_1)->getA(),triangulation.getTriangleAt(idx_1)->getB(),triangulation.getTriangleAt(idx_1)->getC(),*triangulation.getTriangleAt(idx_1),triangulation,dag);
            legalizeEdge(triangulation.getTriangleAt(idx_2)->getA(),triangulation.getTriangleAt(idx_2)->getB(),triangulation.getTriangleAt(idx_2)->getC(),*triangulation.getTriangleAt(idx_2),triangulation,dag);

        }


    }


}
