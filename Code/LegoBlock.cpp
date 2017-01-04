#include "LegoBlock.h"

LegoBlock::~LegoBlock()
{
}

void LegoBlock::SetCovereds(std::vector<std::shared_ptr<LegoBlock>>&v)
{
	float temp = y;
	//check for top covered
	auto it = std::find_if(v.begin(), v.end(), [temp](const LegoBlock& obj) {return obj.y == temp + 1; });
}
