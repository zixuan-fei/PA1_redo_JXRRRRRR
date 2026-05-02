#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "sequence.h"

long *Generate_2p3q_Seq(int n, int *seq_size){
    *seq_size = 0;
    if(n <= 1){
        return malloc(0);
    }
    long result_p = 1;
    int p = 0;
    long* array;

    while(result_p < n){
        result_p = result_p * 2;
        p++;
    }
    p = p-1;

    long result_q = 1;
    int q = 0;
    while(result_q < n){
        result_q = result_q * 3;
        q++;
    }
    q = q-1;
    int most = (q + 2) * (q + 1) / 2 + (p - q + 1) * (p - q); //the biggest number of the integers in the sequence

    array = malloc(sizeof(*array) * most);
    if(!array){
        free(array);
        return NULL;
    }
    int index = 0;
    long initial = 1;
    array[0] = 1;
    index = index+1;
    long follow = 0;
    for(long i = 1; i <= p; i++){
        initial = initial * 2;
        array[index] = initial;
        index++;
        follow = initial;
        for(long j = 1; j <= i; j++){
            follow = follow / 2 * 3;
            if(follow >=n){
                break;
            }
        array[index] = follow;
        index++;
        }
    }

    *seq_size = index;
    long temp;
    for(int k = 1; k < *seq_size; k++){
        for(int l = k; l >= 1; l--){
            if(array[l-1] > array[l]){
                temp = array[l-1];
                array[l-1] = array[l];
                array[l] = temp;
            }
            else{
                break;
            }
        }
    }

    return array;
    

}

