#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX_SIZE 100

struct process
{
  int burstTime;
  int arrivalTime;
  int lastExecTime;
  int previouExecutedTime;
  int executionCompleteTime;
  int remainingTime;
  int waitingTime;
  int turnAroundTime;
};

struct process p[100];
int n;
int queue[MAX_SIZE], r = 0, f = 0;

/*
void enqueue(int item)
{
  q[r]=item;
  r++;
}

int dequeue()
{
  int item=q[f];
  f++;
  return item;
}
*/

void avg()
{
  int i;
  float avgwt = 0, avgtt = 0;
  printf("Process\tWaiting Time\tTurn-Around Time\n");
  for (i = 0; i < n; i++)
  {
    p[i].waitingTime = p[i].lastExecTime - p[i].previouExecutedTime - p[i].arrivalTime;
    p[i].turnAroundTime = p[i].executionCompleteTime - p[i].arrivalTime;
    avgwt += p[i].waitingTime;
    avgtt += p[i].turnAroundTime;

    printf("%d\t\t%d\t\t%d\n", (i + 1), p[i].waitingTime, p[i].turnAroundTime);
  }
  printf("Average Waiting Time is %f\n", (avgwt / n));
  printf("Average Turn Around Time is %f\n", (avgtt / n));
}

void roundRobin(int q)
{
  int i, j, pr, time = 0;
  for (j = 0; j <= time; j++)
  {
    for (i = 0; i < n; i++)
    {
      if (p[i].arrivalTime == j)
      {
        // enqueue(i);
        queue[r++] = i;
      }
    }
  }
  do
  {
    pr = queue[f++];
    if (p[pr].remainingTime > q)
    {
      time += q;
      p[pr].remainingTime -= q;
      p[pr].previouExecutedTime += q;
    }
    else if (p[pr].remainingTime <= q)
    {
      p[pr].lastExecTime = time;
      time += p[pr].remainingTime;
      p[pr].remainingTime = 0;
      p[pr].executionCompleteTime = time;
    }
    for (; j <= time; j++)
    {
      for (i = 0; i < n; i++)
        if (p[i].arrivalTime == j)
        {
          // enqueue(i);
          queue[r++] = i;
        }
    }
    if (p[pr].remainingTime != 0)
      // enqueue(pr);
      queue[r++] = pr;
  } while (r != f);

  avg();
}

void SRTF()
{
  int time = 0;
  int i, count = 0;
  int smallest, smallIndex;
  for (time = 0; count != n; time++)
  {
    smallest = 9999;
    for (i = 0; i < n; i++)
    {
      if (p[i].arrivalTime <= time && p[i].remainingTime < smallest && p[i].remainingTime > 0)
      {
        smallest = p[i].remainingTime;
        smallIndex = i;
      }
    }
    p[smallIndex].remainingTime--;
    if (p[smallIndex].remainingTime == 0)
    {
      p[smallIndex].lastExecTime = time;
      p[smallIndex].executionCompleteTime = time + 1;
      count++;
    }
    else
    {
      p[smallIndex].previouExecutedTime += 1;
    }
  }
  avg();
}

void main()
{
  int ch, i;
  char ans;
  int q;
  do
  {
    printf("Enter the number of processes:");
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
      p[i].previouExecutedTime = 0;
    }
    for (i = 0; i < n; i++)
    {
      printf("Enter the arrival and burst times for Process %d:\n", (i + 1));
      scanf("%d %d", &p[i].arrivalTime, &p[i].burstTime);
      p[i].remainingTime = p[i].burstTime;
    }
    printf("Which scheduling algorithm do you want to apply?\n1.Round Robin Algorithm\n2.Shortest Time Remaining First Algorithm\n");
    printf("Enter your chaice:");
    scanf("%d", &ch);
    switch (ch)
    {
    case 1:
      printf("Enter the quantum:");
      scanf("%d", &q);
      roundRobin(q);
      break;
    case 2:
      SRTF();
      break;
    }
    printf("Do you want to continue (Y/N):");
    scanf(" %c", &ans);
  } while (toupper(ans) == 'Y');
}