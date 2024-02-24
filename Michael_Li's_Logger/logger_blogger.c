#include "logger_blogger.h"

void Info(char* msg){
    printf("Log Info:\t%s", &msg);
}

void Warning(char* msg){
    printf("Log Warning:\t%s", &msg);
}

void Error(char* msg){
    printf("Log Error:\t%s", &msg);
}