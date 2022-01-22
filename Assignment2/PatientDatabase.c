/***************************************
* Author: Muhammad, Adil *
* Email: adil133@my.yorku.ca *
* York Student #: 218059956
************************************** **/

// Include library functions
#include <stdio.h>
#include <ctype.h>       // for tolower
#include <string.h>
#include <stdlib.h>

// Define constant variables
#define SIZE 30          // Storage size
#define fieldLength 200  // Length of name
#define optimalH 120     // High BP 
#define optimalL 80      // Low BP 
 
// Display Structure defined 
struct db_type {
  // Declare variable which stores the names
  char name[fieldLength];

  // Declare variables such as age, high BP, low BP and risk 
  int age;

  float highBP;
  float lowBP;
  float riskFactor;
};

// Method declarations
char prompt_menu(void);
void enterNew(struct db_type * pArr[]);     // Enter a new record
void init_list(struct db_type * pArr[]);    // Initialize the list of records
void displayDB(struct db_type * pArr[]);    // Display the current records  
void sort(struct db_type * pArr[]);         // Sort the records
void swap(struct db_type * pArr[]);         // Swap one record with another
void removeRecord(struct db_type * pArr[]); // Remove a record
void clearDB(struct db_type * pArr[]);      // Clear the records

// Main method
int main(int argc, char *argv[]) {
    struct db_type * db_pArr[SIZE];  // main db storage
    init_list(db_pArr);  // set to NULL
    
    // Declare variable which represents the letter entered in the prompt
    char choice;

    // Continue to loop until q or Q is read, as shown in the switch statement
    for(; ;){
      choice = prompt_menu();

      // Switch statement to compare choice to characters
      switch (choice)
      {
         case 'n': enterNew(db_pArr); break;    // If n, enter record information
         case 'd': displayDB(db_pArr); break;   // If d, display records
        
         case 's': sort(db_pArr); break;        // If s, sort the records
	   
         case 'c': clearDB(db_pArr); break;     // If c, clear the records
        
         case 'p': swap(db_pArr); break;        // If p, swap the records
         case 'r': removeRecord(db_pArr);break; // If r, remove the records
         
         case 'q': exit(1); // terminate the whole program
       }
	
     }

     // End of main, return 0
     return 0;
}

// Method which works with the prompt menu
char prompt_menu(void){
  char s[80];

  // While-true loop
  while(1){
    // Format information of options to choose from prompt menu
    printf("\n-----------------------------------------------------------------\n");
    printf("|    %-20s","(N)ew record");
    printf("%-20s","(R)emove record");
    printf("Swa(p) records\t|\n");
    printf("|    %-20s","(S)ort database");
    printf("%-20s","(C)lear database");
    printf("(D)isplay db\t|\n");
  
    // printf("|    %-20s","(L)oad disk");
    // printf("%-20s","(W)rite disk");
    // printf("(E)mpty disk\t|\n");
   
    // Format information of options to choose from prompt menu
    printf("|    %-20s","(Q)uit");
    printf("*Case Insensitive*\t\t\t|\n");
    printf("-----------------------------------------------------------------\n");
    printf("choose one: ");
  
    fgets(s,50, stdin); // \n added
    //scanf("%s", s);  
    if (strlen(s) == 2 && strchr("edlsuqrcwnvpr", tolower(*s))) 
       return tolower(*s); // s[0], return the first character of s  
    //else
    printf("not a valid input!\n");
 }
}

// Method: Initialize the list
void init_list(struct db_type * pArr[]){
  // Declare variable
  int t;
  // Ensure t is less than the storage size
  for (t = 0; t < SIZE; t++) { 
     // Initially, assign elements of the array to NULL
     pArr[t]= NULL;
  }
}

// Method: Clear the display
void clearDB(struct db_type * pArr[]) {
   char c3[3];
   printf("are you sure to clear db? (y) or (n)? ");
    
   fgets(c3,3,stdin);
   
   // complete the function by calling init_list();
   if (strcmp("y\n", c3) == 0) {
      // Initialize the list if 'y', namely yes, is inputted by the user
      init_list(pArr);
   }
}

