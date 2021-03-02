/*
 * SET07109 Coursework 1: Creating an application to analyse Javadoc comments in Java source code
 * ----------------------------------------------------------------------------------------------
 * a program that reads .java files and produces two outputs: one to console, one to a .txt file
 * author: Vinh Phat Tu
 */
#include <stdio.h>
#include <string.h>
#include "jdoc.h"
#include "formatting.h"

#define NULL_TERMINATOR '\0'    //The null terminator of a string 

/* 
 * Main function: main
 * -------------------
 * collects command line arguments: 
 *  - input_file = name of .java file
 *  - output_file = name of .txt file
 * 
 * parameters:
 *  - argc: number of command line arguments 
 *  - argv: command line arguments
 * 
 * returns: 0
 *  - 0 = successful execution
 */ 
int main(int argc, char **argv)
{   
    //Collects command line arguments
    char *input_file = argv[2];
    char *output_file = argv[4];

    //Reads file
    struct file_information file_info = read_file(input_file);

    //Writes to file
    write_file(output_file, file_info.raw_methods);

    //Prints the class and author name
    printf("\nClass: %s\n", file_info.class_name);
    printf("Author: %s\n", file_info.author_name);

    printf("\n");

    //Formats and prints all methods
    format_methods(file_info.raw_methods);

    //Print line info
    printf("Total number of lines: %d\n", file_info.total_lines);      
    printf("Number of non-blank lines: %d\n", file_info.non_blank_lines);   
    printf("Number of Javadoc comments: %d\n", file_info.number_of_javadoc); 

    return 0;
} 

/*
 * Function: read_file
 * -------------------
 * reads .java files line by line and sets the details of struct:
 *
 * parameter: input_file - name of the .java file to be scanned
 * 
 * returns: struct file_information 
 *          - number of total lines, non-blank lines and javadoc comments in file
 *          - name of author
 *          - name of java class
 *          - lines of all method prototypes and their javadoc comments
 */
struct file_information read_file(const char *input_file)
{
    struct file_information file_stats;
    
    FILE *file = fopen(input_file, "r");
    
    // Local variables 
    char author_name[50];
    char class_name[50];

    int blank_lines = 0;
    int total_lines = 0;
    int javadoc_comments = 0;

    char raw_methods[10][15][100];     
    int method_count = 0;
    int line_count = 0;

    //Reading file
    char line[100];    
    while(fgets(line, 100, file) != NULL)
    {
        /*
         * Counting blank lines, javadoc comments and total lines
         */
        if (check_blank(line))
        {
            blank_lines++;
        }

        /* 
         * If line contains "/**"
         *  - Increment javadoc counter
         */
        if (strstr(line, "/**"))      
        {
            javadoc_comments++;
        } 

        //For each line read, increment total line counter
        total_lines++;   


        /* 
         * Raw line collection of jdoc comments and method prototypes
         * 
         * If line contains '*' and NOT ';' (since * is also used for multiplication, line 48 in Rectangle.java)
         *  - Copy line to method array
         *  - Increment line counter
         *  - Skip to next iteration
         */
        if (strchr(line, '*') && !strchr(line, ';'))     
        {                                                                               
            strcpy(raw_methods[method_count][line_count], line);
            line_count++;
            continue;
        } 
        
        /* 
         * If line contains '{'
         *  - Copy last line of method to method array
         *  - Increment method counter
         *  - Reset line counter
         */
        if (strchr(line, '{'))
        {
            strcpy(raw_methods[method_count][line_count], line);
            method_count++;
            line_count = 0;
        }

    }
    fclose(file);

    /*
     * Format author & class name 
     */ 
    for (int i = 0; i < 15; i++)
    {
        if (raw_methods[0][i][0] == NULL_TERMINATOR)
        {
            break;
        }

        if (strstr(raw_methods[0][i], "@author"))         
        {
            char temp[100];
            strcpy(temp,raw_methods[0][i]);
            char *formatted_author = format_author_class(temp);
            strcpy(author_name, formatted_author);
            free(formatted_author);

        }

        if (strstr(raw_methods[0][i], "class"))
        {
            char temp[100];
            strcpy(temp,raw_methods[0][i]);
            char *formatted_class = format_author_class(temp);
            strcpy(class_name, formatted_class);
            free(formatted_class);
        }
    }   
    
    /* 
     *Assign all local variables to corresponding variables in struct
     */
    for (int j = 0; j < 10; j++)
    {
        for (int k = 0; k < 15; k++)
        {
            strcpy(file_stats.raw_methods[j][k], raw_methods[j][k]);
        }
    }

    strcpy(file_stats.author_name, author_name);
    strcpy(file_stats.class_name, class_name);
    
    file_stats.total_lines = total_lines;
    file_stats.non_blank_lines = total_lines - blank_lines; 
    file_stats.number_of_javadoc = javadoc_comments;


    return file_stats; 
}


/*
 * Function: write_file
 * --------------------
 * writes to a file:
 *  - all javadoc comments (including class name)
 *  - method prototypes
 * 
 * parameters: output_name, methods
 *         - output_name: name of output file
 *         - methods: 2D array containing all methods, javadoc and class strings
 * 
 * returns: void
 *          - if file is not found, creates a new file
 *          - writes to file
 */
void write_file(const char *output_name, const char methods[10][15][100])        
{
    FILE *output_file = fopen(output_name, "w");

    for (int i = 0; i < 10; i++)
    {
        //If method array is empty -> break loop and end writing to file
        if (methods[i][0][0] == NULL_TERMINATOR)
        {
            break;
        } 

        /*
         * Writing methods and jdoc comments:
         * 
         * Keep writing line to file until '{' is found:
         *  - Write last line with the '{'
         *  - Break loop and increase method index
         */
        for (int j = 0; j < 15; j++)
        {
            if (strchr(methods[i][j], '{'))
            {
                fprintf(output_file, "%s", methods[i][j]);       
                break;
            }
            fprintf(output_file, "%s", methods[i][j]);
        }
        fprintf(output_file, "%s", "\n");
    }

    fclose(output_file);

}

