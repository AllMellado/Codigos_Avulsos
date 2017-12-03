#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct vetorVars{
	char letra;
	int flag;
	int chave;
	struct vetorVars* prox;
}vetorVars;

int verificarSimplificacao(FILE* arq, vetorVars* prim, int nrVars);
int verificarGramatica(FILE* arq);
void guardarVariaveis(FILE* arq, vetorVars** prim, int* nrVars);
void print(vetorVars* prim);
void printMax(vetorVars* prim);
int inserir(char aux, vetorVars** terms, int k);
int inserirFim(char aux, vetorVars** terms, int k);
int remover(vetorVars** terms);
char* modificar(vetorVars* terms,vetorVars* prim, char t[], int sinal);
int normChompsky2(FILE* arq, vetorVars** terms, vetorVars* prim, vetorVars* reset);
int normChompsky3(FILE* arq, vetorVars** terms, vetorVars* prim, vetorVars* reset);
void addVar(vetorVars* prim, char newLetra);
void limpar(vetorVars** terms);

int main(){
	srand(time(NULL));
	FILE* arq = fopen("gramaticas.txt","r+");
	vetorVars* prim = NULL;
	vetorVars* terms = NULL;
	vetorVars* reset = NULL;
	int nrVars, nr=0, r;
	
	guardarVariaveis(arq, &prim, &nrVars);
	prim->flag = 1; // Indicação que a primeira variavel pe inicial
	
	print(prim);
	
	if(verificarGramatica(arq))
		return -1;	
	
	if(verificarSimplificacao(arq, prim, nrVars))
		return -1;
	
	normChompsky2(arq, &terms,prim,reset);
	
	for( r = 0; r < 3; r++ ){
		limpar(&terms);
		normChompsky3(arq, &terms,prim,reset);
	}
	return 0;
}

int normChompsky2(FILE* arq, vetorVars** terms, vetorVars* prim, vetorVars* reset){
	fseek(arq, 0, SEEK_SET);
	vetorVars* auxTerms = *terms;
	int k = 0, flag1, flag2, r;
	char aux, ALL[2000], part[255], vTerms[100];
	
	do{
		for( r = 0; r < 3; r++ ){
			aux = fgetc(arq);
			k++;
		}
		do{
			flag1 = 0;
			flag2 = 0;
			while( aux != '|' && aux != ',' && aux != '\n' && aux != EOF ){
				if( aux >= 97 && aux <= 122  ){
					inserir(aux,terms,k);
					flag2 = 1;
				}
				aux = fgetc(arq);
				k++;
				flag1++;
			}
			if(flag1 == 1 && flag2 == 1){
				remover(terms);
			}
			aux = fgetc(arq);
			k++;
		}while(aux != '\n' && aux != EOF);
	}while( aux != EOF );
	
	modificar(*terms, prim, vTerms,0);
	
	reset = prim;
	flag1=1;
	while(reset != NULL){
		flag1++;
		reset=reset->prox;
	}
	
	fseek(arq, 0, SEEK_SET);
	for(r = 0; r < flag1+1; r++){
		fgets(part,255,arq);
		strcat(ALL,part);
	}
	
	fclose(arq);
	arq = fopen("norm2.txt","w+");
	
	for( r = 0 ; r < k - 1; r++ ){
		flag1 = 0;
		while( auxTerms != NULL ){
			if( r+1 == auxTerms->chave ){
				fputc(auxTerms->letra,arq);
				flag1 = 1;
			}
			auxTerms = auxTerms->prox;
		}
		auxTerms = *terms;
		if( flag1 == 0 )
			fputc(ALL[r],arq);
		if( r == k-3 )
			fputc(',',arq);
	}
	reset = *terms;
	r = 0;
	while( auxTerms != NULL ){
		if( auxTerms->flag == 0 ){
			*terms = auxTerms;
			fputc(auxTerms->letra,arq);
			
			aux = auxTerms->letra;
			while( auxTerms != NULL){
				if(auxTerms->letra == aux )
					auxTerms->flag = 1;
				auxTerms = auxTerms->prox;
			}
			auxTerms = *terms;
			
			fputc('>',arq);
			fputc(vTerms[r],arq);
			
			if( r < strlen(vTerms)-1){
				fputc(',',arq);
				fputc('\n',arq);
			}else{
				fputc('\n',arq);
				break;
			}
			r++;
		}
		auxTerms = auxTerms->prox;
	}
	*terms = reset;
}

