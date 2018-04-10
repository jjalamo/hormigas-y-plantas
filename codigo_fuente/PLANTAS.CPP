#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "c:\clase\ia\2004\haciendo\hpl\plantas.h"


/*----------------------------------------*/
/*---- CABECERAS DE PRIMITIVAS -----------*/
/*----------------------------------------*/

/*---------- PRIMITIVAS HORMIGAS -----------*/
hormigap crear_hormigap ();
void destruir_hormigap (hormigap *h);
int consultar_posx_hormigap (hormigap h);
int consultar_posy_hormigap (hormigap h);
void cambiar_posicion_hormigap (hormigap h, int px, int py);
int consultar_especie_hormigap (hormigap h);
void cambiar_especie_hormigap(hormigap h, int e);
int consultar_energia_hormigap (hormigap h);
void cambiar_energia_hormigap (hormigap h,int e);
int consultar_activa_hormigap (hormigap h);
void cambiar_activa_hormigap (hormigap h,int a);
int consultar_caracter_hormigap (hormigap h);
void cambiar_caracter_hormigap (hormigap h,int c);
int consultar_inc_energ_hormigap (hormigap h);
void cambiar_inc_energ_hormigap (hormigap h,int ie);
int consultar_perd_energ_hormigap (hormigap h);
void cambiar_perd_energ_hormigap (hormigap h,int pe);
int consultar_inc_perd_energ_hormigap (hormigap h);
void cambiar_inc_perd_energ_hormigap (hormigap h,int ipe);
int consultar_tmaxt_hormigap (hormigap h);
void cambiar_tmaxt_hormigap (hormigap h,int tm);
int consultar_tmint_hormigap (hormigap h);
void cambiar_tmint_hormigap (hormigap h,int tm);
int consultar_actividad_hormigap (hormigap h);
void cambiar_actividad_hormigap (hormigap h,int a);
int consultar_energia_ini_hormigap (hormigap h);
void cambiar_energia_ini_hormigap (hormigap h,int e);
int consultar_destreza_hormigap (hormigap h);
void cambiar_destreza_hormigap (hormigap h,int d);
/*----------------------------------------*/

/*----------- PRIMITIVAS LISTA DE HORMIGAS -----------*/
lhormigap crear_listahp ();
void destruir_listahp (lhormigap *lh);
void meter_hormigap_listahp (lhormigap lh, hormigap h);
hormigap sacar_hormigap_listahp (lhormigap lh, int pos);
hormigap ver_hormigap_listahp (lhormigap lh, int pos);
int numhormigaps_listahp (lhormigap lh);
int buscar_hormigap_listahp (lhormigap lh, int px, int py);
hormigap siguiente_hormigap_listahp(lhormigap lh, hormigap h);
/*----------------------------------------*/

/*---------- PRIMITIVAS PLANTAS -----------*/
planta crear_planta (int px, int py, int aguamax);
void destruir_planta (planta *p);
int consultar_posx_planta (planta p);
int consultar_posy_planta (planta p);
void inc_agua_planta (planta p);
int madura_planta (planta p);
/*----------------------------------------*/

/*----------- PRIMITIVAS LISTA DE PLANTAS -----------*/
lplanta crear_listap ();
void destruir_listap (lplanta *lp);
void meter_planta_listap (lplanta lp, planta p);
planta sacar_planta_listap (lplanta lp, int pos);
planta ver_planta_listap (lplanta lp, int pos);
int numplantas_listap (lplanta lp);
int buscar_planta_listap (lplanta lp, int px, int py);
/*----------------------------------------*/

/*---------- PRIMITIVAS BLOQUES -----------*/
bloque crear_bloque (int px, int py);
void destruir_bloque (bloque *b);
int ver_posx_bloque (bloque b);
int ver_posy_bloque (bloque b);
/*----------------------------------------*/

