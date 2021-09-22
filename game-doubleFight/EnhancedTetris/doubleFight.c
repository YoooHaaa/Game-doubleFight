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
            printf("��ͼ��ʼ��ʧ�ܣ�\r\n");
        }
    }
}
void _strcpy_square_state(char(*szSquareState)[5], char(*szSquare)[5])//��Ԥ��ķ���״̬��������״̬ͼ
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
void __hold_square(PLAYER *tagPlayer)//������̶��ڵ�ǰλ�ã���д�����ͼ��Ȼ��ɾ���÷���
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
    memset(tagPlayer->szSquareState, 0, 20 * sizeof(char));//���鱻�̶�����״̬����
    tagPlayer->x = 5;//��������Ϊ����ɾ��
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
            if (tagPlayerA->szSquareState[i][j] == '1')//���Bug����3��Сʱ��Ҫ���ǣ������ж����ٸ��ƣ���Ȼ�����齵�䵽�ײ�ʱ��ֱ�Ӹ��ƻḲ�Ǳ߿��Լ��߿����µ�����
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
            printf("  ���A���֣�%5d", tagPlayerA->nScore);
        }
        if (i == 9)
        {
            printf("  ��/w ��/s ��/a ��/d");
        }
        if (i == 12)
        {
            printf("  ���B���֣�%5d", tagPlayerB->nScore);
        }
        if (i == 13)
        {
            printf("  ��/i ��/k ��/j ��/l");
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
                return 0;//0��ʾ������
            }
        }
    }
    return 1;
}
int __down_square(PLAYER *tagPlayer)//0��ʾ�����ˣ�1��ʾÿ������������һ��
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
int __up_square(PLAYER *tagPlayer, PLAYER *tagEnemy)//����ҵĸ�������nUpNum��������ߺ������˷��飬����0������ʼ������һ�����飬1������
{
    int i = 0;

    if (_check_touch(tagPlayer, tagPlayer->x + tagEnemy->nDownNum, tagPlayer->y) == 0)//�ж����ߺ�ײ��᲻���������� 0 ��ʾ������
    {
        for (i = 1; i <= tagEnemy->nDownNum; i++)
        {
            if (_check_touch(tagPlayer, tagPlayer->x + i, tagPlayer->y) == 0)//�ҵ������ߵڼ��ε�ʱ������
            {
                tagPlayer->x = tagPlayer->x - (tagEnemy->nDownNum - i + 1);//������������Ӧ�Ĳ���
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
void _get_square_state(PLAYER *tagPlayer)//�õ���һ����������ͣ�״̬
{
    tagPlayer->nSquTypeNext = rand() % 6 + 1;//1.��    2.����    3.ɽ����    4,5.Z��2��    6.L��
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
    switch (tagPlayer->nSquStateNext)//����״̬����״����4*4����
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

    switch (tagPlayer->nSquState)//����״̬����״����4*4����
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

    switch (cOperate)//�������������Ӧ����
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
    switch (tagPlayer->nSquStateNext)//����״̬����״����4*4����
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

    switch (tagPlayer->nSquState)//����״̬����״����4*4����
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

    switch (cOperate)//�������������Ӧ����
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
    switch (tagPlayer->nSquStateNext)//����״̬����״����4*4����
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

    switch (tagPlayer->nSquState)//����״̬����״����4*4����
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
    switch (cOperate)//�������������Ӧ����
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
    switch (tagPlayer->nSquStateNext)//����״̬����״����4*4����
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

    switch (tagPlayer->nSquState)//����״̬����״����4*4����
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
    switch (cOperate)//�������������Ӧ����
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
    switch (tagPlayer->nSquStateNext)//����״̬����״����4*4����
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

    switch (tagPlayer->nSquState)//����״̬����״����4*4����
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

    switch (cOperate)//�������������Ӧ����
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
char __char_belong(char cOperate)//�ж϶�ȡ���ַ�����һ����ҵ�
{
    if (cOperate == 'i' || cOperate == 'j' || cOperate == 'k' || cOperate == 'l')//�����ʱ���ܵĿ��Ʒ����ǿ���A�ľ�����
    {
        return 'B';
    }

    if (cOperate == 'w' || cOperate == 'a' || cOperate == 's' || cOperate == 'd')//�����ʱ���ܵĿ��Ʒ����ǿ���B�ľ�����
    {
        return 'A';
    }
    return 0;
}
void _operate_square(PLAYER *tagPlayer, char cOperate)//���ݽ��յĲ���ѡ����Ӧ�Ĳ���
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
void __del_grid(PLAYER *tagPlayer, int nLine)//����nLine��ɾ��
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
void _check_full_grid(PLAYER *tagPlayer)// ���ײ��Ƿ�������
{
    int i = 0;
    int j = 0;
    int nFlag = 0;//��־�Ƿ�Ҫ���� 1��ʾҪ��
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
void _draw_next_square(PLAYER *tagPlayer)//����һ�����黭����Ϣ��
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
void _refresh_map(PLAYER *playerA, PLAYER *playerB)//ˢ�µ�ͼ
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
int __produce_square(PLAYER *playerA, PLAYER *playerB)//�������飬����0�����鵽����
{
    playerA->nFlag = 1;
    playerA->nSquType = playerA->nSquTypeNext;
    playerA->nSquState = playerA->nSquStateNext;
    _get_square_state(playerA);//�����µķ������Ϣ,����һ��״̬
    _draw_next_square(playerA);
    playerA->x = 5;
    playerA->y = 9;
    _operate_square(playerA, 0);//��ˢ�µ�ͼ����
    _refresh_map(playerA, playerB);
    if (_check_touch(playerA, playerA->x, playerA->y) == 0)//����Ƿ�ղ����ķ����Ѿ�������
    {
        return 0;
    }
    return 1;
}
int _play_game(PLAYER *playerA, PLAYER *playerB)//��ҿ��Ƴ��򣬷���0��ʾ���� tagMine�������Ϣ��tagEnemy�ǵ�����Ϣ
{
    //    int nUpNum = 0;//������Ҫ���ߵĸ���
    char cOperate = 0;//��¼��ǰ����
    clock_t tCurrent = 0;//����ʱ�����ڵ����ٶ�
    int nLevel = 1000;//1000ms������ʱ����
    int i = 0;
    int j = 0;

    tCurrent = clock();      //��¼��ǰʱ��
    if (playerA->nFlag == 0)
    {
        if (__produce_square(playerA, playerB) == 0)//�������A�ķ���
        {
            return 1;//����1����A����
        }
    }
    if (playerB->nFlag == 0)
    {
        if (__produce_square(playerB, playerA) == 0)//�������B�ķ���
        {
            return 0;//����0����B����
        }
    }
    if (playerA->nDownNum != 0)//������A�����ˣ���ôB����
    {
        if (__up_square(playerB, playerA) == 0)//0��ʾ���ߺ������˷���
        {
            __hold_square(playerB);//���鵽���ˣ������̶���box��
            rewind(stdin);//�������
            playerB->nFlag = 0;
            playerB->tStart = tCurrent;
        }
    }
    if (playerB->nDownNum != 0)//������B�����ˣ���ôA����
    {
        if (__up_square(playerA, playerB) == 0)//0��ʾ���ߺ������˷���
        {
            __hold_square(playerA);//���鵽���ˣ������̶���box��
            rewind(stdin);//�������
            playerA->nFlag = 0;
            playerA->tStart = tCurrent;
        }
    }
    if (tCurrent - playerA->tStart >= nLevel)//����nLevel����������ʱ����,A������ʱ���ж�
    {
        playerA->tStart = tCurrent;

        if ((__down_square(playerA)) == 0)//����0��ʾ�����Ѿ����ף����Բ����µķ��飻�����Զ��½�����
        {
            __hold_square(playerA);//���鵽���ˣ������̶���box��
            rewind(stdin);//�������
            playerA->nFlag = 0;
        }
        _refresh_map(playerA, playerB);
    }
    if (tCurrent - playerB->tStart >= nLevel)//����nLevel����������ʱ������B������ʱ���ж�
    {
        playerB->tStart = tCurrent;

        if ((__down_square(playerB)) == 0)//����0��ʾ�����Ѿ����ף����Բ����µķ��飻�����Զ��½�����
        {
            __hold_square(playerB);//���鵽���ˣ������̶���box��
            rewind(stdin);//�������
            playerB->nFlag = 0;
        }
        _refresh_map(playerB, playerA);
    }
    cOperate = _get_operate();//��ȡ��������
    rewind(stdin);//�������
    if (__char_belong(cOperate) == 'A')//�ò�������A��������
    {
        _operate_square(playerA, cOperate);
        _refresh_map(playerA, playerB);
    }

    if (__char_belong(cOperate) == 'B')//�ò�������B��������
    {
        _operate_square(playerB, cOperate);
        _refresh_map(playerB, playerA);
    }

    _check_full_grid(playerA);//���ײ��Ƿ����񣬶����Ƿ�Խ��,����÷�
    _check_full_grid(playerB);//���ײ��Ƿ����񣬶����Ƿ�Խ��,����÷�
    return 2;//����2�����˳�
}

void game_begin()
{
    PLAYER playerA;
    PLAYER playerB;
    srand((unsigned)time(NULL));
    int cWin = 0;

    init_player_info(&playerA);//��������ҵ���Ϣ��ʼ��
    init_player_info(&playerB);
    playerA.cFlag = 'A';//���������һ����־�����ں�������ʶ�����ĸ����
    playerB.cFlag = 'B';
    playerA.tStart = clock();//��ʼ��ʱ
    playerB.tStart = clock();//��ʼ��ʱ
    _get_square_state(&playerA);//���������һ����ʼ״̬�ķ���
    _get_square_state(&playerB);
    while (1)
    {
        cWin = _play_game(&playerA, &playerB);
        if (cWin == 0)
        {
            printf("\r\n");
            printf("                 ===================\r\n");
            printf("                 ==   ���Aʤ���� ==\r\n");
            printf("                 ===================\r\n");
            printf("\r\n");
            break;
        }
        if (cWin == 1)
        {
            printf("\r\n");
            printf("                 ===================\r\n");
            printf("                 ==   ���Bʤ���� ==\r\n");
            printf("                 ===================\r\n");
            printf("\r\n");
            break;
        }
    }
}