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
	PlanePrim( vector3& p_Normal, double p_D ) : m_Plane( plane( p_Normal, p_D ) ) 
	{
		//x_Dir = vector3( m_Plane.N.y, m_Plane.N.z, -m_Plane.N.x );
		
		x_Dir = m_Plane.N.Cross(vector3(0,1,0));
		y_Dir = x_Dir.Cross( m_Plane.N );
		NORMALIZE(x_Dir);
		NORMALIZE(y_Dir);
		O_H = - m_Plane.N * m_Plane.D;
		
	}
	inline vector3& getNormal() { return m_Plane.N; }
	inline double getD() { return m_Plane.D; }
	Color getColor(vector3& p_Pos);
	int Intersect( Ray& p_Ray, double& p_Dist );
	bool H_IntersectBox( BoundingBox& );
	inline vector3 getNormal( vector3& p_Pos ){return m_Plane.N;};
	inline BoundingBox getBoundingBox() { return BoundingBox(vector3(-10000,-10000,-10000),vector3(20000,20000,20000));}

private:
	plane m_Plane;
	vector3 x_Dir;
	vector3 y_Dir;
	vector3 O_H;//原点在平面上的垂足
};

}

#endif