#ifndef CAMERA_H
#define CAMERA_H

#include "all.h"

namespace HYF
{
/*
class Camera
{

public:
	Camera():m_Eye(0,0,-5),m_Target(0,0,0),m_Dist(5.0),m_Width(8.0),m_Height(6.0),m_Ratio(0.01){}
	Camera(vector3 p_Eye,vector3 p_Target,double p_Dist,double p_Width,double p_Height,double p_Ratio):
		m_Eye(p_Eye),m_Target(p_Target),m_Dist(p_Dist),m_Width(p_Width),m_Height(p_Width),m_Ratio(p_Ratio){}
	inline vector3 getEye(){return m_Eye;}
	vector3 getDir(double x,double y)//像素坐标，整数，也可以在超采样中取小数
	{
		vector3 dir = m_Target - m_Eye;
		NORMALIZE(dir);
		dir = dir * m_Dist;
		//return dir;
		m_x = dir.Cross(vector3(0,1,0));
		NORMALIZE(m_x);
		m_y = m_x.Cross(dir);
		NORMALIZE(m_y);
		vector3 ret = dir + (x * m_Ratio - 0.5 * m_Width) * m_x + (y * m_Ratio - 0.5 * m_Height) * m_y;
		NORMALIZE(ret);
		return ret;
	}
private:
	vector3 m_Eye;
	vector3 m_Target;
	double m_Dist;
	double m_Width;
	double m_Height;
	vector3 m_x;//投影平面的x方向基向量
	vector3 m_y;//投影平面的y方向基向量
	double m_Ratio;//从整点像素到三维坐标系的缩放比，即图像单位像素对应投影平面在坐标系中的长度
};
*/
class Camera
{
public:
	Camera():m_Eye(0,0,-5),m_Target(0,0,0),m_Dist(5.0),m_Width(8.0),m_Height(6.0),m_Ratio(0.01){}
	Camera(vector3 p_Eye,vector3 p_Target,double p_Dist,double p_Width,double p_Height,double p_Ratio):
		m_Eye(p_Eye),m_Target(p_Target),m_Dist(p_Dist),m_Width(p_Width),m_Height(p_Width),m_Ratio(p_Ratio){}
	inline vector3 getEye(){return m_Eye;}
	vector3 getDir(double x,double y)//像素坐标，整数，也可以在超采样中取小数
	{
		vector3 dir = m_Target - m_Eye;
		NORMALIZE(dir);
		dir = dir * m_Dist;
		//return dir;
		m_x = dir.Cross(vector3(0,1,0));
		NORMALIZE(m_x);
		m_y = m_x.Cross(dir);
		NORMALIZE(m_y);
		vector3 ret = dir + (x * m_Ratio - 0.5 * m_Width) * m_x + (y * m_Ratio - 0.5 * m_Height) * m_y;
		NORMALIZE(ret);
		return ret;
	}
	inline void setRV(double p_R,double p_V){ m_R = p_R; m_V = p_V; }
	Ray getRandRay(double x,double y)//景深，获取光圈内随机的一个光线，用以计算颜色
	{
		//printf("%llf\n",LENGTH(m_x));
		double x0,y0;
		do
		{
			x0 = 2.0 * (double)rand() / RAND_MAX - 1.0;
			y0 = 2.0 * (double)rand() / RAND_MAX - 1.0;
		}while(x0 * x0 + y0 * y0 > 1);
		x0 *= m_R;
		y0 *= m_R;
		vector3 randPos = m_Eye + x0 * m_x + y0 * m_y;
		vector3 dir = getDir(x,y);
		vector3 focusPos = m_Eye + dir * m_V * (1.0 / m_Dist);
		vector3 rayDir = focusPos - randPos;
		NORMALIZE(rayDir);
		//return Ray(focusPos,rayDir);
		return Ray(randPos,rayDir);
	}
private:
	vector3 m_Eye;
	vector3 m_Target;
	double m_Dist;
	double m_Width;
	double m_Height;
	vector3 m_x;//投影平面的x方向基向量
	vector3 m_y;//投影平面的y方向基向量
	double m_Ratio;//从整点像素到三维坐标系的缩放比，即图像单位像素对应投影平面在坐标系中的长度

	double m_R;//光圈的半径
	double m_V;//眼睛到焦平面的距离
};
}

#endif