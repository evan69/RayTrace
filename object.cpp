#include "object.h"
#include <fstream>
#include <string>
using std::ifstream;
using std::string;

namespace HYF
{

vector3 ObjTriangle::getNormal( vector3& p_Pos )
{
	/*
	//std::cout << "getnormal\n";
	vector<ObjTriangle*> mTriangleVec = obj->TriangleVec;
	vector<vector<int>> mTriangleInfo = obj->TriangleInfo;
	std::cout << mTriangleVec.size() << '\n';
	//std::cout << mTriangleInfo.size() << '\n';
	vector3 retN;
	for(int k = 0;k < 3;++k)
	{
		if((p_Pos - vertex[k]).Length() < EPS * EPS)
		{
			retN = vector3(0,0,0);
			for(int i = 0;i < mTriangleInfo[vertexIndex[k]].size();++i)
			{
				retN += mTriangleVec[mTriangleInfo[vertexIndex[k]][i]]->getNormal();
			}
			retN *= (1.0 / mTriangleInfo[vertexIndex[k]].size());
			return retN;
		}
	}
	*/
	/*
	for(int r = 1;r < 3;r++)
	{
		for(int s = 0;s < r;s++)
		{
			retN = vector3(0,0,0);
			vector3 a = vertex[r] - vertex[s];
			vector3 b = p_Pos - vertex[r];
			NORMALIZE(a);
			if(b.SqrLength() - DOT(a,b) * DOT(a,b) < EPS * EPS)
			{
				std::cout << r << " " << s << '\n';
				std::cout << vertexIndex[r] << " " << vertexIndex[s] << '\n';
				std::cout << allTriangle.size() << '\n';
				std::cout << allTriangle[vertexIndex[r]].size() << " " << allTriangle[vertexIndex[s]].size() << '\n';
				//for(int i = 0;i < (*allTriangle)[vertexIndex[r]].size();++i)
				int i = 0;
				while(i < allTriangle[vertexIndex[r]].size())
				{
					retN += allTriangle[vertexIndex[r]][i]->getNormal();
					i++;
				}
				i = 0;
				//for(int i = 0;i < (*allTriangle)[vertexIndex[s]].size();++i)
				while(i < allTriangle[vertexIndex[s]].size())
				{
					retN += allTriangle[vertexIndex[s]][i]->getNormal();
					i++;
				}
				retN *= (1.0 / (allTriangle[vertexIndex[r]].size() + allTriangle[vertexIndex[s]].size()));
				return retN;
			}
		}
	}
	*/
	return N;
}

void Object::readin(char* filename,Primitive** p_Prim,int& p_PrimNum,std::vector<TriangleTree*>& poly_vec)
{
	std::vector<Triangle*> tri_vec;
	ifstream fin(filename);
	char flag;
	vector<vector3> PointList;
	PointList.push_back(vector3(0,0,0));
	TriangleInfo.push_back(vector<int>());
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
			vector3 topush = vector3(tmp[0],tmp[1],tmp[2]) * m_alpha + m_move;
			//topush.z = 14 - topush.z;
			//PointList.push_back(vector3(tmp[0],tmp[1],tmp[2]) * m_alpha + m_move);
			PointList.push_back(topush);
			TriangleInfo.push_back(vector<int>());
			//std::cout << TriangleVec.size() << '\n';
		}
		if(flag == 'f' || flag == 'F')//face
		{
			//std::cout << "face:"; 
			int tmp[3];
			//fin >> tmp[0] >> tmp[1] >> tmp[2];
			//此处注意法向！！！
			fin >> tmp[0] >> tmp[2] >> tmp[1];
			//std::cout << tmp[0] << tmp[1] << tmp[2] << '\n'; 
			ObjTriangle* tri = new ObjTriangle(PointList[tmp[0]],PointList[tmp[1]],PointList[tmp[2]]);
			if(tri->getNormal().Length() < EPS) continue;
			TriangleVec.push_back(tri);
#ifndef KD
			p_Prim[p_PrimNum] = tri;
			p_PrimNum++;
#else
			tri_vec.push_back(tri);
#endif
			/*
			tri->id = cnt;
			TriangleInfo[tmp[0]].push_back(cnt);
			TriangleInfo[tmp[1]].push_back(cnt);
			TriangleInfo[tmp[2]].push_back(cnt);
			TriangleVec.push_back(tri);
			*/
			//tri->allTriangle = &TriangleVec;
			/*
			tri->obj = this;
			tri->vertexIndex[0] = tmp[0];
			tri->vertexIndex[1] = tmp[1];
			tri->vertexIndex[2] = tmp[2];
			*/
			/*
			p_Prim[p_PrimNum]->getMaterial()->setColor(Color(0.5,0.5,0.5));
			p_Prim[p_PrimNum]->getMaterial()->setDiffRefl(0.0);
			p_Prim[p_PrimNum]->getMaterial()->setDiffuse(2.0);
			p_Prim[p_PrimNum]->getMaterial()->setReflection(0.0);
			p_Prim[p_PrimNum]->getMaterial()->setRefraction(0.0);
			p_Prim[p_PrimNum]->getMaterial()->setRefr_Rate(1.4);
			p_Prim[p_PrimNum]->getMaterial()->setSpecular(0.0);
			*/
			//TriangleVec.push_back(tri);
			
			//cnt++;
		}
	}
#ifndef KD 
	p_PrimNum--;
#endif
	fin.close();
#ifdef KD
	TriangleTree* tree = new TriangleTree();
	TriangleNode* root = tree->GetRoot();
	root->size = tri_vec.size();
	root->tris = new Triangle*[root->size];
	for(int i = 0;i < root->size;i++){
		root->tris[i] = tri_vec[i];
		root->box.Update(tri_vec[i]);
	}
	tree->BuildTree();
	poly_vec.push_back(tree);
	//tri_vec.clear();
#endif
	//std::cout << TriangleVec.size() << '\n';
	//std::cout << TriangleInfo.size() << '\n';
	
}

void Object::setMaterial(Material* m)
{
	for(unsigned int i = 0;i < TriangleVec.size();++i)
	{
		
		TriangleVec[i]->getMaterial()->setColor(m->getColor());
		TriangleVec[i]->getMaterial()->setDiffRefl(m->getDiffRefl());
		TriangleVec[i]->getMaterial()->setDiffuse(m->getDiffuse());
		TriangleVec[i]->getMaterial()->setReflection(m->getReflection());
		TriangleVec[i]->getMaterial()->setRefraction(m->getRefraction());
		TriangleVec[i]->getMaterial()->setRefr_Rate(m->getRefr_Rate());
		TriangleVec[i]->getMaterial()->setSpecular(m->getSpecular());

		TriangleVec[i]->getMaterial()->emission = m->emission;
		TriangleVec[i]->getMaterial()->BRDFType = m->BRDFType;
		
		/*
		TriangleVec[i]->getMaterial()->setColor(Color(0.5,0.5,0.5));
		TriangleVec[i]->getMaterial()->setDiffRefl(0.0);
		TriangleVec[i]->getMaterial()->setDiffuse(2.0);
		TriangleVec[i]->getMaterial()->setReflection(0.0);
		TriangleVec[i]->getMaterial()->setRefraction(0.0);
		TriangleVec[i]->getMaterial()->setRefr_Rate(1.5);
		TriangleVec[i]->getMaterial()->setSpecular(0.0);
		*/
	}
}

};