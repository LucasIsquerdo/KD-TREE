#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<conio2.h>
#include<math.h>
#define TF 6
#define k 2

struct kd
{
	int no[2];
	struct kd *esq,*dir;
	
};
typedef struct kd KdTree;

KdTree *CriaNo(int ponto[k])
{
	KdTree *nova = (KdTree*)malloc(sizeof(KdTree));
	nova->esq = nova->dir = NULL;
	nova->no[0]=ponto[0];
	nova->no[1]=ponto[1];
	
	return nova;
}
void distanciaEuclidiana(KdTree *raiz, int coord[k], int raio, int n)
{
	
	//x de um menos x de outro eleva ao quadrado
	//mesmo com o y
	//raiz de (x-x)^2 + (y-y)^2
	//ve se est� dentro do raio e olha em x, tem que ser menor ou igual
	int x,y, distEuclid,d, i=0, achou[TF][k];
	d=n%k;
	if(raiz!=NULL)
	{
		if(d==0)
		{
			x = pow(coord[0]-raiz->no[0],2);
			y = pow(coord[1]-raiz->no[1],2);
			distEuclid = sqrt(x+y);
			if(distEuclid<=raio)
			{
				achou[i][0]=raiz->no[0];
				achou[i][1]=raiz->no[1];
				printf("Ponto encontrado no raio %d estabelecido: %d, %d\n",raio,achou[i][0],achou[i][1]);
				i++;
				
			}
			if(coord[0]<=raiz->no[0])
				distanciaEuclidiana(raiz->esq, coord,raio,n+1);
			else
				distanciaEuclidiana(raiz->dir, coord,raio,n+1);
		}
		if(d==1)
		{
			x = pow(coord[0]-raiz->no[0],2);
			y = pow(coord[1]-raiz->no[1],2);
			distEuclid = sqrt(x+y);
			if(distEuclid<=raio)
			{
				achou[i][0]=raiz->no[0];
				achou[i][1]=raiz->no[1];
				printf("Ponto encontrado no raio %d estabelecido: %d, %d\n",raio,achou[i][0],achou[i][1]);
				i++;
			}
			if(coord[1]<=raiz->no[1])
				distanciaEuclidiana(raiz->esq, coord,raio,n+1);
			else
				distanciaEuclidiana(raiz->dir, coord,raio,n+1);
		}
		
	}
}
void ordena(int pontos [TF-1][k],int inicio,int fim,int d)
{
	//se 0 ordena pelo x
	//se 1 pelo y
	int i,j, aux1,aux2;
	if(d==0)
	{
		for(j=fim;j>=1;j--)
		{
			for(i=inicio;i<j;i++)
				if(pontos[i][0]>pontos[i+1][0])
				{
					aux1=pontos[i][0];
					aux2=pontos[i][1];
					pontos[i][0] = pontos[i+1][0];
					pontos[i][1] = pontos[i+1][1];
					pontos[i+1][0]=aux1;
					pontos[i+1][1]=aux2;
				}
			
		}
			
	}
	if(d==1)
	{
		for(j=fim;j>=1;j--)
		{
			for(i=inicio;i<j;i++)
				if(pontos[i][1]>pontos[i+1][1])
				{
					aux1=pontos[i][0];
					aux2=pontos[i][1];
					pontos[i][0] = pontos[i+1][0];
					pontos[i][1] = pontos[i+1][1];
					pontos[i+1][0]=aux1;
					pontos[i+1][1]=aux2;
				}
			
		}
		
	}

}

void ArvKdTree(KdTree **kd, int pontos[TF-1][k], int inicio, int fim, int n)
{

	int d,meio;
	d = n%k;
	ordena(pontos,inicio,fim,d);
	meio = (inicio+fim)/2;
	*kd = CriaNo(pontos[meio]);
	if(inicio<=meio-1)
		ArvKdTree(&(*kd)->esq,pontos,inicio,meio-1,n+1);
	if(meio+1<=fim)
		ArvKdTree(&(*kd)->dir,pontos,meio+1,fim,n+1);
}



void exibeArvore(KdTree *tree, int x, int y, int dist)
{
		
	if(tree != NULL)
	{
		gotoxy(x,y);
		printf("%d,%d",tree->no[0], tree->no[1]);
		if(tree->esq != NULL)
		{
			gotoxy(x - dist/2, y+1);
			printf("/");
		}
		if(tree->dir != NULL)
		{
			gotoxy(x + dist/2, y+1);
			printf("\\");
		}
		exibeArvore(tree->esq, x-dist, y+2, dist/2);
		exibeArvore(tree->dir, x+dist, y+2, dist/2);
	}
	
}


int main()
{
	KdTree *kd = NULL;
	int pontos[TF][k];
	int i,j,inicio=0,fim=TF,n=0;
// VALORES GERADOS RANDOM PARA PONTOS
	for(i=0; i<TF; i++){
		pontos[i][0] = rand() % 99;
		pontos[i][1] = rand() % 99;
	}
// VALORES TESTE QUE EST�O NO EXEMPLO
//	pontos[0][0]=30;
//	pontos[0][1]=40;
//	pontos[1][0]=5;
//	pontos[1][1]=25;
//	pontos[2][0]=10;
//	pontos[2][1]=12;
//	pontos[3][0]=70;
//	pontos[3][1]=70;
//	pontos[4][0]=50;
//	pontos[4][1]=30;
//	pontos[5][0]=35;
//	pontos[5][1]=45;
	ArvKdTree(&kd,pontos,0,TF-1,n);	
	int raio, coord[k];
//  VALORES TESTE QUE EST�O NO EXEMPLO
//	raio = 10;
//	coord[0]=8;
//	coord[1]=18;
//  TESTE COM OUTROS VALORES
	raio = 20;
	coord[0]=95;
	coord[1]=55;
	distanciaEuclidiana(kd,coord,raio,n);
	exibeArvore(kd,40,5,20);

}
