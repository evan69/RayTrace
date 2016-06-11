#ifndef VECTOR3
#define VECTOR3

#include <cmath>

namespace HYF
{

class vector3
{
public:
	vector3();
	vector3( double p_X, double p_Y, double p_Z );
	void set( double p_X, double p_Y, double p_Z );
	double Length();
	double SqrLength();
	double Dot( vector3 p_V );
	vector3 Cross( vector3 b );
	vector3 mult(const vector3 &b);
	vector3& norm();
	vector3 operator%(vector3& b);
	void operator += ( vector3& p_V );
	void operator += ( vector3* p_V );
	void operator -= ( vector3& p_V );
	void operator -= ( vector3* p_V );
	void operator *= ( double f );
	void operator *= ( vector3& p_V );
	void operator *= ( vector3* p_V );
	vector3 operator- () const;
	friend vector3 operator + ( const vector3& v1, const vector3& v2 );
	friend vector3 operator - ( const vector3& v1, const vector3& v2 );
	friend vector3 operator + ( const vector3& v1, vector3* v2 );
	friend vector3 operator - ( const vector3& v1, vector3* v2 );
	friend vector3 operator * ( const vector3& v, double f );
	friend vector3 operator * ( const vector3& v1, vector3& v2 );
	friend vector3 operator * ( double f, const vector3& v );
	union
	{
		struct { double x, y, z; };
		struct { double r, g, b; };
		//struct { double cell[3]; };
	};
};

}
#endif