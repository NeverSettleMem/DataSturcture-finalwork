#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include <windows.h>
#include<string.h>

#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define MAXSIZE 100    //顺序表可能达到的最大长度

typedef struct {
    char id[8];
    char name[20];
    double price;
} BOOK;

typedef struct {
    BOOK *elem;  //存储空间的基地址
    int length;  //图书表中当前图书个数
} SqList;        //图书表的顺序存储结构 SqList

SqList Ll;

void menu();                       //主界面函数
int InitList(SqList *L);           //初始化空表;
void inputBook(SqList *L);         //录入图书信息
void printfBook(SqList L);         // 打印图书信息
void printfBooktemp(SqList L);         // 临时打印图书信息（修改方便）
void seekBook(SqList L);           //查找图书信息
void seekBookISBN(SqList L);       //按ISBN查询图书
void seekBookName(SqList L);       //查找书名图书信息
int seekBookSeat(SqList L);        //查找位置图书信息
int ListInsert(SqList *L);          // 插入图书信息
void listDeleta(SqList *L);         //删除图书信息
void revisePrice(SqList L);        //修改图书信息(价格)
void sortPrice(SqList L);          //排序图书价格
void color(short x);               //改变字体颜色
void backtrack();                  //返回

int main() {
    //程序入口
    menu();
    return 0;
}

void menu() {
    //主界面
    int l;
    system("color F5"); //设置CMD界面颜色
    printf("\t欢迎使用图书管理系统\t\n");
    printf("\t     0.初始化图书表 \t\n");
    printf("\t     1.录入图书信息 \t\n");
    printf("\t     2.打印图书信息 \t\n");
    printf("\t     3.查找图书信息 \t\n");
    printf("\t     4.插入图书信息 \t\n");
    printf("\t     5.删除图书信息\t\n");
    printf("\t     6.修改图书信息\t\n");
    printf("\t     7.排序图书价格   \n");
    printf("\t     8.统计图书数量   \n");
    printf("=================================\n");
    printf("请输入要执行的操作: ");
    scanf("%d", &l);
    switch (l) {
        case 0:
            system("cls");
            InitList(&Ll);
            if (Ll.elem) {
                color(2); //绿色字体
                printf("[tip]图书表初始化成功！\n");
                Sleep(2000);
                color(0xF); //白色字体
            }
            menu();
            break;
        case 1:
            system("cls");
            inputBook(&Ll);
            Sleep(2000);
            system("cls");
            menu();
            break;
        case 2:
            system("cls");
            printfBook(Ll);
            break;
        case 3:
            system("cls");
            seekBook(Ll);
            break;
        case 4:
            system("cls");
            ListInsert(&Ll);
            break;
        case 5:
            system("cls");
            listDeleta(&Ll);
            break;
        case 6:
            system("cls");
            revisePrice(Ll);
            break;
        case 7:
            system("cls");
            sortPrice(Ll);
            break;
        case 8:
            printf("\n当前馆内藏书量为：");
            color(2); //绿色字体
            printf("%d",Ll.length);
            Sleep(5000);
            color(0xF); //白色字体
            system("cls");
            menu();
            break;
        default:
            color(0xc); //红色字体
            printf("\n[ERROR]请重新输入有效数字!\n");
            Sleep(3000);
            color(0xF); //白色字体
            system("cls");
            menu();
            break;
    }
}

void color(short x) {
    //改变字体颜色
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);
}

int InitList(SqList *L) {
    //初始化空表
    L->elem = (BOOK *) malloc(sizeof(BOOK) * MAXSIZE);
    if (!(L->elem)) {
        printf("\n");
        printf("内存分配失败！\n");
        return OVERFLOW; // 返回错误码，而不是退出
    }
    L->length = 0;
    return OK;
}

void inputBook(SqList *L) {
    //录入图书信息
    int number;
    printf("请输入存储的数量：");
    scanf("%d", &number);
    getchar();  // 吸收之前留下的换行符
    int start = L->length;
    for (int i = start; i < (start + number); i++) {
        printf("请输入第%d本图书信息！\n", i + 1);
        printf("图书ISBN：");
        scanf("%s", L->elem[i].id);
        getchar();
        printf("图书名字：");
        fgets(L->elem[i].name, sizeof(L->elem[i].name), stdin);
        L->elem[i].name[strcspn(L->elem[i].name, "\n")] = '\0';  // 去掉换行符
        printf("图书价格：");
        scanf("%lf", &L->elem[i].price);
        getchar();
        L->length++;
        printf("\n");
    }
    color(2); //绿色字体
    printf("[tip]录入完成!\n");
    color(0xF); //白色字体
}

