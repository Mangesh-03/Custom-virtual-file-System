////////////////////////////////////////////////////////////////////////////
//
//  Header file inclusion
//
///////////////////////////////////////////////////////////////////////////

#include"CVFS.h";

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
            
            if(strcmp(Command[0],"exit") == 0)
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

            else if(strcmp(Command[0],"clear") == 0)
            {
                // Conditional pre-processing
                #ifdef _WIN32   
                    system("cls");
                #else
                    system("clear");
                #endif
            }

            // Mangesh/CVFS > ls
            else if(strcmp(Command[0],"ls") == 0)
            {
                ls_File();
            }
            else if(strcmp(Command[0],"pwd") == 0)
            {
                getCurrentDir();
            }
            else
            {   
                printf("zsh : Command not found");
                printf("Please refer Help option or use man command");
            }   // end of invalid command part


        }   // end of if (icount == 1)

        else if(iCount == 2)
        {

            // Mangesh/CVFS > man ls
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
                    printf("Error : Unable to do delete activity as file not present\n");
                }
                else if(iRet == ERR_INVALID_PARAMETER)
                {
                    printf("Error : Invalid parameter for the function\n");
                    printf("Please check man page for more details\n");

                }
            }

            // Mangesh/CVFS > rmdir Desktop
            else if(strcmp(Command[0],"rmdir")==0)
            {
                iRet = UnlinkFile(Command[1]);

                if(iRet == EXECUTE_SUCCESS)
                {
                    printf(" Unlink Operation successfully performed\n");
                }
                else if( iRet == ERR_FILE_NOT_EXIST)
                {
                    printf("Error : Unable to do delete activity as file not present\n");
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

            // Mangesh/CVFS >  write  3            here 3 is fd
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
                    printf("%d bytes gets successfully written\n",iRet);
                }
            }
             // Mangesh/CVFS >  open <file_name>            ex. open Demo.txt    
            else if(strcmp(Command[0],"open") == 0)
            {
                iRet = OpenFile(Command[1]);

                if(iRet == ERR_FILE_NOT_EXIST)
                {
                    printf("Error : Unble to open file as file not exist\n");
                }
                else if(iRet == ERR_MAX_FILE_OPEN)
                {
                    printf("Error : Unble to open file as max file opened\n");
                }
                else
                {
                    printf("File open with fd : %d\n",iRet);
                }
            }
            // Mangesh/CVFS >  close <file_name>            ex. close Demo.txt 
            else if(strcmp(Command[0],"close") == 0)
            {
                iRet = closeFile(Command[1]);

                if(iRet == ERR_INVALID_PARAMETER)
                {
                    printf("Unble to close file as wrong file name\n");
                }
                else if(iRet == ERR_FILE_NOT_OPEN)
                {
                    printf("Unble to closed file bcz file is not open\n");
                }
                else if(iRet == EXECUTE_SUCCESS)
                {
                    printf("File closed successfully\n");
                }
            }

            // Mangesh/CVFS >  mkdir <dir_name>            ex. mkdir Desktop 
            else if(strcmp(Command[0],"mkdir") == 0)
            {
                iRet = MakeDir(Command[1]);

                if(iRet == ERR_INVALID_PARAMETER)
                {
                    printf("Error : Unble to create dir as invalid parameter\n");
                }
                else if(iRet == ERR_FILE_ALREADY_EXIST)
                {
                    printf("Error : Unble to creat dir as file already exist\n");
                }
                else if(iRet == ERR_NO_INODE)
                {
                    printf("Error : Unble to creat dir as No inode \n");
                }
                else if(iRet == ERR_MAX_FILE_OPEN)
                {
                    printf("Error : Unble to creat dir as Max file opend limit reached\n");
                }
                else if(iRet == EXECUTE_SUCCESS)
                {
                    printf("Directory file created successfully\n");
                }
            }

            // Mangesh/CVFS >  cd <dir_name>            ex. cd Desktop 
            else if(strcmp(Command[0],"cd") == 0)
            {
                iRet = ChangeDir(Command[1]);

                if(iRet == ERR_INVALID_PARAMETER)
                {
                    printf("Error : Unble to change dir as invalid parameter\n");
                }
                else if(iRet == ERR_FILE_NOT_EXIST)
                {
                    printf("Error : Unble to change dir as file not exist\n");
                }
                else if(iRet == EXECUTE_SUCCESS)
                {
                    printf("Change current dir successfully\n");
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
                else if(iRet == ERR_MAX_FILE_OPEN)
                {
                    printf("Error : Unable to opened file as max opened  limit  reached\n");
                }
                else if(iRet == ERR_NO_ENTRY_DIR)
                {
                    printf("Error : Directory file is Full no new entry\n");
                }
                else 
                {
                    printf("File is successfully created with fd : %d\n",iRet);
                }

            }
            // Mangesh/CVFS > read 3 10       3-> fd  10->size
            else if(strcmp(Command[0],"read") == 0)
            {
                EmptyBuffer = (char *)malloc(atoi(Command[2]));
                iRet = read_file(atoi(Command[1]),EmptyBuffer,atoi(Command[2]));

                if(iRet == ERR_INSUFFICIENT_DATA)
                {
                    printf("Error : Insufficient data inside file\n");
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