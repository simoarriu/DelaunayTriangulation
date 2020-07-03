#include "voronoidiagramdrawable.h"
#include <cg3/viewer/renderable_objects/2d/renderable_objects2d.h>


namespace cg3
{
    VoronoiDiagramDrawable::VoronoiDiagramDrawable()
    {

    }

    //Method used to draw the voronoi diagram. We scan the vector of triangles, and we draw only
    //the useful triangles, it's necessary to compute the circumcircle of each triangle, and connect
    //it to the other adjacent circumcircle
    void VoronoiDiagramDrawable::draw() const
    {
        for(it=this->triangles.begin(); it != this->triangles.end(); it++)
        {
            if(!(*it)->getRemoveTriangle())
            {
                //Draw the circumcircle of the triangle, that is the vertex of voronoi
                Point2Dd voronoi_vertex = VoronoiDiagramDrawable::computeCircumcircle((*it)->getA(),(*it)->getB(),(*it)->getC());
                viewer::drawPoint2D(voronoi_vertex, this->pointColor, this->pointSize);

                //the edges of the voronoi diagram are the link between the circumcircles of two adjacent triangles,
                //so if the current triangles has some adjacents, we connenct their circumcircles
                if((*it)->getAdj1()!=nullptr)
                {
                    Point2Dd voronoi_vertex_adj = VoronoiDiagramDrawable::computeCircumcircle((*it)->getAdj1()->getA(),(*it)->getAdj1()->getB(),(*it)->getAdj1()->getC());
                    viewer::drawLine2D(voronoi_vertex,voronoi_vertex_adj,this->lineColor,this->lineSize);
                }

                if((*it)->getAdj2()!=nullptr)
                {
                    Point2Dd voronoi_vertex_adj = VoronoiDiagramDrawable::computeCircumcircle((*it)->getAdj2()->getA(),(*it)->getAdj2()->getB(),(*it)->getAdj2()->getC());
                    viewer::drawLine2D(voronoi_vertex,voronoi_vertex_adj,this->lineColor,this->lineSize);
                }

                if((*it)->getAdj3()!=nullptr)
                {
                    Point2Dd voronoi_vertex_adj = VoronoiDiagramDrawable::computeCircumcircle((*it)->getAdj3()->getA(),(*it)->getAdj3()->getB(),(*it)->getAdj3()->getC());
                    viewer::drawLine2D(voronoi_vertex,voronoi_vertex_adj,this->lineColor,this->lineSize);
                }
            }

        }

    }

    Pointd VoronoiDiagramDrawable::sceneCenter() const
    {
        Pointd c = Pointd(0, 0);
        return c;
    }

    double VoronoiDiagramDrawable::sceneRadius() const
    {

        Pointd c = Pointd(0, 0);
        return c.dist(c);
    }

    //Import the vector given as parameter and set it in the voronoi attribute
    void VoronoiDiagramDrawable::importTriangle(std::vector<Triangle*> triangles)
    {
        this->triangles = triangles;

    }

    //Clear the vector of triangles
    void VoronoiDiagramDrawable::clearDiagramDrawable()
    {
        this->triangles.clear();
    }

    // https://www.ics.uci.edu/~eppstein/junkyard/circumcenter.html
    //Compute the circumcircle of a triangle, given 3 points
    Point2Dd VoronoiDiagramDrawable::computeCircumcircle(Point2Dd* A, Point2Dd* B, Point2Dd* C) const
    {
        double D = 2*((A->y()*C->x())+(B->y()*A->x())-(B->y()*C->x())-(A->y()*B->x())-(C->y()*A->x())+(C->y()*B->x()));


        double circum_x = ((B->y()*(pow(A->x(),2)))-(C->y()*(pow(A->x(),2)))-((pow(B->y(),2))*A->y())+((pow(C->y(),2))*A->y())+((pow(B->x(),2))*C->y())
                         +((pow(A->y(),2))*B->y())+((pow(C->x(),2))*A->y())-((pow(C->y(),2))*B->y())-((pow(C->x(),2))*B->y())-((pow(B->x(),2))*A->y())+((pow(B->y(),2))*C->y())-((pow(A->y(),2))*C->y()))/D;


        double circum_y = ((C->x()*(pow(A->x(),2)))+(C->x()*(pow(A->y(),2)))+((pow(B->x(),2))*A->x())-((pow(B->x(),2))*C->x())+((pow(B->y(),2))*A->x())
                           -((pow(B->y(),2))*C->x())-((pow(A->x(),2))*B->x())-((pow(A->y(),2))*B->x())-((pow(C->x(),2))*A->x())+((pow(C->x(),2))*B->x())-((pow(C->y(),2))*A->x())+((pow(C->y(),2))*B->x()))/D;


        return Point2Dd(circum_x, circum_y);



    }

    //Getter and setter for the state of the voronoi diagram
    bool VoronoiDiagramDrawable::getState()
    {
        return this->state;
    }

    void VoronoiDiagramDrawable::setState(bool b)
    {
        this->state=b;
    }


}