/* input items into the db */
void enterNew(struct db_type * pArr[SIZE]) {
    // Declare variable
    int i;

    // Make a copy of structure db_type
    struct db_type *patient = malloc(sizeof(struct db_type));
    // Access name within structure patient
    printf("name: ");    scanf("%[^\n]s", patient -> name);
    // Access age within structure patient
    printf("age: ");     scanf("%d", &patient -> age);
    // Access high bp within structure patient
    printf("high bp: "); scanf("%f", &patient -> highBP);
    // Access low bp within structure patient
    printf("low bp: ");  scanf("%f", &patient -> lowBP);
    getchar();

    // If blood pressure is not higher than optimalH and low blood pressure is not higher
    // than optimalL 
    if (patient -> highBP <= optimalH && patient -> lowBP <= optimalL) {
        patient -> riskFactor = 0;
    }
    // If one of blood pressure is below (or equal to) to its optimal value, but the other is 
    // above the optimal value by no more than 10, then the risk factor is 1
    else if (patient -> lowBP <= optimalL && patient -> highBP <= (optimalH + 10)) {
        patient -> riskFactor = 1;
    }
    else if (patient -> highBP <= optimalH && patient -> lowBP <= (optimalL + 10)) {
        patient -> riskFactor = 1;
    }
    // If both the pressures are above their optimal value (but) by no more than 10, then the risk factor is 2
    else if (patient -> lowBP <= (optimalL + 10) && patient -> highBP <= (optimalH + 10)) {
        patient -> riskFactor = 2;
    }
    // If one pressure is below (or equal to) its optimal value, but the other is above the 
    // optimal value by 11-20, then the risk factor is 3
    else if (patient -> lowBP <= optimalL && patient -> highBP > (optimalH + 10) && patient -> highBP <= (optimalH + 20)) {
        patient -> riskFactor = 3;
    }
    // If both pressures are higher than their optimal value by 11-20, the risk factor is 4
    else if ((patient -> highBP > (optimalH + 10) && patient -> highBP <= (optimalH + 20)) && (patient -> lowBP >
    (optimalL + 10) && patient -> lowBP <= (optimalL + 20))) {
        patient -> riskFactor = 4;
    }
    // In all other higher cases, the risk factor is 5
    else {
        patient -> riskFactor = 5;
    }
    
    // Case where patient is above the age of 50
    if(patient -> age > 50 && patient -> riskFactor > 0) {
        patient -> riskFactor += 0.5;
    }
    
    // Loop through the size of records
    for (i = 0; i < SIZE; i++) {
      // Replace null spaces with the patient information in its structure
      if (pArr[i] == NULL) {
        pArr[i] = patient;
        // Note that this if statement is only entered if the record at a certain position is NULL
        break;
      }
    }
}

/* remove an existing item from the db */
void removeRecord (struct db_type * pArr[])	{
  // Declare variables
  int j;
  int i;
  int position;
  int recordFound = 0;

  // Declare variable which stores the names
  char name[30];
  // Enter statement to remove
  printf("enter full name to remove: ");
  // Exclude the \n when attaining input
  scanf("%[^\n]s", name);
  // Read each character from the standard input
  getchar();
    
  // Loop through the size  
  for (i = 0; i < SIZE; i++) {
    // If the element in the array is null and the name is identical to the one at the current position
    if (pArr[i] != NULL && strcmp(pArr[i]->name, name) == 0) {
      // Name has been removed
      printf("record [%s] removed successfully.", name);
      // Set the position to the current position
      position = i;
      // Set recordfound to 1
      recordFound = 1;
      break;
    }
  }
  
  // Record is not found
  if (recordFound == 0) {
      // Tell the user that the record is not found
      printf("record not found");
  }

  // Record is found
  if (recordFound == 1) {
      // Initially, set j to position
      for (j = position; j < SIZE - 1; j++) {
          // Assign the current element to the succeeding element to illustrate
          // removal of record
          pArr[j] = pArr[j + 1];
      }
  }
}

