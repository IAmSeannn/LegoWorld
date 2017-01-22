#pragma once
#include <d3dx9math.h>

class FrustumClass
{
public:
	FrustumClass();
	FrustumClass(const FrustumClass&);
	~FrustumClass();
	void ConstructFrustum(float, D3DXMATRIX, D3DXMATRIX);
	bool CheckSphere(float, float, float, float);

private:
	D3DXPLANE m_planes[6];
};