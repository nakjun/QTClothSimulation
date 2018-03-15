#pragma once
#include <QGLWidget>
#include <QtOpenGL>
#include "Cloth.h"
#include "render.h"
#include "Barycentric.h"
class MyGLwidget : public QGLWidget
{
	
public:
	MyGLwidget(QWidget *parent = 0);
	void initializeGL();
	void paintGL();
	void resizeGL(int w, int h);
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void wheelEvent(QWheelEvent *event);
	void reset();
public:
	bool BarycentricFlag = false;	
	bool SimulationFlag = false;

	CCloth *Cloth1;//Reference Model
	CCloth *Cloth2;//Simulation Model
	CRender *Renderer;
	CBarycentric *Bary;
	bool isBarycentric = false;
	
	int updateTag=0;
	

private slots:
	void animate();

private:
	QTimer *timer;
	QPoint lastPosition;

	float eyeOrigin[3];
	float eye[3];
	float _center[3];
	float up[3];
};