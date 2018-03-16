#pragma warning(disable:4996)
#pragma once
#include "Include.h"
#include "Cloth.h"
#include "Barycentric.h"
#include <math.h>
#include <Eigen/Eigen/Dense>

int totalMass = 10; // Object 전체의 질량
float dt = 0.00005;
int currFrame22 = 0;
CCloth::CCloth(float st, float sh, float be, float kd, int n, int m, float offset, int id, int flag)
{
	mStrKS = st;
	mShearKS = sh;
	mBendKS = be;

	FaceNodeIndex = Vector3i(0);

	mStrKD = mShearKD = mBendKD = kd;

	Structural_Spring_Count = 0;
	Shear_Spring_Count = 0;
	bend_Spring_Count = 0;
	
	fp = fopen("OptimizeKs.txt", "w");
	fp2 = fopen("tempdata.txt", "w");
	//Simulation Model의 이전 위치정보를 저장할 Vector Data Type;
	mOriginNodeArray = new vector<CNode *>();
	mOriginNodeArray->clear();

	//현재 위치정보를 저장할 Vector Data Type;
	mNodeArray = new vector<CNode *>();
	mNodeArray->clear();
	
	mSpringArray = new vector<CSpring *>();
	mSpringArray->clear();

	mFaceList = new vector<Vector3i>();
	mFaceList->clear();
	
	mBarycentricCoordList = new vector<Eigen::Vector4f*>();
	mBarycentricCoordList->clear();

	mCartesianCoordList = new vector<Vector3f>();
	mCartesianCoordList->clear();

	sFlag = flag; 
	clothID = id;
	IntervalX = lineSize / ((float)n-1.0);
	IntervalY = lineSize / ((float)m-1.0);
	IntervalZ = lineSize / ((float)m-1.0);

	mNodeCount = n * m;

	mOffset = offset;
	initialize(n, m);

	b = Eigen::VectorXd::Zero(mNodeArray->size() * 3);
	matrixA = Eigen::MatrixXd::Zero(mNodeArray->size() * 3, 1);

	currFrame = 0;
}

