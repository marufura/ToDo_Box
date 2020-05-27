#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define StringLength 150 //name や memoの格納可能な文字の量 warning:#54あたり
#define MaxTasks 50 //格納可能な最大のtask数 (サイズ上限近くでの挙動テストはしてません：どうせバグる)
#define NoDeadline(x) x == 2099 //期限未定か否かの判定

#define DeadLine_soon 3 // あとN日以下の課題を表示
#define DeadLine_aboutTime 7
#define Correction 40 //値が大きいほど左に (terminalのウィンドウサイズが大きい時適用)

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
    
    int i=0,separationIndex=0,flag=0;
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
        if(task[i].pri == 2 && flag == 0){
            flag++ ;
            separationIndex = i;
            //printf("%d\n",separationIndex);
        }
        // printf("%s  //  %d/%d/%d/%d/%d  //  %d/%d/%d  //  %s\n",task[i].name, task[i].yy, task[i].mm, task[i].dd, task[i].hr, task[i].min, task[i].rep, task[i].hard, task[i].pri, task[i].memo);
        i++;
    }
    fclose(fp);
    int Number_AllTask = i; //全Taskの数

    //printf("\n\n\n");

    int allFlag = atoi(argv[2]);
    int col = atoi(argv[3]);
    int line = atoi(argv[4]);

    int display1, display2,displayRest;
    line -= (line % 4);
    if(line < 28){
        line = line < 16 ? 16 : line;
        display1 = line/4 -3;
        display2 = 1;
    }else{
        display2 = (line - 8) / 20;
        display1 = line/4 - display2 - 2;
    }
    displayRest = display2;

    printf("\e[4m");      /* 下線を付ける */
    printf("    ToDo Box"); // 1 7
    for(i=0; i < col-12 ; i++) printf(" ");
    printf("\e[0m");      /* デフォルトに戻す */
    printf("\n");

    if(Number_AllTask == 0){
        printf("\n");
        for(i=0; i < col/2 - Correction; i++) printf(" ");
        printf("                        現在やるべきことはありません!!\n");
        printf("\e[0m");      /* デフォルトに戻す */
        printf("\e[4m");      /* 下線を付ける */
        for(i=0; i < col ; i++) printf(" ");
        printf("\e[0m");      /* デフォルトに戻す */
        printf("\n");
        exit(0);
    }

    for(i=0; i < col/2 - Correction - 5; i++) printf(" ");
    printf("  1.必ずやらなければいけないこと\n");
    int task_number = 0;
    int dead_day, dead_hour, dead_min;
    int skipFlag1=0;

    flag = 0;
    for(task_number=0; task_number<Number_AllTask; task_number++){

        if(task_number < separationIndex){
            if(task_number >= display1 && allFlag == 0){
                skipFlag1 = 1; continue;
            }
            printf("\n");
        }else if(flag == 0){
            flag = 1;
            if(skipFlag1){
                for(i=0; i < col/2 ; i++) printf(" ");
                printf("...\n");
            }else{
                displayRest += (display1 - task_number);
            }
            printf("\n");
            for(i=0; i < col/2 - Correction  - 5; i++) printf(" ");
            printf("  2.忙しかったら後回し\n");
            printf("\n");
        }else if(flag == 1){
            if(task_number >= displayRest + separationIndex && allFlag == 0){
                for(i=0; i < col/2 ; i++) printf(" ");
                printf("...\n");
                break;
            }
            printf("\n");
        }

        for(i=0; i < col/2- Correction; i++) printf(" ");
        printf("    [%2d] ",task_number + 1);

        char input[] = "NOINPUT";
        if(task[task_number].hard == 2){
            printf("\e[32m");
            printf(" %s",task[task_number].name);
            if(strcmp(task[task_number].memo,input) != 0){ printf("  (%s)\n",task[task_number].memo); }else{ printf("\n"); }
            for(i=0; i < col/2- Correction; i++) printf(" ");
            printf("        所要時間        :  ~1時間\n");
        }else if(task[task_number].hard == 3){
            printf("\e[34m");
            printf(" %s",task[task_number].name);
            if(strcmp(task[task_number].memo,input) != 0){ printf("  (%s)\n",task[task_number].memo); }else{ printf("\n"); }
            for(i=0; i < col/2- Correction; i++) printf(" ");
            printf("        所要時間        :  ~5時間\n");
        }else if(task[task_number].hard == 4){
            printf("\e[35m");
            printf(" %s",task[task_number].name);
            if(strcmp(task[task_number].memo,input) != 0){ printf("  (%s)\n",task[task_number].memo); }else{ printf("\n"); }
            for(i=0; i < col/2- Correction; i++) printf(" ");
            printf("        所要時間        :  5時間~\n");
        }else{
            printf(" %s",task[task_number].name);
            if(strcmp(task[task_number].memo,input) != 0){ printf("  (%s)\n",task[task_number].memo); }else{ printf("\n"); }
            for(i=0; i < col/2- Correction; i++) printf(" ");
            printf("        所要時間        :  不明\n");
        }
        printf("\e[0m");      /* デフォルトに戻す */

        if(NoDeadline(task[task_number].yy)){
            for(i=0; i < col/2- Correction; i++) printf(" ");
            printf("        期限: なし\n");
        }else{
            dead_day = task[task_number].dead_time / 86400;
            dead_hour = task[task_number].dead_time % 86400 /3600;
            dead_min = task[task_number].dead_time % 86400 % 3600 / 60;
            
            if(task[task_number].mm < 10){
                for(i=0; i < col/2- Correction; i++) printf(" ");
                printf("        完了期限        :  %d月%2d日%2d時%2d分まで      --",task[task_number].mm,task[task_number].dd,task[task_number].hr,task[task_number].min);
            }else{
                for(i=0; i < col/2- Correction; i++) printf(" ");
                printf("        完了期限        : %2d月%2d日%2d時%2d分まで      --",task[task_number].mm,task[task_number].dd,task[task_number].hr,task[task_number].min);
            }

            if(dead_min < 0){
                printf("\e[37;4m");
                printf(" 期限オーバー\n");
                printf("\e[0m");
            }else if(dead_day <= DeadLine_soon - 1){
                printf("\e[31m");
                printf(" 残り: %2d日%2d時間%2d分\n",dead_day,dead_hour,dead_min);
                printf("\e[0m");
            }else if(dead_day <= DeadLine_aboutTime - 1){
                printf("\e[33m");
                printf(" 残り: %2d日%2d時間%2d分\n",dead_day,dead_hour,dead_min);
                printf("\e[0m");
            }else{
                printf("\e[36m");
                printf(" 残り: %2d日%2d時間%2d分\n",dead_day,dead_hour,dead_min);
                printf("\e[0m");
            }

        }
        printf("\e[0m");      /* デフォルトに戻す */

    }

    printf("\e[0m");      /* デフォルトに戻す */
    printf("\e[4m");      /* 下線を付ける */
    for(i=0; i < col ; i++) printf(" ");
    printf("\e[0m");      /* デフォルトに戻す */
    printf("\n");

    //printf("%s %s %s\n",argv[2],argv[3],argv[4]);
    //printf("%d %d %d\n",allFlag,col,line);
    //printf ("%d %d %d\n", line, display1, display2);
    //printf("%d\n",Number_AllTask);
    
    return 0;
}