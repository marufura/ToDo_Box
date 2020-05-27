#include<stdio.h>
#include<time.h>

int main(void)
{

time_t t = time(NULL), t_7;
struct tm local, tt_7;

local = *localtime(&t);
printf("%04d/", local.tm_year + 1900);
printf("%02d/", local.tm_mon + 1);
printf("%02d", local.tm_mday);

printf(" ");

printf("%02d:", local.tm_hour);
printf("%02d:", local.tm_min);
printf("%02d\n", local.tm_sec);

char * const wdays[] = { "日", "月", "火", "水", "木", "金", "土" };
printf("今日は%s曜日\n", wdays[local.tm_wday]);

printf("7日後：");
tt_7 = local;
tt_7.tm_mday += 7;
t_7 = mktime(&local);
tt_7= *localtime(&t_7);
printf("%d年 %2d月 %2d日\n", tt_7.tm_year+1900, tt_7.tm_mon+1, tt_7.tm_mday);

return 0;
}