void CCloth::initialize(int n, int m)
{
	//Cloth 생성을 위한 초기 위치 설정
	float newX = -4.0f;
	float newY = 4.0f;
	float newZ = 0.0f;
	
	// Node position set up: n by m
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			CNode *node = new CNode();
			node->mPosition[0] = newX;
			node->mPosition[1] = newY;
			node->mPosition[2] = newZ;
			mNodeArray->push_back(node);
			mOriginNodeArray->push_back(node);
			newX += IntervalX;			
		}
		//newY -= IntervalY;
		newZ -= IntervalZ;
		newX = -4.0f;
	}
	
	for (int i = 0; i < mNodeArray->size(); i++)
	{
		mNodeArray->at(i)->mMass = (float) totalMass / mNodeArray->size();
		//Flag 형태
		//if (i%m == 0) mNodeArray->at(i)->SimulationFlag = false;
	}
	
	mNodeArray->at(0)->SimulationFlag = false;
	//mNodeArray->at(m-1)->SimulationFlag = false;

	printf("#%d Cloth Node Initialization Success...\n", clothID);
	
	int Spring_index = 0;
	int index = 0;
	
	// Structural Spring 연결: 가로
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < (n - 1); j++)
		{
			if (i>0 && j == 0) index++;
			CSpring *spring = new CSpring();
			spring->Kd = mStrKD;
			spring->Ks = mStrKS;

			spring->init(mNodeArray->at(index), mNodeArray->at(index + 1),0);
			mNodeArray->at(index)->stCount++;
			mNodeArray->at(index + 1)->stCount++;
			index++;
			mSpringArray->push_back(spring);
			Structural_Spring_Count++;
		}
	}
	
	// Structural Spring 연결: 세로	
	for (int i = 0; i < (m - 1); i++)
	{
		for (int j = 0; j < n; j++)
		{
			++index;
			CSpring *spring = new CSpring();
			spring->Kd = mStrKD;
			spring->Ks = mStrKS;

			spring->init(mNodeArray->at((n)*i + j), mNodeArray->at((n)*i + j + n), 0);
			mNodeArray->at((n)*i + j)->stCount++;
			mNodeArray->at((n)*i + j + n)->stCount++;
			mSpringArray->push_back(spring);
			Structural_Spring_Count++;
		}
	}
	
	// Shear Spring 연결: 좌상우하
	int pointindex = 0;
	for (int i = 0; i < (n)*(m - 1); i++)
	{
		if (i%n == (n - 1))
		{
			pointindex++;
			continue;
		}

		CSpring *spring = new CSpring();
		spring->Kd = mShearKD;
		spring->Ks = mShearKS;

		spring->init(mNodeArray->at(pointindex), mNodeArray->at(pointindex + n + 1), 1);
		mNodeArray->at(pointindex)->shCount++;
		mNodeArray->at(pointindex + n + 1)->shCount++;
		mSpringArray->push_back(spring);
		Shear_Spring_Count++;
		pointindex++;
	}

	
	// Shear Spring 연결: 우상좌하		
	pointindex = 0;
	for (int i = 0; i < (n)*(m - 1); i++)
	{
		if (i%n == (0))
		{
			pointindex++;
			continue;
		}

		CSpring *spring = new CSpring();
		spring->Kd = mShearKD;
		spring->Ks = mShearKS;

		spring->init(mNodeArray->at(pointindex), mNodeArray->at(pointindex + n - 1), 1);
		mNodeArray->at(pointindex)->shCount++;
		mNodeArray->at(pointindex + n - 1)->shCount++;
		mSpringArray->push_back(spring);
		Shear_Spring_Count++;
		pointindex++;
	}


	// Bend Spring 연결: 가로
	pointindex = 0;
	for (int i = 0; i < (n)*m; i++)
	{
		if (i%n > n - 3)
		{
			pointindex++;
			continue;
		}

		CSpring *spring = new CSpring();
		spring->Kd = mBendKD;
		spring->Ks = mBendKS;

		spring->init(mNodeArray->at(pointindex), mNodeArray->at(pointindex + 2), 2);
		mNodeArray->at(pointindex)->bCount++;
		mNodeArray->at(pointindex + 2)->bCount++;
		mSpringArray->push_back(spring);
		bend_Spring_Count++;
		pointindex++;
	}

	// Bend Spring 연결: 세로
	pointindex = 0;
	for (int i = 0; i < (n)*(m - 2); i++)
	{
		if (i%n > n - 3)
		{
			pointindex++;
			continue;
		}

		CSpring *spring = new CSpring();
		spring->Kd = mBendKD;
		spring->Ks = mBendKS;

		spring->init(mNodeArray->at(pointindex), mNodeArray->at(pointindex + 2 * m), 2);
		mSpringArray->push_back(spring);
		bend_Spring_Count++;
		pointindex++;
	}
	
	printf("#%d Cloth Spring Initialization Success..\n", clothID);

	// Face List Setup
	for (int i = 0; i < m - 1; ++i)
	{
		for (int j = 0; j < n - 1; ++j)
		{
			int v1 = (i * n) + j;
			int v2 = (i * n) + j + 1;
			int v3 = (i * n) + n + j;
			int v4 = (i * n) + n + j + 1;

			mFaceList->push_back(Vector3i(v1, v3, v2));
			mNodeArray->at(v1)->faceCount++;
			mNodeArray->at(v2)->faceCount++;
			mNodeArray->at(v3)->faceCount++;
			mFaceList->push_back(Vector3i(v2, v3, v4));			
			mNodeArray->at(v2)->faceCount++;
			mNodeArray->at(v3)->faceCount++;
			mNodeArray->at(v4)->faceCount++;
		}
	}
}

