#include<stdio.h>
#include<stdlib.h>
#include<math.h>

double GenerateNeedle(double interval, double length);
double GetRandom(double max);

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
        int i;
        for(i=0; i<loopN; i++){
                double tipPosition = GenerateNeedle(interval, length);
                int isOver = 0;
                if(tipPosition >= interval / 2){
                        isOver = 1;
                }
                printf("%d : %lf\n", isOver, tipPosition);
        }
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
