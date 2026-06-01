# 1 "report.c"


#include <stdio.h>
#include <string.h>
# 13 "report.c"
struct Incident {
    int inc_id;
    char type[50];
    int severity;
    char location[100];
    int resolved;
};
# 28 "report.c"
struct Incident incidents[50];
int incCount = 0;
# 38 "report.c"
void logIncident();
void displayAllIncidents();
void searchIncidentByID();
void resolveIncident();
void displayHighSeverity();
void displaySeverityGraph();
void printSeverityLabel(int severity);
# 53 "report.c"
void incidentMenu() {
    int choice;



    do {

        printf("\n========================================\n");
        printf("       INCIDENT REPORTS MODULE\n");
        printf("========================================\n");
        printf("  1. Log new incident\n");
        printf("  2. View all incidents\n");
        printf("  3. Search incident by ID\n");
        printf("  4. Mark incident as resolved\n");
        printf("  5. View critical active incidents\n");
        printf("  6. View severity bar chart\n");
        printf("  0. Back to main menu\n");
        printf("========================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);


        switch (choice) {
            case 1:
                logIncident();
                break;
            case 2:
                displayAllIncidents();
                break;
            case 3:
                searchIncidentByID();
                break;
            case 4:
                resolveIncident();
                break;
            case 5:
                displayHighSeverity();
                break;
            case 6:
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
# 113 "report.c"
void logIncident() {


    if (incCount >= 50) {
        printf("Error: Maximum incident capacity (50) reached.\n");
        return;
    }



    printf("\n--- LOG NEW INCIDENT ---\n");


    incidents[incCount].inc_id = 101 + incCount;


    printf("Enter incident type (e.g. Flood, Fire, Collapse): ");
    scanf(" %[^\n]", incidents[incCount].type);




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
# 168 "report.c"
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
# 219 "report.c"
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
# 267 "report.c"
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
# 310 "report.c"
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
# 361 "report.c"
void displaySeverityGraph() {

    printf("\n--- CITY DANGER RISK CHART ---\n");


    if (incCount == 0) {
        printf("No incidents logged yet. Add some incidents first.\n");
        return;
    }
# 379 "report.c"
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
# 427 "report.c"
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
# 465 "report.c"
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
# 508 "report.c"
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
# 570 "report.c"
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
# 589 "report.c"
int main() {

    printf("====================================\n");
    printf(" DISASTER RELIEF & RESCUE SYSTEM\n");
    printf("====================================\n");


    incidentMenu();

    printf("\nProgram ended. Goodbye!\n");

    return 0;
}
