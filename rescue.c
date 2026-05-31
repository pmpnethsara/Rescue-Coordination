#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<float.h>

#define CHARMAX 50
#define NOTEAM 5
#define NOMISSION 5

struct Victim {
    int id;
    char name[50];
    int age;
    char gender[10];
    char injury[100];
    char status[20];
    char location[50];
    char contact[15];
};

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

struct sCamps{
    int flocations;
    int fCamps;
    int fVictims;
    int fCapacity;
    int campX;
    int campY;
};

struct Victim victims[100];
int victimCount = 0;
void victimRegistryMenu();
void registerVictim();
void displayAllVictims();
void searchVictimByID();
void searchVictimByKeyword();
void updateVictimStatus();
void displayVictimSummary();
void inputAge(int *age);
void inputGender(char *gender);
void inputStatus(char *status);


void rescueTeamMenu(struct rescueTeam team[], struct rescueMissions mission[], int *count, int *count2);


void addRescueteam(struct rescueTeam team[], int *count ); 
void viewRescueteam(struct rescueTeam team[], int count);
int assignRescueteam(struct rescueMissions mission[], struct rescueTeam team[], int *count2, int *count); 
void trackMission(struct rescueTeam team[], struct rescueMissions mission[], int *count2);
void performanceReport(struct rescueTeam team[], int count); 

int location(struct sCamps ss);
int camps(char locations[][20],int size,struct sCamps ss);
int capacity(int camp[],int size,struct sCamps ss);
int special();
int availability(struct sCamps ss,int campIDs[],int cSize,int campCap[],int space);

char buffer[CHARMAX];

//--------------------

struct sCamps{
    int flocations;
    int fCamps;
    int fVictims;
    int fCapacity;
    int campX;
    int campY;
};
 
int location(struct sCamps ss);
int camps(char locations[][20],int size,struct sCamps ss);
int capacity(int camp[],int size,struct sCamps ss);
int special();
int availability(struct sCamps ss,int campIDs[],int cSize,int campCap[],int space);



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

                victimRegistryMenu();                
				
                break;

            case 2 :
			
                rescueTeamMenu(team, mission, &count, &count2);
                
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

void inputAge(int *age) {
    while (1) {
        printf("Enter Age: ");
        fgets(buffer, CHARMAX, stdin);
        buffer[strcspn(buffer, "\n")] = '\0';
        *age = atoi(buffer);

        if (*age <= 0 || *age > 120) {
            printf("Invalid age! Please enter a value between 1 and 120.\n");
        } else {
            break;
        }
    }
}

void inputGender(char *gender) {
    while (1) {
        printf("Enter Gender (Male/Female): ");
        fgets(buffer, CHARMAX, stdin);
        buffer[strcspn(buffer, "\n")] = '\0';
        strncpy(gender, buffer, 10);

        if (strcasecmp(gender, "Male") == 0 || strcasecmp(gender, "Female") == 0) {
            break;
        } else {
            printf("Invalid gender! Please enter Male or Female.\n");
        }
    }
}

void inputStatus(char *status) {
    while (1) {
        printf("Enter Status (Displaced/Sheltered/Rescued): ");
        fgets(buffer, CHARMAX, stdin);
        buffer[strcspn(buffer, "\n")] = '\0';
        strncpy(status, buffer, 20);

        if (strcasecmp(status, "Displaced") == 0 || strcasecmp(status, "Sheltered") == 0 || strcasecmp(status, "Rescued") == 0) {
            break;
        } else {
            printf("Invalid status! Please enter Displaced, Sheltered, or Rescued.\n");
        }
    }
}