void CCloth::calculateNormalVector(Vector3i tmp)
{
	Vector3f F1 = mNodeArray->at(tmp.x())->mPosition.cross(mNodeArray->at(tmp.y())->mPosition);
	Vector3f F2 = mNodeArray->at(tmp.x())->mPosition.cross(mNodeArray->at(tmp.z())->mPosition);
	Vector3f F3 = mNodeArray->at(tmp.y())->mPosition.cross(mNodeArray->at(tmp.z())->mPosition);

	Vector3f Summation = F1 + F2 + F3;

	mNodeArray->at(tmp.x())->NormalVector += Summation;
	mNodeArray->at(tmp.y())->NormalVector += Summation;
	mNodeArray->at(tmp.z())->NormalVector += Summation;
}

void CCloth::update()
{		
	if (currFrame22 < 33000)
	{
		if (clothID == 1)
		{

			mCartesianCoordList->clear();
			Vector3f Rpos1;  // Reference Cloth의 삼각형 node들의 position
			Vector3f Rpos2;
			Vector3f Rpos3;
			Vector3f cart;

			// Clear Node Force
			for (int i = 0; i < mNodeArray->size(); i++)
			{
				mNodeArray->at(i)->ClearForce();
				fprintf(fp2, "%d Force : %f %f %f\n", mNodeArray->at(i)->mForce.x(), mNodeArray->at(i)->mForce.y(), mNodeArray->at(i)->mForce.z());
			}

			// Compute Spring Force
			for (int i = 0; i < mSpringArray->size(); i++)
			{
				mSpringArray->at(i)->update();
			}

			// Simulation Integration
			for (int i = 0; i < mNodeArray->size(); i++)
			{
				mNodeArray->at(i)->update(dt);
			}

			for (int i = 0; i < mFaceList->size(); i++)
			{
				calculateNormalVector(mFaceList->at(i));
			}

			// Barycentric Node position update
			for (int i = 0; i < mBarycentricCoordList->size(); i++)
			{
				Vector3f pos(mBarycentricCoordList->at(i)->y(), mBarycentricCoordList->at(i)->z(), mBarycentricCoordList->at(i)->w());
				int index = int(mBarycentricCoordList->at(i)->x());
				Rpos1 = mNodeArray->at(mFaceList->at(index).x())->GetPos();
				Rpos2 = mNodeArray->at(mFaceList->at(index).y())->GetPos();
				Rpos3 = mNodeArray->at(mFaceList->at(index).z())->GetPos();
				cart = cartesian(Rpos1, Rpos2, Rpos3, pos);
				mCartesianCoordList->push_back(cart);
			}
		}
	}
	currFrame22++;
}

float CCloth::Distance(const Eigen::Vector3f& a, const Eigen::Vector3f& b) {
	Eigen::Vector3f diff = a - b;
	return std::sqrt(diff.x()*diff.x() + diff.y() * diff.y() + diff.z()*diff.z());
}

float Rounding(float x, int digit)
{
	return (floor((x)* pow(float(10), digit) + 0.5f) / pow(float(10), digit));
}

