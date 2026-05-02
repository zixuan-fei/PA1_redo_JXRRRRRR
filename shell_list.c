#include "shell_array.h"
#include "sequence.h"
#include "shell_list.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static Node* Bubble_Sort_List(Node* list, int size, long* n_comp){
    Node dummy;
    dummy.next = list;

    Node* prev_prev;
    Node* prev;
    Node* curr;

    int last_element;
    Node* next_node = NULL;
    int sorted = 0;
    int last_change = size;

    while(!sorted){
        sorted = 1;
        last_element = last_change - 1;
        prev_prev = &dummy;
        prev = dummy.next;
        curr = prev->next;

        for(int i = 1; i <= last_element; i++){
            if(prev->value > curr->value){
                next_node = curr->next;
                curr->next = prev;
                prev->next = next_node;
                prev_prev->next = curr;
                sorted = 0;
                last_change = i;
                (*n_comp)++;
            }
            prev_prev = prev_prev->next;
            prev = prev_prev->next;
            curr = prev->next;
        }
    }

    list = dummy.next;
    return dummy.next;
}

Node *List_Load_From_File(char *filename, int *status){
    FILE* fp = fopen(filename, "rb");
    if(!fp){
        *status = -1;
        return NULL;
    }

    long value;
    Node* new_node;
    Node dummy;
    dummy.next = NULL;
    Node* tail = &dummy;

    while(fread(&value, sizeof(long), 1, fp) == 1){
        new_node = malloc(sizeof(*new_node));
        if(new_node == NULL){
            fclose(fp);
            *status = -1;
            return NULL;
        }
        new_node->value = value;
        new_node->next = NULL;
        tail->next = new_node;
        tail = new_node;
    }

    fclose(fp);
    *status = 0;
    return dummy.next;
}

int List_Save_To_File(char* filename, Node* list){
    int number = 0;
    FILE* fp = fopen(filename, "wb");
    if(fp == NULL){
        return -1;
    }

    while(list){
        if(fwrite(&(list->value), sizeof(long), 1, fp) != 1){
            fclose(fp);
            return -1;
        }
        list = list->next;
        number++;
    }

    fclose(fp);
    return number;
}

Node *List_Shellsort(Node *list, long *n_comp){
    *n_comp = 0;
    if(list == NULL){
        return NULL;
    }
    int size = 0;
    int seq_size;
    Node* sorted_list;
    Node* walker = list;

    while(walker){
        walker = walker->next;
        size++;
    }

    long* seq_array = Generate_2p3q_Seq(size, &seq_size);
    if(seq_array == NULL){
        sorted_list = Bubble_Sort_List(list, size, n_comp);
        return sorted_list;
    }

    int gap;
    int sorted;
    int last_change;
    int last_element;
    Node* next_node;
    Node* gap_prev;
    Node* left;
    Node dummy;
    dummy.next = list;
    Node* right;
    Node* left_prev;

    for(int s = seq_size - 1; s >= 1; s--){
        gap = seq_array[s];
        sorted = 0;
        last_change = size;

        while(!sorted){
            sorted = 1;
            last_element = last_change - 1;
            left = dummy.next;
            left_prev = &dummy;
            right = dummy.next;
            gap_prev = &dummy;

            for(int j = 0; j < gap; j++){
                gap_prev = right;
                right = right->next;
            }

            for(int i = gap; i <= last_element; i++){
                if(left->value > right->value){
                    next_node = right->next;
                    right->next = left->next;
                    gap_prev->next = left;
                    left->next = next_node;
                    left_prev->next = right;
                    last_change = i;
                    sorted = 0;
                    (*n_comp)++;
                }

                left_prev = left_prev->next;
                left = left_prev->next;
                gap_prev = gap_prev->next;
                right = gap_prev->next;
            }
        }

        list = dummy.next;
    }

    Node* next_swap = NULL;
    sorted = 0;
    last_change = size;

    while(!sorted){
        sorted = 1;
        last_element = last_change - 1;
        left_prev = &dummy;
        left = dummy.next;
        right = left->next;

        for(int i = 1; i <= last_element; i++){
            if(left->value > right->value){
                next_swap = right->next;
                right->next = left;
                left->next = next_swap;
                left_prev->next = right;
                sorted = 0;
                last_change = i;
                (*n_comp)++;
            }
            left_prev = left_prev->next;
            left = left_prev->next;
            right = left->next;
        }
    }

    list = dummy.next;
    free(seq_array);
    return dummy.next;
}
