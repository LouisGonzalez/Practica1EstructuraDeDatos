#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>

using namespace std;

void totalMovimientos(int disco){
    int total = pow(2, disco) - 1;
    cout<<"El total de movimientos que se tuvo que realizar fue de "<<total<<" movimientos"<<endl;
}

void imprimeTablero( int *tab, int fil, int col, int ultNum ){
	int f, c;
	int i, esp;
	for( c=col-1; c >= 0; c-- ){
		for( f=0; f < fil; f++ ){
			esp = ( ultNum - tab[col*f+c] )/2;
			for( i=0; i < esp; i++ )
				printf( " " );
			for( i=0; i < tab[col*f+c]; i++ )
				printf( "*" );

			for( i=0; i < esp; i++ )
				printf( " " );
			printf( "\t" );
		};
		printf( "\n" );
	};
};

void Jugadas(int disco, int torre1, int torre2, int torre3){
    if(disco == 1){
        cout<<"Mover disco de la torre numero "<<torre1<<" hacia la torre numero"<<torre3<<endl;
    } else {
        Jugadas(disco-1, torre1, torre3, torre2);
        cout<<"Mover disco de la torre numero "<<torre1<<" hacia la torre numero"<<torre3<<endl;
        Jugadas(disco-1, torre2, torre1, torre3);
    }

}

void mueveDisco( int *tab, int fil, int col, int ultNum, int filOrig, int filDest ){
	int noColumnas=col-1, noColumnas2=col-1;
	while( noColumnas >= 0  &&  tab[col*filOrig+noColumnas] == 0 ){
		noColumnas--;
	};
	if( noColumnas < 0 )
		noColumnas = 0;
	while( noColumnas2 >= 0  &&  tab[col*filDest+noColumnas2] == 0 ){
		noColumnas2--;
	};
	tab[col*filDest+noColumnas2+1] = tab[col*filOrig+noColumnas];
	tab[col*filOrig+noColumnas] = 0;

	imprimeTablero( tab, fil, col, ultNum );
};

void empezarMovimientos( int *tab, int filtro, int col, int disco, int ultNum, int O, int A, int D, int torre1, int torre2, int torre3 ){
	if( disco==1 ){
		system("clear");
		mueveDisco( tab, filtro, col, ultNum, O, D );
		if(col<=5) system("sleep 0.8"); else if(col<=10) system("sleep 0.3"); else if(col<=15) system("sleep 0.06"); else if(col>15) system("sleep 0.02");
	}else{
		empezarMovimientos( tab, filtro, col, disco-1, ultNum, O, D, A, torre1, torre2, torre3 );
		system("clear");
		mueveDisco( tab, filtro, col, ultNum, O, D );
		if(col<=5) system("sleep 0.8"); else if(col<=10) system("sleep 0.3"); else if(col<=15) system("sleep 0.06"); else if(col>15) system("sleep 0.02");
		empezarMovimientos( tab, filtro, col, disco-1, ultNum, A, O, D , torre1, torre2, torre3);
	};

};

main(){
	int fil=3, col, *tablero = NULL;
	int f, c, disc=1, ultNum;
    int Torre1= 1, Torre2= 2, Torre3 = 3;
	printf( "Indique el numero de discos: " );
	scanf( "%i", &col );
    Jugadas(col, Torre1, Torre2, Torre3);
	tablero = (int *)malloc( sizeof(int)*fil*col );
	for( f=0; f < fil; f++ )
		for( c=col-1; c >= 0; c-- )
			if( f==0 ){
				tablero[col*f+c] = disc;
				disc+=2;
            }
			else
				tablero[col*f+c] = 0;
	ultNum = disc;
	system("clear");
	imprimeTablero( tablero, fil, col, ultNum );
	system("sleep 1");
	empezarMovimientos( tablero, fil, col, col, ultNum, 0, 1, 2, Torre1, Torre2, Torre3 );
	Jugadas(col, Torre1, Torre2, Torre3);
	totalMovimientos(col);

};
