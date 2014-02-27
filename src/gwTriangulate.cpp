#include "../include/gwTriangulate.h"
using namespace std;

namespace GW {

bool checkPoint(const double &x_a, const double &y_a,  const double &x_b,
        const double &y_b, const double &x_c, const double &y_c,
        const double &x_d, const double &y_d)
{
    // Move triangles to intersector of x-axis and y-axis for avoiding 
    // constant b in linear equalization (y = kx + b)
    const double X_DIFF = -x_a;
    const double Y_DIFF = -y_a;
    const double X0 = x_a + X_DIFF;
    const double Y0 = y_a + Y_DIFF;
    const double X1 = x_b + X_DIFF;
    const double Y1 = y_b + Y_DIFF;
    const double X2 = x_c + X_DIFF;
    const double Y2 = y_c + Y_DIFF;
    const double X3 = x_d + X_DIFF;
    const double Y3 = y_d + Y_DIFF;

    // If a and b points makes up vertical line, then new and checking points
    // must be on different sites.
    if (Y0==Y1 && (Y3<Y0 == Y2<Y0)) return true;
    // Similary for horizontal line.
    if (X0==X1 && (X3<X0 == X2<X0)) return true;
    // For diagonal line.
    const double K = (Y1 / X1);
    if (Y3<K*X3 != Y2<K*X2) return true;
    return false;
}


vector <int*> points_delaunay_naive_2d(int node_num, double node_xy[], int *triangle_num)
{
    int count;
    int flag;
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
                                bool isNotNewTriangle;
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

};
