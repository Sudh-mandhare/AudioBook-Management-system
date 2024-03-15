#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LEN 100
typedef enum{Failure,Success} status_code;          //%30s

typedef struct User_tag
{
    int user_id;
    char name[100];
    char email[100];
    char narrator_preference[100];
    char author_preference[100];
    char genre_preference[100];
    struct  User_tag *next;
    struct Audio_book_tag *child;
        
}User;
 

typedef struct Audio_book_tag
{
    int audio_id;
    char title[100];
    char author[100];
    char narrator[100];
    int duration;
    char genre[100];
    float rating;
    int rate_count;
    int timestamp;  //let it only be in minutes as of now
    struct Audio_book_tag *child;
    
}Audio;

typedef struct Audio_list_tag
{
    int audio_id;
    char title[100];
    char author[100];
    char narrator[100];
    int duration;
    char genre[100];
    float rating;
    int rate_count;

    struct Audio_list_tag *next;
    
}Audio_list;


status_code updateAudiobookFile(Audio_list *head_ptr) {
    status_code sc = Success;
    FILE *file = fopen("audiobook.txt", "w"); // overwrite existing content
    if (file == NULL) {
        perror("Error opening file");
        sc = Failure;
    }

    else
    {
        Audio_list *ptr = head_ptr;
        while (ptr != NULL) {
            fprintf(file, "%d %s %s %s %d %s %.2f %d\n", 
                    ptr->audio_id, ptr->title, ptr->author, ptr->narrator, ptr->duration, ptr->genre, ptr->rating,ptr ->rate_count);
            ptr = ptr->next;
        }

        
    }
    fclose(file);
    
    return sc;
}

status_code updateAudiobookFileRate(Audio_list *head_ptr,float new_rate,int new_count,int audio_id) {
    status_code sc = Success;
    FILE *file = fopen("audiobook.txt", "w"); // overwrite existing content
    if (file == NULL) {
        perror("Error opening file");
        sc = Failure;
    }

    else
    {
        Audio_list *ptr = head_ptr;
        while (ptr != NULL) 
        {
            if(ptr ->audio_id == audio_id)
            {
                fprintf(file, "%d %s %s %s %d %s %.2f %d\n", ptr->audio_id, ptr->title, ptr->author, ptr->narrator, ptr->duration, ptr->genre,new_rate,new_count);
            }
            else
            {
                fprintf(file, "%d %s %s %s %d %s %.2f %d\n", ptr->audio_id, ptr->title, ptr->author, ptr->narrator, ptr->duration, ptr->genre, ptr->rating,ptr ->rate_count);
            }
            
            ptr = ptr->next;
        }

        
    }
    fclose(file);
    
    return sc;
}

status_code updateUserFile(User *head_ptr) {
    status_code sc = Success;
    FILE *file = fopen("users.txt", "w"); // overwrite existing content
    if (file == NULL) 
    {
        perror("Error opening file");
        sc = Failure;
    }
    else 
    {
        User *ptr = head_ptr;
        while (ptr != NULL) 
        {
            fprintf(file, "%d %s %s %s %s %s\n",ptr->user_id, ptr->name, ptr->email, ptr->narrator_preference, ptr->author_preference, ptr->genre_preference);
            ptr = ptr->next;
        }
    }
    fclose(file);
    return sc;
}

status_code Add_audiobook(Audio_list *head_ptr)
{
    status_code sc = Success;
    Audio_list *ptr = head_ptr;
    Audio_list *prev = NULL;

    printf("ENter the following inputs \n");
    int audio_id;
    printf("\nAudio book id : ");
    scanf("%d",&audio_id);

    char title[MAX_LINE_LEN];
    printf("\nAudio book title : ");
    scanf("%s",&title);

    char author[MAX_LINE_LEN];
    printf("\nAudiobook author : ");
    scanf("%s",&author);

    char narrator[MAX_LINE_LEN];
    printf("\nAudiobook narrator : ");
    scanf("%s",&narrator);

    int dur;
    printf("\nAudiobook duration : ");
    scanf("%d",&dur);

    char genre[MAX_LINE_LEN];
    printf("\nAudio book genre : ");
    scanf("%s",genre);

    float rating = 0.0;
    

    int rate_count = 0;

    if(head_ptr == NULL)
    {
        sc = Failure;
    }
    else
    {
        while(ptr != NULL && ptr -> audio_id < audio_id )
        {
            prev = ptr;
            ptr = ptr -> next;

        }
        if(ptr == NULL || ptr ->audio_id != audio_id)
        {
            //add new 
            Audio_list*new_aptr = (Audio_list *)malloc(sizeof(Audio_list));
            new_aptr -> audio_id = audio_id;
            strcpy(new_aptr -> title,title);
            strcpy(new_aptr -> author, author);
            strcpy(new_aptr -> narrator, narrator);
            new_aptr -> duration = dur;
            strcpy(new_aptr -> genre, genre);
            new_aptr -> rating = rating;
            new_aptr ->rate_count = rate_count;
            

            new_aptr -> next = ptr;
            prev -> next = new_aptr;
        }
        else
        {
            //edit old
            ptr ->audio_id = audio_id;
            strcpy(ptr -> title , title);
            strcpy(ptr -> author , author);
            strcpy(ptr -> narrator , narrator);
            ptr -> duration = dur;
            strcpy(ptr -> genre , genre);
            ptr -> rating = rating;
            ptr -> rate_count = 0;
            
        }
    }
    
    status_code sc1 = updateAudiobookFile(head_ptr);
    if(sc1 == Success)
    {
        printf("\n updated in audiobook.txt as well \n");
    }
    else
    {
        printf("\n Failed to update \n");
    }

    
    return sc;
}

Audio_list *Delete_audiobook(Audio_list *head_ptr)
{
    int criteria_no;
    printf(" 1.audio_book_id \n 2.title \n 3.Author \n 4.Narrator \n 5.Duration \n 6.Genre \n 7. Rating \n");
    printf("Enter your choice : ");
    scanf("%d", &criteria_no);
    
    Audio_list *ptr = head_ptr;
    Audio_list *prev = NULL;

    if (criteria_no == 1 || criteria_no == 5 || criteria_no == 7) 
    {
        int check_val;
        printf("Enter the value: ");
        scanf("%d", &check_val);

        while (ptr != NULL) 
        {
            if ((criteria_no == 1 && ptr->audio_id == check_val) || (criteria_no == 5 && ptr->duration == check_val) || (criteria_no == 7 && ptr->rating == check_val)) 
            {
                // Node matches the criteria, delete it
                if (ptr == head_ptr)
                {
                    head_ptr = ptr->next;
                    free(ptr);
                    ptr = head_ptr;
                } 
                else 
                {
                    prev->next = ptr->next;
                    free(ptr);
                    ptr = prev->next;
                }
                printf("Audiobook deleted\n");
            } 
            else 
            {
                prev = ptr;
                ptr = ptr->next;
            }
        }
    } 
    
    else 
    {
        char check[100];
        printf("Enter the check string: ");
        scanf("%s", check);

        while (ptr != NULL) {
            int cmp_result = 0;
            if (criteria_no == 2)
            {
                cmp_result = strcmp(ptr->title, check);
            }
                
            else if (criteria_no == 3)
            {
                cmp_result = strcmp(ptr->author, check);
            }
                
            else if (criteria_no == 4)
            {
                cmp_result = strcmp(ptr->narrator, check);
            }
                
            else if (criteria_no == 6)
            {
                cmp_result = strcmp(ptr->genre, check);
            }
                

            if (cmp_result == 0) 
            {
                // Node matches the criteria, delete it
                if (ptr == head_ptr) 
                {
                    head_ptr = ptr->next;
                    free(ptr);
                    ptr = head_ptr;
                } 
                else
                {
                    prev->next = ptr->next;
                    free(ptr);
                    ptr = prev->next;
                }
                printf("Audiobook deleted\n");
            }
            else
            {
                prev = ptr;
                ptr = ptr->next;
            }
        }
    }

    

    
    status_code sc1 = updateAudiobookFile(head_ptr);
    if(sc1 == Success)
    {
        printf("\n updated in audiobook.txt as well \n");
    }
    else
    {
        printf("\n Failed to update \n");
    }

    printf("Audio_book deleted successfully \n");

    
    return head_ptr;
}

