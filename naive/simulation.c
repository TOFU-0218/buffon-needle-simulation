#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

double GenerateNeedle(double interval, double length);
double GetRandom(double max);

static double diff_in_sec(const struct timespec *start,
                          const struct timespec *end){
        return (end->tv_sec - start->tv_sec) +
               (end->tv_nsec - start->tv_nsec) * 1e-9;
}

void PrintProgressBar(int current, int total);

int main(){
        int seed, loopN;
        double length, interval;
        printf("seed:");
        scanf("%d", &seed);
        printf("needle length:");
        scanf("%lf", &length);
        printf("interval:");
        scanf("%lf", &interval);
        printf("times: ");
        scanf("%d", &loopN);
        srand(seed);
        struct timespec t_start, t_end;
        clock_gettime(CLOCK_MONOTONIC, &t_start);
        int hits = 0;
        for(int i=0; i<loopN; i++){
                double tipPosition = GenerateNeedle(interval, length);
                // int isOver = 0;
                if(tipPosition >= interval / 2){
                        // isOver = 1;
                        hits++;
                }
                // printf("%d : %lf\n", isOver, tipPosition);
                // PrintProgressBar(i, loopN);
        }
        clock_gettime(CLOCK_MONOTONIC, &t_end);
        printf("\n");
        double elapsed = diff_in_sec(&t_start, &t_end);
        // printf("===========\n");
        printf("Wall time: %.6f sec\n", elapsed);
        double pi_est = 2.0 * length * loopN / (interval * hits);
        printf("Estimated pi = %.6f\n", pi_est);
}

// [0, max)の一様乱数
double GetRandom(double max){
        return ((double)rand() / (double)RAND_MAX) * max;
}

// 針の先端位置を生成
double GenerateNeedle(double interval, double length){
        double position = GetRandom(interval / 2.0);
        double sin_theta = sin(GetRandom(M_PI/2.0));
        double projection = (length / 2.0) * sin_theta;
        return position + projection;
}

// 進捗バーを描画
void PrintProgressBar(int current, int total){
        const int bar_width = 50;
        double ratio = (double)current / total;
        int filled = (int)(ratio * bar_width);

        // キャリッジリターンで行頭
        printf("\r[");
        for(int i=0; i<filled; i++) printf("=");
        for(int i = filled; i<bar_width; i++) printf(" ");
        printf("] %3.0f%%", ratio*100);

        fflush(stdout);
}
