#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum accommodation_status {UNOCCUPIED, OCCUPIED} acc_stat;

typedef struct accommodation_tag
{
    char firstname [50];
    char lastname [50];
    char accommodation_type [20];
    int idtype;
    struct idnum
    {
        char aadhaar [15];
        char passport [15];
        char empcode [15];
    }idnumber;
    char address [100];
    struct accommodation_tag *next;
}AccNode;

struct accommodation_record
{
    acc_stat Type_I,Type_II,Type_III,Type_IV;

}acc_type[10];  //USING ARRAY OF STRUCTURE AS SIZE IS KNOWN AND IT'LL PROVIDE BETTER SPACE AND TIME COMPLEXITY...

int t1_count=0,t2_count=0,t3_count=0,t4_count=0;


typedef struct index_ll_tag
{
    int index;
    AccNode *ptr;
    struct index_ll_tag *next;

}IndexLL;


//GLOBAL INDEX_LL HEAD POINTER
IndexLL *iptr;


void indexlist(AccNode *head)
{


    AccNode *temp_ll,*prev,*head_of_temp_ll;
    IndexLL *iprev,*head_of_index_ll;
    iprev=NULL;
    prev=NULL;
    temp_ll=NULL;
    head_of_temp_ll=NULL;
    head_of_index_ll=NULL;

    int i=0;

    while(head!=NULL)
    {
        temp_ll=(AccNode *)malloc(sizeof(AccNode));
        strcpy(temp_ll->firstname, head->firstname);
        strcpy(temp_ll->lastname, head->lastname);
        strcpy(temp_ll->accommodation_type, head->accommodation_type);
        temp_ll->idtype=head->idtype;
        strcpy(temp_ll->idnumber.aadhaar, head->idnumber.aadhaar);
        strcpy(temp_ll->idnumber.passport, head->idnumber.passport);
        strcpy(temp_ll->idnumber.empcode, head->idnumber.empcode);
        strcpy(temp_ll->address, head->address);
        temp_ll->next=NULL;

        if(prev==NULL)
        {
            prev=temp_ll;
            head_of_temp_ll=temp_ll;
        }
        else
        {
            prev->next=temp_ll;
            prev=prev->next;
        }

        iptr=(IndexLL *)malloc(sizeof(IndexLL));
        iptr->index=i;
        i++;
        iptr->next=NULL;
        iptr->ptr=temp_ll;

        if(iprev==NULL)
        {
            iprev=iptr;
            head_of_index_ll=iptr;
        }
        else
        {
            iprev->next=iptr;
            iprev=iprev->next;
        }
    }
    //NOW WE CAN WORK WITH TEMP_LL WITHOUT AFFECTING ORIGINAL LINKED LIST...
    iptr=head_of_index_ll;
    temp_ll=head_of_temp_ll;

    AccNode *ahead,*present,*back,*outer_back;
    IndexLL *iahead,*ipresent,*iback,*iouter_back;

    back=NULL;
    iback=NULL;
    outer_back=NULL;
    iouter_back=NULL;

    if(temp_ll!=NULL && temp_ll->next!=NULL)
    {                                           //iftagbegin
        while(temp_ll->next!=NULL)
        {
            present=temp_ll;
            ahead=present->next;
            back=outer_back;

            ipresent=iptr;
            iahead=ipresent->next;
            iback=iouter_back;


            while(ahead!=NULL)
            {
                if((strcmp(present->firstname, ahead->firstname)>0) || ((strcmp(present->firstname, ahead->firstname)==0)&&(strcmp(present->lastname, ahead->lastname)>0)))
                {
                    if(back==NULL)
                    {
                        present->next=ahead->next;
                        ahead->next=present;
                        temp_ll=ahead;
                        ahead=present;
                        present=temp_ll;
                        head_of_temp_ll=temp_ll;


                        ipresent->next=iahead->next;
                        iahead->next=ipresent;
                        iptr=iahead;
                        iahead=ipresent;
                        ipresent=iptr;
                        head_of_index_ll=iptr;

                    }
                    else
                    {
                        present->next=ahead->next;
                        ahead->next=present;
                        back->next=ahead;
                        temp_ll=ahead;
                        ahead=present;
                        present=temp_ll;

                        ipresent->next=iahead->next;
                        iahead->next=ipresent;
                        iback->next=iahead;
                        iptr=iahead;
                        iahead=ipresent;
                        ipresent=iptr;
                    }
                }
                back=back->next;
                present=present->next;
                ahead=ahead->next;

                iback=iback->next;
                ipresent=ipresent->next;
                iahead=iahead->next;

            }
            outer_back=temp_ll;
            temp_ll=temp_ll->next;

            iouter_back=iptr;
            iptr=iptr->next;

         }
    }
    iptr=head_of_index_ll;
}


