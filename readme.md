# Custom Virtual File System (CVFS)

## Description

This project is a C++ implementation of a Custom Virtual File System (CVFS). It simulates the core functionalities of a file system entirely in memory, providing a hands-on understanding of concepts like Inodes, Superblocks, File Descriptor Tables, and system calls for file manipulation. The program features its own custom command-line shell that allows users to create, read, write, and delete files within this virtual environment.

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
Mangesh/CVFS > creat myFile.txt 3<br>
File is succesfully created with FD : 0<br>
<br>
Mangesh/CVFS > write 0<br>
Please enter the data that you want to write into the file :<br>
Hello World<br>
11 bytes gets succesfully written into the file<br>
Data from file is : Hello World<br>
<br>
Mangesh/CVFS > ls<br>
myFile.txt<br>
<br>
Mangesh/CVFS > stat myFile.txt<br>
------------ Statistical Information of file -----------<br>
File name : myFile.txt<br>
File size on Disk : 100<br>
Actual File size : 11<br>
Link count : 1<br>
File permission : Read + Write<br>
File type : Regular file<br>
Mangesh/CVFS > read 0 5<br>
Read operation is successfull<br>
Data from file is : Hello<br>
<br>
Mangesh/CVFS > unlink myFile.txt<br>
Unlink Opertaion is succesfully performed<br>
<br>
Mangesh/CVFS > ls<br>
<br>
(no output, as the file has been deleted)<br>
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