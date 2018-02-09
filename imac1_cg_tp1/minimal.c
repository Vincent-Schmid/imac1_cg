/* Exercice 01 */
/* a. En informatique, une interface de programmation applicative (souvent désignée par le terme API pour Application Programming Interface) est un ensemble normalisé de classes, de méthodes ou de fonctions qui sert de façade par laquelle un logiciel offre des services à d'autres logiciels.     */
/* b. OpenGL (Open Graphics Library) est un ensemble normalisé de fonctions de calcul d'images 2D ou 3D     */
/* c. SDL est une librairie de développement crosse-plateforme conçue pour fournir un accès au son, au clavier, à la souris, à un contrôleur de jeu et à la carte graphique via OpenGL et Direct3D.    */
/* d. Un logiciel Open Source est un programme informatique dont le code source est distribué sous une licence permettant à quiconque de lire, modifier ou redistribuer ce logiciel.      */

/* Exercice 02 */
/* 1. #include est la commande qui permet d'importer une librairie  */
/* 2. ? (-> doc OpenGL et SDL)     */
/* 3. include / makefile    */
/* 4. La fenêtre n'affiche rien pour l'instant  */
/* 5. D'après la description qui suit, "la fonction SDL_SetVideoMode permet d'ouvrir une fenêtre et de fixer ses paramètres     */


#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>

/* Dimensions de la fenêtre */
static unsigned int WINDOW_WIDTH = 400;
static unsigned int WINDOW_HEIGHT = 400;

/* Question 1. Exo 5 */
void Resize() {
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-1., 1., -1., 1.);
}

/* Nombre de bits par pixel de la fenêtre */
static const unsigned int BIT_PER_PIXEL = 32;

/* Nombre minimal de millisecondes separant le rendu de deux images */
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;

int main(int argc, char** argv) {

    /* Initialisation de la SDL */
    if(-1 == SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
        return EXIT_FAILURE;
    }
    
    /* Ouverture d'une fenêtre et création d'un contexte OpenGL */
    if(NULL == SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, BIT_PER_PIXEL, SDL_OPENGL | SDL_GL_DOUBLEBUFFER | SDL_RESIZABLE)) {
        fprintf(stderr, "Impossible d'ouvrir la fenetre. Fin du programme.\n");
        return EXIT_FAILURE;
    }
    
    /* Titre de la fenêtre */
    SDL_WM_SetCaption("Fenêtre TP1", NULL);
    
    /* Boucle d'affichage */
    int loop = 1;
    float x;
    float y;
    
   
    while(loop) {

        /* Récupération du temps au début de la boucle */
        Uint32 startTime = SDL_GetTicks();
        
        /* Placer ici le code de dessin */ 
        glClear(GL_COLOR_BUFFER_BIT);
        
        glClearColor(x,y,0,1);
        
        glColor3ub(150,50,200);
        
        /* Echange du front et du back buffer : mise à jour de la fenêtre */
        /* SDL_GL_SwapBuffers(); */
        
        glClear(GL_COLOR_BUFFER_BIT);
        
        /* Boucle traitant les evenements */
        SDL_Event e;
        while(SDL_PollEvent(&e)) {

            /* L'utilisateur ferme la fenêtre : */
            if(e.type == SDL_KEYUP) {
                loop = 0;
                break;
            }
            
            /* Quelques exemples de traitement d'evenements : */
            switch(e.type) {

                /* Clic souris */ 
                /* Affichage des coordonnées de l'endroit où l'on 
                 * clique  */
                  /* Création d'un point à l'endroit du clique
                 * Exercice 5 Question 3 */
				case SDL_MOUSEBUTTONUP:
                printf("clic en (%d, %d)\n", e.button.x, e.button.y);
                x = e.button.x % 255 / 255.0;
                y = e.button.y % 255 / 255.0;
                float i = e.button.x;
                float j = e.button.y;
                glBegin(GL_POINTS);
                glColor3ub(255, 0, 0);
                glVertex2f(-1 + 2. * i / WINDOW_WIDTH, - (-1 + 2. * j / WINDOW_HEIGHT));
                glEnd();
                SDL_GL_SwapBuffers();
                break;     
                    
                /* Mouvement souris */
                case SDL_MOUSEMOTION:
                    x = e.button.x % 255 / 255.0;
                    y = e.button.y % 255 / 255.0;
                    break;

                /* Touche clavier */
                case SDL_KEYDOWN:
                    printf("touche pressée (code = %d)\n", e.key.keysym.sym);
                    if (e.key.keysym.sym == 133) {
						loop = 0;
						break;
					}
                    break;
                    
                /* Mouvement souris */
                case SDL_VIDEORESIZE:
					WINDOW_WIDTH = e.resize.w;
					WINDOW_HEIGHT = e.resize.h;
                    Resize();
                    SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 
                    BIT_PER_PIXEL, SDL_OPENGL | SDL_GL_DOUBLEBUFFER | SDL_RESIZABLE);
                    break;

                default:
                    break;
                    
                /* Exercice 6 */
            }
        }

        /* Calcul du temps écoulé */
        Uint32 elapsedTime = SDL_GetTicks() - startTime;

        /* Si trop peu de temps s'est écoulé, on met en pause le programme */
        if(elapsedTime < FRAMERATE_MILLISECONDS) {
            SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
        }
    }

    /* Liberation des ressources associées à la SDL */ 
    SDL_Quit();

    return EXIT_SUCCESS;
}