//UPDATE ACCOMMODATION RECORD FUCNTION STARTS HERE...
void updateAccommodationRecord(AccNode *head)
{

    while(head!=NULL)
    {
        if(strcmp(head->accommodation_type,"Type-I")==0)
        {
            acc_type[t1_count].Type_I=OCCUPIED;
            t1_count++;
        }
        else if(strcmp(head->accommodation_type,"Type-II")==0)
        {
            acc_type[t2_count].Type_II=OCCUPIED;
            t2_count++;
        }
        else if(strcmp(head->accommodation_type,"Type-III")==0)
        {
            acc_type[t3_count].Type_III=OCCUPIED;
            t3_count++;
        }
        else
        {
            acc_type[t4_count].Type_IV=OCCUPIED;
            t4_count++;
        }
    }
}
//UPDATE ACCOMMODATION RECORD FUCNTION ENDS HERE...

//INSERTRECORD FUCNTION STARTS HERE...
void InsertRecord(AccNode **head)
{
    AccNode *nptr,*temp;
    int flag=1;

    nptr=(AccNode *)malloc(sizeof(AccNode));

    //scanning data from user...
    scanf("%s",nptr->firstname);
    scanf("%s",nptr->lastname);
    scanf("%s",nptr->accommodation_type);
    scanf("%d",&nptr->idtype);
    if(nptr->idtype==0)
    {
        scanf("%s",nptr->idnumber.aadhaar);
        nptr->idnumber.empcode[0]='\0';
        nptr->idnumber.passport[0]='\0';
    }
    else if(nptr->idtype==1)
    {
        scanf("%s",nptr->idnumber.passport);
        nptr->idnumber.aadhaar[0]='\0';
        nptr->idnumber.empcode[0]='\0';
    }
    else
    {
        scanf("%s",nptr->idnumber.empcode);
        nptr->idnumber.aadhaar[0]='\0';
        nptr->idnumber.passport[0]='\0';
    }
    scanf("%[^\n]s",nptr->address);


    //Inserting the data at appropriate location...
    temp=*head;
    if(*head==NULL)
    {
        nptr->next=NULL;
        *head=nptr;
    }
    else
    {
        if(nptr->idtype==0)
        {
            nptr->next=temp->next;
            *head=nptr;
        }
        else if(nptr->idtype==1)
        {
            if(temp->idtype==2 || temp->idtype==1)
            {
                nptr->next=temp->next;
                *head=nptr;
            }
            else
            {
                while(temp->next!=NULL || flag==1)
                {
                    if(temp->idtype==2 || temp->idtype==1)
                        temp=temp->next;
                    else
                        flag=0;
                }
                nptr->next=temp->next;
                temp->next=nptr;
            }
        }
        else //nptr->idtype==2
        {
            while(temp->next!=NULL)
            {
                temp=temp->next;
            }
            nptr->next=temp->next;
            temp->next=nptr;
        }
    }
    updateAccommodationRecord(*head);

}
//INSERTRECORD FUCNTION ENDS HERE...

