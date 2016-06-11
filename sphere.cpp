#include "all.h"

namespace HYF
{

Color Sphere::getColor(vector3& p_Pos)
{
	if(m_Material.getTexure() == NULL)
	{
		return m_Material.getColor();
	}
	vector3 r_Pos = p_Pos - m_Centre;
	double s = acos(r_Pos.z / m_Radius) / PI;
	double t = acos(r_Pos.x / (m_Radius * sin(PI * s))) / PI;
	return m_Material.getTexure()->getUVColor(s,t);
}

int Sphere::Intersect( Ray& p_Ray, double& p_Dist )
{
	vector3 v = p_Ray.getOrigin() - m_Centre;
	double b = -DOT( v, p_Ray.getDirection() );
	double det = (b * b) - DOT( v, v ) + m_Radius * m_Radius;
	int retval = MISS;
	if (det > EPS)
	{
		det = sqrt( det );
		double i1 = b - det;
		double i2 = b + det;
		if (i2 > EPS)
		{
			if (i1 < EPS) 
			{
				if (i2 < p_Dist) 
				{
					p_Dist = i2;
					retval = INPRIM;
				}
			}
			else
			{
				if (i1 < p_Dist)
				{
					p_Dist = i1;
					retval = HIT;
				}
			}
		}
	}
	/*
	if(p_Dist < EPS)
	{
		std::cout << b << " " << det << "\n";
		std::cout << p_Dist << "\n";
		system("pause");
	}
	*/
	return retval;
	
	/*
	vector3 op = m_Centre-p_Ray.getOrigin(); // Solve t^2*d.d + 2*t*(o-p).d + (o-p).(o-p)-R^2 = 0 
	double t, eps=1e-4, b=op.Dot(p_Ray.getDirection()), det=b*b-op.Dot(op)+m_SqRadius; 
     if (det<0) 
		 return 0; 
	 else 
		 det=sqrt(det); 
     (t=b-det)>eps ? t : ((t=b+det)>eps ? t : 0); 
	 p_Dist = t;
	 return 1;
	 */
	/*
	vector3 op = m_Centre-p_Ray.getOrigin(); // Solve t^2*d.d + 2*t*(o-p).d + (o-p).(o-p)-R^2 = 0 
	double t, eps=1e-4, b=op.Dot(p_Ray.getDirection()), det=b*b-op.Dot(op)+m_Radius*m_Radius; 
     if (det<0) 
		 return 0;
	 else 
		 det=sqrt(det); 
	//double ret = ((t=b-det)>eps ? t : ((t=b+det)>eps ? t : 0)); 
	 double ret;// = ((t=b-det)>eps ? t : ((t=b+det)>eps ? t : 0)); 
	 t=b-det;
	 if(t > eps)
	 {
		 ret = t;
	 }
	 else
	 {
		 t = b+det;
		 if(t > eps)
		 {
			 ret = t;
		 }
		 else
			 ret = 0.0;
	 }
	if(ret < eps) return 0;
	if(p_Dist > ret) p_Dist = ret;
	return 1;
	*/
}



bool Sphere::H_IntersectBox(BoundingBox& p_b)
{
	double dmin = 0;
	vector3 v1 = p_b.getPos(), v2 = p_b.getPos() + p_b.getSize();
	if (m_Centre.x < v1.x) 
	{
		dmin = dmin + (m_Centre.x - v1.x) * (m_Centre.x - v1.x);
	}
	else if (m_Centre.x > v2.x)
	{
		dmin = dmin + (m_Centre.x - v2.x) * (m_Centre.x - v2.x);
	}
	if (m_Centre.y < v1.y)
	{
		dmin = dmin + (m_Centre.y - v1.y) * (m_Centre.y - v1.y);
	}
	else if (m_Centre.y > v2.y)
	{
		dmin = dmin + (m_Centre.y - v2.y) * (m_Centre.y - v2.y);
	}
	if (m_Centre.z < v1.z)
	{
		dmin = dmin + (m_Centre.z - v1.z) * (m_Centre.z - v1.z);
	}
	else if (m_Centre.z > v2.z)
	{
		dmin = dmin + (m_Centre.z - v2.z) * (m_Centre.z - v2.z);
	}
	return (dmin <= m_SqRadius);
}

}