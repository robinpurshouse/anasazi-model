#ifndef LOCATION
#define LOCATION

#include <repast_hpc/AgentId.h>
#include <repast_hpc/SharedDiscreteSpace.h>
#include "Location.h"
#include <vector>

class Location{
private:
	repast::AgentId LocationID;
	
	int state;
	/*
	0 - empty
	1 - household
	2 - field*/
	int zone;
	/*Empty 		- 0
	Natural 		- 1
	Kinbiko 		- 2
	Uplands 		- 3
	North 			- 4
	General 		- 5
	North Dunes - 6
	Mid Dunes 	- 7
	Mid 				- 8*/
	int maizeZone;
	/*Empty 		- 0
		No_Yield 	- 1
		Yield_1		- 2 || North and Mid Valley, Kinbiko Canyon
		Yield_2 	- 3 || General Valley
		Yield_3		- 4 || Arable Uplands
		Sand_dune - 5 || Dunes */
	bool isWater;

	struct WaterSource
	{
		int waterType;
		int startYear;
		int endYear;
		bool isWater;
	};
	std::vector<WaterSource> waterSources;

	//int presentHarvest;
	int expectedHarvest;
	double soilQuality;


public:
	Location(repast::AgentId FieldID, double soilQual);
	Location();
	~Location();

	void setZones(int z, int mz);
	void setState(int s);
	void addWaterSource(int waterType, int startYear, int endYear);

	virtual repast::AgentId& getId() { return LocationID; }
	virtual const repast::AgentId& getId() const { return LocationID; }
	int getZone(){return zone; }
	int getMaizeZone(){return maizeZone; }
	int getExpectedYield();
	bool getWater(){return isWater; }
	int getState(){return state; }

	void checkWater(bool existStreams, bool existAlluvium, int x, int y, int year);
	void calculateYield(int y, double Ha, double gen);
};

#endif
