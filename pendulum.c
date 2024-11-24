#include <stdio.h>
#include <math.h>

#define L 1.29 /* 振り子の長さ */
#define M 1.0 /* 振り子の質量 */
#define G 9.8 /* 重力加速度 */
#define H 0.01 /* 刻み幅 */
#define B 0.6 /* 粘性摩擦係数 */
#define TIME 20 /* 総シミュレーション時間 [s] */

double func_drad (double rad, double speed) {
    return speed; /* 式を実装 */
}
double func_dspeed (double rad, double speed) {
    return -(G/L)*sin(rad)-(B/(M*L*L))*speed; /* 式を実装 */
}

/* メインルーチン */
int main()
{
    /* 状態変数の定義&初期化 */
    double rad = 1.0; /* 質点の位置 rad */
    double speed = 0.0; /* 質点の速度 speed */
    double drad_k1; /* 状態変数の変化量 drad/dt に相当 */
    double drad_k2; /* k1の中点での状態変数の変化量 d(rad+H/2)/dt に相当 */
    double drad_k3; /* k2の中点での状態変数の変化量 d(rad+H/2)/dt に相当 */
    double drad_k4; /* 状態変数の変化量 d(rad+H)/dt に相当 */
    double dspeed_k1; /* 状態変数の変化量 dspeed/dt に相当 */
    double dspeed_k2; /* k1の中点での状態変数の変化量 d(speed+H/2)/dt に相当 */
    double dspeed_k3; /* k2の中点での状態変数の変化量 d(speed+H/2)/dt に相当 */
    double dspeed_k4; /* 状態変数の変化量 d(speed+H)/dt に相当 */
    int t=0; /* 経過時間に相当 */

    FILE *fp; /* 出力用のcsv形式のファイル*/

    fp = fopen("pendulum.csv","w");

    fprintf(fp," ,角度,角速度\n");

    /* シミュレーション */
    for(t=0; t<=(int)(TIME/H); t++) {
        /* 1. まず,現在の位置 (rad),速度 (speed)に対する変化量の加重平均を求める */
        drad_k1 = func_drad(rad, speed);
        drad_k2 = func_drad(rad+drad_k1*H/2, speed+dspeed_k1*H/2);
        drad_k3 = func_drad(rad+drad_k2*H/2, speed+dspeed_k2*H/2);
        drad_k4 = func_drad(rad+drad_k3*H, speed+dspeed_k3*H);
        dspeed_k1 = func_dspeed(rad, speed);
        dspeed_k2 = func_dspeed(rad+drad_k1*H/2, speed+dspeed_k1*H/2);
        dspeed_k3 = func_dspeed(rad+drad_k2*H/2, speed+dspeed_k2*H/2);
        dspeed_k4 = func_dspeed(rad+drad_k3*H, speed+dspeed_k3*H);

        /* 2. 次に,rad, speed を刻み幅 H だけ更新する */
        rad = rad + ((drad_k1+2*drad_k2+2*drad_k3+drad_k4)/6)*H;
        speed = speed + ((dspeed_k1+2*dspeed_k2+2*dspeed_k3+dspeed_k4)/6)*H;

        /* 3. 時刻 (t)と位置 (rad), 速度 (speed)を出力するコードを追加する.*/
        /* 予め設定した"pendulum.csv"に保存する. */
        fprintf(fp,"%f,%f,%f\n",(double)t*H,rad,speed);
    }
    fclose(fp);
    return 0;
}