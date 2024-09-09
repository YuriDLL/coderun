#include "fakeio.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    void *next_element;
    char word[];
 }word_list;

word_list *insert_new_word(word_list *words, char *new_word)
{
    word_list *new_element = malloc(sizeof(word_list) + strlen(new_word) + sizeof('\0'));
    strcpy(new_element->word, new_word);
    new_element->next_element = words;
    return new_element;
}

void print_words(word_list *word)
{
    while (word != NULL)
    {
        printf("%s\n", word->word);
        word = word->next_element;
    }
}

bool is_already_in_array(word_list *words, char new_word[])
{
    while (words != NULL)
    {
        if(strcmp(words->word, new_word) == 0)
        {
            return true;
        }
        words = words->next_element;
    }
    return false;
}

int main()
{
    char word_buf[0xffff];
    if (scanf("%s", word_buf) != 1)
    {
        printf("%d", 0);
        return 0;
    }
    word_list *first_word = NULL;
    first_word = malloc(sizeof(word_list) + strlen(word_buf) + sizeof('\0'));
    strcpy(first_word->word, word_buf);
    first_word->next_element = NULL;
    int word_count = 1;
    
    while(scanf("%s", word_buf) == 1)
    {
        sizeof(word_list);
        if(!is_already_in_array(first_word, word_buf))
        {
            first_word = insert_new_word(first_word, word_buf);
            word_count++;
        }
    }
    printf("%d", word_count);
    return 0;
}