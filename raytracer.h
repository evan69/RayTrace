#ifndef RAYTRACER_H
#define RAYTRACER_H

#include "all.h"

namespace HYF {

class Scene;
class Primitive;
class Engine
{
public:
	Engine();
	~Engine();
	void setTarget();
	inline Scene* getScene() { return m_Scene; }
	Primitive* Runtracer( Ray& p_Ray, Color& p_Acc, int p_Depth, double p_RIndex, double& p_Dist ,double p_Sample,double p_SampleRange);
	Color Runtracer(Ray &r, int depth, unsigned short *Xi);//Path Tracing
	bool HYF_render(cv::Mat&);
	double calShade(Primitive* p_Light, vector3 p_pi, vector3& p_Dir,double p_Sample,double p_SampleRange);
	int findNearestKD(Ray& ray, double& p_Dist, Primitive*& p_Prim);
	int FindNearest(Ray& p_Ray, double& p_Dist, Primitive*& p_Prim);
	void PTintersect(Ray &r,double& t,Primitive* prim);
protected:
	Scene* m_Scene;
	int m_Width, m_Height;
	vector3 m_SR, m_CW;
};

}; // namespace HYF

#endif