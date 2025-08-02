
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struct for the linked list
struct user {
    char name[100];
    char location1[100];
    char location2[100];
    int n_places_visited;
    struct user *next;
};

struct user *head = NULL;

// Struct for binary tree profile (currently unused)
struct user_bt {
    char name[100];
    int places[100];
    int n_places_visited;
    struct user_bt *left;
    struct user_bt *right;
};

struct user_bt *root = NULL;

// Function prototypes
void insert_user_ll(char name[100]);
void remove_user_ll(char *name);
void insert_visit_ll(char *name, int place_number, char place1[50], char place2[50]);
void save_to_file_ll(FILE *f);
void read_from_file_ll(FILE *f);
void display_users();

// Insert new user into linked list (sorted alphabetically)
void insert_user_ll(char name[100]) {
    struct user *new_node = (struct user*)malloc(sizeof(struct user));
    if (new_node == NULL) {
        printf("\nMemory allocation failed!\n");
        return;
    }
    
    strcpy(new_node->name, name);
    strcpy(new_node->location1, "");
    strcpy(new_node->location2, "");
    new_node->n_places_visited = 0;
    new_node->next = NULL;
    
    // If list is empty or new user should be first
    if (head == NULL || strcmp(head->name, new_node->name) > 0) {
        new_node->next = head;
        head = new_node;
        printf("\nUser %s added successfully!\n", name);
        return;
    }
    
    // Find correct position to insert
    struct user *current = head;
    while (current->next != NULL && strcmp(current->next->name, new_node->name) < 0) {
        current = current->next;
    }
    
    new_node->next = current->next;
    current->next = new_node;
    printf("\nUser %s added successfully!\n", name);
}

// Remove user from linked list
void remove_user_ll(char *name) {
    if (head == NULL) {
        printf("\nList is empty. No users to remove.\n");
        return;
    }
    
    struct user *current = head;
    struct user *prev = NULL;
    
    // If head node is to be deleted
    if (strcmp(head->name, name) == 0) {
        head = head->next;
        free(current);
        printf("\nUser %s removed successfully!\n", name);
        return;
    }
    
    // Search for the user to delete
    while (current != NULL && strcmp(current->name, name) != 0) {
        prev = current;
        current = current->next;
    }
    
    if (current == NULL) {
        printf("\nName not found, try again...\n");
        return;
    }
    
    prev->next = current->next;
    free(current);
    printf("\nUser %s removed successfully!\n", name);
}

// Insert visit location for a user
void insert_visit_ll(char *name, int place_number, char place1[50], char place2[50]) {
    struct user *current = head;
    
    // Find the user
    while (current != NULL && strcmp(current->name, name) != 0) {
        current = current->next;
    }
    
    if (current == NULL) {
        printf("\nUser not found, try again.\n");
        return;
    }
    
    if (current->n_places_visited >= 2) {
        printf("\nUser already has maximum locations (2).\n");
        return;
    }
    
    char place[100];
    printf("\nEnter location: ");
    if (scanf("%s", place) != 1) {
        printf("\nInvalid input!\n");
        return;
    }
    
    if (current->n_places_visited == 0) {
        strcpy(current->location1, place);
        current->n_places_visited = 1;
        printf("\nLocation added successfully!\n");
    } else if (current->n_places_visited == 1) {
        strcpy(current->location2, place);
        current->n_places_visited = 2;
        printf("\nLocation added successfully!\n");
    }
}

// Save data to file
void save_to_file_ll(FILE *f) {
    f = fopen("UserDataFile.txt", "wb");
    if (f == NULL) {
        printf("\nThere has been a problem saving your data.\n");
        return;
    }
    
    struct user *current = head;
    while (current != NULL) {
        fwrite(current, sizeof(struct user), 1, f);
        current = current->next;
    }
    
    fclose(f);
    printf("\nData Successfully Saved.\n");
}

