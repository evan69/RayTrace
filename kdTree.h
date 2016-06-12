#ifndef KDTREE_H
#define KDTREE_H
#include <vector>
#include "all.h"
//#include "AABB.h"

namespace HYF
{

const int KD_MAX_THREADS = 6;

class Triangle;

class IntersectResult
{
public:
	IntersectResult() : 
		intersectPoint(0,0,0),
		normalVec(0,0,0),
		distance(1000000000000.0),
		isInObj(false){};
	~IntersectResult(){};
	
	vector3 intersectPoint, normalVec;
	bool isInObj;
	double distance;
	const Material* ma;
	Primitive* primi;
};
const double INF = 1000000000000.0;

class TriangleBox {
public:
	vector3 minPos, maxPos;
	
	TriangleBox();
	~TriangleBox() {}

	void Update(Triangle* tri); // 更新
	bool Cantain(vector3 O);
	double CalnArea();
	double Collide(vector3 ray_O, vector3 ray_V);
};

class TriangleNode {
public:
	Triangle** tris; //每个节点中多个面片
	int size, plane; //
	double split; //分割点
	TriangleBox box; //盒子
	TriangleNode* leftNode; //左节点
	TriangleNode* rightNode;//右节点

	TriangleNode();
	~TriangleNode();
};

class TriangleTree {
	TriangleNode* root;

	void DeleteTree(TriangleNode* node);
	void SortTriangle(Triangle** tris, int l, int r, int coord, bool minCoord);
	void DivideNode(TriangleNode* node);
	IntersectResult TravelTree(TriangleNode* node, vector3 ray_O, vector3 ray_V);

public:
	TriangleTree();
	~TriangleTree();

	TriangleNode* GetRoot() { return root; }
	void BuildTree();
	IntersectResult Collide(Ray ray);//光线和kdtree相交的结果
	int intersect(Ray ray,IntersectResult& result);

};

}

#endif

