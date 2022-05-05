#include <stdio.h>
#include <stdlib.h>
#include "data.h"
#include "generation.h"
#include "cache.h"
#include <stdbool.h>
#include <math.h>

unsigned int *generate_grid(unsigned int size)
{
    unsigned int *a = createArray(size);
    return a;
}

bool getDigit(unsigned int i, int digit)
{
    return i >> digit & 1;
}

int countSetBits(unsigned int i)
{
    int count = 0;
    while (i != 0)
    {
        i &= (i - 1);
        count++;
    }
    return count;
}

SizedList *list_lines(unsigned int size)
{
    int res[(int)pow(2, size)];
    int cpt = 0;

    for (int i = 0; i < pow(2, size); i++) // get lines that work
    {
        int nb = size - 2;
        bool isValid = true;
        for (int digit = 0; digit < nb; digit++) // check successive digits
        {
            int a = getDigit(i, digit);
            int b = getDigit(i, digit + 1);
            int c = getDigit(i, digit + 2);
            if (a == b && b == c)
            {
                isValid = false;
                break;
            }
        }
        if (isValid && countSetBits(i) == size / 2) // check number of set bits
        {
            res[cpt] = i;
            cpt++;
        }
    }
    SizedList *res_ = (SizedList *)malloc(sizeof(SizedList));
    res_->size = cpt;
    res_->data = (unsigned int *)malloc(sizeof(unsigned int) * cpt);
    for (int i = 0; i < cpt; i++)
    {
        res_->data[i] = res[i];
    }
    return res_;
}

SizedList *extend(SizedList *l1, SizedList *l2)
{
    SizedList *res = (SizedList *)malloc(sizeof(SizedList));
    res->size = l1->size + l2->size;
    res->data = (unsigned int *)malloc(sizeof(unsigned int) * res->size);
    for (int i = 0; i < l1->size; i++)
    {
        res->data[i] = l1->data[i];
    }
    for (int i = 0; i < l2->size; i++)
    {
        res->data[i + l1->size] = l2->data[i];
    }
    return res;
}

SizedList *copy(SizedList *l)
{
    SizedList *res = (SizedList *)malloc(sizeof(SizedList));
    res->size = l->size;
    res->data = (unsigned int *)malloc(sizeof(unsigned int) * res->size);
    for (int i = 0; i < l->size; i++)
    {
        res->data[i] = l->data[i];
    }
    return res;
}

SizedList *append(SizedList *l, unsigned int e)
{
    SizedList *res = (SizedList *)malloc(sizeof(SizedList));
    res->size = l->size + 1;
    res->data = (unsigned int *)malloc(sizeof(unsigned int) * res->size);
    for (int i = 0; i < l->size; i++)
    {
        res->data[i] = l->data[i];
    }
    res->data[l->size] = e;
    return res;
}

ListSizedList *appendList(ListSizedList *l, SizedList *e)
{
    ListSizedList *res = (ListSizedList *)malloc(sizeof(ListSizedList));
    res->size = l->size + 1;
    res->data = (SizedList **)malloc(sizeof(SizedList *) * res->size);
    for (int i = 0; i < l->size; i++)
    {
        res->data[i] = l->data[i];
    }
    res->data[l->size] = e;
    return res;
}

ListSizedList *extendList(ListSizedList *l1, ListSizedList *l2)
{
    ListSizedList *res = (ListSizedList *)malloc(sizeof(ListSizedList));
    res->size = l1->size + l2->size;
    res->data = (SizedList **)malloc(sizeof(SizedList *) * res->size);
    for (int i = 0; i < l1->size; i++)
    {
        res->data[i] = l1->data[i];
    }
    for (int i = 0; i < l2->size; i++)
    {
        res->data[i + l1->size] = l2->data[i];
    }
    return res;
}

ListSizedList *knapsack(int i, int target, int k, SizedList *A, int N)
{
    if (i > N - k)
    {
        ListSizedList *res = (ListSizedList *)malloc(sizeof(ListSizedList));
        res->size = 0;
        res->data = NULL;
        return res;
    }
    if (target == 0 && k == 0)
    {
        ListSizedList *res = (ListSizedList *)malloc(sizeof(ListSizedList));
        res->size = 1;
        res->data = (SizedList **)malloc(sizeof(SizedList *));
        res->data[0] = (SizedList *)malloc(sizeof(SizedList));
        res->data[0]->size = 0;
        res->data[0]->data = NULL;
        return res;
    }
    if (k <= 0)
    {
        ListSizedList *res = (ListSizedList *)malloc(sizeof(ListSizedList));
        res->size = 0;
        res->data = NULL;
        return res;
    }
    unsigned int tmpdata[] = {i, target, k};
    SizedList *temp = (SizedList *)malloc(sizeof(SizedList));
    temp->size = 3;
    temp->data = (unsigned int *)malloc(sizeof(unsigned int) * temp->size);
    for (int i = 0; i < temp->size; i++)
    {
        temp->data[i] = tmpdata[i];
    }
    ListSizedList *restemp = find_entry(hashCode(temp));
    if (restemp != NULL)
    {
        return restemp;
    }
    ListSizedList *ret = (ListSizedList *)malloc(sizeof(ListSizedList));
    ret->size = 0;
    ret->data = NULL;
    ListSizedList *res = knapsack(i + 1, target - A->data[i], k - 1, A, N);
    for (int j = 0; j < res->size; j++)
    {
        SizedList *new = copy(res->data[j]);
        new = append(new, A->data[i]);
        ret = appendList(ret, new);
    }
    ret = extendList(ret, knapsack(i + 1, target, k, A, N));
    add_entry(hashCode(temp), ret);
    return ret;
}