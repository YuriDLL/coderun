#include "fakeio.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

enum
{
    CMD_NONE = 0,
    CMD_INSERT_END,
    CMD_INSERT_START,
    CMD_DELETE_END,
    CMD_DELETE_START,
    CMD_XOR_PER,
    CMD_MAX,
    CMD_SHOW,
};

typedef struct
{
    uint32_t value;
    void *prev_elem;
    void *next_elem;
} element_t;

typedef struct
{
    element_t *first_elem;
    element_t *last_elem;
    uint32_t max_value;
} list_t;

static void list_add(list_t *list, uint32_t value, bool to_start);
static uint32_t list_pop(list_t *list, bool from_start);
static void calc_max(list_t *list);
static void list_xor(list_t *list, uint32_t xor_value);
static void list_show(list_t *list);
static void list_swap(list_t *list, uint32_t index1, uint32_t index2);
static element_t* get_element(list_t *list, int32_t index);
static uint32_t length(list_t *list);

int main()
{
    int cmd_count = 0;
    list_t list = {};
    scanf("%d", &cmd_count);
    for (int i = 0; i < cmd_count; i++)
    {
        int cmd = 0;
        scanf("%d", &cmd);
        if (cmd == CMD_INSERT_START)
        {
            uint32_t value = 0;
            scanf("%d", &value);
            list_add(&list, value, true);
        }
        else if (cmd == CMD_INSERT_END)
        {
            uint32_t value = 0;
            scanf("%d", &value);
            list_add(&list, value, false);
        }
        else if (cmd == CMD_DELETE_START)
        {
            printf("%d\n", list_pop(&list, true));
        }
        else if (cmd == CMD_DELETE_END)
        {
            printf("%d\n", list_pop(&list, false));
        }
        else if (cmd == CMD_MAX)
        {
            printf("%d\n", list.max_value);
        }
        else if (cmd == CMD_XOR_PER)
        {
            uint32_t value = 0;
            scanf("%d", &value);
            list_xor(&list, value);
        }
        else if (cmd == CMD_SHOW)
        {
            list_show(&list);
        }
        else
        {
            return 0;
        }

    }
    return 0;
}

static void list_add(list_t *list, uint32_t value, bool to_start)
{
    element_t *new_elem = malloc(sizeof(element_t));
    new_elem->value = value;
    if(list->first_elem == NULL)
    {
        new_elem->next_elem = NULL;
        list->first_elem = new_elem;
        list->last_elem = new_elem;
    }
    else
    {
        if(to_start)
        {
            new_elem->next_elem = list->first_elem;
            new_elem->prev_elem = NULL;
            list->first_elem->prev_elem = new_elem;
            list->first_elem = new_elem;
        }
        else
        {
            new_elem->next_elem = NULL;
            new_elem->prev_elem = list->last_elem;
            list->last_elem->next_elem = new_elem;
            list->last_elem = new_elem;
        }
    }
    if (value > list->max_value)
    {
        list->max_value = value;
    }
}

static uint32_t list_pop(list_t *list, bool from_start)
{
    element_t *poped_element = NULL;
    uint32_t poped_value = 0;
    if (list->first_elem != NULL)
    {
        if(list->last_elem == list->first_elem)
        {
            poped_element = list->first_elem;
            list->last_elem = NULL;
            list->first_elem = NULL;
        }
        else if (from_start)
        {
            poped_element = list->first_elem;
            list->first_elem = list->first_elem->next_elem;
            list->first_elem->prev_elem = NULL;
            calc_max(list);
        }
        else
        {
            poped_element = list->last_elem;
            list->last_elem = list->last_elem->prev_elem;
            list->last_elem->next_elem = NULL;
            calc_max(list);
        }
        poped_value = poped_element->value;
        free(poped_element);
    }
    return poped_value;
}

static void calc_max(list_t *list)
{
    uint32_t max = list->first_elem->value;
    element_t *new_element = list->first_elem->next_elem;
    while (new_element != NULL)
    {
        if(max < new_element->value)
        {
            max = new_element->value;
        }
        new_element = new_element->next_elem;
    }
    list->max_value = max;
}

static void list_xor(list_t *list, uint32_t xor_value)
{
    for(uint32_t i=0; i < length(list); i++)
    {
        if ((i ^ xor_value) > i)
        {
            list_swap(list, i, i ^ xor_value);
        }
    }
}

static void list_show(list_t *list)
{
    for (int i=0; i < length(list); i++)
    {
        element_t *elem = get_element(list, i);
        printf("[%d]=%d\n",i , elem->value);
    }
}

static void list_swap(list_t *list, uint32_t index1, uint32_t index2)
{
    element_t* e1 = get_element(list, index1);
    element_t* e2 = get_element(list, index2);
    uint32_t swap_value = {0};
    swap_value = e1->value;
    e1->value = e2->value;
    e2->value = swap_value;
}

static element_t* get_element(list_t *list, int32_t index)
{
    element_t *elem = list->first_elem;
    for(uint32_t i=0; i < index; i++)
    {
        if (elem == NULL)
            break;
        elem = elem->next_elem;
    }
    return elem;
}

static uint32_t length(list_t *list)
{
    element_t *elem = list->first_elem;
    uint32_t length = 0;
    while(elem != NULL)
    {
        length++;
        elem = elem->next_elem;
    }
    return length;
}