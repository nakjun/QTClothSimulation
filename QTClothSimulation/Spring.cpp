
#include "Spring.h"
#include <math.h>



CSpring::CSpring()
{
	
}
CSpring::~CSpring()
{

}


double Rounding(double x, int digit)
{
	return (floor((x)* pow(float(10), digit) + 0.5f) / pow(float(10), digit));
}


void CSpring::init(CNode *a, CNode *b,int springType)
{
	m1 = a;
	m2 = b;

	Vector3f forceDirection = m2->GetPos() - m1->GetPos();
	
	mRestLength = sqrt((forceDirection.x() * forceDirection.x()) + (forceDirection.y() * forceDirection.y()) + (forceDirection.z() * forceDirection.z()));
	
	mRestLength = Rounding(mRestLength,4);
	
	this->SpringType = springType;
}

void CSpring::ComputeSpringForce(int SpringType)
{
 	Vector3f forceDirection = m2->GetPos() - m1->GetPos();
	Vector3f VelocityDirection = m2->GetVel() - m1->GetVel();
	
	float len = sqrt((forceDirection.x() * forceDirection.x()) + (forceDirection.y() * forceDirection.y()) + (forceDirection.z() * forceDirection.z()));
	
	len = Rounding(len, 4);
	float spforce = (len - mRestLength) * Ks;
	float damp = (VelocityDirection.dot(forceDirection) / len) * Kd;

	Vector3f nSPF = (spforce + damp) * forceDirection / len;
	
	m1->AddForce(nSPF);
	m2->AddForce(-nSPF); 
	
	switch (SpringType)
	{
	case 0:
		m1->StructureForce += nSPF;
		m2->StructureForce -= nSPF;
		break;
	case 1:
		m1->ShearForce += nSPF;
		m2->ShearForce -= nSPF;
		break;
	case 2:
		m1->BendForce += nSPF;
		m2->BendForce -= nSPF;
		break;
	}
}



void CSpring::update()
{
	ComputeSpringForce(this->SpringType);
}