void CCloth::calculate_Ks(CCloth *Reference)
{		
	for (int i = 0; i < mNodeArray->size(); i++)
	{	
		if (!mNodeArray->at(i)->SimulationFlag) continue;
		if (currFrame == 0) continue;
		FaceIndex = Reference->mBarycentricCoordList->at(i)->x();
		FaceNodeIndex = Reference->mFaceList->at(FaceIndex);
		
		nodeTmp[0] = Reference->mNodeArray->at(FaceNodeIndex.x());
		nodeTmp[1] = Reference->mNodeArray->at(FaceNodeIndex.y());
		nodeTmp[2] = Reference->mNodeArray->at(FaceNodeIndex.z());

		structureSum = Vector3f(0.0f);
		shearSum = Vector3f(0.0f);
		bendSum = Vector3f(0.0f);

		for (int n = 0; n < 3; n++)
		{
			structureSum += nodeTmp[n]->StructureForce;
			shearSum += nodeTmp[n]->ShearForce;
			bendSum += nodeTmp[n]->BendForce; 
		}
		
		float sizeStructure = sqrt((structureSum.x()*structureSum.x()) + (structureSum.y()*structureSum.y()) + (structureSum.z()*structureSum.z()));
		float sizeShear = sqrt((shearSum.x()*shearSum.x()) + (shearSum.y()*shearSum.y()) + (shearSum.z()*shearSum.z()));
		float sizeBend = sqrt((bendSum.x()*bendSum.x()) + (bendSum.y()*bendSum.y()) + (bendSum.z()*bendSum.z()));
		float sizeSummation = sizeStructure + sizeShear + sizeBend;

		// 힘의 비율 계산
		if (sizeSummation != 0.0f)
		{
			weightSt = sizeStructure / sizeSummation;
			weightSh = sizeShear / sizeSummation;
			weightB = sizeBend / sizeSummation;

			//fprintf(fp, "Weight : %f %f %f\n", weightSt, weightSh, weightB);
			//fprintf(fp, "mForce : %d %f %f %f\n", i, mNodeArray->at(i)->mForce.x(), mNodeArray->at(i)->mForce.y(), mNodeArray->at(i)->mForce.z());

			mNodeArray->at(i)->StructureForce = mNodeArray->at(i)->mForce * weightSt;
			mNodeArray->at(i)->ShearForce = mNodeArray->at(i)->mForce * weightSh;
			mNodeArray->at(i)->BendForce = mNodeArray->at(i)->mForce * weightB;

		}
		else
		{
			mNodeArray->at(i)->StructureForce = Vector3f(0.0);
			mNodeArray->at(i)->ShearForce = Vector3f(0.0);
			mNodeArray->at(i)->BendForce = Vector3f(0.0);
		}
		/*fprintf(fp, "%d Structure %f %f %f\n", i, mNodeArray->at(i)->StructureForce.x(), mNodeArray->at(i)->StructureForce.y(), mNodeArray->at(i)->StructureForce.z());
		fprintf(fp, "%d Shear %f %f %f\n", i, mNodeArray->at(i)->ShearForce.x(), mNodeArray->at(i)->ShearForce.y(), mNodeArray->at(i)->ShearForce.z());
		fprintf(fp, "%d Bend %f %f %f\n", i, mNodeArray->at(i)->BendForce.x(), mNodeArray->at(i)->BendForce.y(), mNodeArray->at(i)->BendForce.z());*/
		
	}
	for (int i = 0; i < mSpringArray->size(); i++)
	{
		CSpring *tempSpring = mSpringArray->at(i);
		Vector3f SpringForce;

		Vector3f forceDirection = tempSpring->m2->GetPos() - tempSpring->m1->GetPos();
		Vector3f VelocityDirection = tempSpring->m2->GetVel() - tempSpring->m1->GetVel();

		float len = sqrt((forceDirection.x() * forceDirection.x()) + (forceDirection.y() * forceDirection.y()) + (forceDirection.z() * forceDirection.z()));

		forceDirectionMatrix.resize(1, 3);

		for (int i = 0; i < 1; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				forceDirectionMatrix(i, j) = 0.0f;
			}
		}

		forceDirectionMatrix(0, 0) = forceDirection.x();
		forceDirectionMatrix(0, 1) = forceDirection.y();
		forceDirectionMatrix(0, 2) = forceDirection.z();
		
		MatrixXf matrixInv(1,1);

		matrixInv = (forceDirectionMatrix.transpose()*forceDirectionMatrix).inverse();

		for (int i = 0; i < matrixInv.rows(); i++)
		{
			for (int j = 0; j < matrixInv.cols();j++)
			{
				fprintf(fp, "%f ", matrixInv(i, j));
			}
			fprintf(fp, "\n");
		}
		fprintf(fp, "\n");
		
		switch (tempSpring->SpringType)
		{
		case 0:			
			SpringForce = (tempSpring->m2->StructureForce - tempSpring->m1->StructureForce);			
			
			SpringForceMatrix.resize(1, 3);

			SpringForceMatrix(0, 0) = SpringForce.x();
			SpringForceMatrix(0, 1) = SpringForce.y();
			SpringForceMatrix(0, 2) = SpringForce.z();
			
			KsTemp.Zero(1);
			KsTemp = forceDirectionMatrix.inverse();

			tempSizeRow = KsTemp.rows();
			tempSizeCol = KsTemp.cols();

			//fprintf(fp, "%f %f\n", tempSizeRow, tempSizeCol);
			//fprintf(fp, "%f %f %f\n", forceDirection.x(), forceDirection.y(), forceDirection.z());
			//fprintf(fp, "%f %f %f\n %f %f %f \n %f %f %f \n\n", KsTemp(0, 0), KsTemp(0, 1), KsTemp(0, 2), KsTemp(1, 0), KsTemp(1, 1), KsTemp(1, 2), KsTemp(2, 0), KsTemp(2, 1),KsTemp(2,2));
			
			this->mStrKS = (len - tempSpring->mRestLength);
			
			break;
		case 1:
			SpringForce = (tempSpring->m2->ShearForce - tempSpring->m1->ShearForce);						
			
			
			/*if (SpringForce.x() != 0.0 && forceDirection.x() != 0.0)
			{
				ForceSize = SpringForce.x() / forceDirection.x();
			}
			if (SpringForce.y() != 0.0 && forceDirection.y() != 0.0)
			{
				ForceSize = SpringForce.y() / forceDirection.y();
			}
			if (SpringForce.z() != 0.0 && forceDirection.z() != 0.0)
			{
				ForceSize = SpringForce.z() / forceDirection.z();
			}*/
			
			this->mShearKS = (ForceSize - (VelocityDirection.dot(forceDirection) / len)*0.0001) / (len - tempSpring->mRestLength);
			break;
		case 2:
			SpringForce = (tempSpring->m2->BendForce - tempSpring->m1->BendForce);
			
			/*if (SpringForce.x() != 0.0 && forceDirection.x() != 0.0)
			{
				ForceSize = SpringForce.x() / forceDirection.x();
			}
			if (SpringForce.y() != 0.0 && forceDirection.y() != 0.0)
			{
				ForceSize = SpringForce.y() / forceDirection.y();
			}
			if (SpringForce.z() != 0.0 && forceDirection.z() != 0.0)
			{
				ForceSize = SpringForce.z() / forceDirection.z();
			}*/
			
			this->mBendKS = (ForceSize - (VelocityDirection.dot(forceDirection) / len)*0.0001) / (len - tempSpring->mRestLength);			
			break;
		}
		//fprintf(fp, "%d %f\n", i, ForceSize);
		//fprintf(fp, "%d %f %f %f\n", i, this->mStrKS,this->mShearKS,this->mBendKS);
		
	}
}

