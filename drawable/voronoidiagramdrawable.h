#ifndef VORONOIDIAGRAMDRAWABLE_H
#define VORONOIDIAGRAMDRAWABLE_H

#include <cg3/viewer/interfaces/drawable_object.h>
#include <cg3/utilities/color.h>
#include <data_structure/triangle.h>

namespace cg3
{
    class VoronoiDiagramDrawable : public DrawableObject
    {
        public:
            VoronoiDiagramDrawable();

            // DrawableObject interface
            void draw() const;
            Pointd sceneCenter() const;
            double sceneRadius() const;

            //Set the vector of pointers of triangle from a given vector
            void importTriangle(std::vector<Triangle*> triangles);

            //Clear the vector of triangles
            void clearDiagramDrawable();

            //Compute the circumcircle of a triangle, that is the voronoi vertex
            Point2Dd computeCircumcircle(Point2Dd* A, Point2Dd* B, Point2Dd* C) const;


            //Mutable iterator for a const method used to scan the vector
            mutable std::vector<Triangle*>::const_iterator it;

            //Getter and setter for the state of the voronoi (on/off)
            bool getState();
            void setState(bool b);



    private:

        //Attributes used to draw points and edges
        int const pointSize = 6;
        int const lineSize = 2;
        Color const pointColor = Color(0,0,255);
        Color const lineColor = Color(0,0,255);

        //vector of pointers that contains the triangles to display
        std::vector<Triangle*> triangles;

        //boolean related to the state of the diagram
        bool state = false;




    };

}



#endif // VORONOIDIAGRAMDRAWABLE_H