int normChompsky3(FILE* arq, vetorVars** terms, vetorVars* prim, vetorVars* reset){
	fseek(arq, 0, SEEK_SET);
	vetorVars* auxTerms = *terms;
	int k = 0, flag1, flag2, r;
	char aux, ALL[2000], part[255], vTerms[100], temp;
	char str1[50],str2[50];
	memset(ALL, 0, sizeof(ALL));
	memset(part, 0, sizeof(part));
	
	do{
		for( r = 0; r < 3; r++ ){
			aux = fgetc(arq);
			k++;
		}
		do{
			flag1 = 0;
			while( aux != '|' && aux != ',' && aux != '\n' && aux != EOF ){
				if( aux >= 65 && aux <= 90  ){
					if( flag1 >= 1 ){
						inserir(aux,terms,k);
					}
					flag1++;
				}
				aux = fgetc(arq);
				k++;
			}
			if( flag1 > 0 && flag1 <= 2 ){
				remover(terms);
			}
			aux = fgetc(arq);
			k++;
		}while(aux != '\n' && aux != EOF);
	}while( aux != EOF );
	
	modificar(*terms, prim, vTerms,1);
	
	reset = prim;
	flag1=0;
	while(reset != NULL){
		flag1++;
		reset=reset->prox;
	}
	
	fseek(arq, 0, SEEK_SET);
	for(r = 0; r < flag1; r++){
		fgets(part,255,arq);
		strcat(ALL,part);
	}
	
	fclose(arq);
	arq = fopen("norm3.txt","w+");
	
	for( r = 0 ; r < k - 1; r++ ){
		flag1 = 0;
		while( auxTerms != NULL ){
			if( r+1 == auxTerms->chave && auxTerms->letra != temp ){
				fputc(auxTerms->letra,arq);
				//printf("[%c]",auxTerms->letra);
				temp = auxTerms->letra;
				flag1 = 1;
			}
			if( r+1 == auxTerms->chave && auxTerms->letra == temp ){
				flag1 = 1;
			}
			auxTerms = auxTerms->prox;
		}
		auxTerms = *terms;
		if( flag1 == 0 ){
			fputc(ALL[r],arq);
			//printf("{%c}",ALL[r]);
		}
		if( r == k-3 )
			fputc(',',arq);
	}
	
	reset = *terms;
	r = 0;
	while( auxTerms != NULL ){
		if( auxTerms->flag == 0 ){
			*terms = auxTerms;
			fputc(auxTerms->letra,arq);
			temp = auxTerms->letra;
			
			aux = auxTerms->letra;
			while( auxTerms != NULL){
				if(auxTerms->letra == aux )
					auxTerms->flag = 1;
				auxTerms = auxTerms->prox;
			}
			auxTerms = *terms;
			
			fputc('>',arq);
			str1[0] = vTerms[r];
			str1[1] = '\0';
			flag2 = r;
			r++;
		}else{
			str2[0] = vTerms[r];
			str2[1] = '\0';
			strcat(str2,str1);
			strcpy(str1,str2);
			if( auxTerms->prox == NULL || auxTerms->letra != auxTerms->prox->letra ){
				fputs(str1,arq);
				if( r < strlen(vTerms)-1){
					fputc(',',arq);
					fputc('\n',arq);
				}else{
					fputc('\n',arq);
					break;
				}
			}
			r++;
		}
		auxTerms = auxTerms->prox;
	}
	*terms = reset;
}

int inserirFim(char aux, vetorVars** terms, int k){
	while(*terms != NULL ){
		terms = &((*terms)->prox); 
	}
	
	vetorVars* temp = (vetorVars*)malloc(sizeof(vetorVars));
	if(temp == NULL)
		return -1;
		
	temp->letra = aux;
	temp->chave = k;
	temp->prox = NULL;
	temp->flag = 0;
	
	*terms = temp;
	return 0;
}

int inserir(char aux, vetorVars** terms, int k){
	vetorVars* temp = (vetorVars*)malloc(sizeof(vetorVars));
	if(temp == NULL)
		return -1;
		
	temp->letra = aux;
	temp->chave = k;
	temp->prox = (*terms);
	temp->flag = 0;
	
	(*terms) = temp;
	return 0;
}

int remover(vetorVars** terms){
	vetorVars* temp = (*terms);
	
	(*terms) = (*terms)->prox;
	free(temp);
	
	return 0;
}

void limpar(vetorVars** terms){
	if( *terms == NULL )
		return;
		
	vetorVars* aux = *terms;
	(*terms) = (*terms)->prox;
	free(aux);
	
	limpar(terms);
}

char* modificar(vetorVars* terms, vetorVars* prim, char t[], int sinal){
	char v[100], newLetra, auxLetra;
	vetorVars* reset = terms;
	memset(t, 0, sizeof(t));
	vetorVars *aux = prim;
	int r, i = 0, flag, check = 0;
	
	while(terms != NULL){
		flag = 0;
		if( sinal == 0 ){
			for(r = 0; r < 100; r++){
				if(terms->letra == t[r]){
					flag = 1;
					break;
				}
			}
		}
		if(flag == 0){
			aux = prim;
			newLetra = rand()%26+65;
			while(aux != NULL){
				if( aux->letra == newLetra ){
					newLetra = rand()%26+65;
					aux = prim;
				}else{
					aux = aux->prox;
				}
			}
			t[i] = terms->letra;
			v[i] = newLetra;
			i++;
			if(sinal == 0){
				terms->letra = newLetra;
				addVar(prim,newLetra);
			}else{
				if( check == 0 || terms->chave != check-1 ){
					check = terms->chave;
					terms->letra = newLetra;
					auxLetra = newLetra;
					addVar(prim,newLetra);
				}else{
					terms->letra = auxLetra; 
					check--;
				}
			}
		}else{
			terms->letra = v[r];
		}
		terms = terms->prox;
	}
	
	terms = reset;
	return t;
}

