
#include <stdlib.h>
#include <stdio.h>
#include "enigme.h"

void initEnigme( enigme* e,SDL_Color Color)
{
    e->image_enigme = IMG_Load("question.png");
    e->position_enigme.x = 0;
    e->position_enigme.y = 0;
    e->resultat = 0;
    e->corrct =IMG_Load("correct.png");
    e->wrg =IMG_Load("wrong.png");
    e->position_corrct.x = 160;
    e->position_corrct.y = 200;
    e->position_wrg.x = 240;
    e->position_wrg.y = 220;

    e->police=TTF_OpenFont("police.ttf",40 );
    e->qu = TTF_RenderText_Blended(e->police,"what is the solution?",Color);
    e->pos_qu.x=37;
    e->pos_qu.y=250;

    
    e->reponse_1 = NULL;
    e->pos_reponse_1.x=480;
    e->pos_reponse_1.y=275;

    e->reponse_2 = NULL;
    e->pos_reponse_2.x=480;
    e->pos_reponse_2.y=353;

    e->reponse_3 =NULL;
    e->pos_reponse_3.x=480;
    e->pos_reponse_3.y=453;

    e->police_q=TTF_OpenFont("police.ttf",50 );
    e->question = NULL;
    e->pos_question.x=100;
    e->pos_question.y=300;

    e->alea = 0;
}
void blit_enigme ( enigme *e, SDL_Surface* screen)
{
	SDL_BlitSurface(e->image_enigme,NULL, screen, &e->position_enigme );
        SDL_BlitSurface(e->qu,NULL,screen,&e->pos_qu);
	SDL_BlitSurface(e->reponse_1,NULL,screen,&e->pos_reponse_1);
        SDL_BlitSurface(e->reponse_2,NULL,screen,&e->pos_reponse_2);
        SDL_BlitSurface(e->reponse_3,NULL,screen,&e->pos_reponse_3);
        SDL_BlitSurface(e->question,NULL,screen,&e->pos_question);
}
void free_surface_enigme( enigme *e)
{
    SDL_FreeSurface(e->image_enigme);
    SDL_FreeSurface(e->corrct);
    SDL_FreeSurface(e->wrg);
    SDL_FreeSurface(e->reponse_1);
    SDL_FreeSurface(e->reponse_2);
    SDL_FreeSurface(e->reponse_3);
    SDL_FreeSurface(e->question);
    TTF_CloseFont(e->police);
    TTF_CloseFont(e->police_q);
}
void generer(enigme* e,SDL_Color Color)
{
	srand(time(0));
	char operand[4][2] = {"+","-","*","/"} ;

	int x = rand()%9+1;
	int y = rand()%9+1;
	int indic_operand = rand()%3+1;

	char coef_1[2],coef_2[2],question[5]={0},var[2]="x";
	sprintf(coef_1,"%d",x);
	strcat(coef_1 , var );
	strcat(question,coef_1);
	strcat(question,operand[indic_operand]);
	snprintf(coef_1, sizeof(coef_1), "%d", x);
	strcat(question,coef_2);
	float reponse1,reponse2,reponse3; 

	switch ( indic_operand )
	{
	case 0 :
		reponse1 = (-y)/(float)x;
		reponse2 = x+y;
		reponse3 = x-y;
		e->alea = 1;
	break;

	case 1 :
		reponse1 = (-y)/x;
		reponse2 = y/(float)x;
		reponse3 = x*y;
		e->alea = 2;
	break;

	case 2 :
		reponse1 = -y*x;
		reponse2 = x+y;
		reponse3 = (1)/(float)(x*y);
		e->alea = 3;
	break;

	case 3 :
		reponse1 = y/(float)x;
		reponse2 = x*y;
		reponse3 = -x-y;
		e->alea = 1;
	break;

	}
	e->question = TTF_RenderText_Blended(e->police_q,question,Color);
	char rep1[6] = {0},rep2[6] = {0},rep3[6] = {0};

	sprintf(rep1 ,"%.2f" , reponse1);
	e->reponse_1 = TTF_RenderText_Blended(e->police,rep1,Color);

	sprintf(rep2 ,"%.2f" , reponse2);
	e->reponse_2 = TTF_RenderText_Blended(e->police,rep2,Color);

	sprintf(rep3 ,"%.2f" , reponse3);
	e->reponse_3 = TTF_RenderText_Blended(e->police,rep3,Color);

}
int affiche(enigme *e, SDL_Surface* screen )
{

    SDL_Event event;
    int continuer=1;
    SDL_Color Color = {0,0,0};
   generer(e,Color);
    while(continuer == 1)
    {
        SDL_PollEvent(&event);
        switch(event.type)
        {
        case SDL_QUIT:
            continuer=0;

            break;
	case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    continuer=0;
                    break;
                }
                break;

        case SDL_MOUSEBUTTONDOWN:
        {
            switch(event.button.button)
            {
            case SDL_BUTTON_LEFT:
            {
                if ( event.button.x>420 && event.button.x<604 && event.button.y>308 && event.button.y<352)
                {
                    if ( e->alea == 1 )
                    {
                        e->resultat= 1;
                    }
                    else if ( e->alea == 2)
                    {
                        e->resultat = 2;
                    }
                    else if ( e->alea == 3)
                    {
                        e->resultat = 2;
                    }
                    
                }
                if ( event.button.x>420 && event.button.x<604 && event.button.y>391 && event.button.y<435)
                {
                    if ( e->alea == 1 )
                    {
                        e->resultat= 2;
                    }
                    else if ( e->alea == 2)
                    {
                        e->resultat = 1;
                    }
                    else if ( e->alea == 3)
                    {
                        e->resultat = 2;
                    }
                }
                if ( event.button.x>420 && event.button.x<604 && event.button.y>474 && event.button.y<518)
                {
                    if ( e->alea == 1 )
                    {
                        e->resultat= 2;
                    }
                    else if ( e->alea == 2)
                    {
                        e->resultat = 2;
                    }
                    else if ( e->alea == 3)
                    {
                        e->resultat = 1;
                    }
                }
            }
            break;
            }
        }
        break;

        }
        blit_enigme ( e, screen);

        if ( e->resultat == 1 )
        {
            SDL_BlitSurface(e->corrct,NULL, screen, &e->position_corrct );
            SDL_Flip(screen);
            SDL_Delay(2000);
            continuer = 0;
	
	    return 1;
        }
        else if ( e->resultat == 2 )
        {
            SDL_BlitSurface(e->wrg,NULL, screen, &e->position_wrg );
            SDL_Flip(screen);
            SDL_Delay(2000);
            continuer = 0;

	    return 2;
        }
        
        SDL_Flip(screen);


    }

}

