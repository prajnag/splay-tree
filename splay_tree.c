#include "splay_tree_imp.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
int no_of_rot;

void * make_new_dictionary()
{
    dict_t *dict = (dict_t *)malloc(sizeof(struct dict));
    dict->key=0;
    dict->value=0;
    dict->left = NULL;
    dict->right = NULL;
    return dict;
}
dict_t *rotate_right(dict_t * node) 
{ 
    dict_t *temp = node->left; 
    node->left = temp->right; 
    temp->right = node; 
    return temp; 
}

dict_t *rotate_left(dict_t * node) 
{ 
    dict_t *temp = node->right; 
    node->right = temp->left; 
    temp->left = node; 
    return temp; 
} 
dict_t *splay(dict_t *dict, int key) 
{ 
    if (dict == NULL || dict->key == key) 
        return dict; 
    if (dict->key > key) 
    { 
        if (dict->left == NULL) 
        {
            return dict; 
        }
        //Left Left 
        if (dict->left->key > key) 
        {     
            dict->left->left = splay(dict->left->left, key); 
            ++no_of_rot;
            dict = rotate_right(dict); 
        } 
        else if (dict->left->key < key) //Left Right 
        { 
            dict->left->right = splay(dict->left->right, key);           
            if (dict->left->right != NULL) 
            {
                dict->left = rotate_left(dict->left); 
                ++no_of_rot;       
            }
        } 
        if(dict->left==NULL)
        {
            return dict;
        }
        else
        {
            ++no_of_rot;
            return(rotate_right(dict));
        }
    } 
    else 
    { 
        if (dict->right == NULL) 
        {
            return dict; 
        }
        // Right Left
        if (dict->right->key > key) 
        {  
            dict->right->left = splay(dict->right->left, key); 
            if (dict->right->left != NULL) 
            {
                ++no_of_rot;
                dict->right = rotate_right(dict->right); 
            }
        } 
        else if (dict->right->key < key)//Right Right
        { 
            dict->right->right = splay(dict->right->right, key); 
            dict = rotate_left(dict); 
        } 
        if(dict->right==NULL)
        {
            return dict;
        }
        else
        {
            ++no_of_rot;
            return(rotate_left(dict));  
        } 
    } 
} 

void * insert(void * dict, int key, int value)
{ 
   if(((dict_t *)dict)==NULL||((dict_t *)dict)->key==0)
    {

             ((dict_t *)dict)->key = key;
             ((dict_t *)dict)->value = value;
    }
    dict_t *temp  = make_new_dictionary();
    temp->key = key;
    temp->value = value; 
    dict = splay(((dict_t *)dict), key);  
    if (((dict_t *)dict)->key == key){
        //printf("equal\n");
        ((dict_t *)dict)->value = value;
       printf("rotations %d\n", no_of_rot);
        return ((dict_t *)dict); 
    } 
    if(((dict_t *)dict)->key < key) 
    { 
        temp->left = ((dict_t *)dict); 
        temp->right = ((dict_t *)dict)->right; 
        ((dict_t *)dict)->right = NULL; 
    } 
   else
    { 
        temp->right = ((dict_t *)dict); 
        temp->left = ((dict_t *)dict)->left; 
        ((dict_t *)dict)->left = NULL;   
    }

    printf("rotations %d\n", no_of_rot);
    return temp; 
} 
int find(void * dict,int key)
{

    dict_t *temp = splay(dict,key);
    if(temp->key == key)
        return temp->value;
    return -1;
}

void preorder(dict_t *root) 
{
    if (root!= NULL) 
    { 
        printf("%d %d\n", root->key, root->value); 
        preorder(root->left); 
        preorder(root->right); 
    } 
} 
