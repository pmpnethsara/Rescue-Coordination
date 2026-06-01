/*
 * ============================================================
 *  MODULE 5 - INCIDENT REPORTS
 *  Disaster Relief & Rescue Coordination System
 *  Member: Kaveesha
 *  Subject: IN 1101 - Programming Fundamentals
 * ============================================================
 */

/* --- WHAT ARE #include statements? ---
   These lines bring in "libraries" — pre-written code that C
   already has. We need them so we can use printf, scanf, etc. */

#include <stdio.h>   /* Needed for printf() and scanf() — printing and reading input */
#include <string.h>  /* Needed for strcmp() and strcpy() — working with text (strings) */

/* ============================================================
   STEP 1: DEFINE THE STRUCTURE
   A "struct" is like a blueprint for one incident record.
   Think of it like one row in a table — it holds all the
   details about a single incident together in one place.
   ============================================================ */

struct Incident {
    int  inc_id;          /* A unique number to identify each incident (e.g. 101, 102) */
    char type[50];        /* The kind of incident — stored as text, max 50 characters */
    int  severity;        /* How serious: 1 = Low, 2 = Medium, 3 = High */
    char location[100];   /* Where it happened — stored as text, max 100 characters */
    int  resolved;        /* 0 means still active, 1 means it has been resolved */
};

/* ============================================================
   STEP 2: CREATE THE ARRAY AND COUNTER
   An "array of structs" is like a table with many rows.
   incidents[50] means we can store up to 50 incidents.
   incCount keeps track of how many have been added so far.
   ============================================================ */

struct Incident incidents[50]; /* This is our "database" — an array of 50 Incident records */
int incCount = 0;              /* Starts at 0 because no incidents have been logged yet */

/* ============================================================
   FUNCTION PROTOTYPES
   In C, you must "announce" your functions before main().
   This tells the compiler "these functions exist, trust me."
   The actual code for each function comes further below.
   ============================================================ */

void logIncident();           /* Function 1: Add a new incident */
void displayAllIncidents();   /* Function 2: Show all incidents */
void searchIncidentByID();    /* Function 3: Find one incident by its ID */
void resolveIncident();       /* Function 4: Mark an incident as resolved */
void displayHighSeverity();   /* Function 5: Show only critical active incidents */
void displaySeverityGraph();  /* Function 6: Show a # bar chart of incidents by severity */
void printSeverityLabel(int severity); /* Helper: prints "LOW", "MEDIUM", or "HIGH" */

/* ============================================================
   THE MENU FUNCTION
   This is what the main() function in your group's project
   will call. It shows your module's sub-menu and lets the
   user pick which function to run.
   ============================================================ */

void incidentMenu() {
    int choice; /* This variable will store what number the user types */

    /* do...while loop: runs the menu at least once, and keeps
       looping until the user types 0 to go back */
    do {
        /* Print the menu options on screen */
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
        scanf("%d", &choice); /* Read the number the user types; & means "store it in choice" */

        /* switch statement: checks what number was typed and runs the matching case */
        switch (choice) {
            case 1:
                logIncident();         /* User typed 1 → run Function 1 */
                break;                 /* break stops the switch from falling into the next case */
            case 2:
                displayAllIncidents(); /* User typed 2 → run Function 2 */
                break;
            case 3:
                searchIncidentByID();  /* User typed 3 → run Function 3 */
                break;
            case 4:
                resolveIncident();     /* User typed 4 → run Function 4 */
                break;
            case 5:
                displayHighSeverity(); /* User typed 5 → run Function 5 */
                break;
            case 6:
                displaySeverityGraph(); /* User typed 6 → run the bar chart */
                break;
            case 0:
                printf("Returning to main menu...\n"); /* User typed 0 → exit the loop */
                break;
            default:
                /* default runs if the user typed something not in the list */
                printf("Invalid choice. Please enter a number between 0 and 6.\n");
        }

    } while (choice != 0); /* Keep showing the menu until the user types 0 */
}

/* ============================================================
   FUNCTION 1: logIncident()
   Purpose : Let the user enter details of a new incident
             and save it into the incidents[] array.
   Input   : User types — type, severity, location
   Output  : Confirmation message with the new incident ID
   ============================================================ */

