#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "all.h"

namespace HYF
{

class Material
{
public:
	Material();
	void setColor( Color& p_Color ) { m_Color = p_Color; }
	Color getColor() { return m_Color; }
	void setSpecular( double p_Spec ) { m_Spec = p_Spec; }//高光
	void setDiffuse( double p_Diff ) { m_Diff = p_Diff; }
	void setReflection( double p_Refl ) { m_Refl = p_Refl; }
	void setRefraction( double p_Refr ) { m_Refr = p_Refr; }
	void setRefr_Rate( double p_Refr_Rate ) { m_Refr_Rate = p_Refr_Rate; }
	double getSpecular() { return m_Spec; }//高光
	double getDiffuse() { return m_Diff; }//漫反射
	double getReflection() { return m_Refl;}
	double getRefraction() { return m_Refr;}
	double getRefr_Rate() { return m_Refr_Rate;}
private:
	Color m_Color;//材质颜色
	double m_Refl;//反射系数
	double m_Diff;//漫反射系数
	double m_Spec;//高光
	double m_Refr;//透射率
	double m_Refr_Rate;//折射率
};

class Primitive
{
public:
	enum
	{
		SPHERE = 1,
		PLANE = 2,
		AABB
	};
	Primitive() : m_Name( 0 ), m_Light( false ) {};
	Material* getMaterial() { return &m_Material; }
	void setMaterial( Material& p_Mat ) { m_Material = p_Mat; }

	virtual int getType() = 0;
	virtual int Intersect( Ray& p_Ray, double& p_Dist ) = 0;
	virtual bool H_IntersectBox( aabb& ) = 0;
	virtual vector3 getNormal( vector3& p_Pos ) = 0;
	virtual Color getColor() { return m_Material.getColor(); }
	virtual void Light( bool p_Light ) { m_Light = p_Light; }
	virtual aabb getAABB() = 0;
	
	bool IsLight() { return m_Light; }
	void setName( char* p_Name );
	char* getName() { return m_Name; }
protected:
	Material m_Material;
	char* m_Name;
	bool m_Light;
};

class Round
{
	//to be added
};

}

#endif