/*---------- PRIMITIVAS MUROS -----------*/
muro crear_muro (int nbloques, int px, int py, int direccion);
void destruir_muro (muro *m);
int buscar_bloque_muro (muro m, int px, int py);
bloque ver_bloque_muro(muro m, int pos);
int numbloques_muro (muro m);
/*----------------------------------------*/

/*----------- PRIMITIVAS LISTA DE MUROS -----------*/
listam crear_listam ();
void destruir_listam (listam *lm);
void meter_muro_listam (listam lm, muro m);
muro sacar_muro_listam (listam lm, int pos);
muro ver_muro_listam (listam lm, int pos);
int buscar_muro_listam (listam lm, int px, int py);
int nummuros_listam (listam lm);
int numbloques_listam (listam lm);
/*----------------------------------------*/



/*----------------------------------------*/
/*------ DESARROLLO DE PRIMITIVAS --------*/
/*----------------------------------------*/

/*---------- PRIMITIVAS HORMIGAS -----------*/
/*----------------------------------------*/
hormigap crear_hormigap () {
  hormigap nuev;

  nuev=(hormigap) malloc (sizeof (struct hormigap_rep));
  if (!nuev) {
    printf("\nERROR, crear_hormigap: no hay memoria.");
    exit(1);
  }
  nuev->posx=0;
  nuev->posy=0;
  nuev->especie=0;
  nuev->energia=0;
  nuev->activa=0;
  nuev->caracter=0;
  nuev->inc_energ=0;
  nuev->perd_energ=0;
  nuev->inc_perd_energ=0;
  nuev->tmaxt=0;
  nuev->tmint=0;
  nuev->activ=0;
  nuev->energia_ini=0;
  nuev->destreza=0;
  nuev->sig=nuev->ant=NULL;
  return(nuev);
}
/*----------------------------------------*/
void destruir_hormigap (hormigap *h) {
  if(!(*h)) {
    printf("\nError, destruir_hormigap: la hormigap no existe.");
    exit(1);
  }
  free(*h);
  (*h)=NULL;
}
/*----------------------------------------*/
int consultar_posx_hormigap (hormigap h) {
  if (!h) {
    printf("\nError, consultar_posx_hormigap: no existe la hormigap.");
    getch();
//    exit(1);
  }
  return(h->posx);
}
/*----------------------------------------*/
int consultar_posy_hormigap (hormigap h) {
  if (!h) {
    printf("\nError, consultar_posy_hormigap: no existe la hormigap.");
    exit(1);
  }
  return(h->posy);
}
/*----------------------------------------*/
void cambiar_posicion_hormigap (hormigap h, int px, int py) {
  if (!h) {
    printf("\nError, cambiar_posicion_hormigap: no existe la hormigap.");
    exit(1);
  }
  h->posx=px;
  h->posy=py;
}
/*----------------------------------------*/
int consultar_especie_hormigap (hormigap h) {
  if (!h) {
    printf("\nError, consultar_especie_hormigap: no existe la hormigap.");
    exit(1);
  }
  return(h->especie);
}
/*----------------------------------------*/
void cambiar_especie_hormigap(hormigap h, int e) {
  if (!h) {
    printf("\nError, cambiar_especie_hormigap: no existe la hormigap.");
    exit(1);
  }
  h->especie=e;
}
/*----------------------------------------*/
int consultar_energia_hormigap (hormigap h) {
  if (!h) {
    printf("\nError, consultar_energia_hormigap: no existe la hormigap.");
    exit(1);
  }
  return(h->energia);
}
/*----------------------------------------*/
void cambiar_energia_hormigap (hormigap h,int e) {
  if (!h) {
    printf("\nError, cambiar_energia_hormigap: no existe la hormigap.");
    exit(1);
  }
  h->energia=e;
}
/*----------------------------------------*/
int consultar_activa_hormigap (hormigap h) {
  if (!h) {
    printf("\nError, consultar_activa_hormigap: no existe la hormigap.");
    exit(1);
  }
  return(h->activa);
}
/*----------------------------------------*/
void cambiar_activa_hormigap (hormigap h,int a) {
  if (!h) {
    printf("\nError, cambiar_activa_hormigap: no existe la hormigap.");
    exit(1);
  }
  h->activa=a;
}
/*----------------------------------------*/
int consultar_caracter_hormigap (hormigap h) {
  if (!h) {
    printf("\nError, consultar_caracter_hormigap: no existe la hormigap.");
    exit(1);
  }
  return(h->caracter);
}
/*----------------------------------------*/
void cambiar_caracter_hormigap (hormigap h,int c) {
  if (!h) {
    printf("\nError, cambiar_caracter_hormigap: no existe la hormigap.");
    exit(1);
  }
  h->caracter=c;
}
/*----------------------------------------*/
int consultar_inc_energ_hormigap (hormigap h) {
  if (!h) {
    printf("\nError, consultar_inc_energia_hormigap: no existe la hormigap.");
    exit(1);
  }
  return(h->inc_energ);
}
/*----------------------------------------*/
void cambiar_inc_energ_hormigap (hormigap h,int ie) {
  if (!h) {
    printf("\nError, cambiar_inc_energia_hormigap: no existe la hormigap.");
    exit(1);
  }
  h->inc_energ=ie;
}
/*----------------------------------------*/
int consultar_perd_energ_hormigap (hormigap h) {
  if (!h) {
    printf("\nError, consultar_perd_energia_hormigap: no existe la hormigap.");
    exit(1);
  }
  return(h->perd_energ);
}
/*----------------------------------------*/
void cambiar_perd_energ_hormigap (hormigap h,int pe) {
  if (!h) {
    printf("\nError, cambiar_perd_energia_hormigap: no existe la hormigap.");
    exit(1);
  }
  h->perd_energ=pe;
}
/*----------------------------------------*/
int consultar_inc_perd_energ_hormigap (hormigap h) {
  if (!h) {
    printf("\nError, consultar_inc_perd_energia_hormigap: no existe la hormigap.");
    exit(1);
  }
  return(h->inc_perd_energ);
}
/*----------------------------------------*/
void cambiar_inc_perd_energ_hormigap (hormigap h,int ipe) {
  if (!h) {
    printf("\nError, cambiar_inc_perd_energia_hormigap: no existe la hormigap.");
    exit(1);
  }
  h->inc_perd_energ=ipe;
}
/*----------------------------------------*/
int consultar_tmaxt_hormigap (hormigap h) {
  if (!h) {
    printf("\nError, consultar_tmaxt_hormigap: no existe la hormigap.");
    exit(1);
  }
  return(h->tmaxt);
}
/*----------------------------------------*/
void cambiar_tmaxt_hormigap (hormigap h,int tm) {
  if (!h) {
    printf("\nError, cambiar_tmaxt_hormigap: no existe la hormigap.");
    exit(1);
  }
  h->tmaxt=tm;
}
/*----------------------------------------*/
int consultar_tmint_hormigap (hormigap h) {
  if (!h) {
    printf("\nError, consultar_tmint_hormigap: no existe la hormigap.");
    exit(1);
  }
  return(h->tmint);
}
/*----------------------------------------*/
void cambiar_tmint_hormigap (hormigap h,int tm) {
  if (!h) {
    printf("\nError, cambiar_tmint_hormigap: no existe la hormigap.");
    exit(1);
  }
  h->tmint=tm;
}
/*----------------------------------------*/
int consultar_actividad_hormigap (hormigap h) {
  if (!h) {
    printf("\nError, consultar_actividad_hormigap: no existe la hormigap.");
    exit(1);
  }
  return(h->activ);
}
/*----------------------------------------*/
void cambiar_actividad_hormigap (hormigap h,int a) {
  if (!h) {
    printf("\nError, cambiar_actividad_hormigap: no existe la hormigap.");
    exit(1);
  }
  h->activ=a;
}
/*----------------------------------------*/
int consultar_energia_ini_hormigap (hormigap h) {
  if (!h) {
    printf("\nError, consultar_energia_ini_hormigap: no existe la hormigap.");
    exit(1);
  }
  return(h->energia_ini);
}
/*----------------------------------------*/
void cambiar_energia_ini_hormigap (hormigap h,int e) {
  if (!h) {
    printf("\nError, cambiar_energia_ini_hormigap: no existe la hormigap.");
    exit(1);
  }
  h->energia_ini=e;
}
/*----------------------------------------*/
int consultar_destreza_hormigap (hormigap h) {
  if (!h) {
    printf("\nError, consultar_destreza_hormigap: no existe la hormigap.");
    exit(1);
  }
  return(h->destreza);
}
/*----------------------------------------*/
void cambiar_destreza_hormigap (hormigap h,int d) {
  if (!h) {
    printf("\nError, cambiar_destreza_hormigap: no existe la hormigap.");
    exit(1);
  }
  h->destreza=d;
}
/*----------------------------------------*/

