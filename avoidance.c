#include<stdio.h>

int req[100][100],alloc[100][100],need[100][100],avai[100];
int n,m;

void display()
{
    int i,j;
    printf("Process\tAllocation\treq\tNeed\tAvailiable\t");
    for(i=0;i<n;i++)
    {
        printf("\nT%d\t    ",i+1);
        for(j=0;j<m;j++)
        	printf("%d ",alloc[i][j]);
        printf("\t");
        for(j=0;j<m;j++)
			printf("%d ",req[i][j]);
    	printf("\t");
        for(j=0;j<m;j++)
			printf("%d ",need[i][j]); 
		printf("\t");
        if(i==0)
        {
        	for(j=0;j<m;j++)
        		printf("%d ",avai[j]);
        }
    }
    printf("\n");
}

int safety_check()
{
    int finish[100],flag=1,avai1[100];
    int i,j;
    for(i=0;i<m;i++)
    	avai1[i]=avai[i];
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
            if((finish[i]==0) && (need[i][j]<=avai1[j]))
            	c++;
        }
        if(c!=m)
            continue;
        for(j=0;j<m;j++)
        {
            avai1[j]+=alloc[i][j];
            finish[i]=1;
        }
        if(finish[i]==1)
    		i=-1;
    }
    for(i=0;i<n;i++)
    {
        if(finish[i]==0)
        	return 0;
	}
    return 1;
}

void resource_request()
{
	int temp[100],finish[100],k=0,order[100],i,j;
	for(i=0;i<n;i++)
    {
    	for(j=0;j<m;j++)
    		need[i][j]=req[i][j]-alloc[i][j];
	}
	for(i=0;i<n;i++)
		finish[i]=0;
	for(i=0;i<n;i++)
	{
		int f=1;
		if(finish[i]==1)
			continue;
		for(j=0;j<m;j++)
		{
			if(need[i][j]>avai[j])
			{
				f=0;
				break;
			}
		}
		if(f==0)
			continue;
		for(j=0;j<m;j++)
		{
			temp[j]=need[i][j];
			alloc[i][j]+=need[i][j];
			avai[j]-=need[i][j];
			need[i][j]=0;
		}
		int x=safety_check();
		if(x==1)
		{
			for(j=0;j<m;j++)
				avai[j]+=req[i][j],alloc[i][j]=0,req[i][j]=0;
			finish[i]=1;
			order[k++]=i+1;
			i=-1;
		}
		else
		{
			for(j=0;j<m;j++)
				avai[j]+=need[i][j];
			for(j=0;j<m;j++)
				need[i][j]=temp[j],alloc[i][j]-=temp[j];
		}
	}
	printf("\nThe safe sequence is: ");
	for(j=0;j<k;j++)
		printf("T%d ",order[j]);
}

int main()
{
    int i,j;
    printf("-------------Deadlock Avoidance Algorithm------------\n");
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
    printf("Enter req Matrix\n");
    for(i=0;i<n;i++)
    {
        for(j=0;j<m;j++)
             scanf("%d",&req[i][j]);
    }
    printf("\n");
    printf("Enter available resources of each type\n");
	for(j=0;j<m;j++)
        scanf("%d",&avai[j]);
    printf("\n");
    display();
    printf("\n");
    resource_request();
	printf("\n");
    return 0;
}