void printfBook(SqList L) {
    // 打印图书信息
    if (L.length == 0) {
        printf("没有图书可打印。\n");
        return;
    }
    printf("ISBN                书名                定价\n");
    
    color(2); //绿色字体
    for (int i = 0; i < L.length; i++) {
        printf("%-20s%-20s%.2f\n", L.elem[i].id, L.elem[i].name, L.elem[i].price);
    }
    color(0xF); //白色字体

    printf("\n\n是否返回主界面？(y/n)\n");
    getchar();
    if (getchar() == 'y') {
        system("cls");
        menu();
    }
}

void printfBooktemp(SqList L) {
    // 打印图书信息
    if (L.length == 0) {
        printf("没有图书可打印。\n");
        return;
    }
    printf("ISBN                书名                定价\n");
    
    color(2); //绿色字体
    for (int i = 0; i < L.length; i++) {
        printf("%-20s%-20s%.2f\n", L.elem[i].id, L.elem[i].name, L.elem[i].price);
    }
    color(0xF); //白色字体
}

void seekBook(SqList L) {
    //查找图书信息
    int l;
    printf("\t欢迎使用图书查询系统\t\n");
    printf("\t   1.按ISBN查询图书 \t\n");
    printf("\t   2.按书名查询图书 \t\n");
    printf("\t   3.按位置查询图书\t\n");
    printf("\t   4.返回  \n");
    printf("\t=================================\n");
    printf("\t请输入要执行的操作: ");
    scanf("%d", &l);
    switch (l) {
        case 1:
            system("cls");
            seekBookISBN(L);
            break;
        case 2:
            system("cls");
            seekBookName(L);
            break;
        case 3:
            system("cls");
            seekBookSeat(L);
            break;
        case 4:
            system("cls");
            menu();
            break;
        default:
            color(0xc); //红色字体
            printf("\n[ERROR]请重新输入有效数字!\n");
            Sleep(3000);
            color(0xF); //白色字体
            system("cls");
            seekBook(L);
            break;
    }
}

void backtrack() {
    printf("\n\n是否返回主界面？(y/n): ");
    char ch = getchar();
    while (getchar() != '\n'); // 清理输入缓冲区
    if (ch == 'y' || ch == 'Y') {
        system("cls");
        menu();
    } else {
        return;
    }
}

void seekBookISBN(SqList L) {
    //按ISBN查询图书
    char id_1[8];
    printf("请输入需要查询书籍的ISBN：");
    scanf("%s", id_1);
    while (getchar()!= '\n');
    for (int i = 0; i < L.length; i++) {
        if (strcmp(L.elem[i].id, id_1) == 0) {
            printf("\nISBN为%s的书籍信息如下：\n", id_1);
            color(2); //绿色字体
            printf("ISBN:%-20s书名：%-20s价格：%.2lf!\n", L.elem[i].id, L.elem[i].name, L.elem[i].price);
            color(0xF); //白色字体
            backtrack();
            return;
        }
    }
    color(0xc);  //红色字体
    printf("\n[ERROR]无相关书籍信息！(3秒后将自动返回主界面)\n");
    color(0xF); //白色字体
    Sleep(3000);
        system("cls");
        menu();
}

void seekBookName(SqList L) {
    //查找书名图书信息
    char name_1[20];
    printf("请输入需要查询书籍的书名：");
    scanf("%s", name_1);
    while (getchar()!= '\n');
    for (int i = 0; i < L.length; i++) {
        if (strcmp(L.elem[i].name, name_1) == 0) {
            printf("\n书名为%s的书籍信息如下：\n", name_1);
            color(2); //绿色字体
            printf("ISBN:%-20s书名：%-20s价格：%.2lf!\n", L.elem[i].id, L.elem[i].name, L.elem[i].price);
            color(0xF); //白色字体
            backtrack();
            return;
        }
    }
    color(0xc);  //红色字体
    printf("\n[ERROR]无相关书籍信息！(3秒后将自动返回主界面)\n");
    color(0xF); //白色字体
    Sleep(3000);
        system("cls");
        menu();
}

