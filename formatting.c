/*
 * SET07109 Coursework 1: Creating an application to analyse Javadoc comments in Java source code
 * ----------------------------------------------------------------------------------------------
 * 'formatting'/processing functions for main jdoc.c file
 * author: Vinh Phat Tu
 */

/* 
 * References:
 * -----------
 * 1: https://stackoverflow.com/a/14416798 - "Return char[]/string from a function [duplicate]
 * 
 * After trying to return a local char* from a function, I stumbled upon the solution:
 * Once the function ends, the pointer will be overridden in memory (due to popping off stack) and thus I need to allocate memory using malloc();
 * 
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "jdoc.h"
#include "formatting.h"


/*
 * Constants
 * ---------
 * DELIM: Delimiter when splitting strings in strtok()
 * NULL_TERMINATOR: Null terminator character of string
 * 
 * JAVA_DOC_PARAM: Javadoc keyword for parameter
 * JAVA_DOC_RETURN: Javadoc keyword for return
 * 
 * PRINT_PARAMETERS: Flag value for printing parameters
 * PRINT_RETURNS: Flag value for printing returns
 */
#define DELIM " "    
#define NULL_TERMINATOR '\0'

#define JAVA_DOC_PARAM "@param"
#define JAVA_DOC_RETURN "@return"

#define PRINT_PARAMETERS 1
#define PRINT_RETURNS 2

/*
 * Function: check_blank
 * ---------------------
 * checks if string doesn't only contain using isspace():
 *  - '\n': newline character
 *  - ' ': space character
 *  - '\t': tab character
 *  etc.
 * 
 * parameter: input_string - string to be checked 
 * 
 * returns: is_blank - boolean
 *  - 1 if string is blank
 *  - 0 if string is not blank
 */
int check_blank(const char *input_string)
{
    int len = strlen(input_string);
    int is_blank = 1;
    /*
     * Iterate over each character in the string
     */
    for (int i = 0; i < len; i++)
    {
        if (isspace(input_string[i]) == 0)      //If char is not blank, set boolean to false and break loop
        {
            is_blank = 0;
            break;
        }
    }
    return is_blank;
}

/*
 * Function: remove_newline
 * ------------------------
 * removes '\n' at the end of a string
 * 
 * parameter: input_string - string to remove newline character from
 * 
 * return: string without newline character 
 */
char* remove_newline(char *input_string)
{
    int len = strlen(input_string);
    if (len > 0 && input_string[len - 1] == '\n')
    {
        input_string[len - 1] = '\0';
    }
    return input_string;
}


/*
 * Function: remove_space
 * ----------------------
 * removes " " at the end of a string
 * 
 * parameter: input_string - string to remove newline character from
 * 
 * return: string without space character
 */
char* remove_space(char *input_string)
{
    int len = strlen(input_string);
    if (len > 0 && input_string[len - 1] == ' ')
    {
        input_string[len - 1] = '\0';
    }
    return input_string;
}


/*
 * Function: format_author_class
 * -----------------------------
 * splits and formats:
 *  - author name string
 *  - class name string
 * 
 * parameter: line - string with author name or class name
 * 
 * return: formatted author/class string
 */
char *format_author_class(char *line)          
{
    char temp_string[100] = "";    //Local variable used for string manipulation        
    char *split = strtok(line, DELIM); 
    split = strtok(NULL, DELIM);    //Skips '*' or "public"
    split = strtok(NULL, DELIM);    //Skips "@author" or type (void,double, etc.)

    //Collect author/class name
    while (split != NULL)
    {
        strcat(temp_string, split);
        strcat(temp_string, " ");
        split = strtok(NULL, DELIM);
    }
    
    //Remove space and newline from name
    strcpy(temp_string, remove_space(temp_string));
    strcpy(temp_string, remove_newline(temp_string));

    //Removes '{' at the end of the class name
    if (temp_string[strlen(temp_string) - 1] == '{')
    {  
        temp_string[strlen(temp_string) - 1] = NULL_TERMINATOR;
    }

    char *formatted_string = malloc(100);  //Citation: StackOverFlow - Refer to top comment 
    strcpy(formatted_string,temp_string); 
    return formatted_string; 

}


