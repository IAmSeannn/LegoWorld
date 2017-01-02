#pragma once
#include "LegoBlock.h"
#include <vector>
class PatternCreator
{
public:
	PatternCreator();
	~PatternCreator();

	static void AddUniformAmount(std::vector<LegoBlock>&, int, int, int, float, float, float, ColourData);
};