void registerVictim() {
    if (victimCount >= 100) {
        printf("Victim registry is full!\n");
        return;
    }

    struct Victim v;
    v.id = victimCount + 1;

    printf("\n--- Register New Victim ---\n");

    printf("Enter Name: ");
    fgets(buffer, CHARMAX, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    strncpy(v.name, buffer, 50);

    inputAge(&v.age);

    inputGender(v.gender);

    printf("Enter Injury Description: ");
    fgets(buffer, 100, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    strncpy(v.injury, buffer, 100);

    printf("Enter Last Known Location: ");
    fgets(buffer, CHARMAX, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    strncpy(v.location, buffer, 50);

    printf("Enter Contact Number (or press Enter if none): ");
    fgets(buffer, CHARMAX, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    if (strlen(buffer) == 0) {
        strncpy(v.contact, "N/A", 15);
    } else {
        strncpy(v.contact, buffer, 15);
    }

    inputStatus(v.status);

    victims[victimCount] = v;
    victimCount++;

    printf("\nVictim registered successfully! ID: %d\n", v.id);
}

void displayAllVictims() {
    if (victimCount == 0) {
        printf("\nNo victims registered yet.\n");
        return;
    }

    printf("\n--- All Registered Victims ---\n");
    printf("%-5s %-20s %-5s %-10s %-15s %-15s %-20s %-15s\n",
           "ID", "Name", "Age", "Gender", "Status", "Location", "Injury", "Contact");
    printf("----------------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < victimCount; i++) {
        printf("%-5d %-20s %-5d %-10s %-15s %-15s %-20s %-15s\n",
               victims[i].id,
               victims[i].name,
               victims[i].age,
               victims[i].gender,
               victims[i].status,
               victims[i].location,
               victims[i].injury,
               victims[i].contact);
    }
}

void searchVictimByID() {
    int searchId;
    int found = 0;

    printf("\nEnter Victim ID to search: ");
    fgets(buffer, CHARMAX, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    searchId = atoi(buffer);

    printf("\n--- Search Results ---\n");

    for (int i = 0; i < victimCount; i++) {
        if (victims[i].id == searchId) {
            printf("ID       : %d\n", victims[i].id);
            printf("Name     : %s\n", victims[i].name);
            printf("Age      : %d\n", victims[i].age);
            printf("Gender   : %s\n", victims[i].gender);
            printf("Injury   : %s\n", victims[i].injury);
            printf("Status   : %s\n", victims[i].status);
            printf("Location : %s\n", victims[i].location);
            printf("Contact  : %s\n", victims[i].contact);
            printf("------------------------------\n");
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("No victim found with ID: %d\n", searchId);
    }
}

void searchVictimByKeyword() {
    char searchKeyword[50];
    int found = 0;

    printf("\nEnter keyword to search (Name / Gender / Status / Location): ");
    fgets(buffer, CHARMAX, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    strncpy(searchKeyword, buffer, 50);

    printf("\n--- Search Results ---\n");
    printf("%-5s %-20s %-5s %-10s %-15s %-15s %-20s %-15s\n",
           "ID", "Name", "Age", "Gender", "Status", "Location", "Injury", "Contact");
    printf("----------------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < victimCount; i++) {
        if ((strcasecmp(victims[i].name, searchKeyword) == 0) ||
            (strcasecmp(victims[i].gender, searchKeyword) == 0) ||
            (strcasecmp(victims[i].status, searchKeyword) == 0) ||
            (strcasecmp(victims[i].location, searchKeyword) == 0)) {
            printf("%-5d %-20s %-5d %-10s %-15s %-15s %-20s %-15s\n",
               victims[i].id,
               victims[i].name,
               victims[i].age,
               victims[i].gender,
               victims[i].status,
               victims[i].location,
               victims[i].injury,
               victims[i].contact);
            found++;
        }
    }

    printf("----------------------------------------------------------------------------------------------------------\n");
    printf("Records found : %d\n", found);

    if (!found) {
        printf("No victim found with keyword: %s\n", searchKeyword);
    }
}

void updateVictimStatus() {
    int searchId;
    int found = 0;

    printf("\nEnter Victim ID to update status: ");
    fgets(buffer, CHARMAX, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    searchId = atoi(buffer);

    for (int i = 0; i < victimCount; i++) {
        if (victims[i].id == searchId) {
            printf("Current Status: %s\n", victims[i].status);
            inputStatus(victims[i].status);
            printf("Status updated successfully!\n");
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Victim with ID %d not found.\n", searchId);
    }
}

void displayVictimSummary() {
    int displaced = 0, sheltered = 0, rescued = 0;

    for (int i = 0; i < victimCount; i++) {
        if (strcasecmp(victims[i].status, "Displaced") == 0)
            displaced++;
        else if (strcasecmp(victims[i].status, "Sheltered") == 0)
            sheltered++;
        else if (strcasecmp(victims[i].status, "Rescued") == 0)
            rescued++;
    }

    printf("\n--- Victim Registry Summary ---\n");
    printf("Total Registered : %d\n", victimCount);
    printf("Displaced        : %d\n", displaced);
    printf("Sheltered        : %d\n", sheltered);
    printf("Rescued          : %d\n", rescued);
}

void victimRegistryMenu() {
    int choiceReg;

    do {
        printf("\n========== Victim Registry ==========\n");
        printf("1. Register New Victim\n");
        printf("2. Display All Victims\n");
        printf("3. Search Victim by ID\n");
        printf("4. Search Victim by Keyword\n");
        printf("5. Update Victim Status\n");
        printf("6. View Summary\n");
        printf("0. Back to Main Menu\n");
        printf("=====================================\n");
        printf("Enter choice: ");

        fgets(buffer, CHARMAX, stdin);
        buffer[strcspn(buffer, "\n")] = '\0';
        choiceReg = atoi(buffer);

        switch (choiceReg) {
            case 1: 
                registerVictim();        
                break;
            case 2: 
                displayAllVictims();     
                break;
            case 3: 
                searchVictimByID();      
                break;
            case 4: 
                searchVictimByKeyword(); 
                break;
            case 5: 
                updateVictimStatus();    
                break;
            case 6: 
                displayVictimSummary();  
                break;
            case 0: 
                printf("Returning to main menu...\n"); 
                break;
            default: 
                printf("Invalid choice! Try again.\n");
        }

    } while (choiceReg != 0);
}

// Rescue Team
void rescueTeamMenu(struct rescueTeam team[], struct rescueMissions mission[], int *count,  int *count2){
	
	int choice2;
	do{
                   

        printf("\n1. Add Reascue Team \n");
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
				printf("=========== Back to Main Menu ========== \n");
				break;
				
			default :
			
				printf("Invalid Choice Try Again !\n");
				break;
				
		}

	}while(choice2 != 6);
		
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






















