/*
 main test
*/

#include <cstdio>
#include "WorldInfo.h"


int main(int argc, const char* argv[])
{
	WorldInfo  *pWI = new WorldInfo();
	for(int i=0; i< Players_in_team; i++)
	{
		pWI->pAllyState[i] = new PlayerState(new MyPoint(0.0f+0.2f*i,0.0f));
		printf("player #%i, Distance to frame ",i);
		printf("%f\n",pWI->pAllyState[i]->PlayerPosition->distance2DTo(new MyPoint(3.0f,0.0f)));
		/*std:: cout << "player " << i <<  "Distance to frame " 
		<< pWI->AllyState[i]->PlayerPosition->distance2DTo(new MyPoint(3.0f,0.0f)) << std:: endl;*/	
		
	}
	pWI->pBallPosition = new MyPoint(0.0f,0.0f);
	printf("Scenario By Score\n");
	pWI->chooseScenarioByScore();
	printf("Scenario By Position\n");
	pWI->chooseScenarioByAllyPosition();
	
        delete pWI;

	return 0;
}

