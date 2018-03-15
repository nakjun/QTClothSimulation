#pragma once
#include "Include.h"
#include "Cloth.h"

#include <gl\glut.h>


class CRender{
public:
	CRender();
	~CRender();

	void setCamera(float x, float y, float z);
	void render();
	void init();
	void update(int tag);
	void AddClothModel(CCloth *model);

public:
	vector<CCloth *> *Cloth_Model_List;
};