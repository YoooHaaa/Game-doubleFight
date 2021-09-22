////////////下次再写俄罗斯方块，就把6种类型，以及所有的状态写进一个大结构体，其中有6个子结构体，每个子结构体中是他所属类型所有的状态
#include <stdio.h>
#include <stdlib.h>
#include "head.h"

int main(int argc, char *argv[])
{
    char cGet;
    
    game_begin();

    printf("\r\n");
    printf("                   >>按回车退出！<<\r\n");
    while ((cGet = getchar()) != '\n')
    {
        ;
    }
    system("pause");
    return 0;
}