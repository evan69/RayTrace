#include "box.h"

namespace HYF
{

Box::Box() : 
	m_Box( vector3( 0, 0, 0 ), vector3( 0, 0, 0 ) )
{
}

Box::Box( BoundingBox& p_Box ) : 
	m_Box( p_Box )
{
}

int Box::Intersect( Ray& p_Ray, double& p_Dist )
{
	double dist[6];
	vector3 ip[6], d = p_Ray.getDirection(), o = p_Ray.getOrigin();
	bool retval = MISS;
	for ( int i = 0; i < 6; i++ ) dist[i] = -1;
	vector3 v1 = m_Box.getPos(), v2 = m_Box.getPos() + getSize();
	if (d.x) 
	{
		double rc = 1.0f / d.x;
		dist[0] = (v1.x - o.x) * rc;
		dist[3] = (v2.x - o.x) * rc;
	}
	if (d.y) 
	{
		double rc = 1.0f / d.y;
		dist[1] = (v1.y - o.y) * rc;
		dist[4] = (v2.y - o.y) * rc;
	}
	if (d.z) 
	{
		double rc = 1.0f / d.z;
		dist[2] = (v1.z - o.z) * rc;
		dist[5] = (v2.z - o.z) * rc;
	}
	for ( int i = 0; i < 6; i++ ) if (dist[i] > 0)
	{
		ip[i] = o + dist[i] * d;
		if ((ip[i].x > (v1.x - EPS)) && (ip[i].x < (v2.x + EPS)) && 
			(ip[i].y > (v1.y - EPS)) && (ip[i].y < (v2.y + EPS)) &&
			(ip[i].z > (v1.z - EPS)) && (ip[i].z < (v2.z + EPS)))
		{
			if (dist[i] < p_Dist) 
			{
				p_Dist = dist[i];
				retval = HIT;
			}
		}
	}
	return retval;
}

vector3 Box::getNormal( vector3& p_Pos )
{
	double dist[6];
	dist[0] = (double)fabs( m_Box.getSize().x - m_Box.getPos().x );
	dist[1] = (double)fabs( m_Box.getSize().x + m_Box.getSize().x - m_Box.getPos().x );
	dist[2] = (double)fabs( m_Box.getSize().y - m_Box.getPos().y );
	dist[3] = (double)fabs( m_Box.getSize().y + m_Box.getSize().y - m_Box.getPos().y );
	dist[4] = (double)fabs( m_Box.getSize().z - m_Box.getPos().z );
	dist[5] = (double)fabs( m_Box.getSize().z + m_Box.getSize().z - m_Box.getPos().z );
	int best = 0;
	double bdist = dist[0];
	for ( int i = 1 ; i < 6; i++ ) if (dist[i] < bdist) 
	{ 
		bdist = dist[i]; 
		best = i;
	}
	if (best == 0) return vector3( -1, 0, 0 );
	else if (best == 1) return vector3( 1, 0, 0 );
	else if (best == 2) return vector3( 0, -1, 0 );
	else if (best == 3)  return vector3( 0, 1, 0 );
	else if (best == 4) return vector3( 0, 0, -1 );
	else return vector3( 0, 0, 1 );
}

}