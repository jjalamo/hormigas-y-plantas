#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include <alloc.h>
#include <conio.h>
#include <graphics.h>
#include <math.h>
#include "c:\clase\ia\2004\haciendo\hpl\plantas.cpp"

//**************** DEFINICION DE CONSTANTES
#define NEGRO 0
#define AZUL 1
#define VERDE 2
#define CYAN 3
#define ROJO 4
#define ROSA 5
#define MARRON 6
#define GRIS_CLARO 7
#define GRIS 8
#define AZUL_CLARO 9
#define VERDE_CLARO 10
#define CYAN_CLARO 11
#define ROJO_CLARO 12
#define ROSA_CLARO 13
#define AMARILLO 14
#define BLANCO 15

#define REGAR 1
#define LUCHAR 2
#define REPRODUCIRSE 3

#define LARGO 40
#define ANCHO 40
#define MAXHORM 500
#define MAXPLAN 100
#define MAXBLOQ 300
//************************************

//**************** ESTRUCTURAS
struct datsimu_rep {
  int ciclosdianoche;
  int dia;
  int noche;
  int temperatura;
  int cicloscrearmuros;
  int cicloseliminarmuros;
  int longitudmuros;
  int nummuros;
  int cicloscrearplantas;
  int nummaxplantas;
  int aguaplantas;
  int numplantas;
  int perdenergia;
  int indmutacion;
  int nhazul;
  int nhcyan;
  int nhrojo;
  int nhamarillo;
  int nhblanco;
}; typedef struct datsimu_rep datsimu;


//**************** CABECERAS DE FUNCIONES
void crear_simulacion();
void iniciar_modo_grafico();
void dibujar_entorno();
void cuadrado(int x1, int y1, int x2, int y2, int color);
void dibujar_hormiga(int posx, int posy, int color);
void dibujar_planta(int posx, int posy, int color);
void dibujar_muro(int posx, int posy, int color);
void dibujar_linea_temperatura(int posx, int color);
void distribuir_elementos();
void crearhormigas(int especie, int num);
void simulacion();
int moverhormiga();
void iniciar_matriz();
void crearplantas(int num);
void comprobarhp();
int seleccionar_accion(int e, int p, int h);
void comprobar_plantas_comestibles();
void comer_planta();
void regar();
void buscar_posicion_libre(int x, int y, int *rx, int *ry);
void reproducirse();
void luchar();
void matar_hormiga(hormigap hor);
void clima();
void crearmuros(int num);
void destruirmuros();
//************************************

//**************** VARIABLES GLOBALES
datsimu simudat;
listam listamuros;
lplanta listaplantas;
lhormigap listahormigas;
hormigap hormigact;
int temp;
int dianoche=1;
int nplantasinm;
int nplantasma;
int matcomp[3][15];
int ppx;
int ppy;
int hpx;
int hpy;
int velocidad=9;
int nacimientos=0;
int muertes=0;
int mutaciones=0;
//************************************


//**************** PROGRAMA PRINCIPAL
void main() {
  int op;

  clrscr();
  listamuros=crear_listam();
  listaplantas=crear_listap();
  listahormigas=crear_listahp();
  iniciar_matriz();
  randomize();

  crear_simulacion();
  iniciar_modo_grafico();
  dibujar_entorno();
  distribuir_elementos();
  gotoxy(18,24);
  printf("Pulsa C para comenzar");
  op=0;
  while( (op!='c') && (op!='C') ) {
    op=getch();
  }
  gotoxy(18,24);
  printf("                     ");
  simulacion();
  hormigact=NULL;
  destruir_listam(&listamuros);
  destruir_listap(&listaplantas);
  destruir_listahp(&listahormigas);
  restorecrtmode();
  clrscr();
}
//************************************


//**************** DESARROLLO DE FUNCIONES

