#include "object.h"
#include <fstream>
#include <string>
using std::ifstream;
using std::string;

namespace HYF
{

void Object::readin(char* filename,Primitive** p_Prim,int& p_PrimNum)
{
	ifstream fin(filename);
	char flag;
	vector<vector3> PointList;
	PointList.push_back(vector3(0,0,0));
	int cnt = 0;
	while(!fin.eof())
	{
		fin >> flag;
		if(flag == '#')
		{
			string s;
			getline(fin,s);
			continue;
		}
		if(flag == 'v' || flag == 'V')//verticals
		{
			//std::cout << "ver:"; 
			double tmp[3];
			fin >> tmp[0] >> tmp[1] >> tmp[2];
			//std::cout << tmp[0] << tmp[1] << tmp[2] << '\n'; 
			PointList.push_back(vector3(tmp[0],tmp[1],tmp[2]) * m_alpha + m_move);
		}
		if(flag == 'f' || flag == 'F')//face
		{
			//std::cout << "face:"; 
			int tmp[3];
			fin >> tmp[0] >> tmp[1] >> tmp[2];
			//std::cout << tmp[0] << tmp[1] << tmp[2] << '\n'; 
			p_Prim[p_PrimNum] = new ObjTriangle(PointList[tmp[0]],PointList[tmp[1]],PointList[tmp[2]]);
			p_PrimNum++;
		}
	}
	p_PrimNum--;
	fin.close();
}

};