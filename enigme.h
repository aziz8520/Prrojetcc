
#ifndef ENIGME_H_INCLUDED
#define ENIGME_H_INCLUDED
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
struct enigme
{
	SDL_Surface* image_enigme;  
	SDL_Rect position_enigme;
	int resultat;
	SDL_Surface *corrct,*wrg;
	SDL_Rect position_corrct,position_wrg;

	TTF_Font *police,*police_q;
	SDL_Surface *reponse_1,*reponse_2,*reponse_3,*question,*qu;
	SDL_Rect  pos_reponse_1,pos_reponse_2,pos_reponse_3,pos_question,pos_qu;
	int alea;
	
};
typedef struct enigme enigme;

void generer(enigme* e,SDL_Color Color);
void initEnigme( enigme* e ,SDL_Color Color);
void blit_enigme ( enigme *e, SDL_Surface* screen);
void free_surface_enigme( enigme *e );
int affiche(enigme *e, SDL_Surface* screen );
#endif
