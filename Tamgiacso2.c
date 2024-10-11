#include <stdio.h>
#define size 50

void readfile(int a[][size], int *n){
    FILE *f;
    f = fopen("tam_giac_so.txt", "r");
    if(f==NULL){
        printf("Loi!");
        return;
    }
    int i=0,  j ;
    while (!feof(f)){
        for(j=0; j<=i; j++){
            fscanf(f, "%d" , &a[i][j]);
        }
        i++;
    }
    *n= i;
    fclose(f);
}
void printdata( int a[][size],int n ){
    int i , j ;
    for(i=0 ; i<n;i++){
        for(j=0 ; j<=i ; j++){
            printf("%d  ", a[i][j]);
        }
        printf("\n");
    }
}
int cs_max(int n,int f[][n], int i , int j ){
    if(j==0)
        return (f[i-1][0]> f[i-1][1])?0:1;
    if(j==i)
        return i-1;
    if(j==i-1)
        return (f[i-1][i-2]>f[i-1][i-1])?i-2:i-1;
    
    if(f[i-1][j-1]>f[i-1][j]&&f[i-1][j-1]>f[i-1][j+1])
        return j-1;
    if(f[i-1][j]>f[i-1][j-1]&&f[i-1][j]>f[i-1][j+1])
        return j;
    if(f[i-1][j+1]>f[i-1][j] &&f[i-1][j+1]>f[i-1][j-1])
        return j+1;
}

void tao_bang(int a[][50], int n,int f[][n]){
    int i,j;
    f[0][0] = a[0][0];
    f[1][0] = a[1][0]+f[0][0];
    f[1][1] = a[1][1]+f[0][0];

    for(i=2 ; i<n; i++){
        for(j=0 ; j<=i;j++){
            int k = cs_max(n,f,i,j);
            f[i][j] = a[i][j]+f[i-1][k];
        }
    }
}
void in_bang(int n , int f[][n]){
    int i , j ;
    for(i=0 ; i<n;i++){
        for(j=0 ; j<=i ; j++){
            printf("%d  ", f[i][j]);
        }
        printf("\n");
    }
}
int cs_max_dongcuoi(int f[], int j){
    int max = f[0];
    int i,index = 0;
    for(i=1 ; i<=j ;i++){
        if(f[i]> max){
            max = f[i];
            index = i;
        }
    }
    return index;
}
void tra_bang(int a[][size], int n , int f[][n] , int pa[]){
    int i,j;
    j = cs_max_dongcuoi(f[n-1], n-1);
    pa[n-1] = a[n-1][j];
    for(i=n-1 ; i>=1; i--){
        j = cs_max(n,f,i,j);
        pa[i-1] = a[i-1][j];
    }
}
int tong_pa(int pa[], int n){
    int sum =0 ;
    int i ;
    for(i=0 ; i<n ;i++) sum+=pa[i];
    return sum;
}
void in_pa(int pa[], int n){
    printf("Phuong an bang Quy hoach dong la:\n\n");
    printf("%d", pa[0]);
    int i;
    for(i  = 1; i<n ;i++)printf(" => %d" , pa[i]);
    printf("\n\nTong gia tri la %d" , tong_pa(pa, n));
}
int main(){
    int a[size][size];
    int n ;

    readfile(a, &n);
    printdata(a, n);
    

    int f[n][n];
    tao_bang(a, n , f);
    in_bang(n, f);

    int pa[n];
    tra_bang(a,n,f,pa);
    in_pa(pa , n);
}
