#include "all.h"
#include <assert.h>

using namespace cv;
namespace HYF {

Engine::Engine()
{
	m_Scene = new Scene();
	m_Width = 800;
	m_Height = 600;
}

Engine::~Engine()
{
	delete m_Scene;
}

void Engine::setTarget()
{
	m_SR.x = GRIDSIZE / m_Scene->getBoundary().getSize().x;//单位长度内有多少grid
	m_SR.y = GRIDSIZE / m_Scene->getBoundary().getSize().y;
	m_SR.z = GRIDSIZE / m_Scene->getBoundary().getSize().z;
	m_CW = m_Scene->getBoundary().getSize() * (1.0f / GRIDSIZE);//单位gird长度
}

int Engine::findNearestKD(Ray& ray, double& p_Dist, Primitive*& p_Prim)
{
	bool is_light = false;
	int in_out = 0;
	//在场景中的所有物体中寻找最近的一个交点
	/*
	for (auto& it : scene.sphere_vec){
		IntersectResult temp;
		int re = it->intersect(ray, temp);
		if (re){
			if (temp.distance < result.distance){
				result = temp;
				in_out = re;
			}
		}
	}
	for (auto& it : scene.plane_vec){
		IntersectResult temp;
		int re = it->intersect(ray, temp);
		if (re){
			if (temp.distance < result.distance){
				result = temp;
				in_out = re;
			}
		}
	}

	for (auto& it : scene.plight_vec){
		IntersectResult temp;
		int re = (it->get()).intersect(ray, temp);
		if (re){
			if (temp.distance < result.distance){
				is_light = true;
				result = temp;
				result.primi = it;
				in_out = re;
			}
		}
	}

	for (auto& it : scene.blight_vec){
		IntersectResult temp;
		int re = (it->get()).intersect(ray, temp);
		if (re){
			if (temp.distance < result.distance){
				is_light = true;
				result = temp;
				result.primi = it;
				in_out = re;
			}
		}
	}
	*/
	//double dist = 1e10;
	p_Dist = INF;
	for ( int s = 0; s < m_Scene->getNrPrimitives(); s++ )
	{
		Primitive* pr = m_Scene->getPrimitive( s );
		int res;
		if (res = pr->Intersect( ray, p_Dist )) 
		{
			p_Prim = pr;
			in_out = res;
			//std::cout << "intersect\n";
			//result = res; // 0 = miss, 1 = hit, -1 = hit from inside primitive
		}
	}
	for (auto& it : m_Scene->poly_vec){
		IntersectResult temp;
		int re = it->intersect(ray, temp);
		if (re){
			if (temp.distance < p_Dist){
				p_Dist = temp.distance;
				p_Prim = temp.primi;
				in_out = re;
			}
		}
	}

	//IntersectResult temp;
	//int re = scene.root->intersect(ray, temp);
	//if (re){
	//	if (temp.distance < result.distance){
	//		result = temp;
	//		in_out = re;
	//	}
	//}

	if(p_Dist > INF - 1)//没有相加的物体返回0
		return 0;
	else //相交了的话反映是内部还是外部
		return in_out;
}

int Engine::FindNearest( Ray& p_Ray, double& p_Dist, Primitive*& p_Prim )
{
#ifdef KD
	return findNearestKD(p_Ray,p_Dist,p_Prim);
#endif
	int retval = MISS;
	vector3 raydir, curpos;
	BoundingBox e = m_Scene->getBoundary();
	curpos = p_Ray.getOrigin();
	raydir = p_Ray.getDirection();
	// setup 3DDDA (double check reusability of primary ray data)
	vector3 cb, tmax, tdelta, cell;
	cell = (curpos - e.getPos()) * m_SR;
	int stepX, outX, X = (int)cell.x;
	int stepY, outY, Y = (int)cell.y;
	int stepZ, outZ, Z = (int)cell.z;
	if ((X < 0) || (X >= GRIDSIZE) || (Y < 0) || (Y >= GRIDSIZE) || (Z < 0) || (Z >= GRIDSIZE)) return 0;
	if (raydir.x > 0)
	{
		stepX = 1, outX = GRIDSIZE;
		cb.x = e.getPos().x + (X + 1) * m_CW.x;
	}
	else 
	{
		stepX = -1, outX = -1;
		cb.x = e.getPos().x + X * m_CW.x;
	}
	if (raydir.y > 0.0f)
	{
		stepY = 1, outY = GRIDSIZE;
		cb.y = e.getPos().y + (Y + 1) * m_CW.y; 
	}
	else 
	{
		stepY = -1, outY = -1;
		cb.y = e.getPos().y + Y * m_CW.y;
	}
	if (raydir.z > 0.0f)
	{
		stepZ = 1, outZ = GRIDSIZE;
		cb.z = e.getPos().z + (Z + 1) * m_CW.z;
	}
	else 
	{
		stepZ = -1, outZ = -1;
		cb.z = e.getPos().z + Z * m_CW.z;
	}
	double rxr, ryr, rzr;
	if (raydir.x != 0)
	{
		rxr = 1.0f / raydir.x;
		tmax.x = (cb.x - curpos.x) * rxr; 
		tdelta.x = m_CW.x * stepX * rxr;
	}
	else tmax.x = 1000000;
	if (raydir.y != 0)
	{
		ryr = 1.0f / raydir.y;
		tmax.y = (cb.y - curpos.y) * ryr; 
		tdelta.y = m_CW.y * stepY * ryr;
	}
	else tmax.y = 1000000;
	if (raydir.z != 0)
	{
		rzr = 1.0f / raydir.z;
		tmax.z = (cb.z - curpos.z) * rzr; 
		tdelta.z = m_CW.z * stepZ * rzr;
	}
	else tmax.z = 1000000;
	// start stepping
	//ObjectList* list = 0;
	//ObjectList** grid = m_Scene->getGrid();
	std::vector<Primitive*> list;
	//std::vector<Primitive*>* grid = m_Scene->getGrid();
	auto grid = m_Scene->getGrid();
	p_Prim = 0;
	// trace primary ray
	while (1)
	{
		list = grid[X + (Y << GRIDSHFT) + (Z << (GRIDSHFT * 2))];
		unsigned int list_index = 0;
		while (list_index < list.size())
		{
			//Primitive* pr = list->getPrimitive();
			Primitive* pr = list[list_index];
			int result;
			//if (pr->getLastRayID() != p_Ray.getID()) 
				if (result = pr->Intersect( p_Ray, p_Dist )) 
			{
				retval = result;
				p_Prim = pr;
				goto testloop;
			}
			//list = list->getNext();
				list_index++;
		}
		if (tmax.x < tmax.y)
		{
			if (tmax.x < tmax.z)
			{
				X = X + stepX;
				if (X == outX) return MISS;
				tmax.x += tdelta.x;
			}
			else
			{
				Z = Z + stepZ;
				if (Z == outZ) return MISS;
				tmax.z += tdelta.z;
			}
		}
		else
		{
			if (tmax.y < tmax.z)
			{
				Y = Y + stepY;
				if (Y == outY) return MISS;
				tmax.y += tdelta.y;
			}
			else
			{
				Z = Z + stepZ;
				if (Z == outZ) return MISS;
				tmax.z += tdelta.z;
			}
		}
	}
testloop:
	while (1)
	{
		list = grid[X + (Y << GRIDSHFT) + (Z << (GRIDSHFT * 2))];
		unsigned int list_index = 0;
		//while (list)
		while(list_index < list.size())
		{
			//Primitive* pr = list->getPrimitive();
			Primitive* pr = list[list_index];
			int result;
			//if (pr->getLastRayID() != p_Ray.getID()) 
				if (result = pr->Intersect( p_Ray, p_Dist )) 
			{
				p_Prim = pr;
				retval = result;
			}
			//list = list->getNext();
				list_index++;
		}
		if (tmax.x < tmax.y)
		{
			if (tmax.x < tmax.z)
			{
				if (p_Dist < tmax.x) break;
				X = X + stepX;
				if (X == outX) break;
				tmax.x += tdelta.x;
			}
			else
			{
				if (p_Dist < tmax.z) break;
				Z = Z + stepZ;
				if (Z == outZ) break;
				tmax.z += tdelta.z;
			}
		}
		else
		{
			if (tmax.y < tmax.z)
			{
				if (p_Dist < tmax.y) break;
				Y = Y + stepY;
				if (Y == outY) break;
				tmax.y += tdelta.y;
			}
			else
			{
				if (p_Dist < tmax.z) break;
				Z = Z + stepZ;
				if (Z == outZ) break;
				tmax.z += tdelta.z;
			}
		}
	}
	return retval;
}

double Engine::calShade(Primitive* p_Light, vector3 p_pi, vector3& p_Dir,double p_Sample,double p_SampleRange)
{
	double shade = 0.0;
	Primitive* prim = 0;
	if(p_Light->getType() == Primitive::SPHERE)
	{
		Sphere* light = (Sphere*)p_Light;
		vector3 O = light->getCentre();
		p_Dir = O - p_pi;
		NORMALIZE(p_Dir);
		double R = light->getRadius();
		vector3 dir = O - p_pi;
		double dist = LENGTH(dir);
		NORMALIZE(dir);
		if (FindNearest( Ray( p_pi + dir * EPS, dir), dist, prim ))
			if (prim == p_Light) 
				shade += 1.0;
	}
	else if(p_Light->getType() == Primitive::BOX)
	{
		shade = 0.0;
		Box* light = (Box*)p_Light;
		vector3 P = light->getPos();
		vector3 size = light->getSize();
		p_Dir = P + 0.5 * size - p_pi;
		NORMALIZE(p_Dir);
		int n = (int)floor(sqrt(p_Sample + 0.5));
		for(int i = 0;i < n;++i)
			for(int j = 0;j < n;++j)
			{
				vector3 d = vector3(size.x / n,0.0,size.z / n);
				vector3 pos = P + vector3(d.x * (i + (double)rand() / RAND_MAX),0.0,d.z * (j + (double)rand() / RAND_MAX));
				vector3 dir = pos - p_pi;
				double dist = LENGTH(dir);
				NORMALIZE(dir);
				if (FindNearest( Ray( p_pi + dir * EPS, dir), dist, prim ))
					if (prim == p_Light) 
						shade += 1.0 / (n * n);
			}
	}
	return shade;

	//--------------------------------------------
	//vector3 delta = vector3();
	//double shade = 0.0;
	//Primitive* prim = 0;
	if(p_Light->getType() == Primitive::SPHERE)
	{
		//int max_R = 2,max_C = 1;
		Sphere* light = (Sphere*)p_Light;
		vector3 O = light->getCentre();
		p_Dir = O - p_pi;
		NORMALIZE(p_Dir);
		double R = light->getRadius();
		vector3 dir = O - p_pi;
		double dist = LENGTH(dir);
		NORMALIZE(dir);
		if (FindNearest( Ray( p_pi + dir * EPS, dir), dist, prim ))
			if (prim == p_Light) 
				shade += 1.0;
		/*
		for(int i = 0;i < max_R;++i)
			for(int j = 0;j < max_C;++j)
			{
				vector3 d = vector3(std::cos(2 * j * PI / max_C),0.0,std::sin(2 * j * PI / max_C));
				vector3 pos = O + R / (max_R - 1) * i * d;
				vector3 dir = pos - p_pi;
				double dist = LENGTH(dir);
				NORMALIZE(dir);
				if (FindNearest( Ray( p_pi + dir * EPS, dir), dist, prim ))
					if (prim == p_Light) shade += (1.0 / (max_R * max_C));
			}
		*/
	}
	else if(p_Light->getType() == Primitive::BOX)
	{
		//printf("box\n");
		shade = 0.0;
		int max_X = 10,max_Z = 10;
		Box* light = (Box*)p_Light;
		vector3 P = light->getPos();
		vector3 size = light->getSize();
		p_Dir = P + 0.5 * size - p_pi;
		NORMALIZE(p_Dir);
		for(int i = 0;i < max_X;++i)
			for(int j = 0;j < max_Z;++j)
			{
				vector3 d = vector3(size.x / max_X,0.0,size.z / max_Z);
				//printf("%llf,%llf,%llf\n",d.x,d.y,d.z);
				vector3 pos = P + vector3(d.x * (i + (double)rand() / RAND_MAX),0.0,d.z * (j + (double)rand() / RAND_MAX));
				//monte carlo 
				vector3 dir = pos - p_pi;
				double dist = LENGTH(dir);
				NORMALIZE(dir);
				if (FindNearest( Ray( p_pi + dir * EPS, dir), dist, prim ))
					if (prim == p_Light) 
						shade += (1.0 / (max_X * max_Z));
			}
		/*
		shade = 0;
		Box* b = (Box*)p_Light;
		p_Dir = (b->getPos() + 0.5f * b->getSize()) - p_pi;
		NORMALIZE( p_Dir );
		for ( int x = 0; x < 3; x++ ) for ( int y = 0; y < 3; y++ )
		{
			vector3 lp( b->getPos().x + x, b->getPos().y, b->getPos().z + y );
			vector3 dir = lp - p_pi;
			double ldist = (double)LENGTH( dir );
			dir *= 1.0f / ldist;
			if (FindNearest( Ray( p_pi + dir * EPS, dir), ldist, prim ))
				if (prim == p_Light) shade += 1.0f / 9;
		}
		*/
	}
	//printf("%llf\n",shade);
	//return 1.0;
	//for debug
	return shade;
}




#ifndef PATHTRACING
Primitive* Engine::Runtracer( Ray& p_Ray, Color& p_Col, int p_Depth, double p_Refr_Rate, double& p_Dist ,double p_Sample,double p_SampleRange)
{
	if (p_Depth > TRACEDEPTH) return 0;
	// trace primary ray
	p_Dist = 1000000.0;//首先让距离最大，然后逐步通过intersect函数缩小
	vector3 pi;
	Primitive* prim = 0;
	int result;
	// find the nearest intersection
	/*
	for ( int s = 0; s < m_Scene->getNrPrimitives(); s++ )
	{
		Primitive* pr = m_Scene->getPrimitive( s );
		int res;
		if (res = pr->Intersect( p_Ray, p_Dist )) 
		{
			prim = pr;
			result = res; // 0 = miss, 1 = hit, -1 = hit from inside primitive
		}
	}
	*/
#ifndef KD
	if (!(result = FindNearest( p_Ray, p_Dist, prim ))) return 0;
#else
	if (!(result = findNearestKD( p_Ray, p_Dist, prim ))) return 0;
#endif
	//计算一根光线Ray最近的交汇点和距离
	// no hit, terminate ray
	if (!prim) return 0;//光线不和任何物体相交
	//std::cout << "PRIM!=0" << std::endl;
	// handle intersection
	if (prim->IsLight())//如果光线最近遇到光源，直接返回光源颜色
	{
		// we hit a light, stop tracing
		p_Col += Color( 1, 1, 1 );
		//p_Col += prim->getMaterial()->getColor();
		//p_Col = prim->getMaterial()->getColor();
	}
	else//否则，最近的是不发光物体
	{
		//std::cout << "is not light\n";
		// determine color at point of intersection
		pi = p_Ray.getOrigin() + p_Ray.getDirection() * p_Dist;//pi为光线与最近物体交汇的地方
		//std::cout << pi.x << " " << pi.y << " " << pi.z << "\n";
		// trace lights
		//for ( int l = 0; l < m_Scene->getNrPrimitives(); l++ )//再次枚举所有物体
		//std::cout << m_Scene->getNrLights() << "\n";
		for(int l = 0;l < m_Scene->getNrLights() ;++l)
		{
			//Primitive* p = m_Scene->getPrimitive( l );
			Primitive*p = m_Scene->getLight(l);
			if (p->IsLight())//物体为光源时
			{
				Primitive* light = p;
				// handle point light source
				double shade = 1.0;
				/*
				if (light->getType() == Primitive::SPHERE)//球形光源
				{
					vector3 L = ((Sphere*)light)->getCentre() - pi;
					double tdist = LENGTH( L );//距离tdist
					//L *= (1.0 / tdist);//L单位化
					NORMALIZE(L);
					Ray r = Ray( pi + L * EPS, L );//从光线与物体交点到该光源的Ray r
					///*
					//for ( int s = 0; s < m_Scene->getNrPrimitives(); s++ )//检查光线r
					//{
					//	Primitive* pr = m_Scene->getPrimitive( s );
					//	if ((pr != light) && (pr->Intersect( r, tdist )))//如果r和某一个非光源物体相交
					//	{
					//		shade = 0;//则该光源在该处被遮挡，置标记为0
					//		break;
					//	}
					//}
					//
					Primitive* pr;
					FindNearest(r,tdist,pr);
					if(pr != light) shade = 0.0;
				}
				*/
				vector3 L;
				shade = calShade(light,pi,L,p_Sample,p_SampleRange);
				// calculate diffuse shading
				//vector3 L = ((Sphere*)light)->getCentre() - pi;
				//NORMALIZE( L );
				vector3 N = prim->getNormal( pi );//物体在pi处的法向量
				if (prim->getMaterial()->getDiffuse() > 0)//漫反射
				{
					double dot = DOT( L, N );
					if (dot > 0)
					{
						double diff = dot * prim->getMaterial()->getDiffuse() * shade;
						// add diffuse component to ray color
						//p_Col += diff * light->getMaterial()->getColor() * prim->getMaterial()->getColor();
						p_Col += diff * light->getMaterial()->getColor() * prim->getColor(pi);					
					}
				}
				// determine specular component
				if (prim->getMaterial()->getSpecular() > 0)//高光
				{
					// point light source: sample once for specular highlight
					vector3 V = p_Ray.getDirection();//光线方向
					vector3 R = L - 2.0 * DOT( L, N ) * N;
					double dot = DOT( V, R );
					if (dot > 0)
					{
						double spec = pow( dot, 20 ) * prim->getMaterial()->getSpecular() * shade;
						// add specular component to ray color
						p_Col += spec * light->getMaterial()->getColor();
					}
				}
			}
			else
			{
				assert(0);//m_Lights里面有非光源，不合法！
			}
		}
		// calculate reflection
		double refl = prim->getMaterial()->getReflection();
		if (refl > 0.0)//镜面反射
		{
			float drefl = prim->getMaterial()->getDiffRefl();
			vector3 N = prim->getNormal( pi );
			vector3 R = p_Ray.getDirection() - 2.0 * DOT( p_Ray.getDirection(), N ) * N;
			if ((drefl > 0) && (p_Depth < 2))//粗糙镜面反射
			{
				vector3 component1 = vector3( R.z, 0.0, -R.x );
				vector3 component2 = R.Cross( component1 );
				NORMALIZE(component2);
				int num = 20;
				//refl *= m_SScale;
				for ( int i = 0; i < num; i++ )
				{
					double x0,y0;
					while(1)
					{
						x0 = 2.0 * (double)rand() / RAND_MAX - 1.0;
						y0 = 2.0 * (double)rand() / RAND_MAX - 1.0;
						//if((x0 * x0 + y0 * y0) < (drefl * drefl))
						if((x0 * x0 + y0 * y0) < 1.0)
							break;
					}
					x0 *= drefl;
					y0 *= drefl;
					vector3 newR = R + component1 * x0 + component2 * y0;
					NORMALIZE( newR );
					double dist;
					Color rcol( 0, 0, 0 );
#ifdef IMPORTANCE_SAMPLING
					Runtracer( Ray( pi + newR * EPS, newR ), rcol, p_Depth + 1, p_Refr_Rate, dist ,p_Sample * 0.25,p_SampleRange * 4.0);
#else
					Runtracer( Ray( pi + newR * EPS, newR ), rcol, p_Depth + 1, p_Refr_Rate, dist ,p_Sample,p_SampleRange);
#endif
					//p_Col += refl * rcol * prim->getMaterial()->getColor() * (1.0 / (double)num);
					p_Col += refl * rcol * prim->getColor(pi) * (1.0 / (double)num);
				}
			}
			else if (p_Depth < TRACEDEPTH)//光滑镜面反射
			{
				Color rcol( 0, 0, 0 );
				double dist;
#ifdef IMPORTANCE_SAMPLING
				//Runtracer( Ray( pi + newR * EPS, newR ), rcol, p_Depth + 1, p_Refr_Rate, dist ,p_Sample * 0.25,p_SampleRange * 4.0);
				Runtracer( Ray( pi + R * EPS, R ), rcol, p_Depth + 1, p_Refr_Rate, dist ,p_Sample * 0.25,p_SampleRange * 4.0);
#else
				//Runtracer( Ray( pi + newR * EPS, newR ), rcol, p_Depth + 1, p_Refr_Rate, dist ,p_Sample,p_SampleRange);
				Runtracer( Ray( pi + R * EPS, R ), rcol, p_Depth + 1, p_Refr_Rate, dist ,p_Sample,p_SampleRange);
#endif
				//p_Col += refl * rcol * prim->getMaterial()->getColor();
				p_Col += refl * rcol * prim->getColor(pi);
			}
		}
		//计算折射
		double refr = prim->getMaterial()->getRefraction();
		if(refr > 0.0 && p_Depth < TRACEDEPTH)
		{
			Color rcol( 0, 0, 0 );
			double dist;
			vector3 N;
			N = prim->getNormal(pi);
			if(result < 0)
			{
				N = -1.0 * N;
			}
			double tmp_Refr_rate = prim->getMaterial()->getRefr_Rate();
			if(result == INPRIM) tmp_Refr_rate = 1.0;
			double n =  tmp_Refr_rate / p_Refr_Rate;//介质相对于空气的相对折射率
			vector3 V = p_Ray.getDirection();
			double cosi = -DOT( V, N);
			double sinr2 = (1.0 - DOT( V, N) * DOT( V, N)) / (n * n);
			if(0.0 < sinr2 && sinr2 < 1.0)
			{
				double cosr2 = 1.0 - sinr2;
				double sinr = sqrt(sinr2);
				double cosr = sqrt(cosr2);
				vector3 T = (V * (1/n)) + (cosi / n - sqrt( cosr2 )) * N;
#ifdef IMPORTANCE_SAMPLING
				//Runtracer( Ray( pi + newR * EPS, newR ), rcol, p_Depth + 1, p_Refr_Rate, dist ,p_Sample * 0.25,p_SampleRange * 4.0);
				Runtracer(Ray(pi + T * EPS , T),rcol,p_Depth + 1, tmp_Refr_rate,dist,p_Sample * 0.25,p_SampleRange * 4.0);
#else
				//Runtracer( Ray( pi + newR * EPS, newR ), rcol, p_Depth + 1, p_Refr_Rate, dist ,p_Sample,p_SampleRange);
				Runtracer(Ray(pi + T * EPS , T),rcol,p_Depth + 1, tmp_Refr_rate,dist,p_Sample,p_SampleRange);
#endif
				//Color absorbance = prim->getMaterial()->getColor() * 0.15 * -dist;
				Color absorbance = prim->getColor(pi) * 0.15 * -dist;
				Color transparency = Color( exp( absorbance.r ), exp( absorbance.g ), exp( absorbance.b ) );
				p_Col += rcol * transparency;
			}
		}
	}
	return prim;
}

//#define SUPERSAMPLING
bool Engine::HYF_render(cv::Mat& colorim)
{
	//vector3 o( 0, 0, -5 );
	Camera c = Camera();
	//c.setRV(0.005,16);
	Primitive* lastprim = 0;
	for ( int y = 0; y < m_Height; y++ )
	{
		for ( int x = 0; x < m_Width; x++ )
		{
			Color col( 0, 0, 0 );
			
#ifdef SUPERSAMPLING
			//add supersampling here
			for(double i = -1.0;i < 1.5;++i)
				for(double j = -1.0;j < 1.5;++j)
				{
					//vector3 dir = vector3( (1.0 * x + i / 3) / 100 - 4.0 , (1.0 * y + j / 3) / 100 - 3.0, 0 ) - o;
					//NORMALIZE( dir );
					vector3 dir = c.getDir(x,y);
					NORMALIZE(dir);
					Ray r( c.getEye(), dir );
					double dist;
					Primitive* prim = Runtracer( r, col, 1, 1.0, dist ,SAMPLES,(1.0 / SAMPLES));
				}
			int red = (int)(col.r * 256 / 9);
			int green = (int)(col.g * 256 / 9);
			int blue = (int)(col.b * 256 / 9);
			//super sampling
#endif
#ifndef SUPERSAMPLING
			//vector3 dir = vector3( (1.0 * x) / 100 - 4.0 , (1.0 * y) / 100 - 3.0, 0 ) - o;
			//NORMALIZE( dir );
			vector3 dir = c.getDir(x,y);
			NORMALIZE(dir);
			Ray r( c.getEye(), dir );
			double dist;
			Primitive* prim = Runtracer( r, col, 1, 1.0, dist ,SAMPLES,(1.0 / SAMPLES));
#ifdef DEPTH_OF_FIELD
			c.setRV(0.1,9.0);
			for(int oo = 0;oo < 9;++oo)
			{
				//Color tmpCol(0.0,0.0,0.0);
				//prim = Runtracer( c.getRandRay(x,y), tmpCol, 1, 1.0, dist ,SAMPLES,(1.0 / SAMPLES));
				prim = Runtracer( c.getRandRay(x,y), col, 1, 1.0, dist ,SAMPLES,(1.0 / SAMPLES));
				//prim = Runtracer( r, tmpCol, 1, 1.0, dist ,SAMPLES,(1.0 / SAMPLES));
				//col += tmpCol;
			}
			col *= (1.0 / 10);
#endif		
			int red = (int)(col.r * 256);
			int green = (int)(col.g * 256);
			int blue = (int)(col.b * 256);
#endif
			if (red > 255) red = 255;
			if (green > 255) green = 255;
			if (blue > 255) blue = 255;
			colorim.at<Vec3b>(m_Height - y - 1,x) = Vec3b(blue,green,red);
		}
		printf("rendering %dth row...\n",y+1);
		cv::imshow("test",colorim);
		cv::waitKey(10);
	}
	return true;
}

#endif

#ifdef PATHTRACING

