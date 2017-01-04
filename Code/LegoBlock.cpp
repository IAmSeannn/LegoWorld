#include "LegoBlock.h"

LegoBlock::~LegoBlock()
{
}

void LegoBlock::AddVertices(CUSTOMVERTEX * verts)
{
	pVertices = verts;
	counter = 0;
	//maths are for a 1x1 lego block
	//front face
	AddFaceVertical(x, y, z, x + 1, y + 1, z);

	//right face
	AddFaceVertical(x + 1, y, z, x + 1, y + 1, z + 1);

	//top face
	AddFaceHorizontal(x, y + 1, z, x + 1, y + 1, z + 1);

	//left face
	AddFaceVertical(x, y, z + 1, x, y + 1, z);

	//back face
	AddFaceVertical(x + 1, y, z + 1, x, y + 1, z + 1);

	//bottom face
	AddFaceHorizontal(x, y, z + 1, x + 1, y, z);

	//start again and add normals
	counter = 0;

	//front normals
	AddNormal(0.0, 0.0, -1.0);

	//rigth normals
	AddNormal(1.0, 0.0, 0.0);

	//back normals
	AddNormal(0.0, 0.0, 1.0);

	//left normals
	AddNormal(-1.0, 0.0, 0.0);

	//top normal
	AddNormal(0.0, 1.0, 0.0);

	//bottom normal
	AddNormal(0.0, -1.0, 0.0);
}

void LegoBlock::AddFaceHorizontal(float x1, float y1, float z1, float x2, float y2, float z2)
{
	//triangle 1
	pVertices[counter].position.x = x1;
	pVertices[counter].position.y = y1;
	pVertices[counter].position.z = z1;

	counter++;

	pVertices[counter].position.x = x1;
	pVertices[counter].position.y = y2;
	pVertices[counter].position.z = z2;

	counter++;

	pVertices[counter].position.x = x2;
	pVertices[counter].position.y = y2;
	pVertices[counter].position.z = z2;

	counter++;

	//triangle 2
	pVertices[counter].position.x = x2;
	pVertices[counter].position.y = y2;
	pVertices[counter].position.z = z2;

	counter++;

	pVertices[counter].position.x = x2;
	pVertices[counter].position.y = y1;
	pVertices[counter].position.z = z1;

	counter++;

	pVertices[counter].position.x = x1;
	pVertices[counter].position.y = y1;
	pVertices[counter].position.z = z1;

	counter++;
}

void LegoBlock::AddFaceVertical(float x1, float y1, float z1, float x2, float y2, float z2)
{
	//triangle 1
	pVertices[counter].position.x = x1;
	pVertices[counter].position.y = y1;
	pVertices[counter].position.z = z1;

	counter++;

	pVertices[counter].position.x = x1;
	pVertices[counter].position.y = y2;
	pVertices[counter].position.z = z1;

	counter++;

	pVertices[counter].position.x = x2;
	pVertices[counter].position.y = y2;
	pVertices[counter].position.z = z2;

	counter++;

	//triangle 2
	pVertices[counter].position.x = x2;
	pVertices[counter].position.y = y2;
	pVertices[counter].position.z = z2;

	counter++;

	pVertices[counter].position.x = x2;
	pVertices[counter].position.y = y1;
	pVertices[counter].position.z = z2;

	counter++;

	pVertices[counter].position.x = x1;
	pVertices[counter].position.y = y1;
	pVertices[counter].position.z = z1;

	counter++;
}

void LegoBlock::AddNormal(float x, float y, float z)
{
	for (int i = 0; i <= 5; i++)
	{

		pVertices[counter].normal.x = x;
		pVertices[counter].normal.y = y;
		pVertices[counter].normal.z = z;

		counter++;
	}
}