//-----------------------------------
void crear_simulacion() {
  int fin=0;

  //Ciclos dia / noche
  clrscr();
  gotoxy(30,5);
  printf("DEFINICION DEL ENTORNO.");
  gotoxy(35,8);
  printf("DIA / NOCHE");
  gotoxy(5,11);
  printf("N§ de ciclos dia / noche (min. 30):");
  while(!fin) {
    gotoxy(41,11);
    printf("          ");
    gotoxy(41,11);
    scanf("%d",&simudat.ciclosdianoche);
    if(simudat.ciclosdianoche>=30) {
      fin=1;
    }
  }
  simudat.dia=simudat.noche=simudat.ciclosdianoche/2;
  simudat.ciclosdianoche=simudat.dia*2;

  //Temperatura
  clrscr();
  gotoxy(30,5);
  printf("DEFINICION DEL ENTORNO.");
  gotoxy(31,8);
  printf("ZONAS DE TEMPERATURA");
  gotoxy(5,11);
  printf("Temperatura inicial (1-500):");
  fin=0;
  while(!fin) {
    gotoxy(34,11);
    printf("             ");
    gotoxy(34,11);
    scanf("%d",&simudat.temperatura);
    if(simudat.temperatura>=1 && simudat.temperatura<=500) {
      fin=1;
    }
  }

  //Muros
  clrscr();
  gotoxy(30,5);
  printf("DEFINICION DEL ENTORNO.");
  gotoxy(38,8);
  printf("MUROS");
  gotoxy(5,11);
  printf("N§ de ciclos para crear muros (min.10):");
  fin=0;
  while(!fin) {
    gotoxy(45,11);
    printf("             ");
    gotoxy(45,11);
    scanf("%d",&simudat.cicloscrearmuros);
    if(simudat.cicloscrearmuros>=10) {
      fin=1;
    }
  }

  gotoxy(5,13);
  printf("N§ de ciclos para eliminar muros (min.10):");
  fin=0;
  while(!fin) {
    gotoxy(48,13);
    printf("             ");
    gotoxy(48,13);
    scanf("%d",&simudat.cicloseliminarmuros);
    if(simudat.cicloseliminarmuros>=10) {
      fin=1;
    }
  }

  gotoxy(5,15);
  printf("Longitud maxima de los muros (1-15):");
  fin=0;
  while(!fin) {
    gotoxy(42,15);
    printf("             ");
    gotoxy(42,15);
    scanf("%d",&simudat.longitudmuros);
    if(simudat.longitudmuros>=1 && simudat.longitudmuros<=15) {
      fin=1;
    }
  }

  gotoxy(5,17);
  printf("Numero inicial de muros (0-10):");
  fin=0;
  while(!fin) {
    gotoxy(37,17);
    printf("             ");
    gotoxy(37,17);
    scanf("%d",&simudat.nummuros);
    if(simudat.nummuros>=0 && simudat.nummuros<=10) {
      fin=1;
    }
  }

  //PLANTAS
  clrscr();
  gotoxy(30,5);
  printf("DEFINICION DEL ENTORNO.");
  gotoxy(37,8);
  printf("PLANTAS");
  gotoxy(5,11);
  printf("N§ de ciclos para crear plantas (min.1):");
  fin=0;
  while(!fin) {
    gotoxy(46,11);
    printf("             ");
    gotoxy(46,11);
    scanf("%d",&simudat.cicloscrearplantas);
    if(simudat.cicloscrearplantas>=1) {
      fin=1;
    }
  }

  gotoxy(5,13);
  printf("N§ maximo de plantas a crear (max.30):");
  fin=0;
  while(!fin) {
    gotoxy(44,13);
    printf("             ");
    gotoxy(44,13);
    scanf("%d",&simudat.nummaxplantas);
    if(simudat.nummaxplantas>=1 && simudat.nummaxplantas<=30) {
      fin=1;
    }
  }

  gotoxy(5,15);
  printf("Nivel maximo de agua de las plantas (max.50):");
  fin=0;
  while(!fin) {
    gotoxy(51,15);
    printf("             ");
    gotoxy(51,15);
    scanf("%d",&simudat.aguaplantas);
    if(simudat.aguaplantas>=1 && simudat.aguaplantas<=50) {
      fin=1;
    }
  }


  gotoxy(5,17);
  printf("Numero inicial de plantas (0-100):");
  fin=0;
  while(!fin) {
    gotoxy(40,17);
    printf("             ");
    gotoxy(40,17);
    scanf("%d",&simudat.numplantas);
    if(simudat.numplantas>=0 && simudat.numplantas<=100) {
      fin=1;
    }
  }

  //HORMIGAS
  clrscr();
  gotoxy(30,5);
  printf("DEFINICION DE HORMIGAS.");
  gotoxy(5,11);
  printf("Energia que pierde al realizar tareas (1-100):");
  fin=0;
  while(!fin) {
    gotoxy(51,11);
    printf("             ");
    gotoxy(51,11);
    scanf("%d",&simudat.perdenergia);
    if(simudat.perdenergia>=1 && simudat.perdenergia<=100) {
      fin=1;
    }
  }

  gotoxy(5,13);
  printf("Indice de mutacion (1-10):");
  fin=0;
  while(!fin) {
    gotoxy(32,13);
    printf("             ");
    gotoxy(32,13);
    scanf("%d",&simudat.indmutacion);
    if(simudat.indmutacion>=1 && simudat.indmutacion<=10) {
      fin=1;
    }
  }

  gotoxy(5,15);
  printf("Numero inicial de hormigas azules (max.100):");
  fin=0;
  while(!fin) {
    gotoxy(50,15);
    printf("             ");
    gotoxy(50,15);
    scanf("%d",&simudat.nhazul);
    if(simudat.nhazul>=0 && simudat.nhazul<=100) {
      fin=1;
    }
  }

  gotoxy(5,17);
  printf("Numero inicial de hormigas cyan (max.100):");
  fin=0;
  while(!fin) {
    gotoxy(48,17);
    printf("             ");
    gotoxy(48,17);
    scanf("%d",&simudat.nhcyan);
    if(simudat.nhcyan>=0 && simudat.nhcyan<=100) {
      fin=1;
    }
  }

  gotoxy(5,19);
  printf("Numero inicial de hormigas rojas (max.100):");
  fin=0;
  while(!fin) {
    gotoxy(49,19);
    printf("             ");
    gotoxy(49,19);
    scanf("%d",&simudat.nhrojo);
    if(simudat.nhrojo>=0 && simudat.nhrojo<=100) {
      fin=1;
    }
  }

  gotoxy(5,21);
  printf("Numero inicial de hormigas amarillas (max.100):");
  fin=0;
  while(!fin) {
    gotoxy(53,21);
    printf("             ");
    gotoxy(53,21);
    scanf("%d",&simudat.nhamarillo);
    if(simudat.nhamarillo>=0 && simudat.nhamarillo<=100) {
      fin=1;
    }
  }

  gotoxy(5,23);
  printf("Numero inicial de hormigas blancas (max.100):");
  fin=0;
  while(!fin) {
    gotoxy(51,23);
    printf("             ");
    gotoxy(51,23);
    scanf("%d",&simudat.nhblanco);
    if(simudat.nhblanco>=0 && simudat.nhblanco<=100) {
      fin=1;
    }
  }
}
//-----------------------------------
void dibujar_entorno() {
  cuadrado(0,0,322,322,ROJO);

  dibujar_hormiga(46,1,AZUL);
  gotoxy(50,1);
  printf("%d",simudat.nhazul);


  dibujar_hormiga(46,3,CYAN);
  gotoxy(50,2);
  printf("%d",simudat.nhcyan);


  dibujar_hormiga(46,5,ROJO);
  gotoxy(50,3);
  printf("%d",simudat.nhrojo);


  dibujar_hormiga(46,7,AMARILLO);
  gotoxy(50,4);
  printf("%d",simudat.nhamarillo);


  dibujar_hormiga(46,9,BLANCO);
  gotoxy(50,5);
  printf("%d",simudat.nhblanco);

  outtextxy(328,100,"Total: ");
  gotoxy(50,7);
  printf("%d",simudat.nhazul+simudat.nhcyan+simudat.nhrojo+
	 simudat.nhamarillo+simudat.nhblanco);

  line(380,87,440,87);



  dibujar_planta(46,17,AMARILLO);
  gotoxy(50,9);
  printf("%d",simudat.numplantas);


  dibujar_planta(46,19,VERDE);
  gotoxy(50,10);
  printf("0");


  dibujar_muro(46,21,MARRON);
  gotoxy(50,11);
  printf("%d",simudat.nummuros);


  setcolor(BLANCO);
  outtextxy(328,212,"TEMPER:");
  gotoxy(50,14);
  printf("%d",simudat.temperatura);

  setcolor(BLANCO);
  outtextxy(328,260,"DIA  :");
  gotoxy(50,17);
  printf("%d",simudat.dia);

  outtextxy(328,276,"NOCHE:");
  gotoxy(50,18);
  printf("%d",simudat.noche);

  setcolor(AMARILLO);
  outtextxy(328,292,"    D:");
  gotoxy(50,19);
  printf("%d",simudat.dia);

  setcolor(GRIS_CLARO);
  outtextxy(328,308,"    N:");
  gotoxy(50,20);
  printf("%d",0);

  gotoxy(1,22);
  printf("Velocidad:   ");
  gotoxy(14,22);
  printf("%d",9);

  gotoxy(1,23);
  printf("Nacimientos: ");
  gotoxy(14,23);
  printf("%d",0);

  gotoxy(1,24);
  printf("Muertes:     ");
  gotoxy(14,24);
  printf("%d",0);

  gotoxy(1,25);
  printf("Mutaciones:  ");
  gotoxy(14,25);
  printf("%d",0);

  gotoxy(20,22);
  printf("Ciclos:  ");
  gotoxy(28,22);
  printf("%d",0);

  gotoxy(43,22);
  printf("S.. Salir");

  gotoxy(43,23);
  printf("P.. Pausa");

  gotoxy(43,24);
  printf("+.. + Velocidad");

  gotoxy(43,25);
  printf("-.. - Velocidad");
}
//-----------------------------------
void iniciar_modo_grafico() {
  int DRIVER,MODO,codigoerror;

  DRIVER=VGA;
  MODO=VGAHI;
  initgraph(&DRIVER, &MODO, "");
  codigoerror = graphresult();

  if (codigoerror != grOk) {
    printf("Error al iniciar el modo grafico:\n %s\n", grapherrormsg(codigoerror));
    printf("\nPULSA UNA TECLA PARA TERMINAR");
    getch();
    exit(1);
  }
}
//-----------------------------------
void cuadrado(int x1, int y1, int x2, int y2, int color) {
  setcolor(color);
  line(x1,y1,x2,y1);
  line(x1,y1,x1,y2);
  line(x1,y2,x2,y2);
  line(x2,y1,x2,y2);
}
//-----------------------------------
void dibujar_hormiga(int posx, int posy, int color) {
  int x;
  int y;

    x=(((8*posx)-8)+1);
    y=(((8*posy)-8)+1);
    putpixel(x+1,y+1,color);
    putpixel(x+6,y+1,color);
    putpixel(x+1,y+2,color);
    putpixel(x+3,y+2,color);
    putpixel(x+4,y+2,color);
    putpixel(x+6,y+2,color);
    putpixel(x+2,y+3,color);
    putpixel(x+3,y+3,color);
    putpixel(x+4,y+3,color);
    putpixel(x+5,y+3,color);
    putpixel(x+2,y+4,color);
    putpixel(x+3,y+4,color);
    putpixel(x+4,y+4,color);
    putpixel(x+5,y+4,color);
    putpixel(x+1,y+5,color);
    putpixel(x+3,y+5,color);
    putpixel(x+4,y+5,color);
    putpixel(x+6,y+5,color);
    putpixel(x+1,y+6,color);
    putpixel(x+6,y+6,color);
}
//-----------------------------------
void dibujar_planta(int posx, int posy, int color) {
  int x;
  int y;

    x=(((8*posx)-8)+1);
    y=(((8*posy)-8)+1);

    putpixel(x+3,y+2,color);
    putpixel(x+4,y+2,color);

    putpixel(x+2,y+3,color);
    putpixel(x+3,y+3,color);
    putpixel(x+4,y+3,color);
    putpixel(x+5,y+3,color);

    putpixel(x+1,y+4,color);
    putpixel(x+2,y+4,color);
    putpixel(x+3,y+4,color);
    putpixel(x+4,y+4,color);
    putpixel(x+5,y+4,color);
    putpixel(x+6,y+4,color);

    putpixel(x+1,y+5,color);
    putpixel(x+2,y+5,color);
    putpixel(x+3,y+5,color);
    putpixel(x+4,y+5,color);
    putpixel(x+5,y+5,color);
    putpixel(x+6,y+5,color);

    putpixel(x+2,y+6,color);
    putpixel(x+3,y+6,color);
    putpixel(x+4,y+6,color);
    putpixel(x+5,y+6,color);

    putpixel(x+3,y+7,color);
    putpixel(x+4,y+7,color);
}
//-----------------------------------
void dibujar_muro(int posx, int posy, int color) {
  int x;
  int y;

    x=(((8*posx)-8)+1);
    y=(((8*posy)-8)+1);

    setcolor(color);
    line(x+1,y+1,x+6,y+1);
    line(x+1,y+2,x+6,y+2);
    line(x+1,y+3,x+6,y+3);
    line(x+1,y+4,x+6,y+4);
    line(x+1,y+5,x+6,y+5);
    line(x+1,y+6,x+6,y+6);
}
//-----------------------------------
void dibujar_linea_temperatura(int posx, int color) {
  int x;

    x=(((8*posx)-8)+1);
    setcolor(color);
    line(x,2,x,320);
}
//-----------------------------------
void distribuir_elementos() {
  int i;
  int j;
  int longitud;
  int direccion;
  int px;
  int py;
  int pos;
  int fin;
  int agua;
  int aux;
  int n;
  int nazul;
  int ncyan;
  int nrojo;
  int namarillo;
  int nblanco;
  bloque auxbloque;
  muro auxmuro;
  planta auxplanta;

  //muros
  for(i=1;i<=simudat.nummuros;i++) {
    longitud=(rand() % simudat.longitudmuros)+1; //longitud del muro
    px=(rand() % LARGO)+1;  //coordenada x inicial del muro
    py=(rand() % ANCHO)+1;  //coordenada y inicial del muro
    direccion=rand() % 4;//direccion del muro

    //comprueba si el muro tiene espacio hacia arriba sino cambia
    //la direccion hacia abajo
    if(direccion==0) {     //hacia arriba
      if(py-longitud<1) {
	direccion=1;
      }
    }
    //comprueba si el muro tiene espacio hacia abajo sino cambia
    //la direccion hacia arriba
    if(direccion==1) {	//hacia abajo
      if(py+longitud>ANCHO) {
	direccion=0;
      }
    }
    //comprueba si el muro tiene espacio hacia la izquierda sino cambia
    //la direccion hacia la derecha
    if(direccion==2) {	//hacia la izquierda
      if(px-longitud<1) {
	direccion=3;
      }
    }
    //comprueba si el muro tiene espacio hacia la derecha sino cambia
    //la direccion hacia la izquerda
    if(direccion==3) {	//hacia la derecha
      if(px+longitud>LARGO) {
	direccion=2;
      }
    }
    //creamos el muro y lo metemos en la lista de muros
    auxmuro=crear_muro(longitud,px,py,direccion);
    meter_muro_listam(listamuros,auxmuro);
    //dibujamos el muro en pantalla
    for(j=1;j<=longitud;j++) {
      auxbloque=ver_bloque_muro(auxmuro,j);
      px=ver_posx_bloque(auxbloque);
      py=ver_posy_bloque(auxbloque);
      dibujar_muro(px,py,MARRON);
    }
  }

  //plantas
  crearplantas(simudat.numplantas);

  //hormigas
  nazul=simudat.nhazul;
  ncyan=simudat.nhcyan;
  nrojo=simudat.nhrojo;
  namarillo=simudat.nhamarillo;
  nblanco=simudat.nhblanco;
  n=simudat.nhazul+simudat.nhcyan+simudat.nhrojo+simudat.nhamarillo+simudat.nhblanco;
  while(n) {
    if(nazul) {
      crearhormigas(AZUL,1);
      n--;
      nazul--;
    }
    if(ncyan) {
      crearhormigas(CYAN,1);
      n--;
      ncyan--;
    }
    if(nrojo) {
      crearhormigas(ROJO,1);
      n--;
      nrojo--;
    }
    if(namarillo) {
      crearhormigas(AMARILLO,1);
      n--;
      namarillo--;
    }
    if(nblanco) {
      crearhormigas(BLANCO,1);
      n--;
      nblanco--;
    }
  }
}
//-----------------------------------
void crearhormigas(int especie, int num) {
  int i;
  int j;
  int fin;
  int pos;
  int px;
  int py;
  int dato;
  muro auxmuro;
  planta auxplanta;
  hormigap auxhormiga;

  for(i=1;i<=num;i++) {
    fin=0;
    while(!fin) {
      px=(rand() % LARGO)+1; //posicion x de la hormiga
      py=(rand() % ANCHO)+1; //posicion y de la hormiga

      //comprobamos si la posicion x y de la hormiga esta libre
      pos=0;
      for(j=1;( (j<=nummuros_listam(listamuros)) && (!pos) );j++) {
	auxmuro=ver_muro_listam(listamuros,j);
	pos=buscar_bloque_muro(auxmuro,px,py);
      }

      if(pos==0) {
	pos=buscar_planta_listap(listaplantas,px,py);
	if(pos==0) {
	  pos=buscar_hormigap_listahp(listahormigas,px,py);
	  if(pos==0) {
	    fin=1;
	  }
	}
      }
    }
    //cremamos la hormiga y la iniciamos con todos sus valores
    auxhormiga=crear_hormigap();
    cambiar_posicion_hormigap(auxhormiga,px,py);
    cambiar_especie_hormigap(auxhormiga,especie);
    dato=(rand() % 100)+1;
    cambiar_energia_hormigap(auxhormiga,dato);
    cambiar_energia_ini_hormigap(auxhormiga,dato);
    cambiar_activa_hormigap(auxhormiga,1);
    dato=(rand() % 100)+1;
    cambiar_caracter_hormigap(auxhormiga,dato);
    dato=(rand() % 50)+1;
    cambiar_inc_energ_hormigap(auxhormiga,dato);
    dato=(rand() % simudat.perdenergia)+1;
    cambiar_perd_energ_hormigap(auxhormiga,dato);
    dato=(rand() % 10)+1;
    cambiar_inc_perd_energ_hormigap(auxhormiga,dato);
    dato=(rand() % 250)+250;
    cambiar_tmaxt_hormigap(auxhormiga,dato);
    dato=(rand() % 248)+1;
    cambiar_tmint_hormigap(auxhormiga,dato);
    dato=(rand() % 3)+1;
    cambiar_actividad_hormigap(auxhormiga,dato);
    dato=(rand() % 20)+1;
    cambiar_destreza_hormigap(auxhormiga,dato);
    //metemos la hormiga en la lista de hormigas y la dibujamos
    meter_hormigap_listahp(listahormigas,auxhormiga);
    dibujar_hormiga(px,py,especie);
  }
}
//-----------------------------------
void simulacion() {
  int energia;
  int especie;
  int fin;
  int pos;
  int npx;
  int npy;
  int nplantas;
  int contdn;
  int contplantas;
  int contmuros;
  int contdesmuros;
  int accion;
  int dirtemp;
  int plant;
  int hormig;
  int op;
  int retardo=1;
  unsigned long int ciclos=0;
  hormigap auxhormiga;


  nplantasinm=simudat.numplantas;
  nplantasma=0;
  contdn=simudat.dia;
  temp=simudat.temperatura;
  dirtemp=1;
  contplantas=simudat.cicloscrearplantas;
  contmuros=simudat.cicloscrearmuros;
  contdesmuros=simudat.cicloseliminarmuros;
  hormigact=ver_hormigap_listahp(listahormigas,1);

  fin=0;
  while(!fin) {
    if(kbhit()) {
      op=getch();
      if( (op=='s') || (op=='S') ) {
	fin=1;
      }
      if( (op=='p') || (op=='P') ) {
	gotoxy(18,24);
	printf("Pulsa C para continuar");
	while( (op!='c') && (op!='C') ) {
	  op=getch();
	}
	gotoxy(18,24);
	printf("                      ");
      }
      if(op=='+') {
	retardo--;
	velocidad++;
	if(velocidad>10) {
	  velocidad=10;
	}
	if(retardo<0) {
	  retardo=0;
	}
	gotoxy(14,22);
	printf("   ");
	gotoxy(14,22);
	printf("%d",velocidad);
      }
      if(op=='-') {
	retardo++;
	velocidad--;
	if(velocidad<0) {
	  velocidad=0;
	}
	if(retardo>10) {
	  retardo=10;
	}
	gotoxy(14,22);
	printf("   ");
	gotoxy(14,22);
	printf("%d",velocidad);
      }
    }
    if(numhormigaps_listahp(listahormigas)) {
      if(!hormigact) {
	hormigact=ver_hormigap_listahp(listahormigas,1);
      }
      delay(retardo);
      if(moverhormiga()) {
	if(consultar_energia_hormigap(hormigact)<1) {
	  auxhormiga=hormigact;
	  hormigact=siguiente_hormigap_listahp(listahormigas,hormigact);
	  matar_hormiga(auxhormiga);
	} else {
	  comprobar_plantas_comestibles();
	  if( (ppx!=-1) && (ppy!=-1) ) {
	    comer_planta();
	  }
	  comprobarhp();
	  especie=consultar_especie_hormigap(hormigact);
	  accion=plant=hormig=0;
	  if( (ppx!=-1) && (ppy!=-1) ) {
	    plant=1;
	  }
	  if( (hpx!=-1) && (hpy!=-1) ) {
	    hormig=1;
	  }
	  accion=seleccionar_accion(especie,plant,hormig);
	  if(accion==REGAR) {
	    regar();
	    clima();
	  }
	  if(accion==LUCHAR) {
	    luchar();
	    clima();
	  }
	  if(accion==REPRODUCIRSE) {
	    reproducirse();
	    clima();
	  }
	  if(consultar_energia_hormigap(hormigact)<1) {
	    auxhormiga=hormigact;
	    hormigact=siguiente_hormigap_listahp(listahormigas,hormigact);
	    matar_hormiga(auxhormiga);
	  } else {
	    hormigact=siguiente_hormigap_listahp(listahormigas,hormigact);
	  }
	}
      } else {
	hormigact=siguiente_hormigap_listahp(listahormigas,hormigact);
      }
      //siguintes cosas crear plantas dia noche muros temperatura
      //comprobamos si se ha completado un ciclo
      if(!hormigact) {
	hormigact=ver_hormigap_listahp(listahormigas,1);
      }
      npx=consultar_posx_hormigap(hormigact);
      npy=consultar_posy_hormigap(hormigact);
      pos=buscar_hormigap_listahp(listahormigas,npx,npy);
      if(pos==1) {
	ciclos++;

	gotoxy(28,22);
	printf("          ");
	gotoxy(28,22);
	printf("%ld",ciclos);

	gotoxy(14,23);
	printf("     ");
	gotoxy(14,23);
	printf("%d",nacimientos);

	gotoxy(14,24);
	printf("     ");
	gotoxy(14,24);
	printf("%d",muertes);

	gotoxy(14,25);
	printf("     ");
	gotoxy(14,25);
	printf("%d",mutaciones);
	nacimientos=muertes=mutaciones=0;
	//comprobar ciclos dia / noche
	contdn--;
	if(dianoche) {
	  gotoxy(50,19);
	  printf("         ");
	  gotoxy(50,19);
	  printf("%d",contdn);
	} else {
	  gotoxy(50,20);
	  printf("         ");
	  gotoxy(50,20);
	  printf("%d",contdn);
	}
	if(contdn==0) {
	  if(dianoche) {
	    dianoche=0;
	    contdn=simudat.noche;
	    gotoxy(50,20);
	    printf("%d",contdn);
	  } else {
	    dianoche=1;
	    contdn=simudat.dia;
	    gotoxy(50,19);
	    printf("%d",contdn);
	  }
	}
	//crear plantas
	contplantas--;
	if(contplantas==0) {
	  contplantas=simudat.cicloscrearplantas;
	  nplantas=numplantas_listap(listaplantas);
	  if(nplantas<MAXPLAN) {
	    crearplantas((rand() % simudat.nummaxplantas)+1);
	    gotoxy(50,9);
	    printf("         ");
	    gotoxy(50,9);
	    printf("%d",nplantasinm);
	  }
	}
	//crear muros
	contmuros--;
	if(contmuros==0) {
	  contmuros=simudat.cicloscrearmuros;
	  crearmuros(1);
	}
	//eliminarmuros
	if(nummuros_listam(listamuros)) {
	  contdesmuros--;
	  if(contdesmuros==0) {
	    contdesmuros=simudat.cicloseliminarmuros;
	    destruirmuros();
	  }
	}
	//Temperatura
	if(dirtemp) {
	  if (temp==500) {
	    temp--;
	    dirtemp=0;
	  } else {
	    temp++;
	  }
	} else {
	  if(temp==1) {
	    temp++;
	    dirtemp=1;
	  } else {
	    temp--;
	  }
	}
	gotoxy(50,14);
	printf("      ");
	gotoxy(50,14);
	printf("%d",temp);
      }
    }
  }
}
//-----------------------------------
int moverhormiga() {
  muro auxmuro;
  int fin;
  int valido;
  int j;
  int pos;
  int px;
  int py;
  int npx;
  int npy;
  int direccion;
  int energia;
  int perd_energia;
  int actividad;
  int activa;
  int mover=0;

  activa=consultar_activa_hormigap(hormigact);
  actividad=consultar_actividad_hormigap(hormigact);
  if(actividad==3) {
    mover=1;
  } else {
    if(actividad==1) {
      if(dianoche) {
	mover=1;
      } else {
	if(activa) {
	  mover=1;
	  cambiar_activa_hormigap(hormigact,0);
	} else {
	  cambiar_activa_hormigap(hormigact,1);
	}
      }
    } else {
      if(actividad==2) {
	if(!dianoche) {
	  mover=1;
	} else {
	  if(activa) {
	    mover=1;
	    cambiar_activa_hormigap(hormigact,0);
	  } else {
	    cambiar_activa_hormigap(hormigact,1);
	  }
	}
      }
    }
  }
  if(mover) {
    px=consultar_posx_hormigap(hormigact);
    py=consultar_posy_hormigap(hormigact);

    valido=0;
    while(!valido) {
      direccion=(rand() % 8)+1;

      if(direccion==1) {
	npx=px-1;
	npy=py-1;
      }

      if(direccion==2) {
	npx=px;
	npy=py-1;
      }

      if(direccion==3) {
	npx=px+1;
	npy=py-1;
      }

      if(direccion==4) {
	npx=px-1;
	npy=py;
      }

      if(direccion==5) {
	npx=px+1;
	npy=py;
      }

      if(direccion==6) {
	npx=px-1;
	npy=py+1;
      }

      if(direccion==7) {
	npx=px;
	npy=py+1;
      }

      if(direccion==8) {
	npx=px+1;
	npy=py+1;
      }

      if( (npx>=1 && npx<=LARGO) && (npy>=1 && npy<=ANCHO) ) {
	valido=1;
      }
    }

    mover=pos=0;
    for(j=1;( (j<=nummuros_listam(listamuros)) && (!pos) );j++) {
      auxmuro=ver_muro_listam(listamuros,j);
      pos=buscar_bloque_muro(auxmuro,npx,npy);
    }

    if(pos==0) {
      pos=buscar_planta_listap(listaplantas,npx,npy);
      if(pos==0) {
	pos=buscar_hormigap_listahp(listahormigas,npx,npy);
	if(pos==0) {
	  cambiar_posicion_hormigap(hormigact,npx,npy);
	  energia=consultar_energia_hormigap(hormigact);
	  perd_energia=consultar_perd_energ_hormigap(hormigact);
	  cambiar_energia_hormigap(hormigact,energia-perd_energia);
	  mover=1;
	  dibujar_hormiga(px,py,NEGRO);
	  dibujar_hormiga(npx,npy,consultar_especie_hormigap(hormigact));
	}
      }
    }
  }
  if(!mover) {
    energia=consultar_energia_hormigap(hormigact);
    cambiar_energia_hormigap(hormigact,energia-1);
  }
  return(mover);
}
//-----------------------------------
void iniciar_matriz() {
  matcomp[0][0]=matcomp[0][1]=matcomp[0][2]=matcomp[0][3]=0;
  matcomp[0][6]=matcomp[0][9]=matcomp[0][12]=matcomp[1][1]=0;
  matcomp[1][4]=matcomp[1][7]=matcomp[1][10]=matcomp[1][12]=0;
  matcomp[1][13]=matcomp[1][14]=matcomp[2][1]=matcomp[2][4]=0;
  matcomp[2][7]=matcomp[2][10]=matcomp[2][13]=0;
  matcomp[0][4]=25;
  matcomp[0][5]=matcomp[1][9]=matcomp[1][11]=matcomp[2][0]=20;
  matcomp[2][2]=matcomp[2][3]=matcomp[2][5]=matcomp[2][6]=20;
  matcomp[2][8]=matcomp[2][9]=matcomp[2][11]=matcomp[2][12]=20;
  matcomp[2][14]=20;
  matcomp[0][7]=50;
  matcomp[0][8]=matcomp[1][8]=30;
  matcomp[0][10]=75;
  matcomp[0][11]=matcomp[1][5]=matcomp[1][6]=40;
  matcomp[0][13]=100;
  matcomp[0][14]=matcomp[1][0]=matcomp[1][2]=80;
  matcomp[1][3]=60;
}
//-----------------------------------
void crearplantas(int num) {
  int i;
  int j;
  int fin;
  int pos;
  int agua;
  int px;
  int py;
  muro auxmuro;
  planta auxplanta;

  for(i=1;i<=num;i++) {
    agua=(rand() % simudat.aguaplantas)+1;//nivel de agua
    fin=0;
    while(!fin) {
      px=(rand() % LARGO)+1; //posicion x de la planta
      py=(rand() % ANCHO)+1; //posicion y de la planta

      //comprobamos si la posicion x y de la planta esta libre
      pos=0;
      for(j=1;( (j<=nummuros_listam(listamuros)) && (!pos) );j++) {
	auxmuro=ver_muro_listam(listamuros,j);
	pos=buscar_bloque_muro(auxmuro,px,py);
      }

      if(pos==0) {
	pos=buscar_planta_listap(listaplantas,px,py);
	if(pos==0) {
	  pos=buscar_hormigap_listahp(listahormigas,px,py);
	  if(pos==0) {
	    fin=1;
	  }
	}
      }
    }
    //creamos la planta, la metemos en la lista de plantas y
    //la dibujamos en pantalla
    auxplanta=crear_planta(px,py,agua);
    meter_planta_listap(listaplantas,auxplanta);
    dibujar_planta(px,py,AMARILLO);
  }
  nplantasinm=nplantasinm+num;
}
//-----------------------------------
void comprobarhp() {
  int i;
  int j;
  int encontrado;
  int pos;
  int px;
  int py;
  planta auxp;

  ppx=ppy=hpx=hpy=-1;
  px=consultar_posx_hormigap(hormigact);
  py=consultar_posy_hormigap(hormigact);

  //buscar planta
  encontrado=0;
  for(i=-1;(i<=1) && (!encontrado);i++) {
    for(j=-1;(j<=1) && (!encontrado);j++) {
      pos=buscar_planta_listap(listaplantas,px+j,py+i);
      if(pos) {
	auxp=ver_planta_listap(listaplantas,pos);
	if(!madura_planta(auxp)) {
	  encontrado=1;
	  ppx=px+j;
	  ppy=py+i;
	}
      }
    }
  }

  //buscar hormiga
  encontrado=0;
  for(i=-1;(i<=1) && (!encontrado);i++) {
    for(j=-1;(j<=1) && (!encontrado);j++) {
      if( (px+j!=px) || (py+i!=py) ) {
	pos=buscar_hormigap_listahp(listahormigas,px+j,py+i);
	if(pos) {
	  encontrado=1;
	  hpx=px+j;
	  hpy=py+i;
	}
      }
    }
  }
}
//-----------------------------------
int seleccionar_accion(int e, int p, int h) {
    int res=0;
    int aux;

    if( (e==AZUL) && (h) ) {
      aux=(rand() % 100)+1;
      if(aux <= matcomp[2][0]) {
	res=REPRODUCIRSE;
      } else {
	res=LUCHAR;
      }
    }

    if( (e==CYAN) && (!p) && (h) ) {
      aux=(rand() % 100)+1;
      if(aux <= matcomp[1][3]) {
	res=LUCHAR;
      } else {
	if( (aux>matcomp[1][3]) && (aux<=matcomp[1][2] + matcomp[2][3])  ) {
	  res=REPRODUCIRSE;
	}
      }
    }

    if( (e==CYAN) && (p) && (!h) ) {
      aux=(rand() % 100)+1;
      if(aux<=matcomp[0][4]) {
	res=REGAR;
      }
    }

    if( (e==CYAN) && (p) && (h) ) {
      aux=(rand() % 100)+1;
      if(aux<=matcomp[0][5]) {
	res=REGAR;
      } else {
	if( (aux>matcomp[0][5]) && (aux<=matcomp[0][5]+matcomp[1][5]) ) {
	  res=LUCHAR;
	} else {
	  if( (aux>matcomp[0][5]+matcomp[1][5]) &&
	      (aux<=matcomp[0][5]+matcomp[1][2]+matcomp[2][5]) ) {
	    res=REPRODUCIRSE;
	  }
	}
      }
    }

    if( (e==ROJO) && (!p) && (h) ) {
      aux=(rand() % 100)+1;
      if(aux<=matcomp[1][6]) {
	res=LUCHAR;
      } else {
	if( (aux>matcomp[1][6]) && (aux<=matcomp[1][6]+matcomp[2][6]) ) {
	  res=REPRODUCIRSE;
	}
      }
    }

    if( (e==ROJO) && (p) && (!h) ) {
      aux=(rand() % 100)+1;
      if(aux<=matcomp[0][7]) {
	res=REGAR;
      }
    }

    if( (e==ROJO) && (p) && (h) ) {
      aux=(rand() % 100)+1;
      if(aux<=matcomp[0][8]) {
	res=REGAR;
      } else {
	if( (aux>matcomp[0][8]) && (aux<=matcomp[0][8]+matcomp[1][8]) ) {
	  res=LUCHAR;
	} else {
	  if( (aux>matcomp[0][8]+matcomp[1][8]) &&
	      (aux<=matcomp[0][8]+matcomp[1][8]+matcomp[2][8]) ) {
	    res=REPRODUCIRSE;
	  }
	}
      }
    }

    if( (e==AMARILLO) && (!p) && (h) ) {
      aux=(rand() % 100)+1;
      if(aux<=matcomp[1][9]) {
	res=LUCHAR;
      } else {
	if( (aux>matcomp[1][9]) && (aux<=matcomp[1][9]+matcomp[2][9]) ) {
	  res=REPRODUCIRSE;
	}
      }
    }

    if( (e==AMARILLO) && (p) && (!h) ) {
      aux=(rand() % 100)+1;
      if(aux<=matcomp[0][10]) {
	res=REGAR;
      }
    }

    if( (e==AMARILLO) && (p) && (h) ) {
      aux=(rand() % 100)+1;
      if(aux<=matcomp[0][11]) {
	res=REGAR;
      } else {
	if( (aux>matcomp[0][11]) && (aux<=matcomp[0][11]+matcomp[1][11]) ) {
	  res=LUCHAR;
	} else {
	  if( (aux>matcomp[0][11]+matcomp[1][11]) &&
	      (aux<=matcomp[0][11]+matcomp[1][11]+matcomp[2][11]) ) {
	    res=REPRODUCIRSE;
	  }
	}
      }
    }

    if( (e==BLANCO) && (!p) && (h) ) {
      aux=(rand() % 100)+1;
      if(aux<=matcomp[2][12]) {
	res=REPRODUCIRSE;
      }
    }

    if( (e==BLANCO) && (p) && (!h) ) {
      res=REGAR;
    }

    if( (e==BLANCO) && (p) && (h) ) {
      aux=(rand() % 100)+1;
      if(aux<=matcomp[0][14]) {
	res=REGAR;
      } else {
	res=REPRODUCIRSE;
      }
    }
    return(res);
}
//-----------------------------------
void comprobar_plantas_comestibles() {
  int px;
  int py;
  int pos;
  int encontrado;
  int i;
  int j;
  planta auxp;

  ppx=ppy=-1;
  px=consultar_posx_hormigap(hormigact);
  py=consultar_posy_hormigap(hormigact);

  //buscar planta
  encontrado=0;
  for(i=-1;(i<=1) && (!encontrado);i++) {
    for(j=-1;(j<=1) && (!encontrado);j++) {
      pos=buscar_planta_listap(listaplantas,px+j,py+i);
      if(pos) {
	auxp=ver_planta_listap(listaplantas,pos);
	if(madura_planta(auxp)) {
	  encontrado=1;
	  ppx=px+j;
	  ppy=py+i;
	}
      }
    }
  }
}
//-----------------------------------
void comer_planta() {
  int pos;
  int eneract;
  int incener;
  planta auxp;

  pos=buscar_planta_listap(listaplantas,ppx,ppy);
  auxp=sacar_planta_listap(listaplantas,pos);
  destruir_planta(&auxp);
  auxp=NULL;
  dibujar_planta(ppx,ppy,NEGRO);
  nplantasma--;
  gotoxy(50,10);
  printf("       ");
  gotoxy(50,10);
  printf("%d",nplantasma);
  eneract=consultar_energia_hormigap(hormigact);
  incener=consultar_inc_energ_hormigap(hormigact);
  eneract=eneract+incener;
  if(eneract>500) {
    eneract=500;
  }
  cambiar_energia_hormigap(hormigact,eneract);
}
//-----------------------------------
void regar() {
  int pos;
  int eneract;
  int perdener;
  planta auxp;

  pos=buscar_planta_listap(listaplantas,ppx,ppy);
  auxp=ver_planta_listap(listaplantas,pos);
  inc_agua_planta(auxp);
  if(madura_planta(auxp)) {
    dibujar_planta(ppx,ppy,VERDE);
    nplantasinm--;
    nplantasma++;
    gotoxy(50,9);
    printf("       ");
    gotoxy(50,9);
    printf("%d",nplantasinm);
    gotoxy(50,10);
    printf("       ");
    gotoxy(50,10);
    printf("%d",nplantasma);
  }
  eneract=consultar_energia_hormigap(hormigact);
  perdener=consultar_perd_energ_hormigap(hormigact);
  cambiar_energia_hormigap(hormigact,eneract-perdener);
}
//-----------------------------------
void buscar_posicion_libre(int x, int y, int *rx, int *ry) {
  int encontrado=0;
  int valido;
  int pos;
  int i;
  int j;
  int k;
  int fin;
  int posx;
  int posy;
  muro auxmuro;

  for(i=-1; (i<=1) && (!encontrado); i++) {
    for(j=-1; (j<=1) && (!encontrado); j++) {
      pos=0;
      valido=1;
      if( (x+j<1) || (x+j>LARGO) || (y+i<1) || (y+i>ANCHO) ) {
	valido=0;
      }
      if(valido) {
	for(k=1;( (k<=nummuros_listam(listamuros)) && (!pos) );k++) {
	  auxmuro=ver_muro_listam(listamuros,k);
	  pos=buscar_bloque_muro(auxmuro,x+j,y+i);
	}
	if(!pos) {
	  pos=buscar_planta_listap(listaplantas,x+j,y+i);
	  if(!pos) {
	    pos=buscar_hormigap_listahp(listahormigas,x+j,y+i);
	    if(!pos) {
	      encontrado=1;
	      (*rx)=x+j;
	      (*ry)=y+i;
	    }
	  }
	}
      }
    }
  }
  if(!encontrado) {
    fin=0;
    while(!fin) {
      posx=(rand()%LARGO)+1;
      posy=(rand()%ANCHO)+1;
      pos=0;
      for(k=1;( (k<=nummuros_listam(listamuros)) && (!pos) );k++) {
	auxmuro=ver_muro_listam(listamuros,k);
	pos=buscar_bloque_muro(auxmuro,posx,posy);
      }
      if(!pos) {
	pos=buscar_planta_listap(listaplantas,posx,posy);
	if(!pos) {
	  pos=buscar_hormigap_listahp(listahormigas,posx,posy);
	  if(!pos) {
	    fin=1;
	    (*rx)=posx;
	    (*ry)=posy;
	  }
	}
      }
    }
  }
}
//-----------------------------------
void reproducirse() {
  hormigap auxh;
  hormigap nhor;
  int nhormigas;
  int pos;
  int px;
  int py;
  int especie1,especie2;
  int caracter1,caracter2;
  int incener1,incener2;
  int perdener1,perdener2;
  int incperdener1,incperdener2;
  int tmaxt1,tmaxt2;
  int tmint1,tmint2;
  int activ1,activ2;
  int enerini1,enerini2;
  int destreza1,destreza2;
  int eneract;
  int perdener;
  int especie;
  int mutacion;

  nhormigas=numhormigaps_listahp(listahormigas);
  if(nhormigas<MAXHORM) {
    mutacion=(rand() % 100)+1;
    if(mutacion<=simudat.indmutacion) {
      especie=(rand() % 5)+1;
      if(especie==1) {
	especie=AZUL;
      } else {
	if(especie==2) {
	  especie=CYAN;
	} else {
	  if(especie==3) {
	    especie=ROJO;
	  } else {
	    if(especie==4) {
	      especie=AMARILLO;
	    } else {
	      if(especie==5) {
		especie=BLANCO;
	      }
	    }
	  }
	}
      }

      crearhormigas(especie,1);
      nacimientos++;
      mutaciones++;
      eneract=consultar_energia_hormigap(hormigact);
      cambiar_energia_hormigap(hormigact,eneract/2);
    } else {
      eneract=consultar_energia_hormigap(hormigact);
      cambiar_energia_hormigap(hormigact,eneract/2);
      pos=buscar_hormigap_listahp(listahormigas,hpx,hpy);
      auxh=ver_hormigap_listahp(listahormigas,pos);
      buscar_posicion_libre(hpx,hpy,&px,&py);
      nhor=crear_hormigap();
      cambiar_posicion_hormigap(nhor,px,py);
      cambiar_activa_hormigap(nhor,1);
      especie1=consultar_especie_hormigap(hormigact);
      caracter1=consultar_caracter_hormigap(hormigact);
      incener1=consultar_inc_energ_hormigap(hormigact);
      perdener1=consultar_perd_energ_hormigap(hormigact);
      incperdener1=consultar_inc_perd_energ_hormigap(hormigact);
      tmaxt1=consultar_tmaxt_hormigap(hormigact);
      tmint1=consultar_tmint_hormigap(hormigact);
      activ1=consultar_actividad_hormigap(hormigact);
      enerini1=consultar_energia_ini_hormigap(hormigact);
      destreza1=consultar_destreza_hormigap(hormigact);
      especie2=consultar_especie_hormigap(auxh);
      caracter2=consultar_caracter_hormigap(auxh);
      incener2=consultar_inc_energ_hormigap(auxh);
      perdener2=consultar_perd_energ_hormigap(auxh);
      incperdener2=consultar_inc_perd_energ_hormigap(auxh);
      tmaxt2=consultar_tmaxt_hormigap(auxh);
      tmint2=consultar_tmint_hormigap(auxh);
      activ2=consultar_actividad_hormigap(auxh);
      enerini2=consultar_energia_ini_hormigap(auxh);
      destreza2=consultar_destreza_hormigap(auxh);

      if(caracter1>=caracter2) {
	cambiar_especie_hormigap(nhor,especie1);
	cambiar_caracter_hormigap(nhor,caracter1);
	cambiar_actividad_hormigap(nhor,activ1);
	dibujar_hormiga(px,py,especie1);
      } else {
	cambiar_especie_hormigap(nhor,especie2);
	cambiar_caracter_hormigap(nhor,caracter2);
	cambiar_actividad_hormigap(nhor,activ2);
	dibujar_hormiga(px,py,especie1);
      }

      if(enerini1>=enerini2) {
	cambiar_energia_hormigap(nhor,enerini1);
	cambiar_energia_ini_hormigap(nhor,enerini1);
      } else {
	cambiar_energia_hormigap(nhor,enerini2);
	cambiar_energia_ini_hormigap(nhor,enerini2);
      }

      if(incener1>=incener2) {
	cambiar_inc_energ_hormigap(nhor,incener1);
      } else {
	cambiar_inc_energ_hormigap(nhor,incener2);
      }

      if(perdener1>=perdener2) {
	cambiar_perd_energ_hormigap(nhor,perdener2);
      } else {
	cambiar_perd_energ_hormigap(nhor,perdener1);
      }

      if(incperdener1>=incperdener2) {
	cambiar_inc_perd_energ_hormigap(nhor,incperdener2);
      } else {
	cambiar_inc_perd_energ_hormigap(nhor,incperdener1);
      }

      if(tmaxt1>=tmaxt2) {
	cambiar_tmaxt_hormigap(nhor,tmaxt1);
      } else {
	cambiar_tmaxt_hormigap(nhor,tmaxt2);
      }

      if(tmint1>=tmint2) {
	cambiar_tmint_hormigap(nhor,tmint2);
      } else {
	cambiar_tmint_hormigap(nhor,tmint1);
      }

      if(destreza1>=destreza2) {
	cambiar_destreza_hormigap(nhor,destreza1);
      } else {
	cambiar_destreza_hormigap(nhor,destreza2);
      }
      meter_hormigap_listahp(listahormigas,nhor);
      nacimientos++;
      especie=consultar_especie_hormigap(nhor);
    }
    gotoxy(50,7);
    printf("         ");
    gotoxy(50,7);
    printf("%d",numhormigaps_listahp(listahormigas));

    if(especie==AZUL) {
      simudat.nhazul++;
      gotoxy(50,1);
      printf("       ");
      gotoxy(50,1);
      printf("%d",simudat.nhazul);
    }
    if(especie==CYAN) {
      simudat.nhcyan++;
      gotoxy(50,2);
      printf("       ");
      gotoxy(50,2);
      printf("%d",simudat.nhcyan);
    }

    if(especie==ROJO) {
      simudat.nhrojo++;
      gotoxy(50,3);
      printf("       ");
      gotoxy(50,3);
      printf("%d",simudat.nhrojo);
    }

    if(especie==AMARILLO) {
      simudat.nhamarillo++;
      gotoxy(50,4);
      printf("       ");
      gotoxy(50,4);
      printf("%d",simudat.nhamarillo);
    }

    if(especie==BLANCO) {
      simudat.nhblanco++;
      gotoxy(50,5);
      printf("       ");
      gotoxy(50,5);
      printf("%d",simudat.nhblanco);
    }
  }
}
//-----------------------------------
void luchar() {
  hormigap auxh;
  int destreza1,destreza2;
  int energia1,energia2;
  int ener;
  int puntos1,puntos2;
  int pos;
  int combate;
  int i;

  pos=buscar_hormigap_listahp(listahormigas,hpx,hpy);
  auxh=ver_hormigap_listahp(listahormigas,pos);
  destreza1=consultar_destreza_hormigap(hormigact);
  destreza2=consultar_destreza_hormigap(auxh);
  energia1=consultar_energia_hormigap(hormigact);
  energia2=consultar_energia_hormigap(auxh);
  puntos1=puntos2=combate=0;
  for(i=1;i<=5;i++) {
    combate=(rand() % (destreza1+destreza2))+1;
    if(combate<destreza1) {
      puntos1++;
    } else {
      puntos2++;
    }
  }
  if(puntos1>puntos2) {
    ener=energia1+10;
    if(ener>500) {
      ener=500;
    }
    cambiar_energia_hormigap(hormigact,ener);
    cambiar_energia_hormigap(auxh,energia2-10);
  } else {
    ener=energia2+10;
    if(ener>500) {
      ener=500;
    }
    cambiar_energia_hormigap(auxh,ener);
    cambiar_energia_hormigap(hormigact,energia1-10);
  }
}
//-----------------------------------
void matar_hormiga(hormigap hor) {
  int pos;
  int npx;
  int npy;
  int especie;
  hormigap auxhor;

  npx=consultar_posx_hormigap(hor);
  npy=consultar_posy_hormigap(hor);
  pos=buscar_hormigap_listahp(listahormigas,npx,npy);
  especie=consultar_especie_hormigap(hor);
  auxhor=sacar_hormigap_listahp(listahormigas,pos);
  destruir_hormigap(&auxhor);
  muertes++;
  auxhor=hor=NULL;

  dibujar_hormiga(npx,npy,NEGRO);

  gotoxy(50,7);
  printf("         ");
  gotoxy(50,7);
  printf("%d",numhormigaps_listahp(listahormigas));

  if(especie==AZUL) {
    simudat.nhazul--;
    gotoxy(50,1);
    printf("       ");
    gotoxy(50,1);
    printf("%d",simudat.nhazul);
  }
  if(especie==CYAN) {
    simudat.nhcyan--;
    gotoxy(50,2);
    printf("       ");
    gotoxy(50,2);
    printf("%d",simudat.nhcyan);
  }

  if(especie==ROJO) {
    simudat.nhrojo--;
    gotoxy(50,3);
    printf("       ");
    gotoxy(50,3);
    printf("%d",simudat.nhrojo);
  }

  if(especie==AMARILLO) {
    simudat.nhamarillo--;
    gotoxy(50,4);
    printf("       ");
    gotoxy(50,4);
    printf("%d",simudat.nhamarillo);
  }

  if(especie==BLANCO) {
    simudat.nhblanco--;
    gotoxy(50,5);
    printf("       ");
    gotoxy(50,5);
    printf("%d",simudat.nhblanco);
  }
}
//-----------------------------------
void clima() {
  int tempmax;
  int tempmin;
  int eneract;
  int pdener;

  tempmax=consultar_tmaxt_hormigap(hormigact);
  tempmin=consultar_tmint_hormigap(hormigact);
  if( (temp>tempmax) || (temp<tempmin) ) {
    eneract=consultar_energia_hormigap(hormigact);
    pdener=consultar_inc_perd_energ_hormigap(hormigact);
    cambiar_energia_hormigap(hormigact,eneract-pdener);
  }
}
//-----------------------------------
void crearmuros(int num) {
  muro auxmuro;
  bloque auxbloque;
  planta auxp;
  hormigap auxh;
  int i;
  int j;
  int px;
  int py;
  int pos;
  int direccion;
  int longitud;
  int especie;


  if(numbloques_listam(listamuros)<MAXBLOQ) {
    for(i=1;i<=num;i++) {
      longitud=(rand() % simudat.longitudmuros)+1; //longitud del muro
      px=(rand() % LARGO)+1;  //coordenada x inicial del muro
      py=(rand() % ANCHO)+1;  //coordenada y inicial del muro
      direccion=rand() % 4;//direccion del muro

      //comprueba si el muro tiene espacio hacia arriba sino cambia
      //la direccion hacia abajo
      if(direccion==0) {     //hacia arriba
	if(py-longitud<1) {
	  direccion=1;
	}
      }
      //comprueba si el muro tiene espacio hacia abajo sino cambia
      //la direccion hacia arriba
      if(direccion==1) {	//hacia abajo
	if(py+longitud>ANCHO) {
	  direccion=0;
	}
      }
      //comprueba si el muro tiene espacio hacia la izquierda sino cambia
      //la direccion hacia la derecha
      if(direccion==2) {	//hacia la izquierda
	if(px-longitud<1) {
	  direccion=3;
	}
      }
      //comprueba si el muro tiene espacio hacia la derecha sino cambia
      //la direccion hacia la izquerda
      if(direccion==3) {	//hacia la derecha
	if(px+longitud>LARGO) {
	  direccion=2;
	}
      }
      //creamos el muro y lo metemos en la lista de muros
      auxmuro=crear_muro(longitud,px,py,direccion);
      meter_muro_listam(listamuros,auxmuro);
	//dibujamos el muro en pantalla
      for(j=1;j<=longitud;j++) {
	auxbloque=ver_bloque_muro(auxmuro,j);
	px=ver_posx_bloque(auxbloque);
	py=ver_posy_bloque(auxbloque);
	pos=0;
	pos=buscar_planta_listap(listaplantas,px,py);
	if (pos) {
	  auxp=sacar_planta_listap(listaplantas,pos);
	  dibujar_planta(px,py,NEGRO);
	  if(madura_planta(auxp)) {
	    nplantasma--;
	    gotoxy(50,10);
	    printf("       ");
	    gotoxy(50,10);
	    printf("%d",nplantasma);
	  } else {
	    nplantasinm--;
	    gotoxy(50,9);
	    printf("       ");
	    gotoxy(50,9);
	    printf("%d",nplantasinm);
	  }
	  destruir_planta(&auxp);
	}
	pos=0;
	pos=buscar_hormigap_listahp(listahormigas,px,py);
	if(pos) {
	  auxh=sacar_hormigap_listahp(listahormigas,pos);
	  especie=consultar_especie_hormigap(auxh);
	  dibujar_hormiga(px,py,NEGRO);
	  gotoxy(50,7);
	  printf("       ");
	  gotoxy(50,7);
	  printf("%d",numhormigaps_listahp(listahormigas));
	  if(especie==AZUL) {
	    simudat.nhazul--;
	    gotoxy(50,1);
	    printf("       ");
	    gotoxy(50,1);
	    printf("%d",simudat.nhazul);
	  }
	  if(especie==CYAN) {
	    simudat.nhcyan--;
	    gotoxy(50,2);
	    printf("       ");
	    gotoxy(50,2);
	    printf("%d",simudat.nhcyan);
	  }
	  if(especie==ROJO) {
	    simudat.nhrojo--;
	    gotoxy(50,3);
	    printf("       ");
	    gotoxy(50,3);
	    printf("%d",simudat.nhrojo);
	  }
	  if(especie==AMARILLO) {
	    simudat.nhamarillo--;
	    gotoxy(50,4);
	    printf("       ");
	    gotoxy(50,4);
	    printf("%d",simudat.nhamarillo);
	  }
	  if(especie==BLANCO) {
	    simudat.nhblanco--;
	    gotoxy(50,5);
	    printf("       ");
	    gotoxy(50,5);
	    printf("%d",simudat.nhblanco);
	  }
	}
	dibujar_muro(px,py,MARRON);
	gotoxy(50,11);
	printf("        ");
	gotoxy(50,11);
	printf("%d",nummuros_listam(listamuros));
      }
    }
  }
}
//-----------------------------------
void destruirmuros() {
  int i;
  int j;
  int px;
  int py;
  int pos;
  int nbloques;
  int destruir;
  muro auxm;
  bloque auxb;

  if(nummuros_listam(listamuros)) {
    destruir=rand() % 100;
    if(destruir<50) {
      pos=(rand()%nummuros_listam(listamuros))+1;
      auxm=sacar_muro_listam(listamuros,pos);
      nbloques=numbloques_muro(auxm);
      for(i=1;i<=nbloques;i++) {
	auxb=ver_bloque_muro(auxm,i);
	px=ver_posx_bloque(auxb);
	py=ver_posy_bloque(auxb);
	dibujar_muro(px,py,NEGRO);
      }
      destruir_muro(&auxm);
      gotoxy(50,11);
      printf("       ");
      gotoxy(50,11);
      for(i=1;i<=nummuros_listam(listamuros);i++) {
	auxm=ver_muro_listam(listamuros,i);
	nbloques=numbloques_muro(auxm);
	for(j=1;j<=nbloques;j++) {
	  auxb=ver_bloque_muro(auxm,j);
	  px=ver_posx_bloque(auxb);
	  py=ver_posy_bloque(auxb);
	  dibujar_muro(px,py,MARRON);
	}
      }

      printf("%d",nummuros_listam(listamuros));
    }
  }
}

//-----------------------------------

//************************************