// Simulation Model에 Reference Cartesian 적용을 위한 Code
void CCloth::applyCartesian(CCloth *Reference)
{	
	// Simulation Model인 경우 수행
	if (clothID == 2)
	{	
		float StKs = 0.0f;
		float ShKs = 0.0f;
		float BKs = 0.0f;

		for (int i = 0; i < mNodeArray->size(); i++)
		{
			mNodeArray->at(i)->mPrevPosition = mNodeArray->at(i)->mPosition;
			mNodeArray->at(i)->mPrevVelocity = mNodeArray->at(i)->mVelocity;
			mNodeArray->at(i)->ClearForce();

			mNodeArray->at(i)->setPos(Reference->mCartesianCoordList->at(i));
			mNodeArray->at(i)->mVelocity = (mNodeArray->at(i)->mPosition - mNodeArray->at(i)->mPrevPosition) / dt;
			mNodeArray->at(i)->mForce = mNodeArray->at(i)->mMass * (mNodeArray->at(i)->mPrevVelocity + mNodeArray->at(i)->mVelocity) / dt;

			if (currFrame < 50)
			{
				calculate_Ks(Reference);								
			}
			else
				fclose(fp);			
		}
		fprintf(fp, "\n");
		currFrame++;		
	}
}

Vector3f CCloth::cartesian(Vector3f p0, Vector3f p1, Vector3f p2, Vector3f barycentric)
{
	return barycentric[0] * p0 + barycentric[1] * p1 + barycentric[2] * p2;
}

