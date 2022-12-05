#include<stdio.h>

int main(){

    int n, m;

    printf("Enter number of processes: ");
    scanf("%d",&n);
    printf("\nEnter number of resources: ");
    scanf("%d",&m);

    int alloc[n][m], max[n][m], avail[m];

    printf("\nEnter the allocation matrix: ");
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            scanf("%d", &alloc[i][j]);
        }
    }
    printf("\nEnter the max matrix: ");
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            scanf("%d", &max[i][j]);
        }
    }
    printf("\nEnter the available resources: ");
    for(int j=0; j<m; j++){
        scanf("%d", &avail[j]);
    }

    int need[n][m];

    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            need[i][j]=max[i][j]-alloc[i][j];
        }
    }

    int f[n]; //to check wheather every process was able to get available resources

    for(int i; i<n; i++){
        f[i]=0;
    }

    int ans[n],ind=0; //to store safe sequence

    for(int k=0; k<n; k++){
        for(int i=0; i<n; i++){
            if(f[i]==0){
                int flag=0;
                for(int j=0; j<m; j++){
                    if(need[i][j]>avail[j]){
                        flag=1;
                        break;
                    }
                }

                if(flag==0){
                    ans[ind++]=i;
                    for(int j=0; j<m; j++){
                        avail[j] += alloc[i][m];
                    }
                    f[i]=1;
                }
            }
        }
    }

    int flag=1;

    for(int i=0; i<n; i++){
        if(f[i]==0){
            printf("System is not safe");
            flag=0;
            break;
        }
    }

    if(flag==1){
        printf("\n");
        for(int i=0; i<n-1; i++){
            printf("P%d -> ",ans[i]);
        }
        printf("P%d",ans[n-1]);
    }

    return 0;
    
}