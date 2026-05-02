# Custom Virtual File System (CVFS)

## Description

This project is a C++ implementation of a Custom Virtual File System (CVFS). It simulates the core functionalities of a file system entirely in memory, providing a hands-on understanding of essential operating system concepts such as Inodes, Superblocks, File Descriptor Tables, and hierarchical directory structures. The program features a custom command-line shell that allows users to perform standard file and directory operations, including creating, reading, writing, and deleting files, as well as navigating and managing nested directories within this virtual environment

## Features

*   **Custom Shell:** An interactive shell to accept and process file system commands.
*   **In-Memory Simulation:** All file system components (Inodes, data blocks, etc.) are managed in memory using C++ data structures.
*   **File Management:** Supports creation, deletion, and statistical display of files.
*   **I/O Operations:** Implements `write` and `read` functionalities for files using file descriptors.
*   **Permission Control:** Basic read/write permissions are associated with each file upon creation.
*   **Built-in Help System:** Includes `help` and `man` commands to provide command information and usage details.
*   **Structured Data Management:** Utilizes key file system data structures like `Inode`, `SuperBlock`, `FileTable`, and `UAREA` to mimic a real file system architecture.

## Core Data Structures

*   **`BootBlock`**: Contains information to boot the virtual operating system.
*   **`SuperBlock`**: Holds metadata about the file system, such as the total number of inodes and the number of free inodes.
*   **`Inode`**: Represents a file and stores its metadata, including file name, size, type, permissions, and a pointer to its data buffer. All inodes are managed in a singly linked list (DILB - Disk Inode List Block).
*   **`FileTable`**: An entry in the User File Descriptor Table that stores runtime information about an opened file, such as read/write offsets and a pointer to its inode.
*   **`UAREA`**: The User Area structure, which contains the User File Descriptor Table (`UFDT`), an array of pointers to `FileTable` entries for all opened files.

## Available Commands

The following table lists the commands available in the CVFS shell.

| Command | Syntax | Description |
| :--- | :--- | :--- |
| `creat` | `creat <file_name> <permission>` | Creates a new regular file. Permissions: 1 (Read), 2 (Write), 3 (Read+Write). |
| `unlink` | `unlink <file_name>` | Deletes an existing file from the file system. |
| `write` | `write <fd>` | Writes data to a file specified by its file descriptor (fd). |
| `read` | `read <fd> <size>` | Reads a specified number of bytes from a file. |
| `mkdir` | `mkdir <directory_name>` | Create a new directory.|
| `rmdir` | `rmdir <directory_name>` | Remove a directory.|
| `pwd` | `pwd ` | Print current working directory.|
| `cd` | `cd ` | Change current directory.|
| `ls` | `ls` | Lists all files currently existing in the file system. |
| `stat` | `stat <file_name>` | Displays statistical information about a specific file. |
| `man` | `man <command_name>` | Shows the manual page with usage details for a specific command. |
| `help` | `help` | Displays a list of all available commands. |
| `clear` | `clear` | Clears the terminal screen. |
| `exit` | `exit` | Terminates the CVFS shell and deallocates resources. |

## How to Compile and Run

1.  Save the code as a `.cpp` file (e.g., `cvfs.cpp`).
2.  Open a terminal and compile the file using a C++ compiler like g++.
    ```
    g++ cvfs.cpp -o cvfs
    ```
3.  Run the resulting executable.
    ```
    ./cvfs
    ```
4.  The "Mangesh/CVFS > " shell will start, ready to accept commands.

## Example Usage

Here is a sample session demonstrating how to use the CVFS shell:<br>
<br>
The shell prompt appears<br>
Boot Process of Operating System Done<br>
CVFS : super block initialised sucessfully<br>
CVFS : DILB created sucessfully<br>
CVFS : UREA initialised sucessfully<br>
CVFS : Created root directory successfully<br>
CVFS : Auxillary data initialised sucessfully<br>
-----------------------------------------------------------------------------------<br>
------------------------- CVFS started Succesfully---------------------------------<br>
-----------------------------------------------------------------------------------<br>
<br>
Mangesh\CVFS > help<br>
-----------------------------------------------------------------------------------<br>
-------------------------Command manual of CVFS------------------------------------<br>
-----------------------------------------------------------------------------------<br>
man : It is used to display the specific manual page of command<br>
write : It is used to write the data into file<br>
ls : It is used to list out all files from directory<br>
read : It is used to read the data from the file<br>
stat : It is used to display statical information about file<br>
creat : It is used to create new regular file<br>
open : It is used to open regular file<br>
close : It is used to close regular file<br>
mkdir : It is used to create new directory<br>
rmdir : It is used to delete  directory<br>
cd : It is used to change directory from one directory to another<br>
pwd : It is used to display current working directory<br>
unlink : It is used to unlink the file<br>
cls : It is used to clear the console of marvellous CVFS<br>
exit : It is used to terminate the shell of marvellous  CVFS<br>
<br>
Mangesh\CVFS > pwd<br>
Current Dir Name : root<br>
Current Dir inode : 1<br>
<br>
Mangesh\CVFS > man creat <br>
Description : This command is used to create regular file on our system<br>
Usage : create <file_name> <Permission><br>
file_name : The name file that you want to create <br>
Permission : <br>
1 : read<br>
2 : write<br>
3 : readwite<br>
<br>
Mangesh\CVFS > creat myfile.txt 3<br>
File is successfully created with fd : 0<br>
<br>
Mangesh\CVFS > man open	<br>
Description : This command is used to open the file<br>
Usage : open <file_name><br>
file_name : The name of file that you want to open<br>
<br>
Mangesh\CVFS > open myFile.txt<br>
Error : Unble to open file as file not exist<br>

