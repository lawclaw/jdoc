/*
 * SET07109 Coursework 1: Creating an application to analyse Javadoc comments in Java source code
 * ----------------------------------------------------------------------------------------------
 * header file for formatting.c file
 * author: Vinh Phat Tu
 */

#pragma once

//Implementation found in: formatting.c
int check_blank(const char *);

char * remove_newline(char *);

char * remove_space(char *);

char * format_author_class(char *);

void format_methods(char[10][15][100]);

void print_methods (const char*, const char *, const char[15][100]);
