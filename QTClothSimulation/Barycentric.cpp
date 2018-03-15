#include "Barycentric.h"
#include <math.h>

CBarycentric::CBarycentric(CCloth *c1, CCloth *c2)
{	
	init(c1, c2);
}
CBarycentric::~CBarycentric()
{

}

void CBarycentric::init(CCloth *c1, CCloth *c2)
{
	Vector3f pos;    // Simulation Cloth의 Node position
	Vector3f Rpos1;  // Reference Cloth의 삼각형 node들의 position
	Vector3f Rpos2;
	Vector3f Rpos3;
	Vector3f bary;  // Barycentric Coordinate Information
	Vector3f cart;   // Cartesian Coordinate Information
	int insideFlag = 0;
	int count = 0;
	

	// Reference Cloth를 기준으로 Simulation Cloth node들의 위치를 Barycentric으로 계산
	if (c1->sFlag == 1 && c2->sFlag == 2)
	{
		// Simulation cloth의 모든 노드들을 Reference Cloth의 위치에 대한 Barycenteric Coordinate 계산
		for(int i = 0; i < c2->mNodeArray->size(); i++)
		{
			pos = c2->mNodeArray->at(i)->GetPos();
			
			for (int j = 0; j < c1->mFaceList->size(); j++) // Reference Cloth
			{
				Rpos1 = c1->mNodeArray->at(c1->mFaceList->at(j).x())->GetPos();
				Rpos2 = c1->mNodeArray->at(c1->mFaceList->at(j).y())->GetPos();
				Rpos3 = c1->mNodeArray->at(c1->mFaceList->at(j).z())->GetPos();

				bary = barycentric(Rpos1, Rpos2, Rpos3, pos);				
				cart = cartesian(Rpos1, Rpos2, Rpos3, bary);
				
				insideFlag = insideDecision(Rpos1, Rpos2, Rpos3, pos);
				
				if(insideFlag)
				{
					// Reference Cloth에서의 Face index와 Barycentric Coord 저장
					Eigen::Vector4f* tempv4f = new Eigen::Vector4f((float)j, bary[0], bary[1], bary[2]);
					c1->mBarycentricCoordList->push_back(tempv4f);
					count++;
					break;
				}
			}
		}
	}
	else // 1번 cloth는 Reference cloth, 2번 cloth는 Simulation cloth
	{

	}
	
	// Simulation Cloth의 모든 노드들에 대한 Reference Cloth의 위치가 매핑 되었는지를 판단 
	if (count != c2->mNodeArray->size())  
	{		
		exit(1);
	}
	
}

void CBarycentric::update()
{
	
}

float Rounding(double x, int digit)
{
	return (floor((x)* pow(float(10), digit) + 0.5f) / pow(float(10), digit));
}

// p0, p1 and p2  and the points that make up this triangle
Vector3f CBarycentric::barycentric(Vector3f p0, Vector3f p1, Vector3f p2, Vector3f p)
{
	Vector3f tempA = p1 - p0;
	Vector3f tempB = p2 - p0;
	Vector3f tempC = tempA.cross(tempB);
	float tArea = tempC.norm() * 0.5;
	
	tempA = p1 - p;
	tempB = p2 - p;
	tempC = tempA.cross(tempB);
	float u = (tempC.norm() * 0.5) / tArea;

	tempA = p0 - p;
	tempB = p2 - p;
	tempC = tempA.cross(tempB);
	float v = (tempC.norm() * 0.5) / tArea;

	tempA = p0 - p;
	tempB = p1 - p;
	tempC = tempA.cross(tempB);
	float w = (tempC.norm() * 0.5) / tArea;

	Vector3f result(u, v, w);
	
	return result;
}

Vector3f CBarycentric::cartesian(Vector3f p0, Vector3f p1, Vector3f p2, Vector3f barycentric)
{
	return barycentric[0] * p0 + barycentric[1] * p1 + barycentric[2] * p2;
}

int CBarycentric::insideDecision(Vector3f p0, Vector3f p1, Vector3f p2, Vector3f point)
{
	int result = 0;
	Vector3f v0 = p2 - p0;
	Vector3f v1 = p1 - p0;
	Vector3f v2 = point - p0;

	float dot00 = v0.dot(v0);
	float dot01 = v0.dot(v1);
	float dot02 = v0.dot(v2);
	float dot11 = v1.dot(v1);
	float dot12 = v1.dot(v2);

	float invDenom = Rounding(1 / (dot00 * dot11 - dot01 * dot01), 3);
	float u = Rounding((dot11 * dot02 - dot01 * dot12) * invDenom, 3);
	float v = Rounding((dot00 * dot12 - dot01 * dot02) * invDenom, 3);

	if ((u >= 0) && (v >= 0) && (u + v <= 1)) result = 1;
	else result = 0;
	return result;
}