#include<stdio.h>

int req[100][100],alloc[100][100],need[100][100],avai[100];
int n,m;

void display()
{
    int i,j;
    printf("Process\tAllocation\tRequest\tAvailable\t");
    for(i=0;i<n;i++)
    {
        printf("\nP%d\t    ",i+1);
        for(j=0;j<m;j++)
        	printf("%d ",alloc[i][j]);
    	printf("\t");
        for(j=0;j<m;j++)
			printf("%d ",req[i][j]); 
		printf("\t");
        if(i==0)
        {
        	for(j=0;j<m;j++)
        		printf("%d ",avai[j]);
        }
    }
}

void safety_check()
{
    int i,j,finish[100],flag=1,dead[100];
    for(i=0;i<n;i++)
    {
    	int f=1;
		for(j=0;j<m;j++)
		{
			if(alloc[i][j]!=0)
			{
				f=0;
				break;
			}
		}
        finish[i]=f;
    }
	for(i=0;i<n;i++)
    {
        int c=0;
        for(j=0;j<m;j++)
        {
            if((finish[i]==0) && (req[i][j]<=avai[j]))
            	c++;
        }
        if(c!=m)
            continue;
        for(j=0;j<m;j++)
        {
            avai[j]+=alloc[i][j];
            finish[i]=1;
        }
        if(finish[i]==1)
    		i=-1;
    }
    flag=0,j=0;
    for(i=0;i<n;i++)
    {
        if(finish[i]==0)
        {
        	flag=1;
            dead[j]=i+1,j++;
        }
	}
    if(flag==1)
    {
		printf("\n\nDeadlock found, processes are:\n");
    	for(i=0;i<j;i++)
            printf("P%d\t",dead[i]);
    }
    else
        printf("\nNo Deadlock");
}

int main()
{
    int i,j;
    printf("-----------Deadlock Detection Algorithm------\n");
    printf("Enter number of processes: ");
    scanf("%d",&n);
    printf("\n");
    printf("Enter number of resource instances: ");
    scanf("%d",&m);
    printf("\n");
    printf("Enter Allocation Matrix\n");
    for(i=0;i<n;i++)
	{
    	for(j=0;j<m;j++)
            scanf("%d",&alloc[i][j]);
    }
    printf("\n");
    printf("Enter Request Matrix\n");
    for(i=0;i<n;i++)
    {
        for(j=0;j<m;j++)
             scanf("%d",&req[i][j]);
    }
    printf("\n");
    printf("Enter available resources\n");
	for(j=0;j<m;j++)
        scanf("%d",&avai[j]);
    printf("\n");
    display();
    printf("\n");
    safety_check();
    return 0;
}
