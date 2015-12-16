#include "graphics.h"
#define non 0
#define oui 1
#define rien 2
#define murh 3
#define murv 4
#define deplacement 5
#define autre 6
/// /////////////////////////////////////////////////////////////////////////////////////////
/// ////////////////////////////////// variables ////////////////////////////////////////////
/// /////////////////////////////////////////////////////////////////////////////////////////

POINT pr;// les coordonnées du pion rouge x 80
POINT pb;
POINT destination;
struct velement{// le tableau est tabv remplis de mur verticaux
	int ocup;			// oui ou non
	int moitie_inf;};// oui ou non
typedef struct velement velement;

struct helement{//  le tableau tabh est remplis de mur horizontaux
	int ocup; 			//oui ou non
	int moitie_droite;};	//oui ou non
typedef struct helement helement;

struct pelement{
	int accessible;// oui ou non
	int joueur;// rien , rouge ,bleu
};
typedef struct pelement pelement;
int tour;// rouge ou bleu
int nb_mur_rouge; // 10 au depart
int nb_mur_bleu;  
int gagne; // oui ou non

helement tabh[9][8];//mur horizontaux 
velement tabv[8][9];// mur verticaux
pelement plateau[9][9];// joueur ou vide + test pour la fonction recursive

/// /////////////////////////////////////////////////////////////////////////////////////////
/// /////////////////////////////////////////////////////////////////////////////////////////
/// /////////////////////////////////////////////////////////////////////////////////////////




/////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////// fonctions ////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////


void a_qui_le_tour(){
	POINT p1;
	POINT p2;
	p1.x=720; p1.y=600;
	p2.x=1000; p2.y=720;
	
	draw_fill_rectangle(p1,p2,tour);
	}


int quel_est_ce_clic(POINT p){  // return rien , murv, murh ou deplacement ou autre

if (p.x> 720) return autre;

if (p.x%80>8 && p.x%80<72){
	if (p.y%80>8 && p.y%80<72){
		
		if (tour == bleu) { 
			if (plateau[p.x/80][p.y/80].joueur==bleu) return deplacement; /// il faut cliquer sur le pion
			}
		if (tour == rouge) {
			if (plateau[p.x/80][p.y/80].joueur==rouge) return deplacement;
			}
	return rien;
		}
	}// ici je sait que le clic est forcement sur un mur
if (( (p.x)%80>=72 || p.x%80<=8 )&&(p.y%80>=0 && p.y%80<=80))  return murv;
	else return murh;
} 






//////////////////////////////////////////initialisations////////////////////

void init_plateau(){
	int i,j;
	i=0;j=0;
	while(i<9){
		while(j<9){
			plateau[i][j].joueur=rien;	
			j++;
		}
		j=0;
		i++;
	}
plateau[4][0].joueur=rouge;
pr.x=4*80;pr.y=0*80;
plateau[4][8].joueur=bleu;
pb.x=4*80;pb.y=8*80;
}


void clean_acces(){// pour la fonction recursive 
		int i,j;
	i=0;j=0;
	while(i<9){
		while(j<9){
			if (plateau[i][j].joueur!=rien){
				plateau[i][j].accessible=oui;}
			else plateau[i][j].accessible=non;
				
			j++;
		}
		j=0;
		i++;
	}
}
 
void init_jeu(){
	init_plateau();
	tour=bleu;
	nb_mur_bleu=10;
	nb_mur_rouge=10;
	clean_acces();
	gagne=non;
} 

	
int pas_colision_mur_deriere(int i1,int j1,int i2,int j2){
	//plateau[i1][j1]      plateau[i2][j2]
	if ((i1<i2)&&(j1==j2)){/// droite
		if (tabv[i1+1][j1].ocup==oui)return non;// le deplacement ne sera pas possible
	}
	
		if ((i1>i2)&&(j1==j2)){/// gauche
			if (tabv[i1-2][j1].ocup==oui)return non;
	}
	
		if ((i1==i2)&&(j1<j2)){/// haut
			if (tabh[i1][j1+1].ocup==oui)return non;
	}
	
		if ((i1==i2)&&(j1<j2)){/// bas
			if (tabh[i1][j1-2].ocup==oui)return non;
	}

return oui;// alors tout va bien
}



