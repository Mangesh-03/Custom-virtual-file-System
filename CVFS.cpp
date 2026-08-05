////////////////////////////////////////////////////////////////////////////
//
//  Header file inclusion
//
///////////////////////////////////////////////////////////////////////////

#include"CVFS.h";

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

    strcpy(uareaobj.WorkingDir,"root"); 

    uareaobj.dirInode = 1;

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
//  Function name :  InitialiseDirEntry
//  Description:     It is used to initialise Root Director of file system.
//  Author :         Mangesh Ashok Bedre
//  Date :           19/01/2026
//
///////////////////////////////////////////////////////////////////////////

void InitialiseDirEntry()
{
    PINODE root = head;

    // chose inode 1 for root directory
    if(root == NULL)
    {
        printf("Creating root directory failed\n");
        return;
    }
    
    //Initialising root Directory inode
    root->FileSize = MAXFILESIZE;
    root->ActualFileSize = 0;
    root->FileType = SPECIALFILE;
    root->ReferenceCount = 1;
    root->Permission = READ+WRITE;

    // Allocate memory for Directory Entries
    root->Buffer = (char*)malloc(MAXFILESIZE);

    memset(root->Buffer, 0, MAXFILESIZE);

    superobj.FreeInodes--;

    printf("CVFS : Created root directory successfully\n");
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

        newn->InodeNumber = i;
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

    InitialiseDirEntry();

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
    printf("open : It is used to open regular file\n");
    printf("close : It is used to close regular file\n");
    printf("mkdir : It is used to create new directory\n");
    printf("rmdir : It is used to delete  directory\n");
    printf("cd : It is used to change directory from one directory to another\n");
    printf("pwd : It is used to display current working directory\n");
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
        printf("Usage : create <file_name> <Permission>\n");
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
        printf("Usage : unlink <file_name> \n");
        printf("file_name : The name file that you want to delete \n");
        
    }
    else if(strcmp(name,"stat") == 0)
    {
        printf("Description : This command is used to display statistical onfo about file from our system\n");
        printf("Usage : stat <file_name> \n");
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
        printf("Usage : write <file_descriptor>\n");
       
    }
    else if(strcmp(name,"read") == 0)
    {
        printf("Description : This command is used to read the data from file\n");
        printf("Usage : read <file_descriptor> <size>\n");
        printf("file_decriptor : Its a value returned by create system call\n");
        printf("size : Number of byte that you want to read\n");
    }
    else if(strcmp(name,"open") == 0)
    {
        printf("Description : This command is used to open the file\n");
        printf("Usage : open <file_name>\n");
        printf("file_name : The name of file that you want to open\n");
    }
    else if(strcmp(name,"close") == 0)
    {
        printf("Description : This command is used to close the file\n");
        printf("Usage : close <file_name>\n");
        printf("file_name : The name of file that you want to close\n");
    }
    else if(strcmp(name,"mkdir") == 0)
    {
        printf("Description : This command is used to Create Directory\n");
        printf("Usage : mkdir <directory_name>\n");
        printf("directory_name : The name of directory that you want to create\n");
    }
    else if(strcmp(name,"rmdir") == 0)
    {
        printf("Description : This command is used to delete Directory\n");
        printf("Usage : rmdir <directory_name>\n");
        printf("directory_name : The name of directory that you want to delete\n");
    }
    else if(strcmp(name,"cd") == 0)
    {
        printf("Description : This command is used to change Directory\n");
        printf("Usage : cd <directory_name>\n");
        printf("directory_name : The name of directory that you want to change\n");
    }
    else if(strcmp(name,"man") == 0)
    {
        printf("About : It is used to display manual page\n");
        printf("Usage : man <command_name>\n");
        printf("command_name : It is a name of command\n");
    }
    else if(strcmp(name,"clear") == 0)
    {
        printf("About : It is used to clear the shell\n");
        printf("Usage : clear\n");
    }
    else if(strcmp(name,"pwd") == 0)
    {
        printf("About : It is used to display the current working directory\n");
        printf("Usage : pwd\n");
    }

    // add more option here

    else
    {
        printf("\nNo Manual entry for %s\n",name);
    }
}

