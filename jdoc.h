/*
 * SET07109 Coursework 1: Creating an application to analyse Javadoc comments in Java source code
 * ----------------------------------------------------------------------------------------------
 * header file for main jdoc.c file
 * author: Vinh Phat Tu
 */

#pragma once

/*
 * Struct: file_information
 * ------------------------
 * struct which holds information about the file read:
 *  - number of total lines, non_blank_lines, javadoc comments
 *  - name of author and class
 *  - complete javadoc comments and method prototypes
 */
struct file_information
{
    int total_lines;
    int non_blank_lines;
    int number_of_javadoc;
    
    char author_name[50];
    char class_name[50];

    char raw_methods[10][15][100];
};

//Implementation found in: jdoc.c
struct file_information read_file(const char *);

void write_file(const char *, const char[10][15][100]);
