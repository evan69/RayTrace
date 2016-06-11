#ifndef OBJECT_H
#define OBJECT_H

#include "all.h"
#include <vector>
using std::vector;

namespace HYF
{

class Object;

class ObjTriangle : public Triangle
{
public:
	ObjTriangle(vector3 A,vector3 B,vector3 C):Triangle(A,B,C){}
	//ObjTriangle* EdgeNeighbor[3];
	//vector<ObjTriangle*> VertexNeighbor[3];
	int vertexIndex[3];
	int id;
	Object* obj;
	vector3 getNormal( vector3& p_Pos );
	inline vector3 getNormal(){return N;}
};

class Object
{
public:
	Object(){}
	vector3 m_move;
	double m_alpha;
	vector<ObjTriangle*> TriangleVec;
	vector<vector<int> > TriangleInfo;

	inline void setInfo(vector3 p_move,double p_alpha)
	{
		m_move = p_move;
		m_alpha = p_alpha;
	}
	void readin(char*,Primitive**,int&);
	void setMaterial(Material*);
};

};

#endif