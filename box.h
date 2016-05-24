#ifndef BOX_H
#define BOX_H

#include "all.h"

namespace HYF
{

class Box : public Primitive
{
public:
	int GetType() { return BOX; }
	Box();
	Box( BoundingBox& p_Box );
	int Intersect( Ray& p_Ray, float& p_Dist );
	bool IntersectBox( BoundingBox& p_Box ) { return m_Box.Intersect( p_Box ); }
	vector3 getNormal( vector3& );
	bool Contains( vector3& p_Pos ) { return m_Box.Contains( p_Pos ); }
	vector3& getPos() { return m_Box.getPos(); }
	vector3& getSize() { return m_Box.getSize(); }
	BoundingBox getBoundingBox() { return m_Box; }
protected:
	BoundingBox m_Box;
};

}

#endif