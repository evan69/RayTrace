#ifndef OBJECT_H
#define OBJECT_H

#include "all.h"
#include <vector>
using std::vector;

namespace HYF
{

class ObjTriangle : public Triangle
{
public:
	ObjTriangle(vector3 A,vector3 B,vector3 C):Triangle(A,B,C){}
	ObjTriangle* EdgeNeighbor[3];
	vector<ObjTriangle*> VertexNeighbor[3];
};

class Object
{
public:
	Object(){}
	vector3 m_move;
	double m_alpha;
	vector<ObjTriangle*> TriangleVec;

	inline void setInfo(vector3 p_move,double p_alpha)
	{
		m_move = p_move;
		m_alpha = p_alpha;
	}
	void readin(char*,Primitive**,int&);

};

};

#endif