#pragma once
#include "Include.h"
#include "Spring.h"
#include "Node.h"


class CCloth
{
public:
	CCloth(float st,float sh, float be, float kd, int n, int m, float offset, int id, int flag);
	~CCloth();
	void initialize(int n, int m);
	void update();
	void render();
	void applyCartesian(CCloth *Reference);
	void calculate_Ks(CCloth *Reference);
	void calculateSpringForce(CCloth *Reference);
	Vector3f CCloth::cartesian(Vector3f p0, Vector3f p1, Vector3f p2, Vector3f barycentric);
	void setVirtualPosition();	
	void updateOptimizedKs();
	void calculateNormalVector(Vector3i tmp);
	float Distance(const Eigen::Vector3f& a, const Eigen::Vector3f& b);
public:
	float mOffset;
	int clothID;
	int mSpringCount;
	int mNodeCount;
	
	vector<CNode *> *mNodeArray;
	vector<CNode *> *mOriginNodeArray;
	vector<CSpring *> *mSpringArray;
	vector<Vector3i> *mFaceList;
	vector<Eigen::Vector4f*> *mBarycentricCoordList;
	vector<Vector3f> *mCartesianCoordList;

public:
	float xPos;
	float yPos;

	int Structural_Spring_Count;
	int Shear_Spring_Count;
	int bend_Spring_Count;
	int sFlag;   // 1: Reference Model, 2: simulation Model

	float lineSize = 8.0;
	float IntervalX;
	float IntervalY;
	float IntervalZ;

	int FaceIndex;
	Vector3i FaceNodeIndex;
	CNode *nodeTmp[3];
	
	Vector3f structureSum; 
	Vector3f shearSum;
	Vector3f bendSum;

	float weightSt;
	float weightSh;
	float weightB;

	Vector3f Summation;
	
	int mStrKS = 0;
	int mStrKD = 0;
	int mShearKS = 0;
	int mShearKD = 0;
	int mBendKS = 0;
	int mBendKD = 0;
	
	double avgKs = 0.0;

	Eigen::MatrixXd matrixA;
	Eigen::MatrixXd b;
	Eigen::Vector3d* force;	
	Eigen::VectorXd CalculatedKs;

	double curLength;
	double lenChange;

	int currFrame = 0;
	FILE *fp;
	FILE *fp2;
};