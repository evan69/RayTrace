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
	p_Dist = INF;
	for ( int s = 0; s < m_Scene->getNrPrimitives(); s++ )
	{
		Primitive* pr = m_Scene->getPrimitive( s );
		int res;
		if (res = pr->Intersect( ray, p_Dist )) 
		{
			p_Prim = pr;
			in_out = res;
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
	std::vector<Primitive*> list;
	auto grid = m_Scene->getGrid();
	p_Prim = 0;
	while (1)
	{
		list = grid[X + (Y << GRIDSHFT) + (Z << (GRIDSHFT * 2))];
		unsigned int list_index = 0;
		while (list_index < list.size())
		{
			Primitive* pr = list[list_index];
			int result;
				if (result = pr->Intersect( p_Ray, p_Dist )) 
			{
				retval = result;
				p_Prim = pr;
				goto testloop;
			}
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
		while(list_index < list.size())
		{
			Primitive* pr = list[list_index];
			int result;
				if (result = pr->Intersect( p_Ray, p_Dist )) 
			{
				p_Prim = pr;
				retval = result;
			}
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
	}
	else if(p_Light->getType() == Primitive::BOX)
	{
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
	}
	return shade;
}

#ifndef PATHTRACING
Primitive* Engine::Runtracer( Ray& p_Ray, Color& p_Col, int p_Depth, double p_Refr_Rate, double& p_Dist ,double p_Sample,double p_SampleRange)
{
	if (p_Depth > TRACEDEPTH) return 0;
	p_Dist = INF;//首先让距离最大，然后逐步通过intersect函数缩小
	vector3 pi;
	Primitive* prim = 0;
	int result;
#ifndef KD
	if (!(result = FindNearest( p_Ray, p_Dist, prim ))) return 0;
#else
	if (!(result = findNearestKD( p_Ray, p_Dist, prim ))) return 0;
#endif
	if (!prim) return 0;//光线不和任何物体相交
	if (prim->IsLight())//如果光线最近遇到光源，直接返回光源颜色
	{
		p_Col += Color( 1, 1, 1 );
	}
	else//否则，最近的是不发光物体
	{
		pi = p_Ray.getOrigin() + p_Ray.getDirection() * p_Dist;//pi为光线与最近物体交汇的地方
		for(int l = 0;l < m_Scene->getNrLights() ;++l)
		{
			Primitive*p = m_Scene->getLight(l);
			if (p->IsLight())//物体为光源时
			{
				Primitive* light = p;
				double shade = 1.0;
				vector3 L;
				shade = calShade(light,pi,L,p_Sample,p_SampleRange);
				vector3 N = prim->getNormal( pi );//物体在pi处的法向量
				if (prim->getMaterial()->getDiffuse() > 0)//漫反射
				{
					double dot = DOT( L, N );
					if (dot > 0)
					{
						double diff = dot * prim->getMaterial()->getDiffuse() * shade;
						p_Col += diff * light->getMaterial()->getColor() * prim->getColor(pi);					
					}
				}
				if (prim->getMaterial()->getSpecular() > 0)//高光
				{
					// point light source: sample once for specular highlight
					vector3 V = p_Ray.getDirection();//光线方向
					vector3 R = L - 2.0 * DOT( L, N ) * N;
					double dot = DOT( V, R );
					if (dot > 0)
					{
						double spec = pow( dot, 20 ) * prim->getMaterial()->getSpecular() * shade;
						p_Col += spec * light->getMaterial()->getColor();
					}
				}
			}
			else
			{
				assert(0);//m_Lights里面有非光源，不合法！
			}
		}
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
				for ( int i = 0; i < num; i++ )
				{
					double x0,y0;
					while(1)
					{
						x0 = 2.0 * (double)rand() / RAND_MAX - 1.0;
						y0 = 2.0 * (double)rand() / RAND_MAX - 1.0;
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
					p_Col += refl * rcol * prim->getColor(pi) * (1.0 / (double)num);
				}
			}
			else if (p_Depth < TRACEDEPTH)//光滑镜面反射
			{
				Color rcol( 0, 0, 0 );
				double dist;
#ifdef IMPORTANCE_SAMPLING
				Runtracer( Ray( pi + R * EPS, R ), rcol, p_Depth + 1, p_Refr_Rate, dist ,p_Sample * 0.25,p_SampleRange * 4.0);
#else
				Runtracer( Ray( pi + R * EPS, R ), rcol, p_Depth + 1, p_Refr_Rate, dist ,p_Sample,p_SampleRange);
#endif
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
				Runtracer(Ray(pi + T * EPS , T),rcol,p_Depth + 1, tmp_Refr_rate,dist,p_Sample * 0.25,p_SampleRange * 4.0);
#else
				Runtracer(Ray(pi + T * EPS , T),rcol,p_Depth + 1, tmp_Refr_rate,dist,p_Sample,p_SampleRange);
#endif
				Color absorbance = prim->getColor(pi) * 0.15 * -dist;
				Color transparency = Color( exp( absorbance.r ), exp( absorbance.g ), exp( absorbance.b ) );
				p_Col += rcol * transparency;
			}
		}
	}
	return prim;
}

bool Engine::HYF_render(cv::Mat& colorim)
{
	Camera c = Camera();
	Primitive* lastprim = 0;
	for ( int y = 0; y < m_Height; y++ )
	{
		for ( int x = 0; x < m_Width; x++ )
		{
			Color col( 0, 0, 0 );
			
#ifdef SUPERSAMPLING
			for(double i = -1.0;i < 1.5;++i)
				for(double j = -1.0;j < 1.5;++j)
				{
					vector3 dir = c.getDir(x + i / 3,y + j / 3);
					NORMALIZE(dir);
					Ray r( c.getEye(), dir );
					double dist;
					Primitive* prim = Runtracer( r, col, 1, 1.0, dist ,SAMPLES,(1.0 / SAMPLES));
				}
			int red = (int)(col.r * 256 / 9);
			int green = (int)(col.g * 256 / 9);
			int blue = (int)(col.b * 256 / 9);
#endif
#ifndef SUPERSAMPLING
			vector3 dir = c.getDir(x,y);
			NORMALIZE(dir);
			Ray r( c.getEye(), dir );
			double dist;
			Primitive* prim = Runtracer( r, col, 1, 1.0, dist ,SAMPLES,(1.0 / SAMPLES));
#ifdef DEPTH_OF_FIELD
			c.setRV(0.1,9.0);
			for(int oo = 0;oo < 9;++oo)
			{
				prim = Runtracer( c.getRandRay(x,y), col, 1, 1.0, dist ,SAMPLES,(1.0 / SAMPLES));
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
	}
}

Color Engine::Runtracer(Ray &r, int depth, unsigned short *Xi)
{ 
	if(depth > 1400) return Color(0,0,0);
	double t = 1e20;
	Primitive* prim = 0;
#ifndef KD
	FindNearest( r, t, prim );
#else
	findNearestKD(r,t,prim);
#endif
	if (prim == 0) {return vector3();} // if miss, return black 
	vector3 x=r.getOrigin()+r.getDirection()*t, n=prim->getNormal(x).norm(), nl=n.Dot(r.getDirection())<0?n:n*-1, f=prim->getMaterial()->getColor(); 
	double p = f.x>f.y && f.x>f.z ? f.x : f.y>f.z ? f.y : f.z;
	if (++depth>5)
	{
		if(erand48(Xi)<p) 
			f=f*(1/p);
		else 
			return prim->getMaterial()->emission;
	}
	if (prim->getMaterial()->BRDFType == Material::DIFF)
	{
		double r1=2*PI*erand48(Xi), r2=erand48(Xi), r2s=sqrt(r2); 
		vector3 w=nl, u=((fabs(w.x)>.1?vector3(0,1,0):vector3(1,0,0))%w).norm(), v=w%u; 
		vector3 d = (u*cos(r1)*r2s + v*sin(r1)*r2s + w*sqrt(1-r2)).norm(); 
		return prim->getMaterial()->emission + f.mult(Runtracer(Ray(x,d),depth,Xi)); 
	} 
	else if (prim->getMaterial()->BRDFType == Material::SPEC)
		return prim->getMaterial()->emission + f.mult(Runtracer(Ray(x,r.getDirection()-n*2*n.Dot(r.getDirection())),depth,Xi)); 
	Ray reflRay(x, r.getDirection()-n*2*n.Dot(r.getDirection()));
	bool into = n.Dot(nl)>0;
	double nc=1, nt=1.5, nnt=into?nc/nt:nt/nc, ddn=r.getDirection().Dot(nl), cos2t; 
	if ((cos2t=1-nnt*nnt*(1-ddn*ddn))<0)
		return prim->getMaterial()->emission + f.mult(Runtracer(reflRay,depth,Xi)); 
	vector3 tdir = (r.getDirection()*nnt - n*((into?1:-1)*(ddn*nnt+sqrt(cos2t)))).norm(); 
	double a=nt-nc, b=nt+nc, R0=a*a/(b*b), c = 1-(into?-ddn:tdir.Dot(n)); 
	double Re=R0+(1-R0)*c*c*c*c*c,Tr=1-Re,P=.25+.5*Re,RP=Re/P,TP=Tr/(1-P); 
	return prim->getMaterial()->emission + f.mult(depth>2 ? (erand48(Xi)<P ?
		Runtracer(reflRay,depth,Xi)*RP:Runtracer(Ray(x,tdir),depth,Xi)*TP) : 
		Runtracer(reflRay,depth,Xi)*Re+Runtracer(Ray(x,tdir),depth,Xi)*Tr); 
} 

bool Engine::HYF_render(cv::Mat& colorim)
{
	int w=800, h=600;
	int samps = PTSAMP;
	Ray cam(vector3(50,52,295.6), vector3(0,-0.042612,-1).norm());
	vector3 cx=vector3(w*.5135/h,0,0), cy=(cx%cam.getDirection()).norm()*.5135, r, *c=new vector3[w*h]; 
	for (int y=0; y<h; y++)
	{
		printf("rendering %dth row...\n",y+1);
		short unsigned int Xi[3]={0,0,y*y*y};
		for (unsigned short x=0; x<w; x++) 
			for (int sy=0, i=(h-y-1)*w+x; sy<2; sy++)
				for (int sx=0; sx<2; sx++, r=vector3())
				{
					for (int s=0; s<samps; s++)
					{ 
						double r1=2*erand48(Xi), dx=r1<1 ? sqrt(r1)-1: 1-sqrt(2-r1); 
						double r2=2*erand48(Xi), dy=r2<1 ? sqrt(r2)-1: 1-sqrt(2-r2); 
						vector3 d = cx*( ( (sx+.5 + dx)/2 + x)/w - .5) + 
							cy*( ( (sy+.5 + dy)/2 + y)/h - .5) + cam.getDirection(); 
						r = r + Runtracer(Ray(cam.getOrigin()+d*140,d.norm()),0,Xi)*(1./samps); 
					}
					c[i] = c[i] + vector3(clamp(r.x),clamp(r.y),clamp(r.z))*.25; 
					colorim.at<cv::Vec3b>(h - y - 1,x) = cv::Vec3b(toInt(c[i].x), toInt(c[i].y), toInt(c[i].z));
				} 
		cv::imshow("test",colorim);
		//if(fabs(floor(y / 20) - y / 20) < EPS)
		//	cv::imwrite("tmp.png",colorim);
		//cv::imshow("test",colorim);
		cv::waitKey(10);
   } 
	return true;
} 

#endif

}; // namespace HYF