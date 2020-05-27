#include <stdio.h>
#include <time.h>

int main(void)
{
time_t tt1,tt0,tt2;
struct tm st1={0}, st0={0}, st2={0};

puts("日付入力 2013/1/12 形式");
scanf("%d%*c%d%*c%d", &(st1.tm_year), &(st1.tm_mon), &(st1.tm_mday));

st1.tm_year-=1900;
st1.tm_mon-=1;
tt1=mktime(&st1);
st1=*localtime(&tt1);

st0=st1;
st0.tm_mday--;
tt0=mktime(&st0);
st0=*localtime(&tt0);

st2=st1;
st2.tm_mday += 7;
tt2=mktime(&st2);
st2=*localtime(&tt2);

printf("該当日前日 %d年 %2d月 %2d日\n", st0.tm_year+1900, st0.tm_mon+1, st0.tm_mday);
printf("該当日当日 %d年 %2d月 %2d日\n", st1.tm_year+1900, st1.tm_mon+1, st1.tm_mday);
printf("1週間後 %d年 %2d月 %2d日\n", st2.tm_year+1900, st2.tm_mon+1, st2.tm_mday);

return 0;
}