 /*
 struct Vec {        // Usage: time ./smallpt 5000 && xv image.ppm 
   double x, y, z;                  // position, also color (r,g,b) 
   Vec(double x_=0, double y_=0, double z_=0){ x=x_; y=y_; z=z_; } 
   Vec operator+(const Vec &b) const { return Vec(x+b.x,y+b.y,z+b.z); } 
   Vec operator-(const Vec &b) const { return Vec(x-b.x,y-b.y,z-b.z); } 
   Vec operator*(double b) const { return Vec(x*b,y*b,z*b); } 
   Vec mult(const Vec &b) const { return Vec(x*b.x,y*b.y,z*b.z); } 
   Vec& norm(){ return *this = *this * (1/sqrt(x*x+y*y+z*z)); } 
   double dot(const Vec &b) const { return x*b.x+y*b.y+z*b.z; } // cross: 
   Vec operator%(Vec&b){return Vec(y*b.z-z*b.y,z*b.x-x*b.z,x*b.y-y*b.x);} 
 }; 
 */
 //struct Ray { Vec o, d; Ray(Vec o_, Vec d_) : o(o_), d(d_) {} }; 
/*
 enum Refl_t { DIFF, SPEC, REFR };  // material types, used in radiance() 
 struct HSphere { 
   double rad;       // radius 
   vector3 p, e, c;      // position, emission, color 
   Refl_t refl;      // reflection type (DIFFuse, SPECular, REFRactive) 
   HSphere(double rad_, vector3 p_, vector3 e_, vector3 c_, Refl_t refl_): 
     rad(rad_), p(p_), e(e_), c(c_), refl(refl_) {} 
   
   double intersect(Ray &r) const { // returns distance, 0 if nohit 
	   vector3 op = p-r.getOrigin(); // Solve t^2*d.d + 2*t*(o-p).d + (o-p).(o-p)-R^2 = 0 
	   double t, eps=1e-4, b=op.Dot(r.getDirection()), det=b*b-op.Dot(op)+rad*rad; 
     if (det<0) return 0; else det=sqrt(det); 
     return (t=b-det)>eps ? t : ((t=b+det)>eps ? t : 0); 
   } 
 }; 
 
 HSphere HSpheres[] = {//Scene: radius, position, emission, color, material 
   HSphere(1e5, vector3( 1e5+1,40.8,81.6), vector3(),vector3(.75,.25,.25),DIFF),//Left 
   HSphere(1e5, vector3(-1e5+99,40.8,81.6),vector3(),vector3(.25,.25,.75),DIFF),//Rght 
   HSphere(1e5, vector3(50,40.8, 1e5),     vector3(),vector3(.75,.75,.75),DIFF),//Back 
   HSphere(1e5, vector3(50,40.8,-1e5+170), vector3(),vector3(),           DIFF),//Frnt 
   HSphere(1e5, vector3(50, 1e5, 81.6),    vector3(),vector3(.75,.75,.75),DIFF),//Botm 
   HSphere(1e5, vector3(50,-1e5+81.6,81.6),vector3(),vector3(.75,.75,.75),DIFF),//Top 
   HSphere(16.5,vector3(27,16.5,47),       vector3(),vector3(1,1,1)*.999, SPEC),//Mirr 
   HSphere(16.5,vector3(73,16.5,78),       vector3(),vector3(1,1,1)*.999, REFR),//Glas 
   HSphere(600, vector3(50,681.6-.27,81.6),vector3(12,12,12),  vector3(), DIFF) //Lite 
 }; 
 */

/*
inline bool intersect(Ray &r, double &t, int &id)
{ 
	double n=sizeof(HSpheres)/sizeof(HSphere), d, inf=t=1e20; 
	for(int i=int(n);i--;) 
		if((d=HSpheres[i].intersect(r))&&d<t)
		{
			t=d;id=i;
		}
	return t<inf; 
} 
*/
void Engine::PTintersect(Ray &r,double& t,Primitive* prim)
{
	for ( int s = 0; s < m_Scene->getNrPrimitives(); s++ )
	{
		Primitive* pr = m_Scene->getPrimitive( s );
		//int res;
		if (pr->Intersect( r, t )) 
		{
			prim = pr;
			//result = res; // 0 = miss, 1 = hit, -1 = hit from inside primitive
		}
		//std::cout << res << "\n";
	}
}

Color Engine::Runtracer(Ray &r, int depth, unsigned short *Xi)
{ 
	//std::cout << depth << "\n";
	if(depth > 1400) return Color(0,0,0);
	double t = 1e20;                         // distance to intersection 
	//int id=0;                               // id of intersected object 
	Primitive* prim = 0;
	//int result;
	//FindNearest(r,t,prim);
	//std::cout << m_Scene->getNrPrimitives() << "\n";
	//PTintersect(r,t,prim);
	/*
	for ( int s = 0; s < m_Scene->getNrPrimitives(); s++ )
	{
		Primitive* pr = m_Scene->getPrimitive( s );
		int res;
		if (res = pr->Intersect( r, t )) 
		{
			prim = pr;
			//result = res; // 0 = miss, 1 = hit, -1 = hit from inside primitive
		}
	}
	*/
#ifndef KD
	FindNearest( r, t, prim );
#else
	findNearestKD(r,t,prim);
#endif
	//std::cout << t << std::endl;
	if (prim == 0) {return vector3();} // if miss, return black 
	//if (!intersect(r, t, id)) {return vector3();} // if miss, return black 

	//const HSphere &obj = HSpheres[id];        // the hit object 
	//vector3 x=r.getOrigin()+r.getDirection()*t, n=(x-obj.p).norm(), nl=n.Dot(r.getDirection())<0?n:n*-1, f=obj.c; 
	
	vector3 x=r.getOrigin()+r.getDirection()*t, n=prim->getNormal(x).norm(), nl=n.Dot(r.getDirection())<0?n:n*-1, f=prim->getMaterial()->getColor(); 
	//std::cout << t << std::endl;
	//std::cout << n.x << " " << n.y << " " << n.z << std::endl;
	//special add
	//vector3 x=r.getOrigin()+r.getDirection()*t;
	//vector3 n=prim->getNormal(x,r.getOrigin());
	//vector3 nl=n.Dot(r.getDirection())<0?n:n*-1, f=prim->getMaterial()->getColor(); 
	
	double p = f.x>f.y && f.x>f.z ? f.x : f.y>f.z ? f.y : f.z; // max refl 
	if (++depth>5)	
		if (erand48(Xi)<p) f=f*(1/p);
		else 
			return prim->getMaterial()->emission;
		//else return obj.e; //R.R. 
	if (prim->getMaterial()->BRDFType == Material::DIFF)
	//if (obj.refl == DIFF)
	{                  // Ideal DIFFUSE reflection 
		double r1=2*PI*erand48(Xi), r2=erand48(Xi), r2s=sqrt(r2); 
		vector3 w=nl, u=((fabs(w.x)>.1?vector3(0,1,0):vector3(1,0,0))%w).norm(), v=w%u; 
		vector3 d = (u*cos(r1)*r2s + v*sin(r1)*r2s + w*sqrt(1-r2)).norm(); 
		return prim->getMaterial()->emission + f.mult(Runtracer(Ray(x,d),depth,Xi)); 
		//return obj.e + f.mult(Runtracer(Ray(x,d),depth,Xi)); 
	} 
	else if (prim->getMaterial()->BRDFType == Material::SPEC)         // Ideal SPECULAR reflection 
		return prim->getMaterial()->emission + f.mult(Runtracer(Ray(x,r.getDirection()-n*2*n.Dot(r.getDirection())),depth,Xi)); 
	Ray reflRay(x, r.getDirection()-n*2*n.Dot(r.getDirection()));     // Ideal dielectric REFRACTION 
	bool into = n.Dot(nl)>0;                // Ray from outside going in? 
	double nc=1, nt=1.5, nnt=into?nc/nt:nt/nc, ddn=r.getDirection().Dot(nl), cos2t; 
	if ((cos2t=1-nnt*nnt*(1-ddn*ddn))<0)    // Total internal reflection 
		return prim->getMaterial()->emission + f.mult(Runtracer(reflRay,depth,Xi)); 
	vector3 tdir = (r.getDirection()*nnt - n*((into?1:-1)*(ddn*nnt+sqrt(cos2t)))).norm(); 
	double a=nt-nc, b=nt+nc, R0=a*a/(b*b), c = 1-(into?-ddn:tdir.Dot(n)); 
	double Re=R0+(1-R0)*c*c*c*c*c,Tr=1-Re,P=.25+.5*Re,RP=Re/P,TP=Tr/(1-P); 
	return prim->getMaterial()->emission + f.mult(depth>2 ? (erand48(Xi)<P ?   // Russian roulette 
		Runtracer(reflRay,depth,Xi)*RP:Runtracer(Ray(x,tdir),depth,Xi)*TP) : 
		Runtracer(reflRay,depth,Xi)*Re+Runtracer(Ray(x,tdir),depth,Xi)*Tr); 
} 

bool Engine::HYF_render(cv::Mat& colorim)
{
	//int w=1024, h=768; //samps = argc==2 ? atoi(argv[1])/4 : 1; // # samples 
	int w=800, h=600;
	int samps = PTSAMP;
	//cv::Mat colorim(h,w,CV_8UC3);
	Ray cam(vector3(50,52,295.6), vector3(0,-0.042612,-1).norm()); // cam pos, dir 
	vector3 cx=vector3(w*.5135/h,0,0), cy=(cx%cam.getDirection()).norm()*.5135, r, *c=new vector3[w*h]; 
	//#pragma omp parallel for schedule(dynamic, 1) private(r)       // OpenMP 
	for (int y=0; y<h; y++)
	{// Loop over image rows 
		//fprintf(stderr,"\rRendering (%d spp) %5.2f%%",samps*4,100.*y/(h-1)); 
		printf("rendering %dth row...\n",y+1);
		short unsigned int Xi[3]={0,0,y*y*y};
		for (unsigned short x=0; x<w; x++)   // Loop cols 
			for (int sy=0, i=(h-y-1)*w+x; sy<2; sy++)     // 2x2 subpixel rows 
				for (int sx=0; sx<2; sx++, r=vector3())
				{// 2x2 subpixel cols 
					for (int s=0; s<samps; s++)
					{ 
						double r1=2*erand48(Xi), dx=r1<1 ? sqrt(r1)-1: 1-sqrt(2-r1); 
						double r2=2*erand48(Xi), dy=r2<1 ? sqrt(r2)-1: 1-sqrt(2-r2); 
						vector3 d = cx*( ( (sx+.5 + dx)/2 + x)/w - .5) + 
							cy*( ( (sy+.5 + dy)/2 + y)/h - .5) + cam.getDirection(); 
						r = r + Runtracer(Ray(cam.getOrigin()+d*140,d.norm()),0,Xi)*(1./samps); 
					} // Camera rays are pushed ^^^^^ forward to start in interior 
					c[i] = c[i] + vector3(clamp(r.x),clamp(r.y),clamp(r.z))*.25; 
					colorim.at<cv::Vec3b>(h - y - 1,x) = cv::Vec3b(toInt(c[i].x), toInt(c[i].y), toInt(c[i].z));
				} 
		//cv::imshow("test",colorim);
		if(y == 100 || y == 200 || y == 300 || y == 400 || y == 500 || y == 600)
			cv::imwrite("tmp.png",colorim);
		cv::waitKey(10);
   } 
   /*
   for (int i=0; i<w*h; i++) 
   {
	   int y = i / w;
	   int x = i - y * w;
	colorim.at<cv::Vec3b>(y,x) = cv::Vec3b(toInt(c[i].x), toInt(c[i].y), toInt(c[i].z));
   }
   */
	return true;
} 

#endif

}; // namespace HYF