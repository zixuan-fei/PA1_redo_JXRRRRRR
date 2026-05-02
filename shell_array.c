#include "shell_array.h"
#include "sequence.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static void Bubble_sort(long* array, int size, long* n_comp){
    int sign = 0;
    long temp;
    int last_change = size;
    int last_element;
    while(!sign){
        sign = 1;
        last_element = last_change -1;
        for(int i = 1; i<=last_element;i++){
            (*n_comp)++;
            if(array[i-1] > array[i]){
                temp = array[i];
                array[i] = array[i-1];
                array[i-1] = temp;
                last_change = i;
                sign = 0;
            }
        }
    }
}

long *Array_Load_From_File(char *filename, int *size){
    FILE* fp = fopen(filename, "rb");
    if(fp == NULL){
        *size = 0;
        return NULL;
    }

    fseek(fp, 0L, SEEK_END);
    *size = ftell(fp) / sizeof(long);
    fseek(fp, 0L, SEEK_SET);
    long* array = malloc(sizeof(*array) * (*size));
    if(array == NULL){
        *size =0;
        fclose(fp);
        return NULL;
    }
    if(fread(array, sizeof(long), *size, fp) != *size){
        fclose(fp);
        free(array);
        return NULL;
    }

    fclose(fp);
    return array;


}

int Array_Save_To_File(char *filename, long *array, int size){
    if(array == NULL){
        return -1;
    }
    FILE* fp = fopen(filename, "wb");
    if(fp == NULL){
        return -1;
    }
    int num = fwrite(array, sizeof(long), size, fp);
    if(num != size){
        fclose(fp);
        return -1;
    }
    fclose(fp);
    return num;
}

void Array_Shellsort(long *array, int size, long *n_comp){
    int seq_size = 0;
    long* seq_array = Generate_2p3q_Seq(size, &seq_size);
    if(!seq_array){
        Bubble_sort(array, size, n_comp);
        return;
    }
    int k;
    int i;
    long temp_r;
    for(int a = seq_size - 1; a >= 0; a--){
        k = seq_array[a];
        for(int j = k; j < size; j++){
            temp_r = array[j];
            i = j;
            while(i >= k && array[i - k] > temp_r){
                array[i] = array[i-k];
                i = i-k;
                (*n_comp)++;
            }
            array[i] = temp_r;
        }
    }
    free(seq_array);
}
