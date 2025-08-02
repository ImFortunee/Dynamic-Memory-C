
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

  
 
  struct user //struct for the linked list
  {
  char name[100];
  char location1[100];
  char location2[100];
  int n_places_visited;
  struct user *next;
};
struct user *head=0;
//struct for binary tree profile
struct user_bt
{char name[100];
int places[100];
int n_places_visited;
struct user_bt *left;
struct user_bt *right;
};
struct user_bt *root = 0;
//New user insertion into the linked list
void insert_user_ll(char name[100]);
//Inserts users in a linked list
{
    struct user *tmp, *new_node;
    new_node=(struct user*)malloc(sizeof(struct user));
    //New user is given memory
   strcpy(new_node->name, name);
   tmp = head;
   if(head==0 || (strcmp(head->name, new_node->name)>=0))
   {
     new_node->next= head;
     //connects user profile pointer to the first element of the linked list
    new_node->n_places_visited = 0;
    head = new_node;
    // The new user is now located at the top of the list
   }
   else 
   {
     while ((head->next !=0)||(strcmp (head->next->name, new_node)<0))
   {head = head->next;}
   new_node->next = head->next; 
   //new_node is now allocated to the next element in the linked list    
        new_node->n_places_visited = 0;
        head->next = new_node;
}
}

void remove_user_ll (char *name); // removes a user from the list
{
  struct user *tmp, *prev, *after;
  tmp = head;
  prev = 0
  after = head->next;

  while((strcmp(head->name, name)!=0)||(head !=0))
  {prev = head;
  head = head->next;
  after = head->next;
  }
  if (tmp==NULL) // If name is not found...
  {
    printf("\n Name not found, try again...");
  }
  else
  {
   prev->next = head->next;
   free(head); 
  }
  else 
  
  if ((head != 0)||(after == 0))
  {
    free(tmp);
  }
}


  void insert_visit_ll(char *name, int place_number, char place1[50], char place2[50])// inserts locations to a given user
  {
    int numblocat;
    
    printf("\n Choose the number of locations you would like to add - up to 2");
    scanf("%d", &numblocat);
    int x;
    x = numblocat - place_number;
    char place[100];
    if ((x>0)|| (x<3))
    {
      printf("\n Location of user: ");
      scanf("%s", &place[100]);
    if((numblocat-place_number)==2)
    {
      strcpy(place1, place);
    }
    else
    if ((numblocat-place_number)==1)
    {
      strcpy(place2, place);
    }
    }
    else
      {
       printf(" \n User not found, try again.");
     }
      }




  void save_to_file_ll(FILE *f) // This function will allow you to save the data entered into a file
  {
    struct user *tmp;
    f=fopen("UserDataFile.txt", "wb");
    tmp = head;
    if (f!=0)
    {
      for (tmp=head; head!=0; head=head->next)
      {
        fwrite(head, sizeof(struct user), 1, f);
      }
    
       printf("\n Data Successfully Saved.");
    }
    else
    {
      printf("\n There has been a problem saving your data.\n");
     }
    fclose(f);
  }
  void read_from_file_ll(FILE *f) // this function allows you to load the data from a file

  {
    int result;
    struct user *tmp, *new_node, *prev;
    prev = 0;
    new_node = (struct user*) malloc(sizeof(struct user));
   f = fopen("UserDataFile.txt", "rb");
   
   if (f != 0)
   {
     result = fread(new_node, sizeof(struct user), 1, f);
     while(result !=0)
     {
       if (new_node->n_places_visited == 2)
       {
         printf("\n %s was last seen at: \n %s \n %s", new_node->name, new_node->location2, new_node->location1);
       }
       else 
       if (new_node->n_places_visited == 1)
       {
         printf("\n %s was last seen at: \n %s", new_node->name, new_node->location1);
       }
       else
       if (new_node->n_places_visited ==0)
       {
         printf("\n %s was not found at any locations", new_node->name);
       }

       result = fread(new_node, sizeof(struct user), 1, f);
     }
     if (head == 0)
     {
       head = new_node;
       new_node->next=0;
     }
     else
     {
       tmp=head;
       if(strcmp(head->name, new_node->name)>=0)
       {
         head = new_node;
       new_node->next=head;
       }

       else
       {
         while((head !=0)||(strcmp(head->name, new_node->name)<0))
       {
         prev=head;
         head=head->next;
       }
       prev->next = new_node;
       new_node->next =head;
       }
     }
   }
   else
   {
     printf("\n Error Reading File");
   }
   fclose(f);
  }


int main()
{
  int option;
  FILE *fp;
  char username [50];
  char place[50];
  do{
  printf("\n COVID Tracing App Menu:\n\n 1)Introduc user \n\n 2) Introduce visit to venue\n\n 3) Remove user \n\n 4) Check which users have been in a particular place \n\n 5) Save to file \n\n 6) Retrieve data from file \n\n 7) Exit");
  scanf("%d", &option);
  switch(option)
  {
    case 1:
    printf("\n Username:");
    scanf("%s", &username[50]);
    insert_user_ll(username);

    break;

    case 2:
        printf("\n");
          struct user *tmp;
          tmp = head;
    printf("\n Who would you like to insert a Location for?");
    scanf("%s", &username[50]);
    
    if(strcmp(tmp->name, username)==0)
     {
       insert_visit_ll(tmp->name, tmp->n_places_visited, tmp->location1, tmp->location2);
         }
     else
      {
       while(strcmp(tmp->name, username)<0)
        {
          tmp=tmp->next;
         }
        insert_visit_ll(tmp->name, tmp->n_places_visited,tmp->location1, tmp->location2);
      }

      break;
  
     case 3:
     printf("\n\n Enter User you would like to remove:");
     scanf("%s", &username[50]);
     remove_user_ll(username);

     break;

     case 4:
    
     printf("\n\n Select the location at which you would like to check a user's presence");
     scanf("%s", &place[50]);

     break;

     case 5:
     save_to_file_ll(fp);
     printf("\n User Data Successfully saved");

     break;

     case 6:

     read_from_file_ll(fp);

     break;

     case 7:

     printf("\n Exiting Application...");

     break;


  }
}
  while(option !=7);
  return 0;
}
