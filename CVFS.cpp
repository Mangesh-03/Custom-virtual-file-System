////////////////////////////////////////////////////////////////////////////
//
//  Header file inclusion
//
///////////////////////////////////////////////////////////////////////////

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<stdbool.h>

#include<iostream>

using namespace std;

////////////////////////////////////////////////////////////////////////////
//
//  User defined Macros
//
///////////////////////////////////////////////////////////////////////////

// max file size
#define MAXFILESIZE 100  
// maximum number of files that we can opened      
#define MAXOPENEDFILES 20  
// maximum number of files that we can create     
#define MAXINODE 5              

#define READ 1
#define WRITE 2
#define EXECUTE 4

#define REGULARFILE 1
#define SPECIALFILE 2

#define START 0
#define CURRENT 1
#define END 2

#define EXECUTE_SUCCESS 0

////////////////////////////////////////////////////////////////////////////
//
//  User defined Macros for Error handling
//
///////////////////////////////////////////////////////////////////////////

#define ERR_INVALID_PARAMETER -1
#define ERR_NO_INODE -2
#define ERR_FILE_ALREADY_EXIST -3
#define ERR_FILE_NOT_EXIST -4
#define ERR_PERMISSION_DENIED -5
#define ERR_INSUFFICIENT_SPACE -6
#define ERR_INSUFFICIENT_DATA -7

////////////////////////////////////////////////////////////////////////////
//
//  Structure name : BootBlock
//  Description :    Holds information about the opreating system
//
///////////////////////////////////////////////////////////////////////////

struct BootBlock
{
    char Information[100];
};

////////////////////////////////////////////////////////////////////////////
//
//  Structure name : SuperBlock
//  Description :    Holds information about the file system
//
///////////////////////////////////////////////////////////////////////////

struct SuperBlock
{
    int TotalInodes;
    int FreeInodes;
};

////////////////////////////////////////////////////////////////////////////
//
//  Structure name : Inode
//  Description :    Holds information about the file 
//
///////////////////////////////////////////////////////////////////////////

typedef struct Inode
{
    char FileName[50];
    int InodeNumber;
    int FileSize;
    int ActualFileSize;
    int FileType;
    int ReferenceCount;
    int Permission;
    int LinkCount;  //  create shorcut link of any file
    char *Buffer;
    struct Inode *next;

}INODE,*PINODE,**PPINODE;

////////////////////////////////////////////////////////////////////////////
//
//  Structure name : FileTable
//  Description :    Holds information about the opened file 
//
///////////////////////////////////////////////////////////////////////////

typedef struct FileTable
{
    int ReadOffset;
    int WriteOffset;
    int Count;
    int Mode;
    PINODE ptrinode;

}FILETABLE,*PFILETABLE;

////////////////////////////////////////////////////////////////////////////
//
//  Structure name : UAREA
//  Description :    Holds information about the process 
//
///////////////////////////////////////////////////////////////////////////

struct UAREA
{
    char ProcessName[50];
    PFILETABLE UFDT[MAXOPENEDFILES];

};

////////////////////////////////////////////////////////////////////////////
//
//  Global variables and object used in the project
//
///////////////////////////////////////////////////////////////////////////

SuperBlock superobj;
PINODE head = NULL;
UAREA uareaobj;
BootBlock bootobj;

////////////////////////////////////////////////////////////////////////////
//
//  Function name :  InitialiseUREA
//  Description:     It is used to initialise content of UREA
//  Author :         Mangesh Ashok Bedre
//  Date :           10/08/2025
//
///////////////////////////////////////////////////////////////////////////

void InitialiseUREA()
{
    strcpy(uareaobj.ProcessName,"Myexe");

    int i = 0;

    while(i < MAXOPENEDFILES)
    {
        uareaobj.UFDT[i] = NULL;
        i++;
    }
    cout<<"CVFS : UREA initialised sucessfully\n";
}
////////////////////////////////////////////////////////////////////////////
//
//  Function name :  InitialiseSuperBlock
//  Description:     It is used to initialise the contents of super block
//  Author :         Mangesh Ashok Bedre
//  Date :           10/08/2025
//
///////////////////////////////////////////////////////////////////////////

