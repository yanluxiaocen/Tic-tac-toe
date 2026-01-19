#include <stdio.h>
#include<stdlib.h>
#include <windows.h>
#include<string.h>
#define MAXFILM 40
#define MAXTITL 30
#define MAXAUTL 30
#define SIZE sizeof(struct film)

struct film {
    char name[MAXTITL];
    char author[MAXAUTL];
    float score;
};

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// 智能加载动画函数
void showLoading(char* message) {
    char spinner[] = { '|', '/', '-', '\\' };

    if (message != NULL) {
        setColor(11);  // 青色
        printf("%s\n\n", message);
    }

    for (int i = 0; i <= 100; i++) {
        printf("\r");  // 回到行首

        // 智能变色：根据进度改变颜色
        int percent = i * 1;
        if (percent < 30) {
            setColor(12);  // 红色
        }
        else if (percent < 70) {
            setColor(14);  // 黄色
        }
        else {
            setColor(10);  // 绿色
        }

        // 旋转图标
        printf("[%c] ", spinner[i % 4]);

        // 进度条
        printf("[");
        for (int j = 0; j < 100; j++) {
            if (j < i) {
                printf("█");
            }
            else {
                printf(" ");
            }
        }
        printf("] ");

        // 百分比
        printf("%d%%", percent);

        fflush(stdout);  // 立即输出
        Sleep(10);      // 暂停0.1秒
    }

    setColor(7);  // 恢复默认白色
    printf("\n\n");
}

void qipan(char qige[3][3]) {

    setColor(11);
    printf("\n");
    for (int i = 0; i < 3; i++)
    {
        printf("  %c | %c | %c  \n", qige[i][0], qige[i][1], qige[i][2]);
        if (i < 2)
        {
            printf(" ---|---|--- \n");
        }
    }
    printf("\n");
}

char check_win(char qige[3][3]) {
    for (int i = 0; i < 3; i++)
    {
        if (qige[i][0] != ' ' && qige[i][0] == qige[i][1] && qige[i][1] == qige[i][2])
            return qige[i][0];
        if (qige[0][i] != ' ' && qige[0][i] == qige[1][i] && qige[1][i] == qige[2][i])
            return qige[0][i];
    }
    if (qige[0][0] != ' ' && qige[0][0] == qige[1][1] && qige[1][1] == qige[2][2])
        return qige[0][0];
    if (qige[2][0] != ' ' && qige[2][0] == qige[1][1] && qige[1][1] == qige[0][2])
        return qige[2][0];
    return ' ';
}

int main() {
    showLoading("井字棋启动中...");

    setColor(10);  // 绿色
    printf("加载完成！按任意键开始游戏...\n");
    setColor(13);   // 白色

    getchar();

    int lie, hang;
    char player = 'X';
    char qige[3][3] = {
        {' ',' ',' ' },
        {' ',' ',' ' },
        {' ',' ',' ' }
    };


    printf("诶嘿~终于有人来找人家下棋啦！不过你可要做好输的准备哦~\n");
    Sleep(1000);
    printf("要是中途想逃跑的话...输入0 0就行啦，不会说你胆小的~才怪！\n");
    Sleep(1000);

    int flag = 1;

    while (1) {
        setColor(11);
        qipan(qige);
        setColor(13);

        if (flag) {
            Sleep(1000);
            flag = 0;
        }

        printf("该%c了~:", player);
        setColor(6);
        scanf("%d %d", &lie, &hang);
        while (getchar() != '\n');

        if (lie == 0 && hang == 0) {
            printf("诶~这就认输了吗？人家还没玩够呢~胆小鬼~\n\n");
            break;
        }

        lie--, hang--;

        if (lie < 0 || lie > 2 || hang < 0 || hang > 2 || qige[lie][hang] != ' ') {
            printf("啊咧咧~连个坐标都输不对，不愧是杂鱼呢~再给你一次机会好啦~\n");
            continue;
        }

        qige[lie][hang] = player;

        char winner = check_win(qige);
        if (winner != ' ')
        {
            qipan(qige);
            setColor(13);
            printf("哼~没想到你这只杂鱼还有点本事嘛~赢家是 % c，姑且祝贺你一下好了\n\n", winner);
            setColor(11);
            break;
        }

        int check_ping = 1;
        for (int l = 0; l < 3; l++) {
            for (int h = 0; h < 3; h++) {
                if (qige[l][h] == ' ') {
                    check_ping = 0;
                }
            }
        }
        if (check_ping) {
            qipan(qige);
            setColor(13);
            printf("呜...居然打成平手了呢~看来你们两个都是半斤八两的小杂鱼呀~\n");
            setColor(11);
            break;
        }

        player = (player == 'X') ? 'O' : 'X';
    }

    getchar();
    return 0;
}