status_code Search_audiobook(Audio_list *head_ptr)
{
    Audio_list* ptr = head_ptr;
    status_code sc = Success;
    int criteria_no;
    printf(" 1.audio_book_id \n 2.title \n 3.Author \n 4.Narrator \n 5.Duration \n 6.Genre \n 7. Rating \n");
    printf("enter your choice : ");
    scanf("%d",&criteria_no);

    if (criteria_no == 1 || criteria_no == 5) {
    int check_val;
    printf("Enter the value: ");
    scanf("%d", &check_val);
    int flag = 0;
    int i = 1;
    
    char a[MAX_LINE_LEN] = "AUDIO ID";
    char b[MAX_LINE_LEN] = "TITLE";
    char c[MAX_LINE_LEN] = "AUTHOR";
    char d[MAX_LINE_LEN] = "NARRATOR";
    char e[MAX_LINE_LEN] = "GENRE";
    char f[MAX_LINE_LEN] = "RATE COUNT";
    char g[MAX_LINE_LEN] = "OVERALL RATING";
    char h[MAX_LINE_LEN] = "LENGTH(minutes)";
    

    printf("%-10s\t%-20s\t%-20s\t%-20s\t%-20s\t%-10s\t%-10s\t%-20s\n\n", a, b, c, d, e, f, g, h);
    while (ptr != NULL) {
        int cmp = 0;
        
        if (criteria_no == 1 && ptr->audio_id == check_val) 
        {
            cmp = 1;
        }
        
        else if (criteria_no == 5 && ptr->duration == check_val) 
        {
            cmp = 1;
        }
        
        if (cmp == 0) 
        {
            ptr = ptr->next;
        } 
        else 
        {
            printf("%-10d\t%-20s\t%-20s\t%-20s\t%-20s\t%-10d\t%-10f\t%-20d\n",ptr->audio_id, ptr->title, ptr->author, ptr->narrator,ptr->genre, ptr->rate_count, ptr->rating, ptr->duration);
            // printf("Match no. %d\n", i);
            // printf("Audio_book number: %d\n", ptr->audio_id);
            // printf("Title: %s\n", ptr->title);
            // printf("Author: %s\n", ptr->author);
            // printf("Narrator: %s\n", ptr->narrator);
            // printf("Duration: %d\n", ptr->duration);
            // printf("Genre: %s\n", ptr->genre);
            // printf("Rating: %f\n", ptr->rating);
            // printf("Number of ratings: %d\n", ptr->rate_count);
            
            flag = 1;
            ptr = ptr->next;
        }

        // Check if no match is found and if we have reached the end of the list
        if (ptr == NULL && flag == 0) {
            printf("No such element found\n");
            sc = Failure;
        }

        i++;
    }
}

    else if(criteria_no == 7)
    {
        float check_val;
        printf("Enter the value :");
        scanf("%f",&check_val);
        int flag = 0;
        int i = 1;
        while(ptr != NULL)
        {

            while(ptr != NULL && ptr -> rating != check_val )
            {
                ptr = ptr -> next;
            }

            if(ptr == NULL && flag == 0)
            {
                printf("No such element found \n");
                sc = Failure;
            }
            
            else
            {
                
                printf("%-10d\t%-20s\t%-20s\t%-20s\t%-20s\t%-10d\t%-10f\t%-20d\n",ptr->audio_id, ptr->title, ptr->author, ptr->narrator,ptr->genre, ptr->rate_count, ptr->rating, ptr->duration);
                // printf("Match no. %d \n",i);
                // printf("Audio_book number : %d \n",ptr -> audio_id);
                // printf("Title : %s \n",ptr -> title);
                // printf("Author : %s \n",ptr -> author);
                // printf("Narrator : %s \n",ptr -> narrator);
                // printf("Duration : %d \n",ptr -> duration);
                // printf("Genre : %s \n",ptr -> genre);
                // printf("Rating : %f \n",ptr -> rating);
                // printf("Number of ratings : %d \n",ptr ->rate_count);
                
                
                flag = 1;

                ptr = ptr -> next;
            }

            i++;

        }
    }
    else
    {
        char check[100]; 
        printf("Enter the check string :");
        scanf("%s",check);
        int flag = 0;
        int i = 1;
        while(ptr != NULL)
        {
            
            int cmp_result = 0;
            if (criteria_no == 2)
            {
                cmp_result = strcmp(ptr->title, check);
            }
                
            else if (criteria_no == 3)
            {
                cmp_result = strcmp(ptr->author, check);
            }
                
            else if (criteria_no == 4)
            {
                cmp_result = strcmp(ptr->narrator, check);
            }
                
            else if (criteria_no == 6)
            {
                cmp_result = strcmp(ptr->genre, check);
            }
            

            if(cmp_result == 0)
            {
                printf("%-10d\t%-20s\t%-20s\t%-20s\t%-20s\t%-10d\t%-10f\t%-20d\n",ptr->audio_id, ptr->title, ptr->author, ptr->narrator,ptr->genre, ptr->rate_count, ptr->rating, ptr->duration);
                // printf("\n");
                // printf("Match no. %d \n",i);
                // printf("Audio_book number : %d \n",ptr -> audio_id);
                // printf("Title : %s \n",ptr -> title);
                // printf("Author : %s \n",ptr -> author);
                // printf("Narrator : %s \n",ptr -> narrator);
                // printf("Duration : %d \n",ptr -> duration);
                // printf("Genre : %s \n",ptr -> genre);
                // printf("Rating : %f \n",ptr -> rating);
                // printf("Number of Ratings : %d \n",ptr -> rate_count);
                // printf("\n");

            }
            i++;

            ptr = ptr -> next;
        }

        
    }

    return sc;
}

