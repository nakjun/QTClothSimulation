#pragma once
#include <stdio.h>
#include "Include.h"

class CNode{

	//Method
public:
	CNode();
	~CNode();
	void update(float dt);
	void AddForce(Vector3f Force);
	void ClearForce();
	void setPos(Vector3f Pos);

	Vector3f GetForce();
	Vector3f GetVel();
	Vector3f GetPos();

	

//Field
public:
	float mMass;
	Vector3f mPosition;
	Vector3f mVelocity;
	Vector3f mForce;
	Vector3f mPrevPosition;
	Vector3f mPrevVelocity;
	Vector3f mPrevForce;

	Vector3f prevForceIvs;

	Vector3f StructureForce;
	Vector3f ShearForce;
	Vector3f BendForce;

	float weightStructure;
	float weightShear;
	float weightBend;

	float OptimizeStKs;
	float OptimizeShKs;
	float OptimizeBKs;

	int stCount;
	int shCount;
	int bCount;

	int faceCount;

	Vector3f NormalVector;

	Vector3f Gravity;
	bool SimulationFlag = true;
};