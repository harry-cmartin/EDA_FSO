#include <stdio.h>
#define EXC(A, B)        \
    Instru tt = A; \
    A = B;               \
    B = tt

typedef struct{
    char name[16];
    int code;
} Instru;

int binarySearch(Instru *vetor, int start, int end, int search){
    while (start + 1 < end){
        int middle = (start + end) / 2;

        if (vetor[middle].code <= search){
            start = middle;}

        if (vetor[middle].code > search){
            end = middle;}
    }
    return vetor[start].code == search ? start : -1;
}

void select(Instru *vetor, int i){
    int j, min, k;

    for (j = 0; j < i; j++){
        min = j;
        for (k = j + 1; k < i; k++){
            if (vetor[k].code < vetor[min].code){
                min = k;
            }
        }
        EXC(vetor[j], vetor[min]);
    }
}

int main(){
    int num, rep1, entry;
    scanf("%d", &num);
    Instru rel[num];

    for (rep1 = 0; rep1 < num; rep1++){
        scanf("%d %s", &rel[rep1].code, rel[rep1].name);
    }

    select(&rel, num);

    while (scanf("%d", &entry) == 1){
        int returned = binarySearch(rel, 0, num, entry);
        printf("%s\n", returned == -1 ? "undefined" : rel[returned].name);
    }
    return 0;
}
