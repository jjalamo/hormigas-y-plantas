/*----------------------------------------*/
/*---------------ESTRUCTURAS--------------*/
/*----------------------------------------*/

/*-----------ESTRUCTURA HORMIGA --------------------*/
struct hormigap_rep {
  int posx;		//posicion x de la hormiga en pantalla
  int posy;             //posicion y de la hormiga en pantalla
  int especie;		//especie a la que pertenece la hormiga
  int energia;		//energia actual de la hormiga
  int activa;		//indica si la hormiga esta activa o no
  //ADN
  int caracter;		//predominacia de la hormiga sobre su especie
  int inc_energ;	//cantidad de energia que se le incrementa a la hormiga cuando esta come
  int perd_energ;	//cantidad de energia que pierde la hormiga cuando esta realiza acciones
  int inc_perd_energ; //cantidad de energia extra que pierde la hormiga cuando realiza acciones en zonas de temperaturas no soportadas
  int tmaxt;		//temperatura maxima tolerada por la hormiga
  int tmint;		//temperatura minima tolerada por la hormiga
  int activ;		//tipo de actividad de la hormiga, diurna, nocturno, diurna-nocturna
  int energia_ini;	//energia inicial con la que nace la hormiga
  int destreza;		//capacidad de lucha de la hormiga
  struct hormigap_rep *sig;
  struct hormigap_rep *ant;
}; typedef struct hormigap_rep *hormigap;
/*----------------------------------------*/

/*--------- ESTRUCTURA LISTA DE HORMIGAS -----------*/
struct lhormigap_rep {
  int nhormigas;
  struct hormigap_rep *primero;
  struct hormigap_rep *ultimo;
}; typedef struct lhormigap_rep *lhormigap;
/*----------------------------------------*/

/*------------ ESTRUCTURA PLANTA ---------------*/
struct planta_rep {
  int posx;	//posicion x de la planta en la pantalla
  int posy;	//posicion y de la planta en la pantalla
  int agua;	//cantidad de agua actual de la planta
  int max_agua;	//cantidad de agua para que la planta este madura
  struct planta_rep *sig;
  struct planta_rep *ant;
}; typedef struct planta_rep *planta;
/*----------------------------------------*/

/*--------- ESTRUCTURA LISTA DE PLANTAS -----------*/
struct lplanta_rep {
  int nplantas;
  struct planta_rep *primero;
  struct planta_rep *ultimo;
}; typedef struct lplanta_rep *lplanta;
/*----------------------------------------*/


/*--------- ESTRUCTURA BLOQUE -------------------*/
struct bloque_rep {
  int px;
  int py;
  struct bloque_rep *sig;
}; typedef struct bloque_rep *bloque;
/*----------------------------------------*/

/*--------- ESTRUCTURA MURO -------------------*/
struct muro_rep {
  int nbloques;
  struct bloque_rep *primero;
  struct muro_rep *sig;
  struct muro_rep *ant;
}; typedef struct muro_rep *muro;
/*----------------------------------------*/

/*--------- ESTRUCTURA LISTA DE MUROS -----------*/
struct lmuro_rep {
  int nmuros;
  struct muro_rep *primero;
  struct muro_rep *ultimo;
}; typedef struct lmuro_rep *listam;
/*----------------------------------------*/


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

