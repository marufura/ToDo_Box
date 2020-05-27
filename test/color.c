#include <stdio.h>

int main(void)
{
    /* 背景色の指定 */
    printf("\e[40m");     /* 背景色を黒に */
    printf("背景が黒\n");
    printf("\e[41m");     /* 背景色を赤に */
    printf("背景が赤\n");
    printf("\e[42m");     /* 背景色を緑に */
    printf("背景が緑\n");
    printf("\e[43m");     /* 背景色を黄色に */
    printf("背景が黄色\n");
    printf("\e[44m");     /* 背景色を青に */
    printf("背景が青\n");
    printf("\e[45m");     /* 背景色をマゼンタに */
    printf("背景がマゼンタ\n");
    printf("\e[46m");     /* 背景色をシアンに */
    printf("背景がシアン\n");
    printf("\e[47m");     /* 背景色を灰色に */
    printf("背景が灰色\n");
    printf("\e[49m");     /* 背景色をデフォルトに戻す */
    printf("背景色がデフォルト\n");

    printf("\n");

    /* 前景色の指定 */
    printf("\e[30m");     /* 前景色を黒に */
    printf("前景色が黒\n");
    printf("\e[31m");     /* 前景色を赤に */
    printf("前景色が赤\n");
    printf("\e[32m");     /* 前景色を緑に */
    printf("前景色が緑\n");
    printf("\e[33m");     /* 前景色を黄色に */
    printf("前景色が黄色\n");
    printf("\e[34m");     /* 前景色を青に */
    printf("前景色が青\n");
    printf("\e[35m");     /* 前景色をマゼンタに */
    printf("前景色がマゼンタ\n");
    printf("\e[36m");     /* 前景色をシアンに */
    printf("前景色がシアン\n");
    printf("\e[37m");     /* 前景色を白に */
    printf("前景色が白\n");
    printf("\e[39m");     /* 前景色をデフォルトに戻す */
    printf("前景色がデフォルト\n");

    printf("\n");

    printf("\e[4m");      /* 下線を付ける */
    printf("下線を付ける\n");
    printf("\e[1m");      /* 高輝度 */
    printf("高輝度\n");
    printf("\e[7m");      /* 反転（背景色と前景色の入れ替え） */
    printf("反転（背景色と前景色の入れ替え）\n");
    printf("\e[0m");      /* デフォルトに戻す */
    printf("デフォルトに戻す\n");

    return 0;
}