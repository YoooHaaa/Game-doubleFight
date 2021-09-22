#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>
//#include <windows.h>
#include "head.h"

#define WIDTH 21
#define HIGH  22

void _init_box(char(*szMap)[WIDTH])
{
    int i = 0;
    char szMod[HIGH][WIDTH] = {
        "10000000000000000001",
        "10000000000000000001",
        "10000000000000000001",
        "10000000000000000001",
        "11111111111111111111",
        "10000000000000000001",
        "10000000000000000001",
        "10000000000000000001",
        "10000000000000000001",
        "10000000000000000001",
        "10000000000000000001",
        "10000000000000000001",
        "10000000000000000001",
        "10000000000000000001",
        "10000000000000000001",
        "10000000000000000001",
        "10000000000000000001",
        "10000000000000000001",
        "10000000000000000001",
        "10000000000000000001",
        "10000000000000000001",
        "11111111111111111111" };

    for (i = 0; i < HIGH; i++)
    {
        if (strcpy_s(szMap[i], WIDTH, szMod[i]) != 0)
        {
            printf("地图初始化失败！\r\n");
        }
    }
}
void _strcpy_square_state(char(*szSquareState)[5], char(*szSquare)[5])//将预存的方块状态画进方块状态图
{
    int i = 0;
    int j = 0;

    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 5; j++)
        {
            szSquareState[i][j] = szSquare[i][j];
        }
    }
}
void __hold_square(PLAYER *tagPlayer)//将方块固定在当前位置，并写进大地图，然后删除该方块
{
    int i = 0;
    int j = 0;

    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            if (tagPlayer->szSquareState[i][j] == '1')
            {
                tagPlayer->szBox[i + tagPlayer->x][j + tagPlayer->y] = '1';
            }
        }
    }
    memset(tagPlayer->szSquareState, 0, 20 * sizeof(char));//方块被固定，将状态清零
    tagPlayer->x = 5;//坐标变更视为方块删除
    tagPlayer->y = 9;
}
void __add_grid(PLAYER *tagPlayer, int nUpNum)
{
    int i = 0;
    int j = 0;

    for (i = 5; i < HIGH - nUpNum - 1; i++)
    {
        for (j = 1; j < WIDTH - 2; j++)
        {
            tagPlayer->szBox[i][j] = tagPlayer->szBox[i + nUpNum][j];
        }
    }
}
void init_player_info(PLAYER *player)
{
    _init_box(player->szBox);
    _init_box(player->szSquare);
    memset(player->szSquareState, 0, 20);
    memset(player->szSquareStateNext, 0, 20);
    player->x = 0;
    player->y = 0;
    player->nFlag = 0;
    player->xNext = 0;
    player->yNext = 9;
    player->nSquType = 0;
    player->nSquState = 0;
    player->nSquTypeNext = 0;
    player->nSquStateNext = 0;
    player->nScore = 0;
    player->nDownNum = 0;
    player->tStart = 0;
}
void __print_square(PLAYER *tagPlayerA, PLAYER *tagPlayerB)
{
    int i = 0;
    int j = 0;
    char cMark = '@';

    system("cls");
    memset(tagPlayerA->szSquare, 0, HIGH * WIDTH * sizeof(char));
    memset(tagPlayerB->szSquare, 0, HIGH * WIDTH * sizeof(char));

    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 5; j++)
        {
            if (tagPlayerA->szSquareState[i][j] == '1')//这个Bug调了3个小时，要谨记，必须判断了再复制，不然当方块降落到底部时，直接复制会覆盖边框以及边框以下的区域
            {
                tagPlayerA->szSquare[i + tagPlayerA->x][j + tagPlayerA->y] = tagPlayerA->szSquareState[i][j];
            }
        }
    }
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 5; j++)
        {
            tagPlayerA->szSquare[i + tagPlayerA->xNext][j + tagPlayerA->yNext] = tagPlayerA->szSquareStateNext[i][j];
        }
    }
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 5; j++)
        {
            if (tagPlayerB->szSquareState[i][j] == '1')
            {
                tagPlayerB->szSquare[i + tagPlayerB->x][j + tagPlayerB->y] = tagPlayerB->szSquareState[i][j];
            }
        }
    }
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 5; j++)
        {
            tagPlayerB->szSquare[i + tagPlayerB->xNext][j + tagPlayerB->yNext] = tagPlayerB->szSquareStateNext[i][j];
        }
    }
    for (i = 0; i < HIGH; i++)
    {
        printf("   ");
        for (j = 0; j < WIDTH; j++)
        {
            if (tagPlayerA->szBox[i][j] == '1' || tagPlayerA->szSquare[i][j] == '1')
            {
                printf("%c", cMark);
            }
            else
            {
                printf(" ");
            }
        }
        printf("  ^   ");
        for (j = 0; j < WIDTH; j++)
        {
            if (tagPlayerB->szBox[i][j] == '1' || tagPlayerB->szSquare[i][j] == '1')
            {
                printf("%c", cMark);
            }
            else
            {
                printf(" ");
            }
        }
        if (i == 8)
        {
            printf("  玩家A积分：%5d", tagPlayerA->nScore);
        }
        if (i == 9)
        {
            printf("  上/w 下/s 左/a 右/d");
        }
        if (i == 12)
        {
            printf("  玩家B积分：%5d", tagPlayerB->nScore);
        }
        if (i == 13)
        {
            printf("  上/i 下/k 左/j 右/l");
        }
        printf("\r\n");
    }
}
int _check_touch(PLAYER *tagPlayer, int x, int y)
{
    int i = 0;
    int j = 0;
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            if (tagPlayer->szSquareState[i][j] == '1' &&  tagPlayer->szBox[i + x][j + y] == '1')
            {
                return 0;//0表示碰到了
            }
        }
    }
    return 1;
}
int __down_square(PLAYER *tagPlayer)//0表示到底了，1表示每碰到，并下落一格
{
    if (_check_touch(tagPlayer, tagPlayer->x + 1, tagPlayer->y) == 1)
    {
        tagPlayer->x = tagPlayer->x + 1;
        return 1;
    }
    else
    {
        return 0;
    }
}
int __up_square(PLAYER *tagPlayer, PLAYER *tagEnemy)//将玩家的格子升高nUpNum，如果升高后碰到了方块，返回0，代表开始产生下一个方块，1不产生
{
    int i = 0;

    if (_check_touch(tagPlayer, tagPlayer->x + tagEnemy->nDownNum, tagPlayer->y) == 0)//判断升高后底部会不会碰到方块 0 表示碰到了
    {
        for (i = 1; i <= tagEnemy->nDownNum; i++)
        {
            if (_check_touch(tagPlayer, tagPlayer->x + i, tagPlayer->y) == 0)//找到在升高第几次的时候碰到
            {
                tagPlayer->x = tagPlayer->x - (tagEnemy->nDownNum - i + 1);//将方块上移相应的层数
            }
        }
        __add_grid(tagPlayer, tagEnemy->nDownNum);
        tagEnemy->nDownNum = 0;
        return 0;
    }
    __add_grid(tagPlayer, tagEnemy->nDownNum);
    tagEnemy->nDownNum = 0;
    return 1;
}
void _get_square_state(PLAYER *tagPlayer)//得到下一个方块的类型，状态
{
    tagPlayer->nSquTypeNext = rand() % 6 + 1;//1.田    2.长条    3.山字形    4,5.Z形2种    6.L形
    tagPlayer->nSquStateNext = rand() % 4 + 1;
}

