#include <stdio.h>

//F[i,j] la tong cac so tren duong di con tu a(1,1) den a(i,j)
//=>F[n,k] - Phuong an cuoi cung -  la tong cac so tren duong di tu a1,1 den
//a(n,k) (phan tu thu k nao do tren dong n)
//De F[n, k] lon nhat thi tat ca F[i,j] lon nhat
//Truong hop don gian nhat, voi i<=2
//+F[1,1] = a(1,1)
//+F[2,1] = a(2,1) + F[1,1]
//+F[2,2] = a(2,2) + F[1,1]
//----------------------------
// 1,1
// 2,1 2,2
//--------------
// 3,1 3,2 3,3
// 4,1 4,2 4,3 4,4
// 5,1 5,2 5,3 5,4 5,5
// 6,1 6,2 6,3 6,4 6,5 6,
//----------------------------
//Doi voi dong 3 tro be sau:
//Cot 1: F[i,1] = a(i,1) + max(F[i-1, 1], F[i-1, 2])
//Cot i: F[i,i] = a(i,i) + max(F[i-1, i-1])
//Cot i-1: F[i, i-1] = a(i,i-1 ) +max(F[i-1 , i-2], F[i-1, i-1])
//Cot j: (j!=1 ,  va j!=i ,j!= i-1)
// => Tuc la khac phan tu dau tien o cot 1, khac ptu cuoi, va khac phan tu gan cuoi
//F[i,j] = a(i,j)+ max(F[i-1,j-1], F[i-1 , j], F[i-1, j+1])
void readdata(int a[][50], int *n){
    FILE *f;
    f =fopen ("tam_giac_so.txt", "r");
    if(f==NULL){
        printf("Mo file co loi");
        return;
    }
    int i=0, j;
    while(!feof(f)){
        for(j=0; j<=i ; j++){
            fscanf(f, "%d" , &a[i][j]);
        }
        i++;
    }
    *n=i;
    fclose(f);
}
void printdata(int a[][50], int n){
    int i,j;
    printf("\nTam Giac So da chon \n");
    for(i=0; i<n; i++){
        for(j=0; j<=i;j++)
            printf("%5d", a[i][j]);
        printf("\n");
    }
}
//Chi so max
int cs_max(int n , int f[][n], int i, int j){
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
    int i,j;
    printf("Bang f\n");
    for(i=0; i<n;i++){
        for(j=0;j<=i;j++)
            printf("%5d", f[i][j]);
        printf("\n");
    }
}

int cs_max_dongcuoi(int f[], int j){
    int max = f[0];
    int index=0;
    int k;
    for(k=1 ; k<=j;k++){
        if(f[k]>max){
            max = f[k];
            index = k;
        }
    }
    return index;
}

void  tra_bang(int a[][50], int n ,int f[][n], int pa[]){
    int i,j;
    j = cs_max_dongcuoi(f[n-1], n-1);

    pa[n-1] = a[n-1][j];
    for(i = n-1 ; i>=1 ; i--){
        j = cs_max(n,f,i,j);
        pa[i-1] = a[i-1][j];
    }
}

int giaipa(int pa[], int n){
    int i ;
    int sum=0;
    for(i = 0; i<n ; i++)sum+=pa[i];
    return sum;
}
void in_pa(int pa[], int n){
    printf("Phuong an Quy hoach dong:\n");
    printf("Phuong an la duong di qua cac so : \n \n");
    printf("%d", pa[0]);
    int i ;
    for(i=1 ; i<n ; i++) printf(" => %d", pa[i]);
    printf("\n Tong cac so tren duong di la: %d" , giaipa(pa, n));
}
int main(){
    int a[50][50];
    int n;
//Dung de luu tru dong thuc te Tam giac so co n dong
    readdata(a,&n);
    printdata(a,n);
//Mang pa[n] dung de luu phuong an
//Bang f  
    int pa[n];
    int f[n][n];

    tao_bang(a, n,f );
    in_bang(n, f);

    tra_bang(a , n, f , pa);
    in_pa(pa , n);

	return 0;
}
