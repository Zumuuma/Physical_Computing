#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <wiringPi.h>

#define PIN_1 0			  //０番ポート使用。ラズパイ１１番ピンに接続。
#define ON_OFF_BUTTON 7	  //７番ポート使用。ラズパイ７番ピンに接続。
#define LAP_TIME_BUTTON 3 //３番ポート使用。ラズパイ１５番ピンに接続

int val = 0;		//入力ピンの状態がこの変数(val)に記憶される
int old_val = 0;	//valの前の値を保存しておく変数
int lap_val = 0;	//ラップボタンの状態を記憶
int old_lap_val;	//lap_valの前の値を保存
int timer_mode = 0; //タイマーオンモード/タイマーオフモードの状態
int state = 0;		//LEDの状態(0ならオフ、1ならオン)
int lap_time_mode = 0;
int time_sum = 0;						   //計測時間を格納
int diff_time_int = 0;					   //分離した整数部分が入っている(今回は不要)
int diff_time_int_2 = 0;				   //分離した整数部分が入っている(今回は不要)
double diff_time = 0;					   //タイマーの時間の差分(経過時間)を格納
double diff_time_decimal = 0;			   //タイマーの少数部分の時間の差分(経過時間)を格納
double diff_time_for_lap_time = 0;		   //ラップタイムの時間の差分(経過時間)を格納
double diff_time_decimal_for_lap_time = 0; //ラップタイムの少数部分の時間の差分(経過時間)を格納
struct timespec start;					   //タイマー開始時間
struct timespec end;					   //タイマー終了時間
struct timespec old_lap_time;			   //次のラップタイムから引くデータ
struct timespec tmp_lap_time;			   //ラップタイムを取得したデータ

int time_converter_M(int sec) //秒の塊りから分に変換
{
	int min;

	min = (sec % 3600) / 60;

	return min;
}

int time_converter_S(int sec) //秒の塊りから秒だけに変換(分を除いた秒)
{
	sec = sec % 60;

	return sec;
}

double CalcDiffTimeNano(struct timespec start, struct timespec end) //https://iwakurabit.com/training-pgm-c-measure-processing-time-with-clock-gettime-function/より
{
	double sec_diff;
	double nsec_start, nsec_end, nsec_diff;
	double result;

	// 経過時間(整数部)を計算
	sec_diff = (double)difftime(end.tv_sec, start.tv_sec);

	// 開始時刻(小数部)をナノ秒単位に変換
	nsec_start = (double)start.tv_nsec;
	nsec_start = nsec_start * 1e-9;

	// 終了時刻(小数部)をナノ秒単位に変換
	nsec_end = (double)end.tv_nsec;
	nsec_end = nsec_end * 1e-9;

	// 経過時間(小数部)を計算
	if (nsec_start > nsec_end)
	{
		nsec_diff = (1.0 - nsec_start) + nsec_end;
		sec_diff--;
	}
	else
	{
		nsec_diff = nsec_end - nsec_start;
	}

	// 経過時間を計算
	result = sec_diff + nsec_diff;

	return result;
}

void loop()
{
	for (;;)
	{
		val = digitalRead(ON_OFF_BUTTON);		//入力を読みvalに新鮮な値を保存
		lap_val = digitalRead(LAP_TIME_BUTTON); //ラップタイムボタンの入力を読みlap_valに値を保存

		//タクトスイッチが押されたら以下の処理を開始する(それまでは待機状態)
		if ((val == HIGH) && (old_val == LOW))
		{
			timer_mode = 1;	   //タイマーオンモードの処理へ移行
			lap_time_mode = 1; //ラップタイムモードを有効にする。(しかし、lap_valの信号も来ないと動作しない。)
			state = 1 - state; //計測開始とLED点灯を促す
			delay(200);		   //デバウンシング処理
		}

		old_val = val; //古いvalはここに保管

		if (timer_mode == 1) //タイマーオンモードの処理
		{
			if (state == 1) //タイマー開始する時の処理
			{
				clock_gettime(CLOCK_MONOTONIC, &start);		   //計測開始(タイマー機能)
				clock_gettime(CLOCK_MONOTONIC, &old_lap_time); //ラップタイム用計測開始(タイマー機能)
				printf("計測が開始されました。\n");
				digitalWrite(PIN_1, HIGH); //LED光らせる(動作を視覚的にする機能)
				timer_mode = 0;			   //再びタクトスイッチが押されるまでmodeの処理を抜けて待機状態に入る
			}
			else if (state == 0) //タイマー終了する時の処理
			{
				clock_gettime(CLOCK_MONOTONIC, &end); //時間計測終了(タイマー機能)
				printf("計測が終了されました。\n");
				digitalWrite(PIN_1, LOW);							  //LEDオフ
				diff_time = CalcDiffTimeNano(start, end);			  //時間の差分(経過時間求める)
				diff_time_decimal = modff(diff_time, &diff_time_int); //小数部分の時間を分離
				printf("計測結果は%d 分 %d 秒 %3.0lf ミリ秒です。\n", time_converter_M(diff_time), time_converter_S(diff_time), diff_time_decimal * 1000);
				timer_mode = 0;	   //一通りのプロセスが終了したのでタイマーオフモードにする(待機状態へ移行)
				lap_time_mode = 0; //ラップタイムモードを無効にする。
			}
		}

		if ((lap_time_mode == 1) && (lap_val == HIGH) && (old_lap_val == LOW)) //ラップタイムモードが有効でラップタイムボタンが押されたら行う処理
		{
			delay(200);																		  //デバウンシング処理
			clock_gettime(CLOCK_MONOTONIC, &tmp_lap_time);									  //中間地点の時間(タイマー機能)
			diff_time_for_lap_time = CalcDiffTimeNano(old_lap_time, tmp_lap_time);			  //時間の差分(ラップタイム求める)
			diff_time_decimal_for_lap_time = modff(diff_time_for_lap_time, &diff_time_int_2); //少数部分の時間を分離
			printf("ラップタイムは%d 分 %d 秒 %3.0lf ミリ秒です。\n", time_converter_M(diff_time_for_lap_time), time_converter_S(diff_time_for_lap_time), diff_time_decimal_for_lap_time * 1000);
			old_lap_time = tmp_lap_time; //次の計算用に今回のラップタイムボタンが押された時間をold_lap_timeに保管
		}

		old_lap_val = lap_val; //古いlap_valはここに保管
	}
}

int main(void)
{
	wiringPiSetup();				 //https://projects.drogon.net/raspberry-pi/wiringpi/pins/を参照してポート番号を照らし合わせる。
	pinMode(ON_OFF_BUTTON, INPUT);	 //ON_OFF_BUTTONは入力に設定
	pinMode(LAP_TIME_BUTTON, INPUT); //lap_timeは入力に設定
	pinMode(PIN_1, OUTPUT);			 //出力モード

	loop(); //ループさせたいプログラム
}