status_code Add_user_profile(Audio_list* audio_head,User* user_head)
{
    printf("Ener new user Details : \n");   //,"Sudhanshu","sudhmandh@example.com","Somebody","kalam","Horror"

    char name[MAX_LINE_LEN];
    char email[MAX_LINE_LEN];
    char narrator_preference[MAX_LINE_LEN];
    char author_preference[MAX_LINE_LEN];
    char genre_preference[MAX_LINE_LEN];

    printf("Enter name : ");
    scanf("%s",name);
    printf("Enter email : ");
    scanf("%s",email);
    printf("Enter narrator_preference : ");
    scanf("%s",narrator_preference);
    printf("Enter author_preference : ");
    scanf("%s",author_preference);
    printf("Enter genre_preference : ");
    scanf("%s",genre_preference);

    User *prev = NULL;
    status_code sc = Success;
    User *ptr = user_head;
    int flag = 0;
    while(ptr != NULL && flag == 0)
    {
        prev = ptr;
        if(strcmp(ptr -> email,email) == 0)
        {
            flag = 1;
        }
        ptr = ptr -> next;
    }

    if(flag == 1)
    {
        sc = Failure;
    }
    else
    {
        int new_id = (prev ->user_id) + 1;

        User *new_ptr = (User*)malloc(sizeof(User));
        if(new_ptr == NULL) 
        {
            sc = Failure;
        }
        else 
        {
            new_ptr->user_id = new_id;
            strcpy(new_ptr->name , name);
            strcpy(new_ptr->email , email);
            strcpy(new_ptr->narrator_preference , narrator_preference);
            strcpy(new_ptr->author_preference , author_preference);
            strcpy(new_ptr->genre_preference, genre_preference);
            
            // Initialize child pointer to NULL
            new_ptr->child = NULL;

            // If the list is empty, new_ptr becomes the head
            if (prev == NULL) {
                new_ptr->next = ptr;
                user_head = new_ptr; // Update head_ptr
            }
            else {
                prev->next = new_ptr;
                new_ptr->next = ptr;
            }

            Audio_list* audio_ptr = audio_head;
            while(audio_ptr != NULL) {
                if(strcmp(audio_ptr->narrator, new_ptr->narrator_preference) == 0 || strcmp(audio_ptr->author, new_ptr->author_preference) == 0 || strcmp(audio_ptr->genre, new_ptr->genre_preference) == 0) 
                {
                    printf("Appending children \n");
                    Audio *newa_ptr = (Audio *)malloc(sizeof(Audio));
                    // Copying data from audio_ptr to newa_ptr
                    newa_ptr->audio_id = audio_ptr->audio_id;
                    strcpy(newa_ptr->title, audio_ptr->title);
                    strcpy(newa_ptr->author, audio_ptr->author);
                    strcpy(newa_ptr->narrator, audio_ptr->narrator);
                    strcpy(newa_ptr->genre, audio_ptr->genre);
                    newa_ptr->duration = audio_ptr->duration;
                    newa_ptr->rating = audio_ptr->rating;
                    newa_ptr->rate_count = audio_ptr ->rate_count;
                    newa_ptr->timestamp = 0;
                    newa_ptr->child = NULL;

                    // Append newa_ptr to the user's child list
                    if (new_ptr->child == NULL) 
                    {
                        new_ptr->child = newa_ptr;
                    }
                    else 
                    {
                        // Traverse to the end of the child list and append newa_ptr
                        Audio *temp = new_ptr->child;
                        while (temp->child != NULL) {
                            temp = temp->child;
                        }
                        temp->child = newa_ptr;
                    }
                }
                audio_ptr = audio_ptr->next;
            }
        }
    }
    
    status_code sc1 = updateUserFile(user_head);
    if(sc1 == Success)
    {
        printf("User.txt updated successfully \n");
    }
    else
    {
        printf("Failed to update users.txt \n");
    }
    
    return sc;
}

status_code Add_to_UserLibrary(User* user_head,Audio_list *audio_head)
{
    printf("Enter user id : ");
    int uid;
    scanf("%d",&uid);

    printf("Enter audio book id : ");
    int aid;
    scanf("%d",&aid);

    int choice ;
    printf("What task do you want to perform \n 1.Add Audiobook \n 2. Delete Audiobook \n Enteryour choice : ");
    scanf("%d",&choice);

    status_code sc = Success;

    User *uptr = user_head;
    while(uptr != NULL && uptr -> user_id != uid)
    {
        uptr = uptr -> next;
    }
    if(uptr == NULL)
    {
        sc = Failure;
    }
    else
    {
        if (choice == 2)
        {
            Audio *aptr = uptr -> child;
            Audio *prev = NULL;
            while(aptr != NULL && aptr ->audio_id != aid)
            {
                prev =aptr;
                aptr = aptr -> child;
            }

            if(aptr == NULL)
            {
                sc = Failure;
            }
            else
            {
                prev -> child = aptr -> child;
                free(aptr);
                aptr = NULL;
            }
        }
        else if(choice == 1)
        {
            Audio_list* alptr = audio_head;
            int i = 1;

            while(alptr != NULL && alptr ->audio_id != aid)
            {
                
                printf("Entered alptr while ID : %d \n",i);
                alptr = alptr -> next;
                i++;
            }

            if(alptr == NULL)
            {
                sc = Failure;
            }
            else
            {
                printf("Entered new malloc \n");
                Audio *new_ptr = (Audio *)malloc(sizeof(Audio));

                new_ptr ->audio_id = alptr ->audio_id;
                strcpy(new_ptr ->author,alptr->author);
                strcpy(new_ptr ->title,alptr->title);
                strcpy(new_ptr ->narrator,alptr->narrator);
                strcpy(new_ptr ->genre,alptr->genre);
                new_ptr ->duration = alptr ->duration;
                new_ptr ->rating = alptr ->rating;
                new_ptr ->rate_count = alptr ->rate_count;
                new_ptr ->timestamp = 0;


                Audio *aptr = uptr -> child;
                Audio *prev = NULL;
                while(aptr != NULL && aptr ->audio_id < aid)
                {
                    prev = aptr;
                    aptr = aptr -> child;
                }

               
                // as only adding thus will never be unsuccessful
                prev -> child = new_ptr;
                new_ptr -> child = aptr;


            


            }
        }
        else
        {
            printf("\n Enter correct choice !!! \n");
        }

       
        
        
    }

    
    return sc;
}

    
status_code Listening_progress(User* user_head)
{
    status_code sc = Success;
    int uid;
    int aid;
    printf("Enter the user id : ");
    scanf("%d",&uid);
    printf("Enter the audio id : ");
    scanf("%d",&aid);

    

    User* user_traverse = user_head;
    while(user_traverse != NULL&&user_traverse -> user_id != uid)
    {
        user_traverse = user_traverse -> next;
    }
    if(user_traverse == NULL)
    {
        sc = Failure;
        printf("Inside no such User found \n");
    }
    else
    {   
        Audio *audio_traverse = user_traverse -> child;
        while(audio_traverse != NULL &&audio_traverse -> audio_id != aid)
        {
            audio_traverse = audio_traverse -> child;
        }
        if(audio_traverse == NULL)
        {
            sc = Failure;
            printf("Inside audio_traverse is null i.e no such element found \n");
        }
        else
        {
            printf("Total duration of this audiobook is : %d",audio_traverse ->duration);

            int timestmp;
            printf("Enter the timestamp : ");
            scanf("%d",&timestmp);
            audio_traverse -> timestamp = timestmp;
        }
    }

    return sc;
    

}
    
typedef struct Hash
{
    int timestamp;
    Audio *ptr;
    struct Hash *next;
}Hash;


Hash* Merge(Hash* lptr1, Hash* lptr2) {
    Hash* result,*ptr1,*ptr2,*tail;
    result = NULL;
    tail = NULL;
    if(lptr1 == NULL)
    {
        result = lptr2;
    }
    else if(lptr2 == NULL)
    {
        result = lptr1;
    }
    else
    {
        ptr1 = lptr1;
        ptr2 = lptr2;

        if(lptr1 ->timestamp < lptr2 ->timestamp)
        {
            result = lptr1;
            ptr1 = ptr1 -> next;
        }
        else
        {
            result = lptr2;
            ptr2 = ptr2 -> next;
        }

        tail = result;

        while(ptr1 != NULL && ptr2 != NULL)
        {
            if(ptr1 -> timestamp < ptr2 -> timestamp)
            {
                tail -> next = ptr1;
                ptr1 = ptr1 -> next;
                tail = tail -> next;
            }
            else
            {
                tail -> next = ptr2;
                ptr2 = ptr2 -> next;
                tail = tail -> next;
            }
        }

        if(ptr1 != NULL)
        {
            tail -> next = ptr1;
        }
        else
        {
            tail -> next = ptr2;
        }
        return result;
    }
}

// Function to split the linked list into two halves
Hash* Divide(Hash* lptr) 
{
    Hash* slow = lptr;
    Hash* fast = lptr->next;
    while(fast != NULL && fast -> next != NULL)
    {
        //printf("r");
        slow = slow -> next;
        fast = fast -> next -> next;
    }
    Hash* ret_ptr = slow->next;
    slow ->next = NULL;
    return ret_ptr;
}

