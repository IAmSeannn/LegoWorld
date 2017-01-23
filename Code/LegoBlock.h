#pragma once
#include <memory>
#include <vector>
#include <algorithm>
#include <d3dx9.h>		// Direct 3D library (for all Direct 3D funtions).
#include "FrustumClass.h"


class LegoBlock;

//stud quality
extern const int Sides; // The number of sides used to contruct the circle. More sides = smoother circle.
extern float Height; //height of cylindar
extern bool BlockLocations[1000][200][1000];

//basic buffers
extern LPDIRECT3DVERTEXBUFFER9 pTopBuffer; // Buffer to hold vertices of basic block
extern LPDIRECT3DVERTEXBUFFER9 pBottomBuffer; // Buffer to hold vertices of basic block
extern LPDIRECT3DVERTEXBUFFER9 pFrontBuffer; // Buffer to hold vertices of basic block
extern LPDIRECT3DVERTEXBUFFER9 pLeftBuffer; // Buffer to hold vertices of basic block
extern LPDIRECT3DVERTEXBUFFER9 pRightBuffer; // Buffer to hold vertices of basic block
extern LPDIRECT3DVERTEXBUFFER9 pBackBuffer; // Buffer to hold vertices of basic block
extern LPDIRECT3DVERTEXBUFFER9 pStudBuffer; // Buffer to hold vertices of basic block
extern LPDIRECT3DVERTEXBUFFER9 pStudBufferHQTop; // Buffer to hold vertices of basic block
extern LPDIRECT3DVERTEXBUFFER9 pStudBufferHQSides; // Buffer to hold vertices of basic block

extern LPDIRECT3DTEXTURE9		g_pGreenBrick; // The texture.
extern LPDIRECT3DTEXTURE9		g_pRedBrick; // The texture.
extern LPDIRECT3DTEXTURE9		g_pGreyBrick; // The texture.
extern LPDIRECT3DTEXTURE9		g_pBlueBrick ; // The texture.
extern LPDIRECT3DTEXTURE9		g_pHouseRedBrick; // The texture.

extern std::vector<std::shared_ptr<LegoBlock>> g_Blocks;
extern D3DXVECTOR3 g_vCamera;

extern LPDIRECT3DDEVICE9       g_pd3dDevice; // The rendering device
extern FrustumClass* g_Frustum;;

struct CUSTOMVERTEX
{
	D3DXVECTOR3 position;	// Position
	D3DXVECTOR3 normal;		// Vertex normal
	FLOAT u, v;				// Texture co-ordinates.
};

class LegoBlock
{
public:
	LegoBlock(int sizeX, int sizeZ, float posX, float posY, float posZ, LPDIRECT3DTEXTURE9 tex) : x(posX), y(posY), z(posZ), Texture(tex), xNum(sizeX), zNum(sizeZ)
	{
		//set BlockLocations to true in correct location
		for (int i = 0; i < sizeX; ++i)
		{
			for (int j = 0; j < sizeZ; ++j)
			{
				BlockLocations[(int)x + i][(int)y][(int)z+j] = true;
			}
		}

		for (int i = 0; i < sizeX; ++i)
		{
			for (int j = 0; j < sizeZ; ++j)
			{
				D3DXMATRIX temp;
				D3DXMatrixIdentity(&temp);
				D3DXMatrixTranslation(&TranslateMat, x+i, y*1.2f, z+j);
				D3DXMatrixScaling(&ScaleMat, 1.0f, 1.2f, 1.0f);
				D3DXMatrixMultiply(&temp, &temp, &ScaleMat);		// First Scale
				D3DXMatrixMultiply(&temp, &temp, &TranslateMat);	// And finally Translate

				studLocations.push_back(temp);
			}
		}

		D3DXMatrixIdentity(&PostWorldMat);
		D3DXMatrixTranslation(&TranslateMat, x, y*1.2f, z);
		D3DXMatrixScaling(&PostScaleMat, sizeX, 1.2f, sizeZ);
		D3DXMatrixMultiply(&PostWorldMat, &PostWorldMat, &PostScaleMat);		// First Scale
		D3DXMatrixMultiply(&PostWorldMat, &PostWorldMat, &TranslateMat);	// And finally Translate

		TopCovered = true;
		BottomCovered = true;
		RightCovered = true;
		LeftCovered = true;
		FrontCovered = true;
		BackCovered = true;
	};
	~LegoBlock();
	LPDIRECT3DTEXTURE9 Texture;
	D3DXMATRIX WorldMat, TranslateMat, ScaleMat;
	D3DXMATRIX PostWorldMat, PostScaleMat;
	
	std::vector<D3DXMATRIX> studLocations;

	bool TopCovered, BottomCovered, RightCovered, LeftCovered, FrontCovered, BackCovered;
	void SetCovereds(std::vector<std::shared_ptr<LegoBlock>>&);
	void render();
	int xNum, zNum;
	float x, y, z;
protected:
	
};

