Homework 3
- Madison Byrd
-BlazerID: mjbyrd 

To Compile:
    make

To run: 
    ./hw3 <directory_name>
    ./hw3 . 

Description:
This program opens a directory and creates a child process for each regular file.
Then it prints the file name and size and counts words for .txt files only.

Cases it handled:
- Missing command-line argument
- Invalid or inaccessible directory
- Empty directory
- Empty .txt files
- Files that can't be opened
- Ignores subdirectories

