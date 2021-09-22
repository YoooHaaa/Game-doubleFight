////////////////////////////////////////////////////////////////////////////
//���� ��֣ҫ��
//ʱ�� ��2019/4/21
//�����ܣ�˫�˰����˹���飬�����˳��档
////////////////////////////////////////////////////////////////////////////

#pragma once

#define WIDTH 21
#define HIGH  22

typedef struct Player
{
    char cFlag;                   //��ұ�־
    int  nFlag;                   //�����¿�ı�־0�������1������
    char szBox[HIGH][WIDTH];      //��ҽ���
    char szSquare[HIGH][WIDTH];   //�������
    char szSquareState[4][5];     //���鵥���ͼ��
    char szSquareStateNext[4][5]; //��һ�����鵥���ͼ��
    int x;              //��ǰ���������
    int y;              //��ǰ���������
    int xNext;          //��һ����������
    int yNext;          //��һ����������
    int nSquType;       //��������
    int nSquState;      //����״̬
    int nSquTypeNext;   //��һ����������
    int nSquStateNext;  //��һ������״̬
    int nScore;         //�÷�
    int nDownNum;       //Ŀǰ����ĸ���
    long tStart;        //��һ�����俪ʼ��ʱ��
}PLAYER;

void _init_box(char(*szMap)[WIDTH]);//��ʼ�������ͼ

void _strcpy_square_state(char(*szSquareState)[5], char(*szSquare)[5]);//��Ԥ��ķ���״̬��������״̬ͼ


void init_player_info(PLAYER *player);//��ʼ���������

void __print_square(PLAYER *tagPlayerA, PLAYER *tagPlayerB);//��ӡ��ͼ��Ϣ
void _refresh_map(PLAYER *playerA, PLAYER *playerB);//ˢ�µ�ͼ

int _check_touch(PLAYER *tagPlayer, int x, int y);//���x��y���괦�Ƿ��ܷ��·���
void __hold_square(PLAYER *tagPlayer);//��ҿ��Ƶĵ�ǰ���鱻�̶����ͽ�����д������ĵ�ͼ��
int __down_square(PLAYER *tagPlayer);//0��ʾ�����ˣ�1��ʾÿ������������һ��

void __add_grid(PLAYER *tagPlayer, int nUpNum);//����ҽ�������
int __up_square(PLAYER *tagPlayer, PLAYER *tagEnemy);//����ҵĽ�������nUpNum�㣬������ߺ������˷��飬����0������ʼ������һ�����飬1������

void _get_square_state(PLAYER *tagPlayer);//�õ���һ����������ͣ�״̬

char _get_operate();//��ȡ��Ҳ���

/*        ��ȡ��һ���������Ϣ��д����һ���������Ϣ��     */
void _draw_next_square_One(PLAYER *tagPlayer);
void _draw_next_square_Two(PLAYER *tagPlayer);
void _draw_next_square_Three(PLAYER *tagPlayer);
void _draw_next_square_Four(PLAYER *tagPlayer);
void _draw_next_square_Five(PLAYER *tagPlayer);
void _draw_next_square_Six(PLAYER *tagPlayer);
void _draw_next_square(PLAYER *tagPlayer);

/*        ����ҵ����ݴ��뺯������ʼ��������ҵķ���       */
void _operate_square_One(PLAYER *tagPlayer, char cOperate);
void _operate_square_Two(PLAYER *tagPlayer, char cOperate);
void _operate_square_Three(PLAYER *tagPlayer, char cOperate);
void _operate_square_Four(PLAYER *tagPlayer, char cOperate);
void _operate_square_Five(PLAYER *tagPlayer, char cOperate);
void _operate_square_Six(PLAYER *tagPlayer, char cOperate);
void _operate_square(PLAYER *tagPlayer, char cOperate);//���ݽ��յĲ���ѡ����Ӧ�Ĳ���


char __char_belong(char cOperate);//�ж϶�ȡ���ַ�����һ����ҵ�

void __del_grid(PLAYER *tagPlayer, int nLine);//ɾ���ײ�������
void _check_full_grid(PLAYER *tagPlayer);// ���ײ��Ƿ�������


int __produce_square(PLAYER *playerA, PLAYER *playerB);//�������飬����0�����鵽����
int _play_game(PLAYER *playerA, PLAYER *playerB);//��ҿ��Ƴ��򣬷���0��ʾ���� tagMine�������Ϣ��tagEnemy�ǵ�����Ϣ
void game_begin();//main�������ô˺���������Ϸ