#include "LegoBlock.h"

LegoBlock::~LegoBlock()
{
}

void LegoBlock::AddVertices(CUSTOMVERTEX * Verts, std::shared_ptr<int> i)
{
	//give block relavent knowledge
	pVertices = Verts;
	counter = i;
	int old = *counter;

	//maths are for a 2x2 lego block

	//front face
	AddFaceVertical(x, y, z, x + 2, y + 1, z);

	//right face
	AddFaceVertical(x + 2, y, z, x + 2, y + 1, z + 2);

	//top face
	AddFaceHorizontal(x, y + 1, z, x + 2, y + 1, z + 2);

	//left face
	AddFaceVertical(x, y, z + 2, x, y + 1, z);

	//back face
	AddFaceVertical(x + 2, y, z + 2, x, y + 1, z + 2);

	//bottom face
	AddFaceHorizontal(x, y, z + 2, x + 2, y, z);

	//start again and add normals
	*counter = old;

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
	pVertices[*counter].position.x = x1;
	pVertices[*counter].position.y = y1;
	pVertices[*counter].position.z = z1;
	pVertices[*counter].colour = 0x00ff0000; // (red)

	(*counter)++;

	pVertices[*counter].position.x = x1;
	pVertices[*counter].position.y = y2;
	pVertices[*counter].position.z = z2;
	pVertices[*counter].colour = 0x00ff0000; // (yellow)

	(*counter)++;

	pVertices[*counter].position.x = x2;
	pVertices[*counter].position.y = y2;
	pVertices[*counter].position.z = z2;
	pVertices[*counter].colour = 0x00ff0000; // (green)

	(*counter)++;

	//triangle 2
	pVertices[*counter].position.x = x2;
	pVertices[*counter].position.y = y2;
	pVertices[*counter].position.z = z2;
	pVertices[*counter].colour = 0x00ff0000; // (red)

	(*counter)++;

	pVertices[*counter].position.x = x2;
	pVertices[*counter].position.y = y1;
	pVertices[*counter].position.z = z1;
	pVertices[*counter].colour = 0x00ff0000; // (yellow)

	(*counter)++;

	pVertices[*counter].position.x = x1;
	pVertices[*counter].position.y = y1;
	pVertices[*counter].position.z = z1;
	pVertices[*counter].colour = 0x00ff0000; // (green)

	(*counter)++;
}

void LegoBlock::AddFaceVertical(float x1, float y1, float z1, float x2, float y2, float z2)
{
	//triangle 1
	pVertices[*counter].position.x = x1;
	pVertices[*counter].position.y = y1;
	pVertices[*counter].position.z = z1;
	pVertices[*counter].colour = 0x00ff0000; // (red)

	(*counter)++;

	pVertices[*counter].position.x = x1;
	pVertices[*counter].position.y = y2;
	pVertices[*counter].position.z = z1;
	pVertices[*counter].colour = 0x00ff0000; // (yellow)

	(*counter)++;

	pVertices[*counter].position.x = x2;
	pVertices[*counter].position.y = y2;
	pVertices[*counter].position.z = z2;
	pVertices[*counter].colour = 0x00ff0000; // (green)

	(*counter)++;

	//triangle 2
	pVertices[*counter].position.x = x2;
	pVertices[*counter].position.y = y2;
	pVertices[*counter].position.z = z2;
	pVertices[*counter].colour = 0x00ff0000; // (red)

	(*counter)++;

	pVertices[*counter].position.x = x2;
	pVertices[*counter].position.y = y1;
	pVertices[*counter].position.z = z2;
	pVertices[*counter].colour = 0x00ff0000; // (yellow)

	(*counter)++;

	pVertices[*counter].position.x = x1;
	pVertices[*counter].position.y = y1;
	pVertices[*counter].position.z = z1;
	pVertices[*counter].colour = 0x00ff0000; // (green)

	(*counter)++;
}

void LegoBlock::AddNormal(float x, float y, float z)
{
	for (int i = 0; i <= 5; i++)
	{

		pVertices[*counter].normal.x = x;
		pVertices[*counter].normal.x = y;
		pVertices[*counter].normal.x = z;

		(*counter)++;
	}
}

