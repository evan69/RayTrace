#ifndef SCENE_H
#define SCENE_H

#include "all.h"

namespace HYF {

class TriangleTree;
class Scene
{
public:
	Scene() : m_Primitives( 0 ), m_Primitive( 0 ) ,m_Light(0),m_Lights(0){};
	~Scene();
	void init();
	void BuildGrid();
	void initLight();
	inline std::vector<Primitive*>* getGrid() {return m_Grid;}
	inline int getNrPrimitives() { return m_Primitives; }
	inline int getNrLights() {return m_Lights;}
	inline Primitive* getPrimitive( int p_Idx ) { return m_Primitive[p_Idx]; }
	inline Primitive** getAllPrimitive() { return m_Primitive; }
	inline Primitive* getLight(int p_Idx) { return m_Light[p_Idx];}
	inline BoundingBox& getBoundary() {return m_Boundary;}

	std::vector<TriangleTree*> poly_vec;
private:
	int m_Primitives,m_Lights;
	Primitive** m_Primitive,**m_Light;
	BoundingBox m_Boundary;
	std::vector<Primitive*>* m_Grid;
};

}; // namespace HYF

#endif