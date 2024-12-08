#include <stdio.h>

#define M 1.0 /* 質点の質量 */
#define K 20.0 /* バネ定数 */
#define H 0.01 /* 刻み幅 */
#define TIME 10 /* 総シミュレーション時間 [s] */

double func_dy1 (double y1, double y2) {
    return y2; /* 式を実装 */
}
double func_dy2 (double y1, double y2) {
    return -(K/M)*y1; /* 式を実装 */
}

/* メインルーチン */
int main()
{
    /* 状態変数の定義&初期化 */
    double y1 = 0.8; /* 質点の位置 y1 */
    double y2 = 0.0; /* 質点の速度 y2 */
    double dy1; /* 状態変数の変化量 dy1/dt に相当 */
    double dy2; /* 状態変数の変化量 dy2/dt に相当 */
    int t=0; /* 経過時間に相当 */

    FILE *fp; /* 出力用のcsv形式のファイル*/

    fp = fopen("euler.csv","w");

    fprintf(fp," ,位置,速度\n");

    /* シミュレーション */
    for(t=0; t<=(int)(TIME/H); t++) {
        /* 1. まず,現在の位置 (y1),速度 (y2)に対する変化量 (dy1/dt, dy2/dt)を求める */
        dy1 = func_dy1(y1, y2);
        dy2 = func_dy2(y1, y2);

        /* 2. 次に,y1, y2 を刻み幅 H だけ更新する */
        y1 = y1 + dy1*H;
        y2 = y2 + dy2*H;

        /* 3. 時刻 (t)と位置 (y1), 速度 (y2)を出力する*/
        /* 予め設定した"euler.csv"に保存する. */
        fprintf(fp,"%f,%f,%f\n",(double)t*H,y1,y2);
    }
    fclose(fp);
    return 0;
}
