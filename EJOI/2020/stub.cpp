#include <stdio.h>
#include <stdlib.h>
#include "stub.h"

int cards[52], S, T, target;
int swapNum = 0, tryNum = 0;
int n = 52;

void doSwap(int s1, int s2){
    if(s1 < 0 || s2 < 0 || s1 >= n || s2 >= n){
        printf("Invalid swap: %d %d\n", s1, s2);
        exit(0);
    }
    int tmp = cards[s1];
    cards[s1] = cards[s2];
    cards[s2] = tmp;

    printf("Swap #%d: %d %d\n", ++swapNum, s1, s2);
    if(swapNum > S) {
        printf("Swap limit exceeded.\n");
        exit(0);
    }
}
int guess(int idx){
    if(idx < 0 || idx >= n){
        printf("Invalid try: %d\n", idx);
        exit(0);
    }
    printf("Try #%d: index = %d, value = %d\n", tryNum++, idx, cards[idx]);
    if(tryNum > T) {
        printf("Guess limit exceeded.\n");
        exit(0);
    }

    if(cards[idx] == target){
        printf("Correct!");
        exit(0);
    }
    return cards[idx];
}

int swapCards(int cards[], int S, int T);
int guessCard(int S, int T, int target);

int main(){
    printf("Enter input:\n");
    int no = scanf("%d%d", &S, &T);
    int c[52];
    for(int i = 0; i < n; i ++){
        cards[i] = i;
        c[i] = cards[i];
    }


    swapCards(c, S, T);

    no = scanf("%d", &target);

    guessCard(S, T, target);
}
