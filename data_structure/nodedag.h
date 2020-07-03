#ifndef NODEDAG_H
#define NODEDAG_H

#include <cg3/geometry/2d/point2d.h>

class Triangle;


class NodeDag
{
    public:
        NodeDag();
        NodeDag(Triangle* triangle);
        NodeDag(NodeDag& node);
        ~NodeDag();

        //Getter and Setter triangle of the node
        Triangle* getTriangle();
        void setTriangle(Triangle* triangle);

        //Getter and Setter first, second and third child of the node
        NodeDag* getFirstChild();
        NodeDag* getSecondChild();
        NodeDag* getThirdChild();

        void setFirstChild(NodeDag* firstChild);
        void setSecondChild(NodeDag* secondChild);
        void setThirdChild(NodeDag* thirdChild);

        //Getter for the triangle of the first, second and third child
        Triangle* getFirstChildTriangle();
        Triangle* getSecondChildTriangle();
        Triangle* getThirdChildTriangle();

    private:
        Triangle* triangle; //pointer to the triangle of the node
        NodeDag* firstChild = nullptr; //pointer to the first child
        NodeDag* secondChild = nullptr; //pointer to the second child
        NodeDag* thirdChild = nullptr; //pointer to the third child


};

#endif // NODEDAG_H