// Read data from file
void read_from_file_ll(FILE *f) {
    f = fopen("UserDataFile.txt", "rb");
    if (f == NULL) {
        printf("\nError Reading File or file doesn't exist.\n");
        return;
    }
    
    struct user *new_node;
    int result;
    
    while (1) {
        new_node = (struct user*)malloc(sizeof(struct user));
        if (new_node == NULL) {
            printf("\nMemory allocation failed!\n");
            break;
        }
        
        result = fread(new_node, sizeof(struct user), 1, f);
        if (result == 0) {
            free(new_node);
            break;
        }
        
        // Display user information
        if (new_node->n_places_visited == 2) {
            printf("\n%s was last seen at:\n%s\n%s\n", 
                   new_node->name, new_node->location1, new_node->location2);
        } else if (new_node->n_places_visited == 1) {
            printf("\n%s was last seen at:\n%s\n", 
                   new_node->name, new_node->location1);
        } else {
            printf("\n%s was not found at any locations\n", new_node->name);
        }
        
        free(new_node);
    }
    
    fclose(f);
}

// Display all users and their locations
void display_users() {
    if (head == NULL) {
        printf("\nNo users in the system.\n");
        return;
    }
    
    struct user *current = head;
    printf("\n=== USER LIST ===\n");
    
    while (current != NULL) {
        printf("\nName: %s\n", current->name);
        if (current->n_places_visited == 0) {
            printf("Locations: None\n");
        } else if (current->n_places_visited == 1) {
            printf("Location: %s\n", current->location1);
        } else {
            printf("Locations: %s, %s\n", current->location1, current->location2);
        }
        current = current->next;
    }
}

// Check users at a specific location
void check_location(char *location) {
    struct user *current = head;
    int found = 0;
    
    printf("\nUsers found at location '%s':\n", location);
    
    while (current != NULL) {
        if ((current->n_places_visited >= 1 && strcmp(current->location1, location) == 0) ||
            (current->n_places_visited >= 2 && strcmp(current->location2, location) == 0)) {
            printf("- %s\n", current->name);
            found = 1;
        }
        current = current->next;
    }
    
    if (!found) {
        printf("No users found at this location.\n");
    }
}

int main() {
    int option;
    FILE *fp;
    char username[50];
    char place[50];
    
    printf("=== COVID CONTACT TRACING APP ===\n");
    
    do {
        printf("\n\nCOVID Tracing App Menu:\n");
        printf("1) Add user\n");
        printf("2) Add visit to venue\n");
        printf("3) Remove user\n");
        printf("4) Check users at a location\n");
        printf("5) Display all users\n");
        printf("6) Save to file\n");
        printf("7) Load data from file\n");
        printf("8) Exit\n");
        printf("\nEnter your choice: ");
        
        if (scanf("%d", &option) != 1) {
            // Clear the input buffer if scanf fails
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            printf("\nInvalid input! Please enter a number.\n");
            continue;
        }
        
        switch(option) {
            case 1:
                printf("\nEnter username: ");
                if (scanf("%s", username) == 1) {
                    insert_user_ll(username);
                } else {
                    printf("\nInvalid input!\n");
                }
                break;
                
            case 2:
                printf("\nEnter username to add location for: ");
                if (scanf("%s", username) != 1) {
                    printf("\nInvalid input!\n");
                    break;
                }
                
                struct user *tmp = head;
                int user_found = 0;
                
                while (tmp != NULL) {
                    if (strcmp(tmp->name, username) == 0) {
                        insert_visit_ll(tmp->name, tmp->n_places_visited, 
                                      tmp->location1, tmp->location2);
                        user_found = 1;
                        break;
                    }
                    tmp = tmp->next;
                }
                
                if (!user_found) {
                    printf("\nUser not found!\n");
                }
                break;
                
            case 3:
                printf("\nEnter user to remove: ");
                if (scanf("%s", username) == 1) {
                    remove_user_ll(username);
                } else {
                    printf("\nInvalid input!\n");
                }
                break;
                
            case 4:
                printf("\nEnter location to check: ");
                if (scanf("%s", place) == 1) {
                    check_location(place);
                } else {
                    printf("\nInvalid input!\n");
                }
                break;
                
            case 5:
                display_users();
                break;
                
            case 6:
                save_to_file_ll(fp);
                break;
                
            case 7:
                read_from_file_ll(fp);
                break;
                
            case 8:
                printf("\nExiting Application...\n");
                break;
                
            default:
                printf("\nInvalid option! Please try again.\n");
                break;
        }
    } while(option != 8);
    
    // Free remaining memory
    while (head != NULL) {
        struct user *temp = head;
        head = head->next;
        free(temp);
    }
    
    return 0;
}
