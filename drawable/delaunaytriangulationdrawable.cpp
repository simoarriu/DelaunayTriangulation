#include "delaunaytriangulationdrawable.h"
#include <cg3/viewer/renderable_objects/2d/renderable_objects2d.h>

const cg3::Point2Dd BT_P1(1e+10, 0);
const cg3::Point2Dd BT_P2(0, 1e+10);
const cg3::Point2Dd BT_P3(-1e+10, -1e+10);

namespace cg3
{
    DelaunayTriangulationDrawable::DelaunayTriangulationDrawable()
    {

    }

    //Method used to draw the triangulation
    void DelaunayTriangulationDrawable::draw() const
    {
        //If visibile = true, the bounding triangle is visibile,
        //and we draw the whole triangulation,otherwise the other
        //method draw only the triangulation without the bounding triangle
        if(this->visible)
            drawBoundingVisible();
        else
            drawBoundingInvisible();
    }

    Pointd DelaunayTriangulationDrawable::sceneCenter() const
    {
        Pointd c = Pointd(0, 0);
        return c;
    }

    double DelaunayTriangulationDrawable::sceneRadius() const
    {
        Pointd c = Pointd(0, 0);
        return c.dist(c);
    }

    //Given a vector of triangles, we set the vector of the drawable to draw the triangulation
    void DelaunayTriangulationDrawable::importTriangle(std::vector<Triangle*> triangles)
    {
        this->triangles = triangles;

    }

    //clear the vector of triangles
    void DelaunayTriangulationDrawable::clearTrianglesDrawable()
    {
        this->triangles.clear();
    }

    //Set the visibility of the bounding triangle, given a boolean parameter
    void DelaunayTriangulationDrawable::visibilityBoundingTriangle(const bool visible)
    {
        if(visible)
            this->visible=visible;
        else
            this->visible=visible;
    }

    //Draw the triangulation with the bounding triangle. With an interator, we scan the vector of triangles
    //and we draw only the triangles useful for the triangulation
    void DelaunayTriangulationDrawable::drawBoundingVisible() const
    {
        for(it=this->triangles.begin(); it != this->triangles.end(); it++)
        {
            if(!(*it)->getRemoveTriangle())
            {
                // Draw verticies (dereference)
                viewer::drawPoint2D(*(*it)->getA(), this->pointColor, this->pointSize);
                viewer::drawPoint2D(*(*it)->getB(), this->pointColor, this->pointSize);
                viewer::drawPoint2D(*(*it)->getC(), this->pointColor, this->pointSize);

                // Draw triangle (dereference)
                viewer::drawTriangle2D(*(*it)->getA(), *(*it)->getB(), *(*it)->getC(),this->lineColor,this->lineSize,false);

            }

        }
    }


    //Draw the triangulation without the bounding triangle. With an interator, we scan the vector of triangles
    //and we draw only the triangles useful for the triangulation
    void DelaunayTriangulationDrawable::drawBoundingInvisible() const
    {
        for(it = this->triangles.begin(); it != this->triangles.end(); it++)
        {

            if(!(*it)->getRemoveTriangle())
            {
                // Verticies (dereference)
                //Draw a point only if it not belonging to one of the bounding triangles's points
                if((*(*it)->getA()!=BT_P1)&&(*(*it)->getA()!=BT_P2)&&(*(*it)->getA()!=BT_P3))
                    viewer::drawPoint2D(*(*it)->getA(), this->pointColor, this->pointSize);
                if((*(*it)->getB()!=BT_P1)&&(*(*it)->getB()!=BT_P2)&&(*(*it)->getB()!=BT_P3))
                    viewer::drawPoint2D(*(*it)->getB(), this->pointColor, this->pointSize);
                if((*(*it)->getC()!=BT_P1)&&(*(*it)->getC()!=BT_P2)&&(*(*it)->getC()!=BT_P3))
                    viewer::drawPoint2D(*(*it)->getC(), this->pointColor, this->pointSize);

                // Triangles (dereference)
                // Draw a triangle only if it not belonging to the bounding triangle
                if(((*(*it)->getA()!=BT_P1)&&(*(*it)->getA()!=BT_P2)&&(*(*it)->getA()!=BT_P3))&&
                   ((*(*it)->getB()!=BT_P1)&&(*(*it)->getB()!=BT_P2)&&(*(*it)->getB()!=BT_P3))&&
                    (*(*it)->getC()!=BT_P1)&&(*(*it)->getC()!=BT_P2)&&(*(*it)->getC()!=BT_P3))
                     viewer::drawTriangle2D(*(*it)->getA(), *(*it)->getB(), *(*it)->getC(),this->lineColor,this->lineSize,false);
           }

        }
    }

}