// Merge sort function
Hash* Merge_sort(Hash* lptr) {
    Hash*head = lptr;
    Hash*ptr;

    // Base case
    if (head != NULL && head->next != NULL)
    {
        //printf("after divide \n");
        ptr = Divide(lptr); //pointer of right side
        lptr = Merge_sort(lptr);
        //printf("After left sort \n");
        ptr = Merge_sort(ptr);
        //printf("After right sort \n");
        head = Merge(lptr,ptr);
    }

    return head;
        

}

status_code Display_user_libraries(User* user_head)
{

    status_code sc = Success;

    int uid;
    printf("Enter the user id : ");
    scanf("%d",&uid);

    int criteria_no;
    printf("Select the filter criteria you want \n 1.All \n 2.genre \n 3.author \n 4.Narrator \n 5.Rating \n");
    printf("Enter your choice :");
    scanf("%d",&criteria_no);

    User *user_ptr = user_head;
    Audio *audio_ptr,*audio_ptr_head;
    
    
    Hash *Dummy_hash_head = (Hash*)malloc(sizeof(Hash));
    Hash *prev = Dummy_hash_head;


    if (criteria_no == 1)
    {
        
    
        while(user_ptr -> user_id != uid)
        {
            user_ptr = user_ptr -> next;
        }

        audio_ptr = user_ptr -> child;
        audio_ptr_head = audio_ptr;
        int i = 1;
        while(audio_ptr != NULL)
        {
            printf("count while : %d \n",i);
            Hash *hash_ptr = (Hash *)malloc(sizeof(Hash));
            hash_ptr ->timestamp = audio_ptr -> timestamp;
            hash_ptr -> ptr = audio_ptr;
            prev -> next = hash_ptr;
            hash_ptr -> next = NULL;
            prev = hash_ptr;
            audio_ptr = audio_ptr -> child;
        }
    }
    else if(criteria_no == 2)
    {
        char genre[MAX_LINE_LEN];
        printf("Enter genre : ");
        scanf("%s",genre);

        while(user_ptr -> user_id != uid)
        {
            user_ptr = user_ptr -> next;
        }

        audio_ptr = user_ptr -> child;
        audio_ptr_head = audio_ptr;
        int i = 1;
        while(audio_ptr != NULL)
        {
            if(strcmp(audio_ptr -> genre,genre) == 0)
            {
                printf("count while : %d \n",i);
                Hash *hash_ptr = (Hash *)malloc(sizeof(Hash));
                hash_ptr ->timestamp = audio_ptr -> timestamp;
                hash_ptr -> ptr = audio_ptr;
                prev -> next = hash_ptr;
                hash_ptr -> next = NULL;
                prev = hash_ptr;
                audio_ptr = audio_ptr -> child;
            }
            
        }
    }
    else if(criteria_no == 3)
    {
        char author[MAX_LINE_LEN];
        printf("Enter author name : ");
        scanf("%s",author);

        while(user_ptr -> user_id != uid)
        {
            user_ptr = user_ptr -> next;
        }

        audio_ptr = user_ptr -> child;
        audio_ptr_head = audio_ptr;
        int i = 1;
        while(audio_ptr != NULL)
        {
            if(strcmp(audio_ptr -> author,author) == 0)
            {
                printf("count while : %d \n",i);
                Hash *hash_ptr = (Hash *)malloc(sizeof(Hash));
                hash_ptr ->timestamp = audio_ptr -> timestamp;
                hash_ptr -> ptr = audio_ptr;
                prev -> next = hash_ptr;
                hash_ptr -> next = NULL;
                prev = hash_ptr;
                audio_ptr = audio_ptr -> child;
            }
            
        }
    }
    else if(criteria_no == 4)
    {
        char narrator[MAX_LINE_LEN];
        printf("Enter narrator name : ");
        scanf("%s",narrator);

        while(user_ptr -> user_id != uid)
        {
            user_ptr = user_ptr -> next;
        }

        audio_ptr = user_ptr -> child;
        audio_ptr_head = audio_ptr;
        int i = 1;
        while(audio_ptr != NULL)
        {
            if(strcmp(audio_ptr -> author,narrator) == 0)
            {
                printf("count while : %d \n",i);
                Hash *hash_ptr = (Hash *)malloc(sizeof(Hash));
                hash_ptr ->timestamp = audio_ptr -> timestamp;
                hash_ptr -> ptr = audio_ptr;
                prev -> next = hash_ptr;
                hash_ptr -> next = NULL;
                prev = hash_ptr;
                audio_ptr = audio_ptr -> child;
            }
            
        }
    }
    else if(criteria_no == 5)
    {
        int rating;
        printf("Enter rating : ");
        scanf("%f",&rating);

        while(user_ptr -> user_id != uid)
        {
            user_ptr = user_ptr -> next;
        }

        audio_ptr = user_ptr -> child;
        audio_ptr_head = audio_ptr;
        int i = 1;
        while(audio_ptr != NULL)
        {
            if(audio_ptr ->rating == rating)
            {
                printf("count while : %d \n",i);
                Hash *hash_ptr = (Hash *)malloc(sizeof(Hash));
                hash_ptr ->timestamp = audio_ptr -> timestamp;
                hash_ptr -> ptr = audio_ptr;
                prev -> next = hash_ptr;
                hash_ptr -> next = NULL;
                prev = hash_ptr;
                audio_ptr = audio_ptr -> child;
            }
            
        }
    }

    
    
        //merge sort function
        printf("Before sort function \n");
        Hash *ret_head = Merge_sort(Dummy_hash_head ->next);

        char a[MAX_LINE_LEN] = "AUDIO ID";
        char b[MAX_LINE_LEN] = "TITLE";
        char c[MAX_LINE_LEN] = "AUTHOR";
        char d[MAX_LINE_LEN] = "NARRATOR";
        char e[MAX_LINE_LEN] = "GENRE";
        char f[MAX_LINE_LEN] = "RATE COUNT";
        char g[MAX_LINE_LEN] = "OVERALL RATING";
        char h[MAX_LINE_LEN] = "LENGTH(minutes)";
        char i[MAX_LINE_LEN] = "Time listened";

        printf("%-10s\t%-20s\t%-20s\t%-20s\t%-20s\t%-10s\t%-10s\t%-20s\t%-20s\n\n", a, b, c, d, e, f, g, h, i);

        if(ret_head == NULL)
        {
            printf("NULL");
        }

        printf("After Merge Sort \n");

        while(ret_head != NULL)
        {
            printf("inside   \n");

            printf("%-10d\t%-20s\t%-20s\t%-20s\t%-20s\t%-10d\t%-10f\t%-20d\t%-20d\n",audio_ptr->audio_id, audio_ptr->title, audio_ptr->author, audio_ptr->narrator,audio_ptr->genre, audio_ptr->rate_count, audio_ptr->rating, audio_ptr->duration, audio_ptr->timestamp);
            audio_ptr = ret_head ->ptr;
            // printf("Audio id: %d \n",audio_ptr ->audio_id);
            // printf("Title : %s \n",audio_ptr ->title);
            // printf("Author : %s \n",audio_ptr ->author);
            // printf("Narrator : %s \n",audio_ptr ->narrator);
            // printf("Genre : %s \n",audio_ptr ->genre);
            // printf("Rating : %f \n",audio_ptr ->rating);
            // printf("Rate Count : %d \n",audio_ptr ->rate_count);
            // printf("Timestamp : %d \n",audio_ptr ->timestamp);
            // printf("Duration : %d \n",audio_ptr ->duration);
            
            ret_head = ret_head -> next;
        }
    
    return sc;
}

