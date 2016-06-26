#include "all.h"

namespace HYF
{
class Sphere : public Primitive
{
public:
	int getType() { return SPHERE; }
	Sphere( vector3& p_Centre, double p_Radius ) : 
		m_Centre( p_Centre ), m_SqRadius( p_Radius * p_Radius ), 
		m_Radius( p_Radius ), m_RRadius( 1.0f / p_Radius ) {};
	vector3& getCentre() { return m_Centre; }
	double getRadius() { return m_Radius; }
	double getSqRadius() { return m_SqRadius; }
	Color getColor(vector3& p_Pos);
	int Intersect( Ray& p_Ray, double& p_Dist );
	bool H_IntersectBox(BoundingBox&);
	inline vector3 getNormal( vector3& p_Pos ) { return (p_Pos - m_Centre) * m_RRadius; }
	inline vector3 getNormal( vector3& p_Pos ,vector3& p_RayO ) 
	{
		vector3 ret = p_Pos - m_Centre;
		return ret;
	}
	inline BoundingBox getBoundingBox()
	{
		vector3 vecR(m_Radius,m_Radius,m_Radius);
		return BoundingBox(m_Centre - vecR,2*vecR);
	}
private:
	vector3 m_Centre;
	double m_SqRadius, m_Radius, m_RRadius;
	//R平方 R R分之一
};

}