#include "LegoBlock.h"

LegoBlock::~LegoBlock()
{
}

//stud quality
float Height = 0.2; //height of cylindar
const int Sides = 10;
bool BlockLocations[50][10][50] = {{{false}}};

					//basic buffers
LPDIRECT3DVERTEXBUFFER9 pTopBuffer = NULL; // Buffer to hold vertices of basic block
LPDIRECT3DVERTEXBUFFER9 pBottomBuffer = NULL; // Buffer to hold vertices of basic block
LPDIRECT3DVERTEXBUFFER9 pFrontBuffer = NULL; // Buffer to hold vertices of basic block
LPDIRECT3DVERTEXBUFFER9 pLeftBuffer = NULL; // Buffer to hold vertices of basic block
LPDIRECT3DVERTEXBUFFER9 pRightBuffer = NULL; // Buffer to hold vertices of basic block
LPDIRECT3DVERTEXBUFFER9 pBackBuffer = NULL; // Buffer to hold vertices of basic block
LPDIRECT3DVERTEXBUFFER9 pStudBuffer = NULL; // Buffer to hold vertices of basic block
LPDIRECT3DVERTEXBUFFER9 pStudBufferHQTop = NULL; // Buffer to hold vertices of basic block
LPDIRECT3DVERTEXBUFFER9 pStudBufferHQSides = NULL; // Buffer to hold vertices of basic block

LPDIRECT3DTEXTURE9		g_pGreenBrick = NULL; // The texture.
LPDIRECT3DTEXTURE9		g_pRedBrick = NULL; // The texture.
LPDIRECT3DTEXTURE9		g_pGreyBrick = NULL; // The texture.

std::vector<std::shared_ptr<LegoBlock>> g_Blocks;
D3DXVECTOR3 g_vCamera(25.0f, 25.0f, -20.0f);

LPDIRECT3DDEVICE9       g_pd3dDevice = NULL; // The rendering device
FrustumClass* g_Frustum = new FrustumClass;

void LegoBlock::SetCovereds(std::vector<std::shared_ptr<LegoBlock>>&v)
{
	for (int i = 0; i < xNum; ++i)
	{
		for (int j = 0; j < zNum; ++j)
		{
			//check left
			if (!BlockLocations[(int)x-1][(int)y][(int)z + j])
			{
				LeftCovered = false;
			}

			//check right
			if (!BlockLocations[(int)x + xNum][(int)y][(int)z + j])
			{
				RightCovered = false;
			}

			//check top
			if (!BlockLocations[(int)x + i][(int)y+1][(int)z + j])
			{
				TopCovered = false;
			}

			//checl bottom
			if (!BlockLocations[(int)x + i][(int)y - 1][(int)z + j])
			{
				BottomCovered = false;
			}

			//check front
			if (!BlockLocations[(int)x + i][(int)y][(int)z - 1])
			{
				FrontCovered = false;
			}

			//check back
			if (!BlockLocations[(int)x + i][(int)y][(int)z +zNum])
			{
				BackCovered = false;
			}
			
		}
	}
}

void LegoBlock::render()
{
	g_pd3dDevice->SetTexture(0, Texture);
	g_pd3dDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_DIFFUSE);
	g_pd3dDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_TEXTURE);
	g_pd3dDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);


	//check if on screen

	if (g_Frustum->CheckSphere(x, y, z, 0.8f))
	{
		g_pd3dDevice->SetTransform(D3DTS_WORLD, &WorldMat);

		//Draw studs first
		if (!TopCovered)
		{
			//check how close brick is
			D3DXVECTOR3 brickPos(x, y, z);
			D3DXVECTOR3 * length(new D3DXVECTOR3(g_vCamera - brickPos));
			if (D3DXVec3Length(length) >= 40)
			{
				for (auto studMat : studLocations)
				{
					g_pd3dDevice->SetTransform(D3DTS_WORLD, &studMat);
					//draw lq version
					g_pd3dDevice->SetStreamSource(0, pStudBuffer, 0, sizeof(CUSTOMVERTEX));
					g_pd3dDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 6 * 2);
				}
			}
			else
			{
				for (auto studMat : studLocations)
				{
					g_pd3dDevice->SetTransform(D3DTS_WORLD, &studMat);
					//draw hq version
					//draw sides
					g_pd3dDevice->SetStreamSource(0, pStudBufferHQSides, 0, sizeof(CUSTOMVERTEX));
					g_pd3dDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, Sides * 2);
					g_pd3dDevice->SetStreamSource(0, pStudBufferHQTop, 0, sizeof(CUSTOMVERTEX));
					g_pd3dDevice->DrawPrimitive(D3DPT_TRIANGLEFAN, 0, Sides);
				}
			}
			delete length;
		}	
	}

	//then stretch brick to corrent size
	g_pd3dDevice->SetTransform(D3DTS_WORLD, &PostWorldMat);

	//top
	if (!TopCovered)
	{
		g_pd3dDevice->SetStreamSource(0, pTopBuffer, 0, sizeof(CUSTOMVERTEX));
		g_pd3dDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);

	}
	//bottom
	if (!BottomCovered)
	{
		g_pd3dDevice->SetStreamSource(0, pBottomBuffer, 0, sizeof(CUSTOMVERTEX));
		g_pd3dDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);
	}
	//front
	if (!FrontCovered)
	{
		g_pd3dDevice->SetStreamSource(0, pFrontBuffer, 0, sizeof(CUSTOMVERTEX));
		g_pd3dDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);
	}
	//left
	if (!LeftCovered)
	{
		g_pd3dDevice->SetStreamSource(0, pLeftBuffer, 0, sizeof(CUSTOMVERTEX));
		g_pd3dDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);
	}
	//right
	if (!RightCovered)
	{
		g_pd3dDevice->SetStreamSource(0, pRightBuffer, 0, sizeof(CUSTOMVERTEX));
		g_pd3dDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);
	}
	//back
	if (!BackCovered)
	{
		g_pd3dDevice->SetStreamSource(0, pBackBuffer, 0, sizeof(CUSTOMVERTEX));
		g_pd3dDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);
	}
}
