#include "all.h"
using std::vector;

namespace HYF {

Scene::~Scene()
{
	delete m_Primitive;
}

void Scene::init()
{
	/*
	m_Primitive = new Primitive*[100];
	// ground plane
	m_Primitive[0] = new PlanePrim( vector3( 0, 1, 0 ), 4.4f );
	m_Primitive[0]->setName( "plane" );
	m_Primitive[0]->getMaterial()->setReflection( 0.0 );
	m_Primitive[0]->getMaterial()->setRefraction( 0.0);
	m_Primitive[0]->getMaterial()->setDiffuse( 1.0 );
	m_Primitive[0]->getMaterial()->setColor( Color( 0.4f, 0.3f, 0.3f ) );
	// big sphere
	m_Primitive[1] = new Sphere( vector3( 2, 0.8f, 3 ), 2.5f );
	m_Primitive[1]->setName( "big sphere" );
	m_Primitive[1]->getMaterial()->setReflection( 0.2f );
	m_Primitive[1]->getMaterial()->setRefraction( 0.8f );
	m_Primitive[1]->getMaterial()->setRefr_Rate( 1.3f );
	m_Primitive[1]->getMaterial()->setDiffuse( 0.1f );
	m_Primitive[1]->getMaterial()->setSpecular( 0.9f );
	m_Primitive[1]->getMaterial()->setColor( Color( 0.7f, 0.7f, 1.0 ) );
	// small sphere
	m_Primitive[2] = new Sphere( vector3( -5.5f, -0.5, 7 ), 2 );
	m_Primitive[2]->setName( "small sphere" );
	m_Primitive[2]->getMaterial()->setReflection( 0.5 );
	m_Primitive[2]->getMaterial()->setRefraction( 0.0 );
	m_Primitive[2]->getMaterial()->setRefr_Rate( 1.3 );
	m_Primitive[2]->getMaterial()->setDiffuse( 0.1 );
	m_Primitive[2]->getMaterial()->setSpecular( 0.9 );
	m_Primitive[2]->getMaterial()->setColor( Color( 0.7, 0.7, 1.0 ) );
	// light source 1
	m_Primitive[3] = new Sphere( vector3( 0, 5, 5 ), 0.1 );
	m_Primitive[3]->Light( true );
	m_Primitive[3]->getMaterial()->setColor( Color( 0.4, 0.4, 0.4 ) );
	// light source 2
	m_Primitive[4] = new Sphere( vector3( -3, 5, 1 ), 0.1 );
	m_Primitive[4]->Light( true );
	m_Primitive[4]->getMaterial()->setColor( Color( 0.6, 0.6, 0.8 ) );
	// extra sphere
	m_Primitive[5] = new Sphere( vector3( -1.5, -3.8, 1 ), 1.5 );
	m_Primitive[5]->setName( "extra sphere" );
	m_Primitive[5]->getMaterial()->setReflection( 0.0 );
	m_Primitive[5]->getMaterial()->setRefraction( 0.8 );
	m_Primitive[5]->getMaterial()->setDiffuse( 0.1 );
	m_Primitive[5]->getMaterial()->setSpecular( 0.9 );
	m_Primitive[5]->getMaterial()->setColor( Color( 1.0, 0.4, 0.4 ) );
	// back plane
	m_Primitive[6] = new PlanePrim( vector3( 0.4f, 0, -1 ), 12 );
	m_Primitive[6]->setName( "back plane" );
	m_Primitive[6]->getMaterial()->setReflection( 0.0 );
	m_Primitive[6]->getMaterial()->setRefraction( 0.0 );
	m_Primitive[6]->getMaterial()->setSpecular( 0 );
	m_Primitive[6]->getMaterial()->setDiffuse( 0.6 );
	m_Primitive[6]->getMaterial()->setColor( Color( 0.5, 0.3, 0.5 ) );
	// ceiling plane
	m_Primitive[7] = new PlanePrim( vector3( 0, -1, 0 ), 7.4f );
	m_Primitive[7]->setName( "back plane" );
	m_Primitive[7]->getMaterial()->setReflection( 0.0 );
	m_Primitive[7]->getMaterial()->setRefraction( 0.0 );
	m_Primitive[7]->getMaterial()->setSpecular( 0 );
	m_Primitive[7]->getMaterial()->setDiffuse( 0.5 );
	m_Primitive[7]->getMaterial()->setColor( Color( 0.4, 0.7, 0.7 ) );
	// grid
	int prim = 8;
	for ( int x = 0; x < 8; x++ ) for ( int y = 0; y < 7; y++ )
	{
		m_Primitive[prim] = new Sphere( vector3( -4.5 + x * 1.5, -4.3 + y * 1.5, 10 ), 0.3 );
		m_Primitive[prim]->setName( "grid sphere" );
		m_Primitive[prim]->getMaterial()->setReflection( 0 );
		m_Primitive[prim]->getMaterial()->setRefraction( 0 );
		m_Primitive[prim]->getMaterial()->setSpecular( 0.6 );
		m_Primitive[prim]->getMaterial()->setDiffuse( 0.6 );
		m_Primitive[prim]->getMaterial()->setColor( Color( 0.3, 1.0, 0.4 ) );
		prim++;
	}
	// set number of primitives
	m_Primitives = prim;
	*/
	
	m_Primitive = new Primitive*[500];
	// ground plane
	m_Primitive[0] = new PlanePrim( vector3( 0, 1, 0 ), 4.4f );
	m_Primitive[0]->setName( "plane" );
	m_Primitive[0]->getMaterial()->setReflection( 0.0f );
	m_Primitive[0]->getMaterial()->setRefraction( 0.0f );
	m_Primitive[0]->getMaterial()->setDiffuse( 1.0f );
	m_Primitive[0]->getMaterial()->setColor( Color( 0.4f, 0.3f, 0.3f ) );
	// big sphere
	m_Primitive[1] = new Sphere( vector3( 2, 0.8f, 3 ), 2.5f );
	m_Primitive[1]->setName( "big sphere" );
	m_Primitive[1]->getMaterial()->setReflection( 0.2f );
	m_Primitive[1]->getMaterial()->setRefraction( 0.8f );
	m_Primitive[1]->getMaterial()->setRefr_Rate( 1.3f );
	m_Primitive[1]->getMaterial()->setColor( Color( 0.7f, 0.7f, 1.0f ) );
	// small sphere
	m_Primitive[2] = new Sphere( vector3( -5.5f, -0.5, 7 ), 2 );
	m_Primitive[2]->setName( "small sphere" );
	m_Primitive[2]->getMaterial()->setReflection( 0.5f );
	m_Primitive[2]->getMaterial()->setRefraction( 0.0f );
	m_Primitive[2]->getMaterial()->setRefr_Rate( 1.3f );
	m_Primitive[2]->getMaterial()->setDiffuse( 0.1f );
	m_Primitive[2]->getMaterial()->setColor( Color( 0.7f, 0.7f, 1.0f ) );
	// light source 1
	m_Primitive[3] = new Sphere( vector3( 0, 5, 5 ), 0.1f );
	m_Primitive[3]->Light( true );
	m_Primitive[3]->getMaterial()->setColor( Color( 0.4f, 0.4f, 0.4f ) );
	// light source 2
	m_Primitive[4] = new Sphere( vector3( -3, 5, 1 ), 0.1f );
	m_Primitive[4]->Light( true );
	m_Primitive[4]->getMaterial()->setColor( Color( 0.6f, 0.6f, 0.8f ) );
	// extra sphere
	m_Primitive[5] = new Sphere( vector3( -1.5f, -3.8f, 1 ), 1.5f );
	m_Primitive[5]->setName( "extra sphere" );
	m_Primitive[5]->getMaterial()->setReflection( 0.0f );
	m_Primitive[5]->getMaterial()->setRefraction( 0.8f );
	m_Primitive[5]->getMaterial()->setColor( Color( 1.0f, 0.4f, 0.4f ) );
	// back plane
	m_Primitive[6] = new PlanePrim( vector3( 0.4f, 0, -1 ), 12 );
	m_Primitive[6]->setName( "back plane" );
	m_Primitive[6]->getMaterial()->setReflection( 0.0f );
	m_Primitive[6]->getMaterial()->setRefraction( 0.0f );
	m_Primitive[6]->getMaterial()->setSpecular( 0 );
	m_Primitive[6]->getMaterial()->setDiffuse( 0.6f );
	m_Primitive[6]->getMaterial()->setColor( Color( 0.5f, 0.3f, 0.5f ) );
	// ceiling plane
	m_Primitive[7] = new PlanePrim( vector3( 0, -1, 0 ), 7.4f );
	m_Primitive[7]->setName( "back plane" );
	m_Primitive[7]->getMaterial()->setReflection( 0.0f );
	m_Primitive[7]->getMaterial()->setRefraction( 0.0f );
	m_Primitive[7]->getMaterial()->setSpecular( 0 );
	m_Primitive[7]->getMaterial()->setDiffuse( 0.5f );
	m_Primitive[7]->getMaterial()->setColor( Color( 0.4f, 0.7f, 0.7f ) );
	// grid
	int prim = 8;
	for ( int x = 0; x < 8; x++ ) for ( int y = 0; y < 7; y++ )
	{
		m_Primitive[prim] = new Sphere( vector3( -4.5f + x * 1.5f, -4.3f + y * 1.5f, 10 ), 0.3f );
		m_Primitive[prim]->setName( "grid sphere" );
		m_Primitive[prim]->getMaterial()->setReflection( 0 );
		m_Primitive[prim]->getMaterial()->setRefraction( 0 );
		m_Primitive[prim]->getMaterial()->setSpecular( 0.6f );
		m_Primitive[prim]->getMaterial()->setDiffuse( 0.6f );
		m_Primitive[prim]->getMaterial()->setColor( Color( 0.3f, 1.0f, 0.4f ) );
		prim++;
	}
	for ( int x = 0; x < 8; x++ ) for ( int y = 0; y < 8; y++ )
	{
		m_Primitive[prim] = new Sphere( vector3( -4.5f + x * 1.5f, -4.3f, 10.0f - y * 1.5f ), 0.3f );
		m_Primitive[prim]->setName( "grid sphere" );
		m_Primitive[prim]->getMaterial()->setReflection( 0 );
		m_Primitive[prim]->getMaterial()->setRefraction( 0 );
		m_Primitive[prim]->getMaterial()->setSpecular( 0.6f );
		m_Primitive[prim]->getMaterial()->setDiffuse( 0.6f );
		m_Primitive[prim]->getMaterial()->setColor( Color( 0.3f, 1.0f, 0.4f ) );
		prim++;
	}
	for ( int x = 0; x < 16; x++ ) for ( int y = 0; y < 8; y++ )
	{
		m_Primitive[prim] = new Sphere( vector3( -8.5f + x * 1.5f, 4.3f, 10.0f - y ), 0.3f );
		m_Primitive[prim]->setName( "grid sphere" );
		m_Primitive[prim]->getMaterial()->setReflection( 0 );
		m_Primitive[prim]->getMaterial()->setRefraction( 0 );
		m_Primitive[prim]->getMaterial()->setSpecular( 0.6f );
		m_Primitive[prim]->getMaterial()->setDiffuse( 0.6f );
		m_Primitive[prim]->getMaterial()->setColor( Color( 0.3f, 1.0f, 0.4f ) );
		prim++;
	}
	// set number of primitives
	m_Primitives = prim;
	// build the regular gird
	
	BuildGrid();
}

void Scene::BuildGrid()
{
	// initialize regular grid
	m_Grid = new vector<Primitive*>[GRIDSIZE * GRIDSIZE * GRIDSIZE];
	memset( m_Grid, 0, GRIDSIZE * GRIDSIZE * GRIDSIZE * 4 );
	//vector3 p1(-14, -5, -6), p2( 14, 8, 30 );
	vector3 p1(-20, -20, -20), p2( 20, 20, 30 );
	// calculate cell width, height and depth
	double dx = (p2.x - p1.x) / GRIDSIZE, dx_reci = 1.0f / dx;
	double dy = (p2.y - p1.y) / GRIDSIZE, dy_reci = 1.0f / dy;
	double dz = (p2.z - p1.z) / GRIDSIZE, dz_reci = 1.0f / dz;
	m_Boundary = aabb( p1, p2 - p1 );
	m_Light = new Primitive*[MAXLIGHTS];
	m_Lights = 0;
	// store primitives in the grid cells
	for ( int p = 0; p < m_Primitives; p++ )
	{
		if (m_Primitive[p]->IsLight()) m_Light[m_Lights++] = m_Primitive[p];
		aabb bound = m_Primitive[p]->getAABB();
		vector3 bv1 = bound.getPos(), bv2 = bound.getPos() + bound.getSize();
		// find out which cells could contain the primitive (based on aabb)
		int x1 = (int)((bv1.x - p1.x) * dx_reci), x2 = (int)((bv2.x - p1.x) * dx_reci) + 1;
		x1 = (x1 < 0)?0:x1, x2 = (x2 > (GRIDSIZE - 1))?GRIDSIZE - 1:x2;
		int y1 = (int)((bv1.y - p1.y) * dy_reci), y2 = (int)((bv2.y - p1.y) * dy_reci) + 1;
		y1 = (y1 < 0)?0:y1, y2 = (y2 > (GRIDSIZE - 1))?GRIDSIZE - 1:y2;
		int z1 = (int)((bv1.z - p1.z) * dz_reci), z2 = (int)((bv2.z - p1.z) * dz_reci) + 1;
		z1 = (z1 < 0)?0:z1, z2 = (z2 > (GRIDSIZE - 1))?GRIDSIZE - 1:z2;
		// loop over candidate cells
		for ( int x = x1; x < x2; x++ ) 
			for ( int y = y1; y < y2; y++ ) 
				for ( int z = z1; z < z2; z++ )
		{
			// construct aabb for current cell
			int idx = x + y * GRIDSIZE + z * GRIDSIZE * GRIDSIZE;
			vector3 pos( p1.x + x * dx, p1.y + y * dy, p1.z + z * dz );
			aabb cell( pos, vector3( dx, dy, dz ) );
			// do an accurate aabb / primitive intersection test
			if (m_Primitive[p]->H_IntersectBox( cell ))
			{
				m_Grid[idx].push_back(m_Primitive[p]);
			}
		}
	}
}

}; // namespace HYF
