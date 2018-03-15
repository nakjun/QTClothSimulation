#include "qtclothsimulation.h"
#include "Barycentric.h"
QTClothSimulation::QTClothSimulation(QWidget *parent)
: QMainWindow(parent), ui(new Ui::QTClothSimulationClass)
{
	ui->setupUi(this);
	StructuralKs1 = 1000.0f;
	ShearKs1 = 800.0f;
	BendKs1 = 900.0f;

	StructuralKs2 = 0.0f;
	ShearKs2 = 0.0f;
	BendKs2 = 0.0f;

	Kd1 = 0.0001f;
	Kd2 = 0.0001f;
	N1 = 16;
	M1 = 16;
	N2 = 8;
	M2 = 8;
}

QTClothSimulation::~QTClothSimulation()
{

}

void QTClothSimulation::ResetParam()
{
	this->ui->widget->isBarycentric = false;
	this->ui->widget->reset();
}

void QTClothSimulation::setBarycentricFlag()
{
	if (this->ui->widget->isBarycentric == false)
	{
		this->ui->widget->Bary = new CBarycentric(this->ui->widget->Cloth1, this->ui->widget->Cloth2);
		this->ui->widget->isBarycentric = true;
		this->ui->widget->SimulationFlag = false;
	}		
	this->ui->widget->BarycentricFlag = true;
	this->ui->widget->updateTag = 1;
}
void QTClothSimulation::setBarycentricFlagFalse ()
{
	this->ui->widget->BarycentricFlag = false;
	this->ui->widget->updateTag = 0;
}

void QTClothSimulation::CreateReferenceModel()
{
	//this->ui->widget->Cloth1 = new CCloth(StructuralKs1,ShearKs1,BendKs1,Kd1, N1, M1, -8.5, 1, 1);	
	this->ui->widget->Cloth1 = new CCloth(StructuralKs1, ShearKs1, BendKs1, Kd1, N1, M1, 0, 1, 1);
	this->ui->widget->Renderer->AddClothModel(this->ui->widget->Cloth1);
}

void QTClothSimulation::CreateSimulationModel()
{
	//this->ui->widget->Cloth2 = new CCloth(StructuralKs2, ShearKs2, BendKs2, Kd2, N2, M2, -0.25, 2, 2);
	this->ui->widget->Cloth2 = new CCloth(StructuralKs2, ShearKs2, BendKs2, Kd2, N2, M2, 0, 2, 2);
	this->ui->widget->Renderer->AddClothModel(this->ui->widget->Cloth2);
}

void QTClothSimulation::setupdateTag()
{
	this->ui->widget->isBarycentric = false;
	this->ui->widget->SimulationFlag = true;
}
void QTClothSimulation::setupdateTagFalse()
{
	this->ui->widget->isBarycentric = false;
	this->ui->widget->SimulationFlag = false;
}

void QTClothSimulation::setReferenceTag(bool flag)
{
	this->ui->widget->updateTag = 2;
}

void QTClothSimulation::setSimulationTag(bool flag)
{
	this->ui->widget->updateTag = 3;
}
void QTClothSimulation::setBothTag(bool flag)
{
	this->ui->widget->updateTag = 4;
}

void QTClothSimulation::getReferenceNodeNum1(int nodeN)
{
	N1 = nodeN;
}
void QTClothSimulation::getReferenceNodeNum2(int nodeM)
{
	M1 = nodeM;
}
void QTClothSimulation::getSimulationNodeNum1(int nodeN)
{
	N2 = nodeN;
}
void QTClothSimulation::getSimulationNodeNum2(int nodeM)
{
	M2 = nodeM;
}
void QTClothSimulation::setReferenceStructuralKs(double ks)
{
	StructuralKs1 = (float)ks;
}
void QTClothSimulation::setSimulationStructuralKs(double ks)
{
	StructuralKs2 = (float)ks;
}
void QTClothSimulation::setReferenceShearKs(double ks)
{
	ShearKs1 = (float)ks;
}
void QTClothSimulation::setSimulationShearKs(double ks)
{
	ShearKs2 = (float)ks;
}
void QTClothSimulation::setReferenceBendKs(double ks)
{
	BendKs1 = (float)ks;
}
void QTClothSimulation::setSimulationBendKs(double ks)
{
	BendKs2 = (float)ks;
}
void QTClothSimulation::setReferenceKd(double kd)
{
	Kd2 = (float)kd;
}
void QTClothSimulation::setSimulationKd(double kd)
{
	Kd2 = (float)kd;
}