#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<float.h>

#define CHARMAX 50
#define NOTEAM 5
#define NOMISSION 5

struct rescueTeam{
    int teamID;
    char teamName[CHARMAX];
    int memberCount;
    char vehicleType[CHARMAX];
    int teamX;     // Location track from coordinates
    int teamY;
    int availability;
	int totalMissions;
    int completedMissions;
};

struct rescueMissions{
    int missionID;
    char rescueMission[CHARMAX];
    int teamID;
    int victimX;    // Location track from coordinates
    int victimY;
    int state;

};

void rescueTeamMenu(struct rescueTeam team[], struct rescueMissions mission[], int *count, int *count2);

void addRescueteam(struct rescueTeam team[], int *count ); 
void viewRescueteam(struct rescueTeam team[], int count);
int assignRescueteam(struct rescueMissions mission[], struct rescueTeam team[], int *count2, int *count); 
void trackMission(struct rescueTeam team[], struct rescueMissions mission[], int *count2);
void performanceReport(struct rescueTeam team[], int count); 

char buffer[CHARMAX];

int main () {

    struct rescueTeam team[NOTEAM];
    struct rescueMissions mission[NOMISSION];
    int count = 0, count2 = 0;
    int choice;

    do{

        printf("\n================= RESCUE COORDINATION SYSTEM ==================\n\n");
        printf("1. victim registry \n");
        printf("2. Rescue Teams \n");
        printf("3. Supply Management \n");
        printf("4. Shelter Camps \n");
        printf("5. Incident Reports \n");
        printf("6. Exit \n");

        printf("\nEnter Your Choise : ");
        fgets(buffer, CHARMAX, stdin);
        buffer[strcspn(buffer, "\n")] = '\0';
        choice = atoi(buffer);

        switch(choice) {

            case 1 :
                
                
                break;

            case 2 :
                
                rescueTeamMenu(team, mission, &count, &count2);
                break;

            case 3 :

                 
                break;

            case 4 :

               
                break;

            case 5 :

                   
                break;

            case 6 :

                printf("=========== Exiting Program ========== \n");
                break;

            default :

                printf("Invalid Choice Try Again !\n");
                break;
        }


    } while(choice != 6);

}

void rescueTeamMenu(struct rescueTeam team[], struct rescueMissions mission[], int *count,  int *count2){
	
	int choice2;
	do{
                   

        printf("1. Add Reascue Team \n");
        printf("2. View Reascue Team \n");
		printf("3. Assign Rescue Teams \n");
        printf("4. Track Rescue Missions \n");
		printf("5. Performance Report \n");

        printf("\nEnter Your Choice : ");
        fgets(buffer, CHARMAX, stdin);
        buffer[strcspn(buffer, "\n")] = '\0';
        choice2 = atoi(buffer);

        switch(choice2) {

            case 1 :

                printf("How many teams Do you Want to Add : ");
                fgets(buffer, CHARMAX, stdin);
                buffer[strcspn(buffer, "\n")] = '\0';
                int  n = atoi(buffer);

                for(int i = 0; i < n ; i++) {

                    addRescueteam(team, count);

                }
                break;   

            case 2 : 

				viewRescueteam(team, *count);              
                break;
                        
            case 3 :
                assignRescueteam(mission, team, count2, count);
                break;

            case 4 :
                trackMission(team, mission, count2);
				break;

            case 5 :
				performanceReport(team, *count);
				break;
			
			case 6 :
			
				break;
				
			default :
			
			
				break;
				
		}

	}while(choice2 != 7);
		
}

