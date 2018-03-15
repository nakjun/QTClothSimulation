#include "render.h"

CRender::CRender()
{
	init();	
}

void CRender::init()
{
	Cloth_Model_List = new vector<CCloth *>();
	Cloth_Model_List->clear();
}

void CRender::update(int tag)
{	
	if (tag == 1)
	{
		//Reference Model Update Method
		Cloth_Model_List->at(0)->update();

		//Simulation Model Update Method
		Cloth_Model_List->at(1)->applyCartesian(Cloth_Model_List->at(0));
	}
	else if (tag == 2)
	{
		Cloth_Model_List->at(0)->update();
	}
	else if (tag == 3)
	{
		Cloth_Model_List->at(1)->update();
	}
	else if (tag == 4)
	{
		Cloth_Model_List->at(0)->update();
		Cloth_Model_List->at(1)->update();
	}
}

void CRender::AddClothModel(CCloth *model)
{
	Cloth_Model_List->push_back(model);
}


void CRender::render()
{
	for (int i = 0; i < Cloth_Model_List->size(); i++)
	{
		Cloth_Model_List->at(i)->render();
	}
}