status_code Rate_Audiobook(User* user_head,Audio_list *audio_head)
{
    int uid,aid,u_rating;
    printf("Enter the user-id : ");
    scanf("%d",&uid);
    printf("\n Enter the corresponding audiobook id : ");
    scanf("%d",&aid);
    printf("\n Enter the rating : ");
    scanf("%f",&u_rating);

    status_code sc = Success;

    User *uptr = user_head;
    Audio *aptr;
    while(uptr != NULL && uptr ->user_id != uid)
    {
        uptr = uptr -> next;
    }
    if(uptr == NULL)
    {
        sc = Failure;
    }
    else
    {
        aptr = uptr ->child;
        while(aptr != NULL && aptr -> audio_id != aid)
        {
            aptr = aptr -> child;
        }
        if(aptr == NULL )
        {
            sc = Failure;
        }
        else
        {
            float new_rating;
            int new_rate_count = aptr ->rate_count + 1;
            new_rating = ((aptr ->rating * aptr ->rate_count) + u_rating)/(new_rate_count);
            
            aptr ->rate_count = new_rate_count;
            aptr ->rating = new_rating;

            //now update every where

            // 1 => in file 
            printf("rate value : %f",new_rating);
            status_code sc1 = updateAudiobookFileRate(audio_head,new_rating,new_rate_count,aid);
            if(sc1 == Success)
            {
                printf("\n updated in audiobook.txt as well \n");
            }
            else
            {
                printf("\n Failed to update \n");
            }

            // update for al users

            User *uptr = user_head;
            Audio *aptr;

            while(uptr != NULL)
            {
                aptr = uptr -> child;

                while(aptr != NULL)
                {
                    if(aptr -> audio_id == aid)
                    {
                        aptr -> rating = new_rating;
                        aptr -> rate_count = new_rate_count;
                    }
                    aptr = aptr -> child;
                }

                uptr = uptr -> next;
            }

            printf("Updated everywhere succesfully \n");
        }
    }
    return sc;
}

status_code Most_poplular_audiobook(Audio_list *audio_head) // need to complete
{
    status_code sc = Success ;
    Audio_list *ab_ptr = audio_head;
    Audio_list *most_poplular_ab;
    float most_popular = 0.0;
    float curr = 0.0;
    int non_zero_rating = 0;
    while (ab_ptr != NULL )
    {
        curr = ab_ptr->rating;
        if (most_popular < curr)
        {
            most_popular = curr;
            most_poplular_ab = ab_ptr;
        }
        if (ab_ptr->rating > 0.0)
        {
            non_zero_rating = 1;
        }
        ab_ptr = ab_ptr->next;
    }
    if (non_zero_rating == 0)
    {
        printf("No ratings are available to determine popularity.\n");
        sc = Failure;
    }
    else
    {
        ab_ptr = audio_head;
        int i = 1;
        while (ab_ptr!=NULL)
        {
            if(ab_ptr->rating == most_popular)
            {

                // printf("Count : %d",i++);
                printf("\n \nDetails of most popular audiobook are\n");
                printf("Title  : %s\n", ab_ptr->title);
                printf("Author  : %s\n", ab_ptr->author);
                printf("Avg rating  : %f\n", ab_ptr->rating);
            }
            ab_ptr = ab_ptr->next;
        }
    }
    return sc;
}


status_code Listening_history_report_user(User* user_head)
{
    int uid;
    status_code sc = Success;
    printf("Enter the user-id you want report for : ");
    scanf("%d",&uid);

    User*uptr = user_head;
    while(uptr != NULL && uptr -> user_id != uid)
    {
        uptr = uptr -> next;
    }
    if(uptr == NULL)
    {
        sc = Failure;
    }
    else
    {
        char a[MAX_LINE_LEN] = "AUDIO ID";
        char b[MAX_LINE_LEN] = "TITLE";
        char c[MAX_LINE_LEN] = "AUTHOR";
        char d[MAX_LINE_LEN] = "NARRATOR";
        char e[MAX_LINE_LEN] = "GENRE";
        char f[MAX_LINE_LEN] = "RATE COUNT";
        char g[MAX_LINE_LEN] = "OVERALL RATING";
        char h[MAX_LINE_LEN] = "LENGTH(minutes)";
        char i[MAX_LINE_LEN] = "Time listened";
        
        Audio *aptr;
        aptr = uptr -> child;
        int total_time = 0;
        printf("Listening History Report \n ");

        printf("%10s\t%20s\t%20s\t%20s\t%20s\t%10s\t%10s\t%20s\t%20s\n\n",a,b,c,d,e,f,g,h,i);

        while(aptr != NULL)
        {
            printf("%10d\t%20s\t%20s\t%20s\t%20s\t%10f\t%10f\t%20d\t%20d\n",aptr ->audio_id,aptr ->title,aptr ->author,aptr->narrator,aptr->genre,aptr->rate_count,aptr->rating,aptr->duration,aptr ->timestamp);
            total_time = total_time + aptr->timestamp;
            aptr = aptr -> child;
        }
        

        printf("Total Listened Time : %d",total_time);
    }
    return sc;
}

Audio* Merge_title(Audio *lptr1,Audio *lptr2)
{
    Audio *ptr1,*ptr2,*tail,*result;
    tail = NULL;
    result = NULL;

    if(lptr1 == NULL)
    {
        result = lptr1;
    }
    else if(lptr2 == NULL)
    {
        result = lptr2;
    }
    else
    {
        ptr1 = lptr1;
        ptr2 = lptr2;

        if(strcmp(lptr1 -> title,lptr2 -> title) < 0 || (strcmp(lptr1 -> title,lptr2 -> title) == 0 && strcmp(lptr1 -> author,lptr2 -> author) < 0))
        {
            result = lptr1;
            ptr1 = ptr1 -> child;
        }
        else 
        {
            result = lptr2;
            ptr2 = ptr2 -> child;
        }
        tail = result;

        while(ptr1 != NULL && ptr2 != NULL)
        {
            if(strcmp(lptr1 -> title,lptr2 -> title) < 0 || (strcmp(lptr1 -> title,lptr2 -> title) == 0 && strcmp(lptr1 -> author,lptr2 -> author) < 0))
            {
                tail -> child = ptr1;
                ptr1 = ptr1 -> child;
                tail = tail -> child;
            }
            else
            {
                tail -> child = ptr2;
                ptr2 = ptr2 -> child;
                tail = tail -> child;
            }
        }

        if(ptr1 != NULL)
        {
            tail -> child = ptr1;
        }
        else
        {
            tail -> child = ptr2;
        }

        return result;

    }
}

Audio* Divide_title(Audio *lptr)
{
    Audio *fast,*slow,*ptr;
    slow = lptr;
    fast = lptr -> child;

    while(fast != NULL && fast -> child != NULL)
    {
        slow = slow -> child;
        fast = fast -> child -> child;
    }
    ptr = slow -> child;
    slow -> child = NULL;

    return ptr;
}

Audio* Merge_sort_title(Audio *lptr)
{
    Audio *head_ptr = lptr;
    Audio *ptr;

    if((lptr != NULL) && (lptr -> child != NULL))
    {
        //printf("Just before Divide \n");
        ptr = Divide_title(lptr);
        //printf("Just before left enter \n");
        lptr = Merge_sort_title(lptr);
        //printf("Just before right sort \n");
        ptr = Merge_sort_title(ptr);
        //printf("Just before Merging \n");
        head_ptr = Merge_title(lptr,ptr);
    }

    return head_ptr;
}





