#include <stdio.h>    /*  gcc -g exo1.c -o TOTO   valgrind ./TOTO */
#include <stdlib.h>

struct element { int val;struct element* suiv;};
typedef struct element element;
typedef element* liste;

liste liste_vide(){return NULL;	}

int test_vide(liste l){
if (l != NULL)return 0;return 1;	}

void affiche (liste l){
while(!test_vide(l))
{printf("%d  " ,l->val);
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
	if(liste_vide(l)){return ajout_debut(l,e);}
	if (l==NULL || e<l->val){return ajout_debut(l,e);}
	liste tmp=memory();
	tmp=l;
	liste new=memory();
	new->val=e;
	while (tmp->suiv!=NULL && e>tmp->suiv->val){
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


int recherche(liste l,int e){
if (liste_vide(l)) return 0;
if(l->val==e) return 1;
else {return recherche(l->suiv,e);}
}

liste suppr(liste l,int e){
	liste temp=l;
if (liste_vide(l)) return l;
if (l->val==e){temp=l->suiv;
free(l);
return temp;}
while (temp->suiv!=NULL && temp->suiv->val!=e ){
	temp=temp->suiv;}
	if (temp->suiv!=NULL){
	liste g=temp->suiv;
	temp->suiv=temp->suiv->suiv;
	free(g);}
	return l;
}

liste tri_fusion(liste l1,liste l2){
	if (liste_vide(l1)) return l2;
	if (liste_vide(l2)) return l1;
	liste debut,fin;
	if (l1->val<l2->val){
		debut=l1;
		fin=l1;
		l1=l1->suiv;} 
	else{
		debut=l2;
		fin=l2;l2=l2->suiv;}
	while (l1!=NULL && l2!=NULL){
		if(l1->val<l2->val){
			fin->suiv=l1;
			l1=l1->suiv;
			fin=fin->suiv;
		}
		else{
			fin->suiv=l2;
			l2=l2->suiv;
			fin=fin->suiv;
		}}
		if (l1==NULL){fin->suiv=l1;}
		else fin->suiv=l2;
	return debut;	
	
	
}


 


int main(){
liste l;
l=NULL;	

l=ajout_trie(l,1);
l=ajout_trie(l,2);
l=ajout_trie(l,3);
	affiche(l);
printf("\n");
liste m; m=NULL; 
m=ajout_trie(m,4);
m=ajout_trie(m,5);
m=ajout_trie(m,6);
affiche(m);

printf("\n");
l=concat(l,m);
affiche(l);

printf("\n");printf("\n");
l=suppr(l,1);
affiche(l);

} 
