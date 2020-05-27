#include <stdio.h>
#include <time.h>
#define StringLength 150 //name や memoの格納可能な文字の量
#define MaxTasks 50 //格納可能な最大のtask数 (サイズ上限近くでの挙動テストはしてません：どうせバグる)
#define NoDeadline(x) x == 2099 //期限未定か否かの判定
#define MAXINT 2147483647

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
    char memo[StringLength];

    int dead_time;
    int dead_day;
    int dead_hour;
    int dead_min;
};

int main(int argc, char *argv[]){
    
    int i=0,j;
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

//現在時刻を取得し、期限までの残り時間を求める
    struct tm deadtime;
    time_t present = time(NULL), atDeadtime;

    for(i=0; i<Number_AllTask; i++){

        if( NoDeadline(task[i].yy) ){
            task[i].dead_time = MAXINT; //最大値
            //printf("%d\n",task[i].dead_time);
        }else{
            deadtime.tm_sec = 0;       /* 秒 */
            deadtime.tm_min = task[i].min;       /* 分 */
            deadtime.tm_hour = task[i].hr;      /* 時 */
            deadtime.tm_mday = task[i].dd;      /* 日 */
            deadtime.tm_mon = task[i].mm - 1;       /* 月 ( 1月＝0 ) */
            deadtime.tm_year = task[i].yy - 1900;    /* 西暦年 - 1900 */
            deadtime.tm_isdst = -1;    /* サマータイムフラグ */

            atDeadtime = mktime(&deadtime);
            task[i].dead_time = (int) (difftime(atDeadtime, present));
            task[i].dead_day = task[i].dead_time / 86400;
            task[i].dead_hour = task[i].dead_time % 86400 / 3600;
            task[i].dead_min = task[i].dead_time % 86400 % 3600 / 60;
            //printf("%d : ",task[i].dead_time);
            //printf("残り時間は：%d日 %d時間 %d分\n",task[i].dead_day,task[i].dead_hour,task[i].dead_min);
        }
    }

//pri でソート

    for(i=1; i<Number_AllTask; i++){
        j=i;
        while( j>0 && task[j-1].pri > task[j].pri ){
            struct taskSet tmp;
            tmp = task[j-1];
            task[j-1] = task[j];
            task[j] = tmp;
            j--;
        }
    }
    //for(i=0; i<Number_AllTask; i++) printf("%s  //  %d/%d/%d/%d/%d  //  %d/%d/%d  //  %s\n",task[i].name, task[i].yy, task[i].mm, task[i].dd, task[i].hr, task[i].min, task[i].rep, task[i].hard, task[i].pri, task[i].memo);

//priの値で分けた二つのデータについてdead_timeでソートし、taskデータを整理
    int priIndex = 0;
    while( task[priIndex].pri == 1 && task[priIndex + 1].pri == 1 ) priIndex++;
    priIndex++;

    for(i=1; i<priIndex; i++){
        j=i;
        while( j>0 && task[j-1].dead_time > task[j].dead_time ){
            struct taskSet tmp;
            tmp = task[j-1];
            task[j-1] = task[j];
            task[j] = tmp;
            j--;
        }
    }

    for(i=priIndex; i<Number_AllTask; i++){
        j=i;
        while( j>priIndex && task[j-1].dead_time > task[j].dead_time ){
            struct taskSet tmp;
            tmp = task[j-1];
            task[j-1] = task[j];
            task[j] = tmp;
            j--;
        }
    }
    //for(i=1; i<Number_AllTask; i++) printf("%s  //  %d/%d/%d/%d/%d  //  %d/%d/%d  //  %s\n",task[i].name, task[i].yy, task[i].mm, task[i].dd, task[i].hr, task[i].min, task[i].rep, task[i].hard, task[i].pri, task[i].memo);

//ソート結果をtaskファイルに書き込む

    fp = fopen(argv[1], "w");
    if(fp == NULL) {
        printf("Error: task file (~/ToDoBox/ToDo/task) cannot open\n");
        return -1;
    }

    fprintf(fp, "^^^^^\n");
    for(i=0; i<Number_AllTask; i++) fprintf(fp, "%s,%d,%d,%d,%d,%d,%d,%d,%d,%d,%s\n",task[i].name, task[i].yy, task[i].mm, task[i].dd, task[i].hr, task[i].min, task[i].rep, task[i].hard, task[i].pri, task[i].dead_time, task[i].memo);
    fclose(fp);
    
    return 0;
}