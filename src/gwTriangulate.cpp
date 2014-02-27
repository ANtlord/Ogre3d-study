#include "../include/gwTriangulate.h"
using namespace std;

namespace GW {

bool checkPoint(const double &x_a, const double &y_a,  const double &x_b,
        const double &y_b, const double &x_c, const double &y_c,
        const double &x_d, const double &y_d)
{
    return false;
    // If a and b points makes up vertical line, then new and checking points
    // must be on different sites.
    if (y_a==y_b && (y_d<y_a != y_c<y_a)) return true;
    // Similary for horizontal line.
    if (x_a==x_b && (x_d<x_a != x_c<x_a)) return true;
    // For diagonal line.
    const int K = (y_a / x_a);
    if (y_d<K*x_d != y_c<K*x_c) return true;
    return false;
}

vector <int*> points_delaunay_naive_2d(int node_num, double node_xy[], int *triangle_num)
{
    int count;
    int flag = false;
    int i;
    int j;
    int k;
    int m;
    int pass;
    vector <int*> tri;
    double xn;
    double yn;
    double zn;
    double *z;

    count = 0;

    z = new double [ node_num ];

    for ( i = 0; i < node_num; i++ ) {
        // z_i = (x_i)^2 + (y_i)^2
        // z_i is length from intersection of the axes of coordinates.
        z[i] = node_xy[0+i*2] * node_xy[0+i*2] + node_xy[1+i*2] * node_xy[1+i*2];
    }
//
//  First pass counts triangles,
//  Second pass allocates triangles and sets them.
//
    for ( pass = 1; pass <= 2; pass++ ) {
        //if ( pass == 2 ) {
          //tri = new int[3*count];
        //}
        count = 0;
        //
        //  For each triple (I,J,K):
        //
        for ( i = 0; i < node_num - 2; i++ ) {
            for ( j = i+1; j < node_num; j++ ) {
                for ( k = i+1; k < node_num; k++ ) {
                    if ( j != k ) {
                        xn = ( node_xy[1+j*2] - node_xy[1+i*2] ) * ( z[k] - z[i] )
                           - ( node_xy[1+k*2] - node_xy[1+i*2] ) * ( z[j] - z[i] );
                        yn = ( node_xy[0+k*2] - node_xy[0+i*2] ) * ( z[j] - z[i] )
                           - ( node_xy[0+j*2] - node_xy[0+i*2] ) * ( z[k] - z[i] );

                        zn = ( node_xy[0+j*2] - node_xy[0+i*2] )
                           * ( node_xy[1+k*2] - node_xy[1+i*2] )
                           - ( node_xy[0+k*2] - node_xy[0+i*2] )
                           * ( node_xy[1+j*2] - node_xy[1+i*2] );

                        flag = ( zn < 0 );

                        if ( flag ) {
                            for ( m = 0; m < node_num; m++ ) {
                                flag = flag && ( ( node_xy[0+m*2] - node_xy[0+i*2] ) * xn
                                       + ( node_xy[1+m*2] - node_xy[1+i*2] ) * yn
                                       + ( z[m] - z[i] ) * zn <= 0 );
                            }
                        }

                        if ( flag ) {
                          if ( pass == 2 ) {
                            bool isNotNewTriangle=false;
                            for (int c = 0; c < tri.size(); ++c) {
                                isNotNewTriangle = false;
                                bool c1 = k==tri[c][0] && j==tri[c][1];
                                bool c2 = k==tri[c][0] && i==tri[c][2];
                                bool c3 = j==tri[c][0] && i==tri[c][2];
                                // If 2 of 3 indices was saved, that check
                                // coordinates of third point.
                                if (c1){
                                    isNotNewTriangle = checkPoint(
                                            node_xy[0+k*2], node_xy[1+k*2],
                                            node_xy[0+j*2], node_xy[1+j*2],
                                            node_xy[0+tri[c][2]*2], node_xy[1+tri[c][2]*2],
                                            node_xy[0+i*2], node_xy[1+i*2]
                                            );
                                }
                                else if (c2){
                                    isNotNewTriangle = checkPoint(
                                            node_xy[0+k*2], node_xy[1+k*2],
                                            node_xy[0+i*2], node_xy[1+i*2],
                                            node_xy[0+tri[c][1]*2], node_xy[1+tri[c][1]*2],
                                            node_xy[0+j*2], node_xy[1+j*2]
                                            );
                                }
                                else if (c3){
                                    isNotNewTriangle = checkPoint(
                                            node_xy[0+i*2], node_xy[1+i*2],
                                            node_xy[0+j*2], node_xy[1+j*2],
                                            node_xy[0+tri[c][0]*2], node_xy[1+tri[c][0]*2],
                                            node_xy[0+k*2], node_xy[1+k*2]
                                            );
                                }
                            }
                            if (isNotNewTriangle == false){
                                int * indices = new int[3];
                                indices[0] = k;
                                indices[1] = j;
                                indices[2] = i;
                                tri.push_back(indices);
                            }
                          }
                          count = count + 1;
                        }                           
                    //} [> endif <]
                    } /* endif */
                } /* endfor */
            } /* endfor */
        } /* endfor */
    }

  *triangle_num = count;
  delete [] z;

  return tri;
}

vector <int*> points_delaunay_naive_2d(int node_num, float node_xy[], int *triangle_num)
{
    double new_node_xy[2*node_num];
    for (int i = 0; i < 2*node_num; i++) {
        new_node_xy[i] = (double)node_xy[i];
    }
    return points_delaunay_naive_2d(node_num, new_node_xy, triangle_num);
}

};
