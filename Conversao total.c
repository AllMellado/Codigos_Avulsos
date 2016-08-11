#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

long long int MaiorQue10Recebidor();
long long int MenorQue10();
void MaiorQue10Entregador();
void manual();

char nrNominal[100];
int from, to, nrChars, ConvTotal;

int main(){
    setlocale(LC_ALL,"");
    int end = 0, resto, r, s, repeticao, nrDigitos;
    long long int nrRecebido, auxRecebido, nrDecimal, nrConvertido, x;
    
    do{ 
        nrRecebido = 0, ConvTotal = 0, to = 1;
        do{
            printf("AVISO!!! INSERIR VALORES NAO INTEIROS RESULTARA EM ERRO.\n"); 
            printf("---------------------------------------------------------------------\n");
            printf("Para sair, digite (0)\n");
            printf("Para ver a tabela de simbolos, digite (1)\n");
            printf("Para ativar a conversão para todas as bases, digite (100)\n");
            printf("\nPara escolher a BASE INICIAL:\nDigite qualquer numero entre Binario (2) e Pentoctogesimal (85).\n");
            printf("----------------------------\n");
            printf("Digite a opção desejada: ");
            scanf("%d", &from);
            system("cls");
            if ( from == 1 ){
                manual(); 
                getch();
                system("cls");
            }
            if ( from == 100 ){
                ConvTotal = 1;
                from = 1;
                to = 2;
                system("cls");
            }
        }while( from == 1 ); 
        
        
        if ( from != 0 && ConvTotal != 1 ){
            do{
                printf("AVISO!!! INSERIR VALORES NAO INTEIROS RESULTARA EM ERRO.\n");
                printf("---------------------------------------------------------------------\n");
                printf("Digite Zero (0) para sair\n");
                printf("Para ver os valores do simbolos digite (1)\n");
                printf("\nPara escolher a BASE FINAL:\nDigite qualquer numero entre Binario (2) e Pentoctogesimal (85).\n"); 
                printf("----------------------------\n");
                printf("Digite a opção desejada: ");
                scanf("%d", &to);
                system("cls");
                if ( to == 1 ){
                    manual();
                    getch();
                    system("cls");
                }
            }while( to == 1 );
        }
        if ( from > 85 || to > 85 || from < 0 || to < 0 ){
            printf("Opçao Invalida");
            getch();
            system("cls");
        }else{
            if ( to != 0 && from != 0 ){
                if ( from > 10 ){
                    printf("AVISO!!! INSERIR VALORES NAO INTEIROS RESULTARA EM ERRO.\n");
                    printf("---------------------------------------------------------------------\n");
                    printf("Digite o Numero que sera convertido: ");
                    scanf(" %s", &nrNominal);
                    nrChars = strlen(nrNominal);
                    system("cls");
                    printf("\nCONVERSÃO COMPLETA\n");
                    printf("\nOriginal da Base %d: %s\n\n", from, nrNominal );
                }else{
                    printf("AVISO!!! INSERIR VALORES NAO INTEIROS RESULTARA EM ERRO.\n");
                    printf("---------------------------------------------------------------------\n");
                    printf("Digite o Numero que sera convertido: ");
                    scanf("%lli", &nrRecebido);
                    system("cls");
                    printf("\nCONVERSÃO COMPLETA\n");
                    printf("\nOriginal da Base %d: %lli\n\n", from, nrRecebido );
                }
                
                if ( ConvTotal == 1 ){
                    repeticao = 84;
                }else
                    repeticao = 1;
                    
                auxRecebido = nrRecebido;
                for ( s = 0 ; s < repeticao ; s++ ){
                    
                    nrRecebido = auxRecebido;
                    nrDecimal = 0;
                    nrConvertido = 0;
                    x = 1;
                    
                    if ( from == 10 || to == 10 ){
                        if ( from > 10 ){
                            nrConvertido = MaiorQue10Recebidor ( nrNominal );     
                        }else{
                            if ( to > 10 ){
                                MaiorQue10Entregador ( nrRecebido );
                            }else{
                                nrConvertido = MenorQue10( nrRecebido, 0 );
                            }
                        }
                    }else{
                        if ( from < 10 && to < 10 ){    
                            nrDecimal = MenorQue10( nrRecebido, 1 );
                            nrConvertido = MenorQue10( nrDecimal, 2 );
                        }else{
                            if ( from > 10 && to < 10 ){
                                nrDecimal = MaiorQue10Recebidor ( nrNominal );
                                nrConvertido = MenorQue10( nrDecimal, 2 );
                            }else{
                                if ( from < 10 && to > 10 ){
                                    nrDecimal = MenorQue10( nrRecebido, 1 );
                                    MaiorQue10Entregador ( nrDecimal );
                                }else{
                                    nrDecimal = MaiorQue10Recebidor ( nrNominal );
                                    MaiorQue10Entregador ( nrDecimal );
                                }
                            }
                        }
                    
                    }
                    if ( to <= 10 ){           
                        printf("Convertido para Base ");
                        if ( abs( to - 100 ) > 90 )
                            printf(" %d", to);
                        else
                            printf("%d", to);
                        printf(": %lli", nrConvertido);
                        nrDigitos = 0;
                        do{
                            nrDigitos++;
                            nrConvertido = nrConvertido / 10;
                        }while ( nrConvertido != 0 );
                        for ( r = 0 ; r < abs( nrDigitos - 8 ) ; r++ )
                            printf(" ");
                    }else{
                        printf("Convertido para Base %d: ", to);
                        nrDigitos = 0;
                        for ( r = nrChars - 1; r >= 0 ; r-- ){
                            printf("%c", nrNominal[r]);
                            nrDigitos++;
                        }
                        for ( r = 0 ; r < abs( nrDigitos - 8 ) ; r++ )
                            printf(" ");
                    }
                    if ( s % 3 == 0 )
                        printf("\n");
                    to++;
                }
                printf("\n\nAperte qualquer tecla para continuar.");
                getch();
                system("cls");
            }
        }
    }while( from != 0 && to != 0 );
    
    return 1;
}

