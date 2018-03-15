#pragma once
#include "Cloth.h"
class CBarycentric
{
public:
	CBarycentric(CCloth *c1, CCloth *c2);
	~CBarycentric();
	void CBarycentric::init(CCloth *c1, CCloth *c2);
	Vector3f CBarycentric::barycentric(Vector3f p0, Vector3f p1, Vector3f p2, Vector3f p);
	Vector3f CBarycentric::cartesian(Vector3f p0, Vector3f p1, Vector3f p2, Vector3f barycentric);
	int CBarycentric::insideDecision(Vector3f p0, Vector3f p1, Vector3f p2, Vector3f point);
	void update();
public:

};