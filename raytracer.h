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
	Scene* getScene() { return m_Scene; }
	Primitive* Runtracer( Ray& p_Ray, Color& p_Acc, int p_Depth, double p_RIndex, double& p_Dist );
	bool HYF_render(cv::Mat&);
	int FindNearest(Ray& a_Ray, double& a_Dist, Primitive*& a_Prim);
protected:
	Scene* m_Scene;
	int m_Width, m_Height;
	vector3 m_SR, m_CW;
};

}; // namespace HYF

#endif