void move_pion_1(int i1,int j1,int i2,int j2){// change les valeur du pion rouge dans le tab et pr
//plateau[i1][j1]      plateau[i2][j2]
plateau[i1][j1].joueur=rien;
if(tour==rouge){
	if ((i1<i2)){/// droite
		plateau[i1+1][j1].joueur=tour;
		pr.x=pr.x+80;
	}else{
			if ((i1>i2)){/// gauche
			plateau[i1-1][j1].joueur=tour;
			pr.x=pr.x-80;
		}else{
	
				if ((j1<j2)){/// haut
					plateau[i1][j1+1].joueur=tour;
					pr.y=pr.y+80;
				}else{
		
					if ((j1>j2)){/// bas
						plateau[i1][j1-1].joueur=tour;
						pr.y=pr.y-80;
					}else{/// sur place
						if((j1==j2)&&(i1==i2))plateau[i1][j1].joueur=tour;
						
						}
					
				}
			}			
		}
}
else{ 	if ((i1<i2)){/// droite
		plateau[i1+1][j1].joueur=tour;
		pb.x=pb.x+80;
	}else{
			if ((i1>i2)){/// gauche
			plateau[i1-1][j1].joueur=tour;
			pb.x=pb.x-80;
		}else{
	
				if ((j1<j2)){/// haut
					plateau[i1][j1+1].joueur=tour;
					pb.y=pb.y+80;
				}else{
		
					if ((j1>j2)){/// bas
						plateau[i1][j1-1].joueur=tour;
						pb.y=pb.y-80;
					}else{/// sur place
						if((j1==j2)&&(i1==i2))plateau[i1][j1].joueur=tour;
						
						}
					
				}
			}			
		}
}
}


void move_pion_2(int i1,int j1,int i2,int j2){// change les valeur du pion rouge dans le tab et pr
//plateau[i1][j1]      destination
plateau[i1][j1].joueur=rien;

	if ((i1<i2)){/// droite
		plateau[i1+2][j1].joueur=tour;
		pr.x=pr.x+160;
	}else{
			if ((i1>i2)){/// gauche
			plateau[i1-2][j1].joueur=tour;
			pr.x=pr.x-160;
		}else{
	
				if ((j1<j2)){/// haut
					plateau[i1][j1+2].joueur=tour;
					pr.y=pr.y+160;
				}else{
		
					if ((j1>=j2)){/// bas
						plateau[i1][j1-2].joueur=tour;
						pr.y=pr.y-160;
					}
				
						
					
				}
			}			
		}
}




int pas_colision_mur(int i1,int j1,int i2,int j2){
	//plateau[i1][j1]      direction
	if ((i1<i2)){/// droite
		if (tabv[i1][j1].ocup==oui)return non;// le deplacement ne sera pas possible
	}
	
		if ((i1>i2)&&(j1==j2)){/// gauche
			if (tabv[i1-1][j1].ocup==oui)return non;
	}
	
		if ((i1==i2)&&(j1<j2)){/// haut
			if (tabh[i1][j1].ocup==oui)return non;
	}
	
		if ((i1==i2)&&(j1>j2)){/// bas
			if (tabh[i1][j1-1].ocup==oui)return non;
	}

return oui;// alors tout va bien
}

/// //////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/// //////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
///                          fin  deplacement
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/// //////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
/// //////////////////////////////////////////////////////////////////////////////////////////////////////

 




//////////////////////////////////////////affichage///////////////////////////

void affiche_choix(int i,int j){// p.x/80  p.y/80
	POINT p1;
	POINT p2;

	if(pas_colision_mur(i,j,i-1,j)){/// gauche
			
			p1.x=(i-1)*80+8; p1.y=j*80+8;
			p2.x=(i-1)*80+72; p2.y=j*80+72;
			draw_fill_rectangle(p1,p2,jaune);	
	}
	if(pas_colision_mur(i,j,i,j+1)){/// haut
			
			p1.x=(i)*80+8; p1.y=(j+1)*80+8;
			p2.x=(i)*80+72; p2.y=(j+1)*80+72;
			draw_fill_rectangle(p1,p2,jaune);	
	
	
	}
	if(pas_colision_mur(i,j,i,j-1)){/// bas
			
			p1.x=(i)*80+8; p1.y=(j-1)*80+8;
			p2.x=(i)*80+72; p2.y=(j-1)*80+72;
			draw_fill_rectangle(p1,p2,jaune);	
	}
		if(pas_colision_mur(i,j,i+1,j)){/// droite
			p1.x=(i+1)*80+8; p1.y=j*80+8;
			p2.x=(i+1)*80+72; p2.y=j*80+72;
			draw_fill_rectangle(p1,p2,jaune);}
			
}

