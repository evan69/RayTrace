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

int Engine::FindNearest( Ray& p_Ray, double& p_Dist, Primitive*& p_Prim )
{
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

double Engine::calShade(Primitive* p_Light, vector3 p_pi, vector3& p_Dir)
{
	
	//vector3 delta = vector3();
	double shade = 0.0;
	Primitive* prim = 0;
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
	return shade;
}

Primitive* Engine::Runtracer( Ray& p_Ray, Color& p_Col, int p_Depth, double p_Refr_Rate, double& p_Dist )
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
	if (!(result = FindNearest( p_Ray, p_Dist, prim ))) return 0;
	//计算一根光线Ray最近的交汇点和距离
	// no hit, terminate ray
	if (!prim) return 0;//光线不和任何物体相交
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
		// determine color at point of intersection
		pi = p_Ray.getOrigin() + p_Ray.getDirection() * p_Dist;//pi为光线与最近物体交汇的地方
		// trace lights
		//for ( int l = 0; l < m_Scene->getNrPrimitives(); l++ )//再次枚举所有物体
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
				shade = calShade(light,pi,L);
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
					Runtracer( Ray( pi + newR * EPS, newR ), rcol, p_Depth + 1, p_Refr_Rate, dist );
					//p_Col += refl * rcol * prim->getMaterial()->getColor() * (1.0 / (double)num);
					p_Col += refl * rcol * prim->getColor(pi) * (1.0 / (double)num);
				}
			}
			else if (p_Depth < TRACEDEPTH)//光滑镜面反射
			{
				Color rcol( 0, 0, 0 );
				double dist;
				Runtracer( Ray( pi + R * EPS, R ), rcol, p_Depth + 1, p_Refr_Rate, dist );
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
				Runtracer(Ray(pi + T * EPS , T),rcol,p_Depth + 1, tmp_Refr_rate,dist);
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
					Ray r( c.getEye(), dir );
					double dist;
					Primitive* prim = Runtracer( r, col, 1, 1.0, dist );
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
			Ray r( c.getEye(), dir );
			double dist;
			Primitive* prim = Runtracer( r, col, 1, 1.0, dist );
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
		imshow("test",colorim);
		waitKey(10);
	}
	return true;
}

}; // namespace HYF