/* display all records. Generate output with the same formaing as the sample output 
 use \t to align well
*/
void displayDB(struct db_type * pArr[]){
  printf("===============================\n");
  
  // Declare variable
  int i;

  // Loop through storage space
  for (i = 0; i < SIZE; i++) {
    // Given that the record at position i is empty
    if (pArr[i] != NULL) {
      // Output the name, age, display and risk
      printf("name:\t%s\nage:\t%d\ndp:\t%.2f %.2f\nrisk:\t%.1f\n\n", 
             pArr[i] -> name, pArr[i] -> age, pArr[i] -> highBP, pArr[i] -> lowBP, pArr[i] -> riskFactor);
    }
    // Record is already taken, simply break
    else{
      break;
    }
  }
  printf("========== %d records ==========\n", i);
}

/* swap the adjacent records */
void swap(struct db_type * pArr[]) {
  // Declare variable
  int i;

  // Loop through storage space
  for (i = 0; i < SIZE; i += 2) {
    // If the succeeding position is not occupied
    if (pArr[i + 1] != NULL) {
      // Make a copy of structure db_type and save space using malloc
      // Ensure the space that is saved is the same size as the space saved for structure db_type
      struct db_type *temporary = malloc(sizeof(struct db_type));

      *temporary = *pArr[i];      // Set the temporary pointer to the current element
      *pArr[i] = *pArr[i + 1];    // Set the current element to the succeeding element
      *pArr[i + 1] = *temporary;  // Set the succeeding element to temporary (which contains the current element)
    }
  }
} 
 
// sort the record, either by name or risk factor, prompt use for choice
void sort(struct db_type * pArr[]) {
  // Set size of sort array to 30 (same as that of constant SIZE)
  char sortRecords[SIZE];
  printf("sort by name (n) or risk (r)? ");

  // Store the user input in variable sort
  scanf("%s", sortRecords);
  // Get the user input 
  getchar();

  // Sort by name if character n is given by user
  if (strcmp("n", sortRecords) == 0) {
    // Declare variables
    int i;
    int j;

    // Loop through the storage space
    for (i = 0; i < SIZE; i++) {
      // If the current position is not NULL
      if (pArr[i] != NULL) {
        // Compare with the succeeding element
        for (j = i + 1; j < SIZE; j++) {
          // // If the succeeding position is not NULL
          if (pArr[j] != NULL) {
            // If current element is greater than the succeeding element
            if (strcmp(pArr[i] -> name , pArr[j] -> name) > 0) {
              // Declare a temporary structure that is the same space as structure db_type
              struct db_type *temporary = malloc(sizeof(struct db_type));

              // Swap current element with succeeding element
              *temporary = *pArr[i];
              *pArr[i] = *pArr[j];
              *pArr[j] = *temporary;
            }
          }
        }
      }
    }
  }

  // Sort by risk if character r is inputted by user
  if (strcmp("r", sortRecords) == 0) {
    // Declare variables
    int i;
    int j;
    // Loop through the storage space
    for (i = 0; i < SIZE; i++) {
      // If the current position is not NULL
      if (pArr[i] != NULL) {
        for (j = i + 1; j < SIZE; j++) {
          // If the succeeding position is not NULL
          if (pArr[j] != NULL) {
            // If current element is greater than the succeeding element
            if (pArr[i] -> riskFactor > pArr[j] -> riskFactor) {
              // Declare a temporary structure that is the same space as structure db_type
              struct db_type *temporary = malloc(sizeof(struct db_type));

              // Swap current element with succeeding element
              *temporary = *pArr[i];
              *pArr[i] = *pArr[j];
              *pArr[j] = *temporary;
            }
          }
        }
      }
    }
  }
}