//REMOVE DUPLICATES FUNCTION STARTS HERE...
void removeDuplicates(AccNode **head)
{
    AccNode *ahead,*back,*temp;
    if(*head!=NULL)
    {
        back=*head;
        ahead=back->next;

        while(back->next!=NULL)
        {
            ahead=back->next;

            while(ahead!=NULL)
            {
                if((strcmp(ahead->firstname, back->firstname)==0) && (strcmp(ahead->lastname, back->lastname)==0) && (ahead->idtype==back->idtype))  //DUPLICATE RECORDS
                {
                    temp=ahead;
                    ahead=ahead->next;
                    free(temp);
                    temp=NULL;
                }
                else    //RECORDS DO NOT MATCH
                {
                    ahead=ahead->next;
                }
            } //AHEAD POINTER REACHES TO THE END OF LIST
            back=back->next;
        }//BACK POINTER REACHES TO THE LAST NODE

    }//IF STATEMENT ENDS
    updateAccommodationRecord(*head);
}
//REMOVE DUPLICATES FUCNTION ENDS HERE...





//PRINT RECORDS FUNCTION BEGINS HERE...
void printRecords(AccNode *head)
{
    //INSERT RECORD FUNCTION ENSURES THAT RECORDS ARE STORED SUCH THAT RECORDS APPEAR IN THE ORDER OF INCREASING IDTYPE.
    while(head!=NULL)
    {
        printf("First name : %s\n",head->firstname);
        printf("Last name : %s\n",head->lastname);
        printf("Accommodation type : %s\n",head->accommodation_type);
        printf("ID Type : %d\n",head->idtype);

        switch(head->idtype)
        {
        case 0:
            printf("Aadhaar number : %s\n",head->idnumber.aadhaar);
        case 1:
            printf("Passport number : %s\n",head->idnumber.passport);
        case 2:
            printf("Employee code : %s\n",head->idnumber.empcode);
        }

        printf("Address : %s\n\n\n",head->address);

    }

}
//PRINT RECORDS FUNCTION ENDS HERE...


//SEARCH FUNCTION BEGINS HERE...
void search(AccNode *head)
{
    char fname[50],lname[50];
    int flag=1;

    printf("Enter firstname and lastname of the person separated by space : ");
    scanf("%s",fname);
    scanf("%s",lname);

    while(head!=NULL)
    {
        if((strcmp(head->firstname, fname)==0) && (strcmp(head->lastname, lname)==0))
        {
            printf("First name : %s\n",head->firstname);
            printf("Last name : %s\n",head->lastname);
            printf("Accommodation type : %s\n",head->accommodation_type);
            printf("ID Type : %d\n",head->idtype);

            switch(head->idtype)
            {
            case 0:
                printf("Aadhaar number : %s\n",head->idnumber.aadhaar);
            case 1:
                printf("Passport number : %s\n",head->idnumber.passport);
            case 2:
                printf("Employee code : %s\n",head->idnumber.empcode);
            }

            printf("Address : %s\n\n\n",head->address);
            flag=0;
        }
        head=head->next;
    }
    if(flag==1)
        printf("Record Not Found!\n\n\n");
}
//SEARCH FUNCTION ENDS HERE...





