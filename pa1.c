#include <stdio.h>
#include <stdlib.h>
#include "sequence.h"
#include "shell_array.h"
#include "shell_list.h"
#include <string.h>

int main(int argc, char **argv){
  /*if(argc != 2){
     return EXIT_FAILURE;
  }
    int n = 100;
    int size = 0;
    long *seq = Generate_2p3q_Seq(n, &size);
    if(seq == NULL) {
        printf("Sequence failed\n");
        return EXIT_FAILURE;
    }
    for(int i =0; i< size; i++){
        printf("%ld ", seq[i]);
    }
    printf("\n");
    free(seq);
    return EXIT_SUCCESS;
    */
    if(argc != 4){
        return EXIT_FAILURE;
    }
    long* array = NULL;
    char* input = argv[2];
    char* output = argv[3];
    int array_size = 0;
    int status;
    long n_comp = 0;
    int save_size;
    if(strcmp(argv[1], "-a") == 0){
        array = Array_Load_From_File(input, &array_size);
        if(!array){
            return EXIT_FAILURE;
        }
        Array_Shellsort(array, array_size, &n_comp);
        fprintf(stdout, "%ld\n", n_comp);
        save_size = Array_Save_To_File(output, array, array_size);
        if(save_size == -1){
            free(array);
            return EXIT_FAILURE;
        }
        free(array);
    }
    else if(strcmp(argv[1], "-l") == 0){
        Node* list = List_Load_From_File(input, &status);
        if(status == -1){
            return EXIT_FAILURE;
        }
        list = List_Shellsort(list, &n_comp);
        fprintf(stdout, "%ld\n", n_comp);
        save_size = List_Save_To_File(output, list);
        if(save_size == -1){
            return EXIT_FAILURE;
        }

        Node* temp = NULL;
        while(list){
            temp = list;
            list = list->next;
            free(temp);
        }
    }
    else{
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;

} 
