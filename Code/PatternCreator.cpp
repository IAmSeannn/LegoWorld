#include "PatternCreator.h"



PatternCreator::PatternCreator()
{
}


PatternCreator::~PatternCreator()
{
}

 void PatternCreator::AddUniformAmount(std::vector<std::shared_ptr<LegoBlock>> &blocks, int sizeX, int sizeY, int sizeZ, float posX, float posY, float posZ, LPDIRECT3DTEXTURE9 tex)
{

	for (int sX = 0; sX < sizeX; sX++)
	{
		for (int sY = 0; sY < sizeY; sY++)
		{
			for (int sZ = 0; sZ < sizeZ; sZ++)
			{
				std::shared_ptr<LegoBlock> b(new LegoBlock(posX + sX, posY + sY, posZ + sZ, tex));
				blocks.push_back(b);
			}
		}
	}
}
