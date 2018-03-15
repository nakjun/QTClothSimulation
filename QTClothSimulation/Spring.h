#include "Include.h"
#include "Node.h"
class CSpring{
//Method
public:
	CSpring();
	~CSpring();
	void update();
	void init(CNode *m1,CNode *m2, int springType);
	void ComputeSpringForce(int springType);
	
//Field
public:
	CNode *m1;			
	CNode *m2;

	Vector3f middlePosition;
	Vector3f middlePrevPosition;

	//0 Structure, 1 Shear, 2 Bend
	int SpringType = 0;

	float mRestLength;
	float Ks, Kd;
};