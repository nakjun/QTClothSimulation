#pragma once
#include "myglwidget.h"
#include <cmath>
#include <windows.h> 
#include <QMessageBox>

enum CAMERA_MODE{ CAMERA_MOVE = 1, CAMERA_ROTATE = 2, CAMERA_ZOOM = 4 };

float AmbientColor[] = { 0.5f, 0.5f, 0.5f, 1.0f };         //주변광
float DiffuseColor1[] = { 1.0f, 1.0f, 1.0f, 1.0f };          //분산광
float DiffuseColor2[] = { 0.0f, 1.0f, 0.0f, 1.0f };          //분산광
float SpecularColor[] = { 0.7f, 0.7f, 0.7f, 1.0f };        //방사광
float Position1[] = { 5.0f, 10.0f, 5.0f, 1.0f };  
float Position2[] = { -5.0f, 10.0f, 5.0f, 1.0f }; 

float yMinLimit = -60.0f;
float yMaxLimit = 80.0f;

float xRot = 0;
float yRot = 0;

float angleX = 0.0f;
float angleY = 0.0f;

float Interval = 0.1;

int prevX;
int currX;

int prevY;
int currY;

int ViewX = 0, ViewY = 0;

float deltaAngleX = 0.0f;
float deltaAngleY = 0.0f;
int xOrigin = -1;
int yOrigin = -1;
int currFrame = 0;
int SIDE_WIDTH = 300;


MyGLwidget::MyGLwidget(QWidget *parent) :
 QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{		
	Renderer = new CRender();

	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), SLOT(updateGL()));
	timer->start();

	for (int i = 0; i < 3; i++)
	{
		eye[i] = 0.0f;
		_center[i] = 0.0f;
		up[i] = 0.0f;
	}

	eye[2] = 40.0f;
	for (int i = 0; i < 3; i++) eyeOrigin[i] = eye[i];
	up[1] = 1.0f;

	prevX = 0;
	prevY = 0;
}

void MyGLwidget::animate()
{
	qDebug() << "C++ Style Debug Message";
	
	this->update();
}

void MyGLwidget::initializeGL()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	//glShadeModel(GL_SMOOTH);
	glShadeModel(GL_PHONG_WIN);	
	glEnable(GL_CULL_FACE);                               // 후면 제거
	glEnable(GL_LIGHTING);

	// LIGHT0 설정
	glLightfv(GL_LIGHT0, GL_AMBIENT, AmbientColor);       
	glLightfv(GL_LIGHT0, GL_DIFFUSE, DiffuseColor1);
	glLightfv(GL_LIGHT0, GL_SPECULAR, SpecularColor);       
	glLightfv(GL_LIGHT0, GL_POSITION, Position1);     
	
	// LIGHT1 설정
	glLightfv(GL_LIGHT1, GL_AMBIENT, AmbientColor);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, DiffuseColor2);
	glLightfv(GL_LIGHT1, GL_SPECULAR, SpecularColor);
	glLightfv(GL_LIGHT1, GL_POSITION, Position2);

	// LIGHT0을 켠다.
	glEnable(GL_LIGHT0);
	//glEnable(GL_LIGHT1);
	glEnable(GL_COLOR_MATERIAL);
	//glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void MyGLwidget::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();

	glPushMatrix();
	gluLookAt(eye[0], eye[1], eye[2], _center[0], _center[1], _center[2], up[0], up[1], up[2]);			
	
	//update tag 1: Barycentric 2: Reference 3: Simulation
	
	if (BarycentricFlag)
		Renderer->update(updateTag);
	
	Renderer->render();
	glPopMatrix();
	glFlush();
}

void MyGLwidget::resizeGL(int w, int h)
{
	if (h == 0) h = 1;
	GLfloat aspect = (GLfloat)w / (GLfloat)h;

	glViewport(0, 0, w, h);


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45.0f, aspect, 0.1f, 10000.0f);
}

void MyGLwidget::mousePressEvent(QMouseEvent *event) {
	lastPosition = event->pos();
}

void MyGLwidget::wheelEvent(QWheelEvent *event) {	
	eye[2] += (event->delta() / 20);	
}

void MyGLwidget::mouseMoveEvent(QMouseEvent *event) {
	float sensitive = 0.05;
	eye[0] += (event->x() - lastPosition.x()) * sensitive;
	eye[1] += (event->y() - lastPosition.y()) * sensitive;

	lastPosition = event->pos();
}

void MyGLwidget::reset()
{
	for (int i = 0; i < 3; i++) eye[i] = eyeOrigin[i];	
	
	//제대로 작동하지 않음..	
	for (int i = 0; i < Renderer->Cloth_Model_List->size(); i++)
	{
		CCloth *temp = Renderer->Cloth_Model_List->at(i);

		for (int j = 0; j < temp->mNodeCount; j++)
		{
			temp->mNodeArray->at(j) = temp->mOriginNodeArray->at(j);
		}
		
		Renderer->Cloth_Model_List->at(i) = temp;	
	}
}