void logIncident() {

    /* First, check if the array is full (max 50 incidents) */
    if (incCount >= 50) {
        printf("Error: Maximum incident capacity (50) reached.\n");
        return; /* return exits the function immediately */
    }

    /* Create a temporary variable to build the new incident.
       incidents[incCount] is the next empty slot in our array. */
    printf("\n--- LOG NEW INCIDENT ---\n");

    /* Auto-assign the ID: start at 101, so 2nd is 102, 3rd is 103, etc. */
    incidents[incCount].inc_id = 101 + incCount;

    /* Read the incident type from the user */
    printf("Enter incident type (e.g. Flood, Fire, Collapse): ");
    scanf(" %[^\n]", incidents[incCount].type);
    /* NOTE: %[^\n] reads a full line of text including spaces.
       The space before % clears any leftover newline from previous input. */

    /* Read the severity level */
    printf("Enter severity (1 = Low, 2 = Medium, 3 = High): ");
    scanf("%d", &incidents[incCount].severity);

    /* Validate severity — it must be 1, 2, or 3 */
    while (incidents[incCount].severity < 1 || incidents[incCount].severity > 3) {
        printf("Invalid severity. Please enter 1, 2, or 3: ");
        scanf("%d", &incidents[incCount].severity);
        /* This while loop keeps asking until the user enters a valid number */
    }

    /* Read the location */
    printf("Enter location: ");
    scanf(" %[^\n]", incidents[incCount].location);

    /* Auto-set resolved to 0 (meaning "not resolved yet") */
    incidents[incCount].resolved = 0;

    /* Print a success message showing the new incident's ID */
    printf("\nIncident #%d logged successfully.\n", incidents[incCount].inc_id);

    /* Increase the counter so the next incident goes into the next slot */
    incCount++;
    /* incCount++ is shorthand for incCount = incCount + 1 */
}

/* ============================================================
   FUNCTION 2: displayAllIncidents()
   Purpose : Loop through the entire array and print each
             incident's details on screen.
   Input   : None (reads from the global incidents[] array)
   Output  : A formatted list of all incidents
   ============================================================ */

void displayAllIncidents() {

    printf("\n--- ALL INCIDENTS ---\n");

    /* Check if there are any incidents to display */
    if (incCount == 0) {
        printf("No incidents have been logged yet.\n");
        return; /* Exit the function early — nothing to show */
    }

    /* Print a table header so the output looks neat */
    printf("%-6s %-20s %-10s %-25s %-10s\n",
           "ID", "Type", "Severity", "Location", "Status");
    printf("----------------------------------------------------------------------\n");
    /* %-6s means: print as text, left-aligned, minimum 6 characters wide.
       This makes the columns line up neatly. */

    /* Loop from index 0 up to (but not including) incCount */
    int i; /* Loop counter variable */
    for (i = 0; i < incCount; i++) {
        /* Print the ID and Type */
        printf("%-6d %-20s ", incidents[i].inc_id, incidents[i].type);

        /* Print severity as a word instead of a number */
        printSeverityLabel(incidents[i].severity); /* calls our helper function */
        printf("      "); /* add spacing after the severity label */

        /* Print location */
        printf("%-25s ", incidents[i].location);

        /* Print resolved status as a word */
        if (incidents[i].resolved == 0) {
            printf("ACTIVE\n");     /* resolved = 0 means still active */
        } else {
            printf("RESOLVED\n");   /* resolved = 1 means done */
        }
    }

    printf("----------------------------------------------------------------------\n");
    printf("Total incidents: %d\n", incCount); /* Show how many in total */
}

/* ============================================================
   FUNCTION 3: searchIncidentByID()
   Purpose : Ask the user for an ID number, then find and
             display that specific incident from the array.
   Input   : User types — inc_id (e.g. 101)
   Output  : Full details of the matching incident, or
             "not found" message
   ============================================================ */