long long int MenorQue10( long long int numero, int flag ){
    long long int nrRecebido, nrDecimal, nrConvertido, x = 1; 
    int resto;
    
    if( flag == 0 ){   
        nrRecebido = numero;
        nrConvertido = 0;
        do{
            resto = nrRecebido % to;
            nrConvertido = nrConvertido + resto*x;
            x = x*from;
            nrRecebido = nrRecebido / to;
        }while( nrRecebido > 0 );
    }else{
        if( flag == 1 ){
            nrRecebido = numero;
            nrDecimal = 0;
            do{
                resto = nrRecebido % 10;
                nrDecimal = nrDecimal + resto*x;
                x = x*from;
                nrRecebido = nrRecebido / 10;
            }while( nrRecebido > 0 );
        }else{
            nrDecimal = numero;
            nrConvertido = 0;
            do{
                resto = nrDecimal % to;
                nrConvertido = nrConvertido + resto*x;
                x = x*10;
                nrDecimal = nrDecimal / to;
            }while( nrDecimal > 0 );
        }
    }
    
    if( flag == 1 ){
        return nrDecimal;
    }else{
        return nrConvertido;
    }
}

long long int MaiorQue10Recebidor ( char nrNominal[100] ){
    int r, Unidades[100];
    long long int nrDecimal = 0, x = 1;
   
    for ( r = 0 ; r < nrChars ; r++ ){
        if ( isdigit( nrNominal[r] ) == 0 ){
            switch ( nrNominal[r] ){
                case 'A' : Unidades[r] = 10;
                        break;
                case 'B' : Unidades[r] = 11;
                        break;
                case 'C' : Unidades[r] = 12;
                        break;
                case 'D' : Unidades[r] = 13;
                        break;
                case 'E' : Unidades[r] = 14;
                        break;
                case 'F' : Unidades[r] = 15;
                        break;
                case 'G' : Unidades[r] = 16;
                        break;
                case 'H' : Unidades[r] = 17;
                        break;
                case 'I' : Unidades[r] = 18;
                        break;
                case 'J' : Unidades[r] = 19;
                        break;
                case 'K' : Unidades[r] = 20;
                        break;
                case 'L' : Unidades[r] = 21;
                        break;
                case 'M' : Unidades[r] = 22;
                        break;
                case 'N' : Unidades[r] = 23;
                        break;
                case 'O' : Unidades[r] = 24;
                        break;
                case 'P' : Unidades[r] = 25;
                        break;
                case 'Q' : Unidades[r] = 26;
                        break;
                case 'R' : Unidades[r] = 27;
                        break;
                case 'S' : Unidades[r] = 28;
                        break;
                case 'T' : Unidades[r] = 29;
                        break;
                case 'U' : Unidades[r] = 30;
                        break;
                case 'V' : Unidades[r] = 31;
                        break;
                case 'W' : Unidades[r] = 32;
                        break;
                case 'X' : Unidades[r] = 33;
                        break;
                case 'Y' : Unidades[r] = 34;
                        break;
                case 'Z' : Unidades[r] = 35;
                        break;
                case 'a' : Unidades[r] = 36;
                        break;
                case 'b' : Unidades[r] = 37;
                        break;
                case 'c' : Unidades[r] = 38;
                        break;
                case 'd' : Unidades[r] = 39;
                        break;
                case 'e' : Unidades[r] = 40;
                        break;
                case 'f' : Unidades[r] = 41;
                        break;
                case 'g' : Unidades[r] = 42;
                        break;
                case 'h' : Unidades[r] = 43;
                        break;
                case 'i' : Unidades[r] = 44;
                        break;
                case 'j' : Unidades[r] = 45;
                        break;
                case 'k' : Unidades[r] = 46;
                        break;
                case 'l' : Unidades[r] = 47;
                        break;
                case 'm' : Unidades[r] = 48;
                        break;
                case 'n' : Unidades[r] = 49;
                        break;
                case 'o' : Unidades[r] = 50;
                        break;
                case 'p' : Unidades[r] = 51;
                        break;
                case 'q' : Unidades[r] = 52;
                        break;
                case 'r' : Unidades[r] = 53;
                        break;
                case 's' : Unidades[r] = 54;
                        break;
                case 't' : Unidades[r] = 55;
                        break;
                case 'u' : Unidades[r] = 56;
                        break;
                case 'v' : Unidades[r] = 57;
                        break;
                case 'w' : Unidades[r] = 58;
                        break;
                case 'x' : Unidades[r] = 59;
                        break;
                case 'y' : Unidades[r] = 60;
                        break;
                case 'z' : Unidades[r] = 61;
                        break;
                case '.' : Unidades[r] = 62;
                        break;
                case '-' : Unidades[r] = 63;
                        break;
                case ':' : Unidades[r] = 64;
                        break;
                case '+' : Unidades[r] = 65;
                        break;
                case '=' : Unidades[r] = 66;
                        break;
                case '^' : Unidades[r] = 67;
                        break;
                case '!' : Unidades[r] = 68;
                        break;
                case '/' : Unidades[r] = 69;
                        break;
                case '*' : Unidades[r] = 70;
                        break;
                case '?' : Unidades[r] = 71;
                        break;
                case '&' : Unidades[r] = 72;
                        break;
                case '<' : Unidades[r] = 73;
                        break;
                case '>' : Unidades[r] = 74;
                        break;
                case '(' : Unidades[r] = 75;
                        break;
                case ')' : Unidades[r] = 76;
                        break;
                case '[' : Unidades[r] = 77;
                        break;
                case ']' : Unidades[r] = 78;
                        break;
                case '{' : Unidades[r] = 79;
                        break;
                case '}' : Unidades[r] = 80;
                        break;
                case '@' : Unidades[r] = 81;
                        break;
                case '~' : Unidades[r] = 82;
                        break;
                case '$' : Unidades[r] = 83;
                        break;
                case '#' : Unidades[r] = 84;
                        break;
                default : printf("Simbolo não encontrado\n");
            }
        }else
            Unidades[r] = nrNominal[r] - '0';
    }
    if ( ConvTotal == 1 && to > 11 ){
        for ( r = 0 ; r < nrChars ; r++ ){
            nrDecimal = nrDecimal + Unidades[r]*x;
            x = x*(to - 1);
        }
    }else{
        for ( r = nrChars - 1 ; r >= 0 ; r-- ){
            nrDecimal = nrDecimal + Unidades[r]*x;
            x = x*from;
        }
    }
    return nrDecimal;
}

