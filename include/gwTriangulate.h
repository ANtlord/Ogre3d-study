#include <iostream>
#include <vector>
namespace GW {

/*
 * Method return false if point makes up triangle, which intersects existing
 * triangle, else true. Point "d" is new point. Point "c" is point for
 * checking.
 */
bool checkPoint(const double &x_a, const double &y_a,  const double &x_b,
        const double &y_b, const double &x_c, const double &y_c,
        const double &x_d, const double &y_d);

/******************************************************************************
 *
 * Purpose:
 *
 *   POINTS_DELAUNAY_NAIVE_2D computes the Delaunay triangulation in 2D.
 *
 * Discussion:
 *
 *   A naive and inefficient (but extremely simple) method is used.
 *
 *   This routine is only suitable as a demonstration code for small
 *   problems.  Its running time is of order NODE_NUM^4.  Much faster
 *   algorithms are available.
 *
 *   Given a set of nodes in the plane, a triangulation is a set of
 *   triples of distinct nodes, forming triangles, so that every
 *   point with the convex hull of the set of  nodes is either one
 *   of the nodes, or lies on an edge of one or more triangles,
 *   or lies within exactly one triangle.
 *
 *   The number of nodes must be at least 3.
 *
 * Licensing:
 *
 *   This code is distributed under the GNU LGPL license.
 *
 * Modified:
 *
 *   13 June 2005
 *
 * Author:
 *
 *   John Burkardt
 *
 * Reference:
 *
 *   Joseph ORourke,
 *   Computational Geometry,
 *   Cambridge University Press,
 *   Second Edition, 1998, page 187.
 *
 * Parameters:
 *
 *   Input, int NODE_NUM, the number of nodes.
 *
 *   Input, double NODE_XY[2*NODE_NUM], the coordinates of the nodes.
 *
 *   Output, int *TRIANGLE_NUM, the number of triangles.
 *
 *   Output, int POINTS_DELAUNAY_NAIVE_2D[3*TRIANGLE_NUM], the indices of the
 *   nodes making each triangle.
 *
 */
std::vector <int*> points_delaunay_naive_2d(int node_num, double node_xy[],
        int *triangle_num);


std::vector <int*> points_delaunay_naive_2d(int node_num, float node_xy[],
        int *triangle_num);
};
