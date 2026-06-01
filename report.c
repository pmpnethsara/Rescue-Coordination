#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<float.h>

#define CHARMAX 100
#define NOTEAM 5
#define NOMISSION 5

struct Incident {
    int inc_id;
    char type[50];
    int severity;
    char location[100];
    int resolved;
};

struct Incident incidents[50];
int incCount = 0;

void logIncident();
void displayAllIncidents();
void searchIncidentByID();
void resolveIncident();
void displayHighSeverity();
void displaySeverityGraph();
void printSeverityLabel(int severity);

void incidentMenu() {
    int choice;



    do {

        printf("\n========================================\n");
        printf("       INCIDENT REPORTS MODULE\n");
        printf("========================================\n");
        printf("  1. View All Missions\n");
        printf("  2. Search Mission by ID\n");
        printf("  3. Mission Status\n");
        printf("  4. View Critical Active Incidents\n");
        printf("  5. View Severity Graph\n");
        printf("  0. Back to main menu\n");
        printf("========================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);


        switch (choice) {
           
            case 1:
                displayAllIncidents();
                break;
            case 2:
                searchIncidentByID();
                break;
            case 3:
                resolveIncident();
                break;
            case 4:
                displayHighSeverity();
                break;
            case 5:
                displaySeverityGraph();
                break;
            case 0:
                printf("Returning to main menu...\n");
                break;
            default:

                printf("Invalid choice. Please enter a number between 0 and 6.\n");
        }

    } while (choice != 0);
}

void logIncident() {


    if (incCount >= 50) {
        printf("Error: Maximum incident capacity (50) reached.\n");
        return;
    }



    printf("\n--- LOG NEW INCIDENT ---\n");


    incidents[incCount].inc_id = 101 + incCount;

while(1){
    printf("Enter Mission Type (e.g. Search, Rescue, Evacuation): ");
    fgets(incidents[incCount].type,50,stdin);
    incidents[incCount].type[strcspn(incidents[incCount].type,"\n")] = '\0';
    if (strcasecmp(incidents[incCount].type,"Search") != 0 && strcasecmp(incidents[incCount].type,"Rescue") != 0 &&
    strcasecmp(incidents[incCount].type,"Evacuation") != 0){
        printf("Invalid mission type! \n");
    }
    else{
        break;
    }
}

    printf("Enter severity (1 = Low, 2 = Medium, 3 = High): ");
    scanf("%d", &incidents[incCount].severity);


    while (incidents[incCount].severity < 1 || incidents[incCount].severity > 3) {
        printf("Invalid severity. Please enter 1, 2, or 3: ");
        scanf("%d", &incidents[incCount].severity);

    }


    printf("Enter location: ");
    scanf(" %[^\n]", incidents[incCount].location);


    incidents[incCount].resolved = 0;


    printf("\nIncident #%d logged successfully.\n", incidents[incCount].inc_id);


    incCount++;

}

void displayAllIncidents() {

    printf("\n--- ALL INCIDENTS ---\n");


    if (incCount == 0) {
        printf("No incidents have been logged yet.\n");
        return;
    }


    printf("%-6s %-20s %-10s %-25s %-10s\n",
           "ID", "Type", "Severity", "Location", "Status");
    printf("----------------------------------------------------------------------\n");




    int i;
    for (i = 0; i < incCount; i++) {

        printf("%-6d %-20s ", incidents[i].inc_id, incidents[i].type);


        printSeverityLabel(incidents[i].severity);
        printf("      ");


        printf("%-25s ", incidents[i].location);


        if (incidents[i].resolved == 0) {
            printf("ACTIVE\n");
        } else {
            printf("RESOLVED\n");
        }
    }

    printf("----------------------------------------------------------------------\n");
    printf("Total incidents: %d\n", incCount);
}

void searchIncidentByID() {

    printf("\n--- SEARCH INCIDENT BY ID ---\n");

    int searchID;
    printf("Enter incident ID to search: ");
    scanf("%d", &searchID);

    int found = 0;
    int i;


    for (i = 0; i < incCount; i++) {


        if (incidents[i].inc_id == searchID) {


            printf("\n--- INCIDENT FOUND ---\n");
            printf("ID       : %d\n", incidents[i].inc_id);
            printf("Type     : %s\n", incidents[i].type);
            printf("Severity : ");
            printSeverityLabel(incidents[i].severity);
            printf("\n");
            printf("Location : %s\n", incidents[i].location);
            printf("Status   : %s\n", incidents[i].resolved == 0 ? "ACTIVE" : "RESOLVED");



            found = 1;
            break;
        }
    }


    if (found == 0) {
        printf("Incident with ID %d not found.\n", searchID);
    }
}

void resolveIncident() {

    printf("\n--- MARK INCIDENT AS RESOLVED ---\n");

    int targetID;
    printf("Enter incident ID to mark as resolved: ");
    scanf("%d", &targetID);

    int found = 0;
    int i;

    for (i = 0; i < incCount; i++) {

        if (incidents[i].inc_id == targetID) {


            if (incidents[i].resolved == 1) {
                printf("Incident #%d is already marked as resolved.\n", targetID);
            } else {

                incidents[i].resolved = 1;
                printf("Incident #%d has been marked as RESOLVED.\n", targetID);
            }

            found = 1;
            break;
        }
    }

    if (found == 0) {
        printf("Incident with ID %d not found.\n", targetID);
    }
}

void displayHighSeverity() {

    printf("\n--- CRITICAL ACTIVE INCIDENTS (Severity: HIGH) ---\n");

    int found = 0;
    int i;

    for (i = 0; i < incCount; i++) {


        if (incidents[i].severity == 3 && incidents[i].resolved == 0) {


            printf("ID: %-4d | Type: %-20s | Location: %s\n",
                   incidents[i].inc_id,
                   incidents[i].type,
                   incidents[i].location);

            found = 1;
        }
    }


    if (found == 0) {
        printf("No critical active incidents at this time.\n");
    }
}

void displaySeverityGraph() {

    printf("\n--- CITY DANGER RISK CHART ---\n");


    if (incCount == 0) {
        printf("No incidents logged yet. Add some incidents first.\n");
        return;
    }

    char cityNames[50][100];
    int cityScore[50];
    int cityCount = 0;

    int i, j;


    for (i = 0; i < incCount; i++) {

        int alreadySeen = 0;


        for (j = 0; j < cityCount; j++) {


            if (strcmp(incidents[i].location, cityNames[j]) == 0) {


                cityScore[j] += incidents[i].severity;


                alreadySeen = 1;
                break;
            }
        }


        if (alreadySeen == 0) {


            strcpy(cityNames[cityCount], incidents[i].location);



            cityScore[cityCount] = incidents[i].severity;

            cityCount++;
        }
    }

    int cityRisk[50];
    int cityIncidents[50];


    for (i = 0; i < cityCount; i++) {
        cityIncidents[i] = 0;

        for (j = 0; j < incCount; j++) {

            if (strcmp(incidents[j].location, cityNames[i]) == 0) {
                cityIncidents[i]++;
            }
        }


        int maxPossible = 3 * cityIncidents[i];




        cityRisk[i] = (cityScore[i] * 100) / maxPossible;
    }

    int chartHeight = 10;

    printf("\n");
    printf("  100%% |  (Each # = 10%% risk)\n");



    int row;
    for (row = chartHeight; row >= 1; row--) {



        if (row * 10 == 100) {
            printf("       |");
        } else {
            printf("  %3d%% |", row * 10);


        }


        for (i = 0; i < cityCount; i++) {




            if (cityRisk[i] >= row * 10) {
                printf("  # ");
            } else {
                printf("    ");
            }
        }

        printf("\n");
    }

    printf("    0%% +");
    for (i = 0; i < cityCount; i++) {
        printf("----");
    }
    printf("\n");


    printf("         ");
    for (i = 0; i < cityCount; i++) {


        printf("%-4.4s", cityNames[i]);
    }
    printf("\n");


    printf("         ");
    for (i = 0; i < cityCount; i++) {
        printf("%3d%%", cityRisk[i]);
    }
    printf("\n");






    printf("\n  --- RISK LEVEL KEY ---\n");
    printf("  0%%  - 33%%  : LOW RISK    (mostly minor incidents)\n");
    printf("  34%% - 66%%  : MEDIUM RISK (mixed severity)\n");
    printf("  67%% - 99%%  : HIGH RISK   (mostly serious incidents)\n");
    printf("  100%%        : CRITICAL    (all incidents are HIGH severity!)\n");


    printf("\n  --- CITY SUMMARY ---\n");
    for (i = 0; i < cityCount; i++) {
        printf("  %-20s | Score: %2d | Incidents: %2d | Risk: %3d%%",
               cityNames[i],
               cityScore[i],
               cityIncidents[i],
               cityRisk[i]);


        if (cityRisk[i] == 100) {
            printf(" [!! CRITICAL !!]\n");
        } else if (cityRisk[i] >= 67) {
            printf(" [HIGH RISK]\n");
        } else if (cityRisk[i] >= 34) {
            printf(" [MEDIUM RISK]\n");
        } else {
            printf(" [LOW RISK]\n");
        }
    }
}

void printSeverityLabel(int severity) {
    if (severity == 1) {
        printf("LOW   ");
    } else if (severity == 2) {
        printf("MEDIUM");
    } else if (severity == 3) {
        printf("HIGH  ");
    } else {
        printf("UNKNOWN");
    }
}


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
        printf("1. Log New Mission\n");
        printf("2. Victim Registry \n");
        printf("3. Rescue Teams \n");
        printf("4. Supply Management \n");
        printf("5. Shelter Camps \n");
        printf("6. Incident Reports \n");
        printf("7. Exit \n\n");

        printf("Enter Your Choice : ");
        fgets(buffer, CHARMAX, stdin);
        buffer[strcspn(buffer, "\n")] = '\0';
        choice = atoi(buffer);

        switch(choice) {

            case 1: 
            
                logIncident();
                break;

            case 2:

                victimRegistryMenu();                
				
                break;

            case 3 :
			
                rescueTeamMenu(team, mission, &count, &count2);
                
                break;

            case 4 :

                 
                break;

            case 5 :
                
            

              printf("======================= Shelter Camps ======================\n");
              printf("============================================================\n");
              

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

            case 6 :
                printf("====================================\n");
                printf(" DISASTER RELIEF & RESCUE SYSTEM\n");
                printf("====================================\n");
                incidentMenu();
                break;

            case 7 :

                printf("=========== Exiting Program ========== \n");
                break;

            default :

                printf("Invalid Choice Try Again !\n");
                break;
        }


    } while(choice != 7);

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

        printf("Team ID       = %d \n", team[i].teamID);
        printf("Team Name     = %s \n", team[i].teamName);
        printf("Members       = %d \n", team[i].memberCount);
        printf("vehicle Type  = %s \n", team[i].vehicleType);
        printf("Status        = %s \n", team[i].availability ? "Available" : "busy");

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

        printf("Mission ID        = %d \n", mission[i].missionID);
        printf("Mission Type      = %s \n", mission[i].rescueMission);
        printf("Team ID           = %d \n", mission[i].teamID);
        printf("Mission State     = %s \n", mission[i].state ? "Finished" : "Ongoing");
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
		
		printf("Team ID              = %d\n", team[i].teamID);
        printf("Team Name            = %s\n", team[i].teamName);
        printf("Total Missions       = %d\n", team[i].totalMissions);
        printf("Completed Missions   = %d\n", team[i].completedMissions);
        printf("Success Rate         = %.2f%%\n", successRate);

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