/*----------- PRIMITIVAS LISTA DE HORMIGAS -----------*/
/*----------------------------------------*/
lhormigap crear_listahp () {
  lhormigap nuev;

  nuev=(lhormigap) malloc (sizeof(struct lhormigap_rep));
  if(!nuev) {
    printf("\nError, crear_listahp: no hay memoria.");
    exit(1);
  }
  nuev->nhormigas=0;
  nuev->primero=nuev->ultimo=NULL;
  return(nuev);
}
/*----------------------------------------*/
void destruir_listahp (lhormigap *lh) {
  int i;
  hormigap aux;

  if (!(*lh)) {
    printf("\nError, destruir_listahp: no existe la lista.");
    exit(1);
  }
  for (i=1;i<=(*lh)->nhormigas;i++) {
    aux=(*lh)->primero;
    (*lh)->primero=aux->sig;
    aux->sig=aux->ant=NULL;
    destruir_hormigap(&aux);
  }
  aux=(*lh)->primero=(*lh)->ultimo=NULL;
  free(*lh);
  (*lh)=NULL;
}
/*----------------------------------------*/
void meter_hormigap_listahp (lhormigap lh, hormigap h) {
  if(!lh) {
    printf ("\nError, meter_hormigap_listahp: no existe la lista.");
    exit(1);
  }
  if(!h) {
    printf("\nError, meter_hormigap_listahp: no existe la hormigap.");
    exit(1);
  }
  if(lh->nhormigas==0) {
    h->sig=h->ant=NULL;
    lh->primero=lh->ultimo=h;
  }else{
    h->sig=NULL;
    h->ant=lh->ultimo;
    lh->ultimo->sig=h;
    lh->ultimo=h;
  }
  lh->nhormigas++;
}
/*----------------------------------------*/
hormigap sacar_hormigap_listahp (lhormigap lh, int pos) {
  int i;
  hormigap aux;

  if(!lh) {
    printf("\nError, sacar_hormigap_listahp: no existe la lista.");
    exit(1);
  }
  if( (pos<1)||(pos>lh->nhormigas) ){
    printf("\nError, sacar_hormigap_listahp: posicion invalida de hormigap.");
    exit(1);
  }
  if(pos==lh->nhormigas) {
    aux=lh->ultimo;
    lh->ultimo=aux->ant;
    lh->ultimo->sig=aux->ant=aux->sig=NULL;
  }else{
    if(pos==1) {
      aux=lh->primero;
      lh->primero=aux->sig;
      lh->primero->ant=aux->ant=aux->sig=NULL;
    }else{
      aux=lh->primero;
      for(i=2;i<=pos;i++){
	aux=aux->sig;
      }
      aux->ant->sig=aux->sig;
      aux->sig->ant=aux->ant;
      aux->sig=aux->ant=NULL;
    }
  }
  lh->nhormigas--;
  return(aux);
}
/*----------------------------------------*/
hormigap ver_hormigap_listahp (lhormigap lh, int pos) {
  int i;
  hormigap aux;

  if(!lh) {
    printf("\nError, sacar_hormigap_listahp: no existe la lista.");
    exit(1);
  }
  if( (pos<1)||(pos>lh->nhormigas) ){
    printf("\nError, sacar_hormigap_listahp: posicion invalida de hormigap.");
    exit(1);
  }
  if(pos==lh->nhormigas) {
    aux=lh->ultimo;
  }else{
    if(pos==1) {
      aux=lh->primero;
    }else{
      aux=lh->primero;
      for(i=2;i<=pos;i++){
	aux=aux->sig;
      }
    }
  }
  return(aux);
}
/*----------------------------------------*/
int numhormigaps_listahp (lhormigap lh) {
  if(!lh) {
    printf("\nError, numhormigaps_listahp: no existe la lista.");
    exit(1);
  }
  return(lh->nhormigas);
}
/*----------------------------------------*/
int buscar_hormigap_listahp (lhormigap lh, int px, int py) {
  int i;
  int pos;
  hormigap aux;

  if(!lh) {
    printf("\nError, buscar_hormigap_listahp: no existe la lista.");
    exit(1);
  }
  pos=0;
  if (lh->nhormigas>0) {
    aux=lh->primero;
    for(i=1;(pos==0)&&(aux!=NULL);i++) {
      if( (aux->posx==px)&&(aux->posy==py) ){
	pos=i;
      }
      aux=aux->sig;
    }
  }
  return(pos);
}
/*----------------------------------------*/
hormigap siguiente_hormigap_listahp(lhormigap lh, hormigap h) {
  hormigap aux;

  if(!lh) {
    printf("\nError, siguiente_hormigap_listahp: no existe la lista.");
    exit(1);
  }
  if(!h) {
    printf("\nError, siguiente_hormigap_listahp: no existe la hormiga.");
    exit(1);
  }
  if(lh->ultimo==h) {
    aux=lh->primero;
  } else {
    aux=h->sig;
  }
  return(aux);
}
/*----------------------------------------*/


