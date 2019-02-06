/** @file BIL105 Spring 2016 HomeWork 1
*
* A program that simulates a passing game. Desired number
* of passes makes teams to win a round
* and desired number of round wins leads to game win.
* It prints "Team1 won" or, "Team2 won" and it also
* prints every player and passes.
*
* @author
*
* Name:             Yunus Güngör
*
* Student no:       150150701
*
* Date:             02/03/2016
*
* E-Mail:           yunusgnr@gmail.com
*
* Tested on: (My Personal Computer)
*
* Compiler:    GCC 4.9.3.1
*
* IDE:              Code::Blocks 16.01
*
* Operating System: Microsoft Windows 10.0.10586 (10 Pro)
*
* Tested on: (ITU SSH Server)
*
* Compiler:		GCC 4.8.5 20150623
*
* IDE:		None
*
* Operating System: Linux Red Hat 4.8.5-4
*/

#include <stdio.h>
#include <stdlib.h>
int main () {
	srand(17837837); //start random number generator
	int N,S,P,W; //Inputs
	int score1=0,score2=0; //score of the teams
	int player=0, team=0; //player and team number
	int playersTouched=0; //number of players touched the ball
	int temp; //temporary
	int round; //Round Number
	do{
		printf("Enter the number of player in each team \n");
		scanf("%d",&N);
	}while(N<=0);
	do{
		printf("Enter the success rate of passes \n");
		scanf("%d",&P);
	}while(P<=0 || P>100);
	if (N==1)
	{
		//1 player can't pass ball to another player. Whoever gets the ball wins.
		printf("Number of players needed to pass arond has been set to 1\n");
		W=1;
	}
	else
	{
		//Teams has more than 1 player
		do{
			printf("Enter the player number needed to pass around to win a round \n");
			scanf("%d",&W);
		}while(W<1);
	}
	do{
		printf("Enter the score needed to win the game \n");
		scanf("%d",&S);
	}while(S<=0);
	round=1;
	team=(rand()%2); //Give ball to a random team
	printf("Round-1:");
    if(team==0)
    {//Team 1 Gets the ball
		printf("\n  Team 1 selected\n");
    }
    else
    {//Team 2 Gets the ball
		printf("\n  Team 2 selected\n");
    }
	while(score1<S && score2<S)
	{
		//round start
		playersTouched=1;
		player=rand()%N+1; //Give ball to a random player
		printf("    Player%d",player );
		while(((rand()%100)+1)<=P && playersTouched<W)
		/*Player tries to pass and program checks number
		of players who touched the ball, loop goes on until
		reaching desired number of players who passed*/
		{
			//Successful pass
			do{
				/*get random player until player who has the ball and
				player who gets the pass is not same*/
				temp=(rand()%N)+1;
			}
			while(temp==player);
			player=temp;
			printf(" -> Player%d",player);
			playersTouched++;
			//Unsuccessful pass exits loop
		}
		if (playersTouched==W)
		{
			//round is over detect who gets the point
			if (team==0)
			{
			    score1++;
			    printf("\n  Success! New Score of Team1 is %d\n ",score1);
			}
			else
			{
			    score2++;
				printf("\n  Success! New Score of Team2 is %d\n", score2);
			}
			if(score1<S && score2<S) //Blocking extra outputs about round start in the last loop
            {
                team=(rand()%2); // give ball to a random team
                round++;
                printf("\nRound-%d:",round);
                if(team==0)
                {//Team 1 Gets the ball
                    printf("\n  Team 1 selected\n");
                }
                else
                {//Team 2 Gets the ball
                    printf("\n  Team 2 selected\n");
                }
            }
		}
		else
        {
			team=(team+1)%2; //change team
			if(team==0)
            {//Team 1 Gets the ball
                printf("\n  Team 1 captured the ball\n");
            }
            else
            {//Team 2 Gets the ball
                printf("\n  eam 2 captured the ball\n");
            }
        }
	}
	if(score1>score2)
		printf("\nGAME OVER: Team1 reached the target score (%d) and won the game.",score1);
	else
		printf("\nGAME OVER: Team2 reached the target score (%d) and won the game.",score2);
	return 0;
}