void InitialiseSuperBlock()
{
    superobj.TotalInodes = MAXINODE;
    superobj.FreeInodes = MAXINODE;

    cout<<"CVFS : super block initialised sucessfully\n";

}
////////////////////////////////////////////////////////////////////////////
//
//  Function name :  CreateDILB
//  Description:     It is used to create linked list of inode
//  Author :         Mangesh Ashok Bedre
//  Date :           10/08/2025
//
///////////////////////////////////////////////////////////////////////////

void CreateDILB()
{
    int i = 1;
    PINODE newn = NULL;
    PINODE temp = head;

    while(i <= MAXINODE)
    {
        newn = new INODE;

        newn->InodeNumber = 1;
        newn->FileSize = 0;
        newn->ActualFileSize = 0;
        newn->LinkCount = 0;
        newn->Permission = 0;
        newn->FileType = 0;
        newn->ReferenceCount = 0;
        newn->Buffer = NULL;
        newn->next = NULL;

        if(temp == NULL)
        {
            head = newn;
            temp = head;
        }
        else
        {
            temp->next = newn;
            temp = temp->next;
        }
        i++;
    }
    cout<<"CVFS : DILB created sucessfully\n";
}
////////////////////////////////////////////////////////////////////////////
//
//  Function name :  StartAuxillaryDataInitialisation
//  Description:     It is used to initialise the Auxillary data
//  Author :         Mangesh Ashok Bedre
//  Date :           10/08/2025
//
///////////////////////////////////////////////////////////////////////////

void StartAuxillaryDataInitialisation()
{
    strcpy(bootobj.Information , "Boot Process of Operating System Done");

    cout<<bootobj.Information<<"\n";

    InitialiseSuperBlock();
    
    CreateDILB();
    
    InitialiseUREA();

    cout<<"CVFS : Auxillary data initialised sucessfully\n";
}
////////////////////////////////////////////////////////////////////////////
//
//  Function name :  DispalyHelp
//  Description:     It is used to Display the information about command
//  Author :         Mangesh Ashok Bedre
//  Date :           11/08/2025
//
///////////////////////////////////////////////////////////////////////////

void DispalyHelp()
{
    printf("-----------------------------------------------------------------------------------\n");
    printf("-------------------------Command manual of CVFS------------------------------------\n");
    printf("-----------------------------------------------------------------------------------\n");

    // add more option here

    printf("man : It is used to display the specific manual page of command\n");
    printf("write : It is used to write the data into file\n");
    printf("ls : It is used to list out all files from directory\n");
    printf("read : It is used to read the data from the file\n");
    printf("stat : It is used to display statical information about file\n");
    printf("creat : It is used to create new regular file\n");
    printf("unlink : It is used to unlink the file\n");
    printf("cls : It is used to clear the console of marvellous CVFS\n");
    printf("exit : It is used to terminate the shell of marvellous  CVFS\n");
    

}
////////////////////////////////////////////////////////////////////////////
//
//  Function name :  ManPage
//  Description:     It is used to Display the manual page of the  command
//  Input :          It accept the command name
//  Output :         Display the manual details of the command
//  Author :         Mangesh Ashok Bedre
//  Date :           11/08/2025
//
///////////////////////////////////////////////////////////////////////////