/*---------- PRIMITIVAS PLANTAS -----------*/
/*----------------------------------------*/
planta crear_planta (int px, int py, int aguamax) {
  planta nuev;

  nuev=(planta) malloc (sizeof (struct planta_rep));
  if (!nuev) {
    printf("\nERROR, crear_planta: no hay memoria.");
    exit(1);
  }
  nuev->posx=px;
  nuev->posy=py;
  nuev->agua=0;
  nuev->max_agua=aguamax;
  nuev->sig=nuev->ant=NULL;
  return(nuev);
}
/*----------------------------------------*/
void destruir_planta (planta *p) {
  if(!(*p)) {
    printf("\nError, destruir_planta: la planta no existe.");
    exit(1);
  }
  free(*p);
  (*p)=NULL;
}
/*----------------------------------------*/
int consultar_posx_planta (planta p) {
  if (!p) {
    printf("\nError, consultar_posx_planta: no existe la planta.");
    exit(1);
  }
  return(p->posx);
}
/*----------------------------------------*/
int consultar_posy_planta (planta p) {
  if(!p) {
    printf("\nError, consultar_posy_planta: no existe la planta.");
    exit(1);
  }
  return (p->posy);
}
/*----------------------------------------*/
void inc_agua_planta (planta p) {
  if(!p) {
    printf("\nError, inc_agua_planta: no existe la planta.");
    exit(1);
  }
  p->agua++;
}
/*----------------------------------------*/
int madura_planta (planta p) {
  int res=0;

  if(!p) {
    printf("\nError, madura_planta: no existe la planta.");
    exit(1);
  }
  if(p->agua>=p->max_agua) {
    res=1;
  }
  return(res);
}
/*----------------------------------------*/

