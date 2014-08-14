//
// Always on the Run
//


#include <stdio.h>

#define MAX_F 1000
#define MAX_N 10
#define MAX_D 30

int S[MAX_F+1][MAX_N]; //the minimum total cost of taking d flights to city i, 0 <= i < n

int C[MAX_N][MAX_N][MAX_D+1]; //the cost of flight from city j to city i on day d.


int dp(int n, int k) {
    
    for(int d=0;d<=k;d++) {
        for(int j=0;j<n;j++)
            S[d][j] = -1;
    }
    
    S[0][0] = 0;
    
    for(int d=1;d<=k;d++) {
        
        for(int j=0;j<n;j++) {
            
            if(S[d-1][j] == -1) //can't reach city j on day d-1
                continue;

            for(int i=0;i<n;i++) {
                
                if(j == i) //can't go to the same city
                    continue;
                
                int f = (d-1) % C[j][i][0] + 1;
                if(C[j][i][f] == 0) //no flight
                    continue;
                int cost = S[d-1][j] + C[j][i][f];
                if(S[d][i] == -1 || cost < S[d][i]) {
                    S[d][i] = cost;
                }
                
            }
            
        }
        
    }
    
    return S[k][n-1];
}


int main()
{
    int n,k,t = 0;
    
    
    while(scanf("%d %d", &n, &k) != EOF) {
        
        
        if(n == 0 || k == 0)
            break;
        
        for(int i=0;i<n;i++) {
            for(int j=0;j<n;j++) {
                for(int d=0;d<=MAX_D;d++) {
                    C[i][j][d] = 0;
                }
            }
        }
        
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

