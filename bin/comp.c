#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define StringLength 150 //name や memoの格納可能な文字の量
#define MaxTasks 50 //格納可能な最大のtask数 (サイズ上限近くでの挙動テストはしてません：どうせバグる)
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
        exit(1);
    }
    fscanf(fp, "%*5c"); // ^^^^^ を除外
    // fscanfの最初の空白は大事 (最初に改行文字を読むことを防ぐ)
    while( ( fscanf(fp, " %[^,],%d,%d,%d,%d,%d,%d,%d,%d,%d,%s",task[i].name, &task[i].yy, &task[i].mm, &task[i].dd, &task[i].hr, &task[i].min, &task[i].rep, &task[i].hard, &task[i].pri, &task[i].dead_time, task[i].memo )) != EOF){
        //printf("input : %s  //  %d/%d/%d/%d/%d  //  %d/%d/%d  //  %d  //  %s\n",task[i].name, task[i].yy, task[i].mm, task[i].dd, task[i].hr, task[i].min, task[i].rep, task[i].hard, task[i].pri, task[i].dead_time, task[i].memo);
        i++;
    }
    fclose(fp);
    int Number_AllTask = i; //全Taskの数

// 変更する行を見つける。入力の種類で分類:name or line
    int charFlag = 0;
    char fileName[StringLength] = "" ;
    int fileLine = MAXINT;

    for(i=0 ; i < strlen(argv[2]) ; i++){
        if( 47 < argv[2][i]  && argv[2][i] < 58 ){
            continue;
        }else{
            charFlag = 1; //true
            break;
        }
    }

    if( charFlag ){
        strcpy(fileName,argv[2]);
        //printf("string : %s",fileName);
        for(i=0; i<Number_AllTask; i++){
            if(strcmp(fileName, task[i].name) == 0){
                //printf("   match completed task : %s\n",task[i].name);
                fileLine = i;
                break;
            }
        }

        if(fileLine == MAXINT){
            printf("        No name error\n");
            exit(1);
        }
        //printf("int : %d\n",fileLine);
    }else{
        fileLine = atoi(argv[2]) - 1;
        //printf("fileline : %d\n",fileLine);
        if(fileLine > Number_AllTask){
            printf("        No exist error : Task number \n");
            exit(1);
        }
    }

    int EraseFlag = 0, isYes;

    time_t Later;
    struct tm nowTime = {0}, LaterTime;

    nowTime.tm_year = task[fileLine].yy - 1900;
    nowTime.tm_mon = task[fileLine].mm - 1;
    nowTime.tm_mday = task[fileLine].dd;
    nowTime.tm_hour = task[fileLine].hr;
    nowTime.tm_min = task[fileLine].min;
    nowTime.tm_sec = 0;
    nowTime.tm_isdst = 0;
    LaterTime = nowTime;
    //printf("input: %d/%d/%d/%d/%d : %d\n",nowTime.tm_year +1900,nowTime.tm_mon +1,nowTime.tm_mday,nowTime.tm_hour,nowTime.tm_min,nowTime.tm_sec);

    switch (task[fileLine].rep)
    {
    case 1:
        printf("    この Task ( %s ) は完了しました。お疲れ様です。\n",task[fileLine].name);
        EraseFlag = 1;
        break;
    case 2:
        printf("この Task ( %s ) は毎日繰り返されるようです。繰り返しますか？ [y/n] -> ",task[fileLine].name);
        isYes = getchar();
        if(isYes == 121){//y
            LaterTime.tm_mday++ ;
            Later = mktime(&LaterTime);
            LaterTime = *localtime(&Later);
            printf("    (再設定しました): %s  -> 新しい期限: %d/%2d/%2d/%2d/%2d\n",task[fileLine].name, LaterTime.tm_year+1900, LaterTime.tm_mon+1, LaterTime.tm_mday, task[fileLine].hr, task[fileLine].min);
        }else if(isYes == 110){//n
            printf("    この Task ( %s ) は完了しました。お疲れ様です。\n",task[fileLine].name);
            EraseFlag = 1;
        }else{
            printf("Error: valid input is [y] or [n] ( case : 2 )\n");
            exit(1);
        }
        break;
    case 3:
        printf("この Task ( %s ) は毎週繰り返されるようです。繰り返しますか？ [y/n] -> ",task[fileLine].name);
        isYes = getchar();
        if(isYes == 121){//y
            LaterTime.tm_mday += 7 ;
            Later = mktime(&LaterTime);
            LaterTime = *localtime(&Later);
            printf("    (再設定しました): %s  -> 新しい期限: %d/%2d/%2d/%2d/%2d\n",task[fileLine].name, LaterTime.tm_year+1900, LaterTime.tm_mon+1, LaterTime.tm_mday, task[fileLine].hr, task[fileLine].min);
        }else if(isYes == 110){//n
            printf("    この Task ( %s ) は完了しました。お疲れ様です。\n",task[fileLine].name);
            EraseFlag = 1;
        }else{
            printf("Error: valid input is [y] or [n] ( case : 3 )\n");
            exit(1);
        }
        break;
    case 4:
        printf("この Task ( %s ) は毎月繰り返されるようです。繰り返しますか？ [y/n] -> ",task[fileLine].name);
        isYes = getchar();
        if(isYes == 121){//y
            LaterTime.tm_mon++ ;
            Later = mktime(&LaterTime);
            LaterTime = *localtime(&Later);
            printf("    (再設定しました): %s  -> 新しい期限: %d/%2d/%2d/%2d/%2d\n",task[fileLine].name, LaterTime.tm_year+1900, LaterTime.tm_mon+1, LaterTime.tm_mday, task[fileLine].hr, task[fileLine].min);
        }else if(isYes == 110){//n
            printf("    この Task ( %s ) は完了しました。お疲れ様です。\n",task[fileLine].name);
            EraseFlag = 1;
        }else{
            printf("Error: valid input is [y] or [n] ( case : 4 )\n");
            exit(1);
        }
        break;
    default:
        printf("Error: valid input is [y] or [n] ( case : default )\n");
        exit(1);
        break;
    }
    

//結果をtaskファイルに書き込む

    fp = fopen(argv[1], "w");
    if(fp == NULL) {
        printf("Error: task file (~/ToDoBox/ToDo/task) cannot open\n");
        return -1;
    }

    fprintf(fp, "^^^^^\n");
    for(i=0; i<Number_AllTask; i++){
        if(i == fileLine && EraseFlag == 1){
            continue;
        }else if(i == fileLine && EraseFlag == 0){
            fprintf(fp, "%s,%d,%d,%d,%d,%d,%d,%d,%d,%d,%s\n",task[i].name, LaterTime.tm_year+1900, LaterTime.tm_mon+1, LaterTime.tm_mday, task[i].hr, task[i].min, task[i].rep, task[i].hard, task[i].pri, task[i].dead_time, task[i].memo);
            continue;
        }
        fprintf(fp, "%s,%d,%d,%d,%d,%d,%d,%d,%d,%d,%s\n",task[i].name, task[i].yy, task[i].mm, task[i].dd, task[i].hr, task[i].min, task[i].rep, task[i].hard, task[i].pri, task[i].dead_time, task[i].memo);
    }
    fclose(fp);

    return 0;
}