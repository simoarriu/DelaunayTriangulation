#ifndef LEGALIZEEDGE_H
#define LEGALIZEEDGE_H

#include <cg3/geometry/2d/utils2d.h>
#include <utils/delaunay_checker.h>
#include <data_structure/dag.h>
#include <data_structure/nodedag.h>
#include <data_structure/triangle.h>
#include <algorithms/delaunaytriangulationalgorithm.h>


class LegalizeEdge
{
public:
    LegalizeEdge();

    //Method used to check if an edge pipj is legal or not
    static void legalizeEdge(cg3::Point2Dd* input_point, cg3::Point2Dd* pi, cg3::Point2Dd* pj, Triangle& t, Triangulation& triangulation, Dag& dag);

};

#endif // LEGALIZEEDGE_H
