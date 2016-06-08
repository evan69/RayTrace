#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "all.h"

namespace HYF
{

class Triangle : public Primitive
{
public:
	Triangle(vector3 A,vector3 B,vector3 C)
	{
		vertex[0] = A;vertex[1] = B;vertex[2] = C;
		/*
		std::cout << A.x << " "<< A.y << " " << A.z << '\n';
		std::cout << B.x << " "<< B.y << " " << B.z << '\n';
		std::cout << C.x << " "<< C.y << " " << C.z << '\n';
		*/
		N = (B - A).Cross(C - B);
		NORMALIZE(N);
	}
	int getType() {return TRIANGLE;}
	int Intersect( Ray& p_Ray, double& p_Dist );
	bool H_IntersectBox( BoundingBox& );
	inline vector3 getNormal( vector3& p_Pos ){return N;}
	//Color getColor(vector3& p_Pos);
	BoundingBox getBoundingBox();
private:
	vector3 vertex[3];
	vector3 N;
};

}

#endif