void ManPage(
                char *name  // Name of command
            )
{
    if(strcmp(name,"creat") == 0)
    {
        printf("Description : This command is used to create regular file on our system\n");
        printf("Usage : create file_name Permission\n");
        printf("file_name : The name file that you want to create \n");
        printf("Permission : \n1 : read\n2 : write\n3 : readwite\n");
    }
    else if(strcmp(name,"exit") == 0)
    {
        printf("Description : This command is used to terminate shell od CVFS\n");
        printf("Usage : exit\n");
        
    }
    else if(strcmp(name,"unlink") == 0)
    {
        printf("Description : This command is used to delete regular file from our system\n");
        printf("Usage : unlink file_name \n");
        printf("file_name : The name file that you want to delete \n");
        
    }
    else if(strcmp(name,"stat") == 0)
    {
        printf("Description : This command is used to display statistical onfo about file from our system\n");
        printf("Usage : stat file_name \n");
        printf("file_name : The name file whose information you want to dispaly\n");
        
    }
    else if(strcmp(name,"ls") == 0)
    {
        printf("Description : This command is used to list all filename from directory\n");
        printf("Usage : ls\n");
       
    }
    else if(strcmp(name,"write") == 0)
    {
        printf("Description : This command is used to write the data into file\n");
        printf("Usage : write file_descriptor\n");
       
    }
    else if(strcmp(name,"read") == 0)
    {
        printf("Description : This command is used to read the data from file\n");
        printf("Usage : read file_descriptor size\n");
        printf("file_decriptor : Its a value returned by create system call\n");
        printf("size : Number of byte that you want to read\n");
    }

    // add more option here

    else
    {
        printf("\nNo Manual entry for %s\n",name);
    }
}

////////////////////////////////////////////////////////////////////////////
//
//  Function name :  isFileExists
//  Description:     It is used to check whether given file name exists or not
//  Input :          It accept the file name 
//  Output :         It return boolean value(True : if present, False : if not present)
//  Author :         Mangesh Ashok Bedre
//  Date :           11/08/2025
//
///////////////////////////////////////////////////////////////////////////

// helper function
bool isFileExists(
                    char *name // name of file that we want to check
                )
{
    bool bFlaf = false;
    PINODE temp = head;

    while(temp != NULL)
    {
        if((strcmp(name,temp->FileName) == 0) && temp->FileType == REGULARFILE)
        {
            bFlaf = true;
            break;
        }
        temp = temp->next;
    }
    return bFlaf;
}

////////////////////////////////////////////////////////////////////////////
//
//  Function name :  CreateFile
//  Description:     It is used to create new regular file
//  Input :          It accept the file name and permission
//  Output :         It return file descriptor
//  Author :         Mangesh Ashok Bedre
//  Date :           11/08/2025
//
///////////////////////////////////////////////////////////////////////////

int CreateFile(
                char * name,        // Name of file
                int permission      // Permission to create file
            )
{
    PINODE temp = head;
    int i = 0;

    printf("Current inode remaining %d\n",superobj.FreeInodes);
    //Filters

    // if file name missing
    if(name == NULL)
    {
        return ERR_INVALID_PARAMETER;
    }

    // if enterd permission is invalid
    if(permission < 1 || permission > 3)
    {
        return ERR_INVALID_PARAMETER;
    }

    // Check whether empty inode is there or not 
    if(superobj.FreeInodes == 0)
    {
        return ERR_NO_INODE;
    }

    //check whether file already exists or not
    if(isFileExists(name))
    {
        return ERR_FILE_ALREADY_EXIST;
    }

    // Loop to search free inode

    while(temp != NULL)
    {
        if(temp->FileType == 0)
        {
            break;
        }
        temp = temp->next;
    }

    // inode not found
    if(temp == NULL)
    {
        printf("Inode not found\n");
        return ERR_NO_INODE;
    }

    // serach first non null value from UFDT
    for(i = 0; i < MAXINODE; i++)
    {
        if(uareaobj.UFDT[i] == NULL)
        {
            break;
        }
    }
    if(i == MAXINODE)
    {
        printf("Unable to opened file as max opened  limit  reached\n");
    }

    // Allocate memory for file table
    uareaobj.UFDT[i] = (PFILETABLE)malloc(sizeof(FileTable));

    // initialise file table
    uareaobj.UFDT[i]->ReadOffset = 0;
    uareaobj.UFDT[i]->WriteOffset = 0;
    uareaobj.UFDT[i]->Count = 1;
    uareaobj.UFDT[i]->Mode = permission;

    // connect to IIT
    uareaobj.UFDT[i]->ptrinode = temp;

    strcpy(uareaobj.UFDT[i]->ptrinode->FileName,name);
    uareaobj.UFDT[i]->ptrinode->FileSize = MAXFILESIZE;
    uareaobj.UFDT[i]->ptrinode->ActualFileSize = 0;
    uareaobj.UFDT[i]->ptrinode->FileType = REGULARFILE;
    uareaobj.UFDT[i]->ptrinode->ReferenceCount = 1;
    uareaobj.UFDT[i]->ptrinode->LinkCount = 1;
    uareaobj.UFDT[i]->ptrinode->Permission = permission;


    // Allocate memory for buffer

    uareaobj.UFDT[i]->ptrinode->Buffer = (char *)malloc(MAXFILESIZE);

    // Decrement the number of free inode
    superobj.FreeInodes--;

    return i;
    
}

