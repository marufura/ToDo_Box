#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define StringLength 61 //name や memoの格納可能な文字の量 warning:#54あたり
#define MaxTasks 50 //格納可能な最大のtask数 (サイズ上限近くでの挙動テストはしてません：どうせバグる)
#define NoDeadline(x) x == 2099 //期限未定か否かの判定

#define DeadLine_soon 3
#define DeadLine_aboutTime 7

struct taskSet // taskの持つデータ classみたいなもの <-ならJavaで書け
{
    char name[StringLength];
    int yy;
    int mm;
    int dd;
    int hr;
    int min;
    int rep;
    int hard;
    int pri;
    int dead_time;
    char memo[StringLength];
};

int main(int argc, char *argv[]){
    
    int i=0;
    struct taskSet task[MaxTasks];

//Taskファイルを読み込む
    FILE *fp;
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("Error: task file (~/ToDoBox/ToDo/task) cannot open\n");
        return -1;
    }
    fscanf(fp, "%*5c"); // ^^^^^ を除外
    while( ( fscanf(fp, " %[^,],%d,%d,%d,%d,%d,%d,%d,%d,%d,%s",task[i].name, &task[i].yy, &task[i].mm, &task[i].dd, &task[i].hr, &task[i].min, &task[i].rep, &task[i].hard, &task[i].pri, &task[i].dead_time, task[i].memo )) != EOF){
        // printf("%s  //  %d/%d/%d/%d/%d  //  %d/%d/%d  //  %s\n",task[i].name, task[i].yy, task[i].mm, task[i].dd, task[i].hr, task[i].min, task[i].rep, task[i].hard, task[i].pri, task[i].memo);
        i++;
    }
    fclose(fp);
    int Number_AllTask = i; //全Taskの数

    //printf("\n\n\n");

    int allFlag = atoi(argv[2]);
    int col = atoi(argv[3]);
    int line = atoi(argv[4]);

    printf("\e[4m");      /* 下線を付ける */
    printf("    ToDo Box                                                                    \n"); // 1 7
    printf("\e[0m");      /* デフォルトに戻す */
    printf("\n");

    printf("  1.必ずやらなければいけないこと\n");
    int task_number = 0,flag = 0;
    int dead_day, dead_hour, dead_min;

    for(task_number=0; task_number<Number_AllTask; task_number++){

        if(task[task_number].pri == 2 && flag == 0){
            flag = 1;
            printf("  2.忙しかったら後回し\n");
        }

        printf("    [%2d] ",task_number + 1);
 
        if(task[task_number].hard == 2){
            printf("\e[32m");
            printf(" %-30s\n        所要時間        : ~1時間\n",task[task_number].name);
        }else if(task[task_number].hard == 3){
            printf("\e[34m");
            printf(" %-30s\n        所要時間        : ~5時間\n",task[task_number].name);
        }else if(task[task_number].hard == 4){
            printf("\e[35m");
            printf(" %-30s\n        所要時間        : 5時間~\n",task[task_number].name);
        }else{
            printf(" %-30s\n        所要時間        : 不明\n",task[task_number].name);
        }
        printf("\e[0m");      /* デフォルトに戻す */

        if(NoDeadline(task[task_number].yy)){
            printf("        期限: なし\n");
        }else{
            dead_day = task[task_number].dead_time / 86400;
            dead_hour = task[task_number].dead_time % 86400 /3600;
            dead_min = task[task_number].dead_time % 86400 % 3600 / 60;
            
            if(task[task_number].mm < 10){
                printf("        完了期限        :  %d月%2d日%2d時%2d分まで      --",task[task_number].mm,task[task_number].dd,task[task_number].hr,task[task_number].min);
            }else{
                printf("        完了期限        : %2d月%2d日%2d時%2d分まで      --",task[task_number].mm,task[task_number].dd,task[task_number].hr,task[task_number].min);
            }

            if(dead_min < 0){
                printf("\e[37;4m");
                printf(" 期限オーバー\n");
                printf("\e[0m");
            }else if(dead_day <= DeadLine_soon){
                printf("\e[31m");
                printf(" 残り: %d日%2d時間%2d分\n",dead_day,dead_hour,dead_min);
                printf("\e[0m");
            }else if(dead_day <= DeadLine_aboutTime){
                printf("\e[33m");
                printf(" 残り: %d日%2d時間%2d分\n",dead_day,dead_hour,dead_min);
                printf("\e[0m");
            }else{
                printf("\e[36m");
                printf(" 残り: %d日%2d時間%2d分\n",dead_day,dead_hour,dead_min);
                printf("\e[0m");
            }

        }
        printf("\e[0m");      /* デフォルトに戻す */

        if(task_number == Number_AllTask -1){
            printf("\e[4m");      /* 下線を付ける */
            printf("                                                                                \n"); // 1 7
            printf("\e[0m");      /* デフォルトに戻す */
        }else{
            printf("\n");
        }

    }

    printf("\e[0m");      /* デフォルトに戻す */
    printf("\n");

    printf("%s %s %s\n",argv[2],argv[3],argv[4]);
    printf("%d %d %d\n",allFlag,col,line);
    
    return 0;
}