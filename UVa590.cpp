//
// Always on the Run
//


#include <stdio.h>

#define MAX_F 1000
#define MAX_N 10
#define MAX_D 30

int S[MAX_N][MAX_F+1]; //the minimum total cost to city u by taking d flights, 0 <= u < n

int C[MAX_N][MAX_N][MAX_D+1]; //the cost of flight from city u to city v on day d.

int dp(int n, int k) {

    for(int u=0;u<n;u++)
        for(int d=0;d<=k;d++)
            S[u][d] = -1;
    
    S[0][0] = 0;
    
    for(int d=1;d<=k;d++) {
        
        for(int u=0;u<n;u++) {
            
            if(S[u][d-1] == -1) //can't reach city u on day d-1
                continue;

            for(int v=0;v<n;v++) {
                
                if(u == v) //can't go to the same city
                    continue;
                
                int f = (d-1) % C[u][v][0] + 1;
                if(C[u][v][f] == 0) //no flight
                    continue;
                int cost = S[u][d-1] + C[u][v][f];
                if(S[v][d] == -1 || cost < S[v][d]) {
                    S[v][d] = cost;
                }
            }
        }
    }
    return S[n-1][k];
}


int main()
{
    int n,k,t = 0;
    
    while(scanf("%d %d", &n, &k) != EOF) {
        
        if(n == 0 || k == 0)
            break;
        
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                for(int d=0;d<=MAX_D;d++)
                    C[i][j][d] = 0;
                    
        for(int i=0;i<n;i++) {
            
            for(int j=0;j<n;j++) {
                
                if(i == j)
                    continue;
                int p;
                scanf("%d", &p);
                
                C[i][j][0] = p;
                
                for(int d=1;d<=p;d++) {
                    scanf("%d", &C[i][j][d]);
                }
            }
        }
        
        printf("Scenario #%d\n", ++t);
        int ans = dp(n,k);
        if(ans == -1) {
            printf("No flight possible.\n\n");
        }
        else {
            printf("The best flight costs %d.\n\n", ans);
        }
    }
    return 0;
}