/*----------- PRIMITIVAS LISTA DE PLANTAS -----------*/
/*----------------------------------------*/
lplanta crear_listap () {
  lplanta nuev;

  nuev=(lplanta) malloc (sizeof(struct lplanta_rep));
  if(!nuev) {
    printf("\nError, crear_listap: no hay memoria.");
    exit(1);
  }
  nuev->nplantas=0;
  nuev->primero=nuev->ultimo=NULL;
  return(nuev);
}
/*----------------------------------------*/
void destruir_listap (lplanta *lp) {
  int i;
  planta aux;

  if (!(*lp)) {
    printf("\nError, destruir_listap: no existe la lista.");
    exit(1);
  }
  for (i=1;i<=(*lp)->nplantas;i++) {
    aux=(*lp)->primero;
    (*lp)->primero=aux->sig;
    aux->sig=aux->ant=NULL;
    destruir_planta(&aux);
  }
  aux=(*lp)->primero=(*lp)->ultimo=NULL;
  free(*lp);
  (*lp)=NULL;
}
/*----------------------------------------*/
void meter_planta_listap (lplanta lp, planta p) {
  if(!lp) {
    printf ("\nError, meter_planta_listap: no existe la lista.");
    exit(1);
  }
  if(!p) {
    printf("\nError, meter_planta_listap: no existe la planta.");
    exit(1);
  }
  if(lp->nplantas==0) {
    p->sig=p->ant=NULL;
    lp->primero=lp->ultimo=p;
  }else{
    p->sig=NULL;
    p->ant=lp->ultimo;
    lp->ultimo->sig=p;
    lp->ultimo=p;
  }
  lp->nplantas++;
}
/*----------------------------------------*/
planta sacar_planta_listap (lplanta lp, int pos) {
  int i;
  planta aux;

  if(!lp) {
    printf("\nError, sacar_planta_listap: no existe la lista.");
    exit(1);
  }
  if( (pos<1)||(pos>lp->nplantas) ){
    printf("\nError, sacar_planta_listap: posicion invalida de planta.");
    exit(1);
  }
  if(pos==lp->nplantas) {
    aux=lp->ultimo;
    lp->ultimo=aux->ant;
    lp->ultimo->sig=aux->ant=aux->sig=NULL;
  }else{
    if(pos==1) {
      aux=lp->primero;
      lp->primero=aux->sig;
      lp->primero->ant=aux->ant=aux->sig=NULL;
    }else{
      aux=lp->primero;
      for(i=2;i<=pos;i++){
	aux=aux->sig;
      }
      aux->ant->sig=aux->sig;
      aux->sig->ant=aux->ant;
      aux->sig=aux->ant=NULL;
    }
  }
  lp->nplantas--;
  return(aux);
}
/*----------------------------------------*/
planta ver_planta_listap (lplanta lp, int pos) {
  int i;
  planta aux;

  if(!lp) {
    printf("\nError, sacar_planta_listap: no existe la lista.");
    exit(1);
  }
  if( (pos<1)||(pos>lp->nplantas) ){
    printf("\nError, sacar_planta_listap: posicion invalida de planta.");
    exit(1);
  }
  if(pos==lp->nplantas) {
    aux=lp->ultimo;
  }else{
    if(pos==1) {
      aux=lp->primero;
    }else{
      aux=lp->primero;
      for(i=2;i<=pos;i++){
	aux=aux->sig;
      }
    }
  }
  return(aux);
}
/*----------------------------------------*/
int numplantas_listap (lplanta lp) {
  if(!lp) {
    printf("\nError, numplantas_listap: no existe la lista.");
    exit(1);
  }
  return(lp->nplantas);
}
/*----------------------------------------*/
int buscar_planta_listap (lplanta lp, int px, int py) {
  int i;
  int pos;
  planta aux;

  if(!lp) {
    printf("\nError, buscar_planta_listap: no existe la lista.");
    exit(1);
  }
  pos=0;
  if (lp->nplantas>0) {
    aux=lp->primero;
    for(i=1;(pos==0)&&(aux!=NULL);i++) {
      if( (aux->posx==px)&&(aux->posy==py) ){
	pos=i;
      }
      aux=aux->sig;
    }
  }
  return(pos);
}
/*----------------------------------------*/