Mangesh\CVFS > ls<br>
-------------------------------------------------------------------<br>
Marvellous CVFS Files Information------------------<br>
-------------------------------------------------------------------<br>
<br>
Sr.no              File/Directory<br>
-------------------------------------------------------------------<br>
1			myfile.txt<br>
<br>
-------------------------------------------------------------------<br>
<br>
Mangesh\CVFS > open myfile.txt<br>
File open with fd : 1<br>
<br>
Mangesh\CVFS > man write <br>
Description : This command is used to write the data into file<br>
Usage : write <file_descriptor><br>
<br>
Mangesh\CVFS > write 1<br>
Please enter the data you want to write into file : <br>
Jay Ganesh...<br>
13 bytes gets successfully written<br>
<br>
Mangesh\CVFS > man read<br>
Description : This command is used to read the data from file<br>
Usage : read <file_descriptor> <size><br>
file_decriptor : Its a value returned by create system call<br>
size : Number of byte that you want to read<br>
<br>
Mangesh\CVFS > read 1 13<br>
Read operation is Successful <br>
Data from file : Jay Ganesh...<br>
<br>
Mangesh\CVFS > pwd <br>
Current Dir Name : root<br>
Current Dir inode : 1<br>
<br>
Mangesh\CVFS > mkdir Desktop<br>
Directory file created successfully<br>
<br>
Mangesh\CVFS > ls <br>
-------------------------------------------------------------------<br>
Marvellous CVFS Files Information------------------<br>
-------------------------------------------------------------------<br>
<br>
Sr.no              File/Directory<br>
-------------------------------------------------------------------<br>
1			myfile.txt<br>
2			Desktop<br>
<br>
-------------------------------------------------------------------<br>
<br>
Mangesh\CVFS > cd Desktop<br>
Change current dir successfully<br>
<br>
Mangesh\CVFS > ls<br>
-------------------------------------------------------------------<br>
Marvellous CVFS Files Information------------------<br>
-------------------------------------------------------------------<br>
<br>
Sr.no              File/Directory<br>
-------------------------------------------------------------------<br>
<br>
-------------------------------------------------------------------<br>
<br>
Mangesh\CVFS > creat newfile.txt 3<br>
File is successfully created with fd : 2<br>
<br>
Mangesh\CVFS > ls<br>
-------------------------------------------------------------------<br>
Marvellous CVFS Files Information------------------<br>
-------------------------------------------------------------------<br>
<br>
Sr.no              File/Directory<br>
-------------------------------------------------------------------<br>
1			newfile.txt<br>
<br>
-------------------------------------------------------------------<br>
<br>
Mangesh\CVFS > pwd<br>
Current Dir Name : Desktop<br>
Current Dir inode : 3<br>
<br>
Mangesh\CVFS > open newfile.txt<br>
File open with fd : 3<br>
<br>
Mangesh\CVFS > write 3<br>
Please enter the data you want to write into file : <br>
I am Student<br>
12 bytes gets successfully written<br>
<br>
Mangesh\CVFS > man read<br>
Description : This command is used to read the data from file<br>
Usage : read <file_descriptor> <size><br>
file_decriptor : Its a value returned by create system call<br>
size : Number of byte that you want to read<br>
<br>
Mangesh\CVFS > read 3 12<br>
Read operation is Successful <br>
Data from file : I am Student<br>

<br>
CVFS > exit<br>
Thank you for using CVFS<br>
Deallocating all resources...<br>
<br>
## Core Functions

This table provides an overview of the key C++ functions that implement the logic for the Custom Virtual File System.

| Function Signature | Description |
| :--- | :--- |
| `int main()` | The main entry point and command-line shell loop. It reads user input, parses commands, and calls the appropriate handler functions. |
| `void StartAuxilaryDataInitialisation()` | A high-level initialization function that orchestrates the setup of the entire file system by calling the `InitialiseSuperblock`, `CreateDILB`, and `InitialiseUAREA` functions. |
| `void InitialiseSuperblock()` | Initializes the `superobj` global variable, setting the total and free inode counts based on the `MAXINODE` macro. |
| `void CreateDILB()` | "Creates the Disk Inode List Block" by allocating a singly linked list of `INODE` structures, which serves as the Inode Table. |
| `void InitialiseUAREA()` | Initializes the User Area (`uareaobj`) by setting the process name and preparing the User File Descriptor Table (UFDT) with NULL entries. |
| `void DisplayHelp()` | Prints a formatted list of all available commands and their brief descriptions to the console. |
| `void ManPage(char *name)` | Displays detailed usage information for a specific command, including its purpose, syntax, and arguments. |
| `bool IsFileExists(char *name)` | Traverses the inode linked list to check if a file with the given name already exists. |
| `int CreateFile(char *name, int permission)` | Handles the logic for creating a new file. It finds a free inode, allocates a file table entry in the UFDT, initializes file metadata, and returns a file descriptor. |
| `int UnlinkFile(char *name)` | Deletes a file by deallocating its data buffer and resetting its inode, making it available for reuse. |
| `void ls_file()` | Lists all existing files by traversing the inode linked list and printing the `FileName` of each active inode. |
| `int stat_file(char *name)` | Displays detailed metadata for a given file, including its inode number, file size, link count, and permissions. |
| `int write_file(int fd, char *data, int size)` | Writes data from a character buffer into the file's in-memory data block, updating the write offset and actual file size. |
| `int read_file(int fd, char *data, int size)` | Reads data from a file's in-memory data block into a specified buffer, advancing the read offset. |


## Author
- Mangesh Ashok Bedre