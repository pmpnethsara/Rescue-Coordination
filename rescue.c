
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<float.h>

#define CHARMAX 100
#define TEAMS 50
#define MAX_ITEMS 100
#define MAX_SPECIALS 50

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
    int teamX;
    int teamY;
    int availability;
    int totalMissions;
    int completedMissions;
};

struct supply {
    int supply_id;
    char main_category[50];
    char sub_category[30];
    char item_name[20];
    double quantity;
    double low_limit;
};


struct specialrequest {
    char item_name[50];
    int target_camp_id;
};

struct campSystem{
    int totalLocations;
    int totalCamps;
    int totalVictims;

};

struct cLocation{
     char locName[1000][20];
     int locID[1000];
     int numOfCampLoc[1000];

};

struct sCamps{
     int campID[1000];
     int campCap[1000];
     int fullCap;
};

struct campVictim{
     int vicID[1000];
     int assignedCamp[1000];

};

struct campSpecial{
     int spcvicID[1000];
     int needType;
};


struct Incident {
    int inc_id;
    char type[50];
    int severity;
    char location[100];
    int incX;
    int incY;
    int resolved;
    int teamID;
};

struct Victim victims[100];
int victimCount = 0;

struct supply list[MAX_ITEMS];
int item_count = 0;
int next_id = 1;

struct specialrequest special_list[MAX_SPECIALS];
int special_count = 0;

struct Incident missions[50];
int incCount = 0;

char buffer[CHARMAX];

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

void rescueTeamMenu(struct rescueTeam team[], struct Incident missions[], int *count, int incCount);
void addRescueteam(struct rescueTeam team[], int *count);
void viewallRescueteam(struct rescueTeam team[], int count);
void searchRescueByIdOrName(struct rescueTeam team[]);
void assignRescueteam(struct Incident missions[], struct rescueTeam team[], int count);
void performanceReport(struct rescueTeam team[], int count);
void searchRescueID(struct rescueTeam team[]);
void searchRescueName(struct rescueTeam team[]);
void trackRescueTeam(struct rescueTeam team[], struct Incident missions[], int targetID);
void addDefaultTeams(struct rescueTeam team[], int *count);

void addfood();
void viewallitems();
void checklowstock();
void distributeTocamp();
void addspecial();
void viewspecial();
double getfixedLimits(char name[]);

int location(struct campSystem aa);
int camps(struct campSystem aa,char campLocname[][20],int rows);
int victim(struct campSystem aa,struct sCamps cc);
int special();
int availability(struct campSystem aa,struct sCamps cc);

void logIncident();
void displayAllmissions();
void searchIncidentByID();
void resolveIncident(struct rescueTeam team[]);
void displayHighSeverity();
void displaySeverityGraph();
void printSeverityLabel(int severity);
void incidentMenu(struct rescueTeam team[]);

int main() {
    struct rescueTeam team[TEAMS];
    struct campSystem aa;
    int count = 0;
    int choice;
    int choise;
    char input[20];
    
    addDefaultTeams(team, &count);

    do {
        printf("\n================= RESCUE COORDINATION SYSTEM ==================\n");
        printf("\n1. Log New Mission\n");
        printf("2. Victim Registry\n");
        printf("3. Rescue Teams\n");
        printf("4. Supply Management\n");
        printf("5. Shelter Camps\n");
        printf("6. Incident Reports\n");
        printf("7. Exit\n\n");
        printf("Enter Your Choice: ");
        
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

            case 3:
                rescueTeamMenu(team, missions, &count, incCount);
                break;

            case 4:
                do {
                    printf("\n___SUPPLY MANAGEMENT SYSTEM___\n\n");
                    printf("1. Add Food Supplies\n");
                    printf("2. View All Items & ID\n");
                    printf("3. View Low Stock Items\n");
                    printf("4. Distribute Supplies To Camp\n");
                    printf("5. Add Special Needed Items\n");
                    printf("6. View Special Request List\n");
                    printf("7. Back to Main Menu\n");
                    printf("Enter your Choice: ");
                    
                    fgets(buffer, CHARMAX, stdin);
                    buffer[strcspn(buffer, "\n")] = '\0';
                    choise = atoi(buffer);

                    switch(choise) {
                        case 1:
                            addfood();
                            break;
                        case 2:
                            viewallitems();
                            break;
                        case 3:
                            checklowstock();
                            break;
                        case 4:
                            distributeTocamp();
                            break;
                        case 5:
                            addspecial();
                            break;
                        case 6:
                            viewspecial();
                            break;
                        case 7:
                            printf("\nReturning to Main Menu\n");
                            break;
                        default:
                            printf("\nInvalid Choice! Please Enter Valid Number.\n");
                    }
                } while(choise != 7);
                break;

            case 5:
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
                    scanf("%d",&aa.totalLocations);

                    printf("\n\n");

                    printf("Enter total number of shelter Camps\n");
                    scanf("%d",&aa.totalCamps);

                    printf("\n\n");

                    printf("Enter number of victims\n");
                    scanf("%d",&aa.totalVictims);

                    printf("\n\n");

                    location(aa);
                break;

            case 6:
                printf("====================================\n");
                printf(" DISASTER RELIEF & RESCUE SYSTEM\n");
                printf("====================================\n");
                incidentMenu(team);
                break;

            case 7:
                printf("=========== Exiting Program ==========\n");
                break;

            default:
                printf("Invalid Choice Try Again!\n");
                break;
        }
    } while(choice != 7);

    return 0;
}

