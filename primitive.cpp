#include "all.h"

namespace HYF
{

void Primitive::setName( char* p_Name )
{
	delete m_Name; 
	m_Name = new char[strlen( p_Name ) + 1]; 
	strcpy( m_Name, p_Name ); 
}

Material::Material() :
	m_Color( Color( 0.2f, 0.2f, 0.2f ) ),
	m_Refl( 0 ), m_Diff( 0.2f ), m_Spec( 0.8f ), m_Refr_Rate( 1.5f )
{

}

}