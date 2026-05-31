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
    char status[20];
    char location[50];
    char contact[15];
};

struct Victim victims[100];
int victimCount = 0;

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


int main() {
    int choice;

    do {
        printf("\n================= RESCUE COORDINATION SYSTEM ==================\n");
        printf("1. Victim Registry\n");
        printf("2. Rescue Teams\n");
        printf("3. Supply Management\n");
        printf("4. Shelter Camps\n");
        printf("5. Incident Reports\n");
        printf("6. Exit\n");
        printf("Enter Your Choice: ");

        fgets(buffer, CHARMAX, stdin);
        buffer[strcspn(buffer, "\n")] = '\0';
        choice = atoi(buffer);

        switch(choice) {
            case 1: victimRegistryMenu(); break;
            case 2: break;
            case 3: break;
            case 4: break;
            case 5: break;
            case 6: printf("=========== Exiting Program ==========\n"); break;
            default: printf("Invalid Choice Try Again!\n"); break;
        }

    } while(choice != 6);

    return 0;
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
