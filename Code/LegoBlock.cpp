#include "LegoBlock.h"

LegoBlock::~LegoBlock()
{
}

void LegoBlock::SetCovereds(std::vector<std::shared_ptr<LegoBlock>>&v)
{
	for (int i = 0; i < v.size(); ++i)
	{
		if ((v[i]->y == this->y + 1) && (v[i]->x == this->x) && (v[i]->z == this->z))
		{
			TopCovered = true;
		}

		else if ((v[i]->y == this->y - 1) && (v[i]->x == this->x) && (v[i]->z == this->z))
		{
			BottomCovered = true;
		}

		else if ((v[i]->y == this->y) && (v[i]->x == this->x) && (v[i]->z == this->z - 1))
		{
			FrontCovered = true;
		}

		else if ((v[i]->y == this->y) && (v[i]->x == this->x) && (v[i]->z == this->z + 1))
		{
			BackCovered = true;
		}

		else if ((v[i]->y == this->y) && (v[i]->x == this->x + 1) && (v[i]->z == this->z))
		{
			RightCovered = true;
		}

		else if ((v[i]->y == this->y) && (v[i]->x == this->x - 1) && (v[i]->z == this->z))
		{
			LeftCovered = true;
		}
	}
}
