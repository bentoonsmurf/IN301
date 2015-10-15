#include <stdio.h>
#include <stdlib.h>

struct element { int val;struct element* suiv;};
typedef struct element element;
typedef element* liste;

liste liste_vide(){return NULL;	}

int test_vide(liste l){
if (l != NULL)return 0;return 1;	}

void affiche (liste l){
while(!test_vide(l))
{printf("%d\n" ,l->val);
l=l->suiv;}             /*  (*l).suiv==l->suiv */
}

void libere(liste l){
	liste temp;
	if (!liste_vide(l)){
		temp=l->suiv;
		free(l);
		l=temp;
		libere(l);
	}		
}
liste memory(){
return malloc(sizeof(element));
}

liste ajout_debut(liste l,int e){
	liste tmp;
	tmp=memory();
	tmp->val=e;
	tmp->suiv=l;
	return tmp;
	}
/*int nb_ele(liste l){
	return 0;
}
*/



int main(){
liste l;l=NULL;	

l=ajout_debut(l,1);
l=ajout_debut(l,2);
l=ajout_debut(l,3);
	affiche(l);
}
