#include "LegoBlock.h"

LegoBlock::~LegoBlock()
{
}

void LegoBlock::SetCovereds(std::vector<std::shared_ptr<LegoBlock>>&v)
{
	//check for top covered
	auto top = std::find_if(v.begin(), v.end(), [this](const std::shared_ptr<LegoBlock>& obj) {return (obj->y == this->y + 1) && (obj->x == this->x) && (obj->z == this->z); });
	if (top != v.end())
	{
		TopCovered = true;
	}

	//check for bottom covered
	auto bottom = std::find_if(v.begin(), v.end(), [this](const std::shared_ptr<LegoBlock>& obj) {return (obj->y == this->y - 1) && (obj->x == this->x) && (obj->z == this->z); });
	if (bottom != v.end())
	{
		BottomCovered = true;
	}

	//check for front covered
	auto front = std::find_if(v.begin(), v.end(), [this](const std::shared_ptr<LegoBlock>& obj) {return (obj->y == this->y) && (obj->x == this->x) && (obj->z == this->z-1); });
	if (front != v.end())
	{
		FrontCovered = true;
	}

	//check for back covered
	auto back = std::find_if(v.begin(), v.end(), [this](const std::shared_ptr<LegoBlock>& obj) {return (obj->y == this->y) && (obj->x == this->x) && (obj->z == this->z+1); });
	if (back != v.end())
	{
		BackCovered = true;
	}

	//check for right covered
	auto right = std::find_if(v.begin(), v.end(), [this](const std::shared_ptr<LegoBlock>& obj) {return (obj->y == this->y) && (obj->x == this->x+1) && (obj->z == this->z); });
	if (right != v.end())
	{
		RightCovered = true;
	}

	//check for left covered
	auto left = std::find_if(v.begin(), v.end(), [this](const std::shared_ptr<LegoBlock>& obj) {return (obj->y == this->y) && (obj->x == this->x-1) && (obj->z == this->z); });
	if (left != v.end())
	{
		LeftCovered = true;
	}
}