////////////////////////////////////////////////////////////////////////////
//
//  Function name :  UnlinkFile
//  Description:     It is used to delete a regular file
//  Input :          It accept the file name 
//  Output :         It return nothing
//  Author :         Mangesh Ashok Bedre
//  Date :           15/08/2025
//
///////////////////////////////////////////////////////////////////////////

// Mangesh/CVFS > unlink name
int UnlinkFile(
                    char *name      // Name of file
                )
{
    int i = 0;

    if(name == NULL)
    {
        return ERR_INVALID_PARAMETER;
    }
    if(isFileExists(name) == false)
    {
        return ERR_FILE_NOT_EXIST;
    }

    for(i = 0; i < MAXINODE; i++)
    {
        if(uareaobj.UFDT[i] != NULL)
        {
            if(strcmp(uareaobj.UFDT[i]->ptrinode->FileName,name) == 0)
            {
                //Deallocate memory of buffer 
                free(uareaobj.UFDT[i]->ptrinode->Buffer);

                //reset all value of inode
                uareaobj.UFDT[i]->ptrinode->FileSize = 0;
                uareaobj.UFDT[i]->ptrinode->ActualFileSize = 0;
                uareaobj.UFDT[i]->ptrinode->LinkCount = 0;
                uareaobj.UFDT[i]->ptrinode->Permission = 0;
                uareaobj.UFDT[i]->ptrinode->FileType = 0;
                uareaobj.UFDT[i]->ptrinode->ReferenceCount =0 ;

                //deallocate memory of FileTable

                free(uareaobj.UFDT[i]);

                //set NULL to ufdt member
                uareaobj.UFDT[i] = NULL;

                //Increment the value FreeInode Count
                superobj.FreeInodes++;
                break;

            }//end of if
        }// end of if

    }// end of for



    return EXECUTE_SUCCESS;

}

////////////////////////////////////////////////////////////////////////////
//
//  Function name :  ls_File
//  Description:     It is used to display information about all files in the directory.
//  Input :          nothing
//  Output :         nothing
//  Author :         Mangesh Ashok Bedre
//  Date :           15/08/2025
//
///////////////////////////////////////////////////////////////////////////

// Mangesh/CVFS > ls
void ls_File()
{
    PINODE temp = head;
    
    while(temp != NULL)
    {
        if(temp->FileType != 0)
        {
            printf("%s\n",temp->FileName);
        }

        temp = temp->next;
    }
}

////////////////////////////////////////////////////////////////////////////
//
//  Function name :  stat_file
//  Description:     It is used to display information about given file
//  Input :          It accept the file name 
//  Output :         It return nothing
//  Author :         Mangesh Ashok Bedre
//  Date :           15/08/2025
//
///////////////////////////////////////////////////////////////////////////

// Mangesh/CVFS > stat file_name

