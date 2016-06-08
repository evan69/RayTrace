#include "all.h"
#include <cmath>

namespace HYF
{

int Triangle::Intersect(Ray& p_Ray, double& p_Dist)
{
	vector3 dir = p_Ray.getDirection();
	vector3 ori = p_Ray.getOrigin();
	double distance = - DOT( (ori - vertex[0]), N ) / DOT( dir, N );
	if ((distance < EPS) || (distance > 1e6)) return MISS;
	vector3 interPoint = ori + distance * dir;
	double u,v;

	vector3 diru = vertex[1] - vertex[0];
	NORMALIZE(diru);
	vector3 Hu1 = vertex[0] + diru * DOT(diru,(vertex[2] - vertex[0]));
	vector3 Hu2 = vertex[0] + diru * DOT(diru,(interPoint - vertex[0]));
	u = (interPoint - Hu2).x / (vertex[2] - Hu1).x;
	if(u < 0) return MISS;

	vector3 dirv = vertex[2] - vertex[0];
	NORMALIZE(dirv);
	vector3 Hv1 = vertex[0] + dirv * DOT(dirv,(vertex[1] - vertex[0]));
	vector3 Hv2 = vertex[0] + dirv * DOT(dirv,(interPoint - vertex[0]));
	v = (interPoint - Hv2).x / (vertex[1] - Hv1).x;
	if(v < 0) return MISS;

	if(u+v > 1) return MISS;
	p_Dist = distance;
	return HIT;
}

bool Triangle::H_IntersectBox( BoundingBox& box)
{
	BoundingBox a = getBoundingBox();
	return a.Intersect(box);
}

BoundingBox Triangle::getBoundingBox()
{
	vector3 mina = vector3(std::min((std::min(vertex[0].x,vertex[1].x)),vertex[2].x),
		std::min((std::min(vertex[0].y,vertex[1].y)),vertex[2].y),
		std::min((std::min(vertex[0].z,vertex[1].z)),vertex[2].z));
	vector3 maxa = vector3(std::max((std::max(vertex[0].x,vertex[1].x)),vertex[2].x),
		std::max((std::max(vertex[0].y,vertex[1].y)),vertex[2].y),
		std::max((std::max(vertex[0].z,vertex[1].z)),vertex[2].z));
	return BoundingBox(mina,maxa - mina);
}

};