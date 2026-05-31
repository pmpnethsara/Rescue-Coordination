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
    int teamX;
    int teamY;
    int availability;
};

struct rescueMissions{
    int missionID;
    char rescueMission[CHARMAX];
    int proirityLevel;
    int victimX;    // Location track from coordinates
    int victimY;


};

struct sCamps{
    int flocations;
    int fCamps;
    int fVictims;
    int fCapacity;
    int campX;
    int campY;
};

void addRescueteam(struct rescueTeam team[], int *count ); 
void viewRescueteam(struct rescueTeam team[], int count);
int assignRescueteam(struct rescueMissions mission[], struct rescueTeam team[], int *count22, int *count); 

int location(struct sCamps ss);
int camps(char locations[][20],int size,struct sCamps ss);
int capacity(int camp[],int size,struct sCamps ss);
int special();
int availability(struct sCamps ss,int campIDs[],int cSize,int campCap[],int space);

char buffer[CHARMAX];

int main () {

    struct rescueTeam team[NOTEAM];
    struct rescueMissions mission[NOMISSION];
    struct sCamps ss;
    int count = 0, count2 = 0;
    int choice;

    do{

        printf("\n================= RESCUE COORDINATION SYSTEM ==================\n");
        printf("1. victim registry \n");
        printf("2. Rescue Teams \n");
        printf("3. Supply Management \n");
        printf("4. Shelter Camps \n");
        printf("5. Incident Reports \n");
        printf("6. Exit \n\n");

        printf("Enter Your Choise : ");
        fgets(buffer, CHARMAX, stdin);
        buffer[strcspn(buffer, "\n")] = '\0';
        choice = atoi(buffer);

        switch(choice) {

            case 1 :
                
                
                break;

            case 2 :
                do{
                   

                    printf("1. Add Reascue Team : \n");
                    printf("2. View Reascue Team : \n");
                    printf("3. Assign Rescue Teams : \n");
                       
                    printf("Enter Your Choice : ");
                    fgets(buffer, CHARMAX, stdin);
                    buffer[strcspn(buffer, "\n")] = '\0';
                    int choice2 = atoi(buffer);

                    switch(choice2) {

                        case 1 :

                            printf("How many teams Do you Want to Add : ");
                            fgets(buffer, CHARMAX, stdin);
                            buffer[strcspn(buffer, "\n")] = '\0';
                            int  n = atoi(buffer);

                            for(int i = 0; i < n ; i++) {

                                addRescueteam(team, &count);

                            }
                            break;   

                        case 2 : 

                            viewRescueteam(team, count);              
                            break;
                        
                        case 3 :
                            assignRescueteam(mission, team, &count2, &count);
                            break;

                    }



                }while(choice != 7);
                
                break;

            case 3 :

                 
                break;

            case 4 :
                
                for(int i=1;i<=20;++i){
                      printf("-");
                }

                printf("Shelter Camps");

                for(int j=1;j<=20;++j){
                       printf("-");
                 }

                printf("\n");

                for(int k=1;k<=53;++k){
                         printf("-");
                 }
 
                 printf("\n\n");

                 printf("Enter total number of locations\n");
                 scanf("%d",&ss.flocations);

                 printf("\n\n");

                 printf("Enter total number of shelter Camps\n");
                 scanf("%d",&ss.fCamps);

                 printf("\n\n");

                 printf("Enter number of victims\n");
                 scanf("%d",&ss.fVictims);

                printf("\n\n");

                location(ss);
               
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
    
    printf("Enter Mission Type (Search,Rescue,Evacuation) : ");
    fgets(mission[*count2].rescueMission, CHARMAX, stdin);
    mission[*count2].rescueMission[strcspn(mission[*count2].rescueMission, "\n")] = '\0';
    
    printf("Enter Priority Level (1-5) : ");
    fgets(buffer, CHARMAX, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    mission[*count2].proirityLevel = atoi(buffer);

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

    printf("Mission Assigned Successfully \n");
    printf("Assigned Team %s", team[matchTeam].teamName);



}