void searchIncidentByID() {

    printf("\n--- SEARCH INCIDENT BY ID ---\n");

    int searchID; /* Variable to store the ID the user types */
    printf("Enter incident ID to search: ");
    scanf("%d", &searchID); /* Read the number from the user */

    int found = 0; /* Flag variable: 0 = not found yet, 1 = found */
    int i;         /* Loop counter */

    /* Loop through all incidents to find a matching ID */
    for (i = 0; i < incCount; i++) {

        /* Check if this incident's ID matches what the user typed */
        if (incidents[i].inc_id == searchID) {

            /* Found it! Print the full details */
            printf("\n--- INCIDENT FOUND ---\n");
            printf("ID       : %d\n",   incidents[i].inc_id);
            printf("Type     : %s\n",   incidents[i].type);     /* %s prints text */
            printf("Severity : ");
            printSeverityLabel(incidents[i].severity); /* print LOW/MEDIUM/HIGH */
            printf("\n");
            printf("Location : %s\n",   incidents[i].location);
            printf("Status   : %s\n",   incidents[i].resolved == 0 ? "ACTIVE" : "RESOLVED");
            /* The ? : above is a shortcut for if/else:
               if resolved==0 print "ACTIVE", else print "RESOLVED" */

            found = 1; /* Set the flag to 1 so we know we found it */
            break;     /* Stop the loop — no need to check the rest */
        }
    }

    /* After the loop, check if we found anything */
    if (found == 0) {
        printf("Incident with ID %d not found.\n", searchID);
    }
}

/* ============================================================
   FUNCTION 4: resolveIncident()
   Purpose : Find an incident by ID and change its resolved
             field from 0 to 1 (marking it as done).
   Input   : User types — inc_id of the incident to resolve
   Output  : Confirmation message, or "not found"
   ============================================================ */

void resolveIncident() {

    printf("\n--- MARK INCIDENT AS RESOLVED ---\n");

    int targetID; /* Variable to store the ID the user types */
    printf("Enter incident ID to mark as resolved: ");
    scanf("%d", &targetID);

    int found = 0; /* Flag: 0 = not found, 1 = found */
    int i;

    for (i = 0; i < incCount; i++) {

        if (incidents[i].inc_id == targetID) {

            /* Check if it's already resolved — no need to do it twice */
            if (incidents[i].resolved == 1) {
                printf("Incident #%d is already marked as resolved.\n", targetID);
            } else {
                /* This is the key line: change resolved from 0 to 1 */
                incidents[i].resolved = 1;
                printf("Incident #%d has been marked as RESOLVED.\n", targetID);
            }

            found = 1; /* We found and handled the incident */
            break;     /* Stop looping */
        }
    }

    if (found == 0) {
        printf("Incident with ID %d not found.\n", targetID);
    }
}

/* ============================================================
   FUNCTION 5: displayHighSeverity()
   Purpose : Show only incidents that are BOTH severity = 3
             (High) AND not yet resolved (resolved = 0).
             This acts as an emergency dashboard.
   Input   : None
   Output  : Filtered list of critical active incidents
   ============================================================ */

void displayHighSeverity() {

    printf("\n--- CRITICAL ACTIVE INCIDENTS (Severity: HIGH) ---\n");

    int found = 0; /* We'll use this to detect if none match */
    int i;

    for (i = 0; i < incCount; i++) {

        /* The && means "AND" — BOTH conditions must be true to print */
        if (incidents[i].severity == 3 && incidents[i].resolved == 0) {

            /* This incident is high severity AND still active — print it */
            printf("ID: %-4d | Type: %-20s | Location: %s\n",
                   incidents[i].inc_id,
                   incidents[i].type,
                   incidents[i].location);

            found = 1; /* At least one match was found */
        }
    }

    /* If no incidents matched the filter, tell the user */
    if (found == 0) {
        printf("No critical active incidents at this time.\n");
    }
}

/* ============================================================
   FUNCTION 6: displaySeverityGraph()
   Purpose : For each unique city in the incidents array,
             calculate a DANGER RISK % and draw a vertical
             bar chart using # characters.

   How risk % is calculated:
     - Every incident has a severity: 1 (Low), 2 (Medium), 3 (High)
     - We add up all severity scores for that city → "totalScore"
     - The WORST possible score = 3 (max severity) x number of incidents
       in that city → "maxPossible"
     - Risk % = (totalScore / maxPossible) x 100
     - So a city with only HIGH incidents = 100% danger
     - A city with only LOW incidents = 33% danger

   The vertical bar: the chart is 10 rows tall (each row = 10%).
   A city with 80% risk will have # filled in rows 1–8 from
   the bottom, and empty rows 9–10 at the top.

   Input   : None (reads from the global incidents[] array)
   Output  : A vertical bar chart, one column per city
   ============================================================ */