void incidentMenu(struct rescueTeam team[]) {
    int choice;

    do {
        printf("\n========================================\n");
        printf("       INCIDENT REPORTS MODULE\n");
        printf("========================================\n");
        printf("  1. View All Missions\n");
        printf("  2. Search Mission by ID\n");
        printf("  3. Mission Status\n");
        printf("  4. View Critical Active missions\n");
        printf("  5. View Severity Graph\n");
        printf("  0. Back to main menu\n");
        printf("========================================\n");
        printf("Enter your choice: ");
        
        fgets(buffer, CHARMAX, stdin);
        buffer[strcspn(buffer, "\n")] = '\0';
        choice = atoi(buffer);

        switch(choice) {
            case 1:
                displayAllmissions();
                break;
            case 2:
                searchIncidentByID();
                break;
            case 3:
                resolveIncident(team);
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
                printf("Invalid choice. Please enter a number between 0 and 5.\n");
        }
    } while(choice != 0);
}

void logIncident() {
    if(incCount >= 50) {
        printf("Error: Maximum incident capacity (50) reached.\n");
        return;
    }

    printf("\n--- LOG NEW INCIDENT ---\n");
    missions[incCount].inc_id = 101 + incCount;

    while(1) {
        printf("Enter Mission Type (Search, Rescue, Evacuation): ");
        fgets(missions[incCount].type, 50, stdin);
        missions[incCount].type[strcspn(missions[incCount].type, "\n")] = '\0';
        
        if(strcasecmp(missions[incCount].type, "Search") != 0 && 
           strcasecmp(missions[incCount].type, "Rescue") != 0 &&
           strcasecmp(missions[incCount].type, "Evacuation") != 0) {
            printf("Invalid mission type!\n");
        } else {
            break;
        }
    }

    printf("Enter severity (1 = Low, 2 = Medium, 3 = High): ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    missions[incCount].severity = atoi(buffer);

    while(missions[incCount].severity < 1 || missions[incCount].severity > 3) {
        printf("Invalid severity. Please enter 1, 2, or 3: ");
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = '\0';
        missions[incCount].severity = atoi(buffer);
    }

    printf("Enter location: ");
    fgets(missions[incCount].location, 100, stdin);
    missions[incCount].location[strcspn(missions[incCount].location, "\n")] = '\0';

    missions[incCount].resolved = 0;
    missions[incCount].teamID = -1;

    printf("Enter incident X coordinates: ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    missions[incCount].incX = atoi(buffer);

    printf("Enter incident Y coordinates: ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    missions[incCount].incY = atoi(buffer);

    printf("\nIncident #%d logged successfully.\n", missions[incCount].inc_id);
    incCount++;
}

void displayAllmissions() {
    printf("\n--- ALL MISSIONS ---\n");

    if(incCount == 0) {
        printf("No missions have been logged yet.\n");
        return;
    }

    printf("%-6s %-20s %-10s %-25s %-10s\n", "ID", "Type", "Severity", "Location", "Status");
    printf("----------------------------------------------------------------------\n");

    for(int i = 0; i < incCount; i++) {
        printf("%-6d %-20s ", missions[i].inc_id, missions[i].type);
        printSeverityLabel(missions[i].severity);
        printf("      %-25s ", missions[i].location);
        
        if(missions[i].resolved == 0) {
            printf("ACTIVE\n");
        } else {
            printf("RESOLVED\n");
        }
    }

    printf("----------------------------------------------------------------------\n");
    printf("Total missions: %d\n", incCount);
}

void searchIncidentByID() {
    printf("\n--- SEARCH INCIDENT BY ID ---\n");

    int searchID;
    printf("Enter incident ID to search: ");
    fgets(buffer, CHARMAX, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    searchID = atoi(buffer);

    int found = 0;

    for(int i = 0; i < incCount; i++) {
        if(missions[i].inc_id == searchID) {
            printf("\n--- INCIDENT FOUND ---\n");
            printf("ID       : %d\n", missions[i].inc_id);
            printf("Type     : %s\n", missions[i].type);
            printf("Severity : ");
            printSeverityLabel(missions[i].severity);
            printf("\n");
            printf("Location : %s\n", missions[i].location);
            printf("Status   : %s\n", missions[i].resolved == 0 ? "ACTIVE" : "RESOLVED");
            found = 1;
            break;
        }
    }

    if(found == 0) {
        printf("Incident with ID %d not found.\n", searchID);
    }
}

void resolveIncident(struct rescueTeam team[]) {
    printf("\n--- MARK INCIDENT AS RESOLVED ---\n");

    int targetID;
    printf("Enter incident ID to mark as resolved: ");
    fgets(buffer, CHARMAX, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    targetID = atoi(buffer);

    int found = 0;

    for(int i = 0; i < incCount; i++) {
        if(missions[i].inc_id == targetID) {
            if(missions[i].resolved == 1) {
                printf("Incident #%d is already marked as resolved.\n", targetID);
            } else {
                missions[i].resolved = 1;
                printf("Incident #%d has been marked as RESOLVED.\n", targetID);
            }

            trackRescueTeam(team, missions, targetID);
            found = 1;
            break;
        }
    }

    if(found == 0) {
        printf("Incident with ID %d not found.\n", targetID);
    }
}

void displayHighSeverity() {
    printf("\n--- CRITICAL ACTIVE MISSIONS (Severity: HIGH) ---\n");

    int found = 0;

    for(int i = 0; i < incCount; i++) {
        if(missions[i].severity == 3 && missions[i].resolved == 0) {
            printf("ID: %-4d | Type: %-20s | Location: %s\n",
                   missions[i].inc_id, missions[i].type, missions[i].location);
            found = 1;
        }
    }

    if(found == 0) {
        printf("No critical active missions at this time.\n");
    }
}

void displaySeverityGraph() {
    printf("\n--- CITY DANGER RISK CHART ---\n");

    if(incCount == 0) {
        printf("No missions logged yet. Add some missions first.\n");
        return;
    }

    char cityNames[50][100];
    int cityScore[50];
    int cityCount = 0;

    for(int i = 0; i < incCount; i++) {
        int alreadySeen = 0;

        for(int j = 0; j < cityCount; j++) {
            if(strcmp(missions[i].location, cityNames[j]) == 0) {
                cityScore[j] += missions[i].severity;
                alreadySeen = 1;
                break;
            }
        }

        if(alreadySeen == 0) {
            strcpy(cityNames[cityCount], missions[i].location);
            cityScore[cityCount] = missions[i].severity;
            cityCount++;
        }
    }

    int cityRisk[50];
    int citymissions[50];

    for(int i = 0; i < cityCount; i++) {
        citymissions[i] = 0;

        for(int j = 0; j < incCount; j++) {
            if(strcmp(missions[j].location, cityNames[i]) == 0) {
                citymissions[i]++;
            }
        }

        int maxPossible = 3 * citymissions[i];
        cityRisk[i] = (cityScore[i] * 100) / maxPossible;
    }

    int chartHeight = 10;

    printf("\n");
    printf("  100%% |  (Each # = 10%% risk)\n");

    for(int row = chartHeight; row >= 1; row--) {
        if(row * 10 == 100) {
            printf("       |");
        } else {
            printf("  %3d%% |", row * 10);
        }

        for(int i = 0; i < cityCount; i++) {
            if(cityRisk[i] >= row * 10) {
                printf("  # ");
            } else {
                printf("    ");
            }
        }
        printf("\n");
    }

    printf("    0%% +");
    for(int i = 0; i < cityCount; i++) {
        printf("----");
    }
    printf("\n");

    printf("         ");
    for(int i = 0; i < cityCount; i++) {
        printf("%-4.4s", cityNames[i]);
    }
    printf("\n");

    printf("         ");
    for(int i = 0; i < cityCount; i++) {
        printf("%3d%%", cityRisk[i]);
    }
    printf("\n");

    printf("\n  --- RISK LEVEL KEY ---\n");
    printf("  0%%  - 33%%  : LOW RISK    (mostly minor missions)\n");
    printf("  34%% - 66%%  : MEDIUM RISK (mixed severity)\n");
    printf("  67%% - 99%%  : HIGH RISK   (mostly serious missions)\n");
    printf("  100%%        : CRITICAL    (all missions are HIGH severity!)\n");

    printf("\n  --- CITY SUMMARY ---\n");
    for(int i = 0; i < cityCount; i++) {
        printf("  %-20s | Score: %2d | Missions: %2d | Risk: %3d%%",
               cityNames[i], cityScore[i], citymissions[i], cityRisk[i]);

        if(cityRisk[i] == 100) {
            printf(" [!! CRITICAL !!]\n");
        } else if(cityRisk[i] >= 67) {
            printf(" [HIGH RISK]\n");
        } else if(cityRisk[i] >= 34) {
            printf(" [MEDIUM RISK]\n");
        } else {
            printf(" [LOW RISK]\n");
        }
    }
}

void printSeverityLabel(int severity) {
    if(severity == 1) {
        printf("LOW   ");
    } else if(severity == 2) {
        printf("MEDIUM");
    } else if(severity == 3) {
        printf("HIGH  ");
    } else {
        printf("UNKNOWN");
    }
}

void inputAge(int *age) {
    while(1) {
        printf("Enter Age: ");
        fgets(buffer, CHARMAX, stdin);
        buffer[strcspn(buffer, "\n")] = '\0';
        *age = atoi(buffer);

        if(*age <= 0 || *age > 120) {
            printf("Invalid age! Please enter a value between 1 and 120.\n");
        } else {
            break;
        }
    }
}

void inputGender(char *gender) {
    while(1) {
        printf("Enter Gender (Male/Female): ");
        fgets(buffer, CHARMAX, stdin);
        buffer[strcspn(buffer, "\n")] = '\0';
        strncpy(gender, buffer, 10);

        if(strcasecmp(gender, "Male") == 0 || strcasecmp(gender, "Female") == 0) {
            break;
        } else {
            printf("Invalid gender! Please enter Male or Female.\n");
        }
    }
}

void inputStatus(char *status) {
    while(1) {
        printf("Enter Status (Displaced/Sheltered/Rescued): ");
        fgets(buffer, CHARMAX, stdin);
        buffer[strcspn(buffer, "\n")] = '\0';
        strncpy(status, buffer, 20);

        if(strcasecmp(status, "Displaced") == 0 || 
           strcasecmp(status, "Sheltered") == 0 || 
           strcasecmp(status, "Rescued") == 0) {
            break;
        } else {
            printf("Invalid status! Please enter Displaced, Sheltered, or Rescued.\n");
        }
    }
}

void registerVictim() {
    if(victimCount >= 100) {
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
    
    if(strlen(buffer) == 0) {
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
    if(victimCount == 0) {
        printf("\nNo victims registered yet.\n");
        return;
    }

    printf("\n--- All Registered Victims ---\n");
    printf("%-5s %-20s %-5s %-10s %-15s %-15s %-20s %-15s\n",
           "ID", "Name", "Age", "Gender", "Status", "Location", "Injury", "Contact");
    printf("----------------------------------------------------------------------------------------------------------\n");

    for(int i = 0; i < victimCount; i++) {
        printf("%-5d %-20s %-5d %-10s %-15s %-15s %-20s %-15s\n",
               victims[i].id, victims[i].name, victims[i].age,
               victims[i].gender, victims[i].status, victims[i].location,
               victims[i].injury, victims[i].contact);
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

    for(int i = 0; i < victimCount; i++) {
        if(victims[i].id == searchId) {
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

    if(!found) {
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

    for(int i = 0; i < victimCount; i++) {
        if((strcasecmp(victims[i].name, searchKeyword) == 0) ||
           (strcasecmp(victims[i].gender, searchKeyword) == 0) ||
           (strcasecmp(victims[i].status, searchKeyword) == 0) ||
           (strcasecmp(victims[i].location, searchKeyword) == 0)) {
            printf("%-5d %-20s %-5d %-10s %-15s %-15s %-20s %-15s\n",
                   victims[i].id, victims[i].name, victims[i].age,
                   victims[i].gender, victims[i].status, victims[i].location,
                   victims[i].injury, victims[i].contact);
            found++;
        }
    }

    printf("----------------------------------------------------------------------------------------------------------\n");
    printf("Records found : %d\n", found);

    if(!found) {
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

    for(int i = 0; i < victimCount; i++) {
        if(victims[i].id == searchId) {
            printf("Current Status: %s\n", victims[i].status);
            inputStatus(victims[i].status);
            printf("Status updated successfully!\n");
            found = 1;
            break;
        }
    }

    if(!found) {
        printf("Victim with ID %d not found.\n", searchId);
    }
}

void displayVictimSummary() {
    int displaced = 0, sheltered = 0, rescued = 0;

    for(int i = 0; i < victimCount; i++) {
        if(strcasecmp(victims[i].status, "Displaced") == 0)
            displaced++;
        else if(strcasecmp(victims[i].status, "Sheltered") == 0)
            sheltered++;
        else if(strcasecmp(victims[i].status, "Rescued") == 0)
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

        switch(choiceReg) {
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
    } while(choiceReg != 0);
}

void rescueTeamMenu(struct rescueTeam team[], struct Incident missions[], int *count, int incCount) {
    int choice2;
    
    do {
        printf("\n=========== Rescue Team Management ==========\n");
        printf("\n1. Add Rescue Team\n");
        printf("2. View Rescue Team\n");
        printf("3. Search Rescue Team by Team ID or Team Name\n");
        printf("4. Assign Rescue Teams\n");
        printf("5. Performance Report\n");
        printf("6. Back to Main Menu\n");
        printf("\nEnter Your Choice: ");
        
        fgets(buffer, CHARMAX, stdin);
        buffer[strcspn(buffer, "\n")] = '\0';
        choice2 = atoi(buffer);

        switch(choice2) {
            case 1:
                addRescueteam(team, count);
                break;
            case 2:
                viewallRescueteam(team, *count);
                break;
            case 3:
                searchRescueByIdOrName(team);
                break;
            case 4:
                assignRescueteam(missions, team, *count);
                break;
            case 5:
                performanceReport(team, *count);
                break;
            case 6:
                printf("=========== Back to Main Menu ==========\n");
                break;
            default:
                printf("Invalid Choice Try Again!\n");
                break;
        }
    } while(choice2 != 6);
}

void addRescueteam(struct rescueTeam team[], int *count) {
    if(*count >= TEAMS) {
        printf("Maximum rescue team limit reached!\n");
        return;
    }

    team[*count].teamID = *count + 1;

    printf("Enter Team Name: ");
    fgets(team[*count].teamName, CHARMAX, stdin);
    team[*count].teamName[strcspn(team[*count].teamName, "\n")] = '\0';

    while(1) {
        printf("Members Count (1 - 50): ");
        fgets(buffer, CHARMAX, stdin);
        buffer[strcspn(buffer, "\n")] = '\0';
        team[*count].memberCount = atoi(buffer);

        if(team[*count].memberCount <= 0 || team[*count].memberCount > 50) {
            printf("Invalid member count! Enter between 1 and 50.\n");
        } else {
            break;
        }
    }

    printf("Enter Vehicle Type: ");
    fgets(team[*count].vehicleType, CHARMAX, stdin);
    team[*count].vehicleType[strcspn(team[*count].vehicleType, "\n")] = '\0';

    printf("Enter Team X coordinates: ");
    fgets(buffer, CHARMAX, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    team[*count].teamX = atoi(buffer);

    printf("Enter Team Y coordinates: ");
    fgets(buffer, CHARMAX, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    team[*count].teamY = atoi(buffer);

    team[*count].availability = 1;
    team[*count].totalMissions = 0;
    team[*count].completedMissions = 0;

    printf("\nRescue Team Added Successfully!\n");
    printf("Team ID = %d\n", team[*count].teamID);

    (*count)++;
}

void viewallRescueteam(struct rescueTeam team[], int count) {
    struct rescueTeam *ptr;

    printf("\n======= RESCUE TEAMS =======\n");

    for(int i = 0; i < count; i++) {
        ptr = &team[i];

        printf("Team ID       = %d\n", ptr->teamID);
        printf("Team Name     = %s\n", ptr->teamName);
        printf("Members       = %d\n", ptr->memberCount);
        printf("Vehicle Type  = %s\n", ptr->vehicleType);
        printf("Status        = %s\n", ptr->availability ? "Available" : "Busy");
        printf("----------------------------\n");
    }
}

void assignRescueteam(struct Incident missions[], struct rescueTeam team[], int count) {
    if(incCount == 0) {
        printf("No missions available!\n");
        return;
    }

    int missionID;
    int missionIndex = -1;

    printf("\n===== ACTIVE MISSIONS =====\n");

    for(int i = 0; i < incCount; i++) {
        if(missions[i].resolved == 0) {
            printf("Mission ID: %d | Type: %s | Location: %s\n", 
                   missions[i].inc_id, missions[i].type, missions[i].location);
        }
    }

    while(1) {
        printf("\nEnter Mission ID to assign a rescue team: ");
        fgets(buffer, CHARMAX, stdin);
        buffer[strcspn(buffer, "\n")] = '\0';
        missionID = atoi(buffer);

        for(int i = 0; i < incCount; i++) {
            if(missions[i].inc_id == missionID && missions[i].resolved == 0) {
                missionIndex = i;
                break;
            }
        }

        if(missionIndex != -1) {
            break;
        }

        printf("Invalid Mission ID! Try Again.\n");
    }

    float minDistance = FLT_MAX;
    int matchTeam = -1;

    for(int i = 0; i < count; i++) {
        if(team[i].availability == 1) {
            float distance = 
                ((team[i].teamX - missions[missionIndex].incX) * 
                 (team[i].teamX - missions[missionIndex].incX)) + 
                ((team[i].teamY - missions[missionIndex].incY) * 
                 (team[i].teamY - missions[missionIndex].incY));

            if(distance < minDistance) {
                minDistance = distance;
                matchTeam = i;
            }
        }
    }

    if(matchTeam == -1) {
        printf("No Available Rescue Team Found!\n");
        return;
    }

    team[matchTeam].availability = 0;
    team[matchTeam].totalMissions++;
    missions[missionIndex].teamID = team[matchTeam].teamID;

    printf("\nMission Assigned Successfully!\n");
    printf("Assigned Team : %s\n", team[matchTeam].teamName);
    printf("Team ID       : %d\n", team[matchTeam].teamID);
}

void trackRescueTeam(struct rescueTeam team[], struct Incident missions[], int targetID) {
    for(int i = 0; i < incCount; i++) {
        if(missions[i].inc_id == targetID) {
            int assignedTeam = missions[i].teamID;

            if(assignedTeam != -1 && assignedTeam > 0 && assignedTeam <= TEAMS) {
                team[assignedTeam - 1].availability = 1;
                team[assignedTeam - 1].completedMissions++;
                missions[i].teamID = -1;
                printf("Rescue Team Released Successfully!\n");
            }
            break;
        }
    }
}

void searchRescueByIdOrName(struct rescueTeam team[]) {
    int choice;

    do {
        printf("1. Search Rescue Team By ID\n");
        printf("2. Search Rescue Team By Name\n");
        printf("3. Back To Main Menu\n\n");
        printf("Enter Choice: ");
        
        fgets(buffer, CHARMAX, stdin);
        buffer[strcspn(buffer, "\n")] = '\0';
        choice = atoi(buffer);

        switch(choice) {
            case 1:
                searchRescueID(team);
                break;
            case 2:
                searchRescueName(team);
                break;
            case 3:
                printf("Back to Main Menu\n");
                break;
            default:
                printf("Invalid Choice Try Again!\n");
        }
    } while(choice != 3);
}

void searchRescueID(struct rescueTeam team[]) {
    int id;
    int found = 0;

    printf("Enter Team ID: ");
    fgets(buffer, CHARMAX, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    id = atoi(buffer);

    for(int i = 0; i < TEAMS; i++) {
        if(team[i].teamID == id) {
            printf("\nTeam Found!\n");
            printf("Team ID       : %d\n", team[i].teamID);
            printf("Team Name     : %s\n", team[i].teamName);
            printf("Members       : %d\n", team[i].memberCount);
            printf("Vehicle       : %s\n", team[i].vehicleType);
            found = 1;
            break;
        }
    }

    if(found == 0) {
        printf("Team Not Found!\n");
    }
}

void searchRescueName(struct rescueTeam team[]) {
    char searchName[CHARMAX];
    int found = 0;

    printf("Enter Rescue Team Name: ");
    fgets(searchName, CHARMAX, stdin);
    searchName[strcspn(searchName, "\n")] = '\0';

    for(int i = 0; i < TEAMS; i++) {
        if(strlen(team[i].teamName) == 0) {
            continue;
        }

        if(strcasecmp(team[i].teamName, searchName) == 0) {
            printf("\n===== Rescue Team Found =====\n");
            printf("Team ID       : %d\n", team[i].teamID);
            printf("Team Name     : %s\n", team[i].teamName);
            printf("Members       : %d\n", team[i].memberCount);
            printf("Vehicle Type  : %s\n", team[i].vehicleType);
            printf("Coordinates   : (%d, %d)\n", team[i].teamX, team[i].teamY);
            printf("Availability  : %s\n", team[i].availability ? "Available" : "Busy");
            found = 1;
            break;
        }
    }

    if(found == 0) {
        printf("No Rescue Team Found!\n");
    }
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
        printf("----------------------------\n");

        if(team[i].completedMissions > team[bestTeam].completedMissions) {
            bestTeam = i;
        }
    }

    printf("===== BEST PERFORMING TEAM =====\n\n");
    printf("Team Name = %s\n", team[bestTeam].teamName);
    printf("Completed Missions = %d\n\n", team[bestTeam].completedMissions);

    printf("===== Team Performance Bar Chart =====\n\n");

    for(int i = 0; i < count; i++) {
        printf("%s\t|", team[i].teamName);
        for(int j = 0; j < team[i].completedMissions; j++) {
            printf("*");
        }
        printf("\n");
    }
}

void addDefaultTeams(struct rescueTeam team[], int *count) {
    team[*count].teamID = *count + 1;
    strcpy(team[*count].teamName, "Shark Rescue");
    team[*count].memberCount = 8;
    strcpy(team[*count].vehicleType, "Boat");
    team[*count].teamX = 10;
    team[*count].teamY = 15;
    team[*count].availability = 1;
    team[*count].totalMissions = 8;
    team[*count].completedMissions = 5;
    (*count)++;

    team[*count].teamID = *count + 1;
    strcpy(team[*count].teamName, "Mora Team");
    team[*count].memberCount = 6;
    strcpy(team[*count].vehicleType, "Ambulance");
    team[*count].teamX = 20;
    team[*count].teamY = 25;
    team[*count].availability = 1;
    team[*count].totalMissions = 5;
    team[*count].completedMissions = 2;
    (*count)++;

    team[*count].teamID = *count + 1;
    strcpy(team[*count].teamName, "Rapid Response");
    team[*count].memberCount = 10;
    strcpy(team[*count].vehicleType, "Helicopter");
    team[*count].teamX = 30;
    team[*count].teamY = 40;
    team[*count].availability = 1;
    team[*count].totalMissions = 1;
    team[*count].completedMissions = 1;
    (*count)++;
}

void addfood() {
    char main_name[20];
    char sub_name[20];
    int main_ch, item_ch;
    double input_qut;

    printf("Add Food Supplies\n");
    printf("1. Baby Foods\n2. Adults Foods\n");
    printf("Enter the Number: ");
    
    fgets(buffer, CHARMAX, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    main_ch = atoi(buffer);

    switch(main_ch) {
        case 1:
            strcpy(main_name, "Baby Food");
            printf("Select Baby Food\n1. Milk Powder\n2. Biscuits\n3. Other\n");
            printf("Enter Choice (1-3): ");
            
            fgets(buffer, CHARMAX, stdin);
            buffer[strcspn(buffer, "\n")] = '\0';
            item_ch = atoi(buffer);

            switch(item_ch) {
                case 1:
                    strcpy(sub_name, "Milk Powder");
                    break;
                case 2:
                    strcpy(sub_name, "Biscuit");
                    break;
                default:
                    printf("Enter Custom Baby Food Name: ");
                    fgets(sub_name, sizeof(sub_name), stdin);
                    sub_name[strcspn(sub_name, "\n")] = '\0';
                    break;
            }
            break;
            
        case 2:
            strcpy(main_name, "Adult Food");
            printf("\nSelect Adult Food:\n1. Rice\n2. Dhal\n3. Sugar\n4. Coconut\n5. Other\n");
            printf("Enter choice (1-5): ");
            
            fgets(buffer, CHARMAX, stdin);
            buffer[strcspn(buffer, "\n")] = '\0';
            item_ch = atoi(buffer);

            switch(item_ch) {
                case 1:
                    strcpy(sub_name, "Rice");
                    break;
                case 2:
                    strcpy(sub_name, "Dhal");
                    break;
                case 3:
                    strcpy(sub_name, "Sugar");
                    break;
                case 4:
                    strcpy(sub_name, "Coconut");
                    break;
                default:
                    printf("Enter Custom Adult Food Name: ");
                    fgets(sub_name, sizeof(sub_name), stdin);
                    sub_name[strcspn(sub_name, "\n")] = '\0';
                    break;
            }
            break;
            
        default:
            printf("Invalid Category Choice! Please enter 1 or 2.\n");
            return;
    }

    printf("Enter Quantity: ");
    fgets(buffer, CHARMAX, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    input_qut = atof(buffer);

    for(int i = 0; i < item_count; i++) {
        if(strcmp(list[i].item_name, sub_name) == 0) {
            list[i].quantity += input_qut;
            printf("\n[UPDATE] '%s' already exists (ID: %d). Updated stock! New Total: %.2f\n",
                   list[i].item_name, list[i].supply_id, list[i].quantity);
            return;
        }
    }

    if(item_count >= MAX_ITEMS) {
        printf("\n[ERROR] Inventory is full!\n");
        return;
    }

    struct supply item;
    item.supply_id = next_id++;
    strcpy(item.main_category, "Food");
    strcpy(item.sub_category, main_name);
    strcpy(item.item_name, sub_name);
    item.quantity = input_qut;
    item.low_limit = getfixedLimits(item.item_name);

    list[item_count] = item;
    item_count++;

    printf("\n[SUCCESS] New Food Item added! ID: %d | Name: %s | Qty: %.2f\n", 
           item.supply_id, item.item_name, item.quantity);
}

void viewallitems() {
    if(item_count == 0) {
        printf("\n[INFO] Inventory is empty! No items registered yet.\n");
        return;
    }

    printf("\n___CURRENT WAREHOUSE INVENTORY LIST___\n");
    for(int i = 0; i < item_count; i++) {
        printf("Item ID: %d | Name: %-25s | Category: %-20s | Stock: %.2f\n",
               list[i].supply_id, list[i].item_name, list[i].sub_category, list[i].quantity);
    }
}

void checklowstock() {
    if(item_count == 0) {
        printf("\n[INFO] Inventory is empty! No items to check.\n");
        return;
    }

    int has_low_stock = 0;
    printf("\n___ITEMS THAT HAVE REACHED MINIMUM LIMIT___\n");

    for(int i = 0; i < item_count; i++) {
        if(list[i].quantity <= list[i].low_limit) {
            has_low_stock = 1;
            printf("ID: %d | Item: %-20s | Current Qty: %-8.2f | Fixed Limit: %.2f [CRITICAL]\n",
                   list[i].supply_id, list[i].item_name, list[i].quantity, list[i].low_limit);
        }
    }

    if(!has_low_stock) {
        printf("All items have sufficient stock. No items below the minimum limit.\n");
    }
}

void distributeTocamp() {
    if(item_count == 0) {
        printf("\n[INFO] Inventory is empty! No items available to distribute.\n");
        return;
    }

    int search_id, found = 0, camp_id;
    double req_quantity;

    printf("\n___DISTRIBUTE SUPPLIES TO CAMP___\n");
    printf("Enter Supply ID to distribute: ");
    
    fgets(buffer, CHARMAX, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    search_id = atoi(buffer);

    for(int i = 0; i < item_count; i++) {
        if(list[i].supply_id == search_id) {
            found = 1;
            printf("Item Found: %s (%s) | Available Stock: %.2f\n", 
                   list[i].item_name, list[i].main_category, list[i].quantity);

            printf("Enter Destination Camp ID: ");
            fgets(buffer, CHARMAX, stdin);
            buffer[strcspn(buffer, "\n")] = '\0';
            camp_id = atoi(buffer);

            printf("Enter Quantity to Send: ");
            fgets(buffer, CHARMAX, stdin);
            buffer[strcspn(buffer, "\n")] = '\0';
            req_quantity = atof(buffer);

            if(req_quantity > list[i].quantity) {
                printf("\n[ERROR] Not enough stock available!\n");
            } else {
                list[i].quantity -= req_quantity;
                printf("\n[SUCCESS] Sent %.2f of %s to Camp %d successfully.\n", 
                       req_quantity, list[i].item_name, camp_id);
                printf("Remaining Stock for %s: %.2f\n", list[i].item_name, list[i].quantity);

                if(list[i].quantity <= list[i].low_limit) {
                    printf("[ALERT] Warning! %s stock has reached or dropped below its minimum limit (%.2f)!\n", 
                           list[i].item_name, list[i].low_limit);
                }
            }
            break;
        }
    }

    if(!found) {
        printf("\n[ERROR] Supply ID not found!\n");
    }
}

void addspecial() {
    if(special_count >= MAX_SPECIALS) {
        printf("\n[ERROR] Special Request List is full!\n");
        return;
    }

    struct specialrequest req;

    printf("\n__ADD SPECIAL NEEDED ITEM (FUTURE REQUEST)__\n");
    printf("Enter Special Item Name: ");
    fgets(req.item_name, sizeof(req.item_name), stdin);
    req.item_name[strcspn(req.item_name, "\n")] = '\0';

    printf("Enter Target Camp ID: ");
    fgets(buffer, CHARMAX, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    req.target_camp_id = atoi(buffer);

    special_list[special_count] = req;
    special_count++;

    printf("\n[SUCCESS] Special request for '%s' saved successfully!\n", req.item_name);
}

void viewspecial() {
    if(special_count == 0) {
        printf("\n[INFO] No special requested items at the moment.\n");
        return;
    }

    printf("\n__SPECIAL REQUEST LIST (FUTURE PROCUREMENT)__\n");
    for(int i = 0; i < special_count; i++) {
        printf("%d) Item Name: %-25s | Target Camp ID: %02d\n",
               i + 1, special_list[i].item_name, special_list[i].target_camp_id);
    }
}

double getfixedLimits(char name[]) {
    if(strcmp(name, "Rice") == 0) return 250.0;
    if(strcmp(name, "Dhal") == 0) return 100.0;
    if(strcmp(name, "Sugar") == 0) return 50.0;
    if(strcmp(name, "Coconut") == 0) return 200.0;
    if(strcmp(name, "Milk Powder") == 0) return 20.0;
    if(strcmp(name, "Biscuit") == 0) return 25.0;
    return 15.0;
}

//shelter camps

int location(struct campSystem aa){
    struct cLocation bb;
    int ch;



    printf("Enter camp name or location name\n\n");

     for(int j=0;j<aa.totalLocations;++j){
        while((ch=getchar())!='\n' && ch!=EOF);
        printf("Camp no %d is ",j+1);
        fgets(bb.locName[j],20,stdin);
        bb.locName[j][strcspn(bb.locName[j],"\n")]='\0';
        bb.locID[j]=1000+j;
        printf("Enter number of camps for camp no/location %d :",j+1);
        scanf("%d",&bb.numOfCampLoc[j]);
        printf("\n");
    }

    printf("\n\n");

    camps(aa,bb.locName,1000);

    return 0;
}

int camps(struct campSystem aa,char campLocname[][20],int rows){

    int campID[1000];
    struct sCamps cc;

      for(int i=0;i<aa.totalCamps;++i){
          printf("Enter full capacity in %s :",campLocname[i]);
          scanf("%d",&cc.campCap[i]);
          cc.fullCap+=cc.campCap[i];
          printf("\n");

      }

      if(aa.totalVictims>cc.fullCap)
          printf("**Occupy more camps\n");

      for(int j=0;j<aa.totalCamps;++j){
           cc.campID[j]=10+j;
      }

      for(int m=0;m<aa.totalCamps;++m){
         printf("Camp ID for camp no %d is %d\n",m+1,cc.campID[m]);
      }

      printf("\n\n");

      victim(aa,cc);

      return 0;

}

int victim(struct campSystem aa,struct sCamps cc){

    struct campVictim dd;
    int spc=0,n=1,m=0;

    for(int j=0;j<aa.totalVictims;++j){
           dd.vicID[j]=100+j;
      }

    for(int i=0;i<3;++i){
        for(int j=0;j<40;++j){
           printf("*") ;
        }
        printf("\n");
    }

    for(int k=0;k<10;++k){
        printf(" ");
    }

    printf("Assigning victims to camps\n\n");

    printf("Victim ID");

    for(int k=0;k<15;++k){
        printf(" ");
    }

    printf("Camp ID\n\n");

    for(int a=0;a<aa.totalVictims;++a){
        printf("%d",dd.vicID[a]);

        for(int k=0;k<20;++k){
            printf(" ");
        }

        if(n<=cc.campCap[m]){
            printf("%d",cc.campID[m]);
            n+=1;
        }else{
           m+=1;
           n=2;
           printf("%d",cc.campID[m]);
        }

        printf("\n");
    }

    printf("\n");

    for(int i=0;i<3;++i){
        for(int j=0;j<40;++j){
           printf("*") ;
        }
        printf("\n");
    }

    printf("\n\n");

    printf("Is there victims with special necessities?\n");
    printf("Enter 1 if yes, enter 0 if not: ");
    scanf("%d",&spc);

     printf("\n\n");

     if(spc==1){
        special();
     }


     availability(aa,cc);

    return 0;

}

int special(){
    int val=1,n=0;
    struct campSpecial ee;

    while(val==1){

          printf("Enter Victim IDs of victims with special care :");
          scanf("%d",&ee.spcvicID[n]);
        if(ee.spcvicID[n]>=100){
          printf("Enter 1 for parental necessities:\n");
          printf("Enter 2 for medical necessities:\n");
          printf("Enter 3 for elderly necessities:\n");
          printf("Enter 0 for none:\n");
          scanf("%d",&ee.needType);

          printf("\n");

          switch(ee.needType){

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

        }else{
            printf("Invalid ID\n");
        }

           printf("\nEnter 1 if there any other victims who need special care :");
           scanf("%d",&val);

           printf("\n");

           n+=1;
    }

    return 0;

}

int availability(struct campSystem aa,struct sCamps cc){
    int avaSpace;

    for(int i=0;i<3;++i){
        for(int j=0;j<40;++j){
           printf("*") ;
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

    for(int a=0;a<aa.totalCamps;++a){
        printf("%d",cc.campID[a]);

        for(int k=0;k<20;++k){
            printf(" ");
        }
      if(aa.totalVictims!=0){
        if(aa.totalVictims>cc.campCap[a]){
            printf("NOT Available");
            aa.totalVictims-=cc.campCap[a];
        }else{
            avaSpace=cc.campCap[a]-aa.totalVictims;
            if(aa.totalVictims==0)
                printf("NOT Available");
            else
                printf("%d spaces available",avaSpace);
            aa.totalVictims=0;
        }
      }else{
          printf("Available");
      }

        printf("\n");
    }

    printf("\n");

    for(int i=0;i<3;++i){
        for(int j=0;j<40;++j){
           printf("*") ;
        }
        printf("\n");
    }

    return 0;
}