status_code Merge_user_libraries(User *user_head)
{
    int uid1,uid2;
    status_code sc = Success;
    printf("Enter user id 1 : ");
    scanf("%d",&uid1);

    printf("Enter user id 2 : ");
    scanf("%d",&uid2);

    User *uptr = user_head;
    User *uptr1 = NULL;
    User *uptr2 = NULL;

    int flag = 0;
    while(uptr != NULL && flag <=1)
    {
        if(flag == 0 && uptr -> user_id == uid1)
        {
            uptr1 = uptr;
            flag++;
        }
        else if(flag == 1 && uptr -> user_id == uid2)
        {
            uptr2 = uptr;
            flag++;
        }

        uptr = uptr -> next;
    }

    if(uptr1 == NULL || uptr2 == NULL)
    {
        sc = Failure;
    }
    else
    {
        Audio *aptr1 = uptr1 ->child;
        Audio *aptr2 = uptr2 -> child;
        Audio *prev1 = NULL;
        Audio *prev2 = NULL;
        

        if(aptr1 -> audio_id < aptr2 -> audio_id)
        {
            Audio *new_ptr = (Audio *)malloc(sizeof(Audio));
            new_ptr ->audio_id = aptr1 ->audio_id;
            new_ptr ->rating = aptr1 ->rating;
            new_ptr -> duration = aptr1 ->duration;
            new_ptr -> rate_count = aptr1 ->rate_count;
            new_ptr -> timestamp = 0;
            strcpy(new_ptr ->author,aptr1 -> author);
            strcpy(new_ptr ->genre,aptr1 ->genre);
            strcpy(new_ptr ->narrator,aptr1 ->narrator);
            strcpy(new_ptr ->title,aptr1 -> title);

            new_ptr -> child = aptr2;
            uptr2 -> child = new_ptr;
            
            prev1 = aptr1;
            prev2 = new_ptr;
            aptr1 = aptr1 -> child;
        }

        else if(aptr1 -> audio_id > aptr2 -> audio_id)
        {
            Audio *new_ptr = (Audio *)malloc(sizeof(Audio));
            new_ptr ->audio_id = aptr2 ->audio_id;
            new_ptr ->rating = aptr2 ->rating;
            new_ptr -> duration = aptr2 ->duration;
            new_ptr -> rate_count = aptr2 -> rate_count;
            new_ptr -> timestamp = 0;
            strcpy(new_ptr ->author,aptr2 -> author);
            strcpy(new_ptr ->genre,aptr2 ->genre);
            strcpy(new_ptr ->narrator,aptr2 ->narrator);
            strcpy(new_ptr ->title,aptr2 -> title);

            new_ptr -> child = aptr1;
            uptr1 -> child = new_ptr;

            prev1 = new_ptr;
            prev2 = aptr2;
            aptr2 = aptr2 -> child;
        }

        else
        {
            aptr1 = aptr1 -> child;
            aptr2 = aptr2 -> child;
        }

        while(aptr1 != NULL & aptr2 != NULL)
        {
            if(aptr1 -> audio_id < aptr2 -> audio_id)
            {
                Audio *new_ptr = (Audio *)malloc(sizeof(Audio));
                new_ptr ->audio_id = aptr1 ->audio_id;
                new_ptr ->rating = aptr1 ->rating;
                new_ptr -> duration = aptr1 ->duration;
                new_ptr -> rate_count = aptr1 -> rate_count;
                new_ptr -> timestamp = 0;
                strcpy(new_ptr ->author,aptr1 -> author);
                strcpy(new_ptr ->genre,aptr1 ->genre);
                strcpy(new_ptr ->narrator,aptr1 ->narrator);
                strcpy(new_ptr ->title,aptr1 -> title);

                new_ptr -> child = aptr2;
                prev2 -> child = new_ptr;

                prev2 = new_ptr;

                aptr1 = aptr1 -> child;
                prev1 = prev1 -> child;
            }

            else if(aptr1 -> audio_id > aptr2 -> audio_id)
            {
                Audio *new_ptr = (Audio *)malloc(sizeof(Audio));
                new_ptr ->audio_id = aptr2 ->audio_id;
                new_ptr ->rating = aptr2 ->rating;
                new_ptr -> duration = aptr2 ->duration;
                new_ptr -> rate_count = aptr2 -> rate_count;
                new_ptr -> timestamp = 0;
                strcpy(new_ptr ->author,aptr2 -> author);
                strcpy(new_ptr ->genre,aptr2 ->genre);
                strcpy(new_ptr ->narrator,aptr2 ->narrator);
                strcpy(new_ptr ->title,aptr2 -> title);

                new_ptr -> child = aptr1;
                prev1 -> child = new_ptr;
                prev1 = new_ptr;

                aptr2 = aptr2 -> child;
                prev2 = prev2 -> child;
            }
            else
            {
                aptr1 = aptr1 -> child;
                aptr2 = aptr2 -> child;
                prev1 = prev1 -> child;
                prev2 = prev2 -> child;
            }

            
        }

        while(aptr1 != NULL)
        {
            Audio *new_ptr = (Audio *)malloc(sizeof(Audio));
            new_ptr ->audio_id = aptr1 ->audio_id;
            new_ptr ->rating = aptr1 ->rating;
            new_ptr -> duration = aptr1 ->duration;
            new_ptr -> rate_count = aptr1 -> rate_count;
            new_ptr -> timestamp = 0;
            strcpy(new_ptr ->author,aptr1 -> author);
            strcpy(new_ptr ->genre,aptr1 ->genre);
            strcpy(new_ptr ->narrator,aptr1 ->narrator);
            strcpy(new_ptr ->title,aptr1 -> title);

            

            new_ptr -> child = aptr2;
            prev2 -> child = new_ptr;

            prev2 = new_ptr;

            aptr1 = aptr1 -> child;
            prev1 = prev1 -> child;

        }

        while(aptr2 != NULL)
        {
            Audio *new_ptr = (Audio *)malloc(sizeof(Audio));
            new_ptr ->audio_id = aptr2 ->audio_id;
            new_ptr ->rating = aptr2 ->rating;
            new_ptr -> duration = aptr2 ->duration;
            new_ptr -> rate_count = aptr2 -> rate_count;
            new_ptr -> timestamp = 0;
            strcpy(new_ptr ->author,aptr2 -> author);
            strcpy(new_ptr ->genre,aptr2 ->genre);
            strcpy(new_ptr ->narrator,aptr2 ->narrator);
            strcpy(new_ptr ->title,aptr2 -> title);

            new_ptr -> child = aptr1;
            prev1 -> child = new_ptr;
            prev1 = new_ptr;

            aptr2 = aptr2 -> child;
            prev2 = prev2 -> child;
        }

        printf("Merging is successful\n");


        // Audio *ret_ptr1 = Merge_sort_title(uptr1 -> child);
        // Audio *ret_ptr2 = Merge_sort_title(uptr2 -> child);

        // uptr1 -> child = ret_ptr1;
        // uptr2 -> child = ret_ptr2;

    }
    
    return sc;
    
}

status_code Listening_history_report_audiobook(User* user_head,Audio_list* audio_head)
{
    int aid;
    status_code sc = Success;
    printf("Enter the audio book id : ");
    scanf("%d",&aid);
    Audio_list *alptr = audio_head;
    while(alptr != NULL && alptr -> audio_id != aid)
    {
        alptr = alptr -> next;
    }

    if(alptr == NULL)
    {
        sc = Failure;
    }
    else
    {
        //first calculate toatal listening time
        User *uptr = user_head;
        Audio *aptr;
        int total_time = 0;
        while(uptr != NULL)
        {
            aptr = uptr -> child;
            while(aptr != NULL)
            {
                if(aptr ->audio_id == aid)
                {
                    total_time = total_time + aptr ->timestamp;
                }
                aptr = aptr -> child;
            }
            uptr = uptr -> next;
        }

        printf ("Audio Book Details Audio BOOk ID - %d : \n",aid);
        printf("Title of BOOK : %s \n",alptr ->title);
        printf("Author of BOOK : %s \n",alptr ->author);
        printf("Total Listening time : %d \n",total_time);

    }
    return sc;
}

