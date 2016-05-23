#ifndef ALL_H
#define ALL_H

#include <opencv2\opencv.hpp>
#include <cmath>
#include <cstdlib>
#include <vector>
#include "vector3.h"

typedef unsigned int Pixel;

namespace HYF 
{

//inline double Rand( double p_Range ) { return ((double)rand() / RAND_MAX) * p_Range; }

#define HIT		 1		// Ray hit primitive
#define MISS	 0		// Ray missed primitive
#define INPRIM	-1		// Ray started inside primitive

#define AIR_REFR_INDEX 1.0

#define DOT(A,B)		(A.x*B.x+A.y*B.y+A.z*B.z)
#define NORMALIZE(A)	{double l=1/sqrt(A.x*A.x+A.y*A.y+A.z*A.z);A.x*=l;A.y*=l;A.z*=l;}
#define LENGTH(A)		(sqrt(A.x*A.x+A.y*A.y+A.z*A.z))
//#define SQRLENGTH(A)	(A.x*A.x+A.y*A.y+A.z*A.z)
//#define SQRDISTANCE(A,B) ((A.x-B.x)*(A.x-B.x)+(A.y-B.y)*(A.y-B.y)+(A.z-B.z)*(A.z-B.z))

#define EPS			0.0001f
#define TRACEDEPTH		6
#define GRIDSIZE		8
#define GRIDSHFT		3
#define MAXLIGHTS		10

#define PI				3.141592653589793238462f

class aabb
{
public:
	aabb() : m_Pos( vector3( 0, 0, 0 ) ), m_Size( vector3( 0, 0, 0 ) ) {};
	aabb( vector3& a_Pos, vector3& a_Size ) : m_Pos( a_Pos ), m_Size( a_Size ) {};
	//pos-三个向量维度最小值 size三个维度尺寸
	vector3& getPos() { return m_Pos; }
	vector3& getSize() { return m_Size; }
	bool Intersect( aabb& b2 )
	{
		vector3 v1 = b2.getPos(), v2 = b2.getPos() + b2.getSize();
		vector3 v3 = m_Pos, v4 = m_Pos + m_Size;
		return ((v4.x > v1.x) && (v3.x < v2.x) && // x-axis overlap
				(v4.y > v1.y) && (v3.y < v2.y) && // y-axis overlap
				(v4.z > v1.z) && (v3.z < v2.z));   // z-axis overlap
	}
	bool Contains( vector3 a_Pos )
	{
		vector3 v1 = m_Pos, v2 = m_Pos + m_Size;
		return ((a_Pos.x > (v1.x - EPS)) && (a_Pos.x < (v2.x + EPS)) &&
				(a_Pos.y > (v1.y - EPS)) && (a_Pos.y < (v2.y + EPS)) &&
				(a_Pos.z > (v1.z - EPS)) && (a_Pos.z < (v2.z + EPS)));
	}
private:
	vector3 m_Pos, m_Size;
};

typedef vector3 Color;

};

#include "ray.h"
#include "primitive.h"
#include "sphere.h"
#include "plane.h"
#include "scene.h"
#include "raytracer.h"

#endif