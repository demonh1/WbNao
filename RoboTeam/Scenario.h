#pragma once
#include "PlayerAction.h"
#include "Constants.h"

enum ScenarioID
{
	S_Default =0,
	S_Rush=1,
	S_FlankAttack=2,
	S_FullDefend=3
};
class Scenario
{
public:
	Scenario(void);
	Scenario(int nID,char *nName);
	~Scenario(void);
	// название сценария
	char *pScenarioName;
	// id сценария
	int ID;
	// действия для всех игроков
	PlayerAction **PAction;
	void displayInfo(void);
};



class Rush: public Scenario
{
public:
	Rush(void);
	~Rush(void);
};

class FlankAttack: public Scenario
{
public:
	FlankAttack(void);
	~FlankAttack(void);
};

class FullDefence: public Scenario
{
	public:
	FullDefence(void);
	~FullDefence(void);
};
