#include <iostream>
#include <cstdio>
#include <windows.h>
#include <conio.h>
#include <io.h>
#include <process.h>
#include <unordered_map>
#include <string.h>
using namespace std;
unordered_map<int, int> op_map; // 操作映射表
int n;          // 指令数目
int cb[100];    // conveying_belt 传送带上的物品
int ep[100];    // empty_space 空位
int op[100];    // out_put 输出
string cm[100]; // command
int op_aim[100];
int current = 0x3f3f3f3f; // 当前处理的物品
int idx_cb = 1, idx_ep = 0, idx_op = 1; // 传送带、空位和输出的索引
int robot_command = 0; // 机器人的命令
int cb_empty = 0, op_okey = 1, ep_max = 0; // 传送带是否为空，输出是否正确，空位的最大值
int op_num1 = 2, op_num2 = 8, op_num3 = 2; // 操作数

// 声明函数

void in_forward();                 // 控制向前输入
void push_out();                   // 推出操作
void robot_move_forward();         // 控制机器人向前移动
void robot_move_back();            // 控制机器人向后移动
void map();                        // 显示地图
void show_cursor(bool if_visible); // 控制光标的显示与隐藏
void execution();                  // 执行操作
void check();                      // 检查操作
void user_command();               // 用户命令输入
void menu();                       // 显示菜单
void welcome();                    // 欢迎界面
void hello();                      // 打招呼
void level_1();                    // 第一关
void level_2();                    // 第二关
void level_3();                    // 第三关
void gotoxy(int x, int y);         // 控制光标位置
void play();                       // 开始游戏
void init();                       // 初始化游戏