void CCloth::render()
{	
		glPushMatrix();
		if (clothID == 2)
			glTranslatef(0, 0.001, 0.0);

		glPushMatrix();
		if (clothID == 1)
			glColor3f(0.42, 0.75, 1);
		else
			glColor3f(1, 0.56, 0.56);

		for (int i = 0; i < mFaceList->size(); i++)
		{
			glBegin(GL_TRIANGLES);
			Vector3i index = mFaceList->at(i);
			CNode *Node[3];

			Node[0] = mNodeArray->at(index.x());
			Node[1] = mNodeArray->at(index.y());
			Node[2] = mNodeArray->at(index.z());
			
			glNormal3f(Node[0]->NormalVector.x() / Node[0]->faceCount, Node[0]->NormalVector.y() / Node[0]->faceCount, Node[0]->NormalVector.z() / Node[0]->faceCount);
			glVertex3f(Node[0]->mPosition.x(), Node[0]->mPosition.y(), Node[0]->mPosition.z());
			glNormal3f(Node[1]->NormalVector.x() / Node[1]->faceCount, Node[1]->NormalVector.y() / Node[1]->faceCount, Node[1]->NormalVector.z() / Node[1]->faceCount);
			glVertex3f(Node[1]->mPosition.x(), Node[1]->mPosition.y(), Node[1]->mPosition.z());
			glNormal3f(Node[2]->NormalVector.x() / Node[2]->faceCount, Node[2]->NormalVector.y() / Node[2]->faceCount, Node[2]->NormalVector.z() / Node[2]->faceCount);
			glVertex3f(Node[2]->mPosition.x(), Node[2]->mPosition.y(), Node[2]->mPosition.z());
			glEnd();
		}

		glPopMatrix();
		glPushMatrix();

		// Node Rendering
		glPointSize(3.0);
		glBegin(GL_POINTS);
		for (int i = 0; i < mNodeArray->size(); i++)
		{
			if (mNodeArray->at(i)->SimulationFlag) continue;
			else glColor3f(1.0, 0.0, 0.0);  // 고정된 node들은 Red 
			glVertex3f(mNodeArray->at(i)->mPosition[0] + mOffset, mNodeArray->at(i)->mPosition[1], mNodeArray->at(i)->mPosition[2]);
		}
		glEnd();
		glPopMatrix();
		glPushMatrix();
		// Spring Rendering


		for (int i = 0; i < Structural_Spring_Count + Shear_Spring_Count; i++)
		{
			glBegin(GL_LINES);

			if (clothID == 1)
				glColor3f(0.0, 0.0, 0.0);
			else
				glColor3f(1, 1, 1);
			glVertex3f(mSpringArray->at(i)->m1->mPosition[0] + mOffset, mSpringArray->at(i)->m1->mPosition[1], mSpringArray->at(i)->m1->mPosition[2]);
			glVertex3f(mSpringArray->at(i)->m2->mPosition[0] + mOffset, mSpringArray->at(i)->m2->mPosition[1], mSpringArray->at(i)->m2->mPosition[2]);
			glEnd();
		}
		glPopMatrix();

		glPopMatrix();                   
	
	
}