/*
 * Function: format_methods
 * ------------------------
 * formats strings, by splitting using strtok(), for: 
 *  - method strings
 *  - parameters/return strings
 * 
 * then calls print_methods for printing
 * 
 * parameter: methods - 2D array containing all methods, javadoc and class strings 
 * 
 * returns: void 
 *          - no printing -> refer to print_methods()
 */
void format_methods(char methods[10][15][100])
{
    char *class_character = "class";

    char *split;

    char *parameter_string = "Parameter: ";
    char *return_string = "Returns: ";


    for (int i = 1; i < 10; i++) 
    {   
        char params_returns[15][100]; //Local array to hold all parameters/returns
        for (int k = 0; k < 15; k++)
        {
            params_returns[k][0] = NULL_TERMINATOR;
        }
        char param_returns_index = 0;  


        int printing_mode;          //Flag to distinguish from parameter or return  


        for (int j = 0; j < 15; j++)
        {
            //If line is empty, break loop
            if (methods[i][j][0] == NULL_TERMINATOR)
            {
                break;
            }

            /* If line contains "@return" or "@param":
                - Split line
                - Set flag for printing
                - Collect all parameters/returns
            */
            if (strstr(methods[i][j], JAVA_DOC_RETURN) || strstr(methods[i][j], JAVA_DOC_PARAM)) 
            {
                split = strtok(methods[i][j], DELIM);
                split = strtok(NULL, DELIM);  //Skips '*'

                if (strcmp(split, JAVA_DOC_RETURN) == 0) 
                {
                    printing_mode = PRINT_RETURNS;
                } else if (strcmp(split, JAVA_DOC_PARAM) == 0)
                {
                    printing_mode = PRINT_PARAMETERS;
                }

                split = strtok(NULL, DELIM);        //Skips the @return/@param tag


                char temp_line[100] = "";   //Local variable for string concatonation

                while(split != NULL)
                {
                    strcat(temp_line, split);
                    strcat(temp_line, " ");
                    split = strtok(NULL,DELIM);
                }
                strcpy(temp_line, remove_space(temp_line));
                strcpy(temp_line, remove_newline(temp_line));
                strcpy(params_returns[param_returns_index], temp_line);
                param_returns_index++;
            }            


            /* If line contains "{" (end of method prototype):
                - Split line 
                - Concatonate method name to printing string
                - Check print mode
                - Call print_methods()
            */
            if (strchr(methods[i][j], '{'))
            {
                split = strtok(methods[i][j], DELIM);
                split = strtok(NULL, DELIM);
                split = strtok(NULL, DELIM);
                char method_string[100] = "Method: ";
                strcat(method_string, split);

                switch (printing_mode)
                {
                    case PRINT_PARAMETERS:
                        print_methods(method_string, parameter_string, params_returns);
                        break;
                    case PRINT_RETURNS:
                        print_methods(method_string, return_string, params_returns);
                        break;
                    default:
                        break;
                }
            }

        }
    }
}


/*
 * Function: print_methods
 * -----------------------
 * prints out formatted methods from format_methods():
 * 
 * Format: 
 *  - "Method: method_name_string"
 *  - "Parameter: parameter_string" or "Returns: return_string"
 * 
 * parameters: method_string, phrase, parameters_returns
 *  - method_string: complete method string to be printed
 *  - phrase: depending on method, "Parameter: " or "Method"
 *  - parameters_returns: array of all parameters/returns 
 * 
 * returns: void
 *         - only printing
 */
void print_methods (const char* method_string, const char *phrase, const char parameters_returns[15][100])
{
    printf("%s\n", method_string);
    for (int i = 0; i < 15; i++)
    {
        //If current line doesn't contain NULL_TERMINATOR, print
        if (parameters_returns[i][0] != NULL_TERMINATOR)
        {
            printf("%s%s\n", phrase, parameters_returns[i]);
        }
    } 
    printf("\n");

}
