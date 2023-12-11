#include <iostream>
#include <cstdio>
#include <windows.h>
#include <conio.h>
#include <io.h>
#include <process.h>
#include <unordered_map>
#include <string.h>
using namespace std;
unordered_map<int, int> op_map; // ����ӳ���
int n;          // ָ����Ŀ
int cb[100];    // conveying_belt ���ʹ��ϵ���Ʒ
int ep[100];    // empty_space ��λ
int op[100];    // out_put ���
string cm[100]; // command
int op_aim[100];
int current = 0x3f3f3f3f; // ��ǰ�������Ʒ
int idx_cb = 1, idx_ep = 0, idx_op = 1; // ���ʹ�����λ�����������
int robot_command = 0; // �����˵�����
int cb_empty = 0, op_okey = 1, ep_max = 0; // ���ʹ��Ƿ�Ϊ�գ�����Ƿ���ȷ����λ�����ֵ
int op_num1 = 2, op_num2 = 8, op_num3 = 2; // ������

// ��������

void in_forward();                 // ������ǰ����
void push_out();                   // �Ƴ�����
void robot_move_forward();         // ���ƻ�������ǰ�ƶ�
void robot_move_back();            // ���ƻ���������ƶ�
void map();                        // ��ʾ��ͼ
void show_cursor(bool if_visible); // ���ƹ�����ʾ������
void execution();                  // ִ�в���
void check();                      // ������
void user_command();               // �û���������
void menu();                       // ��ʾ�˵�
void welcome();                    // ��ӭ����
void hello();                      // ���к�
void level_1();                    // ��һ��
void level_2();                    // �ڶ���
void level_3();                    // ������
void gotoxy(int x, int y);         // ���ƹ��λ��
void play();                       // ��ʼ��Ϸ
void init();                       // ��ʼ����Ϸ