void affiche_plateau(){
	int i,j;
	POINT p1,p2;
	
	for(i=0;i<9;i++){
		for(j=0;j<9;j++){			
			p1.x=i*80+8; p1.y=j*80+8;
			p2.x=i*80+72; p2.y=j*80+72;
			draw_fill_rectangle(p1,p2,argent);

			if (plateau[i][j].joueur==rouge) {
				p1.x=i*80+40; p1.y=80*j+40;
				draw_fill_circle(p1,32,rouge);		
			}
			if (plateau[i][j].joueur==bleu) {
				p1.x=i*80+40; p1.y=80*j+40;
				draw_fill_circle(p1,32,bleu);		
			}
		}	
	}

for(i=0;i<9;i++){
		for(j=0;j<8;j++){
			if(tabh[i][j].ocup==oui){
				p1.x=i*80; p1.y=(j+1)*80-8;
				p2.x=i*80+80; p2.y=(j+1)*80+8;
				draw_fill_rectangle(p1,p2,darkolivegreen);
			}
		}
	
	}
	
for(i=0;i<8;i++){
		for(j=0;j<9;j++){
			if(tabv[i][j].ocup==oui){
				p1.x=(i+1)*80-8;  p1.y=j*80;
				p2.x=(i+1)*80+8;  p2.y=j*80+80;
				draw_fill_rectangle(p1,p2,darkolivegreen);
			}
		}
	
	}

p1.x=720;p1.y=0;	
p2.x=1000;p2.y=720;	
draw_fill_rectangle(p1,p2,noir);
a_qui_le_tour();
}



