# c_coursework
__    .___             
    |__| __| _/____   ____  
    |  |/ __ |/  _ \_/ ___\ 
    |  / /_/ (  <_> )  \___ 

/\_*| \_*\_\_ |\_***/ \_** \> \_*\_\_\_\_| / /

README jdoc is a command line program that analyzes .java files and
prints output to a specified .txt file and to the console.

FILE STRUCTURE jdoc.h: Header file for the main program jdoc.c: Main
source file with main function: Most functions here are with
reading/writing to files

    formatting.h: Header file for formatting.command source file
    formatting.c: Implementation file of prototype functions specified in the formatting header file: Most functions here are connected to file analysis 

BUILDING For Developer Command Prompt for VS (Microsoft Compiler): - In
the command line using the makefile: nmake jdoc - This should create a
jdoc.exe executable!

USAGE Once the program has been built, it is run using the following
command:

        jdoc -i "name_of_file.java" -o "name_of_output.txt"
             
    where,
    - "name_of_file.java": java file to be analyzed
    - "name_of_output.txt": the name of the text output 

CLEANING Files can be deleted after building by:

        nmake clean

    WARNING: This will remove all files in the current directory with the extension: .obj, .asm, .exe