void displaySeverityGraph() {

    printf("\n--- CITY DANGER RISK CHART ---\n");

    /* Check if there is any data to graph */
    if (incCount == 0) {
        printf("No incidents logged yet. Add some incidents first.\n");
        return; /* Exit the function early — nothing to draw */
    }

    /* -------------------------------------------------------
       STEP A: FIND ALL UNIQUE CITIES
       We scan through incidents[] and collect each city name
       only once into a separate cityNames[] array.
       We also keep a parallel cityScore[] array to store the
       total severity score for each city.
       ------------------------------------------------------- */

    char cityNames[50][100]; /* Stores up to 50 unique city names, each max 100 chars */
    int  cityScore[50];      /* Stores the total severity score for each city */
    int  cityCount = 0;      /* How many unique cities we have found so far */

    int i, j; /* Loop counters — i for outer loops, j for inner loops */

    /* Loop through every incident */
    for (i = 0; i < incCount; i++) {

        int alreadySeen = 0; /* Flag: 0 = this city is new, 1 = already in our list */

        /* Check if this incident's location is already in cityNames[] */
        for (j = 0; j < cityCount; j++) {

            /* strcmp() compares two strings — returns 0 if they are identical */
            if (strcmp(incidents[i].location, cityNames[j]) == 0) {

                /* City already exists — just add this incident's severity to its score */
                cityScore[j] += incidents[i].severity;
                /* += means "add to existing value", same as cityScore[j] = cityScore[j] + severity */

                alreadySeen = 1; /* Mark that we found it */
                break;           /* Stop the inner loop — no need to keep searching */
            }
        }

        /* If alreadySeen is still 0, this is a brand new city — add it to the list */
        if (alreadySeen == 0) {

            /* Copy the city name into the next empty slot in cityNames[] */
            strcpy(cityNames[cityCount], incidents[i].location);
            /* strcpy(destination, source) copies text from source into destination */

            /* Start its score with this first incident's severity */
            cityScore[cityCount] = incidents[i].severity;

            cityCount++; /* Move to the next slot for the next new city */
        }
    }

    /* -------------------------------------------------------
       STEP B: CALCULATE RISK % FOR EACH CITY
       Max possible score for a city = 3 x number of incidents
       in that city. We need to count incidents per city first.
       Risk % = (cityScore / maxPossible) * 100
       We store risk as an integer (e.g. 67, not 66.6).
       ------------------------------------------------------- */

    int cityRisk[50];       /* Stores the risk percentage (0–100) for each city */
    int cityIncidents[50];  /* Stores the number of incidents per city */

    /* Count how many incidents belong to each city */
    for (i = 0; i < cityCount; i++) {
        cityIncidents[i] = 0; /* Start the count at 0 for each city */

        for (j = 0; j < incCount; j++) {
            /* If this incident's location matches the city name, count it */
            if (strcmp(incidents[j].location, cityNames[i]) == 0) {
                cityIncidents[i]++;
            }
        }

        /* Max possible score = 3 (highest severity) × number of incidents in city */
        int maxPossible = 3 * cityIncidents[i];

        /* Risk % = (actual score / max possible) × 100
           We multiply by 100 FIRST before dividing to avoid losing decimals
           in integer division. E.g. (4 * 100) / 6 = 66, not (4/6)*100 = 0 */
        cityRisk[i] = (cityScore[i] * 100) / maxPossible;
    }

    /* -------------------------------------------------------
       STEP C: DRAW THE VERTICAL BAR CHART
       The chart has 10 rows, each representing 10% risk.
       Row 10 (top)    = 91–100%
       Row 9           = 81–90%
       ...
       Row 1 (bottom)  = 1–10%

       For each row (from top = 10 down to bottom = 1),
       we print a # under a city if its risk % is high enough
       to reach that row, otherwise print a space.

       After all rows, we print the city names and scores.
       ------------------------------------------------------- */

    int chartHeight = 10; /* The bar chart has 10 rows = 10 levels of 10% each */

    printf("\n");
    printf("  100%% |  (Each # = 10%% risk)\n");
    /* Note: %% prints a literal % sign in printf — one % would confuse printf */

    /* Outer loop: goes from the TOP row (10) down to the BOTTOM row (1) */
    int row;
    for (row = chartHeight; row >= 1; row--) {

        /* Print the Y-axis percentage label on the left side */
        /* row * 10 gives us 100, 90, 80 ... 10 */
        if (row * 10 == 100) {
            printf("       |"); /* 100% row already printed above as header */
        } else {
            printf("  %3d%% |", row * 10);
            /* %3d prints the number in a field 3 wide so columns align:
               100 → "100",  90 → " 90",  10 → " 10" */
        }

        /* Inner loop: go through every city and decide # or space for this row */
        for (i = 0; i < cityCount; i++) {

            /* A city gets a # in this row if its risk % is >= this row's threshold.
               Row 10 threshold = 100%, row 9 = 90%, row 1 = 10%
               threshold = row * 10 */
            if (cityRisk[i] >= row * 10) {
                printf("  # "); /* Print a # — this city's bar reaches this height */
            } else {
                printf("    "); /* Print spaces — bar does not reach this row */
            }
        }

        printf("\n"); /* Move to the next line after printing all cities for this row */
    }

    /* -------------------------------------------------------
       STEP D: PRINT THE BOTTOM AXIS AND CITY LABELS
       Draw a horizontal line, then print each city name
       and its risk % score underneath its column.
       ------------------------------------------------------- */

    /* Print the horizontal base line of the chart */
    printf("    0%% +");
    for (i = 0; i < cityCount; i++) {
        printf("----"); /* 4 dashes per city column to match column width */
    }
    printf("\n");

    /* Print city names under each column */
    printf("         ");
    for (i = 0; i < cityCount; i++) {
        /* %-4s prints the first 4 characters of the city name, left-aligned.
           This keeps columns the same width even for long city names. */
        printf("%-4.4s", cityNames[i]);
    }
    printf("\n");

    /* Print the risk % number under each city name */
    printf("         ");
    for (i = 0; i < cityCount; i++) {
        printf("%3d%%", cityRisk[i]); /* e.g. " 67%" or "100%" */
    }
    printf("\n");

    /* -------------------------------------------------------
       STEP E: PRINT A RISK LEVEL KEY so the user understands
       what the percentages mean in plain English.
       ------------------------------------------------------- */

    printf("\n  --- RISK LEVEL KEY ---\n");
    printf("  0%%  - 33%%  : LOW RISK    (mostly minor incidents)\n");
    printf("  34%% - 66%%  : MEDIUM RISK (mixed severity)\n");
    printf("  67%% - 99%%  : HIGH RISK   (mostly serious incidents)\n");
    printf("  100%%        : CRITICAL    (all incidents are HIGH severity!)\n");

    /* Print a summary of each city with full details */
    printf("\n  --- CITY SUMMARY ---\n");
    for (i = 0; i < cityCount; i++) {
        printf("  %-20s | Score: %2d | Incidents: %2d | Risk: %3d%%",
               cityNames[i],
               cityScore[i],
               cityIncidents[i],
               cityRisk[i]);

        /* Print a plain-English warning label next to each city */
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

/* ============================================================
   HELPER FUNCTION: printSeverityLabel()
   Purpose : Converts a severity number (1, 2, 3) into a
             readable word (LOW, MEDIUM, HIGH).
   This is used inside displayAllIncidents() and search.
   ============================================================ */

void printSeverityLabel(int severity) {
    if (severity == 1) {
        printf("LOW   "); /* Extra spaces to keep column alignment */
    } else if (severity == 2) {
        printf("MEDIUM");
    } else if (severity == 3) {
        printf("HIGH  ");
    } else {
        printf("UNKNOWN");
    }
}

/* ============================================================
   MAIN FUNCTION
   This is only here so you can test YOUR MODULE by itself.
   When you merge with your group, the main() will be in
   the group's combined file — delete this main() then.
   ============================================================ */

int main() {

    printf("====================================\n");
    printf(" DISASTER RELIEF & RESCUE SYSTEM\n");
    printf("====================================\n");

    /* Call your module's menu — this runs your whole module */
    incidentMenu();

    printf("\nProgram ended. Goodbye!\n");

    return 0; /* return 0 means the program finished without errors */
}