/*---------- PRIMITIVAS BLOQUES -----------*/
/*----------------------------------------*/
bloque crear_bloque (int px, int py) {
  bloque nuev;

  nuev=(bloque) malloc (sizeof(struct bloque_rep));
  if(!nuev) {
    printf("\nError, crear_bloque: no hay memoria.");
    exit(1);
  }
  nuev->px=px;
  nuev->py=py;
  nuev->sig=NULL;
  return(nuev);
}
/*----------------------------------------*/
void destruir_bloque (bloque *b) {
  if (!(*b)) {
    printf("\nError, destruir_bloque: no existe el bloque.");
    exit(1);
  }
  free(*b);
  (*b)=NULL;
}
/*----------------------------------------*/
int ver_posx_bloque (bloque b) {
  if(!b) {
    printf("\nError, ver_posx_bloque: no existe el bloque.");
    exit(1);
  }
  return(b->px);
}
/*----------------------------------------*/
int ver_posy_bloque (bloque b) {
  if(!b) {
    printf("\nError, ver_posy_bloque: no existe el bloque.");
    exit(1);
  }
  return(b->py);
}
/*----------------------------------------*/

/*---------- PRIMITIVAS MUROS -----------*/
/*----------------------------------------*/
muro crear_muro (int nbloques, int px, int py, int direccion) {
  muro nuev;
  bloque aux;
  bloque aux2;
  int i;

  nuev=(muro)  malloc (sizeof (struct muro_rep));
  if(!nuev) {
    printf ("\nError, crear_muro: no hay memoria.");
    exit(1);
  }
  if( (direccion<0) && (direccion>3) ) {
    printf("\nError, crear_muro: direccion incorrecta.");
    exit(1);
  }
  aux=crear_bloque(px,py);
  nuev->primero=aux2=aux;
  for(i=1;i<nbloques;i++) {
    if(direccion==0) {
      aux=crear_bloque(px,py-i);
    }
    if(direccion==1) {
      aux=crear_bloque(px,py+i);
    }
    if(direccion==2) {
      aux=crear_bloque(px-i,py);
    }
    if(direccion==3) {
      aux=crear_bloque(px+i,py);
    }
    aux2->sig=aux;
    aux2=aux;
  }
  nuev->sig=nuev->ant=NULL;
  nuev->nbloques=nbloques;
  return(nuev);
}
/*----------------------------------------*/
void destruir_muro (muro *m) {
  bloque aux;
  int i;

  if(!(*m)) {
    printf("\nError, destruir_muro: No existe el muro.");
    exit(1);
  }
  for(i=1;i<=(*m)->nbloques;i++) {
    aux=(*m)->primero;
    (*m)->primero=aux->sig;
    destruir_bloque(&aux);
  }
  free(*m);
  (*m)=NULL;
  aux=NULL;
}
/*----------------------------------------*/
int buscar_bloque_muro (muro m, int px, int py) {
  bloque aux;
  int res=0;

  if(!m) {
    printf("\nError, buscar_bloque_muro: no existe el muro.");
    exit(1);
  }

  aux=m->primero;
  while( (!res) && (aux!=NULL) ) {
    if( (aux->px==px) && (aux->py==py) ) {
      res=1;
    } else {
      aux=aux->sig;
    }
  }
  return(res);
}
/*----------------------------------------*/
bloque ver_bloque_muro(muro m, int pos) {
  bloque aux;
  int i;

  if(!m) {
    printf("\nError, ver_bloque_muro: no existe el muro.");
    exit(1);
  }
  if(pos<1 || pos>m->nbloques) {
    printf("\nError, ver_bloque_muro: no existe el bloque.");
    exit(1);
  }
  aux=m->primero;
  for(i=1;i<pos;i++) {
    aux=aux->sig;
  }
  return(aux);
}
/*----------------------------------------*/
int numbloques_muro (muro m) {
  if(!m) {
    printf("\nError, numbloques_muro: no existe del muro.");
    exit(1);
  }
  return(m->nbloques);
}
/*----------------------------------------*/

