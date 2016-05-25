#ifndef PLANE_H
#define PLANE_H

#include "all.h"

namespace HYF
{

class plane
{
public:
	plane() : N( 0, 0, 0 ), D( 0 ) {};
	plane( vector3 p_Normal, double p_D ) : N( p_Normal ), D( p_D ) {};
	union
	{
		struct
		{
			vector3 N;
			double D;
		};
		double cell[4];
	};
};

class PlanePrim : public Primitive
{
public:
	int getType() { return PLANE; }
	PlanePrim( vector3& p_Normal, double p_D ) : m_Plane( plane( p_Normal, p_D ) ) {};
	inline vector3& getNormal() { return m_Plane.N; }
	inline double getD() { return m_Plane.D; }
	int Intersect( Ray& p_Ray, double& p_Dist );
	bool H_IntersectBox( BoundingBox& );
	inline vector3 getNormal( vector3& p_Pos ){return m_Plane.N;};
	inline BoundingBox getBoundingBox() { return BoundingBox(vector3(-10000,-10000,-10000),vector3(20000,20000,20000));}

private:
	plane m_Plane;
};

}

#endif