//DELETE RECORD FUNCTION BEGINS HERE...
void deleteRecord(AccNode **head)
{
    int type;
    char number[15],bfr;
    int flag=1;
    AccNode *temp,*prev;

    prev=NULL;

    printf("Enter idtype and idnum separated by space : ");
    scanf("%d",&type);
    scanf("%c",&bfr);
    scanf("%s",number);

    if(*head!=NULL)
    {
        temp=*head;

        while(temp!=NULL && flag==1)
        {
            if(temp->idtype==type)
            {
                switch(temp->idtype)
                {
                case 0:
                    if(strcmp(number, temp->idnumber.aadhaar)==0) //MATCHING RECORD FOUND...
                    {
                        if(*head==temp)   //MATCH FOUND AT FIRST NODE...
                        {
                            *head=temp->next;
                            free(temp);
                            temp=NULL;
                            flag=0;
                        }
                        else
                        {
                            prev->next=temp->next;
                            free(temp);
                            temp=NULL;
                            flag=0;
                        }
                    }
                    break;

                case 1:
                    if(strcmp(number, temp->idnumber.passport)==0) //MATCHING RECORD FOUND...
                    {
                        if(*head==temp)   //MATCH FOUND AT FIRST NODE...
                        {
                            *head=temp->next;
                            free(temp);
                            temp=NULL;
                            flag=0;
                        }
                        else
                        {
                            prev->next=temp->next;
                            free(temp);
                            temp=NULL;
                            flag=0;
                        }
                    }
                    break;

                case 2:
                    if(strcmp(number, temp->idnumber.empcode)==0)   //MATCHING RECORD FOUND...
                    {
                        if(*head==temp)   //MATCH FOUND AT FIRST NODE...
                        {
                            *head=temp->next;
                            free(temp);
                            temp=NULL;
                            flag=0;
                        }
                        else
                        {
                            prev->next=temp->next;
                            free(temp);
                            temp=NULL;
                            flag=0;
                        }
                    }
                    break;
                }
            }
            if(flag==1)     //IF RECORD IS NOT MATCHED, GO TO NEXT NODE...
            {
                prev=temp;
                temp=temp->next;
            }
        }

    }
    if(flag==1) //COULDN'T FIND RECORD TO BE DELETED
    {
        printf("Invalid operation! Record Not Found.");
    }
    else        //DELETION HAPPENED
    {
        indexlist(*head);
        updateAccommodationRecord(*head);
    }

}
//DELETE RECORD FUNCTION ENDS HERE...



//UPDATE RECORD FUNCTION BEGINS HERE...
void updateRecord(AccNode *head)
{
    char fname[50],lname[50],new_val[100];
    int id_choice;
    char buffer;
    AccNode *temp;
    int flag=1,field;

    printf("Enter first name and last name of the employee separated by space : ");
    scanf("%s",fname);
    scanf("%s",lname);

    temp=head;
    while(temp!=NULL && flag==1)
    {
        if((strcmp(temp->firstname, fname)==0) &&  (strcmp(temp->lastname, lname)))
            flag=0;
        else
            temp=temp->next;
    }
    if(flag==0)        //RECORD FOUND...
    {
        printf("1. Firstname\n");
        printf("2. Lastname\n");
        printf("3. Accommodation Type\n");
        printf("4. ID\n");
        printf("5. Address\n");
        printf("Enter field number which needs to be updated : ");
        scanf("%d",&field);
        switch(field)
        {
        case 1:
            printf("Enter new Firstname : ");
            scanf("%s",new_val);
            strcpy(temp->firstname, new_val);
            break;
        case 2:
            printf("Enter new Lastname : ");
            scanf("%s",new_val);
            strcpy(temp->lastname, new_val);
            break;
        case 3:
            printf("Enter new Accommodation Type : ");
            scanf("%s",new_val);
            strcpy(temp->accommodation_type,new_val);
            break;
        case 4:
            printf("Enter 0/1/2 for Aadhaar, Passport, Employee code respectively : ");
            scanf("%d",&id_choice);

            //Since a person can have only one type of ID, he/she can only update the type which is already present in the record.

            if(id_choice==temp->idtype)
            {
                printf("Enter new ID number : ");
                scanf("%s",new_val);
                switch(id_choice)
                {
                case 0:
                    strcpy(temp->idnumber.aadhaar, new_val);
                    break;
                case 1:
                    strcpy(temp->idnumber.passport, new_val);
                    break;
                case 2:
                    strcpy(temp->idnumber.empcode, new_val);
                    break;
                }
            }
            else
            {
                printf("An employee cannot have more than One ID type.\n");
            }
            break;
        case 5:
            scanf("%c",&buffer);
            printf("Enter address : ");
            scanf("%[^\n]s",temp->address);
            break;

        }
    }
    else
    {
        printf("Record Not Found. Operation Unsuccessful.\n");
    }
    if(field==1 || field==2)
    {
        indexlist(head);
    }
    updateAccommodationRecord(head);
}
//UPDATE RECORD FUNCTION ENDS HERE...




