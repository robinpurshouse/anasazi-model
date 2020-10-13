#include <stdio.h>
#include "Location.h"
#include "repast_hpc/AgentId.h"
#include "repast_hpc/SharedDiscreteSpace.h"
#include "repast_hpc/Properties.h"
#include "repast_hpc/Point.h"
#include "repast_hpc/Random.h"
#include <vector>

Location::Location(repast::AgentId FieldID, double soilQual){
	LocationID = FieldID;
	soilQuality = 1 + soilQual;
	isWater = false;
	state = 0;
}

Location::Location(){
	isWater = false;
}

Location::~Location() {}

void Location::setZones(int z, int mz){
	zone = z;
	maizeZone = mz;
}

void Location::setState(int s){
	state = s;
}

//get expected field harvest
int Location::getExpectedYield(){
	return expectedHarvest;
}

//calculate harvest of the field
void Location::calculateYield(int y, double Ha, double gen)
{
	//y is YieldLevel, Ha is Harvest Adjust and q is soil quality
	double baseYield = y * soilQuality * Ha;
	expectedHarvest = baseYield*(1+gen);
}

void Location::checkWater(bool existStreams, bool existAlluvium, int x, int y, int year)
{
	isWater = false;
	for(std::vector<WaterSource>::iterator it = waterSources.begin(); it != waterSources.end(); ++it)
	{
		if(it->waterType == 1)
		{
			if((existAlluvium == 1) && ((zone == 5) or (zone == 4) or (zone == 8) or (zone == 2)))
			{
				isWater = true;
				return;
			}
			else if((existStreams == 1) && (zone == 2))
			{
				isWater = true;
				return;
			}

			//for these locations: (location 72 114) (location 70 113) (location 69 112)	(location 68 111) (location 67 110) (location 66 109) (location 65 108) (location 65 107))
			if (((x==72)&&(y==114))or((x==70)&&(y==113))or((x==69)&&(y==112))or((x==68)&&(y==111))or((x==67)&&(y==110))or((x==66)&&(y==109))or((x==65)&&(y==108))or((x==65)&&(y==107)))
			{
				isWater = true;
				return;
			}
		}
		else if(it->waterType == 2)
		{
			isWater = true;
			return;
		}
		else if(it->waterType == 3)
		{
			if((year >= it->startYear) && (year <= it->endYear))
			{
				isWater = true;
				return;
			}
		}
	}
}

void Location::addWaterSource(int waterType, int startYear, int endYear)
{
	waterSources.push_back({waterType, startYear, endYear});
}
