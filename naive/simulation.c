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
                int isOver = 0;
                if(tipPosition >= interval / 2){
                        isOver = 1;
                        hits++;
                }
                printf("%d : %lf\n", isOver, tipPosition);
        }
        clock_gettime(CLOCK_MONOTONIC, &t_end);
        double elapsed = diff_in_sec(&t_start, &t_end);
        printf("===========\n");
        printf("Wall time: %.6f sec\n", elapsed);

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
