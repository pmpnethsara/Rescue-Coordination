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
    char input[20];

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
                fgets(input,sizeof(input),stdin);
                sscanf(input,"%d",&ss.flocations);

                printf("\n\n");

                printf("Enter total number of shelter Camps\n");
                fgets(input,sizeof(input),stdin);
                sscanf(input,"%d",&ss.fCamps);

                printf("\n\n");

                printf("Enter number of victims\n");
                fgets(input,sizeof(input),stdin);
                sscanf(input,"%d",&ss.fVictims);

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

//Shelter Camps
int location(struct sCamps ss){

    char places[ss.flocations][20];
    int locId[ss.flocations];

    for(int j=0;j<ss.flocations;++j){
        printf("Location no %d is ",j+1);
        fgets(places[j],20,stdin);
        places[j][strcspn(places[j],"\n")] = '\0';
        locId[j]=1000+j;
    }

    printf("\n\n");

    camps(places,ss.flocations,ss);

    return 0;
}

int camps(char locations[][20],int size,struct sCamps ss){

    int numOfCamps[size];
    int campID[ss.fCamps];
    char input[20];

    for(int i=0;i<ss.flocations;++i){

        printf("Enter number of camps in %s :",locations[i]);

        fgets(input,sizeof(input),stdin);
        sscanf(input,"%d",&numOfCamps[i]);

        printf("\n\n");

        if(ss.fCamps<numOfCamps[i]){
            numOfCamps[i]=0;
            break;
        }
    }

    for(int j=0;j<ss.fCamps;++j){
        campID[j]=10+j;
    }

    for(int m=0;m<ss.fCamps;++m){
        printf("Camp ID for camp no %d is %d\n",m+1,campID[m]);
    }

    printf("\n\n");

    capacity(campID,ss.fCamps,ss);

    return 0;
}

int capacity(int camp[],int size,struct sCamps ss){

    ss.fCapacity=0;
    int capacities[ss.fCamps];
    int spc;
    char input[20];

    printf("Enter capacities of each camp\n");

    for(int i=0;i<ss.fCamps;++i){

        printf("Capacity of camp id %d is ",camp[i]);

        fgets(input,sizeof(input),stdin);
        sscanf(input,"%d",&capacities[i]);

        printf("\n");

        ss.fCapacity+=capacities[i];
    }

    printf("\n\n");

    if(ss.fVictims>ss.fCapacity)
        printf("**Occupy more camps\n");

    printf("Is there victims with special necessities?\n");
    printf("Enter 1 if yes, enter 0 if not: ");

    fgets(input,sizeof(input),stdin);
    sscanf(input,"%d",&spc);

    printf("\n\n");

    if(spc==1)
        special();

    availability(ss,camp,ss.fCamps,capacities,ss.fCamps);

    return 0;
}

int special(){

    int ntype;
    char input[20];

    printf("Enter 1 for parental necessities:\n");
    printf("Enter 2 for medical necessities:\n");
    printf("Enter 3 for elderly necessities:\n");

    fgets(input,sizeof(input),stdin);
    sscanf(input,"%d",&ntype);

    printf("\n");

    switch(ntype){

        case 1:
            printf("Send to maternal area\n");
            break;

        case 2:
            printf("Send to medical area\n");
            break;

        case 3:
            printf("Send to elder care area\n");
            break;

        default:
            printf("Service can not be provided\n");
    }

    printf("\n");

    return 0;
}


int availability(struct sCamps ss,int campIDs[],int cSize,int campCap[],int space){

    int avaSpace;

    for(int i=0;i<3;++i){
        for(int j=0;j<40;++j){
            printf("*");
        }
        printf("\n");
    }

    for(int k=0;k<10;++k){
        printf(" ");
    }

    printf("Camp Details\n\n");

    printf("Camp ID");

    for(int k=0;k<15;++k){
        printf(" ");
    }

    printf("Availability\n\n");

    for(int a=0;a<ss.fCamps;++a){

        printf("%d",campIDs[a]);

        for(int k=0;k<20;++k){
            printf(" ");
        }

        if(ss.fVictims!=0){

            if(ss.fVictims>campCap[a]){
                printf("NOT Available");
                ss.fVictims-=campCap[a];
            }
            else{

                avaSpace=campCap[a]-ss.fVictims;

                if(ss.fVictims==0)
                    printf("NOT Available");
                else
                    printf("%d spaces available",avaSpace);

                ss.fVictims=0;
            }
        }
        else{
            printf("Available");
        }

        printf("\n");
    }

    printf("\n");

    for(int i=0;i<3;++i){
        for(int j=0;j<40;++j){
            printf("*");
        }
        printf("\n");
    }

    return 0;
}
























