#include <stdio.h>
#include <malloc.h>
#include <string.h>

// Bai toan cai balo 1
// Moi mot vat co so luong ko han che

// Ky thuat Quy Hoach Dong
typedef struct
{
	char tenDV[20];
	float GT;
	int TL, So_DV_Duoc_Chon;
} DoVat;

DoVat *ReadFromFile(int *w, int *n)
{
	FILE *f;
	DoVat *dsdv;
	f = fopen("Balo.txt", "r");
	fscanf(f, "%d", w);
	dsdv = (DoVat *)malloc(sizeof(DoVat));
	int i = 0;
	while (!feof(f))
	{
		fscanf(f, "%d%f%[^\n]", &dsdv[i].TL, &dsdv[i].GT, &dsdv[i].tenDV);
		// 	 	dsdv[i].DG = dsdv[i].GT / dsdv[i].TL;
		dsdv[i].So_DV_Duoc_Chon = 0;
		i++;
		dsdv = realloc(dsdv, sizeof(DoVat) * (i + 1));
	}
	*n = i;
	// So luong do vat
	fclose(f);
	return dsdv;
}
void InDSDV(DoVat *dsdv, int n, int w)
{
	int i, tongTL = 0.0;
	float tonggt = 0.0;
	printf("\nPhuong an thu duoc tu ky that Quy Hoach Dong nhu sau : \n");

	printf("|---|--------------------|---------|---------|-------------------|\n");
	printf("|STT|-----Ten Do Vat-----|T. Luong |-Cia Tri-|So Do Vat Duoc Chon|\n");
	printf("|---|--------------------|---------|---------|-------------------|\n");
	for (i = 0; i < n; i++)
	{
		printf("|%-3d|%-20s|%5d	   |%9.2f|%8d           |\n", i + 1, dsdv[i].tenDV, dsdv[i].TL, dsdv[i].GT, dsdv[i].So_DV_Duoc_Chon);

		tongTL = tongTL + dsdv[i].So_DV_Duoc_Chon * dsdv[i].TL;
		tonggt = tonggt + dsdv[i].So_DV_Duoc_Chon * dsdv[i].GT;
	}

	printf("|---|--------------------|---------|---------|-------------------|\n");
	printf("\nTrong luong cua balo = %d\n ", w);
	printf("\nTong trong luong cac vat duoc chon la : %d\n\n Tong gia tri la: %-9.2f", tongTL, tonggt);
}
void TaoBang(DoVat *dsdv, int n, int w, float f[][w + 1], int x[][w + 1]) {
	int xk, yk, k;
	int XMax, V;
	float FMax;
	// Dien hang dau tien cua bang
	for (V = 0; V <= w; V++)
	{
		x[0][V] = V / dsdv[0].TL;
		f[0][V] = x[0][V] * dsdv[0].GT;
	}
	// Dien cac dong con lai
	for (k = 1; k < n; k++)
	{
		for (V = 0; V <= w; V++)
		{
			FMax = f[k - 1][V];
			XMax = 0;
			yk = V / dsdv[k].TL;
			// Balo 2 : yk = min (i, v/dsdv[k].TL);
			// Balo 3 : yk = min (dsdv[k].SL , v/dsdv[k]/Tl);
			for (xk = 1; xk <= yk; xk++)
			{
				if (f[k - 1][V - xk * dsdv[k].TL] + xk * dsdv[k].GT > FMax)
				{
					FMax = f[k - 1][V - xk * dsdv[k].TL] + xk * dsdv[k].GT;
					XMax = xk;
				}
			}
			f[k][V] = FMax;
			x[k][V] = XMax;
		}
	}
}
void InBang(int n, int w, float f[][w + 1], int x[][w + 1])
{
	int v, k;
	printf("\nBang F va X:\n\n");
	for (k = 0; k < n; k++)
	{
		for (v = 0; v <= w; v++)
			printf("%c%4.1f|%2d", 186, f[k][v], x[k][v]);
		printf("%c\n", 186);
	}
}
void TraBang(DoVat *dsdv, int n, int w, int x[][w + 1])
{
	int k, v;
	v = w;
	for (k = n - 1; k >= 0; k--)
	{
		dsdv[k].So_DV_Duoc_Chon = x[k][v];
		v = v - x[k][v] * dsdv[k].TL;
	}
}
int main()
{
	int n, w;
	DoVat *dsdv;
	dsdv = ReadFromFile(&w, &n);

	float f[n][w + 1];
	int x[n][w + 1];

	TaoBang(dsdv, n, w, f, x); 

	InBang(n, w, f, x);
	TraBang(dsdv, n, w, x);
	InDSDV(dsdv, n, w);
	free(dsdv);

	return 0;
}
