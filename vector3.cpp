#include "vector3.h"

namespace HYF
{

vector3::vector3() : x( 0.0 ), y( 0.0 ), z( 0.0 ) {};

vector3::vector3( double p_X, double p_Y, double p_Z ) : x( p_X ), y( p_Y ), z( p_Z ) {};

void vector3::set( double p_X, double p_Y, double p_Z ) 
{ 
	x = p_X; y = p_Y; z = p_Z; 
}

double vector3::Length() 
{ 
	return (double)sqrt( x * x + y * y + z * z ); 
}

double vector3::SqrLength() 
{ 
	return x * x + y * y + z * z; 
}

double vector3::Dot( vector3 p_V ) 
{ 
	return x * p_V.x + y * p_V.y + z * p_V.z; 
}

vector3 vector3::Cross( vector3 b ) 
{ 
	return vector3( y * b.z - z * b.y, z * b.x - x * b.z, x * b.y - y * b.x ); 
}

void vector3::operator += ( vector3& p_V ) 
{ 
	x += p_V.x; y += p_V.y; z += p_V.z; 
}

void vector3::operator += ( vector3* p_V ) 
{ 
	x += p_V->x; y += p_V->y; z += p_V->z; 
}

void vector3::operator -= ( vector3& p_V ) 
{ 
	x -= p_V.x; y -= p_V.y; z -= p_V.z; 
}

void vector3::operator -= ( vector3* p_V ) 
{ 
	x -= p_V->x; y -= p_V->y; z -= p_V->z; 
}

void vector3::operator *= ( double f ) 
{ 
	x *= f; y *= f; z *= f; 
}

void vector3::operator *= ( vector3& p_V ) 
{ 
	x *= p_V.x; y *= p_V.y; z *= p_V.z; 
}

void vector3::operator *= ( vector3* p_V ) 
{ 
	x *= p_V->x; y *= p_V->y; z *= p_V->z; 
}

vector3 vector3::operator- () const 
{ 
	return vector3( -x, -y, -z ); 
}

vector3 operator + ( const vector3& v1, const vector3& v2 ) 
{ 
	return vector3( v1.x + v2.x, v1.y + v2.y, v1.z + v2.z ); 
}

vector3 operator - ( const vector3& v1, const vector3& v2 ) 
{ 
	return vector3( v1.x - v2.x, v1.y - v2.y, v1.z - v2.z ); 
}

vector3 operator + ( const vector3& v1, vector3* v2 ) 
{ 
	return vector3( v1.x + v2->x, v1.y + v2->y, v1.z + v2->z ); 
}

vector3 operator - ( const vector3& v1, vector3* v2 ) 
{ 
	return vector3( v1.x - v2->x, v1.y - v2->y, v1.z - v2->z ); 
}

vector3 operator * ( const vector3& v, double f ) 
{ 
	return vector3( v.x * f, v.y * f, v.z * f ); 
}

vector3 operator * ( const vector3& v1, vector3& v2 ) 
{ 
	return vector3( v1.x * v2.x, v1.y * v2.y, v1.z * v2.z ); 
}

vector3 operator * ( double f, const vector3& v ) 
{ 
	return vector3( v.x * f, v.y * f, v.z * f ); 
}

}