/// //////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/// //////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
///                           deplacement
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/// //////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
/// //////////////////////////////////////////////////////////////////////////////////////////////////////
 

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int colision_joueur(int i1,int j1,int i2,int j2){// return oui si il ya a colision sinon return non
//plateau[i1][j1]      destination.x et .y
plateau[i1][j1].joueur=rien;

	if ((i1<i2)&&(j1==j2)){/// droite
		if(plateau[i1+1][j1].joueur!=rien)return oui;
	}
		if ((i1>i2)&&(j1==j2)){/// gauche
			if (plateau[i1-1][j1].joueur!=rien)return oui;
	}
	
		if ((i1==i2)&&(j1<j2)){/// haut
			if(plateau[i1][j1+1].joueur!=rien)return oui;
			pr.y=pr.y+80;
	}
	
		if ((i1==i2)&&(j1>j2)){/// bas
			if(plateau[i1][j1-1].joueur!=rien)return oui;
	}

return non;// alors tout va bien pas de colisions
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





int droit_murh(int i,int j){
	if(i==8) return non;
	if(tabv[i][j].moitie_inf==oui) return non;
	if(tabh[i+1][j].ocup==oui) return non;

	return oui;
} 
 
int droit_murv(int i,int j){
	if(j==0) return non;
	if(tabh[i+1][j-1].moitie_droite == oui) return non;
	if(tabv[i][j-1].ocup==oui) return non;
	return oui;
}



//////////////////////////////////////////////////////////////////////////////



int autorisation_recur_test(int i,int j){// coordoné d'un pion 
	// doit prendre en plateau un plateau clean_acces()
	if ((i<8) && pas_colision_mur(i,j,i+1,j)){/// droite
		if (plateau[i+1][j].accessible==non){
			plateau[i+1][j].accessible=oui;
			autorisation_recur_test(i+1,j);
		}
	}else
		if ((i>0) && pas_colision_mur(i,j,i-1,j)){/// gauche
			if (plateau[i-1][j].accessible==non){
				plateau[i-1][j].accessible=oui;
				autorisation_recur_test(i-1,j);
			}
		}
	else
		if ((j<8) && pas_colision_mur(i,j,i,j+1)){/// haut
			if (plateau[i][j+1].accessible==non){
				plateau[i][j+1].accessible=oui;
				autorisation_recur_test(i,j+1);
			}
		}
	else{
		if ((j>0) && pas_colision_mur(i,j,i,j-1)){/// bas
			if (plateau[i][j-1].accessible==non){
				plateau[i][j-1].accessible=oui;
				autorisation_recur_test(i,j-1);
			}
		}
	}
	if (tour==rouge){
		j=0;
		while(i<9){
			if( plateau[i][j].accessible==oui)return oui;
			}
	}else{
		j=8;
		while(i<9){
			if( plateau[i][j].accessible==oui)return oui;
			}
		}
	return non;}




///////////////////////////////////////////////////////////////////////////////////////////////////







void boucle(POINT p){
	if(gagne==non){
if (quel_est_ce_clic(p)==autre){
	if(p.y<150){// get_sauvegarde(????); boucle(wait_clic());
	}
	if(p.y<300){// roll_back(????);---> suprr la fin de sauvgarde courante 
	}			// puis charge la sauvgarde courante
	if(p.y<450){// sauvgarder  copie la sauvegarde courante dans la sauvgarde finale
	}
	if(p.y>450){boucle(wait_clic());
	}
}

if (quel_est_ce_clic(p)==deplacement){
	affiche_choix(p.x/80, p.y/80);
	destination=wait_clic();
	if(  pas_colision_mur(p.x/80, p.y/80, destination.x/80, destination.y/80) == oui ){
		
		
			if(colision_joueur(p.x/80, p.y/80, destination.x/80, destination.y/80)&& 
		pas_colision_mur_deriere(p.x/80, p.y/80, destination.x/80, destination.y/80) ){
			
				
				move_pion_2 (p.x/80, p.y/80, destination.x/80, destination.y/80);
					if(tour==bleu)tour=rouge;
				else tour=bleu;	
				affiche_plateau();
				boucle(wait_clic());
		}
		else {
			if(colision_joueur(p.x/80, p.y/80, destination.x/80, destination.y/80)
			&& 
			pas_colision_mur_deriere(p.x/80, p.y/80, destination.x/80, destination.y/80) == non){
				boucle(wait_clic());
				}
			}
	
		/// ici le coup est valide, c'est un deplacement simple
		//ecrit dans la suvergarde courante la coups joué
			move_pion_1(p.x/80, p.y/80, destination.x/80, destination.y/80);
			if(tour==bleu)tour=rouge;
				else tour=bleu;	
		
		
		
	}
	else{ // il ya une colision 
	boucle(wait_clic());	
	}

}

// ici je sait que le clic est sur un mur
if(tour==rouge){
	if (quel_est_ce_clic(p)==murv){
		if (nb_mur_rouge>0){								
			if(droit_murv((p.x-8)/80,p.y/80)==oui){
				tabv[(p.x-8)/80][p.y/80].ocup=oui;
				tabv[(p.x-8)/80][(p.y/80)-1].ocup=oui;
				tabv[(p.x-8)/80][(p.y/80)-1].moitie_inf=oui;
				nb_mur_rouge=nb_mur_rouge-1;
				tour=bleu;
				affiche_plateau();
				boucle(wait_clic());
			}
		}
	}
	else {
		if (quel_est_ce_clic(p)==murh){
			if (nb_mur_rouge>0){
				if(droit_murh(p.x/80,(p.y-8)/80)==oui){
					tabh[p.x/80][(p.y-8)/80].ocup=oui;
					tabh[(p.x/80)+1][(p.y-8)/80].ocup=oui;
					tabh[(p.x/80)+1][(p.y-8)/80].moitie_droite=oui;
					nb_mur_rouge=nb_mur_rouge-1;
					tour=bleu;
					affiche_plateau();
					boucle(wait_clic());
				}
			}
		}
	}
}else{// fin du if tour rouge
	if (quel_est_ce_clic(p)==murv){
		if (nb_mur_bleu>0){
			if(droit_murv((p.x-8)/80,p.y/80)==oui){
				tabv[(p.x-8)/80][p.y/80].ocup=oui;
				tabv[(p.x-8)/80][(p.y/80)-1].ocup=oui;
				tabv[(p.x-8)/80][(p.y/80)-1].moitie_inf=oui;
				nb_mur_bleu=nb_mur_bleu-1;
				tour=rouge;
				affiche_plateau();
				boucle(wait_clic());		
			}	
		}
	}
	else {
			if (quel_est_ce_clic(p)==murh){
			if (nb_mur_rouge>0){
				if(droit_murh(p.x/80,(p.y-8)/80)==oui){
					tabh[p.x/80][(p.y-8)/80].ocup=oui;
					tabh[(p.x/80)+1][(p.y-8)/80].ocup=oui;
					tabh[(p.x/80)+1][(p.y-8)/80].moitie_droite=oui;
					nb_mur_bleu=nb_mur_bleu-1;
					tour=rouge;
					affiche_plateau();
					boucle(wait_clic());
				}
			}
		}
	}	
}
affiche_plateau();
boucle(wait_clic());
}

}// fin de boucle




int main()
{
init_graphics(1000,720);
fill_screen(blanc);
// Debut du code


init_jeu();
tour=rouge;
//printf(" salut");
//int k;k=autorisation_recur_test(pr.x/80,pr.y/80);
//printf("%d",k);
printf(" bonjour");
affiche_plateau();
POINT p; 
p=wait_clic();

boucle(p);
// Fin du code

wait_escape();
exit(0);
}
