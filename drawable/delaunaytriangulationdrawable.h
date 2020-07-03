#ifndef DELAUNAYTRIANGULATIONDRAWABLE_H
#define DELAUNAYTRIANGULATIONDRAWABLE_H

#include <cg3/viewer/interfaces/drawable_object.h>
#include <cg3/utilities/color.h>
#include <data_structure/triangle.h>


namespace cg3
{

class DelaunayTriangulationDrawable : public DrawableObject
{

    public:
        DelaunayTriangulationDrawable();

        // DrawableObject interface
        void draw() const;
        Pointd sceneCenter() const;
        double sceneRadius() const;

        //Import the vector of pointers of triangles from the triangulation
        void importTriangle(std::vector<Triangle*> triangles);

        //Clear the vector
        void clearTrianglesDrawable();

        //Set the visibility of the bounding triangle
        void visibilityBoundingTriangle(const bool visible);

        //Mutable iterator for a const method used to scan the vector
        mutable std::vector<Triangle*>::const_iterator it;

        //Method to handle two cases: bounding trinagle on/off
        void drawBoundingVisible() const;
        void drawBoundingInvisible() const;

   private:
        //Attributes used to draw
        int const pointSize = 3;
        int const lineSize = 1;
        Color const pointColor = Color(255,0,0);
        Color const lineColor = Color(0,0,0);

        //Boolean for the bounding triangle
        bool visible = false;

        //vector that contains the pointers to the triangles to draw
        std::vector<Triangle*> triangles;




};
}

#endif // DELAUNAYTRAINGULATIONDRAWABLE_H