void addRescueteam(struct rescueTeam team[], int *count ) {
    
    team[*count].teamID = *count;

    printf("Enter Team Name: ");
    fgets(team[*count].teamName, CHARMAX, stdin);
    team[*count].teamName[strcspn(team[*count].teamName, "\n")] = '\0';
    
    printf("Members Count : ");
    fgets(buffer, CHARMAX, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    team[*count].memberCount = atoi(buffer);
    
    printf("Enter Vehicle Type : ");
    fgets(team[*count].vehicleType, CHARMAX, stdin);
    team[*count].vehicleType[strcspn(team[*count].vehicleType, "\n")] = '\0';

    printf("Enter Team X coordinates : ");
    fgets(buffer, CHARMAX, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    team[*count].teamX = atoi(buffer);

    printf("Enter Team Y coordinates : ");
    fgets(buffer, CHARMAX, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    team[*count].teamY = atoi(buffer);
    
    team[*count].availability = 1;
	team[*count].totalMissions = 0;
    team[*count].completedMissions = 0;

    (*count)++;
     


}

void viewRescueteam(struct rescueTeam team[], int count) {

    printf("\n=======RESCUE TEAMS=======\n");

    for(int i = 0; i < count; i++) {

        printf("Team ID = %d \n", team[i].teamID);
        printf("Team Name = %s \n", team[i].teamName);
        printf("Members = %d \n", team[i].memberCount);
        printf("vehicle Type = %s \n", team[i].vehicleType);
        printf("Status = %s \n", team[i].availability ? "Available" : "busy");

    }


}

int assignRescueteam(struct rescueMissions mission[], struct rescueTeam team[], int *count2, int *count) {
    
    mission[*count2].missionID = *count2;

    printf("Enter Mission Type (Search,Rescue,Evacuation) : ");
    fgets(mission[*count2].rescueMission, CHARMAX, stdin);
    mission[*count2].rescueMission[strcspn(mission[*count2].rescueMission, "\n")] = '\0';

    printf("Enter Victim X coordinates : ");
    fgets(buffer, CHARMAX, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    mission[*count2].victimX = atoi(buffer);

    printf("Enter Victim Y coordinates : ");
    fgets(buffer, CHARMAX, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    mission[*count2].victimY = atoi(buffer);

    (*count2)++;

    float distance;
    float minDistance = FLT_MAX;
    int matchTeam = -1;

    for(int i = 0; i < *count; i++){

        float distance = (team[i].teamX - mission[i].victimX) * (team[i].teamX - mission[i].victimX);
        if(distance < minDistance && team[i].availability == 1 ) {
            
            minDistance = distance;
            matchTeam = i;                          // select proper rescue team from distance
    
        } 
        
    }
    if(matchTeam == -1){
    
        printf("No Rescue Team Found \n");
        return 0;
    }
    
    team[matchTeam].availability = 0;

    mission[*count].teamID = matchTeam;
    mission[*count].state = 0;

    printf("Mission Assigned Successfully \n");
    printf("Assigned Team %s", team[matchTeam].teamName);



}


void trackMission(struct rescueTeam team[], struct rescueMissions mission[], int *count2){

    printf("=========Current Rescue Mission Details==========\n");

    for(int i = 0; i < *count2; i++) {

        printf("Mission ID = %d \n", mission[i].missionID);
        printf("Mission Type = %s \n", mission[i].rescueMission);
        printf("Team ID = %d \n", mission[i].teamID);
        printf("Mission State = %s \n", mission[i].state ? "Finished" : "Ongoing");
    }

    int id;

    do{

        printf("Enter Finished Mission ID (-1 for Exit) : ");

        fgets(buffer, CHARMAX, stdin);
        buffer[strcspn(buffer, "\n")] = '\0';
        id = atoi(buffer);

        mission[id].state = 1;
        team[mission[id].teamID].availability = 1;
        team[mission[id].teamID].completedMissions ++;

    }while(id != -1);

}

void performanceReport(struct rescueTeam team[], int count) {


	if(count == 0) {
        printf("No rescue teams registered.\n");
        return;
    }
	
	int bestTeam = 0;
	
	for(int i = 0; i < count; i++) {

        float successRate = 0;

        if(team[i].totalMissions > 0) {
            successRate = ((float)team[i].completedMissions / team[i].totalMissions) * 100;
        }
		
		printf("Team ID = %d\n", team[i].teamID);
        printf("Team Name = %s\n", team[i].teamName);
        printf("Total Missions = %d\n", team[i].totalMissions);
        printf("Completed Missions = %d\n", team[i].completedMissions);
        printf("Success Rate = %.2f%%\n", successRate);

		if(team[i].completedMissions > team[bestTeam].completedMissions) {

            bestTeam = i;
        }
    }

    printf("===== BEST PERFORMING TEAM =====\n");
    printf("Team Name = %s\n", team[bestTeam].teamName);
    printf("Completed Missions = %d\n", team[bestTeam].completedMissions);
    
    for(int i = 0; i < count ; i ++) {

            printf("%s \t|", team[i].teamName);
            for(int j = 0; j < team[i].completedMissions; j++){
                printf("*");
            }
            printf("\n");

    }

}