void MaiorQue10Entregador ( long long int nrRecebido ){
    int r = 0, resto;
    nrChars = 0;
    do{
        nrChars++;
        resto = nrRecebido % to;
        nrRecebido = nrRecebido / to;
        if ( resto < 10 ){
            nrNominal[r] = resto + '0';
        }else{
            switch ( resto ){
                        case 10 : nrNominal[r] = 'A';
                            break;
                        case 11 : nrNominal[r] = 'B';
                            break;
                        case 12 : nrNominal[r] = 'C';
                            break;
                        case 13 : nrNominal[r] = 'D';
                            break;
                        case 14 : nrNominal[r] = 'E';
                            break;
                        case 15 : nrNominal[r] = 'F';
                            break;
                        case 16 : nrNominal[r] = 'G';
                            break;
                        case 17 : nrNominal[r] = 'H';
                            break;
                        case 18 : nrNominal[r] = 'I';
                            break;
                        case 19 : nrNominal[r] = 'J';
                            break;
                        case 20 : nrNominal[r] = 'K';
                            break;
                        case 21 : nrNominal[r] = 'L';
                            break;
                        case 22 : nrNominal[r] = 'M';
                            break;
                        case 23 : nrNominal[r] = 'N';
                            break;
                        case 24 : nrNominal[r] = 'O';
                            break;
                        case 25 : nrNominal[r] = 'P';
                            break;
                        case 26 : nrNominal[r] = 'Q';
                            break;
                        case 27 : nrNominal[r] = 'R';
                            break;
                        case 28 : nrNominal[r] = 'S';
                            break;
                        case 29 : nrNominal[r] = 'T';
                            break;
                        case 30 : nrNominal[r] = 'U';
                            break;
                        case 31 : nrNominal[r] = 'V';
                            break;
                        case 32 : nrNominal[r] = 'W';
                            break;
                        case 33 : nrNominal[r] = 'X';
                            break;
                        case 34 : nrNominal[r] = 'Y';
                            break;
                        case 35 : nrNominal[r] = 'Z';
                            break;
                        case 36 : nrNominal[r] = 'a';
                            break;
                        case 37 : nrNominal[r] = 'b';
                            break;
                        case 38 : nrNominal[r] = 'c';
                            break;
                        case 39 : nrNominal[r] = 'd';
                            break;
                        case 40 : nrNominal[r] = 'e';
                            break;
                        case 41 : nrNominal[r] = 'f';
                            break;
                        case 42 : nrNominal[r] = 'g';
                            break;
                        case 43 : nrNominal[r] = 'h';
                            break;
                        case 44 : nrNominal[r] = 'u';
                            break;
                        case 45 : nrNominal[r] = 'j';
                            break;
                        case 46 : nrNominal[r] = 'k';
                            break;
                        case 47 : nrNominal[r] = 'l';
                            break;
                        case 48 : nrNominal[r] = 'm';
                            break;
                        case 49 : nrNominal[r] = 'n';
                            break;
                        case 50 : nrNominal[r] = 'o';
                            break;
                        case 51 : nrNominal[r] = 'p';
                            break;
                        case 52 : nrNominal[r] = 'q';
                            break;
                        case 53 : nrNominal[r] = 'r';
                            break;
                        case 54 : nrNominal[r] = 's';
                            break;
                        case 55 : nrNominal[r] = 't';
                            break;
                        case 56 : nrNominal[r] = 'u';
                            break;
                        case 57 : nrNominal[r] = 'v';
                            break;
                        case 58 : nrNominal[r] = 'w';
                            break;
                        case 59 : nrNominal[r] = 'x';
                            break;
                        case 60 : nrNominal[r] = 'y';
                            break;
                        case 61 : nrNominal[r] = 'z';
                            break;
                        case 62 : nrNominal[r] = '.';
                            break;
                        case 63 : nrNominal[r] = '-';
                            break;
                        case 64 : nrNominal[r] = ':';
                            break;
                        case 65 : nrNominal[r] = '+';
                            break;
                        case 66 : nrNominal[r] = '=';
                            break;
                        case 67 : nrNominal[r] = '^';
                            break;
                        case 68 : nrNominal[r] = '!';
                            break;
                        case 69 : nrNominal[r] = '/';
                            break;
                        case 70 : nrNominal[r] = '*';
                            break;
                        case 71 : nrNominal[r] = '?';
                            break;
                        case 72 : nrNominal[r] = '&';
                            break;
                        case 73 : nrNominal[r] = '<';
                            break;
                        case 74 : nrNominal[r] = '>';
                            break;
                        case 75 : nrNominal[r] = '(';
                            break;
                        case 76 : nrNominal[r] = ')';
                            break;
                        case 77 : nrNominal[r] = '[';
                            break;
                        case 78 : nrNominal[r] = ']';
                            break;
                        case 79 : nrNominal[r] = '{';
                            break;
                        case 80 : nrNominal[r] = '}';
                            break;
                        case 81 : nrNominal[r] = '@';
                            break;
                        case 82 : nrNominal[r] = '~';
                            break;
                        case 83 : nrNominal[r] = '$';
                            break;
                        case 84 : nrNominal[r] = '#';
                            break;
                        default : printf("Opcao Indisponível.\n");
                    }
        }
        r++;
    }while ( nrRecebido > 0 );;
}

