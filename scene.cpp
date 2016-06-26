#include "all.h"
using std::vector;

namespace HYF {

Scene::~Scene()
{
	delete m_Primitive;
}

void Scene::init()
{
	std::cout << "init\n";
	m_Primitive = 0;
#ifdef PATHTRACING
	m_Primitive = new Primitive*[500000];
	//Scene: radius, position, emission, color, material 
	m_Primitive[0] = new Sphere( vector3( 1e5+1,40.8,81.6), 1e5 );
	m_Primitive[0]->getMaterial()->emission = vector3();
	m_Primitive[0]->getMaterial()->setColor(vector3(.75,.25,.25));
	m_Primitive[0]->getMaterial()->BRDFType = Material::DIFF;
	//HSphere(1e5, vector3( 1e5+1,40.8,81.6), vector3(),vector3(.75,.25,.25),DIFF),//Left 

	m_Primitive[1] = new Sphere( vector3(-1e5+99,40.8,81.6), 1e5 );
	m_Primitive[1]->getMaterial()->emission = vector3();
	m_Primitive[1]->getMaterial()->setColor(vector3(.25,.25,.75));
	m_Primitive[1]->getMaterial()->BRDFType = Material::DIFF;
	//HSphere(1e5, vector3(-1e5+99,40.8,81.6),vector3(),vector3(.25,.25,.75),DIFF),//Rght 
   
	m_Primitive[2] = new Sphere( vector3(50,40.8, 1e5), 1e5 );
	m_Primitive[2]->getMaterial()->emission = vector3();
	m_Primitive[2]->getMaterial()->setColor(vector3(.75,.75,.25));
	m_Primitive[2]->getMaterial()->BRDFType = Material::DIFF;
	//HSphere(1e5, vector3(50,40.8, 1e5),     vector3(),vector3(.75,.75,.75),DIFF),//Back 

	m_Primitive[3] = new Sphere( vector3(50,40.8,-1e5+170), 1e5 );
	m_Primitive[3]->getMaterial()->emission = vector3();
	//m_Primitive[3]->getMaterial()->setColor(vector3());
	m_Primitive[3]->getMaterial()->setColor(vector3(.75,.75,.75));
	m_Primitive[3]->getMaterial()->BRDFType = Material::DIFF;
	//HSphere(1e5, vector3(50,40.8,-1e5+170), vector3(),vector3(),           DIFF),//Frnt 
	
	m_Primitive[4] = new Sphere( vector3(50, 1e5, 81.6), 1e5 );
	m_Primitive[4]->getMaterial()->emission = vector3();
	m_Primitive[4]->getMaterial()->setColor(vector3(.75,.75,.75));
	m_Primitive[4]->getMaterial()->BRDFType = Material::DIFF;
	//HSphere(1e5, vector3(50, 1e5, 81.6),    vector3(),vector3(.75,.75,.75),DIFF),//Botm 

	m_Primitive[5] = new Sphere( vector3(50,-1e5+81.6,81.6), 1e5 );
	m_Primitive[5]->getMaterial()->emission = vector3();
	m_Primitive[5]->getMaterial()->setColor(vector3(.75,.75,.75));
	m_Primitive[5]->getMaterial()->BRDFType = Material::DIFF;
   //HSphere(1e5, vector3(50,-1e5+81.6,81.6),vector3(),vector3(.75,.75,.75),DIFF),//Top 

	m_Primitive[6] = new Sphere( vector3(22,14,45), 14 );
	m_Primitive[6]->getMaterial()->emission = vector3();
	m_Primitive[6]->getMaterial()->setColor(vector3(1,1,1)*.999);
	m_Primitive[6]->getMaterial()->BRDFType = Material::SPEC;

	m_Primitive[7] = new Sphere( vector3(50,681.6-.27,81.6), 600 );
	m_Primitive[7]->getMaterial()->emission = vector3(12,12,12);
	m_Primitive[7]->getMaterial()->setColor(vector3(0,0,0));
	m_Primitive[7]->getMaterial()->BRDFType = Material::DIFF;
	//HSphere(600, vector3(50,681.6-.27,81.6),vector3(12,12,12),  vector3(), DIFF) //Lite 
	 
	m_Primitive[8] = new Sphere( vector3(87,10,96), 10);
	m_Primitive[8]->getMaterial()->emission = vector3();;
	m_Primitive[8]->getMaterial()->setColor(vector3(1,1,1)*.999);
	m_Primitive[8]->getMaterial()->BRDFType = Material::REFR;
	 
	m_Primitives = 9;
	
	Object dragon;
	//dragon.setInfo(vector3(73,16.5,78),0.5);
	dragon.setInfo(vector3(65,20,70),28.0);
	dragon.readin("dragon.obj",m_Primitive,m_Primitives,this->poly_vec);
	Material* m =  new Material;
	m->setColor(Color(1.0,1.0,1.0) * 0.9);
	m->emission = vector3(0,0,0);
	//m->BRDFType = Material::REFR;
	m->BRDFType = Material::DIFF;
	dragon.setMaterial(m);
	
	Object bunny;
	bunny.setInfo(vector3( 25,-4.6,108),150.0);
	bunny.readin("bunny.obj",m_Primitive,m_Primitives,this->poly_vec);
	Material* mm =  new Material;
	mm->setColor(Color(1.0,1.0,1.0) * 0.9);
	//mm->setColor(Color(0.5,0.5,0.5));
	mm->emission = vector3(0,0,0);
	//mm->BRDFType = Material::DIFF;
	mm->BRDFType = Material::SPEC;
	bunny.setMaterial(mm);
//#endif
//#ifdef SCENE_OBJCORNELLBOX
#else
	m_Primitive = new Primitive*[500000];
	// ground plane
	m_Primitive[0] = new PlanePrim( vector3( 0, 1, 0 ), 4.4f );
	m_Primitive[0]->setName( "plane" );
	m_Primitive[0]->getMaterial()->setReflection( 0.6f );
	m_Primitive[0]->getMaterial()->setSpecular(0.8f);
	m_Primitive[0]->getMaterial()->setRefraction( 0.0f );
	m_Primitive[0]->getMaterial()->setDiffuse( 1.0f );
	m_Primitive[0]->getMaterial()->setColor( Color( 0.3f, 0.3f, 0.3f ) );

	m_Primitive[1] = new PlanePrim( vector3( 0, 0, 0 ), 6.0f );
	m_Primitive[1]->setName( "backplane2" );
	m_Primitive[1]->getMaterial()->setSpecular(0.8f);
	m_Primitive[1]->getMaterial()->setReflection( 0.0f );
	m_Primitive[1]->getMaterial()->setRefraction( 0.0f );
	m_Primitive[1]->getMaterial()->setDiffuse( 1.0f );
	m_Primitive[1]->getMaterial()->setColor( Color( 0.0f, 0.2f, 0.0f ) );

	// small sphere
	m_Primitive[2] = new Sphere( vector3( -5, -2.7f, 9 ), 1.5 );
	m_Primitive[2]->setName( "small sphere" );
	m_Primitive[2]->getMaterial()->setReflection( 0.8f );
	m_Primitive[2]->getMaterial()->setRefraction( 0.0f );
	m_Primitive[2]->getMaterial()->setRefr_Rate( 1.3f );
	m_Primitive[2]->getMaterial()->setDiffuse( 0.1f );
	m_Primitive[2]->getMaterial()->setColor( Color( 0.7f, 0.7f, 1.0f ) );
	m_Primitive[2]->getMaterial()->setDiffRefl( 0.1f );
	
	// third sphere
	m_Primitive[3] = new Sphere( vector3( 4, -3.2f, 7 ), 1 );
	m_Primitive[3]->setName( "middle sphere" );
	m_Primitive[3]->getMaterial()->setReflection( 0.1f );
	m_Primitive[3]->getMaterial()->setRefraction( 0.9f );
	m_Primitive[3]->getMaterial()->setRefr_Rate( 1.5f );
	m_Primitive[3]->getMaterial()->setDiffuse( 0.1f );
	m_Primitive[3]->getMaterial()->setSpecular( 0.2f );
	m_Primitive[3]->getMaterial()->setColor( Color( 0.7f, 0.7f, 1.0f ) );
	m_Primitive[3]->getMaterial()->setDiffRefl( 0.1f );
#if 0
	// area light
	m_Primitive[4] = new Box( BoundingBox( vector3( -1, 4.8, 4 ), vector3( 2, 0.01f, 2 ) ) );
	m_Primitive[4]->Light( true );
	m_Primitive[4]->getMaterial()->setColor( Color( 1, 1, 1 ) );
#else
	// light source 1
	m_Primitive[4] = new Sphere( vector3( 0, 4.8, 5 ), 0.1f );
	m_Primitive[4]->Light( true );
	m_Primitive[4]->getMaterial()->setColor( Color( 1, 1, 1 ) );
#endif
	// back plane
	m_Primitive[5] = new PlanePrim( vector3( 0, 0, -1 ), 12.4f );
	m_Primitive[5]->setName( "backplane" );
	m_Primitive[5]->getMaterial()->setSpecular(0.4f);
	m_Primitive[5]->getMaterial()->setReflection( 0.0f );
	m_Primitive[5]->getMaterial()->setRefraction( 0.0f );
	m_Primitive[5]->getMaterial()->setDiffuse( 1.0f );
	m_Primitive[5]->getMaterial()->setColor( Color( 0.4f, 0.3f, 0.3f ) );
	m_Primitive[5]->getMaterial()->setTexure(new Texture( "textures/marble.tga" ));
	m_Primitive[5]->getMaterial()->setTexRatio(3.0);
	
	m_Primitive[6] = new PlanePrim( vector3( 0, -1, 0), 5.2f);
	m_Primitive[6]->setName( "ceiling" );
	m_Primitive[6]->getMaterial()->setSpecular(0.8f);
	m_Primitive[6]->getMaterial()->setReflection( 0.0f );
	m_Primitive[6]->getMaterial()->setRefraction( 0.0f );
	m_Primitive[6]->getMaterial()->setDiffuse( 1.0f );
	m_Primitive[6]->getMaterial()->setColor( Color( 0.4f, 0.3f, 0.3f ) );

	m_Primitive[7] = new PlanePrim( vector3( 1, 0, 0), 7.0f);
	m_Primitive[7]->setName( "right plane" );
	m_Primitive[7]->getMaterial()->setSpecular(0.0f);
	m_Primitive[7]->getMaterial()->setReflection( 0.0f );
	m_Primitive[7]->getMaterial()->setRefraction( 0.0f );
	m_Primitive[7]->getMaterial()->setDiffuse( 0.5f );
	m_Primitive[7]->getMaterial()->setColor( Color( 0.2f, 0.0f, 0.0f ) );
	m_Primitive[7]->getMaterial()->setTexure(new Texture( "textures/wood.tga" ));
	m_Primitive[7]->getMaterial()->setTexRatio(3.0);

	m_Primitive[8] = new PlanePrim( vector3( -1, 0, 0), 7.0f);
	m_Primitive[8]->setName( "left plane" );
	m_Primitive[8]->getMaterial()->setSpecular(0.0f);
	m_Primitive[8]->getMaterial()->setReflection( 0.0f );
	m_Primitive[8]->getMaterial()->setRefraction( 0.0f );
	m_Primitive[8]->getMaterial()->setDiffuse( 0.8f );
	//m_Primitive[8]->getMaterial()->setColor( Color( 0.0f, 0.0f, 0.2f ) );
	m_Primitive[8]->getMaterial()->setColor( Color(241.0f, 158.0f, 194.0f ) * (1.0 / 256) );

	m_Primitive[9] = new Sphere( vector3( -5.8, -3.0f, 5 ), 1.2 );
	m_Primitive[9]->setName( "small sphere" );
	m_Primitive[9]->getMaterial()->setReflection( 0.0f );
	m_Primitive[9]->getMaterial()->setRefraction( 0.0f );
	m_Primitive[9]->getMaterial()->setRefr_Rate( 1.3f );
	m_Primitive[9]->getMaterial()->setDiffuse( 0.9f );
	m_Primitive[9]->getMaterial()->setColor( Color( 0.7f, 0.7f, 1.0f ) );
	//m_Primitive[9]->getMaterial()->setDiffRefl( 0.3f );
	m_Primitive[9]->getMaterial()->setTexure(new Texture( "textures/marble.tga" ));
	
	m_Primitives = 10;
	
	Object bunny;
	bunny.setInfo(vector3( 2, -5.0f, 4),15);
	bunny.readin("bunny.obj",m_Primitive,m_Primitives,this->poly_vec);
	Material* m =  new Material;
	m->setColor(Color(242,192,86) * (1.0 / 256));
	m->setDiffRefl(0.0);
	//m->setDiffuse(2.0);
	m->setDiffuse(0.45);
	//m->setReflection(0.0);
	m->setReflection(0.5);
	m->setRefraction(0.0);
	m->setRefr_Rate(1.5);
	m->setSpecular(0.0);
	bunny.setMaterial(m);

	Object dragon;
	dragon.setInfo(vector3( 0, -2.2f, 9),2.8);
	dragon.readin("dragon.obj",m_Primitive,m_Primitives,this->poly_vec);
	Material* mm =  new Material;
	mm->setColor(Color(250,235,215) * (0.5 / 256));
	mm->setDiffRefl(0.0);
	mm->setDiffuse(2.0);
	mm->setReflection(0.0);
	mm->setRefraction(0.0);
	mm->setRefr_Rate(1.5);
	mm->setSpecular(0.0);
	dragon.setMaterial(mm);
#endif

#ifndef KD
	BuildGrid();
#else
	initLight();
#endif
}

void Scene::BuildGrid()
{
	m_Grid = new vector<Primitive*>[GRIDSIZE * GRIDSIZE * GRIDSIZE];
	memset( m_Grid, 0, GRIDSIZE * GRIDSIZE * GRIDSIZE * 4 );
	vector3 p1(-100, -100, -100), p2( 200, 200, 200 );
	double dx = (p2.x - p1.x) / GRIDSIZE, dx_reci = 1.0f / dx;
	double dy = (p2.y - p1.y) / GRIDSIZE, dy_reci = 1.0f / dy;
	double dz = (p2.z - p1.z) / GRIDSIZE, dz_reci = 1.0f / dz;
	m_Boundary = BoundingBox( p1, p2 - p1 );
	m_Light = new Primitive*[MAXLIGHTS];
	m_Lights = 0;
	for ( int p = 0; p < m_Primitives; p++ )
	{
		if (m_Primitive[p]->IsLight()) m_Light[m_Lights++] = m_Primitive[p];
		BoundingBox bound = m_Primitive[p]->getBoundingBox();
		vector3 bv1 = bound.getPos(), bv2 = bound.getPos() + bound.getSize();
		int x1 = (int)((bv1.x - p1.x) * dx_reci), x2 = (int)((bv2.x - p1.x) * dx_reci) + 1;
		x1 = (x1 < 0)?0:x1, x2 = (x2 > (GRIDSIZE - 1))?GRIDSIZE - 1:x2;
		int y1 = (int)((bv1.y - p1.y) * dy_reci), y2 = (int)((bv2.y - p1.y) * dy_reci) + 1;
		y1 = (y1 < 0)?0:y1, y2 = (y2 > (GRIDSIZE - 1))?GRIDSIZE - 1:y2;
		int z1 = (int)((bv1.z - p1.z) * dz_reci), z2 = (int)((bv2.z - p1.z) * dz_reci) + 1;
		z1 = (z1 < 0)?0:z1, z2 = (z2 > (GRIDSIZE - 1))?GRIDSIZE - 1:z2;
		for ( int x = x1; x < x2; x++ ) 
			for ( int y = y1; y < y2; y++ ) 
				for ( int z = z1; z < z2; z++ )
		{
			int idx = x + y * GRIDSIZE + z * GRIDSIZE * GRIDSIZE;
			vector3 pos( p1.x + x * dx, p1.y + y * dy, p1.z + z * dz );
			BoundingBox cell( pos, vector3( dx, dy, dz ) );
			if (m_Primitive[p]->H_IntersectBox( cell ))
			{
				m_Grid[idx].push_back(m_Primitive[p]);
			}
		}
	}
}

void Scene::initLight()
{
	m_Light = new Primitive*[MAXLIGHTS];
	m_Lights = 0;
	for ( int p = 0; p < m_Primitives; p++ )
	{
		if (m_Primitive[p]->IsLight()) m_Light[m_Lights++] = m_Primitive[p];
	}
}

}; // namespace HYF
