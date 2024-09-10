#include "fakeio.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define stdin in

typedef struct {
    void *next_element;
    int word_start_index;
 }word_list;

static bool is_separator(char sym)
{
    return sym == ' ' || sym == '\n';
}

static bool is_equal_word(int word_index1, int word_index2)
{
    char sym1, sym2;
    do {
        fseek(stdin, word_index1, SEEK_SET);
        sym1 = fgetc(stdin);
        fseek(stdin, word_index2, SEEK_SET);
        sym2 = fgetc(stdin);
        if (is_separator(sym1) && is_separator(sym2))
        {
            return true;
        }

        word_index1++;
        word_index2++;
    } while(sym1 == sym2);

    return false;
}

static word_list *insert_new_word(word_list *first_word, int new_word_index)
{
    word_list *new_element = malloc(sizeof(word_list));
    new_element->word_start_index = new_word_index;
    if (first_word != NULL)
    {
        new_element->next_element = first_word;
    }
    else
    {
        new_element->next_element = NULL;
    }
    return new_element;
}

static int length(word_list *first_word)
{
    int length = 0;
    word_list *word = first_word;
    while(word != NULL)
    {
        char buf[100];
        fseek(stdin, word->word_start_index, SEEK_SET);
        fscanf(stdin, "%s", buf);
        length++;
        word = word->next_element;
    }
    return length;
}

static word_list *add_unique_word(word_list *first_word, int new_word_index)
{
    word_list *word = first_word;
    while(word != NULL)
    {
        if(is_equal_word(word->word_start_index, new_word_index))
        {
            return first_word;
        }
        word = word->next_element;
    }
    return insert_new_word(first_word, new_word_index);
}

int main()
{
    word_list *first_word = NULL;
    char sym = fgetc(stdin);
    int index = 0;
    bool last_sym_separator = true;
    while (sym != EOF)
    {
        if(!is_separator(sym) && last_sym_separator)
        {
            fpos_t position;
            fgetpos(stdin, &position);
            first_word = add_unique_word(first_word, index);
            fsetpos(stdin, &position);
        }
        last_sym_separator = is_separator(sym);
        index++;
        fseek(stdin, index, SEEK_SET);
        sym = fgetc(stdin);
    }
    printf("%d", length(first_word));
    return 0;
}