#include<stdio.h>
#include<stdlib.h>

// float GenerateNeedles(float range);
float GetRandom(float max);

int main(int argc, char *argv[]){
        if(argc!=3){
                fprintf(stderr, "Error: Invalid number of arguments.\n");
                exit(1);
        }
        int seed = atoi(argv[1]);
        float max = atoi(argv[2]);
        srand(seed);
        int i;
        for(i=0; i<10; i++){
                printf("%lf\n", GetRandom(max));
        }
}

float GetRandom(float max){
        return ((float)rand() / (float)RAND_MAX) * max;
}
