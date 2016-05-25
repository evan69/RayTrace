#ifndef BOX_H
#define BOX_H

#include "all.h"

namespace HYF
{

class Box : public Primitive
{
public:
	inline int getType() { return BOX; }
	Box();
	Box( BoundingBox& p_Box );
	int Intersect( Ray& p_Ray, double& p_Dist );
	bool H_IntersectBox( BoundingBox& p_Box ) { return m_Box.Intersect( p_Box ); }
	vector3 getNormal( vector3& );
	bool Contains( vector3& p_Pos ) { return m_Box.Contains( p_Pos ); }
	vector3& getPos() { return m_Box.getPos(); }
	vector3& getSize() { return m_Box.getSize(); }
	inline BoundingBox getBoundingBox() { return m_Box; }
protected:
	BoundingBox m_Box;
};

}

#endif