/*----------- PRIMITIVAS LISTA DE MUROS -----------*/
/*----------------------------------------*/
listam crear_listam () {
  listam nuev;

  nuev=(listam) malloc (sizeof (struct lmuro_rep));
  if(!nuev) {
    printf("\nError, crear_listam: no hay memoria.");
    exit(1);
  }
  nuev->nmuros=0;
  nuev->primero=nuev->ultimo=NULL;
  return(nuev);
}
/*----------------------------------------*/
void destruir_listam (listam *lm) {
  muro aux;
  int i;

  if(!(*lm)) {
    printf("\Error, destruir_listam: no existe la lista.");
    exit(1);
  }

  for(i=1;i<=(*lm)->nmuros;i++) {
    aux=(*lm)->primero;
    (*lm)->primero=aux->sig;
    destruir_muro(&aux);
  }
  free(*lm);
  (*lm)=NULL;
  aux=NULL;
}
/*----------------------------------------*/
void meter_muro_listam (listam lm, muro m) {
  if(!lm) {
    printf("\nError, meter_muro_listam: no existe la lista.");
    exit(1);
  }
  if(!m) {
    printf("\nError, meter_muro_listam: no existe el muro.");
    exit(1);
  }

  if(lm->nmuros==0) {
    lm->primero=lm->ultimo=m;
  } else {
    lm->ultimo->sig=m;
    m->ant=lm->ultimo;
    lm->ultimo=m;
  }
  lm->nmuros++;
}
/*----------------------------------------*/
muro sacar_muro_listam (listam lm, int pos) {
  muro aux;
  int i;

  if(!lm) {
    printf("\nError, sacar_muro_listam: no existe la lista.");
    exit(1);
  }
  if(pos<1 || pos>lm->nmuros) {
    printf("\nError, sacar_muro_listam: la posicion no es valida.");
    exit(1);
  }
  aux=lm->primero;
  if(lm->nmuros==1) {
    lm->primero=lm->ultimo=NULL;
  } else {
    for(i=1;i<pos;i++) {
      aux=aux->sig;
    }
    if(aux==lm->primero) {
      aux->sig->ant=NULL;
      lm->primero=aux->sig;
    } else {
      if(aux==lm->ultimo) {
	aux->ant->sig=NULL;
	lm->ultimo=aux->ant;
      } else {
	aux->ant->sig=aux->sig;
	aux->sig->ant=aux->ant;
      }
    }
  }
  aux->sig=aux->ant=NULL;
  lm->nmuros--;
  return(aux);
}
/*----------------------------------------*/
muro ver_muro_listam (listam lm, int pos) {
  muro aux;
  int i;

  if(!lm) {
    printf("\nError, ver_muro_listam: no existe la lista.");
    exit(1);
  }
  if(pos<1 || pos>lm->nmuros) {
    printf("\nError, ver_muro_listam: la posicion no es valida.");
    exit(1);
  }
  aux=lm->primero;
  for(i=1;i<pos;i++) {
    aux=aux->sig;
  }
  return(aux);
}
/*----------------------------------------*/
int buscar_muro_listam (listam lm, int px, int py);
/*----------------------------------------*/
int nummuros_listam (listam lm) {
  if(!lm) {
    printf("\nError, nummuros_listam: no existe la lista.");
    exit(1);
  }
  return(lm->nmuros);
}
/*----------------------------------------*/
int numbloques_listam (listam lm) {
  int cont=0;
  int i;
  muro aux;

  if(!lm) {
    printf("\nError, numbloques_listam: no existe la lista."),
    exit(1);
  }

  aux=lm->primero;
  for(i=1;i<=lm->nmuros;i++) {
    cont=cont+aux->nbloques;
    aux=aux->sig;
  }
  return(cont);
}
/*----------------------------------------*/
