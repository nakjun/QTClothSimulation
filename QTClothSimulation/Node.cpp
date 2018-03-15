#include "Node.h"

CNode::CNode()
{
	mMass = 0.0f;
	mVelocity = Vector3f(0.0);
	mPosition = Vector3f(0.0);
	mForce = Vector3f(0.0);	
	prevForceIvs = Vector3f(0.0);
	StructureForce = Vector3f(0.0);
	ShearForce = Vector3f(0.0);
	BendForce = Vector3f(0.0);
	stCount = 0;
	shCount = 0;
	bCount = 0;
	NormalVector = Vector3f(0.0);
	faceCount = 0;
}

void CNode::update(float dt)
{	
	if (SimulationFlag)
	{
		mVelocity += (mForce / mMass + Vector3f(0.0,-9.8,0.0)) * dt;	// V(t+1) = V(t) + (F(t) / mass) * h 	
		mPosition += mVelocity * dt;				    // X(t+1) = X(t) + V(t) * h	
	}	
}

void CNode::AddForce(Vector3f Force)
{
	//Add External Force(ex. Spring Force)
	mForce += Force;
}

void CNode::setPos(Vector3f Pos)
{	
	mPosition = Pos;
}

void CNode::ClearForce()
{
	// Clear Node Force	
	mForce = Vector3f(0.0f); 
}

Vector3f CNode::GetForce()
{
	return mForce;
}
Vector3f CNode::GetVel()
{
	return mVelocity;
}
Vector3f CNode::GetPos()
{
	return mPosition;
}