void manual(){
    
    printf(" \n\n| 10 -> A | 28 -> S | 46 -> k | 64 -> : | 82 -> ~ |\n");
    printf("| 11 -> B | 29 -> T | 47 -> l | 65 -> + | 83 -> & |\n");
    printf("| 12 -> C | 30 -> U | 48 -> m | 66 -> = | 84 -> # |\n");
    printf("| 13 -> D | 31 -> V | 49 -> n | 67 -> ^ |\n");
    printf("| 14 -> E | 32 -> W | 50 -> o | 68 -> ! |\n");
    printf("| 15 -> F | 33 -> X | 51 -> p | 69 -> / |\n");
    printf("| 16 -> G | 34 -> Y | 52 -> q | 70 -> * |\n");
    printf("| 17 -> H | 35 -> Z | 53 -> r | 71 -> ? |\n");
    printf("| 18 -> I | 36 -> a | 54 -> s | 72 -> & |\n");
    printf("| 19 -> J | 37 -> b | 55 -> t | 73 -> < |\n");
    printf("| 20 -> K | 38 -> c | 56 -> u | 74 -> > |\n");
    printf("| 21 -> L | 39 -> d | 57 -> v | 75 -> ( |\n");
    printf("| 22 -> M | 40 -> e | 58 -> w | 76 -> ) |\n");
    printf("| 23 -> N | 41 -> f | 59 -> x | 77 -> [ |\n"); 
    printf("| 24 -> O | 42 -> g | 60 -> y | 78 -> ] |\n");
    printf("| 25 -> P | 43 -> h | 61 -> z | 79 -> { |\n");
    printf("| 26 -> Q | 44 -> i | 62 -> . | 80 -> } |\n");
    printf("| 27 -> R | 45 -> j | 63 -> - | 81 -> @ |\n");
}

