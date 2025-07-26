#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// 関数のプロトタイプ宣言
double GenerateNeedle(double interval, double length);
double GetRandom(double max);
double DiffInSec(const struct timespec *start, const struct timespec *end);
void PrintProgressBar(int current, int total);

int main() {
    // stdoutのバッファリングを無効化
    setvbuf(stdout, NULL, _IONBF, 0);

    // シミュレーションに必要な変数を宣言
    int seed, loopN;
    double length, interval;

    // ユーザーからの入力を受け取る
    printf("seed: " );
    scanf("%d", &seed);
    printf("needle length: ");
    scanf("%lf", &length);
    printf("interval: ");
    scanf("%lf", &interval);
    printf("times: ");
    scanf("%d", &loopN);

    // 乱数のシードを設定
    srand(seed);

    // 時間計測を開始
    struct timespec t_start, t_end;
    clock_gettime(CLOCK_MONOTONIC, &t_start);

    int hits = 0; // 針が線と交差した回数

    printf("\n----------\n");

    // シミュレーションのメインループ
    for (int i = 0; i < loopN; i++) {
        // 針をランダムに配置し、その先端の位置を取得
        double tipPosition = GenerateNeedle(interval, length);

        // 針が線と交差したかどうかを判定
        if (tipPosition >= interval / 2) {
            hits++;
        }

        // 進捗バーを更新
        PrintProgressBar(i + 1, loopN);
    }

    printf("\n----------\n");

    // 時間計測を終了
    clock_gettime(CLOCK_MONOTONIC, &t_end);

    // 経過時間を計算して表示
    double elapsed = DiffInSec(&t_start, &t_end);
    printf("Wall time: %.6f sec\n", elapsed);

    // ビュフォンの針の公式を用いて円周率を推定
    double pi_est = 2.0 * length * loopN / (interval * hits);
    printf("Estimated pi = %.6f\n", pi_est);

    return 0;
}

/**
 * @brief 2つの時刻の差を秒単位で計算する
 * @param start 開始時刻
 * @param end 終了時刻
 * @return 経過時間（秒）
 */
double DiffInSec(const struct timespec *start, const struct timespec *end) {
    return (end->tv_sec - start->tv_sec) + (end->tv_nsec - start->tv_nsec) * 1e-9;
}

/**
 * @brief [0, max)の範囲で一様乱数を生成する
 * @param max 乱数の最大値（含まない）
 * @return 生成された乱数
 */
double GetRandom(double max) {
    return ((double)rand() / (double)RAND_MAX) * max;
}

/**
 * @brief 針をランダムに配置し、その先端の位置を計算する
 * @param interval 平行線の間隔
 * @param length 針の長さ
 * @return 針の先端のy座標（最も近い線からの距離）
 */
double GenerateNeedle(double interval, double length) {
    // 針の中心のy座標を[0, interval/2]の範囲でランダムに決定
    double position = GetRandom(interval / 2.0);
    // 針の角度θを[0, π/2]の範囲でランダムに決定し、そのsinを計算
    double sin_theta = sin(GetRandom(M_PI / 2.0));
    // 針の半分の長さの、y軸への射影を計算
    double projection = (length / 2.0) * sin_theta;
    // 針の先端のy座標を返す
    return position + projection;
}

/**
 * @brief コンソールに進捗バーを表示する
 * @param current 現在の進捗
 * @param total 全体の量
 */
void PrintProgressBar(int current, int total) {
    int ten_percent = total / 10;
    if (current % ten_percent == 0) {
        printf("#");
    }
}
