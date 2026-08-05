#ifndef CVFS_H
#define CVFS_H

// Header files
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <iostream>

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
#define ERR_NO_ENTRY_DIR -8
#define ERR_MAX_FILE_OPEN -9
#define ERR_FILE_NOT_OPEN -10

////////////////////////////////////////////////////////////////////////////
//
//  Function Declaration
//
///////////////////////////////////////////////////////////////////////////

void InitialiseUREA();
void InitialiseDirEntry();
void InitialiseSuperBlock();
void CreateDILB();
void StartAuxillaryDataInitialisation();
void DispalyHelp();

void ManPage(
                char *name  // Name of command
            );

int GetInodeOfFile(
                    char *name
                  );
bool isFileExists(
                    char *name // name of file that we want to check
                );

bool AddFileEntryInDir(
                            char* name,
                            int inode
                        );
int OpenFile(
                char *name
            );
int CreateFile(
                char * name,        // Name of file
                int permission      // Permission to create file
            );
bool isOpen(
                char *name
           );
int closeFile(
                char *name
            );
int UnlinkFile(
                    char *name      // Name of file
                );
void ls_File();

int stat_file(
                    char *name      // Name of file
                );
int write_file( 
                int fd,         // file descriptor
                char *data ,    // Data that we want to write
                int size        // Size of data that we want to write
            );

int read_file(
                int fd,         // File descriptor
                char *data,     // Addres of empty buffer
                int size        // Number of bytes you want to read
            );

int MakeDir(
                char* name
            );

int ChangeDir(
                char *name
            );
void getCurrentDir();        


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
    char WorkingDir[50];
    int dirInode;
    PFILETABLE UFDT[MAXOPENEDFILES];

};

////////////////////////////////////////////////////////////////////////////
//
//  Structure name : DirEntry
//  Description :    Holds File names and its Inode Numbers
//
///////////////////////////////////////////////////////////////////////////

struct DirEntry
{
    char FileName[20];
    int InodeNumber;
};

////////////////////////////////////////////////////////////////////////////
//
//  Global variables and object used in the project
//
///////////////////////////////////////////////////////////////////////////

extern SuperBlock superobj;
extern PINODE head;
extern UAREA uareaobj;
extern BootBlock bootobj;


#endif