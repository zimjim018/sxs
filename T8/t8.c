#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int n, r, max[10][10], allocated[10][10], need[10][10], available[10], work[10];
int finish[10], safeSequence[10];

int less(int i)
{
    int j;
    for (j = 0; j < r; j++)
    {
        if (need[i][j] > work[j])
        {
            return 0;
        }
    }
    return 1;
}

void add(int i)
{
    int j;
    for (j = 0; j < r; j++)
    {
        work[j] += allocated[i][j];
    }
}

void bankersAlgorithm()
{
    int i, s = 0, count = 0, previousCount;
    for (i = 0; i < r; i++)
    {
        work[i] = available[i];
    }
    for (i = 0; i < n; i++)
    {
        finish[i] = 0;
    }
    while (count != n)
    {
        previousCount = count;
        for (i = 0; i < n; i++)
        {
            if (!finish[i] && less(i))
            {
                add(i);
                finish[i] = 1;
                safeSequence[s] = i;
                s++;
                count++;
            }
        }
        if (previousCount == count)
        {
            printf("There are unsafe states\n");
            exit(0);
        }
    }
    printf("The safe sequence is:\n");
    for (i = 0; i < n; i++)
    {
        printf("%d\t", safeSequence[i]);
    }
    printf("\n");
}

void resourceRequest()
{
    int flag = 0;
    int i, p, request[10];
    printf("Which process requests?(0/1/2/3/4):");
    scanf("%d", &p);
    printf("Enter the request vector:\n");
    for (i = 0; i < r; i++)
        scanf("%d", &request[i]);
    for (i = 0; i < r; i++)
    {
        if (request[i] > need[p][i] || request[i] > available[i])
        {
            flag = 1;
        }
    }
    if (flag == 0)
    {
        for (i = 0; i < r; i++)
        {
            allocated[p][i] += request[i];
            need[p][i] -= request[i];
            available[i] -= request[i];
        }
        bankersAlgorithm();
        if (safeSequence[0] == p)
            printf("The request can be granted immediately\n");
        else
            printf("The request cannot be granted immediately\n");
    }
    else
    {
        printf("Request Cannot be accomplished\n");
    }
}

void main()
{
    int i, j;
    char ch;
    printf("Enter the number of processes:");
    scanf("%d", &n);
    printf("Enter the number of resources:");
    scanf("%d", &r);
    printf("Enter the allocation matrix:\n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < r; j++)
        {
            scanf("%d", &(allocated[i][j]));
        }
    }
    printf("Enter the maximum requirement matrix:\n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < r; j++)
        {
            scanf("%d", &(max[i][j]));
        }
    }
    printf("Enter the number of instances of each resource available:\n");
    for (i = 0; i < r; i++)
    {
        scanf("%d", &(available[i]));
    }

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            need[i][j] = max[i][j] - allocated[i][j];
        }
    }
    bankersAlgorithm();
    while (1)
    {
        printf("Do you want to execute Resource Request Algorithm(Y/N):");
        scanf(" %c", &ch);
        switch (toupper(ch))
        {
        case 'Y':
            resourceRequest();
            break;
        case 'N':
            exit(0);
        }
    }
}