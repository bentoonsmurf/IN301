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
int nb_ele(liste l){int n;n=0;
    
    if (test_vide(l))return 0;
return 1+nb_ele(l->suiv);
}

liste ajout_fin(liste l,int e){
	liste tmp=l;
	if(test_vide) return ajout_debut(l,e);
	while (tmp->suiv!=NULL){tmp=tmp->suiv;}
	liste new=memory();
	new->val=e; 
	new->suiv=NULL;
	tmp->suiv=new;
	return l;
}
liste ajout_trie(liste l,int e){
	liste tmp=l;
	liste new=memory();
	new->val=e;
	if (l!=NULL || e<l->val){return ajout_debut(l,e);}
	while (tmp->suiv==NULL && e>tmp->suiv->val){
		tmp=tmp->suiv;}
	new->suiv=tmp->suiv;
	tmp->suiv=new;
	return l;
	
}



liste concat(liste l, liste m){
	liste tmp=l;
while (tmp->suiv!=NULL){tmp=tmp->suiv;}
tmp->suiv=m;
return l;
}



int main(){
liste l;l=NULL;	

l=ajout_debut(l,1);
l=ajout_debut(l,2);
l=ajout_debut(l,3);
	affiche(l);

liste m; m=NULL;
m=ajout_debut(m,4);
m=ajout_debut(m,5);
m=ajout_debut(m,6);
affiche(m);

printf("\n");
l=concat(l,m);
//affiche(l);

l=ajout_trie(l,3);
affiche(l);
}
