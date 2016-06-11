#include "all.h"
using std::vector;

namespace HYF {

Scene::~Scene()
{
	delete m_Primitive;
}

//#define SCENE_OBJCORNELLBOX
//#define SCENE_3
#define PT1
void Scene::init()
{
	std::cout << "init\n";
	m_Primitive = 0;
#ifdef PATHTRACING
#ifdef PT1
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
	m_Primitive[2]->getMaterial()->setColor(vector3(.75,.75,.75));
	m_Primitive[2]->getMaterial()->BRDFType = Material::DIFF;
	//HSphere(1e5, vector3(50,40.8, 1e5),     vector3(),vector3(.75,.75,.75),DIFF),//Back 

	   m_Primitive[3] = new Sphere( vector3(50,40.8,-1e5+170), 1e5 );
	 m_Primitive[3]->getMaterial()->emission = vector3();
	 m_Primitive[3]->getMaterial()->setColor(vector3());
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

	   m_Primitive[6] = new Sphere( vector3(27,10,87), 10 );
	 m_Primitive[6]->getMaterial()->emission = vector3();
	 m_Primitive[6]->getMaterial()->setColor(vector3(1,1,1)*.999);
	 m_Primitive[6]->getMaterial()->BRDFType = Material::SPEC;

	   m_Primitive[7] = new Sphere( vector3(50,681.6-.27,81.6), 600 );
	 m_Primitive[7]->getMaterial()->emission = vector3(12,12,12);
	 m_Primitive[7]->getMaterial()->setColor(vector3(0,0,0));
	 m_Primitive[7]->getMaterial()->BRDFType = Material::DIFF;
   //HSphere(600, vector3(50,681.6-.27,81.6),vector3(12,12,12),  vector3(), DIFF) //Lite 
	 /*
	 m_Primitive[9] = new Triangle( vector3(73,16.5,78), vector3(73,16.5,78) , vector3(73,16.5,78));
	 m_Primitive[9]->getMaterial()->emission = vector3();;
	 m_Primitive[9]->getMaterial()->setColor(vector3(1,1,1)*.999);
	 m_Primitive[9]->getMaterial()->BRDFType = Material::REFR;
	 */
	 m_Primitives = 8;
	 
	Object dragon;
	//dragon.setInfo(vector3(73,16.5,78),0.5);
	dragon.setInfo(vector3(50,20,45),27.0);
	dragon.readin("dragon.obj",m_Primitive,m_Primitives);
	
	Material* m =  new Material;
	m->setColor(Color(0.5,0.5,0.5));
	m->emission = vector3(0,0,0);
	m->BRDFType = Material::DIFF;
	dragon.setMaterial(m);
	
#endif

#ifdef PT2
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
	m_Primitive[2]->getMaterial()->setColor(vector3(.75,.75,.75));
	m_Primitive[2]->getMaterial()->BRDFType = Material::DIFF;
	//HSphere(1e5, vector3(50,40.8, 1e5),     vector3(),vector3(.75,.75,.75),DIFF),//Back 

	   m_Primitive[3] = new Sphere( vector3(50,40.8,-1e5+170), 1e5 );
	 m_Primitive[3]->getMaterial()->emission = vector3();
	 m_Primitive[3]->getMaterial()->setColor(vector3());
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

	   m_Primitive[6] = new Sphere( vector3(27,16.5,47), 16.5 );
	 m_Primitive[6]->getMaterial()->emission = vector3();
	 m_Primitive[6]->getMaterial()->setColor(vector3(1,1,1)*.999);
	 m_Primitive[6]->getMaterial()->BRDFType = Material::SPEC;
   //HSphere(16.5,vector3(27,16.5,47),       vector3(),vector3(1,1,1)*.999, SPEC),//Mirr 
	 /*
	   m_Primitive[7] = new Sphere( vector3(73,16.5,78), 16.5 );
	 m_Primitive[7]->getMaterial()->emission = vector3();
	 m_Primitive[7]->getMaterial()->setColor(vector3(1,1,1)*.999);
	 m_Primitive[7]->getMaterial()->BRDFType = Material::REFR;
	 */
	 //m_Primitive[7] = new Triangle( vector3(65,16.5,78), vector3(63,16.5,78) , vector3(63,18.5,78));
	 m_Primitive[7] = new Triangle( vector3(73,16.5,78), vector3(27,16.5,47) , vector3(50,30.5,60));
	 m_Primitive[7]->getMaterial()->emission = vector3();;
	 m_Primitive[7]->getMaterial()->setColor(vector3(1,1,1)*.999);
	 m_Primitive[7]->getMaterial()->BRDFType = Material::DIFF;
   //HSphere(16.5,vector3(73,16.5,78),       vector3(),vector3(1,1,1)*.999, REFR),//Glas 

	   m_Primitive[8] = new Sphere( vector3(50,681.6-.27,81.6), 600 );
	 m_Primitive[8]->getMaterial()->emission = vector3(12,12,12);
	 m_Primitive[8]->getMaterial()->setColor(vector3(0,0,0));
	 m_Primitive[8]->getMaterial()->BRDFType = Material::DIFF;
   //HSphere(600, vector3(50,681.6-.27,81.6),vector3(12,12,12),  vector3(), DIFF) //Lite 
	 /*
	 m_Primitive[9] = new Triangle( vector3(73,16.5,78), vector3(73,16.5,78) , vector3(73,16.5,78));
	 m_Primitive[9]->getMaterial()->emission = vector3();;
	 m_Primitive[9]->getMaterial()->setColor(vector3(1,1,1)*.999);
	 m_Primitive[9]->getMaterial()->BRDFType = Material::REFR;
	 */
	 m_Primitives = 9;
	 
	Object dragon;
	//dragon.setInfo(vector3(73,16.5,78),0.5);
	dragon.setInfo(vector3(50,20,45),27.0);
	dragon.readin("dragon.obj",m_Primitive,m_Primitives);
	
	Material* m =  new Material;
	m->setColor(Color(0.5,0.5,0.5));
	m->emission = vector3(0,0,0);
	m->BRDFType = Material::DIFF;
	dragon.setMaterial(m);
#endif

#endif
#ifdef SCENE_3
	m_Primitive = new Primitive*[10000];
	// ground plane
	m_Primitive[0] = new PlanePrim( vector3( 0, 1, 0 ), 4.4f );
	m_Primitive[0]->setName( "plane" );
	m_Primitive[0]->getMaterial()->setReflection( 0.0 );
	m_Primitive[0]->getMaterial()->setRefraction( 0.0);
	m_Primitive[0]->getMaterial()->setDiffuse( 1.0 );
	m_Primitive[0]->getMaterial()->setColor( Color( 0.4f, 0.3f, 0.3f ) );
	// big sphere
	//m_Primitive[1] = new Sphere( vector3( 2, 0.8f, 3 ), 2.5f );
	//m_Primitive[1] = new Triangle( vector3( 2, 0.8f, 1.0 ),  vector3( 2.5, 0.8f, 1.5 ) ,vector3( 2, 1.2, 1.2 ) );
	m_Primitive[1] = new Triangle( vector3( 2, -1.8f, 3 ) ,vector3( -1.5, -3.8, 1 ) ,vector3( -5.5f, -0.5, 7 ));
	m_Primitive[1]->setName( "big sphere" );
	/*
	m_Primitive[1]->getMaterial()->setReflection( 0.2f );
	m_Primitive[1]->getMaterial()->setRefraction( 0.8f );
	m_Primitive[1]->getMaterial()->setRefr_Rate( 1.3f );
	m_Primitive[1]->getMaterial()->setDiffuse( 0.1f );
	m_Primitive[1]->getMaterial()->setSpecular( 0.9f );
	m_Primitive[1]->getMaterial()->setColor( Color( 0.7f, 0.7f, 1.0 ) );
	*/
	m_Primitive[1]->getMaterial()->setReflection( 0.1f );
	m_Primitive[1]->getMaterial()->setRefraction( 0.0f );
	m_Primitive[1]->getMaterial()->setRefr_Rate( 1.3f );
	m_Primitive[1]->getMaterial()->setDiffuse( 1.0f );
	m_Primitive[1]->getMaterial()->setSpecular( 0.1f );
	m_Primitive[1]->getMaterial()->setColor( Color( 0.7f, 0.1f, 0.1f ) );
	//m_Primitive[1]->Light(true);
	//m_Primitive[1]->getMaterial()->setTexure(new Texture("textures/marble.tga"));
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
	m_Primitive[6] = new PlanePrim( vector3( 0.4f, 0, -1 ), 20 );
	m_Primitive[6]->setName( "back plane" );
	m_Primitive[6]->getMaterial()->setReflection( 0.0 );
	m_Primitive[6]->getMaterial()->setRefraction( 0.0 );
	m_Primitive[6]->getMaterial()->setSpecular( 0 );
	m_Primitive[6]->getMaterial()->setDiffuse( 0.6 );
	m_Primitive[6]->getMaterial()->setColor( Color( 0.5, 0.3, 0.5 ) );
	m_Primitive[6]->getMaterial()->setTexure(new Texture( "textures/wood.tga" ));
	m_Primitive[6]->getMaterial()->setTexRatio(5.0);
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
	Object dinosaur;
	dinosaur.setInfo(vector3( 2, 0.8f, 3),0.05);
	dinosaur.readin("dinosaur.obj",m_Primitive,m_Primitives);
	Material* m =  new Material;
	m->setColor(Color(0.5,0.5,0.5));
	m->setDiffRefl(0.0);
	m->setDiffuse(2.0);
	m->setReflection(0.0);
	m->setRefraction(0.0);
	m->setRefr_Rate(1.5);
	m->setSpecular(0.0);
	dragon.setMaterial(m);
	std::cout << m_Primitives << std::endl;
#endif

#ifdef SCENE_4
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
	//m_Primitive[3] = new Sphere( vector3( 0, 5, 5 ), 0.1f );
	m_Primitive[3] = new Sphere( vector3( 0, 5, 5 ), 0.1f );
	//m_Primitive[3] = new Box( BoundingBox(vector3( -2.0, 5, 3.0 ), vector3(4,0.1,4) ));
	m_Primitive[3]->Light( true );
	//m_Primitive[3]->getMaterial()->setColor( Color( 0.4f, 0.4f, 0.4f ) );
	m_Primitive[3]->getMaterial()->setColor( Color( 1.0f, 1.0f, 1.0f ) );
	// light source 2
	//m_Primitive[4] = new Sphere( vector3( -3, 5, 1 ), 0.1f );
	m_Primitive[4] = new Sphere( vector3( -3, 5, 1 ), 1.0f );
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
#endif

#ifdef SCENE_5
	m_Primitive = new Primitive*[500];
	// ground plane
	m_Primitive[0] = new PlanePrim( vector3( 0, 1, 0 ), 4.4f );
	m_Primitive[0]->setName( "plane" );
	m_Primitive[0]->getMaterial()->setReflection( 0.0f );
	//m_Primitive[0]->getMaterial()->setSpecular(0.8f);
	m_Primitive[0]->getMaterial()->setRefraction( 0.0f );
	m_Primitive[0]->getMaterial()->setDiffuse( 1.0f );
	m_Primitive[0]->getMaterial()->setColor( Color( 0.4f, 0.3f, 0.3f ) );
	// big sphere
	m_Primitive[1] = new Sphere( vector3( 0, -0.8f, 7 ), 2 );
	m_Primitive[1]->setName( "big sphere" );
	m_Primitive[1]->getMaterial()->setReflection( 0.2f );
	m_Primitive[1]->getMaterial()->setRefraction( 0.8f );
	m_Primitive[1]->getMaterial()->setRefr_Rate( 1.3f );
	m_Primitive[1]->getMaterial()->setColor( Color( 0.7f, 0.7f, 1.0f ) );
	m_Primitive[1]->getMaterial()->setDiffRefl( 0.3f );
	// small sphere
	m_Primitive[2] = new Sphere( vector3( -5, -0.8f, 7 ), 2 );
	m_Primitive[2]->setName( "small sphere" );
	m_Primitive[2]->getMaterial()->setReflection( 0.5f );
	m_Primitive[2]->getMaterial()->setRefraction( 0.0f );
	m_Primitive[2]->getMaterial()->setRefr_Rate( 1.3f );
	m_Primitive[2]->getMaterial()->setDiffuse( 0.1f );
	m_Primitive[2]->getMaterial()->setColor( Color( 0.7f, 0.7f, 1.0f ) );
	m_Primitive[2]->getMaterial()->setDiffRefl( 0.6f );
	// third sphere
	m_Primitive[3] = new Sphere( vector3( 5, -0.8f, 7 ), 2 );
	m_Primitive[3]->setName( "small sphere" );
	m_Primitive[3]->getMaterial()->setReflection( 0.5f );
	m_Primitive[3]->getMaterial()->setRefraction( 0.0f );
	m_Primitive[3]->getMaterial()->setRefr_Rate( 1.3f );
	m_Primitive[3]->getMaterial()->setDiffuse( 0.1f );
	m_Primitive[3]->getMaterial()->setColor( Color( 0.7f, 0.7f, 1.0f ) );
#if 1
	// area light
	m_Primitive[4] = new Box( BoundingBox( vector3( -1, 5.0, 4 ), vector3( 2, 0.1f, 2 ) ) );
	m_Primitive[4]->Light( true );
	m_Primitive[4]->getMaterial()->setColor( Color( 1, 1, 1 ) );
#else
	// light source 1
	m_Primitive[4] = new Sphere( vector3( 0, 5, 5 ), 0.1f );
	m_Primitive[4]->Light( true );
	m_Primitive[4]->getMaterial()->setColor( Color( 1, 1, 1 ) );
#endif
	// back plane
	m_Primitive[5] = new PlanePrim( vector3( 0, 0, -1 ), 12.4f );
	m_Primitive[5]->setName( "backplane" );
	//m_Primitive[5]->getMaterial()->setSpecular(0.8f);
	m_Primitive[5]->getMaterial()->setReflection( 0.0f );
	m_Primitive[5]->getMaterial()->setRefraction( 0.0f );
	m_Primitive[5]->getMaterial()->setDiffuse( 1.0f );
	m_Primitive[5]->getMaterial()->setColor( Color( 0.4f, 0.3f, 0.3f ) );
	// ceiling
	m_Primitive[6] = new PlanePrim( vector3( 0, -1, 0 ), 5.2f );
	m_Primitive[6]->setName( "ceiling" );
	//m_Primitive[6]->getMaterial()->setSpecular(0.8f);
	m_Primitive[6]->getMaterial()->setReflection( 0.0f );
	m_Primitive[6]->getMaterial()->setRefraction( 0.0f );
	m_Primitive[6]->getMaterial()->setDiffuse( 1.0f );
	//m_Primitive[6]->getMaterial()->setColor( Color( 0.4f, 0.3f, 0.3f ) );
	m_Primitive[6]->getMaterial()->setColor( Color( 0.4f, 0.0f, 0.0f ) );
	m_Primitives = 7;

#endif

#ifdef SCENE_CORNELLBOX
	m_Primitive = new Primitive*[500000];
	// ground plane
	m_Primitive[0] = new PlanePrim( vector3( 0, 1, 0 ), 4.4f );
	m_Primitive[0]->setName( "plane" );
	m_Primitive[0]->getMaterial()->setReflection( 0.5f );
	m_Primitive[0]->getMaterial()->setSpecular(0.8f);
	m_Primitive[0]->getMaterial()->setRefraction( 0.0f );
	m_Primitive[0]->getMaterial()->setDiffuse( 1.0f );
	m_Primitive[0]->getMaterial()->setColor( Color( 0.2f, 0.2f, 0.2f ) );
	// big sphere
	m_Primitive[1] = new Sphere( vector3( 0, -1.7f, 7 ), 2.5 );
	m_Primitive[1]->setName( "big sphere" );
	m_Primitive[1]->getMaterial()->setReflection( 0.3f );
	m_Primitive[1]->getMaterial()->setRefraction( 0.9f );
	m_Primitive[1]->getMaterial()->setRefr_Rate( 1.3f );
	m_Primitive[1]->getMaterial()->setColor( Color( 0.7f, 0.7f, 1.0f ) );
	m_Primitive[1]->getMaterial()->setDiffRefl( 0.005f );
	// small sphere
	m_Primitive[2] = new Sphere( vector3( -6, -3.7f, 5 ), 0.7 );
	m_Primitive[2]->setName( "small sphere" );
	m_Primitive[2]->getMaterial()->setReflection( 0.8f );
	m_Primitive[2]->getMaterial()->setRefraction( 0.0f );
	m_Primitive[2]->getMaterial()->setRefr_Rate( 1.3f );
	m_Primitive[2]->getMaterial()->setDiffuse( 0.1f );
	m_Primitive[2]->getMaterial()->setColor( Color( 0.7f, 0.7f, 1.0f ) );
	m_Primitive[2]->getMaterial()->setDiffRefl( 0.3f );
	// third sphere
	m_Primitive[3] = new Sphere( vector3( 4, -3.2f, 7 ), 1 );
	m_Primitive[3]->setName( "small sphere" );
	m_Primitive[3]->getMaterial()->setReflection( 0.5f );
	m_Primitive[3]->getMaterial()->setRefraction( 0.01f );
	m_Primitive[3]->getMaterial()->setRefr_Rate( 1.3f );
	m_Primitive[3]->getMaterial()->setDiffuse( 0.1f );
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
	m_Primitive[5]->getMaterial()->setSpecular(0.8f);
	m_Primitive[5]->getMaterial()->setReflection( 0.0f );
	m_Primitive[5]->getMaterial()->setRefraction( 0.0f );
	m_Primitive[5]->getMaterial()->setDiffuse( 1.0f );
	m_Primitive[5]->getMaterial()->setColor( Color( 0.4f, 0.3f, 0.3f ) );
	// ceiling
	m_Primitive[6] = new PlanePrim( vector3( 0, -1, 0), 5.2f);
	m_Primitive[6]->setName( "ceiling" );
	m_Primitive[6]->getMaterial()->setSpecular(0.8f);
	m_Primitive[6]->getMaterial()->setReflection( 0.0f );
	m_Primitive[6]->getMaterial()->setRefraction( 0.0f );
	m_Primitive[6]->getMaterial()->setDiffuse( 1.0f );
	m_Primitive[6]->getMaterial()->setColor( Color( 0.4f, 0.3f, 0.3f ) );
	/*
	m_Primitive[7] = new Sphere( vector3( 0, 5, 5 ), 0.1f );
	m_Primitive[7]->Light( true );
	m_Primitive[7]->getMaterial()->setColor( Color( 1, 1, 1 ) );
	*/
	m_Primitive[7] = new PlanePrim( vector3( 1, 0, 0), 7.0f);
	m_Primitive[7]->setName( "right plane" );
	m_Primitive[7]->getMaterial()->setSpecular(0.8f);
	m_Primitive[7]->getMaterial()->setReflection( 0.0f );
	m_Primitive[7]->getMaterial()->setRefraction( 0.0f );
	m_Primitive[7]->getMaterial()->setDiffuse( 2.0f );
	m_Primitive[7]->getMaterial()->setColor( Color( 0.2f, 0.0f, 0.0f ) );
	
	m_Primitive[8] = new PlanePrim( vector3( -1, 0, 0), 7.0f);
	m_Primitive[8]->setName( "left plane" );
	m_Primitive[8]->getMaterial()->setSpecular(0.8f);
	m_Primitive[8]->getMaterial()->setReflection( 0.0f );
	m_Primitive[8]->getMaterial()->setRefraction( 0.0f );
	m_Primitive[8]->getMaterial()->setDiffuse( 2.0f );
	m_Primitive[8]->getMaterial()->setColor( Color( 0.0f, 0.0f, 0.2f ) );
	
	m_Primitive[9] = new PlanePrim( vector3( 0, 0, 1 ), 6.0f );
	m_Primitive[9]->setName( "backplane2" );
	m_Primitive[9]->getMaterial()->setSpecular(0.8f);
	m_Primitive[9]->getMaterial()->setReflection( 0.0f );
	m_Primitive[9]->getMaterial()->setRefraction( 0.0f );
	m_Primitive[9]->getMaterial()->setDiffuse( 1.0f );
	m_Primitive[9]->getMaterial()->setColor( Color( 0.0f, 0.2f, 0.0f ) );

	m_Primitives = 10;
#endif

#ifdef SCENE_OBJCORNELLBOX
	m_Primitive = new Primitive*[500000];
	// ground plane
	m_Primitive[0] = new PlanePrim( vector3( 0, 1, 0 ), 4.4f );
	m_Primitive[0]->setName( "plane" );
	m_Primitive[0]->getMaterial()->setReflection( 0.5f );
	m_Primitive[0]->getMaterial()->setSpecular(0.8f);
	m_Primitive[0]->getMaterial()->setRefraction( 0.0f );
	m_Primitive[0]->getMaterial()->setDiffuse( 1.0f );
	m_Primitive[0]->getMaterial()->setColor( Color( 0.2f, 0.2f, 0.2f ) );
	// small sphere
	m_Primitive[2] = new Sphere( vector3( -6, -3.7f, 5 ), 0.7 );
	m_Primitive[2]->setName( "small sphere" );
	m_Primitive[2]->getMaterial()->setReflection( 0.8f );
	m_Primitive[2]->getMaterial()->setRefraction( 0.0f );
	m_Primitive[2]->getMaterial()->setRefr_Rate( 1.3f );
	m_Primitive[2]->getMaterial()->setDiffuse( 0.1f );
	m_Primitive[2]->getMaterial()->setColor( Color( 0.7f, 0.7f, 1.0f ) );
	m_Primitive[2]->getMaterial()->setDiffRefl( 0.3f );
	// third sphere
	m_Primitive[3] = new Sphere( vector3( 4, -3.2f, 7 ), 1 );
	m_Primitive[3]->setName( "small sphere" );
	m_Primitive[3]->getMaterial()->setReflection( 0.5f );
	m_Primitive[3]->getMaterial()->setRefraction( 0.01f );
	m_Primitive[3]->getMaterial()->setRefr_Rate( 1.3f );
	m_Primitive[3]->getMaterial()->setDiffuse( 0.1f );
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
	m_Primitive[5]->getMaterial()->setSpecular(0.8f);
	m_Primitive[5]->getMaterial()->setReflection( 0.0f );
	m_Primitive[5]->getMaterial()->setRefraction( 0.0f );
	m_Primitive[5]->getMaterial()->setDiffuse( 1.0f );
	m_Primitive[5]->getMaterial()->setColor( Color( 0.4f, 0.3f, 0.3f ) );
	// ceiling
	m_Primitive[6] = new PlanePrim( vector3( 0, -1, 0), 5.2f);
	m_Primitive[6]->setName( "ceiling" );
	m_Primitive[6]->getMaterial()->setSpecular(0.8f);
	m_Primitive[6]->getMaterial()->setReflection( 0.0f );
	m_Primitive[6]->getMaterial()->setRefraction( 0.0f );
	m_Primitive[6]->getMaterial()->setDiffuse( 1.0f );
	m_Primitive[6]->getMaterial()->setColor( Color( 0.4f, 0.3f, 0.3f ) );
	/*
	m_Primitive[7] = new Sphere( vector3( 0, 5, 5 ), 0.1f );
	m_Primitive[7]->Light( true );
	m_Primitive[7]->getMaterial()->setColor( Color( 1, 1, 1 ) );
	*/
	m_Primitive[7] = new PlanePrim( vector3( 1, 0, 0), 7.0f);
	m_Primitive[7]->setName( "right plane" );
	m_Primitive[7]->getMaterial()->setSpecular(0.8f);
	m_Primitive[7]->getMaterial()->setReflection( 0.0f );
	m_Primitive[7]->getMaterial()->setRefraction( 0.0f );
	m_Primitive[7]->getMaterial()->setDiffuse( 2.0f );
	m_Primitive[7]->getMaterial()->setColor( Color( 0.2f, 0.0f, 0.0f ) );
	
	m_Primitive[8] = new PlanePrim( vector3( -1, 0, 0), 7.0f);
	m_Primitive[8]->setName( "left plane" );
	m_Primitive[8]->getMaterial()->setSpecular(0.8f);
	m_Primitive[8]->getMaterial()->setReflection( 0.0f );
	m_Primitive[8]->getMaterial()->setRefraction( 0.0f );
	m_Primitive[8]->getMaterial()->setDiffuse( 2.0f );
	m_Primitive[8]->getMaterial()->setColor( Color( 0.0f, 0.0f, 0.2f ) );
	
	m_Primitive[1] = new PlanePrim( vector3( 0, 0, 1 ), 6.0f );
	m_Primitive[1]->setName( "backplane2" );
	m_Primitive[1]->getMaterial()->setSpecular(0.8f);
	m_Primitive[1]->getMaterial()->setReflection( 0.0f );
	m_Primitive[1]->getMaterial()->setRefraction( 0.0f );
	m_Primitive[1]->getMaterial()->setDiffuse( 1.0f );
	m_Primitive[1]->getMaterial()->setColor( Color( 0.0f, 0.2f, 0.0f ) );

	m_Primitives = 9;
	Object dragon;
	dragon.setInfo(vector3( 0, -5.0f, 7),20);
	dragon.readin("bunny.obj",m_Primitive,m_Primitives);
	Material* m =  new Material;
	m->setColor(Color(0.5,0.5,0.5));
	m->setDiffRefl(0.0);
	m->setDiffuse(2.0);
	m->setReflection(0.0);
	m->setRefraction(0.0);
	m->setRefr_Rate(1.5);
	m->setSpecular(0.0);
	dragon.setMaterial(m);
#endif

#ifdef SCENE_CORNELLBOX2
	m_Primitive = new Primitive*[500000];
	// ground plane
	m_Primitive[0] = new PlanePrim( vector3( 0, 1, 0 ), 4.4f );
	m_Primitive[0]->setName( "plane" );
	m_Primitive[0]->getMaterial()->setReflection( 0.0f );
	m_Primitive[0]->getMaterial()->setSpecular(0.8f);
	m_Primitive[0]->getMaterial()->setRefraction( 0.0f );
	m_Primitive[0]->getMaterial()->setDiffuse( 1.0f );
	m_Primitive[0]->getMaterial()->setColor( Color( 0.2f, 0.2f, 0.2f ) );
#if 0
	// area light
	m_Primitive[1] = new Box( BoundingBox( vector3( -1, 4.8, 4 ), vector3( 2, 0.01f, 2 ) ) );
	m_Primitive[1]->Light( true );
	m_Primitive[1]->getMaterial()->setColor( Color( 1, 1, 1 ) );
#else
	// light source 1
	//m_Primitive[1] = new Sphere( vector3( 0, 4.8, 5 ), 0.1f );
	m_Primitive[1] = new Sphere( vector3( 0, 4.8, 0 ), 0.1f );
	m_Primitive[1]->Light( true );
	m_Primitive[1]->getMaterial()->setColor( Color( 1, 1, 1 ) );
#endif
	// back plane
	m_Primitive[2] = new PlanePrim( vector3( 0, 0, -1 ), 12.4f );
	m_Primitive[2]->setName( "backplane" );
	m_Primitive[2]->getMaterial()->setSpecular(0.8f);
	m_Primitive[2]->getMaterial()->setReflection( 0.8f );
	m_Primitive[2]->getMaterial()->setRefraction( 0.0f );
	m_Primitive[2]->getMaterial()->setDiffuse( 1.0f );
	m_Primitive[2]->getMaterial()->setColor( Color( 0.4f, 0.3f, 0.3f ) );
	// ceiling
	m_Primitive[3] = new PlanePrim( vector3( 0, -1, 0), 5.2f);
	m_Primitive[3]->setName( "ceiling" );
	m_Primitive[3]->getMaterial()->setSpecular(0.8f);
	m_Primitive[3]->getMaterial()->setReflection( 0.0f );
	m_Primitive[3]->getMaterial()->setRefraction( 0.0f );
	m_Primitive[3]->getMaterial()->setDiffuse( 1.0f );
	m_Primitive[3]->getMaterial()->setColor( Color( 0.4f, 0.3f, 0.3f ) );
	/*
	m_Primitive[7] = new Sphere( vector3( 0, 5, 5 ), 0.1f );
	m_Primitive[7]->Light( true );
	m_Primitive[7]->getMaterial()->setColor( Color( 1, 1, 1 ) );
	*/
	m_Primitive[4] = new PlanePrim( vector3( 1, 0, 0), 7.0f);
	m_Primitive[4]->setName( "right plane" );
	m_Primitive[4]->getMaterial()->setSpecular(0.8f);
	m_Primitive[4]->getMaterial()->setReflection( 0.0f );
	m_Primitive[4]->getMaterial()->setRefraction( 0.0f );
	m_Primitive[4]->getMaterial()->setDiffuse( 2.0f );
	m_Primitive[4]->getMaterial()->setColor( Color( 0.2f, 0.0f, 0.0f ) );
	
	m_Primitive[5] = new PlanePrim( vector3( -1, 0, 0), 7.0f);
	m_Primitive[5]->setName( "left plane" );
	m_Primitive[5]->getMaterial()->setSpecular(0.8f);
	m_Primitive[5]->getMaterial()->setReflection( 0.0f );
	m_Primitive[5]->getMaterial()->setRefraction( 0.0f );
	m_Primitive[5]->getMaterial()->setDiffuse( 2.0f );
	m_Primitive[5]->getMaterial()->setColor( Color( 0.0f, 0.0f, 0.2f ) );
	/*
	m_Primitive[6] = new PlanePrim( vector3( 0, 0, 1 ), 6.0f );
	m_Primitive[6]->setName( "backplane2" );
	m_Primitive[6]->getMaterial()->setSpecular(0.8f);
	m_Primitive[6]->getMaterial()->setReflection( 0.0f );
	m_Primitive[6]->getMaterial()->setRefraction( 0.0f );
	m_Primitive[6]->getMaterial()->setDiffuse( 1.0f );
	m_Primitive[6]->getMaterial()->setColor( Color( 0.0f, 0.2f, 0.0f ) );
	*/
	m_Primitives = 6;
	Object dragon;
	dragon.setInfo(vector3( 0, -5.0f, 7),20);
	dragon.readin("bunny.obj",m_Primitive,m_Primitives);
	//std::cout << m_Primitives << std::endl;
	//std::cout << dragon.TriangleVec.size() << std::endl;
	Material* m =  new Material;
	m->setColor(Color(0.5,0.5,0.5));
	m->setDiffRefl(0.0);
	m->setDiffuse(2.0);
	m->setReflection(0.0);
	m->setRefraction(0.0);
	m->setRefr_Rate(1.5);
	m->setSpecular(0.0);
	dragon.setMaterial(m);
#endif

//#ifndef PATHTRACING
	BuildGrid();
//#endif
}

void Scene::BuildGrid()
{
	// initialize regular grid
	m_Grid = new vector<Primitive*>[GRIDSIZE * GRIDSIZE * GRIDSIZE];
	memset( m_Grid, 0, GRIDSIZE * GRIDSIZE * GRIDSIZE * 4 );
	//vector3 p1(-14, -5, -6), p2( 14, 8, 30 );
	//vector3 p1(-20, -20, -20), p2( 20, 20, 20 );
	vector3 p1(-100, -100, -100), p2( 200, 200, 200 );
	// calculate cell width, height and depth
	double dx = (p2.x - p1.x) / GRIDSIZE, dx_reci = 1.0f / dx;
	double dy = (p2.y - p1.y) / GRIDSIZE, dy_reci = 1.0f / dy;
	double dz = (p2.z - p1.z) / GRIDSIZE, dz_reci = 1.0f / dz;
	m_Boundary = BoundingBox( p1, p2 - p1 );
	m_Light = new Primitive*[MAXLIGHTS];
	m_Lights = 0;
	// store primitives in the grid cells
	for ( int p = 0; p < m_Primitives; p++ )
	{
		if (m_Primitive[p]->IsLight()) m_Light[m_Lights++] = m_Primitive[p];
		BoundingBox bound = m_Primitive[p]->getBoundingBox();
		vector3 bv1 = bound.getPos(), bv2 = bound.getPos() + bound.getSize();
		// find out which cells could contain the primitive (based on BoundingBox)
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
			// construct BoundingBox for current cell
			int idx = x + y * GRIDSIZE + z * GRIDSIZE * GRIDSIZE;
			vector3 pos( p1.x + x * dx, p1.y + y * dy, p1.z + z * dz );
			BoundingBox cell( pos, vector3( dx, dy, dz ) );
			// do an accurate BoundingBox / primitive intersection test
			if (m_Primitive[p]->H_IntersectBox( cell ))
			{
				m_Grid[idx].push_back(m_Primitive[p]);
			}
		}
	}
}

}; // namespace HYF