//SPECIAL REQUEST ALLOCATION FUNCTION BEGINS HERE...
void specialRequestAllocation(AccNode *head)
{
    char fname[50],lname[50],requirement[10];
    int found=0;

    //identifying employee

    printf("Enter full name(first last) of the employee requesting allocation : ");
    scanf("%s",fname);
    scanf("%s",lname);
    while(head!=NULL && found==0)
    {
        if((strcmp(fname, head->firstname)==0)&&(strcmp(lname, head->lastname)==0))
            found=1;
        else
            head=head->next;
    }
    printf("Enter type of accommodation required : ");
    scanf("%s",requirement);
    if(strcmp(requirement, "Type-I")==0)
    {
        if(t1_count<=9)
        {
            //we found vacancy for new accommodation hence previous accommodation must be vacated
            if(strcmp(head->accommodation_type, "Type-I")==0)
            {
                acc_type[t1_count-1].Type_I=UNOCCUPIED;
                t1_count--;
            }
            else if(strcmp(head->accommodation_type, "Type-II")==0)
            {
                acc_type[t2_count-1].Type_II=UNOCCUPIED;
                t2_count--;
            }
            else if(strcmp(head->accommodation_type, "Type-III")==0)
            {
                acc_type[t3_count-1].Type_III=UNOCCUPIED;
                t3_count--;
            }
            else
            {
                acc_type[t4_count-1].Type_IV=UNOCCUPIED;
                t4_count--;
            }
            strcpy(head->accommodation_type, "Type-I");
            acc_type[t1_count].Type_I=OCCUPIED;
            t1_count++;
        }
        else
        {
            printf("Accommodation type requested is not available");
        }
    }
    else if(strcmp(requirement, "Type-II")==0)
    {
        if(t2_count<=9)
        {
            //we found vacancy for new accommodation hence previous accommodation must be vacated
            if(strcmp(head->accommodation_type, "Type-I")==0)
            {
                acc_type[t1_count-1].Type_I=UNOCCUPIED;
                t1_count--;
            }
            else if(strcmp(head->accommodation_type, "Type-II")==0)
            {
                acc_type[t2_count-1].Type_II=UNOCCUPIED;
                t2_count--;
            }
            else if(strcmp(head->accommodation_type, "Type-III")==0)
            {
                acc_type[t3_count-1].Type_III=UNOCCUPIED;
                t3_count--;
            }
            else
            {
                acc_type[t4_count-1].Type_IV=UNOCCUPIED;
                t4_count--;
            }
            strcpy(head->accommodation_type, "Type-II");
            acc_type[t2_count].Type_II=OCCUPIED;
            t2_count++;
        }
        else
        {
            printf("Accommodation type requested is not available");
        }
    }
    else if(strcmp(requirement, "Type-III")==0)
    {
        if(t3_count<=9)
        {
            //we found vacancy for new accommodation hence previous accommodation must be vacated
            if(strcmp(head->accommodation_type, "Type-I")==0)
            {
                acc_type[t1_count-1].Type_I=UNOCCUPIED;
                t1_count--;
            }
            else if(strcmp(head->accommodation_type, "Type-II")==0)
            {
                acc_type[t2_count-1].Type_II=UNOCCUPIED;
                t2_count--;
            }
            else if(strcmp(head->accommodation_type, "Type-III")==0)
            {
                acc_type[t3_count-1].Type_III=UNOCCUPIED;
                t3_count--;
            }
            else
            {
                acc_type[t4_count-1].Type_IV=UNOCCUPIED;
                t4_count--;
            }

            strcpy(head->accommodation_type, "Type-III");
            acc_type[t3_count].Type_III=OCCUPIED;
            t3_count++;
        }
        else
        {
            printf("Accommodation type requested is not available");
        }
    }
    else if(strcmp(requirement, "Type-IV")==0)
    {
        if(t4_count<=9)
        {
            //we found vacancy for new accommodation hence previous accommodation must be vacated
            if(strcmp(head->accommodation_type, "Type-I")==0)
            {
                acc_type[t1_count-1].Type_I=UNOCCUPIED;
                t1_count--;
            }
            else if(strcmp(head->accommodation_type, "Type-II")==0)
            {
                acc_type[t2_count-1].Type_II=UNOCCUPIED;
                t2_count--;
            }
            else if(strcmp(head->accommodation_type, "Type-III")==0)
            {
                acc_type[t3_count-1].Type_III=UNOCCUPIED;
                t3_count--;
            }
            else
            {
                acc_type[t4_count-1].Type_IV=UNOCCUPIED;
                t4_count--;
            }
            strcpy(head->accommodation_type, "Type-IV");
            acc_type[t4_count].Type_IV=OCCUPIED;
            t4_count++;
        }
        else
        {
            printf("Accommodation type requested is not available");
        }
    }
}
//SPECIAL REQUEST ALLOCATION FUNCTION ENDS HERE...


