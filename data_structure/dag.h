#ifndef DAG_H
#define DAG_H

#include <data_structure/triangle.h>
#include <data_structure/nodedag.h>


class Dag
{
    public:
        Dag();

        //create and push back the node to the vector given as parameter a pointer to the triangle
        void createAndAddNode(Triangle* t);

        //return the vector of pointers of nodes
        std::vector<NodeDag*> getNodes();

        //getter for the first and the last node of the vector
        NodeDag* getBack();
        NodeDag* getFront();

        //Clear the vector
        void clearNodes();

        //Delete the pointers of the vector
        void deletePointersNodes();

        //Given a point and the first node of the vector (the parent),
        //the method return the node where the point lies
        static NodeDag* findNode(NodeDag* nodesDag,const cg3::Point2Dd& p);

        //Add the node given the triangle as parameter to the vector and set
        //the childrens of the node
        void addToDag(Triangle* t, NodeDag& currentNode);

        //Like the previous method, but this is used for the edge flip
        void addToDagAfterFlip(Triangle* t, NodeDag& currentNode,NodeDag& adjNode);


    private:

        // vector of pointers that contains the nodes of the dag
        std::vector<NodeDag*> nodesDag;

        // iterator for the vector
        std::vector<NodeDag*>::iterator it_n;
};

#endif // DAG_H
