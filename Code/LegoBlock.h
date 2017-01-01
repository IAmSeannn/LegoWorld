#pragma once
#include "CUSTOMVERTEX.h"
#include <memory>
class LegoBlock
{
public:
	LegoBlock(float ix, float iy, float iz) : x(ix), y(iy), z(iz) {};
	~LegoBlock();
	void AddVertices(CUSTOMVERTEX*, std::shared_ptr<int>);
	static const int VertNum = 36;

private:
	float x, y, z;
	void AddFaceHorizontal(float, float, float, float, float, float);
	void AddFaceVertical(float, float, float, float, float, float);
	void AddNormal(float, float, float);
	CUSTOMVERTEX * pVertices;
	std::shared_ptr<int> counter;
};

