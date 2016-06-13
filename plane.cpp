#include "all.h"

namespace HYF
{

Color PlanePrim::getColor(vector3& p_Pos)
{
	if(m_Material.getTexure() == NULL)
	{
		return m_Material.getColor();
	}
	double u = DOT(p_Pos,x_Dir) * m_Material.getTexRatioDao();
	double v = DOT(p_Pos,y_Dir) * m_Material.getTexRatioDao();
	//std::cout << u << " " << v << std::endl;
	return m_Material.getTexure()->getUVColor(u,v);
	//return m_Material.getColor();
}

int PlanePrim::Intersect( Ray& p_Ray, double& p_Dist )
{
	double d = DOT( m_Plane.N, p_Ray.getDirection() );
	if (d != 0)
	//if (d < EPS && d > -EPS)
	{
		double dist = -(DOT( m_Plane.N, p_Ray.getOrigin() ) + m_Plane.D) / d;
		if (dist > 0)
		{
			if (dist < p_Dist) 
			{
				p_Dist = dist;
				return HIT;
			}
		}
	}
	return MISS;
}

bool PlanePrim::H_IntersectBox(BoundingBox& p_b)
{
	vector3 pos = p_b.getPos();
	vector3 size = p_b.getSize();
	int num1 = 0,num2 = 0;
	for(int i = 0;i < 2;++i)
		for(int j = 0;j < 2;++j)
			for(int k = 0;k < 2;++k)
			{
				vector3 newpos = pos + vector3(i * size.x,j * size.y,k * size.z);
				if((DOT(newpos,getNormal()) + m_Plane.D) < 0)
				{
					num1++;
				}
				else
				{
					num2++;
				}
			}
	if(num1 == 0 || num2 == 0) return false;
	else return true;
}
/*
bool PlanePrim::H_IntersectBox( BoundingBox& p_Box )
{
	vector3 v[2];
	v[0] = p_Box.getPos(), v[1] = p_Box.getPos() + p_Box.getSize();
	int side1,side2,i;
	for ( side1 = 0, side2 = 0, i = 0; i < 8; i++ )
	{
		vector3 p( v[i & 1].x, v[(i >> 1) & 1].y, v[(i >> 2) & 1].z );
		if ((DOT( p, m_Plane.N ) + m_Plane.D) < 0) side1++; else side2++;
	}
	if ((side1 == 0) || (side2 == 0)) return false; else return true;
}
*/

}