int stat_file(
                    char *name      // Name of file
                )
{
    PINODE temp = head;

    if(name == NULL)
    {
        return ERR_INVALID_PARAMETER;
    }

    if(isFileExists(name) == false)
    {
        return ERR_FILE_NOT_EXIST;
    }

    while(temp != NULL)
    {
        if((strcmp(name,temp->FileName) == 0) && (temp->FileType != 0))
        {
            printf("-----------------Statical Information of file------------------------\n");
            printf("File name : %s\n",temp->FileName);
            printf("File size on disk : %d bytes\n",temp->FileSize);
            printf("Actual file size : %d bytes \n",temp->ActualFileSize);
            printf("Link Count : %d\n",temp->LinkCount);
            printf("File Permission : ");

            if(temp->Permission == READ)
            {
                printf("Read\n");
            }
            else if(temp->Permission == WRITE)
            {
                printf("Write\n");
            }
            else if( temp->Permission == WRITE + READ)
            {
                printf("Read + write \n");
            }
            printf("File type : ");

            if(temp->FileType == REGULARFILE)
            {
                printf("Regular file\n");
            }
            else if(temp->FileType == SPECIALFILE)
            {
                printf("Special File\n");
            }

            printf("------------------------------------------------------------------------\n");

        }

        temp = temp->next;
    }
    

    return EXECUTE_SUCCESS;

}

////////////////////////////////////////////////////////////////////////////
//
//  Function name :  write_file
//  Description:     It is used to write content into the file
//  Input :          file descriptor,
//                   Address of buffer which contains data,
//                   Size of data that we want to write
//  Output :         Number of bytes successfully write iinto file
//  Author :         Mangesh Ashok Bedre
//  Date :           15/08/2025
//
///////////////////////////////////////////////////////////////////////////

// Mangesh/CVFS > write fd

int write_file( 
                int fd,         // file descriptor
                char *data ,    // Data that we want to write
                int size        // Size of data that we want to write
            )
{
    unsigned long int offset = 0;
    printf("File descriptor : %d\n",fd);
    printf("Data that we want to write : %s\n",data);
    printf("number of bytes that we want to write : %d\n",size);

    //filter
    
    // Invalid value of fd
    if(fd < 0 || fd > MAXOPENEDFILES)
    {
        return ERR_INVALID_PARAMETER;
    }
    
    // File is not opened or created with the given fd
    if(uareaobj.UFDT[fd] == NULL)
    {
        return ERR_FILE_NOT_EXIST;
    }

    // if there is no permission to write the data into the file
    if(uareaobj.UFDT[fd]->ptrinode->Permission  < WRITE)
    {
        return ERR_PERMISSION_DENIED;
    }

    // Unable to write into file as Insufficient space
    if((MAXFILESIZE - uareaobj.UFDT[fd]->WriteOffset) < size)
    {
        return ERR_INSUFFICIENT_SPACE;
    }


    // write the actual data
    strncpy(uareaobj.UFDT[fd]->ptrinode->Buffer + uareaobj.UFDT[fd]->WriteOffset,data,size);

    // Update the writeOffset
    uareaobj.UFDT[fd]->WriteOffset = uareaobj.UFDT[fd]->WriteOffset + size;

    //Update the actual size of file after writing the data
    uareaobj.UFDT[fd]->ptrinode->ActualFileSize = uareaobj.UFDT[fd]->ptrinode->ActualFileSize + size;

    return 0;
}

////////////////////////////////////////////////////////////////////////////
//
//  Function name :  read_file
//  Description:     It is used to read content from the file
//  Input :          file descriptor,
//                   Address of Empty buffer ,
//                   Size of data that we want to read
//  Output :         Number of bytes successfully read into file
//  Author :         Mangesh Ashok Bedre
//  Date :           15/08/2025
//
///////////////////////////////////////////////////////////////////////////

// Mangesh/CVFS > read fd size

int read_file(
                int fd,         // File descriptor
                char *data,     // Addres of empty buffer
                int size        // Number of bytes you want to read
            )

