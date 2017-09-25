#include <stdio.h>
#include <stdlib.h>

int main(){
	FILE* arq;
	int x, y = 0;
	char c;
	
	/*
	* Criar um arquivo txt na mesma pasta que esta algoritomo.
	* Nomear o arquivo txt como "palavras" sem aspas.
	* Inserir as plavras a serem verificaas neste arquivo txt.
	*/
	arq = fopen("palavras.txt","r"); 
	
	while(x != EOF){ //Rotina roda ate o fim do arquivo lendo char por char.
		printf("\nEstado 1 -");
		
		c = fgetc(arq);
		x = (int)c;
		switch(x){
			case 117: //u
				printf("%c-> Estado 4 -",c);
				
				c = fgetc(arq);
				x = (int)c;
				switch(x){
					case 117: //u
						printf("%c-> Estado 6 -",c);
						
						c = fgetc(arq);
						x = (int)c;
						if( x == 83 ){ //S
							printf("%c-> Estado 7 -",c);
								
							c = fgetc(arq);
							x = (int)c;
							if( x == 117 ){ //u
								printf("%c-> Estado 8 -",c);
							
								c = fgetc(arq);
								x = (int)c;
								if( x == 65 ){
									printf("%c-> Estado 10 -",c);
											
									x = (int)fgetc(arq);
									if( x == 10 || x == EOF){
										printf("> Palavra Aceita\n",c);
									}
								}else{
									printf("%c-> Palavra Rejeitada | Transicao inexistente.",c); 
								}
							}else{
								if( x == 10 || x == EOF ){
									printf("> Palavra Rejeitada | Estado atual nao eh final.");
								}else{
									printf("%c-> Palavra Rejeitada | Transicao inexistente.",c);
								}
							}					
						}else{
							if( x == 10 || x == EOF ){
								printf("> Palavra Rejeitada | Estado atual nao eh final.");
							}else{
								printf("%c-> Palavra Rejeitada | Transicao inexistente.",c);
							}
						}
					break;
					
					case 105: //i
						printf("%c-> Estado 5 -",c);
						
						x = (int)fgetc(arq);
						if( x == 117 ){
							printf("%c-> Estado 9 -",c);
						
							x = (int)fgetc(arq);
							switch(x){
								case 65: //A
									printf("%c-> Estado 10 -",c);
												
									x = (int)fgetc(arq);
									if( x == 10 || x == EOF){
										printf("> Palavra Aceita\n",c);
									}
								break;
									
								case 68: //D
									printf("%c-> Estado 11 ",c);
												
									x = (int)fgetc(arq);
									if( x == 10 || x == EOF){
										printf("> Palavra Aceita\n",c);
									}
								break;
									
								default: printf("%c-> Palavra Rejeitada | Transicao inexistente.",c);
									
							}
						}else{
							if( x == 10 || x == EOF ){
								printf("> Palavra Rejeitada | Estado atual nao eh final.");
							}else{
								printf("%c-> Palavra Rejeitada | Transicao inexistente.",c);
							}
						}
					break;
					
					default: if( x == 10 || x == EOF ){
								printf("> Palavra Rejeitada | Estado atual nao eh final.");
							}else{
								printf("%c-> Palavra Rejeitada | Transicao inexistente.",c);
							}
				}
			break;
			
			case 105: //i
				printf("%c-> Estado 2 -",c);
				
				c = fgetc(arq);
				x = (int)c;
				if( x == 117 ){
					printf("%c-> Estado 3 -",c);
				
					c = fgetc(arq);
					x = (int)c;
					switch(x){
						case 65: //A
							printf("%c-> Estado 10 ",c);
											
							x = (int)fgetc(arq);
							if( x == 10 || x == EOF){
								printf("> Palavra Aceita\n",c);
							}							 
						break;
							
						case 68: //D
							printf("%c-> Estado 11 ",c);
											
							x = (int)fgetc(arq);
							if( x == 10 || x == EOF){
								printf("> Palavra Aceita\n",c);
							}							
						break;
							
						default: printf("%c-> Palavra Rejeitada | Transicao inexistente.",c);
					}
				}else{
					if( x == 10 || x == EOF ){
						printf("> Palavra Rejeitada | Estado atual nao eh final.");
					}else{
						printf("%c-> Palavra Rejeitada | Transicao inexistente.",c);
					}
				}			
			break;
			
			case 106: //j
				printf("%c-> Estado 13 -",c);
				
				c = fgetc(arq);
				x = (int)c;
				switch(x){
					case 117: //u
						printf("%c-> Estado 14 -",c);
				
						c = fgetc(arq);
						x = (int)c;		
						switch(x){
							case 65: //A
								printf("%c-> Estado 10 -",c);
						
								x = (int)fgetc(arq);
								if( x == 10 || x == EOF){
									printf("> Palavra Aceita\n",c);
								}
							break;
	
							case 68: //D
								printf("%c-> Estado 15 -",c);
						
								c = fgetc(arq);
								x = (int)c;
								if( x == 117 ){
									printf("%c-> Estado 16 -",c);
						
									c = fgetc(arq);
									x = (int)c;
									if( x == 117 ){
										printf("%c-> Estado 18 -",c);
						
										c = fgetc(arq);
										x = (int)c;
										if( x == 65 ){
											printf("%c-> Estado 10 -",c);
						
											x = (int)fgetc(arq);
											if( x == 10 || x == EOF){
												printf("> Palavra Aceita\n",c);
											}
										}else{
											printf("%c-> Palavra Rejeitada | Transicao inexistente.",c);
										}
									}else{
										if( x == 10 || x == EOF ){
											printf("> Palavra Rejeitada | Estado atual nao eh final.");
										}else{
											printf("%c-> Palavra Rejeitada | Transicao inexistente.",c);
										}
									}
								}else{
									if( x == 10 || x == EOF ){
										printf("> Palavra Rejeitada | Estado atual nao eh final.");
									}else{
										printf("%c-> Palavra Rejeitada | Transicao inexistente.",c);
									}
								}
							break;
							
							default: if( x == 10 || x == EOF ){
										printf("> Palavra Rejeitada | Estado atual nao eh final.");
									}else{
										printf("%c-> Palavra Rejeitada | Transicao inexistente.",c);
									}
						}		
					break;
					
					case 105: //i
						printf("%c-> Estado 17 -",c);
				
						c = fgetc(arq);
						x = (int)c;
						switch(x){
							case 65: //A
								printf("%c-> Estado 10 -",c);
						
								x = (int)fgetc(arq);
								if( x == 10 || x == EOF){
									printf("> Palavra Aceita\n",c);
								}
							break;
							
							case 68: //D
								printf("%c-> Estado 11 -",c);
						
								x = (int)fgetc(arq);
								if( x == 10 || x == EOF){
									printf("> Palavra Aceita\n",c);
								}
							break;
							
							default: printf("%c-> Palavra Rejeitada | Transicao inexistente.",c);
						}
					break;
						
					default: if( x == 10 || x == EOF ){
								printf("> Palavra Rejeitada | Estado atual nao eh final.");
							}else{
								printf("%c-> Palavra Rejeitada | Transicao inexistente.",c);
							}
				}			
			break;
			
			case 107: //k
				printf("%c-> Estado 12 -",c);
				
				c = fgetc(arq);
				x = (int)c;
				if(x == 117 ){
					printf("%c-> Estado 19 -",c);
				
					c = fgetc(arq);
					x = (int)c;
					if( x == 68 ){
						printf("%c-> Estado 11 -",c);
						
						x = (int)fgetc(arq);
						if( x == 10 || x == EOF){
							printf("> Palavra Aceita\n",c);
						}
					}else{
						printf("%c-> Palavra Rejeitada | Transicao inexistente.",c);
					}
				}else{
					if( x == 10 || x == EOF ){
						printf("> Palavra Rejeitada | Estado atual nao eh final.");
					}else{
						printf("%c-> Palavra Rejeitada | Transicao inexistente.",c);
					}
				}
			break;
			
			case 108: //l
				printf("%c-> Estado 23 -",c);
				
				c = fgetc(arq);
				x = (int)c;
				if( x == 68 ){
					printf("%c-> Estado 11 -",c);
						
					x = (int)fgetc(arq);
					if( x == 10 || x == EOF){
						printf("> Palavra Aceita\n",c);
					}
				}else{
					printf("%c-> Palavra Rejeitada | Transicao inexistente.",c);
				}
			break;
			
			case 68: //D
				printf("%c-> Estado 20 -",c);
				
				c = fgetc(arq);
				x = (int)c;
				switch(x){
					case 105: //i
						printf("%c-> Estado 21 -",c);
				
						c = fgetc(arq);
						x = (int)c;
						if( x == 117 ){
							printf("%c-> Estado 22 -",c);
				
							c = fgetc(arq);
							x = (int)c;
							switch(x){
								case 65: //A
									printf("%c-> Estado 10 -",c);
						
									x = (int)fgetc(arq);
									if( x == 10 || x == EOF){
										printf("> Palavra Aceita\n",c);
									}
								break;
									
								case 68: //D
									printf("%c-> Estado 11 -",c);
						
									x = (int)fgetc(arq);
									if( x == 10 || x == EOF){
										printf("> Palavra Aceita\n",c);
									}
								break;
									
								default: printf("%c-> Palavra Rejeitada | Transicao inexistente.",c);
							}
						}else{
							if( x == 10 || x == EOF ){
								printf("> Palavra Rejeitada | Estado atual nao eh final.");
							}else{
								printf("%c-> Palavra Rejeitada | Transicao inexistente.",c);
							}
						}
					break;
					
					case 108: //l
						printf("%c-> Estado 11 -",c);
						
						x = (int)fgetc(arq);
						if( x == 10 || x == EOF){
							printf("> Palavra Aceita\n",c);
						}
					break;
					
					default: printf("%c-> Palavra Rejeitada | Transicao inexistente.",c);
				}
			break;
			
			case 65: //A
				printf("%c-> Estado 24 -",c);
				
				c = fgetc(arq);
				x = (int)c;
				switch(x){
					case 117: //u
						printf("%c-> Estado 25 -",c);
				
						c = fgetc(arq);
						x = (int)c;
						switch(x){
							case 83: //S
								printf("%c-> Estado 27 -",c);
				
								c = fgetc(arq);
								x = (int)c;
								switch(x){
									case 105: //i
										printf("%c-> Estado 26 -",c);
				
										c = fgetc(arq);
										x = (int)c;
										switch(x){
											case 68: //D
												printf("%c-> Estado 11 -",c);
						
												x = (int)fgetc(arq);
												if( x == 10 || x == EOF){
													printf("> Palavra Aceita\n",c);
												}
											break;
											
											default: printf("%c-> Palavra Rejeitada | Transicao inexistente.",c);
										}
									break;
									
									default: if( x == 10 || x == EOF ){
												printf("> Palavra Rejeitada | Estado atual nao eh final.");
											}else{
												printf("%c-> Palavra Rejeitada | Transicao inexistente.",c);
											}
								}
							break;
							
							case 105: //i
								printf("%c-> Estado 26 -",c);
				
								c = fgetc(arq);
								x = (int)c;
								switch(x){
									case 68: //D
										printf("%c-> Estado 11 -",c);
						
										x = (int)fgetc(arq);
										if( x == 10 || x == EOF){
											printf("> Palavra Aceita\n",c);
										}
									break;
											
									default: printf("%c-> Palavra Rejeitada | Transicao inexistente.",c);
								}
							break;
							
							case 65: //A
								printf("%c-> Estado 10 -",c);
						
								x = (int)fgetc(arq);
								if( x == 10 || x == EOF){
									printf("> Palavra Aceita\n",c);
								}
							break;
							
							default: printf("%c-> Palavra Rejeitada | Transicao inexistente.",c);
						}
					break;
					
					case 108: //l
						printf("%c-> Estado 10 -",c);
						
						x = (int)fgetc(arq);
						if( x == 10 || x == EOF){
							printf("> Palavra Aceita\n",c);
						}
					break;
					
					default: printf("%c-> Palavra Rejeitada | Transicao inexistente.",c);
				}
			break;
			
			default: if( x == 10 || x == EOF ){
						printf("> Palavra Rejeitada | Estado atual nao eh final.");
					}else{
						printf("%c-> Palavra Rejeitada | Transicao inexistente.",c);
					}
		}
		/*
		* Rotina que le o resto da palavra caso ela tenha sido rejeitado antes de seu fim.
		*/
		while(x != 10 && x != EOF){ 
			x = (int)fgetc(arq);
		}
	}
	fclose(arq);
	return 0;
}