int seekBookSeat(SqList L) {
    // 查找位置图书信息
    int seat;
    printf("请输入需要查询书籍的位置：");
    scanf("%d", &seat);
    while (getchar()!= '\n');
    if (seat < 1 || seat > L.length) {
        color(0xc);  //红色字体
        printf("\n[ERROR]输入的位置无效！(3秒后将自动返回主界面)\n");
        color(0xF);  //白色字体
        Sleep(3000);
            system("cls");
            menu();
        return ERROR;
    } else {
        printf("位置为%d的书籍信息如下：\n", seat);
        color(2);  //绿色字体
        printf("ISBN:%-20s书名：%-20s价格：%.2lf!\n", L.elem[seat - 1].id, L.elem[seat - 1].name, L.elem[seat - 1].price);
        color(0xF);  //白色字体
        backtrack();
        return OK;
    }
}

int ListInsert(SqList *L) {
    //插入图书信息
    int insertSeat;
    printf("当前书籍列表如下：\n");
    printfBooktemp(Ll);
    printf("\n请输入插入图书的位置：");
    scanf("%d", &insertSeat);
    while(getchar() != '\n'); // 清理输入缓冲区
    if ((insertSeat < 1) || (insertSeat > L->length + 1)) {
        color(0xc);  //红色字体
        printf("\n[ERROR]插入位置不合法！(3秒后将自动返回主界面)\n");
        color(0xF);  //白色字体
        Sleep(3000);
            system("cls");
            menu();
        return ERROR;
    }
    for (int i = L->length - 1; i >= insertSeat - 1; i--) {
        L->elem[i + 1] = L->elem[i];
    }
    printf("请输入插入图书的信息：\n");
    printf("图书ISBN：");
    scanf("%s", L->elem[insertSeat - 1].id);
    while(getchar() != '\n');
    printf("图书名称：");
    fgets(L->elem[insertSeat - 1].name, sizeof(L->elem[insertSeat - 1].name), stdin);
    L->elem[insertSeat - 1].name[strcspn(L->elem[insertSeat - 1].name, "\n")] = '\0'; // 去掉换行符
    printf("图书价格：");
    scanf("%lf", &L->elem[insertSeat - 1].price);
    L->length++;
    color(2);  //绿色字体
    printf("\n[tip]图书信息插入成功！\n");
    color(0xF);  //白色字体
    Sleep(3000);
            system("cls");
            menu();
    return OK;
    
}

void listDeleta(SqList *L) {
    // 删除图书信息
    int deleteSeat;
    printf("当前书籍列表如下：\n");
    printfBooktemp(Ll);
    printf("\n请输入需要删除的书籍位置：");
    scanf("%d", &deleteSeat);
    if (deleteSeat < 1 || deleteSeat > L->length) {
        color(0xc);  //红色字体
        printf("\n[ERROR]输入的位置无效！(3秒后将自动返回主界面)\n");
        color(0xF);  //白色字体
        Sleep(3000);
            system("cls");
            menu();
        return;
    }
    for (int i = deleteSeat - 1; i < L->length - 1; i++) {
        L->elem[i] = L->elem[i + 1];
    }
    L->length--;
    color(2);  //绿色字体
    printf("\n[tip]书籍信息删除成功！\n");
    color(0xF);  //白色字体
    Sleep(3000);
            system("cls");
            menu();
}

void revisePrice(SqList L) {
    // 修改图书信息(价格)
    int seat;
    printf("当前书籍列表如下：\n");
    printfBooktemp(Ll);
    printf("\n请输入修改价格的图书位置：");
    scanf("%d", &seat);
    if (seat < 1 || seat > L.length) {
        color(0xc);  //红色字体
        printf("\n[ERROR]输入的位置无效！(3秒后将自动返回主界面)\n");
        color(0xF);  //白色字体
        Sleep(3000);
            system("cls");
            menu();
        return;
    }
    printf("当前图书价格为：%.2f\n", L.elem[seat - 1].price);
    printf("请输入新的价格：");
    scanf("%lf", &L.elem[seat - 1].price);
    color(2);  //绿色字体
    printf("\n[tip]价格修改成功！\n");
    color(0xF);  //白色字体
    Sleep(3000);
            system("cls");
            menu();
}

void sortPrice(SqList L) {
    // 排序图书价格
    if (L.length == 0) {
        printf("\n 没有图书可以排序。(3秒后将自动返回主界面)\n");
        Sleep(3000);
            system("cls");
            menu();
        return;
    }
    BOOK t;
    for (int i = 0; i < L.length; i++) {
        for (int j = 0; j < L.length - i - 1; j++) {
            if (L.elem[j].price < L.elem[j + 1].price) {
                t = L.elem[j];
                L.elem[j] = L.elem[j + 1];
                L.elem[j + 1] = t;
            }
        }
    }
    printf("排序后书籍信息如下（降序）：\n");
    printfBook(L);
    backtrack();
}