//PRINT SORTED RECORD FUCNTION STARTS HERE...
void printSortedRecords()
{
    IndexLL *temp;
    temp=iptr;
    while(temp!=NULL)
    {
        printf("First name : %s\n",temp->ptr->firstname);
        printf("Last name : %s\n",temp->ptr->lastname);
        printf("Accommodation Type : %s\n",temp->ptr->accommodation_type);
        printf("ID type : %d\n",temp->ptr->idtype);
        switch(temp->ptr->idtype)
        {
        case 0:
            printf("Aadhaar card Number : %s\n",temp->ptr->idnumber.aadhaar);
            break;

        case 1:
            printf("Passport Number : %s\n",temp->ptr->idnumber.passport);
            break;

        case 2:
            printf("Employee Code : %s\n",temp->ptr->idnumber.empcode);
            break;
        }
        printf("Address : %s\n",temp->ptr->address);
        printf("\n");
        temp=temp->next;
    }
}
//PRINT SORTED RECORD FUCNTION ENDS HERE...







int main()
{
    AccNode *head;
    int num_rec,menu_loop;
    char buffer,choice;
    iptr=NULL;
    for(int i=0; i<10;i++)
    {
        acc_type[i].Type_I=UNOCCUPIED;
        acc_type[i].Type_II=UNOCCUPIED;
        acc_type[i].Type_III=UNOCCUPIED;
        acc_type[i].Type_IV=UNOCCUPIED;
    }
    printf("Enter the number of records you wish to insert : ");
    scanf("%d",&num_rec);
    scanf("%c",&buffer);
    for(int i=0;i<num_rec;i++)
    {
        printf("Enter details : ");
        InsertRecord(&head);
    }


    do
    {
        printf("a. Insert Record");
        printf("b. Remove Duplicates");
        printf("c. Print Records");
        printf("d. Print Sorted Records");
        printf("e. Search Records");
        printf("f. Delete Record");
        printf("g. Update Record");
        printf("h. Special Request Allocation");
        printf("Enter your choice : ");
        scanf("%c",&choice);
        switch(choice)
        {
        case 'a':
            printf("Enter details : ");
            InsertRecord(&head);
            break;
        case 'b':
            removeDuplicates(&head);
            break;
        case 'c':
            printRecords(head);
            break;
        case 'd':
            printSortedRecords();
            break;
        case 'e':
            search(head);
            break;
        case 'f':
            deleteRecord(&head);
            break;
        case 'g':
            updateRecord(head);
            break;
        case 'h':
            specialRequestAllocation(head);
            break;
        default:
            printf("If you wish to use menu again, press 1 else 0 :");
            scanf("%d",&menu_loop);
            scanf("%c",&buffer);

        }

    }while(menu_loop==1);
}