void menu() // ��ʾ�˵��ĺ���
{
    int a = 1; // ��ʼ��ѡ�����aΪ1
    while (1)  // ����ѭ����ֱ���û�ѡ���˳�
    {
        // ����a��ֵ��ʾ��ͬ�Ĳ˵�
        switch (a)
        {
        case 1:
            system("cls"); // ����
            // ��ʾ��һ��ѡ�����������ɫ�ͱ��
            printf("\033[1;30;47m*1.Level 1*\n\033[0m");
            printf("2.Level 2\n");
            printf("3.Level 3\n");
            printf("4.Level 0x3f3f3f3f\n");
            printf("Exit\n");
            break;
        // ͬ�ϣ�����case���ƣ�ֻ�Ǹ�����ʾ��ѡ�ͬ
        case 2:
            system("cls");
            printf("1.Level 1\n");
            printf("\033[1;30;47m*2.Level 2*\n\033[0m");
            printf("3.Level 3\n");
            printf("4.Level 0x3f3f3f3f\n");
            printf("Exit\n");
            break;
        case 3:
            system("cls");
            printf("1.Level 1\n");
            printf("2.Level 2\n");
            printf("\033[1;30;47m*3.Level 3*\n\033[0m");
            printf("4.Level 0x3f3f3f3f\n");
            printf("Exit\n");
            break;
        case 4:
            system("cls");
            printf("1.Level 1\n");
            printf("2.Level 2\n");
            printf("3.Level 3\n");
            printf("\033[1;30;47m*4.Level 0x3f3f3f3f*\n\033[0m");
            printf("Exit\n");
            break;
        case 5:
            system("cls");
            printf("1.Level 1\n");
            printf("2.Level 2\n");
            printf("3.Level 3\n");
            printf("4.Level 0x3f3f3f3f\n");
            printf("\033[1;30;47m*Exit*\n\033[0m");
            break;
        default:;
        }
        char t;
        t = _getch(); // ���������ҷ�������ȡ����,��һ�ζ���-32,�ڶ�����:72,��:80,��:75,��:77
        if (t == -32 || t == 13)
        {
            if (t == -32)
                t = _getch();
            switch (t)
            {
            case 72: // �ϼ�
                if (a <= 1)
                    a = 1;
                if (a > 1)
                    a--;
                break;
            case 80: // �¼�
                if (a >= 5)
                    a = 5;
                if (a < 5)
                    a++;
                break;
            case 13: // �س���
                switch (a)
                {
                case 1:
                    level_1(); // �����һ��
                    system("pause");
                    break;
                case 2:
                    level_2();
                    system("pause");
                    break;
                case 3:
                    level_3();
                    system("pause");
                    break;
                case 4:
                    system("cls");
                    printf("sorry,haven't design yet\n");
                    system("pause");
                    break;
                case 5:
                    exit(0); // �˳�����
                default:;
                }
                break;
            default:;
            }
        }
    }
    /*
        ��ʾ��ʽ��
        0��Ĭ��ֵ��
        1��������ʾ��˳��Ӵ֣���ȷ����
        2��������
        22���Ǵ��壬��ȷ����
        4���»��ߣ�
        5����˸��������û������ʲôЧ��������
        25������˸��
        7�����ԣ���Ҳû����Ч����
        27���Ƿ��ԣ�
        8�����أ�
        ������ɫ��
        30����ɫ��
        31����ɫ��
        32����ɫ��
        33����ɫ��
        34����ɫ��
        35��Ʒ�죩
        36����ɫ��
        37����ɫ��
        ����ɫ��
        40����ɫ��
        41����ɫ��
        42����ɫ��
        43����ɫ��
        44����ɫ��
        45��Ʒ�죩
        46����ɫ��
        47����ɫ��
        ��ʽ��printf("\033[��ʾ��ʽ;������ɫ;����ɫm*����*\033[0m");
        ����printf("\033[4;31;42m*ѡ��1*\033[0m");
        */
}
void gotoxy(int x, int y) // ����һ�������������ƶ�����̨�Ĺ��λ��
{
    HANDLE hout;                            // ����һ����������ڻ�ȡ����̨��������
    COORD coord;                            // ����һ������ṹ���������ù��λ��
    coord.X = y;                            // ���ù���ˮƽλ��
    coord.Y = x;                            // ���ù��Ĵ�ֱλ��
    hout = GetStdHandle(STD_OUTPUT_HANDLE); // ��ȡ����̨��������
    SetConsoleCursorPosition(hout, coord);  // ���ÿ���̨�Ĺ��λ��
}
void in_forward() // ����һ�����������ڽ����ʹ��ϵ���Ʒ��ǰ��
{
    // ����ض�λ�õ������������Ҫʱ��ʾ��ǰֵ
    gotoxy(8, 15);
    cout << "  ";
    gotoxy(8, 15);
    if (current != 0x3f3f3f3f)
    {
        if (current <= -10)
            gotoxy(8, 14);
        printf("%d", current);
    }
    // ѭ��6�Σ�ÿ�δ���һ�����ʹ�λ��
    for (int i = 1; i <= 6; i++)
    {
        // ���㴫�ʹ�λ�õ�����
        int xi = 3 * i + 5, yi = 6;
        // ������ƶ������ʹ�λ��
        gotoxy(xi, yi);
        // ��մ��ʹ�λ�õ�����
        cout << "  ";
        // ������ƶ��ش��ʹ�λ��
        gotoxy(xi, yi);
        // ������ʹ�λ������Ʒ������ʾ��Ʒ��ֵ
        // �����Ʒ��ֵС�ڵ���-10����Ϊ����ʾȫ���֣���Ҫ����������ƶ�һ��
        if (cb[idx_cb + i - 1] != 0x3f3f3f3f)
        {
            if (cb[idx_cb + i - 1] <= -10)
                gotoxy(xi, yi - 1);
            cout << cb[idx_cb + i - 1];
        }
        // ������ʹ�λ��û����Ʒ������ʾ'X'
        else
            cout << 'X';
    }
    // ѭ��4�Σ�ÿ�δ���һ����λ
    for (int i = 0; i <= 3; i++)
    {
        // �����λ����Ʒ������ʾ��Ʒ��ֵ
        // �����Ʒ��ֵС�ڵ���-10����Ϊ����ʾȫ���֣���Ҫ����������ƶ�һ��
        if (ep[i] != 0x3f3f3f3f)
        {
            gotoxy(18, 15 + 6 * i);
            cout << "  ";
            gotoxy(18, 15 + 6 * i);
            if (ep[i] <= -10)
                gotoxy(18, 14 + 6 * i);
            cout << ep[i];
        }
    }
}
void push_out() // ����һ�����������ڽ��������Ʒ�Ƴ�
{
    // ѭ��4�Σ�ÿ�δ���һ�����λ��
    for (int i = 1; i <= 4; i++)
    {
        // �������λ�õ�����
        int xi = 3 * i + 5, yi = 53;
        // ������ƶ������λ��
        gotoxy(xi, yi);
        // ������λ�õ�����
        cout << "  ";
        // ������ƶ������λ��
        gotoxy(xi, yi);
        // ������λ������Ʒ������ʾ��Ʒ��ֵ
        // �����Ʒ��ֵС�ڵ���-10����Ϊ����ʾȫ���֣���Ҫ����������ƶ�һ��
        if (idx_op - i >= 1 && op[idx_op - i] != 0x3f3f3f3f)
        {
            if (op[idx_op - i] <= -10)
                gotoxy(xi, yi - 1);
            cout << op[idx_op - i];
        }
        // ������λ��û����Ʒ������ʾ'X'
        else
            cout << 'X';
    }
}
void inbox() // "inbox"ָ��Ὣ���ʹ��ϵĵ�ǰ��Ʒȡ�������˵�����
{
    // �����ʹ��ϵĵ�ǰ��Ʒȡ�������˵�����
    current = cb[idx_cb++];
    // �����ʹ��ϵ���Ʒ��ǰ��
    in_forward();
}
void outbox() // "outbox"ָ��Ὣ���������е���Ʒ�ŵ����λ��
{
    // ��������ǰ�ƶ�
    robot_move_forward();
    // �����������������Ʒ������Ʒ�ŵ����λ��
    if (current != 0x3f3f3f3f)
        op[idx_op++] = current;
    // ��ջ����˵����е���Ʒ
    current = 0x3f3f3f3f;
    // ���������Ʒ�Ƴ�
    push_out();
    // ����������ƶ�
    robot_move_back();
}
void add(int x) // "add"ָ��Ὣ���������е���Ʒ��ָ��λ�õ���Ʒ���
{
    // �������������û����Ʒ����ָ��λ�õ���Ʒȡ�������˵�����
    if (current == 0x3f3f3f3f)
    {
        current = ep[x];
    }
    // �����������������Ʒ���򽫻��������е���Ʒ��ָ��λ�õ���Ʒ���
    else
        current += ep[x];
    // �����ʹ��ϵ���Ʒ��ǰ��
    in_forward();
}
void sub(int x) // "sub"ָ��Ὣ���������е���Ʒ��ָ��λ�õ���Ʒ���
{
    // �����������е���Ʒ��ָ��λ�õ���Ʒ���
    current -= ep[x];
    // �����ʹ��ϵ���Ʒ��ǰ��
    in_forward();
}
void copyto(int x) // "copyto"ָ��Ὣ���������е���Ʒ���Ƶ�ָ��λ��
{
    // �����������е���Ʒ���Ƶ�ָ��λ��
    ep[x] = current;
    // �����ʹ��ϵ���Ʒ��ǰ��
    in_forward();
}
void copyfrom(int x) // "copyfrom"ָ��Ὣָ��λ�õ���Ʒȡ�������˵�����
{
    // ��ָ��λ�õ���Ʒȡ�������˵�����
    current = ep[x];
    // �����ʹ��ϵ���Ʒ��ǰ��
    in_forward();
}
void jump(int x) // "jump"ָ���ʹ��������ת��ָ����ָ��
{
    // ʹ��������ת��ָ����ָ��
    robot_command = x - 1;
}
void jumpifzero(int x) // "jumpifzero"ָ����ڻ��������е���ƷΪ0ʱ��ʹ��������ת��ָ����ָ��
{
    // ������������е���ƷΪ0����ʹ��������ת��ָ����ָ��
    if (current == 0)
        robot_command = x - 1;
}
void level_1() // ����һ���������������õ�һ�ص���Ϸ״̬
{
    // ��տ���̨������
    system("cls");
    // ��ʼ����Ϸ��״̬
    init();
    // ��ӡ�ؿ�����Ϣ
    printf("Level information:Level 1\n");
    // ��ӡ�ؿ������������Ϣ
    cout << "    a. �ؿ����������\n";
    cout << "        b. �������У�1, 2\n";
    cout << "        c. Ŀ��������У�1, 2\n";
    // ��ӡ���ÿյ���
    cout << "    d. ���ÿյ�����0\n";
    // ��ӡ����ָ�
    cout << "    e. ����ָ���inbox,outbox\n";
    cout << endl;
    // ��ʾ��ͼ
    map();
    // ��ʾ����̨�Ĺ��
    show_cursor(1);
    // ���ô��ʹ��ϵ���Ʒ
    cb[1] = 1;
    cb[2] = 2;
    // ���������Ŀ��
    op_aim[1] = 1;
    op_aim[2] = 2;
    // ��ʼ��Ϸ
    play();
}
void level_2() // ����һ���������������õڶ��ص���Ϸ״̬
{
    // ��տ���̨������
    system("cls");
    // ��ʼ����Ϸ��״̬
    init();
    // ��ӡ�ؿ�����Ϣ
    printf("Level information:Level 2\n");
    // ��ӡ�ؿ������������Ϣ
    cout << "    a. �ؿ����������\n";
    cout << "        b. �������У�3,9,5,1,-2,-2,9,-9\n";
    cout << "        c. Ŀ��������У�-6,6,4,-4,0,0,18,-18\n";
    // ��ӡ���ÿյ���
    cout << "    d. ���ÿյ�����3\n";
    // ��ӡ����ָ�
    cout << "    e. ����ָ���inbox,outbox,copyfrom,copyto,add,sub,jump,jumpifzero\n";
    cout << endl;
    // ��ʾ��ͼ
    map();
    // ��ʾ����̨�Ĺ��
    show_cursor(1);
    // ���ô��ʹ��ϵ���Ʒ
    cb[1] = 3;
    cb[2] = 9;
    cb[3] = 5;
    cb[4] = 1;
    cb[5] = -2;
    cb[6] = -2;
    cb[7] = 9;
    cb[8] = -9;
    // ���������Ŀ��
    op_aim[1] = -6;
    op_aim[2] = 6;
    op_aim[3] = 4;
    op_aim[4] = -4;
    op_aim[5] = 0;
    op_aim[6] = 0;
    op_aim[7] = 18;
    op_aim[8] = -18;
    // ���ÿ��ÿյ���
    ep_max = 3;
    // ��ʼ��Ϸ
    play();
}
void level_3() // ����һ���������������õ����ص���Ϸ״̬
{
    // ��տ���̨������
    system("cls");
    // ��ʼ����Ϸ��״̬
    init();
    // ��ӡ�ؿ�����Ϣ
    printf("Level information:Level 3\n");
    // ��ӡ�ؿ������������Ϣ
    cout << "    a. �ؿ����������\n";
    cout << "        b. �������У�6,2,7,7,-9,3,-3,-3\n";
    cout << "        c. Ŀ��������У�7,-3\n";
    // ��ӡ���ÿյ���
    cout << "    d. ���ÿյ�����3\n";
    // ��ӡ����ָ�
    cout << "    e. ����ָ���inbox,outbox,copyfrom,copyto,add,sub,jump,jumpifzero\n";
    cout << endl;
    // ��ʾ��ͼ
    map();
    // ��ʾ����̨�Ĺ��
    show_cursor(1);
    // ���ô��ʹ��ϵ���Ʒ
    cb[1] = 6;
    cb[2] = 2;
    cb[3] = 7;
    cb[4] = 7;
    cb[5] = -9;
    cb[6] = 3;
    cb[7] = -3;
    cb[8] = -3;
    // ���������Ŀ��
    op_aim[1] = 7;
    op_aim[2] = -3;
    // ���ÿ��ÿյ���
    ep_max = 3;
    // ��ʼ��Ϸ
    play();
}
void play() // ����һ�����������ڿ�ʼ��Ϸ
{
    // ��ʼ�����ʹ�������Ϳ�λ������
    idx_cb = 1, idx_op = 1, idx_ep = 0;
    // ��ȡ�û���ָ��
    user_command();
    // ���ؿ���̨�Ĺ��
    show_cursor(0);
    // ���������Ʒ����
    in_forward();
    // ���������Ʒ�Ƴ�
    push_out();
    // ��ͣ500����
    Sleep(500);
    // ִ���û���ָ��
    execution();
    // ������ƶ�������̨���ض�λ��
    gotoxy(24, 0);
    // �����Ϸ��״̬
    check();
}
void check() // ����һ�����������ڼ����Ϸ��״̬
{
    // ������ƶ�������̨���ض�λ��
    gotoxy(26, 0);
    // ������ʹ���û����Ʒ����cb_empty����Ϊ1
    if (cb[idx_cb] == 0x3f3f3f3f)
        cb_empty = 1;
    // ѭ����������Ŀ���ʵ�ʵ�����Ƿ�ƥ��
    for (int i = 1; i <= 20; i++)
    {
        // ��������Ŀ���ʵ�ʵ������ƥ�䣬��op_okey����Ϊ0
        if (op_aim[i] != 0x3f3f3f3f)
            if (op[i] != op_aim[i])
                op_okey = 0;
    }
    // ������ʹ���û����Ʒ���������Ŀ���ʵ�ʵ����ƥ�䣬����ʾ"you made it"
    // ������ʾ"sorry,you lose"
    if (cb_empty && op_okey)
        cout << "you made it";
    else
        cout << "sorry,you lose";
}
void show_cursor(bool if_visible) // �������ؿ���̨���
{
    HANDLE hOut;
    CONSOLE_CURSOR_INFO cur = {20, if_visible}; // ��������dwSize(1~100)������bVisible��������
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    // cur.dwSize=1;
    // cur.bVisible=False;
    SetConsoleCursorInfo(hOut, &cur);
}
void robot_move_forward() // �û����˰ᶫ����ȥ
{
    for (int i = 0; i <= 30; i++)
    {
        gotoxy(7, 13 + i);
        cout << " +---+";
        gotoxy(8, 13 + i);
        if (current >= 0 && current < 10)
            cout << " | " << current << " |";
        else if (current <= -10)
            cout << " |" << current << "|";
        else
            cout << " | " << current << "|";
        gotoxy(9, 13 + i);
        cout << " +---+";
        gotoxy(10, 13 + i);
        cout << " @   @";
        gotoxy(11, 13 + i);
        cout << " -----";
        gotoxy(12, 13 + i);
        cout << " |@ @|";
        gotoxy(13, 15 + i);
        cout << " +";
        gotoxy(14, 13 + i);
        cout << " /   \\";
        gotoxy(15, 14 + i);
        cout << " | |";
        Sleep(80);
    }
}
void robot_move_back() // �û������߻���
{
    for (int i = 30; i >= 0; i--)
    {
        gotoxy(7, 13 + i);
        cout << "+---+ ";
        gotoxy(8, 13 + i);
        cout << "| " << 'X' << " | ";
        gotoxy(9, 13 + i);
        cout << "+---+ ";
        gotoxy(10, 13 + i);
        cout << "@   @ ";
        gotoxy(11, 13 + i);
        cout << "----- ";
        gotoxy(12, 13 + i);
        cout << "|@ @| ";
        gotoxy(13, 15 + i);
        cout << "+ ";
        gotoxy(14, 13 + i);
        cout << "/   \\ ";
        gotoxy(15, 14 + i);
        cout << "| | ";
        Sleep(80);
    }
}
void user_command() // ����һ�����������ڻ�ȡ�û���ָ��
{
    // �ڿ���̨���ض�λ�ô�ӡ���ߣ����ڷָ���ͬ������
    for (int i = 1; i <= 17; i++)
    {
        gotoxy(i + 6, 62);
        cout << '|';
    }
    // ��ʾ�û�����ָ������
    gotoxy(7, 66);
    cout << "����������ָ������:";
    // ��ȡ�û������ָ������
    cin >> n;
    // �����û������ָ��������ѭ����ȡÿһ��ָ��
    for (int i = 1; i <= n; i++)
    {
        // �ڿ���̨���ض�λ����ʾָ������
        gotoxy(i + 7, 66);
        cout << i << " ";
        // ��ȡ�û������ָ��
        cin >> cm[i];
        int num;
        // ���ָ���"inbox"��"outbox"������Ҫ��ȡһ������
        if (cm[i] != "inbox" && cm[i] != "outbox")
        {
            cin >> num;
            // ��ָ����ź����ִ���ӳ���
            op_map[i] = num;
        }
    }
    // �ڿ���̨���ض�λ����ʾ">"����ʾ�����û������ָ��
    gotoxy(7, 64);
    cout << ">";
    // ��ͣ500����
    Sleep(500);
    // ���">"����ʾ��ʼִ���û������ָ��
    gotoxy(7, 64);
    cout << " ";
}
void execution() // ����һ������������ִ���û���ָ��
{
    // �����û������ָ��������ѭ��ִ��ÿһ��ָ��
    for (int i = 1; i <= n; i++)
    {
        // ���û����˵�����Ϊ��ǰ��ָ�����
        robot_command = i;
        // �ڿ���̨���ض�λ����ʾ">"����ʾ����ִ�е�ǰ��ָ��
        gotoxy(robot_command + 7, 64);
        cout << ">";
        // ��ͣ300����
        Sleep(300);
        // ����ָ������ͣ�������Ӧ�ĺ���
        if (cm[robot_command] == "inbox")
            inbox();
        else if (cm[robot_command] == "outbox")
            outbox();
        else if (cm[robot_command] == "add")
            add(op_map[robot_command]);
        else if (cm[robot_command] == "sub")
            sub(op_map[robot_command]);
        else if (cm[robot_command] == "copyto")
            copyto(op_map[robot_command]);
        else if (cm[robot_command] == "copyfrom")
            copyfrom(op_map[robot_command]);
        else if (cm[robot_command] == "jump")
        {
            jump(op_map[robot_command]);
            // ���ָ����"jump"������ת���û�ָ����λ��
            i = robot_command;
        }
        else if (cm[robot_command] == "jumpifzero")
        {
            jumpifzero(op_map[robot_command]);
            // ���ָ����"jumpifzero"������ת���û�ָ����λ��
            i = robot_command;
        }
        // ������ʹ���û����Ʒ���ҵ�ǰ�������ƷΪ�գ��������Ŀ��Ϊ�գ������ִ��
        if (cb[idx_cb] == 0x3f3f3f3f && current == 0x3f3f3f3f && op_aim[idx_op] == 0x3f3f3f3f)
            break;
        // ��ͣ300����
        Sleep(300);
        // ���">"����ʾ��ǰ��ָ��ִ�н���
        gotoxy(i + 7, 64);
        cout << " ";
    }
}
void map() // ��ӡ��ͼ
{
    char a[70][70] = {
        "    +---+    +---+                                 +---+     ",
        "In  | X |    | X |                                 | X |  OUT",
        "    +---+    +---+                                 +---+     ",
        "    +---+    @   @                                 +---+     ",
        "    | X |    -----                                 | X |     ",
        "    +---+    |@ @|                                 +---+     ",
        "    +---+      +                                   +---+     ",
        "    | X |    /   \\                                 | X |    ",
        "    +---+     | |                                  +---+     ",
        "    +---+                                          +---+     ",
        "    | X |    +---+ +---+ +---+ +---+               | X |     ",
        "    +---+    | X | | X | | X | | X |               +---+     ",
        "    +---+    +---+ +---+ +---+ +---+                         ",
        "    | X |      0     1     2     3                           ",
        "    +---+                                                    ",
        "    +---+                                                    ",
        "    | X |                                                    ",
        "    +---+                                                    ",
    };
    for (int i = 0; i <= 17; i++)
    {
        puts(a[i]);
        // printf("\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
    }
}
void Welcome() // ��ӭ����
{
    // ��ӡ��Ϸ����
    printf("\n           Human resource machine");
    // ��ʾ�û����������ʼ��Ϸ
    printf("\n\n            �밴�������ʼ��Ϸ");
    int a;
    // ʹ��_getch������ȡ�û��İ������룬_getch������ȴ��û�������
    a = _getch();
    // ������Ϊ��Ϸ��ʼ��׼��
    system("cls");
}
void init() // ��ʼ�����������ڽ�����cb��op_aim��ep��op������Ԫ�ض�����Ϊ0x3f3f3f3f
{
    memset(cb, 0x3f, sizeof cb);
    memset(op_aim, 0x3f, sizeof op_aim);
    memset(ep, 0x3f, sizeof ep);
    memset(op, 0x3f, sizeof op);
}
int main()
{
    // ���ÿ���̨����ɫ���ԣ�07��ʾ����ɫΪ��ɫ��ǰ��ɫΪ��ɫ
    system("color 07");
    /*
    ��ɫ����������ʮ����������ָ�� -- ��һ��
    ��Ӧ�ڱ������ڶ�����Ӧ��ǰ����ÿ������
    ����Ϊ�����κ�ֵ:
    0 = ��ɫ       8 = ��ɫ
    1 = ��ɫ       9 = ����ɫ
    2 = ��ɫ       A = ����ɫ
    3 = ǳ��ɫ     B = ��ǳ��ɫ
    4 = ��ɫ       C = ����ɫ
    5 = ��ɫ       D = ����ɫ
    6 = ��ɫ       E = ����ɫ
    7 = ��ɫ       F = ����ɫ
    */
    // ��ʾ��ӭ��Ϣ
    Welcome();
    // ���ؿ���̨�Ĺ��
    show_cursor(0);
    // ��ʾ�˵�
    menu();
    // ��ͣһ��
    Sleep(1000);
    return 0;
}
