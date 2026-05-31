#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define CHARMAX 50

struct Victim {
    int id;
    char name[50];
    int age;
    char gender[10];
    char injury[100];
    char status[20];      // "Displaced", "Sheltered", "Rescued"
    char location[50];    // Last known location
};

struct Victim victims[100];
int victimCount = 0;

void victimRegistryMenu();
void registerVictim();
void displayAllVictims();
void searchVictimByKeyword();
void updateVictimStatus();
void displayVictimSummary();

char buffer[CHARMAX];

int main () {



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
                victimRegistryMenu();
                break;

            case 2 :

                
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

void registerVictim() {
    if (victimCount >= 100) {
        printf("Victim registry is full!\n");
        return;
    }

    struct Victim v;
    v.id = victimCount + 1;

    printf("\n--- Register New Victim ---\n");

    printf("Enter Name: ");
    scanf(" %[^\n]", v.name);

    printf("Enter Age: ");
    scanf("%d", &v.age);

    printf("Enter Gender (Male/Female/Other): ");
    scanf("%s", v.gender);

    printf("Enter Injury Description: ");
    scanf(" %[^\n]", v.injury);

    printf("Enter Last Known Location: ");
    scanf(" %[^\n]", v.location);

    printf("Enter Status (Displaced/Sheltered/Rescued): ");
    scanf("%s", v.status);

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
    printf("%-5s %-20s %-5s %-10s %-15s %-15s %-15s\n",
           "ID", "Name", "Age", "Gender", "Status", "Location", "Injury Description");
    printf("----------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < victimCount; i++) {
        printf("%-5d %-20s %-5d %-10s %-15s %-15s %-15s\n",
               victims[i].id,
               victims[i].name,
               victims[i].age,
               victims[i].gender,
               victims[i].status,
               victims[i].location,
               victims[i].injury);
    }
}

void searchVictimByKeyword() {
    char searchKeyword[50];
    int found = 0;

    printf("\nEnter keyword to search: ");
    scanf(" %[^\n]", searchKeyword);

    printf("\n--- Search Results ---\n");
    printf("%-5s %-20s %-5s %-10s %-15s %-15s %-15s\n",
           "ID", "Name", "Age", "Gender", "Status", "Location", "Injury Description");
    printf("----------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < victimCount; i++) {
        if ((strcasecmp(victims[i].name, searchKeyword) == 0) || (strcasecmp(victims[i].status, searchKeyword) == 0) || (strcasecmp(victims[i].location, searchKeyword) == 0) || (victims[i].id==searchKeyword) ) {
            printf("%-5d %-25s %-5d %-10s %-15s %-20s %-15s\n",
               victims[i].id,
               victims[i].name,
               victims[i].age,
               victims[i].gender,
               victims[i].status,
               victims[i].location,
               victims[i].injury);
            found++;
        }
    }

    printf("----------------------------------------------------------------------------------------------\n");
    printf("No of records : %d\n", found);

    if (!found) {
        printf("No victim found with keyword: %s\n", searchKeyword);
    }
}

void updateVictimStatus() {
    int searchId;
    int found = 0;

    printf("\nEnter Victim ID to update status: ");
    scanf("%d", &searchId);

    for (int i = 0; i < victimCount; i++) {
        if (victims[i].id == searchId) {
            printf("Current Status: %s\n", victims[i].status);
            printf("Enter New Status (Displaced/Sheltered/Rescued): ");
            scanf("%s", victims[i].status);
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
        if (strcmp(victims[i].status, "Displaced") == 0)
            displaced++;
        else if (strcmp(victims[i].status, "Sheltered") == 0)
            sheltered++;
        else if (strcmp(victims[i].status, "Rescued") == 0)
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
        printf("3. Search Victim by Keyword\n");
        printf("4. Update Victim Status\n");
        printf("5. View Summary\n");
        printf("0. Back to Main Menu\n");
        printf("=====================================\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        while (getchar() != '\n');

        switch (choiceReg) {
            case 1: 
                registerVictim();     
                break;
            
            case 2: 
                displayAllVictims();  
                break;
            
            case 3: 
                searchVictimByKeyword(); 
                break;
            
            case 4: 
                updateVictimStatus(); 
                break;
            
            case 5: 
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