void addVar(vetorVars* prim, char newLetra){
	while( prim->prox != NULL )
		prim = prim->prox;
		
	prim->prox = (vetorVars*)malloc(sizeof(vetorVars));
	if( prim->prox == NULL )
		return;
		
	(prim->prox)->letra = newLetra;
	(prim->prox)->chave = 0;
	(prim->prox)->prox = NULL;
	(prim->prox)->flag = 0;
}

int verificarGramatica(FILE* arq){
	char aux;
	int r, n = 0;
	
	fseek(arq, 0, SEEK_SET);
	
	do{
		aux = fgetc(arq);
		while( aux != '>' ){
			n++;
			aux = fgetc(arq);
		}
		if( n > 1 ){
			printf("Nao eh uma GLC\n");
			return 1;
		}
		while( aux != ',' && aux != EOF ){
			aux = fgetc(arq);
		}
		aux = fgetc(arq);
		n = 0; 
	}while( aux != EOF );
		
	printf("Eh uma GLC\n");
	return 0;
}

int verificarSimplificacao(FILE* arq, vetorVars* prim, int nrVars ){
	vetorVars* reset = prim;
	char aux;
	int r,i;
	
	fseek(arq, 0, SEEK_SET);
	
	do{
		/* 
		* Le a variavel e a seta
		* e deixa guardado o primero conteudo do corpo
		*/
		for( r = 0; r < 3; r++ )
			aux = fgetc(arq); 
		while( aux != ',' && aux != EOF ){
			if( aux == '&'){
				r = 10;
				break;
			}
			aux = fgetc(arq);
		}
	}while( aux != EOF && r != 10 );
	
	if( r == 10 ){
		printf("Nao esta simplificada na primeira etapa.\n");
		return 1;
	}
	
	fseek(arq, 0, SEEK_SET);
	int flag = 0;
	do{
		/* 
		* Le a variavel e a seta
		* e deixa guardado o primero conteudo do corpo
		*/
		for( r = 0; r < 3; r++ )
			aux = fgetc(arq); 
		while( aux != ',' && aux != '\n' && aux != EOF){
		
			for(i = 0; i < nrVars; i++ ){
				if( aux == prim->letra ){
					i = nrVars;
					aux = fgetc(arq);
					if( aux == '|' || aux == ',' ){
						flag = 1;
						break;
					}
				}else{
					prim = prim->prox;
					if(prim == NULL)
						break;
				}
					
			}
					
			prim = reset;
				
			while(aux != '|' && aux != ',' && aux != EOF ){
				aux = fgetc(arq);
			}
				
			aux = fgetc(arq);
		}
		if( aux == ',' )
			fgetc(arq);
	}while( aux != EOF );
	
	if( flag == 1 ){
		printf("Nao esta simplificada na segunda etapa.\n");
		return 1;
	}
	
	fseek(arq, 0, SEEK_SET);
	
	flag = 0;
	do{
		/* 
		* Le a variavel e a seta
		* e deixa guardado o primero conteudo do corpo
		*/
		for( r = 0; r < 3; r++ )
			aux = fgetc(arq); 
		while( aux != ',' && aux != EOF ){
			if( aux >= 65 && aux <= 90 ){
				for(i = 0; i < nrVars; i++ ){
					if( aux == prim->letra ){
						flag = 1;
						prim->flag = 1;
					}else{
						prim = prim->prox;
					}		
				}
				prim = reset;
				if( flag == 0 ){
					printf("Nao esta simplificada na terceira etapa.\n");
					return 1;
				}
				flag = 0;
			}
			aux = fgetc(arq);
		}
	}while( aux != EOF && r != 10 );
	
	for(i = 0; i < nrVars; i++ ){
		if( prim->flag == 0 ){
			printf("%c -> Nao esta simplificada na terceira etapa!!.\n",prim->letra);
			return 1;
		}
		prim = prim->prox;
	}
	prim = reset;
	
	printf("Esta simplificada.\n");
	return 0;
}

void guardarVariaveis(FILE* arq,vetorVars** prim, int* nrVars){
	char aux;
	
	*prim = (vetorVars*)malloc(sizeof(vetorVars));
	if(*prim == NULL)
		return;
	(*prim)->prox = NULL;
	(*prim)->letra = fgetc(arq);
	(*prim)->flag = 0;
	(*prim)->chave = 0;
	*nrVars += 1;
	
	aux = fgetc(arq);
	while( aux != ',' && aux != EOF ){
		aux = fgetc(arq);
	}
	if( aux == EOF )
		return;
	
	fgetc(arq); // Ler o \n
	guardarVariaveis(arq, &((*prim)->prox),nrVars);

}

void printMax(vetorVars* prim){
	if(prim == NULL)
		return;
	printf("%c | %i \n", prim->letra, prim->chave);
	printMax(prim->prox);
}

void print(vetorVars* prim){
	if(prim == NULL)
		return;
	printf("%c\n",prim->letra);
	print(prim->prox);
}



