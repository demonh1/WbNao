#include <cstdio>
#include "Scenario.h"

Scenario::Scenario(void)
{
	PAction=new PlayerAction*[Players_in_team];
	ID=S_Default;
	pScenarioName = "Default Empty";
}

Scenario::~Scenario(void)
{
	delete PAction;
}


Scenario::Scenario(int nID,char *nName)
{
	PAction=new PlayerAction*[Players_in_team];
	this->pScenarioName=nName;
	this->ID=nID;
	
}


Rush::Rush():Scenario(S_Rush,"Rush")
{
	
}

Rush::~Rush()
{

}

FlankAttack::FlankAttack():Scenario(S_FlankAttack,"Flank Attack")
{
	
}

FlankAttack::~FlankAttack()
{
}
FullDefence::FullDefence():Scenario(S_FullDefend,"Full Defence")
{

}

FullDefence::~FullDefence()
{

}
void Scenario::displayInfo(void)
{
	printf("ID=%i\n",this->ID);
	char ch = pScenarioName[0];
	int count = 0;
	while(ch != '\0' || ch != NULL)
	{
		printf("%c",this->pScenarioName[count++]);
		ch = pScenarioName[count];
	}
	printf("\n");
}
