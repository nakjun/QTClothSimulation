#ifndef QTCLOTHSIMULATION_H
#define QTCLOTHSIMULATION_H

#include <QtWidgets/QMainWindow>
#include "ui_qtclothsimulation.h"

class QTClothSimulation : public QMainWindow
{
	Q_OBJECT

public:
	QTClothSimulation(QWidget *parent = 0);
	~QTClothSimulation();
public slots:
	void setBarycentricFlag();
	void setBarycentricFlagFalse();
	
	void setReferenceStructuralKs(double ks);
	void setReferenceShearKs(double ks);
	void setReferenceBendKs(double ks);

	void setSimulationStructuralKs(double ks);
	void setSimulationShearKs(double ks);
	void setSimulationBendKs(double ks);

	void setReferenceKd(double kd);
	void setSimulationKd(double kd);

	void getReferenceNodeNum1(int NodeN);
	void getReferenceNodeNum2(int NodeM);
	void getSimulationNodeNum1(int NodeN);
	void getSimulationNodeNum2(int NodeM);
	void CreateReferenceModel();	
	void CreateSimulationModel();
	void ResetParam();

	void setBothTag(bool flag);
	void setSimulationTag(bool flag);
	void setReferenceTag(bool flag);

	void setupdateTag();
	void setupdateTagFalse();
public:
	int N1,N2;
	int M1,M2;
	float StructuralKs1, StructuralKs2;
	float ShearKs1, ShearKs2;
	float BendKs1, BendKs2;
	float Kd1,Kd2;

private:
	Ui::QTClothSimulationClass *ui;
};

#endif // QTCLOTHSIMULATION_H