typedef struct Hash_Rate
{
    float rating;
    Audio_list *ptr;
    struct Hash_Rate *next;
}Hash_Rate;

Hash_Rate* Merge_rate(Hash_Rate* lptr1, Hash_Rate* lptr2) {
    Hash_Rate* result,*ptr1,*ptr2,*tail;
    result = NULL;
    tail = NULL;
    if(lptr1 == NULL)
    {
        result = lptr2;
    }
    else if(lptr2 == NULL)
    {
        result = lptr1;
    }
    else
    {
        ptr1 = lptr1;
        ptr2 = lptr2;

        if(lptr1 ->rating < lptr2 ->rating)
        {
            result = lptr1;
            ptr1 = ptr1 -> next;
        }
        else
        {
            result = lptr2;
            ptr2 = ptr2 -> next;
        }

        tail = result;

        while(ptr1 != NULL && ptr2 != NULL)
        {
            if(ptr1 -> rating < ptr2 -> rating)
            {
                tail -> next = ptr1;
                ptr1 = ptr1 -> next;
                tail = tail -> next;
            }
            else
            {
                tail -> next = ptr2;
                ptr2 = ptr2 -> next;
                tail = tail -> next;
            }
        }

        if(ptr1 != NULL)
        {
            tail -> next = ptr1;
        }
        else
        {
            tail -> next = ptr2;
        }
        return result;
    }
}

// Function to split the linked list into two halves
Hash_Rate* Divide_rate(Hash_Rate* lptr) 
{
    Hash_Rate* slow = lptr;
    Hash_Rate* fast = lptr->next;
    while(fast != NULL && fast -> next != NULL)
    {
        printf("r");
        slow = slow -> next;
        fast = fast -> next -> next;
    }
    Hash_Rate* ret_ptr = slow->next;
    slow ->next = NULL;
    return ret_ptr;
}

// Merge sort function
Hash_Rate* Merge_sort_rate(Hash_Rate* lptr) {
    Hash_Rate*head = lptr;
    Hash_Rate*ptr;

    // Base case
    if (head != NULL && head->next != NULL)
    {
        printf("after divide \n");
        ptr = Divide_rate(lptr); //pointer of right side
        lptr = Merge_sort_rate(lptr);
        printf("After left sort \n");
        ptr = Merge_sort_rate(ptr);
        printf("After right sort \n");
        head = Merge_rate(lptr,ptr);
    }

    return head;
        
}

status_code Display_Audiobook_Acc_Ratng(Audio_list*audio_head)
{
    status_code sc = Success;
    Audio_list *alptr = audio_head;
    Hash_Rate *Dummy_ptr = (Hash_Rate*)malloc(sizeof(Hash_Rate));
    Hash_Rate *tail = Dummy_ptr;

    char a[MAX_LINE_LEN] = "AUDIO ID";
    char b[MAX_LINE_LEN] = "TITLE";
    char c[MAX_LINE_LEN] = "AUTHOR";
    char d[MAX_LINE_LEN] = "NARRATOR";
    char e[MAX_LINE_LEN] = "GENRE";
    char f[MAX_LINE_LEN] = "RATE COUNT";
    char g[MAX_LINE_LEN] = "OVERALL RATING";
    char h[MAX_LINE_LEN] = "LENGTH(minutes)";

    printf("%-10s\t%-20s\t%-20s\t%-20s\t%-20s\t%-10s\t%-10s\t%-20s\n\n", a, b, c, d, e, f, g, h);

    while(alptr != NULL)
    {
        Hash_Rate *new_ptr = (Hash_Rate *)malloc(sizeof(Hash_Rate));
        new_ptr ->rating = alptr ->rating;
        new_ptr ->ptr = alptr;
        tail -> next = new_ptr;
        new_ptr -> next = NULL;
        tail = tail -> next;
        alptr = alptr ->next;
    }

    Hash_Rate *ret_head = Merge_sort_rate(Dummy_ptr ->next);
    if(ret_head == NULL)
    {
        sc = Failure;
        
    }
    else
    {
        while(ret_head != NULL)
        {
            

            alptr = ret_head ->ptr;
            printf("%-10d\t%-20s\t%-20s\t%-20s\t%-20s\t%-10d\t%-10f\t%-20d\n",alptr->audio_id, alptr->title, alptr->author, alptr->narrator,alptr->genre, alptr->rate_count, alptr->rating, alptr->duration);
            ret_head = ret_head -> next;
        }

    }
    
    
    return sc;
}

User * Create_user_list(Audio_list* audio_head)
{
    //printf("entered in create user list \n");
    User* ret_val;
    FILE *fptr;
    char line[MAX_LINE_LEN];
    fptr = fopen("users.txt","r");

    if(fptr == NULL)
    {
        ret_val = NULL;
    }
    else
    {
        User* Dummy_ptr_user = (User*)malloc(sizeof(User));
        Dummy_ptr_user -> next = NULL;
        User*prev = Dummy_ptr_user;
        int flag = 0;
        int i = 0;
        while(fgets(line,MAX_LINE_LEN,fptr) != NULL && flag == 0)
        {
            //printf("Inside first while %d \n",i);
            if(strcmp(line,"\n") == 0)
            {
                flag = 1;
                //printf("flag changed \n");
            }
            else
            {
                //user data entered
                User* ptr = (User*)malloc(sizeof(User));
                sscanf(line, "%d %s %s %s %s %s", &ptr->user_id, ptr->name, ptr->email, ptr->narrator_preference, ptr->author_preference, ptr->genre_preference);
                prev -> next = ptr;
                ptr -> next = NULL;
                prev = ptr;
                
                //appending prefence audiobook as child
                Audio_list* audio_ptr = audio_head;
                int flag = 0;
                Audio* prev_child = NULL;
                int count = 0;
                while(audio_ptr != NULL)
                {
                    if(strcmp(audio_ptr -> narrator , ptr ->narrator_preference) != 0 && strcmp(audio_ptr -> author , ptr ->author_preference) != 0 && strcmp(audio_ptr -> genre , ptr ->genre_preference) != 0 )
                    {
                        //printf("inside while -> if \n");
                    }
                    else
                    {
                        //printf("inside while -> else \n");
                        //printf("Appending children \n");
                        Audio *new_ptr = (Audio *)malloc(sizeof(Audio));
                        //copying data in Audio to be appended in user list
                        new_ptr ->audio_id = audio_ptr ->audio_id;
                        strcpy(new_ptr ->title,audio_ptr ->title);
                        strcpy(new_ptr ->author,audio_ptr ->author);
                        strcpy(new_ptr ->narrator,audio_ptr ->narrator);
                        strcpy(new_ptr ->genre,audio_ptr ->genre);
                        new_ptr -> duration = audio_ptr -> duration;
                        
                        new_ptr -> rating = audio_ptr -> rating;
                        new_ptr -> rate_count = audio_ptr ->rate_count;
                        new_ptr ->timestamp = 0;
                        
                        
                        if(flag == 0)   //only first time
                        {
                            ptr -> child = new_ptr;
                            new_ptr -> child = NULL;
                            flag = 1;
                        }
                        else
                        {
                            prev_child -> child = new_ptr;
                            new_ptr ->child = NULL;
                        }

                        prev_child = new_ptr;
                        count ++;
                    
                    }
                    audio_ptr = audio_ptr -> next;
                    
                }
                //printf("Completed appending all childer \n");
            }
            i++;
        }
        //printf("Just outside while loop \n");

        ret_val = Dummy_ptr_user -> next;
        free(Dummy_ptr_user);
        
        
    }
    //printf("Done with the function \n");
    return ret_val;
}