void menu() // 显示菜单的函数
{
    int a = 1; // 初始化选项变量a为1
    while (1)  // 无限循环，直到用户选择退出
    {
        // 根据a的值显示不同的菜单
        switch (a)
        {
        case 1:
            system("cls"); // 清屏
            // 显示第一关选项，带有特殊颜色和标记
            printf("\033[1;30;47m*1.Level 1*\n\033[0m");
            printf("2.Level 2\n");
            printf("3.Level 3\n");
            printf("4.Level 0x3f3f3f3f\n");
            printf("Exit\n");
            break;
        // 同上，其他case类似，只是高亮显示的选项不同
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
        t = _getch(); // 按上下左右方向键会读取两次,第一次都是-32,第二次上:72,下:80,左:75,右:77
        if (t == -32 || t == 13)
        {
            if (t == -32)
                t = _getch();
            switch (t)
            {
            case 72: // 上键
                if (a <= 1)
                    a = 1;
                if (a > 1)
                    a--;
                break;
            case 80: // 下键
                if (a >= 5)
                    a = 5;
                if (a < 5)
                    a++;
                break;
            case 13: // 回车键
                switch (a)
                {
                case 1:
                    level_1(); // 进入第一关
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
                    exit(0); // 退出程序
                default:;
                }
                break;
            default:;
            }
        }
    }
    /*
        显示方式：
        0（默认值）
        1（高亮显示，顺便加粗？不确定）
        2（暗淡）
        22（非粗体，不确定）
        4（下划线）
        5（闪烁，但是我没看出有什么效果。。）
        25（非闪烁）
        7（反显，我也没看出效果）
        27（非反显）
        8（隐藏）
        字体颜色：
        30（黑色）
        31（红色）
        32（绿色）
        33（黄色）
        34（蓝色）
        35（品红）
        36（青色）
        37（白色）
        背景色：
        40（黑色）
        41（红色）
        42（绿色）
        43（黄色）
        44（蓝色）
        45（品红）
        46（青色）
        47（白色）
        格式：printf("\033[显示方式;字体颜色;背景色m*文字*\033[0m");
        例：printf("\033[4;31;42m*选择1*\033[0m");
        */
}
void gotoxy(int x, int y) // 定义一个函数，用于移动控制台的光标位置
{
    HANDLE hout;                            // 定义一个句柄，用于获取控制台的输出句柄
    COORD coord;                            // 定义一个坐标结构，用于设置光标位置
    coord.X = y;                            // 设置光标的水平位置
    coord.Y = x;                            // 设置光标的垂直位置
    hout = GetStdHandle(STD_OUTPUT_HANDLE); // 获取控制台的输出句柄
    SetConsoleCursorPosition(hout, coord);  // 设置控制台的光标位置
}
void in_forward() // 定义一个函数，用于将传送带上的物品向前推
{
    // 清除特定位置的输出，并在需要时显示当前值
    gotoxy(8, 15);
    cout << "  ";
    gotoxy(8, 15);
    if (current != 0x3f3f3f3f)
    {
        if (current <= -10)
            gotoxy(8, 14);
        printf("%d", current);
    }
    // 循环6次，每次处理一个传送带位置
    for (int i = 1; i <= 6; i++)
    {
        // 计算传送带位置的坐标
        int xi = 3 * i + 5, yi = 6;
        // 将光标移动到传送带位置
        gotoxy(xi, yi);
        // 清空传送带位置的内容
        cout << "  ";
        // 将光标移动回传送带位置
        gotoxy(xi, yi);
        // 如果传送带位置有物品，则显示物品的值
        // 如果物品的值小于等于-10，则为了显示全数字，需要将光标向左移动一格
        if (cb[idx_cb + i - 1] != 0x3f3f3f3f)
        {
            if (cb[idx_cb + i - 1] <= -10)
                gotoxy(xi, yi - 1);
            cout << cb[idx_cb + i - 1];
        }
        // 如果传送带位置没有物品，则显示'X'
        else
            cout << 'X';
    }
    // 循环4次，每次处理一个空位
    for (int i = 0; i <= 3; i++)
    {
        // 如果空位有物品，则显示物品的值
        // 如果物品的值小于等于-10，则为了显示全数字，需要将光标向左移动一格
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
void push_out() // 定义一个函数，用于将输出的物品推出
{
    // 循环4次，每次处理一个输出位置
    for (int i = 1; i <= 4; i++)
    {
        // 计算输出位置的坐标
        int xi = 3 * i + 5, yi = 53;
        // 将光标移动到输出位置
        gotoxy(xi, yi);
        // 清空输出位置的内容
        cout << "  ";
        // 将光标移动回输出位置
        gotoxy(xi, yi);
        // 如果输出位置有物品，则显示物品的值
        // 如果物品的值小于等于-10，则为了显示全数字，需要将光标向左移动一格
        if (idx_op - i >= 1 && op[idx_op - i] != 0x3f3f3f3f)
        {
            if (op[idx_op - i] <= -10)
                gotoxy(xi, yi - 1);
            cout << op[idx_op - i];
        }
        // 如果输出位置没有物品，则显示'X'
        else
            cout << 'X';
    }
}
void inbox() // "inbox"指令会将传送带上的当前物品取到机器人的手中
{
    // 将传送带上的当前物品取到机器人的手中
    current = cb[idx_cb++];
    // 将传送带上的物品向前推
    in_forward();
}
void outbox() // "outbox"指令会将机器人手中的物品放到输出位置
{
    // 机器人向前移动
    robot_move_forward();
    // 如果机器人手中有物品，则将物品放到输出位置
    if (current != 0x3f3f3f3f)
        op[idx_op++] = current;
    // 清空机器人的手中的物品
    current = 0x3f3f3f3f;
    // 将输出的物品推出
    push_out();
    // 机器人向后移动
    robot_move_back();
}
void add(int x) // "add"指令会将机器人手中的物品和指定位置的物品相加
{
    // 如果机器人手中没有物品，则将指定位置的物品取到机器人的手中
    if (current == 0x3f3f3f3f)
    {
        current = ep[x];
    }
    // 如果机器人手中有物品，则将机器人手中的物品和指定位置的物品相加
    else
        current += ep[x];
    // 将传送带上的物品向前推
    in_forward();
}
void sub(int x) // "sub"指令会将机器人手中的物品和指定位置的物品相减
{
    // 将机器人手中的物品和指定位置的物品相减
    current -= ep[x];
    // 将传送带上的物品向前推
    in_forward();
}
void copyto(int x) // "copyto"指令会将机器人手中的物品复制到指定位置
{
    // 将机器人手中的物品复制到指定位置
    ep[x] = current;
    // 将传送带上的物品向前推
    in_forward();
}
void copyfrom(int x) // "copyfrom"指令会将指定位置的物品取到机器人的手中
{
    // 将指定位置的物品取到机器人的手中
    current = ep[x];
    // 将传送带上的物品向前推
    in_forward();
}
void jump(int x) // "jump"指令会使机器人跳转到指定的指令
{
    // 使机器人跳转到指定的指令
    robot_command = x - 1;
}
void jumpifzero(int x) // "jumpifzero"指令会在机器人手中的物品为0时，使机器人跳转到指定的指令
{
    // 如果机器人手中的物品为0，则使机器人跳转到指定的指令
    if (current == 0)
        robot_command = x - 1;
}
void level_1() // 定义一个函数，用于设置第一关的游戏状态
{
    // 清空控制台的内容
    system("cls");
    // 初始化游戏的状态
    init();
    // 打印关卡的信息
    printf("Level information:Level 1\n");
    // 打印关卡的输入输出信息
    cout << "    a. 关卡的输入输出\n";
    cout << "        b. 输入序列：1, 2\n";
    cout << "        c. 目标输出序列：1, 2\n";
    // 打印可用空地数
    cout << "    d. 可用空地数：0\n";
    // 打印可用指令集
    cout << "    e. 可用指令集：inbox,outbox\n";
    cout << endl;
    // 显示地图
    map();
    // 显示控制台的光标
    show_cursor(1);
    // 设置传送带上的物品
    cb[1] = 1;
    cb[2] = 2;
    // 设置输出的目标
    op_aim[1] = 1;
    op_aim[2] = 2;
    // 开始游戏
    play();
}
void level_2() // 定义一个函数，用于设置第二关的游戏状态
{
    // 清空控制台的内容
    system("cls");
    // 初始化游戏的状态
    init();
    // 打印关卡的信息
    printf("Level information:Level 2\n");
    // 打印关卡的输入输出信息
    cout << "    a. 关卡的输入输出\n";
    cout << "        b. 输入序列：3,9,5,1,-2,-2,9,-9\n";
    cout << "        c. 目标输出序列：-6,6,4,-4,0,0,18,-18\n";
    // 打印可用空地数
    cout << "    d. 可用空地数：3\n";
    // 打印可用指令集
    cout << "    e. 可用指令集：inbox,outbox,copyfrom,copyto,add,sub,jump,jumpifzero\n";
    cout << endl;
    // 显示地图
    map();
    // 显示控制台的光标
    show_cursor(1);
    // 设置传送带上的物品
    cb[1] = 3;
    cb[2] = 9;
    cb[3] = 5;
    cb[4] = 1;
    cb[5] = -2;
    cb[6] = -2;
    cb[7] = 9;
    cb[8] = -9;
    // 设置输出的目标
    op_aim[1] = -6;
    op_aim[2] = 6;
    op_aim[3] = 4;
    op_aim[4] = -4;
    op_aim[5] = 0;
    op_aim[6] = 0;
    op_aim[7] = 18;
    op_aim[8] = -18;
    // 设置可用空地数
    ep_max = 3;
    // 开始游戏
    play();
}
void level_3() // 定义一个函数，用于设置第三关的游戏状态
{
    // 清空控制台的内容
    system("cls");
    // 初始化游戏的状态
    init();
    // 打印关卡的信息
    printf("Level information:Level 3\n");
    // 打印关卡的输入输出信息
    cout << "    a. 关卡的输入输出\n";
    cout << "        b. 输入序列：6,2,7,7,-9,3,-3,-3\n";
    cout << "        c. 目标输出序列：7,-3\n";
    // 打印可用空地数
    cout << "    d. 可用空地数：3\n";
    // 打印可用指令集
    cout << "    e. 可用指令集：inbox,outbox,copyfrom,copyto,add,sub,jump,jumpifzero\n";
    cout << endl;
    // 显示地图
    map();
    // 显示控制台的光标
    show_cursor(1);
    // 设置传送带上的物品
    cb[1] = 6;
    cb[2] = 2;
    cb[3] = 7;
    cb[4] = 7;
    cb[5] = -9;
    cb[6] = 3;
    cb[7] = -3;
    cb[8] = -3;
    // 设置输出的目标
    op_aim[1] = 7;
    op_aim[2] = -3;
    // 设置可用空地数
    ep_max = 3;
    // 开始游戏
    play();
}
void play() // 定义一个函数，用于开始游戏
{
    // 初始化传送带、输出和空位的索引
    idx_cb = 1, idx_op = 1, idx_ep = 0;
    // 获取用户的指令
    user_command();
    // 隐藏控制台的光标
    show_cursor(0);
    // 将输入的物品拿起
    in_forward();
    // 将输出的物品推出
    push_out();
    // 暂停500毫秒
    Sleep(500);
    // 执行用户的指令
    execution();
    // 将光标移动到控制台的特定位置
    gotoxy(24, 0);
    // 检查游戏的状态
    check();
}
void check() // 定义一个函数，用于检查游戏的状态
{
    // 将光标移动到控制台的特定位置
    gotoxy(26, 0);
    // 如果传送带上没有物品，则将cb_empty设置为1
    if (cb[idx_cb] == 0x3f3f3f3f)
        cb_empty = 1;
    // 循环检查输出的目标和实际的输出是否匹配
    for (int i = 1; i <= 20; i++)
    {
        // 如果输出的目标和实际的输出不匹配，则将op_okey设置为0
        if (op_aim[i] != 0x3f3f3f3f)
            if (op[i] != op_aim[i])
                op_okey = 0;
    }
    // 如果传送带上没有物品，且输出的目标和实际的输出匹配，则显示"you made it"
    // 否则，显示"sorry,you lose"
    if (cb_empty && op_okey)
        cout << "you made it";
    else
        cout << "sorry,you lose";
}
void show_cursor(bool if_visible) // 用于隐藏控制台光标
{
    HANDLE hOut;
    CONSOLE_CURSOR_INFO cur = {20, if_visible}; // 必须设置dwSize(1~100)再设置bVisible才能隐藏
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    // cur.dwSize=1;
    // cur.bVisible=False;
    SetConsoleCursorInfo(hOut, &cur);
}
void robot_move_forward() // 让机器人搬东西过去
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
void robot_move_back() // 让机器人走回来
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
void user_command() // 定义一个函数，用于获取用户的指令
{
    // 在控制台的特定位置打印竖线，用于分隔不同的区域
    for (int i = 1; i <= 17; i++)
    {
        gotoxy(i + 6, 62);
        cout << '|';
    }
    // 提示用户输入指令数量
    gotoxy(7, 66);
    cout << "请输入您的指令数量:";
    // 获取用户输入的指令数量
    cin >> n;
    // 根据用户输入的指令数量，循环获取每一条指令
    for (int i = 1; i <= n; i++)
    {
        // 在控制台的特定位置显示指令的序号
        gotoxy(i + 7, 66);
        cout << i << " ";
        // 获取用户输入的指令
        cin >> cm[i];
        int num;
        // 如果指令不是"inbox"和"outbox"，则还需要获取一个数字
        if (cm[i] != "inbox" && cm[i] != "outbox")
        {
            cin >> num;
            // 将指令序号和数字存入映射表
            op_map[i] = num;
        }
    }
    // 在控制台的特定位置显示">"，表示读入用户输入的指令
    gotoxy(7, 64);
    cout << ">";
    // 暂停500毫秒
    Sleep(500);
    // 清除">"，表示开始执行用户输入的指令
    gotoxy(7, 64);
    cout << " ";
}
void execution() // 定义一个函数，用于执行用户的指令
{
    // 根据用户输入的指令数量，循环执行每一条指令
    for (int i = 1; i <= n; i++)
    {
        // 设置机器人的命令为当前的指令序号
        robot_command = i;
        // 在控制台的特定位置显示">"，表示正在执行当前的指令
        gotoxy(robot_command + 7, 64);
        cout << ">";
        // 暂停300毫秒
        Sleep(300);
        // 根据指令的类型，调用相应的函数
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
            // 如果指令是"jump"，则跳转到用户指定的位置
            i = robot_command;
        }
        else if (cm[robot_command] == "jumpifzero")
        {
            jumpifzero(op_map[robot_command]);
            // 如果指令是"jumpifzero"，则跳转到用户指定的位置
            i = robot_command;
        }
        // 如果传送带上没有物品，且当前处理的物品为空，且输出的目标为空，则结束执行
        if (cb[idx_cb] == 0x3f3f3f3f && current == 0x3f3f3f3f && op_aim[idx_op] == 0x3f3f3f3f)
            break;
        // 暂停300毫秒
        Sleep(300);
        // 清除">"，表示当前的指令执行结束
        gotoxy(i + 7, 64);
        cout << " ";
    }
}
void map() // 打印地图
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
void Welcome() // 欢迎界面
{
    // 打印游戏标题
    printf("\n           Human resource machine");
    // 提示用户按任意键开始游戏
    printf("\n\n            请按任意键开始游戏");
    int a;
    // 使用_getch函数获取用户的按键输入，_getch函数会等待用户的输入
    a = _getch();
    // 清屏，为游戏开始做准备
    system("cls");
}
void init() // 初始化函数，用于将数组cb、op_aim、ep和op的所有元素都设置为0x3f3f3f3f
{
    memset(cb, 0x3f, sizeof cb);
    memset(op_aim, 0x3f, sizeof op_aim);
    memset(ep, 0x3f, sizeof ep);
    memset(op, 0x3f, sizeof op);
}
int main()
{
    // 设置控制台的颜色属性，07表示背景色为黑色，前景色为白色
    system("color 07");
    /*
    颜色属性由两个十六进制数字指定 -- 第一个
    对应于背景，第二个对应于前景。每个数字
    可以为以下任何值:
    0 = 黑色       8 = 灰色
    1 = 蓝色       9 = 淡蓝色
    2 = 绿色       A = 淡绿色
    3 = 浅绿色     B = 淡浅绿色
    4 = 红色       C = 淡红色
    5 = 紫色       D = 淡紫色
    6 = 黄色       E = 淡黄色
    7 = 白色       F = 亮白色
    */
    // 显示欢迎信息
    Welcome();
    // 隐藏控制台的光标
    show_cursor(0);
    // 显示菜单
    menu();
    // 暂停一秒
    Sleep(1000);
    return 0;
}