{
    // Invalid value of fd
    if(fd < 0 || fd > MAXOPENEDFILES)
    {
        return ERR_INVALID_PARAMETER;
    }

    if(data == NULL || size <= 0)
    {
        return ERR_INVALID_PARAMETER;
    }
    
    // File is not opened or created with the given fd
    if(uareaobj.UFDT[fd] == NULL)
    {
        return ERR_FILE_NOT_EXIST;
    }

    // if there is no permission to read the data from the file
    if(uareaobj.UFDT[fd]->ptrinode->Permission  <  READ)
    {
        return ERR_PERMISSION_DENIED;
    }

    // Unable to read  as Insufficient data
    if((MAXFILESIZE - uareaobj.UFDT[fd]->ReadOffset) < size)
    {
        return ERR_INSUFFICIENT_DATA;
    }

    strncpy(data,uareaobj.UFDT[fd]->ptrinode->Buffer + uareaobj.UFDT[fd]->ReadOffset,size);

    uareaobj.UFDT[fd]->ReadOffset = uareaobj.UFDT[fd]->ReadOffset + size;

    return EXECUTE_SUCCESS;
}

////////////////////////////////////////////////////////////////////////////
//
//  Entry point function of project (main)
//
///////////////////////////////////////////////////////////////////////////

int main()
{
    char str[80] = {'\0'};
    int iCount = 0;
    int iRet = 0;
    char Command[5][80];
    char InputBuffer[MAXFILESIZE] = {'\0'};
    char *EmptyBuffer = NULL;

    StartAuxillaryDataInitialisation() ;

    cout<<"-----------------------------------------------------------------------------------\n";
    cout<<"------------------------- CVFS started Succesfully---------------------------------\n";
    cout<<"-----------------------------------------------------------------------------------\n";

    while(1)
    {   
        fflush(stdin);

        strcpy(str,"");

        printf("\nMangesh\\CVFS > ");
        fgets(str,sizeof(str),stdin);    //stdin -> keyboard

        iCount = sscanf(str,"%s %s %s %s",Command[0],Command[1],Command[2],Command[3]);

        fflush(stdin);

        if(iCount == 1)
        {   
            // Mangesh/CVFS > exit
            
            if(stricmp(Command[0],"exit") == 0)
            {
                printf("\nThank you for using marvellous CVFS\n");
                printf("Deallocating all the resouces...\n");
                break;
            }

            // Mangesh/CVFS > --help

            else if(strcmp(Command[0],"help") == 0)
            {
                DispalyHelp();
            }

            // Mangesh/CVFS > clear

            else if(strcmp(Command[0],"cls") == 0)
            {
                system("cls");
            }

            // Mangesh/CVFS > ls
            else if(strcmp(Command[0],"ls") == 0)
            {
                ls_File();
            }
            else
            {   
                printf("zsh : Command not found");
                printf("Please refer Help option or use man command");
            }   // end of invalid command part


        }   // end of if (icount == 1)


        

        else if(iCount == 2)
        {

            // Mangesh/CVFS > man
            if(strcmp(Command[0],"man") == 0)
            {
                ManPage(Command[1]);
            }

            // Mangesh/CVFS > unlink demo.txt
            else if(strcmp(Command[0],"unlink")==0)
            {
                iRet = UnlinkFile(Command[1]);

                if(iRet == EXECUTE_SUCCESS)
                {
                    printf(" Unlink Operation successfully performed\n");
                }
                else if( iRet == ERR_FILE_NOT_EXIST)
                {
                    printf("Error : Unable to do display activity as file not present\n");
                }
                else if(iRet == ERR_INVALID_PARAMETER)
                {
                    printf("Error : Invalid parameter for the function\n");
                    printf("Please check man page for more details\n");

                }
            }

            // Mangesh/CVFS > stat demo.txt
            else if(strcmp(Command[0],"stat") == 0)
            {
                iRet = stat_file(Command[1]);
                
                if( iRet == ERR_FILE_NOT_EXIST)
                {
                    printf("Error : Unable to  Display statistic as file not present\n");
                }
                else if(iRet == ERR_INVALID_PARAMETER)
                {
                    printf("Error : Invalid parameter for the function\n");
                    printf("Please check man page for more details\n");

                }
            }

            // Mangesh/CVFS >  write 3            here 3 is fd
            else if(strcmp(Command[0],"write") == 0)
            {
                
                printf("Please enter the data you want to write into file : \n");
                //scanf("%s[^'\n']",InputBuffer);

                fgets(InputBuffer,MAXFILESIZE,stdin);
                
                iRet = write_file(atoi(Command[1]),InputBuffer,strlen(InputBuffer)-1);

                if(iRet == ERR_INSUFFICIENT_SPACE)
                {
                    printf("Error : Insufficient space for the data block for file\n");
                }
                else if(iRet == ERR_PERMISSION_DENIED)
                {
                    printf("Error : Unable to write as there is no write permission\n");
                }
                else if(iRet == ERR_INVALID_PARAMETER)
                {
                    printf("Error : Invalid parameter for the function\n");
                    printf("Please check man page for more details\n");
                }
                else if(iRet == ERR_FILE_NOT_EXIST)
                {
                    printf("Fd is Invalid \n");
                }
                else
                {
                    printf(" %d bytes gets successfully written\n",iRet);
                    printf("Data from file is : %s\n",uareaobj.UFDT[0]->ptrinode->Buffer);
                }
            }
            else
            {   
                printf("zsh : Command not found\n");
                printf("Please refer Help option or use man command\n");
            }   

        }    // end of if icount == 2

        else if(iCount == 3)
        {
            // Mangesh/CVFS > creat Ganesh.txt 3

            if(strcmp(Command[0],"creat") == 0)
            {
                iRet = CreateFile(Command[1],atoi(Command[2])); // atoi -> asckii to integer

                if(iRet == ERR_INVALID_PARAMETER)
                {
                    printf("Error : Invalid parameter for the function\n");
                    printf("Please check man page for more details\n");

                }
                else if(iRet == ERR_NO_INODE)
                {
                    printf("Error : Unable to create file as there is no Inodes\n");
                }
                else if(iRet == ERR_FILE_ALREADY_EXIST)
                {
                    printf("Error : Unable to create file as file already exists\n");
                }
                else
                {
                    printf("File is successfully created with fd %d\n",iRet);
                }


            }
            // Mangesh/CVFS > read 3 10       3-> fd  10->size
            else if(strcmp(Command[0],"read") == 0)
            {
                EmptyBuffer = (char *)malloc(atoi(Command[2]));
                iRet = read_file(atoi(Command[1]),EmptyBuffer,atoi(Command[2]));

                if(iRet == ERR_INSUFFICIENT_DATA)
                {
                    printf("Error : Insufficient data of the data block  file\n");
                }
                else if(iRet == ERR_PERMISSION_DENIED)
                {
                    printf("Error : Unable to read as there is no read permission\n");
                }
                else if(iRet == ERR_INVALID_PARAMETER)
                {
                    printf("Error : Invalid parameter for the function\n");
                    printf("Please check man page for more details\n");
                }
                else if(iRet == ERR_FILE_NOT_EXIST)
                {
                    printf("Fd is Invalid \n");
                }
                else
                {
                    printf("Read operation is Successful \n");
                    printf("Data from file : %s\n",EmptyBuffer);

                    free(EmptyBuffer);
                }
            }

            else
            {   
                printf("zsh : Command not found");
                printf("Please refer Help option or use man command");
            }  
        }    // end of if icount == 3
        else if(iCount == 4)
        {

        }    // end of if icount == 4
        else
        {   
            printf("zsh : Command not found");
            printf("Please refer Help option or use man command");
        }   // end of invalid command part

    }//End of while(custom shell)

    return 0;

}//End of main