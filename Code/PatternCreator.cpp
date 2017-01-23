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
				std::shared_ptr<LegoBlock> b(new LegoBlock(1, 1,posX + sX, posY + sY, posZ + sZ, tex));
				blocks.push_back(b);
			}
		}
	}
}

 void PatternCreator::AddFlatPlane(std::vector<std::shared_ptr<LegoBlock>> &blocks, int sizeX, int sizeY, int sizeZ, float posX, float posY, float posZ, LPDIRECT3DTEXTURE9 tex)
 {
	 for (int sX = 0; sX < sizeX; sX+=2)
	 {
		 for (int sY = 0; sY < sizeY; sY++)
		 {
			 for (int sZ = 0; sZ < sizeZ; sZ += 2)
			 {
				 std::shared_ptr<LegoBlock> b(new LegoBlock(2, 2, posX + sX, posY + sY, posZ + sZ, tex));
				 blocks.push_back(b);
			 }
		 }
	 }
 }

 void PatternCreator::AddWall(std::vector<std::shared_ptr<LegoBlock>>&blocks, int sizeX, int sizeY, int sizeZ, float posX, float posY, float posZ, LPDIRECT3DTEXTURE9 tex)
 {
	 int numOfFullBlocks = 0;
	 int sizeOfFinalBrick = 0;
	 bool alternate = false;
	 //decide direction
	 if (sizeX > sizeZ)
	 {
		 //going in x direction
		 numOfFullBlocks = sizeX / 4;
		 sizeOfFinalBrick = sizeX % 4;

		 //build z number of walls
		 for (int j = 0; j < sizeZ; ++j)
		 {
			 for (int k = 0; k < sizeY; ++k)
			 {
				 if (alternate)
				 {
					 //place all the full size (1x4) blocks
					 for (int i = 0; i < numOfFullBlocks * 4; i += 4)
					 {
						 std::shared_ptr<LegoBlock> b(new LegoBlock(4, 1, posX + i, posY + k, posZ + j, tex));
						 blocks.push_back(b);
					 }
					 std::shared_ptr<LegoBlock> b(new LegoBlock(sizeOfFinalBrick, 1, posX + sizeX - sizeOfFinalBrick, posY + k, posZ + j, tex));
					 blocks.push_back(b);
				 }
				 else
				 {
					 std::shared_ptr<LegoBlock> b(new LegoBlock(sizeOfFinalBrick, 1, posX, posY + k, posZ + j, tex));
					 blocks.push_back(b);

					 //place all the full size (1x4) blocks
					 for (int i = sizeOfFinalBrick; i < sizeX; i += 4)
					 {
						 std::shared_ptr<LegoBlock> b(new LegoBlock(4, 1, posX + i, posY + k, posZ + j, tex));
						 blocks.push_back(b);
					 }
					 
				 }
				 alternate = !alternate;
			 } 
		 }	 
	 }
	 else
	 {
		 //going in z direction
		 numOfFullBlocks = sizeZ / 4;
		 sizeOfFinalBrick = sizeZ % 4;

		 //build x number of walls
		 for (int j = 0; j < sizeX; ++j)
		 {
			 for (int k = 0; k < sizeY; ++k)
			 {
				 if (alternate)
				 {
					 //place all the full size (1x4) blocks
					 for (int i = 0; i < numOfFullBlocks * 4; i += 4)
					 {
						 std::shared_ptr<LegoBlock> b(new LegoBlock(1, 4, posX + j, posY + k, posZ + i, tex));
						 blocks.push_back(b);
					 }
					 std::shared_ptr<LegoBlock> b(new LegoBlock(1, sizeOfFinalBrick, posX + j, posY + k, posZ + sizeZ - sizeOfFinalBrick, tex));
					 blocks.push_back(b);
				 }
				 else
				 {
					 std::shared_ptr<LegoBlock> b(new LegoBlock(1, sizeOfFinalBrick, posX + j, posY + k, posZ, tex));
					 blocks.push_back(b);
					 //place all the full size (1x4) blocks
					 for (int i = sizeOfFinalBrick; i < sizeZ; i += 4)
					 {
						 std::shared_ptr<LegoBlock> b(new LegoBlock(1, 4, posX + j, posY + k, posZ + i, tex));
						 blocks.push_back(b);
					 }
					 
				 }
				 alternate = !alternate;
			 }
		 }
	 }
 }

 void PatternCreator::AddHouse(std::vector<std::shared_ptr<LegoBlock>>&blocks, float posX, float posY, float posZ)
 {
	 //9 along x axis
	 //8 along z axis
	 int height = 5;

	 //front wall
	 AddWall(blocks, 9, height, 1, posX + 1, posY, posZ, g_pRedBrick);
	 //back wall
	 AddWall(blocks, 9, height, 1, posX + 1, posY, posZ+7, g_pRedBrick);
	 //left
	 AddWall(blocks, 1, height, 8, posX, posY, posZ, g_pRedBrick);
	 //right wall
	 AddWall(blocks, 1, height, 8, posX+10, posY, posZ, g_pRedBrick);

	 ////////////////////
	 //ROOF
	 ///////////////////
	 AddFlatPlane(blocks, 13, 1, 10, posX - 1, posY + height, posZ - 1, g_pGreyBrick);
	 AddFlatPlane(blocks, 9, 1, 6, posX + 1, posY + height + 1, posZ + 1, g_pGreyBrick);
	 AddFlatPlane(blocks, 5, 1, 2, posX + 3, posY + height +2, posZ + 3, g_pGreyBrick);

 }

 void PatternCreator::AddBridge(std::vector<std::shared_ptr<LegoBlock>>&blocks, float posX, float posY, float posZ)
 {
	 AddWall(blocks, 1, 3, 7, posX, posY, posZ, g_pGreyBrick);
	 AddWall(blocks, 1, 3, 7, posX+3, posY, posZ, g_pGreyBrick);

	 AddWall(blocks, 4, 1, 1, posX, posY + 3, posZ, g_pGreyBrick);
	 AddWall(blocks, 4, 1, 1, posX, posY + 3, posZ+2, g_pGreyBrick);
	 AddWall(blocks, 4, 1, 1, posX, posY + 3, posZ+4, g_pGreyBrick);
	 AddWall(blocks, 4, 1, 1, posX, posY + 3, posZ+6, g_pGreyBrick);
 }

 void PatternCreator::AddBoat(std::vector<std::shared_ptr<LegoBlock>>&blocks, float posX, float posY, float posZ)
 {
	 //block 1
	 std::shared_ptr<LegoBlock> b1(new LegoBlock(2, 2, posX, posY, posZ, g_pBoatBrick));
	 b1->moveable = true;
	 b1->SetCovereds(g_Blocks);
	 g_Blocks.push_back(b1);

	 //block 2
	 std::shared_ptr<LegoBlock> b2(new LegoBlock(2, 2, posX+2, posY, posZ, g_pBoatBrick));
	 b2->moveable = true;
	 b2->SetCovereds(g_Blocks);
	 g_Blocks.push_back(b2);

	 //block 3
	 std::shared_ptr<LegoBlock> b3(new LegoBlock(2, 2, posX+1, posY+1, posZ, g_pBoatBrick));
	 b3->moveable = true;
	 b3->SetCovereds(g_Blocks);
	 g_Blocks.push_back(b3);
 }