////////////////////////////////////////////////////////////////////////////
//
//  Function name :  GetCurrentDirBuffer
//  Description:     It is used to get buffer of current Directory
//  Input :          -
//  Output :         Returns Buffer of Current directory .
//  Author :         Mangesh Ashok Bedre
//  Date :           09/02/2026
//
///////////////////////////////////////////////////////////////////////////

struct DirEntry* GetCurrentDirBuffer()
{
    PINODE temp = head;
    while(temp != NULL)
    {
        if(temp->InodeNumber == uareaobj.dirInode)
        {
            return (struct DirEntry*)temp->Buffer;
        }
        temp = temp->next;
    }
    return NULL;
}

////////////////////////////////////////////////////////////////////////////
//
//  Function name :  GetInodeOfFile
//  Description:     It is used to get entry of file from directory
//  Input :          It accept the file name .
//  Output :         InodeNumber
//  Author :         Mangesh Ashok Bedre
//  Date :           20/01/2026
//
///////////////////////////////////////////////////////////////////////////

int GetInodeOfFile(
                    char *name
                  )
{
    PINODE temp = head;
    int MaxEntry = 0,i = 0;
    int InodeNumber = 0;

    struct DirEntry* DIR = NULL;

    // If we want inode of root. we have give it manually we root entry not register any where.
    if((strcmp(name,"root") == 0)) 
    {
        cout << "going from here" <<"\n";
        return 1;
    }
    // Check we are in which current dir and get its Buffer
    DIR = GetCurrentDirBuffer();
    if(DIR == NULL) 
    {
        cout << "zero from here" <<"\n";
        return false;
    }

    cout << "File Name : " << DIR->FileName << "\n";
    cout << "Inode No : " << DIR->InodeNumber << "\n";

    MaxEntry = MAXFILESIZE / sizeof(struct DirEntry);

    // Searching for of given file name inode inside current working directory
    for(i = 0 ; i < MaxEntry; i++)
    {
        if(strcmp(DIR[i].FileName,name) == 0)
        {
            cout << "Inside break\n";
            InodeNumber = DIR[i].InodeNumber;
            break;
        }
    }

    if(i == MaxEntry)
    {
        return ERR_NO_ENTRY_DIR;
    }
    else
    {
        return InodeNumber;
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
    bool bFlag = false;
    PINODE temp = head;
    int iRet = 0;

    // Getting inode number of name
    iRet = GetInodeOfFile(name);

    // if name entry not present in directory
    if(iRet == ERR_NO_ENTRY_DIR)
    {
        return bFlag;
    }

    // Entry present but check file exists
    while(temp != NULL)
    {
        if((temp->FileType != 0) && ((temp->InodeNumber) == iRet))
        {
            bFlag = true;
            break;
        }
        temp = temp->next;
    }

    return bFlag;
}

////////////////////////////////////////////////////////////////////////////
//
//  Function name :  AddFileEntryInDir
//  Description:     It is used to register entry of file into directory
//  Input :          It accept the file name and InodeNumber
//  Output :         Nothing
//  Author :         Mangesh Ashok Bedre
//  Date :           20/01/2026
//
///////////////////////////////////////////////////////////////////////////

bool AddFileEntryInDir(
                            char* name,
                            int inode
                        )
{
    PINODE temp = head;
    int MaxEntry = 0,i = 0;
    bool Flag = false;

    struct DirEntry* DIR = GetCurrentDirBuffer();
    if(DIR == NULL) return Flag;
    
    MaxEntry = MAXFILESIZE / sizeof(struct DirEntry);

    for(i = 0; i < MaxEntry; i++)
    {
        if(DIR[i].InodeNumber == 0 )
        {
            strcpy(DIR[i].FileName,name);
            DIR[i].InodeNumber = inode;
            Flag = true;
            break;
        }
    }

    return Flag;
}

////////////////////////////////////////////////////////////////////////////
//
//  Function name :  OpenFile
//  Description:     It is used to open regular file
//  Input :          It accept the file name and permission
//  Output :         It return file descriptor
//  Author :         Mangesh Ashok Bedre
//  Date :           20/01/2026
//
///////////////////////////////////////////////////////////////////////////

int OpenFile(
                char *name
            )
{
    int iRet = 0,i = 0;
    PINODE temp = head;

    iRet = GetInodeOfFile(name);

    if(iRet == ERR_NO_ENTRY_DIR)
    {
        return ERR_FILE_NOT_EXIST;
    }

    // Finding inode of file from DILB
    while(temp != NULL)
    {
        if((temp->InodeNumber == iRet) && (temp->FileType == 1))
        {
            break;
        }

        temp = temp->next;
    }

    // Finding NULL entry from UFDT
    for(i = 0; i < MAXOPENEDFILES; i++)
    {
        if(uareaobj.UFDT[i] == NULL)
        {
            break;
        }
    }

    if(i == MAXOPENEDFILES)
    {
        return ERR_MAX_FILE_OPEN;
    }

    uareaobj.UFDT[i] = (PFILETABLE)malloc(sizeof(FILETABLE));

    
    uareaobj.UFDT[i]->ReadOffset = 0;
    uareaobj.UFDT[i]->WriteOffset = 0;
    uareaobj.UFDT[i]->Count = 1;
    
    //Connecting to inode
    uareaobj.UFDT[i]->ptrinode = temp;

    return i;

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
        return ERR_NO_INODE;
    }

    // serach first non null value from UFDT
    for(i = 0; i < MAXOPENEDFILES; i++)
    {
        if(uareaobj.UFDT[i] == NULL)
        {
            break;
        }
    }

    if(i == MAXOPENEDFILES)
    {    
        return ERR_MAX_FILE_OPEN;
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

    // strcpy(uareaobj.UFDT[i]->ptrinode->FileName,name);
    uareaobj.UFDT[i]->ptrinode->FileSize = MAXFILESIZE;
    uareaobj.UFDT[i]->ptrinode->ActualFileSize = 0;
    uareaobj.UFDT[i]->ptrinode->FileType = REGULARFILE;
    uareaobj.UFDT[i]->ptrinode->ReferenceCount = 1;
    uareaobj.UFDT[i]->ptrinode->LinkCount = 1;
    uareaobj.UFDT[i]->ptrinode->Permission = permission;

    // Registering file entry into Directory
    if(AddFileEntryInDir(name, temp->InodeNumber) == false) {
        // Rollback!
        free(uareaobj.UFDT[i]->ptrinode->Buffer);
        free(uareaobj.UFDT[i]);
        uareaobj.UFDT[i] = NULL;
        superobj.FreeInodes++;
        temp->FileType = 0; // Mark inode as free again
        return ERR_NO_ENTRY_DIR;
    }

    // Allocate memory for buffer
    uareaobj.UFDT[i]->ptrinode->Buffer = (char *)malloc(MAXFILESIZE);

    // Decrement the number of free inode
    superobj.FreeInodes--;

    return i;
    
}

////////////////////////////////////////////////////////////////////////////
//
//  Function name :  isOpen
//  Description:     It is used to check either file is opened or not.
//  Input :          fileName
//  Output :         bool 
//  Author :         Mangesh Ashok Bedre
//  Date :           28/01/2026
//
///////////////////////////////////////////////////////////////////////////

bool isOpen(
                char *name
           )
{
    int i = 0,iRet = 0;
    bool bFlag = false;

    iRet = GetInodeOfFile(name);

    if(iRet == ERR_NO_ENTRY_DIR)
    {
        printf("File not exists\n");
        return bFlag;
    }

    // Checking UFDT for Not-NULL entry and check whether given file is opend or not 
    for(i = 0; i < MAXOPENEDFILES; i++)
    {
        if(uareaobj.UFDT[i] != NULL)
        {
            if(((uareaobj.UFDT[i]->ptrinode->InodeNumber) == iRet))
            {
                bFlag = true;
                break;

            }//end of if
        }// end of if

    }// end of for

    return bFlag;

}
////////////////////////////////////////////////////////////////////////////
//
//  Function name :  closeFile
//  Description:     It is used to closed the open file.
//  Input :          fileName
//  Output :         int 
//  Author :         Mangesh Ashok Bedre
//  Date :           28/01/2026
//
///////////////////////////////////////////////////////////////////////////

int closeFile(
                char *name
            )
{
    int i = 0,iRet = 0;
    
    // Check is file name is missing
    if(name == NULL)
    {
        return ERR_INVALID_PARAMETER;
    }

    if(isOpen(name) == false)
    {
        return ERR_FILE_NOT_OPEN;
    }

    iRet = GetInodeOfFile(name);

    for(i = 0; i < MAXOPENEDFILES; i++)
    {
        if(uareaobj.UFDT[i] != NULL)
        {
            if(((uareaobj.UFDT[i]->ptrinode->InodeNumber) == iRet))
            {
                //deallocate memory of FileTable

                free(uareaobj.UFDT[i]);

                //set NULL to ufdt member
                uareaobj.UFDT[i] = NULL;

                break;   

            }//end of if
        }// end of if

    }// end of for

    return EXECUTE_SUCCESS;
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
    int iRet = 0,i = 0;
    PINODE temp = head;
    int MaxEntry = 0;
    struct DirEntry *DIR = NULL;
    
    DIR = GetCurrentDirBuffer();

    if(DIR == NULL)
    {
        printf("Error: Could not get current directory buffer\n");
        return ERR_INVALID_PARAMETER;
    }

    MaxEntry = MAXFILESIZE / sizeof(struct DirEntry);

    //Filters

    // if name is missing
    if(name == NULL)
    {
        return ERR_INVALID_PARAMETER;
    }

    //File not exist
    if(isFileExists(name) == false)
    {
        return ERR_FILE_NOT_EXIST;
    }

    // Check whether file is opened before it get deleted
    iRet = GetInodeOfFile(name);

    // Instead of calling closeFile(name), do a full sweep:
    for(i = 0; i < MAXOPENEDFILES; i++)
    {
        if(uareaobj.UFDT[i] != NULL && uareaobj.UFDT[i]->ptrinode->InodeNumber == iRet)
        {
            free(uareaobj.UFDT[i]);
            uareaobj.UFDT[i] = NULL;
        }
    }

    //clearing data from inode
    while(temp != NULL)
    {
        if((iRet == temp->InodeNumber) && (temp->FileType == REGULARFILE))
        {
            temp->FileSize = 0;
            temp->ActualFileSize = 0;
            temp->LinkCount = 0;
            temp->Permission = 0;
            temp->FileType = 0;
            temp->ReferenceCount =0 ; 

            //Increment the value FreeInode Count
            superobj.FreeInodes++;

            break;
        }

        temp = temp->next;
    }

    // Clearing entry from Directory File
    for(i = 0; i < MaxEntry; i++)
    {
        if((DIR[i].InodeNumber == iRet))
        {
            strcpy(DIR[i].FileName,"");
            DIR[i].InodeNumber = 0;
            break;
        }
    }

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
    PINODE temp  = head;
    struct DirEntry* dir = NULL;

    int MaxEntry = MAXFILESIZE/sizeof(DirEntry);

    if(strcmp(uareaobj.WorkingDir,"root") == 0)
    {
        dir = (struct DirEntry*)temp->Buffer; 
    }
    else
    {
        while(temp != NULL)
        {
            if(((uareaobj.dirInode) == temp->InodeNumber) && temp->FileType == SPECIALFILE)
            {
                dir = (struct DirEntry *)temp->Buffer;
                break;
            }
            temp = temp->next;
        }
    }

    printf("-------------------------------------------------------------------\n");
    printf("----------------Marvellous CVFS Files Information------------------\n");
    printf("-------------------------------------------------------------------\n\n");
    printf("Sr.no              File/Directory\n");
    printf("-------------------------------------------------------------------\n");

    for(int i = 0; i < MaxEntry; i++)
    {     
        if(dir[i].InodeNumber != 0)
        {
            printf("%d\t\t\t%s\n",i+1,dir[i].FileName);
        }
        
    }
    printf("\n-------------------------------------------------------------------\n");
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
    int iRet = 0;

    if(name == NULL)
    {
        return ERR_INVALID_PARAMETER;
    }

    if(isFileExists(name) == false)
    {
        return ERR_FILE_NOT_EXIST;
    }

    iRet = GetInodeOfFile(name);

    while(temp != NULL)
    {
        if((iRet == temp->InodeNumber) && (temp->FileType != 0))
        {
            printf("\n-------------------------------------------------------------------\n");
            printf("-----------------Statical Information of file------------------------\n");
            printf("-------------------------------------------------------------------\n\n");
            printf("File name : %s\n",name);
            printf("File size on disk : %d bytes\n",temp->FileSize);
            printf("Actual file size : %d bytes \n",temp->ActualFileSize);
            printf("Link Count : %d\n",temp->LinkCount);
            printf("Inode Number : %d\n",iRet);
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
            break;
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

    return size;
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
    if((uareaobj.UFDT[fd]->ptrinode->ActualFileSize - uareaobj.UFDT[fd]->ReadOffset) < size)
    {
        return ERR_INSUFFICIENT_DATA;
    }

    strncpy(data,uareaobj.UFDT[fd]->ptrinode->Buffer + uareaobj.UFDT[fd]->ReadOffset,size);

    uareaobj.UFDT[fd]->ReadOffset = uareaobj.UFDT[fd]->ReadOffset + size;

    return EXECUTE_SUCCESS;
}

////////////////////////////////////////////////////////////////////////////
//
//  Function name :  MakeDir
//  Description:     It is used to create directory file
//  Input :          It accept the dir file name 
//  Output :         int
//  Author :         Mangesh Ashok Bedre
//  Date :           29/01/2026
//
///////////////////////////////////////////////////////////////////////////

int MakeDir(
                char* name
            )
{
    PINODE temp = head;
    int i = 0;
    
    // name of file missing 
    if(name == NULL)
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

    while(temp != NULL)
    {
        if(temp->FileType == 0)
        {
            break;
        }
        temp = temp -> next;
    }

    // no inode remain for make new file
    if(temp == NULL)
    {
        return ERR_NO_INODE;
    }

    //Initialising inode member
    temp->FileType = SPECIALFILE;
    temp->FileSize = MAXFILESIZE;
    temp->ActualFileSize = 0;
    temp->ReferenceCount = 1; // It is referenced by the parent directory
    temp->Permission = READ + WRITE; // Give permissions

    //Allocate memory for file data(data block)
    temp->Buffer = (char*)malloc(MAXFILESIZE);

    memset(temp->Buffer,'\0',MAXFILESIZE);

    //Registering entry of new dir in root or current directory
    AddFileEntryInDir(name,temp->InodeNumber);
    
    // Deallocate memory of fileTable
    // free(uareaobj.UFDT[i]);
    // uareaobj.UFDT[i] = NULL;
    
    superobj.FreeInodes--;

    return EXECUTE_SUCCESS;

}

////////////////////////////////////////////////////////////////////////////
//
//  Function name :  ChangeDir
//  Description:     It is used to change current directory file
//  Input :          It accept the dir file name 
//  Output :         int
//  Author :         Mangesh Ashok Bedre
//  Date :           29/01/2026
//
///////////////////////////////////////////////////////////////////////////

int ChangeDir(
                char *name
            )
{
    int iRet = 0;
    
    if(name == NULL)
    {
        return ERR_INVALID_PARAMETER;
    }

    if(isFileExists(name) == false)
    {
        return ERR_FILE_NOT_EXIST;
    }

    // changing current directory
    uareaobj.dirInode = GetInodeOfFile(name);
    strcpy(uareaobj.WorkingDir,name);

    return EXECUTE_SUCCESS;

}

////////////////////////////////////////////////////////////////////////////
//
//  Function name :  getCurrentDir
//  Description:     It is used to get current directory file
//  Input :          -
//  Output :         -
//  Author :         Mangesh Ashok Bedre
//  Date :           09/02/2026
//
///////////////////////////////////////////////////////////////////////////

void getCurrentDir()
{
    printf("Current Dir Name : %s\n",uareaobj.WorkingDir);
    printf("Current Dir inode : %d\n",uareaobj.dirInode);
}