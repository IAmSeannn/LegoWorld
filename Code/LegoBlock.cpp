#include "LegoBlock.h"

LegoBlock::~LegoBlock()
{
}

void LegoBlock::AddVertices(CUSTOMVERTEX * Verts, std::shared_ptr<int> i)
{
	//give block relavent knowledge
	pVertices = Verts;
	counter = i;

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
}

void LegoBlock::AddFaceHorizontal(float x1, float y1, float z1, float x2, float y2, float z2)
{
	//triangle 1
	pVertices[*counter].x = x1;
	pVertices[*counter].y = y1;
	pVertices[*counter].z = z1;
	pVertices[*counter].colour = 0x00ff0000; // (red)

	(*counter)++;

	pVertices[*counter].x = x1;
	pVertices[*counter].y = y2;
	pVertices[*counter].z = z2;
	pVertices[*counter].colour = 0x00ff0000; // (yellow)

	(*counter)++;

	pVertices[*counter].x = x2;
	pVertices[*counter].y = y2;
	pVertices[*counter].z = z2;
	pVertices[*counter].colour = 0x00ff0000; // (green)

	(*counter)++;

	//triangle 2
	pVertices[*counter].x = x2;
	pVertices[*counter].y = y2;
	pVertices[*counter].z = z2;
	pVertices[*counter].colour = 0x00ff0000; // (red)

	(*counter)++;

	pVertices[*counter].x = x2;
	pVertices[*counter].y = y1;
	pVertices[*counter].z = z1;
	pVertices[*counter].colour = 0x00ff0000; // (yellow)

	(*counter)++;

	pVertices[*counter].x = x1;
	pVertices[*counter].y = y1;
	pVertices[*counter].z = z1;
	pVertices[*counter].colour = 0x00ff0000; // (green)

	(*counter)++;
}

void LegoBlock::AddFaceVertical(float x1, float y1, float z1, float x2, float y2, float z2)
{
	//triangle 1
	pVertices[*counter].x = x1;
	pVertices[*counter].y = y1;
	pVertices[*counter].z = z1;
	pVertices[*counter].colour = 0x00ff0000; // (red)

	(*counter)++;

	pVertices[*counter].x = x1;
	pVertices[*counter].y = y2;
	pVertices[*counter].z = z1;
	pVertices[*counter].colour = 0x00ff0000; // (yellow)

	(*counter)++;

	pVertices[*counter].x = x2;
	pVertices[*counter].y = y2;
	pVertices[*counter].z = z2;
	pVertices[*counter].colour = 0x00ff0000; // (green)

	(*counter)++;

	//triangle 2
	pVertices[*counter].x = x2;
	pVertices[*counter].y = y2;
	pVertices[*counter].z = z2;
	pVertices[*counter].colour = 0x00ff0000; // (red)

	(*counter)++;

	pVertices[*counter].x = x2;
	pVertices[*counter].y = y1;
	pVertices[*counter].z = z2;
	pVertices[*counter].colour = 0x00ff0000; // (yellow)

	(*counter)++;

	pVertices[*counter].x = x1;
	pVertices[*counter].y = y1;
	pVertices[*counter].z = z1;
	pVertices[*counter].colour = 0x00ff0000; // (green)

	(*counter)++;
}