char _get_operate()
{
    char cOperate = 0;

    if (_kbhit())
    {
        cOperate = _getch();
    }
    return cOperate;
}
void _draw_next_square_One(PLAYER *tagPlayer)
{
    char szSquare[][5] = {
        "1100",
        "1100",
        "0000",  //@@
        "0000" };//@@
    _strcpy_square_state(tagPlayer->szSquareStateNext, szSquare);
}
void _operate_square_One(PLAYER *tagPlayer, char cOperate)
{
    char szSquare[][5] = {
        "1100",
        "1100",
        "0000",  //@@
        "0000" };//@@

    _strcpy_square_state(tagPlayer->szSquareState, szSquare);
    switch (cOperate)
    {
    case 'a':
    case 'j':
        if (_check_touch(tagPlayer, tagPlayer->x, tagPlayer->y - 1))
        {
            tagPlayer->y = tagPlayer->y - 1;
        }
        break;
    case 'd':
    case 'l':
        if (_check_touch(tagPlayer, tagPlayer->x, tagPlayer->y + 1))
        {
            tagPlayer->y = tagPlayer->y + 1;
        }
        break;
    case 'w':
    case 'i':
        break;
    case 's':
    case 'k':
        if (_check_touch(tagPlayer, tagPlayer->x + 1, tagPlayer->y))
        {
            tagPlayer->x = tagPlayer->x + 1;
        }
        break;
    default:break;
    }
}
void _draw_next_square_Two(PLAYER *tagPlayer)
{
    char szSquare_One[][5] = {
        "0100",
        "1110",//      @
        "0000",//     @@@
        "0000" };

    char szSquare_Two[][5] = {
        "0100",//      @
        "0110",//      @@
        "0100",//      @
        "0000" };

    char szSquare_Three[][5] = {
        "0000",
        "1110",//    @@@
        "0100",//     @
        "0000" };

    char szSquare_Four[][5] = {
        "0100",//      @
        "1100",//     @@
        "0100",//      @
        "0000" };
    switch (tagPlayer->nSquStateNext)//根据状态将形状画进4*4数组
    {
    case 1:
        _strcpy_square_state(tagPlayer->szSquareStateNext, szSquare_One);
        break;
    case 2:
        _strcpy_square_state(tagPlayer->szSquareStateNext, szSquare_Two);
        break;
    case 3:
        _strcpy_square_state(tagPlayer->szSquareStateNext, szSquare_Three);
        break;
    case 4:
        _strcpy_square_state(tagPlayer->szSquareStateNext, szSquare_Four);
        break;
    default:break;
    }
}
void _operate_square_Two(PLAYER *tagPlayer, char cOperate)
{
    char szSquare_One[][5] = {
        "0100",
        "1110",//      @
        "0000",//     @@@
        "0000" };

    char szSquare_Two[][5] = {
        "0100",//      @
        "0110",//      @@
        "0100",//      @
        "0000" };

    char szSquare_Three[][5] = {
        "0000",
        "1110",//    @@@
        "0100",//     @
        "0000" };

    char szSquare_Four[][5] = {
        "0100",//      @
        "1100",//     @@
        "0100",//      @
        "0000" };

    switch (tagPlayer->nSquState)//根据状态将形状画进4*4数组
    {
    case 1:
        _strcpy_square_state(tagPlayer->szSquareState, szSquare_One);
        break;
    case 2:
        _strcpy_square_state(tagPlayer->szSquareState, szSquare_Two);
        break;
    case 3:
        _strcpy_square_state(tagPlayer->szSquareState, szSquare_Three);
        break;
    case 4:
        _strcpy_square_state(tagPlayer->szSquareState, szSquare_Four);
        break;
    default:break;
    }

    switch (cOperate)//根据输入进行相应操作
    {
    case 'a':
    case 'j':
        if (_check_touch(tagPlayer, tagPlayer->x, tagPlayer->y - 1))
        {
            tagPlayer->y = tagPlayer->y - 1;
        }
        break;
    case 'd':
    case 'l':
        if (_check_touch(tagPlayer, tagPlayer->x, tagPlayer->y + 1))
        {
            tagPlayer->y = tagPlayer->y + 1;
        }
        break;
    case 'w':
    case 'i':
        if (tagPlayer->szBox[tagPlayer->x + 2][tagPlayer->y] == '0' && tagPlayer->szBox[tagPlayer->x + 2][tagPlayer->y + 1] == '0'
            && tagPlayer->szBox[tagPlayer->x + 2][tagPlayer->y + 2] == '0' && tagPlayer->szBox[tagPlayer->x][tagPlayer->y] == '0'
            && tagPlayer->szBox[tagPlayer->x + 1][tagPlayer->y] == '0' && tagPlayer->szBox[tagPlayer->x][tagPlayer->y + 2] == '0'
            && tagPlayer->szBox[tagPlayer->x + 1][tagPlayer->y + 2] == '0')
        {
            switch (tagPlayer->nSquState)
            {
            case 1:
                _strcpy_square_state(tagPlayer->szSquareState, szSquare_Two);
                break;
            case 2:
                _strcpy_square_state(tagPlayer->szSquareState, szSquare_Three);
                break;
            case 3:
                _strcpy_square_state(tagPlayer->szSquareState, szSquare_Four);
                break;
            case 4:
                _strcpy_square_state(tagPlayer->szSquareState, szSquare_One);
                break;
            default:break;
            }
            tagPlayer->nSquState = tagPlayer->nSquState % 4 + 1;
        }
        break;
    case 's':
    case 'k':
        if (_check_touch(tagPlayer, tagPlayer->x + 1, tagPlayer->y))
        {
            tagPlayer->x = tagPlayer->x + 1;
        }
        break;
    default:break;
    }
}
void _draw_next_square_Three(PLAYER *tagPlayer)
{
    char szSquare_One[][5] = {
        "1000",
        "1100",//      @
        "0100",//      @@
        "0000" };//     @

    char szSquare_Two[][5] = {
        "0110",//       @@
        "1100",//      @@
        "0000" ,
        "0000" };
    switch (tagPlayer->nSquStateNext)//根据状态将形状画进4*4数组
    {
    case 1:
        _strcpy_square_state(tagPlayer->szSquareStateNext, szSquare_One);
        break;
    case 3:
        _strcpy_square_state(tagPlayer->szSquareStateNext, szSquare_One);
        break;
    case 2:
        _strcpy_square_state(tagPlayer->szSquareStateNext, szSquare_Two);
        break;
    case 4:
        _strcpy_square_state(tagPlayer->szSquareStateNext, szSquare_Two);
        break;
    default:break;
    }
}
void _operate_square_Three(PLAYER *tagPlayer, char cOperate)
{
    char szSquare_One[][5] = {
        "1000",
        "1100",//      @
        "0100",//      @@
        "0000" };//     @

    char szSquare_Two[][5] = {
        "0110",//       @@
        "1100",//      @@
        "0000" ,
        "0000" };

    switch (tagPlayer->nSquState)//根据状态将形状画进4*4数组
    {
    case 1:
        _strcpy_square_state(tagPlayer->szSquareState, szSquare_One);
        break;
    case 3:
        _strcpy_square_state(tagPlayer->szSquareState, szSquare_One);
        break;
    case 2:
        _strcpy_square_state(tagPlayer->szSquareState, szSquare_Two);
        break;
    case 4:
        _strcpy_square_state(tagPlayer->szSquareState, szSquare_Two);
        break;
    default:break;
    }

    switch (cOperate)//根据输入进行相应操作
    {
    case 'a':
    case 'j':
        if (_check_touch(tagPlayer, tagPlayer->x, tagPlayer->y - 1))
        {
            tagPlayer->y = tagPlayer->y - 1;
        }
        break;
    case 'd':
    case 'l':
        if (_check_touch(tagPlayer, tagPlayer->x, tagPlayer->y + 1))
        {
            tagPlayer->y = tagPlayer->y + 1;
        }
        break;
    case 'w':
    case 'i':
        if (tagPlayer->szBox[tagPlayer->x + 2][tagPlayer->y] == '0' && tagPlayer->szBox[tagPlayer->x + 2][tagPlayer->y + 1] == '0'
            && tagPlayer->szBox[tagPlayer->x + 2][tagPlayer->y + 2] == '0' && tagPlayer->szBox[tagPlayer->x][tagPlayer->y] == '0'
            && tagPlayer->szBox[tagPlayer->x + 1][tagPlayer->y] == '0' && tagPlayer->szBox[tagPlayer->x][tagPlayer->y + 2] == '0'
            && tagPlayer->szBox[tagPlayer->x + 1][tagPlayer->y + 2] == '0')
        {
            switch (tagPlayer->nSquState)
            {
            case 1:
                _strcpy_square_state(tagPlayer->szSquareState, szSquare_Two);
                break;
            case 3:
                _strcpy_square_state(tagPlayer->szSquareState, szSquare_Two);
                break;
            case 2:
                _strcpy_square_state(tagPlayer->szSquareState, szSquare_One);
                break;
            case 4:
                _strcpy_square_state(tagPlayer->szSquareState, szSquare_One);
                break;
            default:break;
            }
            tagPlayer->nSquState = tagPlayer->nSquState % 4 + 1;
        }
        break;
    case 's':
    case 'k':
        if (_check_touch(tagPlayer, tagPlayer->x + 1, tagPlayer->y))
        {
            tagPlayer->x = tagPlayer->x + 1;
        }
        break;
    default:break;
    }
}
void _draw_next_square_Four(PLAYER *tagPlayer)
{
    char szSquare_One[][5] = {
        "0100",
        "1100",//       @
        "1000",//      @@
        "0000" };//    @

    char szSquare_Two[][5] = {
        "1100",//     @@
        "0110",//      @@
        "0000" ,
        "0000" };
    switch (tagPlayer->nSquStateNext)//根据状态将形状画进4*4数组
    {
    case 1:
        _strcpy_square_state(tagPlayer->szSquareStateNext, szSquare_One);
        break;
    case 3:
        _strcpy_square_state(tagPlayer->szSquareStateNext, szSquare_One);
        break;
    case 2:
        _strcpy_square_state(tagPlayer->szSquareStateNext, szSquare_Two);
        break;
    case 4:
        _strcpy_square_state(tagPlayer->szSquareStateNext, szSquare_Two);
        break;
    default:break;
    }
}
void _operate_square_Four(PLAYER *tagPlayer, char cOperate)
{
    char szSquare_One[][5] = {
        "0100",
        "1100",//       @
        "1000",//      @@
        "0000" };//    @

    char szSquare_Two[][5] = {
        "1100",//     @@
        "0110",//      @@
        "0000" ,
        "0000" };

    switch (tagPlayer->nSquState)//根据状态将形状画进4*4数组
    {
    case 1:
        _strcpy_square_state(tagPlayer->szSquareState, szSquare_One);
        break;
    case 3:
        _strcpy_square_state(tagPlayer->szSquareState, szSquare_One);
        break;
    case 2:
        _strcpy_square_state(tagPlayer->szSquareState, szSquare_Two);
        break;
    case 4:
        _strcpy_square_state(tagPlayer->szSquareState, szSquare_Two);
        break;
    default:break;
    }
    switch (cOperate)//根据输入进行相应操作
    {
    case 'a':
    case 'j':
        if (_check_touch(tagPlayer, tagPlayer->x, tagPlayer->y - 1))
        {
            tagPlayer->y = tagPlayer->y - 1;
        }
        break;
    case 'd':
    case 'l':
        if (_check_touch(tagPlayer, tagPlayer->x, tagPlayer->y + 1))
        {
            tagPlayer->y = tagPlayer->y + 1;
        }
        break;
    case 'w':
    case 'i':
        if (tagPlayer->szBox[tagPlayer->x + 2][tagPlayer->y] == '0' && tagPlayer->szBox[tagPlayer->x + 2][tagPlayer->y + 1] == '0'
            && tagPlayer->szBox[tagPlayer->x + 2][tagPlayer->y + 2] == '0' && tagPlayer->szBox[tagPlayer->x][tagPlayer->y] == '0'
            && tagPlayer->szBox[tagPlayer->x + 1][tagPlayer->y] == '0' && tagPlayer->szBox[tagPlayer->x][tagPlayer->y + 2] == '0'
            && tagPlayer->szBox[tagPlayer->x + 1][tagPlayer->y + 2] == '0')
        {
            switch (tagPlayer->nSquState)
            {
            case 1:
                _strcpy_square_state(tagPlayer->szSquareState, szSquare_Two);
                break;
            case 3:
                _strcpy_square_state(tagPlayer->szSquareState, szSquare_Two);
                break;
            case 2:
                _strcpy_square_state(tagPlayer->szSquareState, szSquare_One);
                break;
            case 4:
                _strcpy_square_state(tagPlayer->szSquareState, szSquare_One);
                break;
            default:break;
            }
            tagPlayer->nSquState = tagPlayer->nSquState % 4 + 1;
        }
        break;
    case 's':
    case 'k':
        if (_check_touch(tagPlayer, tagPlayer->x + 1, tagPlayer->y))
        {
            tagPlayer->x = tagPlayer->x + 1;
        }
        break;
    default:break;
    }
}
void _draw_next_square_Five(PLAYER *tagPlayer)
{
    char szSquare_One[][5] = {
        "0100",
        "0100",//      @
        "0110",//      @
        "0000" };//    @@
    char szSquare_Two[][5] = {
        "0010",
        "1110",//      @
        "0000",//    @@@
        "0000" };
    char szSquare_Three[][5] = {
        "0110",
        "0010",//     @@
        "0010",//      @
        "0000" };//    @
    char szSquare_Four[][5] = {
        "1110",
        "1000",//      @@@
        "0000",//      @
        "0000" };
    switch (tagPlayer->nSquStateNext)//根据状态将形状画进4*4数组
    {
    case 1:
        _strcpy_square_state(tagPlayer->szSquareStateNext, szSquare_One);
        break;
    case 2:
        _strcpy_square_state(tagPlayer->szSquareStateNext, szSquare_Two);
        break;
    case 3:
        _strcpy_square_state(tagPlayer->szSquareStateNext, szSquare_Three);
        break;
    case 4:
        _strcpy_square_state(tagPlayer->szSquareStateNext, szSquare_Four);
        break;
    default:break;
    }
}
void _operate_square_Five(PLAYER *tagPlayer, char cOperate)
{
    char szSquare_One[][5] = {
        "0100",
        "0100",//      @
        "0110",//      @
        "0000" };//    @@
    char szSquare_Two[][5] = {
        "0010",
        "1110",//      @
        "0000",//    @@@
        "0000" };
    char szSquare_Three[][5] = {
        "0110",
        "0010",//     @@
        "0010",//      @
        "0000" };//    @
    char szSquare_Four[][5] = {
        "1110",
        "1000",//      @@@
        "0000",//      @
        "0000" };

    switch (tagPlayer->nSquState)//根据状态将形状画进4*4数组
    {
    case 1:
        _strcpy_square_state(tagPlayer->szSquareState, szSquare_One);
        break;
    case 2:
        _strcpy_square_state(tagPlayer->szSquareState, szSquare_Two);
        break;
    case 3:
        _strcpy_square_state(tagPlayer->szSquareState, szSquare_Three);
        break;
    case 4:
        _strcpy_square_state(tagPlayer->szSquareState, szSquare_Four);
        break;
    default:break;
    }
    switch (cOperate)//根据输入进行相应操作
    {
    case 'a':
    case 'j':
        if (_check_touch(tagPlayer, tagPlayer->x, tagPlayer->y - 1))
        {
            tagPlayer->y = tagPlayer->y - 1;
        }
        break;
    case 'd':
    case 'l':
        if (_check_touch(tagPlayer, tagPlayer->x, tagPlayer->y + 1))
        {
            tagPlayer->y = tagPlayer->y + 1;
        }
        break;
    case 'w':
    case 'i':
        if (tagPlayer->szBox[tagPlayer->x + 2][tagPlayer->y] == '0' && tagPlayer->szBox[tagPlayer->x + 2][tagPlayer->y + 1] == '0' && tagPlayer->szBox[tagPlayer->x + 2][tagPlayer->y + 2] == '0' && tagPlayer->szBox[tagPlayer->x][tagPlayer->y] == '0'
            && tagPlayer->szBox[tagPlayer->x + 1][tagPlayer->y] == '0' && tagPlayer->szBox[tagPlayer->x][tagPlayer->y + 2] == '0' && tagPlayer->szBox[tagPlayer->x + 1][tagPlayer->y + 2] == '0')
        {
            switch (tagPlayer->nSquState)
            {
            case 1:
                _strcpy_square_state(tagPlayer->szSquareState, szSquare_Two);
                break;
            case 2:
                _strcpy_square_state(tagPlayer->szSquareState, szSquare_Three);
                break;
            case 3:
                _strcpy_square_state(tagPlayer->szSquareState, szSquare_Four);
                break;
            case 4:
                _strcpy_square_state(tagPlayer->szSquareState, szSquare_One);
                break;
            default:break;
            }
            tagPlayer->nSquState = tagPlayer->nSquState % 4 + 1;
        }
        break;
    case 's':
    case 'k':
        if (_check_touch(tagPlayer, tagPlayer->x + 1, tagPlayer->y))
        {
            tagPlayer->x = tagPlayer->x + 1;
        }
        break;
    default:break;
    }
}
void _draw_next_square_Six(PLAYER *tagPlayer)
{
    char szSquare_One[][5] = {
        "0100",//       @
        "0100",//       @
        "0100",//       @
        "0100" };//     @

    char szSquare_Two[][5] = {
        "0000",
        "1111",//      @@@@
        "0000" ,
        "0000" };
    switch (tagPlayer->nSquStateNext)//根据状态将形状画进4*4数组
    {
    case 1:
        _strcpy_square_state(tagPlayer->szSquareStateNext, szSquare_One);
        break;
    case 3:
        _strcpy_square_state(tagPlayer->szSquareStateNext, szSquare_One);
        break;
    case 2:
        _strcpy_square_state(tagPlayer->szSquareStateNext, szSquare_Two);
        break;
    case 4:
        _strcpy_square_state(tagPlayer->szSquareStateNext, szSquare_Two);
        break;
    default:break;
    }
}
void _operate_square_Six(PLAYER *tagPlayer, char cOperate)
{
    char szSquare_One[][5] = {
        "0100",//       @
        "0100",//       @
        "0100",//       @
        "0100" };//     @

    char szSquare_Two[][5] = {
        "0000",
        "1111",//      @@@@
        "0000" ,
        "0000" };

    switch (tagPlayer->nSquState)//根据状态将形状画进4*4数组
    {
    case 1:
        _strcpy_square_state(tagPlayer->szSquareState, szSquare_One);
        break;
    case 3:
        _strcpy_square_state(tagPlayer->szSquareState, szSquare_One);
        break;
    case 2:
        _strcpy_square_state(tagPlayer->szSquareState, szSquare_Two);
        break;
    case 4:
        _strcpy_square_state(tagPlayer->szSquareState, szSquare_Two);
        break;
    default:break;
    }

    switch (cOperate)//根据输入进行相应操作
    {
    case 'a':
    case 'j':
        if (_check_touch(tagPlayer, tagPlayer->x, tagPlayer->y - 1))
        {
            tagPlayer->y = tagPlayer->y - 1;
        }
        break;
    case 'd':
    case 'l':
        if (_check_touch(tagPlayer, tagPlayer->x, tagPlayer->y + 1))
        {
            tagPlayer->y = tagPlayer->y + 1;
        }
        break;
    case 'w':
    case 'i':
        if (tagPlayer->szBox[tagPlayer->x + 3][tagPlayer->y] == '0' && tagPlayer->szBox[tagPlayer->x + 3][tagPlayer->y + 1] == '0'
            && tagPlayer->szBox[tagPlayer->x + 3][tagPlayer->y + 2] == '0' && tagPlayer->szBox[tagPlayer->x + 3][tagPlayer->y + 3] == '0'
            && tagPlayer->szBox[tagPlayer->x][tagPlayer->y] == '0' && tagPlayer->szBox[tagPlayer->x + 1][tagPlayer->y] == '0'
            && tagPlayer->szBox[tagPlayer->x + 2][tagPlayer->y] == '0' && tagPlayer->szBox[tagPlayer->x][tagPlayer->y + 3] == '0'
            && tagPlayer->szBox[tagPlayer->x + 1][tagPlayer->y + 3] == '0' && tagPlayer->szBox[tagPlayer->x + 2][tagPlayer->y + 3] == '0')
        {
            switch (tagPlayer->nSquState)
            {
            case 1:
                _strcpy_square_state(tagPlayer->szSquareState, szSquare_Two);
                break;
            case 3:
                _strcpy_square_state(tagPlayer->szSquareState, szSquare_Two);
                break;
            case 2:
                _strcpy_square_state(tagPlayer->szSquareState, szSquare_One);
                break;
            case 4:
                _strcpy_square_state(tagPlayer->szSquareState, szSquare_One);
                break;
            default:break;
            }
            tagPlayer->nSquState = tagPlayer->nSquState % 4 + 1;
        }
        break;
    case 's':
    case 'k':
        if (_check_touch(tagPlayer, tagPlayer->x + 1, tagPlayer->y))
        {
            tagPlayer->x = tagPlayer->x + 1;
        }
        break;
    default:break;
    }
}
char __char_belong(char cOperate)//判断读取的字符是哪一个玩家的
{
    if (cOperate == 'i' || cOperate == 'j' || cOperate == 'k' || cOperate == 'l')//如果此时接受的控制符不是控制A的就跳出
    {
        return 'B';
    }

    if (cOperate == 'w' || cOperate == 'a' || cOperate == 's' || cOperate == 'd')//如果此时接受的控制符不是控制B的就跳出
    {
        return 'A';
    }
    return 0;
}
void _operate_square(PLAYER *tagPlayer, char cOperate)//根据接收的参数选择相应的操作
{
    switch (tagPlayer->nSquType)
    {
    case 1:
        _operate_square_One(tagPlayer, cOperate);
        break;
    case 2:
        _operate_square_Two(tagPlayer, cOperate);
        break;
    case 3:
        _operate_square_Three(tagPlayer, cOperate);
        break;
    case 4:
        _operate_square_Four(tagPlayer, cOperate);
        break;
    case 5:
        _operate_square_Five(tagPlayer, cOperate);
        break;
    case 6:
        _operate_square_Six(tagPlayer, cOperate);
        break;
    default:break;
    }
}
void __del_grid(PLAYER *tagPlayer, int nLine)//将第nLine行删除
{
    int i = 0;
    int j = 0;

    for (i = nLine; i > 5; i--)
    {
        for (j = 1; j < WIDTH - 2; j++)
        {
            tagPlayer->szBox[i][j] = tagPlayer->szBox[i - 1][j];
        }
    }
}
void _check_full_grid(PLAYER *tagPlayer)// 检查底部是否有满格
{
    int i = 0;
    int j = 0;
    int nFlag = 0;//标志是否要消格 1表示要消
    int nCount = 0;

    while (1)
    {
        for (i = HIGH - 2; i > 5; i--)
        {
            nFlag = 1;
            for (j = 1; j < WIDTH - 2; j++)
            {
                if (tagPlayer->szBox[i][j] == '0')
                {
                    nFlag = 0;
                    break;
                }
            }
            if (nFlag == 1)
            {
                __del_grid(tagPlayer, i);
                nCount++;
                break;
            }
        }
        if (i == 5)
        {
            break;
        }
    }
    tagPlayer->nDownNum = nCount;
    switch (nCount)
    {
    case 1:
        tagPlayer->nScore = tagPlayer->nScore + 100;
        break;
    case 2:
        tagPlayer->nScore = tagPlayer->nScore + 300;
        break;
    case 3:
        tagPlayer->nScore = tagPlayer->nScore + 600;
        break;
    case 4:
        tagPlayer->nScore = tagPlayer->nScore + 1000;
        break;
    default:break;
    }
}
void _draw_next_square(PLAYER *tagPlayer)//将下一个方块画进信息区
{
    switch (tagPlayer->nSquTypeNext)
    {
    case 1:
        _draw_next_square_One(tagPlayer);
        break;
    case 2:
        _draw_next_square_Two(tagPlayer);
        break;
    case 3:
        _draw_next_square_Three(tagPlayer);
        break;
    case 4:
        _draw_next_square_Four(tagPlayer);
        break;
    case 5:
        _draw_next_square_Five(tagPlayer);
        break;
    case 6:
        _draw_next_square_Six(tagPlayer);
        break;
    default:break;
    }
}
void _refresh_map(PLAYER *playerA, PLAYER *playerB)//刷新地图
{
    if (playerA->cFlag == 'A')
    {
        __print_square(playerA, playerB);
    }
    else
    {
        __print_square(playerB, playerA);
    }
}
int __produce_square(PLAYER *playerA, PLAYER *playerB)//生产方块，返回0代表方块到顶了
{
    playerA->nFlag = 1;
    playerA->nSquType = playerA->nSquTypeNext;
    playerA->nSquState = playerA->nSquStateNext;
    _get_square_state(playerA);//产生新的方块的信息,给下一个状态
    _draw_next_square(playerA);
    playerA->x = 5;
    playerA->y = 9;
    _operate_square(playerA, 0);//起到刷新地图作用
    _refresh_map(playerA, playerB);
    if (_check_touch(playerA, playerA->x, playerA->y) == 0)//检查是否刚产生的方块已经到顶了
    {
        return 0;
    }
    return 1;
}
int _play_game(PLAYER *playerA, PLAYER *playerB)//玩家控制程序，返回0表示结束 tagMine是玩家信息，tagEnemy是敌人信息
{
    //    int nUpNum = 0;//本次需要升高的格数
    char cOperate = 0;//记录当前按键
    clock_t tCurrent = 0;//计算时间差，用于调整速度
    int nLevel = 1000;//1000ms的下落时间间隔
    int i = 0;
    int j = 0;

    tCurrent = clock();      //记录当前时间
    if (playerA->nFlag == 0)
    {
        if (__produce_square(playerA, playerB) == 0)//生产玩家A的方块
        {
            return 1;//返回1代表A输了
        }
    }
    if (playerB->nFlag == 0)
    {
        if (__produce_square(playerB, playerA) == 0)//生产玩家B的方块
        {
            return 0;//返回0代表B输了
        }
    }
    if (playerA->nDownNum != 0)//如果玩家A降格了，那么B升格
    {
        if (__up_square(playerB, playerA) == 0)//0表示升高后碰到了方块
        {
            __hold_square(playerB);//方块到底了，把它固定在box里
            rewind(stdin);//清理键盘
            playerB->nFlag = 0;
            playerB->tStart = tCurrent;
        }
    }
    if (playerB->nDownNum != 0)//如果玩家B降格了，那么A升格
    {
        if (__up_square(playerA, playerB) == 0)//0表示升高后碰到了方块
        {
            __hold_square(playerA);//方块到底了，把它固定在box里
            rewind(stdin);//清理键盘
            playerA->nFlag = 0;
            playerA->tStart = tCurrent;
        }
    }
    if (tCurrent - playerA->tStart >= nLevel)//根据nLevel来调整下落时间间隔,A的下落时间判断
    {
        playerA->tStart = tCurrent;

        if ((__down_square(playerA)) == 0)//返回0表示方块已经到底，可以产生新的方块；方块自动下降函数
        {
            __hold_square(playerA);//方块到底了，把它固定在box里
            rewind(stdin);//清理键盘
            playerA->nFlag = 0;
        }
        _refresh_map(playerA, playerB);
    }
    if (tCurrent - playerB->tStart >= nLevel)//根据nLevel来调整下落时间间隔，B的下落时间判断
    {
        playerB->tStart = tCurrent;

        if ((__down_square(playerB)) == 0)//返回0表示方块已经到底，可以产生新的方块；方块自动下降函数
        {
            __hold_square(playerB);//方块到底了，把它固定在box里
            rewind(stdin);//清理键盘
            playerB->nFlag = 0;
        }
        _refresh_map(playerB, playerA);
    }
    cOperate = _get_operate();//获取键盘输入
    rewind(stdin);//清理键盘
    if (__char_belong(cOperate) == 'A')//该操作符是A玩家输入的
    {
        _operate_square(playerA, cOperate);
        _refresh_map(playerA, playerB);
    }

    if (__char_belong(cOperate) == 'B')//该操作符是B玩家输入的
    {
        _operate_square(playerB, cOperate);
        _refresh_map(playerB, playerA);
    }

    _check_full_grid(playerA);//检查底部是否满格，顶部是否越界,降格得分
    _check_full_grid(playerB);//检查底部是否满格，顶部是否越界,降格得分
    return 2;//返回2正常退出
}

void game_begin()
{
    PLAYER playerA;
    PLAYER playerB;
    srand((unsigned)time(NULL));
    int cWin = 0;

    init_player_info(&playerA);//将两个玩家的信息初始化
    init_player_info(&playerB);
    playerA.cFlag = 'A';//给两个玩家一个标志，便于后续操作识别是哪个玩家
    playerB.cFlag = 'B';
    playerA.tStart = clock();//初始计时
    playerB.tStart = clock();//初始计时
    _get_square_state(&playerA);//给两个玩家一个初始状态的方块
    _get_square_state(&playerB);
    while (1)
    {
        cWin = _play_game(&playerA, &playerB);
        if (cWin == 0)
        {
            printf("\r\n");
            printf("                 ===================\r\n");
            printf("                 ==   玩家A胜利！ ==\r\n");
            printf("                 ===================\r\n");
            printf("\r\n");
            break;
        }
        if (cWin == 1)
        {
            printf("\r\n");
            printf("                 ===================\r\n");
            printf("                 ==   玩家B胜利！ ==\r\n");
            printf("                 ===================\r\n");
            printf("\r\n");
            break;
        }
    }
}