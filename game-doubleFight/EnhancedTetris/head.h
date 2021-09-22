////////////////////////////////////////////////////////////////////////////
//作者 ：郑耀华
//时间 ：2019/4/21
//程序功能：双人版俄罗斯方块，此消彼长版。
////////////////////////////////////////////////////////////////////////////

#pragma once

#define WIDTH 21
#define HIGH  22

typedef struct Player
{
    char cFlag;                   //玩家标志
    int  nFlag;                   //产生新块的标志0代表产生1不产生
    char szBox[HIGH][WIDTH];      //玩家界面
    char szSquare[HIGH][WIDTH];   //方块界面
    char szSquareState[4][5];     //方块单体的图像
    char szSquareStateNext[4][5]; //下一个方块单体的图像
    int x;              //当前方块的坐标
    int y;              //当前方块的坐标
    int xNext;          //下一个方块坐标
    int yNext;          //下一个方块坐标
    int nSquType;       //方块类型
    int nSquState;      //方块状态
    int nSquTypeNext;   //下一个方块类型
    int nSquStateNext;  //下一个方块状态
    int nScore;         //得分
    int nDownNum;       //目前降格的个数
    long tStart;        //上一次下落开始的时间
}PLAYER;

void _init_box(char(*szMap)[WIDTH]);//初始化界面地图

void _strcpy_square_state(char(*szSquareState)[5], char(*szSquare)[5]);//将预存的方块状态画进方块状态图


void init_player_info(PLAYER *player);//初始化玩家数据

void __print_square(PLAYER *tagPlayerA, PLAYER *tagPlayerB);//打印地图信息
void _refresh_map(PLAYER *playerA, PLAYER *playerB);//刷新地图

int _check_touch(PLAYER *tagPlayer, int x, int y);//检查x，y坐标处是否能放下方块
void __hold_square(PLAYER *tagPlayer);//玩家控制的当前方块被固定，就将方块写进界面的地图里
int __down_square(PLAYER *tagPlayer);//0表示到底了，1表示每碰到，并下落一格

void __add_grid(PLAYER *tagPlayer, int nUpNum);//将玩家界面升高
int __up_square(PLAYER *tagPlayer, PLAYER *tagEnemy);//将玩家的界面升高nUpNum层，如果升高后碰到了方块，返回0，代表开始产生下一个方块，1不产生

void _get_square_state(PLAYER *tagPlayer);//得到下一个方块的类型，状态

char _get_operate();//获取玩家操作

/*        获取下一个方块的信息，写进下一个方块的信息区     */
void _draw_next_square_One(PLAYER *tagPlayer);
void _draw_next_square_Two(PLAYER *tagPlayer);
void _draw_next_square_Three(PLAYER *tagPlayer);
void _draw_next_square_Four(PLAYER *tagPlayer);
void _draw_next_square_Five(PLAYER *tagPlayer);
void _draw_next_square_Six(PLAYER *tagPlayer);
void _draw_next_square(PLAYER *tagPlayer);

/*        将玩家的数据传入函数，开始操作该玩家的方块       */
void _operate_square_One(PLAYER *tagPlayer, char cOperate);
void _operate_square_Two(PLAYER *tagPlayer, char cOperate);
void _operate_square_Three(PLAYER *tagPlayer, char cOperate);
void _operate_square_Four(PLAYER *tagPlayer, char cOperate);
void _operate_square_Five(PLAYER *tagPlayer, char cOperate);
void _operate_square_Six(PLAYER *tagPlayer, char cOperate);
void _operate_square(PLAYER *tagPlayer, char cOperate);//根据接收的参数选择相应的操作


char __char_belong(char cOperate);//判断读取的字符是哪一个玩家的

void __del_grid(PLAYER *tagPlayer, int nLine);//删除底部的满格
void _check_full_grid(PLAYER *tagPlayer);// 检查底部是否有满格


int __produce_square(PLAYER *playerA, PLAYER *playerB);//生产方块，返回0代表方块到顶了
int _play_game(PLAYER *playerA, PLAYER *playerB);//玩家控制程序，返回0表示结束 tagMine是玩家信息，tagEnemy是敌人信息
void game_begin();//main函数调用此函数开启游戏