Audio_list* Create_Audio_list()
{
    //printf("Start - Create_Audio_list()");
    //printf("entered in create audio list \n");
    Audio_list* ret_val;
    FILE *fptr1;
    char line[MAX_LINE_LEN];
    fptr1 = fopen("audiobook.txt","r");

    if(fptr1 == NULL)
    {
        ret_val = NULL;
    }
    else
    {
        Audio_list* Dummy_ptr_audio = (Audio_list*)malloc(sizeof(Audio_list));
        Dummy_ptr_audio -> next = NULL;
        Audio_list*prev = Dummy_ptr_audio;
        int flag = 0;
        int i = 0;
        while(fgets(line,MAX_LINE_LEN,fptr1) != NULL && flag == 0)
        {
            if(strcmp(line,"\n") == 0)
            {
                flag = 1;
            }
            else
            {
                //printf("Time : %d \n",i);
                Audio_list* ptr = (Audio_list*)malloc(sizeof(Audio_list));
                sscanf(line, "%d %s %s %s %d %s %f %d", &ptr->audio_id, ptr->title, ptr->author, ptr->narrator, &ptr->duration, ptr->genre,&ptr -> rating,&ptr ->rate_count);
                prev -> next = ptr;
                ptr -> next = NULL;
                prev = ptr;
            }
            i++;
        }

        
        ret_val = Dummy_ptr_audio -> next;
        free(Dummy_ptr_audio);
        fclose(fptr1);
            
    }
    //printf("End - Create_Audio_list()");

    return ret_val;
} 

void print_user(User* user_head)
{
    User* user_ptr = user_head;
    Audio *audio_ptr;
    while(user_ptr != NULL)
    {
        printf("User id : %d \t",user_ptr -> user_id);

        audio_ptr = user_ptr -> child;
        while(audio_ptr != NULL)
        {
            printf("%d ",audio_ptr -> audio_id);
            audio_ptr = audio_ptr -> child;
        }
        user_ptr = user_ptr -> next;
        printf("\n");

    }
}

int main()
{

    //create audio list
    Audio_list* audio_head = Create_Audio_list();
        if(audio_head != NULL)
        {
            printf("audio list created successfullly \n");
        }
        else
        {
            printf("Failed to create user list \n");
        }

    //making user list with preference audiobook stored

    User* user_head = Create_user_list(audio_head);
    if(user_head != NULL)
    {
        printf("user list created successfullly \n");
    }
    else
    {
        printf("Failed to create user list \n");
    }

    print_user(user_head);
    

    int choice;
    int quit_flag = 0;
    while(quit_flag == 0)
    {
        printf("\n \n \nWhich function do you want to perform \n1.\t Add or Edit Audiobook \n2.\t Delete an audiobook \n3.\t Search for an audiobook \n4. \t Add a new user profile \n5. \t Add audiobook to user's libraray \n6. \t Update listening progress \n7. \t Display user's library \n8. \t Rate a audiobook \n9. \t Display the most popular audiobook \n10. \t Listening history report of a user \n11.\t Merge user libraries \n12. \t Listening history report of an audiobook \n13. \t Display Audiobook sorted based on rating \n14. \t Check the program structure \n15. \t Quit Program \n");
        printf("Enter your choice : ");
        scanf("%d",&choice);

        if(choice == 1)
        {
            //function  1 => ratings ieee is getting stored in audiobook
            status_code sc = Add_audiobook(audio_head);
            if(sc == Success)
            {
                printf("Audio book added/edited successfully \n");
            }
            else
            {
                printf("Failed to add/edit \n");
            }
        }

        else if(choice == 2)
        {
            //function 2  => some error :: Audio_book deleted successfully => never gets printed
            audio_head = Delete_audiobook(audio_head);

            
        }

        else if(choice == 3)
        {
            
            //function 3 => 1.extra match number is being printed + 2.rating is printed to be null
            status_code sc = Search_audiobook(audio_head);
            if(sc == Success)
            {
                printf("Search completed successfully \n");
            }
            else
            {
                printf("No such audiobook found");
            }
        }
        
        else if(choice == 4)
        {
            //function 4    // check if preferrwed audiobooks are getting added or not
            status_code sc2 = Add_user_profile(audio_head,user_head);
            if(sc2 == Success)
            {
                printf("Successful");
            }
            else
            {
                printf("Failed");
            }
        }

        else if(choice == 5)
        {
            //function 5 => not completed need to veify procedure from sumedh
            status_code sc5 = Add_to_UserLibrary(user_head,audio_head);
            if(sc5 == Success)
            {
                printf("Task completed successfully");
            }
            else
            {
                printf("Failed to complete the task");
            }
        }

        else if(choice == 6)
        {
            //function 6 => shows successfull but need to print and check
            status_code sc4 = Listening_progress(user_head);
            if(sc4 == Success)
            {
                printf("Task completed successfully");
            }
            else
            {
                printf("Failed to complete the task");
            }
        }

        else if(choice == 7)
        {
            //function 7 => written but need to check once rate count added
            status_code sc5 = Display_user_libraries(user_head);
            if(sc5 == Success)
            {
                printf("Task completed successfully");
            }
            else
            {
                printf("Failed to complete the task");
            }
        }

        else if(choice == 8)
        {
            //function 8    =>contribution to overall rating is left 
            status_code sc8 = Rate_Audiobook(user_head,audio_head);
            if(sc8 == Success)
            {
                printf("Task completed successfully");
            }
            else
            {
                printf("Failed to complete the task");
            }
        }

        else if(choice == 9)
        {
            //function 9 => inut must be user id and not audio  OR no need of user id => shows ieee-754 value from float
            status_code sc9 = Most_poplular_audiobook(audio_head);
            if(sc9 == Success)
            {
                printf("Task completed successfully");
            }
            else
            {
                printf("Failed to complete the task");
            }
        }

        else if(choice == 10)
        {
            //function 10 => 
            status_code sc10 = Listening_history_report_user(user_head);
            if(sc10 == Failure)
            {
                printf("No such Audiobook found \n");
            }
            else
            {
                printf("\n Task completed successfully");
            }
        }

        else if(choice == 11)
        {
            //function 11
            status_code sc11 = Merge_user_libraries(user_head) ;
            if(sc11 == Success)
            {
                printf("Task completed successfully");
            }
            else
            {
                printf("Failed to complete the task");
            }
            printf("Do you want to check if it was successful : (yes/no)");
            char input[10];
            scanf("%s",input);
            if(strcmp(input,"yes") == 0)
            {
                print_user(user_head);
            }
            else
            {
                printf("\n Ok \n");
            }

        }

        else if(choice == 12)
        {
            //function 12
            status_code sc12 = Listening_history_report_audiobook(user_head,audio_head);
            if(sc12 == Success)
            {
                printf("\n Task completed successfully \n");
            }
            else
            {
                printf("Failed to complete the task \n");
            }
        }

        else if(choice == 13)
        {
            //function 13
            status_code sc13 = Display_Audiobook_Acc_Ratng(audio_head);
            if(sc13 = Success)
            {
                printf("Task Completed Successfully \n");
            }
            else
            {
                printf("Failed to complete the task \n");
            }
        }

        else if (choice == 14)
        {
            print_user(user_head);
        }

        else if(choice == 15)
        {
            quit_flag = 1;
        }

        else
        {
            printf("\n Enter valid select number !!!\n");
        }

    
    }
    return 0; 
}