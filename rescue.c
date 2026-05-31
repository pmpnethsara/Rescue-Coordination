#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define CHARMAX 50
#define NOTEAM 2

struct rescueTeam{
    int teamID;
    char teamName[CHARMAX];
    int memberCount;
    char vehicleType[CHARMAX];
    int availability;
};

void addRescueteam(struct rescueTeam team[], int *count ); 
void viewRescueteam(struct rescueTeam team[], int count);

char buffer[CHARMAX];

int main () {

    struct rescueTeam team[NOTEAM];

    int count = 0;
    int choice;

    do{

        printf("\n================= RESCUE COORDINATION SYSTEM ==================\n");
        printf("1. victim registry \n");
        printf("2. Rescue Teams \n");
        printf("3. Supply Management \n");
        printf("4. Shelter Camps \n");
        printf("5. Incident Reports \n");
        printf("6. Exit \n");

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


                    }



                }while(choice != 7);
                
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

void addRescueteam(struct rescueTeam team[], int *count ) {
    
    team[*count].teamID = *count;

    printf("Enter Team Name: ");
    fgets(team[*count].teamName, CHARMAX, stdin);
    team[*count].teamName[strcspn(team[*count].teamName, "\n")] = '\0';
    
    printf("Members Count : ");
    fgets(buffer, CHARMAX, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    int noMember = atoi(buffer);
    team[*count].memberCount = noMember;
    
    printf("Enter Vehicle Type : ");
    fgets(team[*count].vehicleType, CHARMAX, stdin);
    team[*count].vehicleType[strcspn(team[*count].vehicleType, "\n")] = '\0';

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
