#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"

typedef struct TreeNode TreeNode;


struct TreeNode {
    Pair* pair;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
};

struct TreeMap {
    TreeNode * root;
    TreeNode * current;
    int (*lower_than) (void* key1, void* key2);
};

int is_equal(TreeMap* tree, void* key1, void* key2){
    if(tree->lower_than(key1,key2)==0 &&  
        tree->lower_than(key2,key1)==0) return 1;
    else return 0;
}


TreeNode * createTreeNode(void* key, void * value) {
    TreeNode * new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL) return NULL;
    new->pair = (Pair *)malloc(sizeof(Pair));
    new->pair->key = key;
    new->pair->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) {
    TreeMap * new = (TreeMap*) malloc (sizeof(TreeMap));
    new -> root = NULL;
    new -> current =  NULL;
    new->lower_than = lower_than;
    return new;
}

void insertTreeMap(TreeMap * tree, void* key, void * value) {
    tree -> current = tree -> root;
    do{
        if (is_equal (tree, key, tree -> current -> pair -> key) == 1)return;
        else{
            if (tree -> lower_than(key, tree -> current -> pair -> key) == 1){
                if(!(tree->current->left)){
                    tree -> current -> left = createTreeNode(key,value);
                    tree -> current -> left -> parent = tree -> current;
                    tree -> current = tree -> current -> left;
                    break; 
                }
                else tree -> current = tree -> current ->left;
            }
            else{
                if(!(tree->current->right)){
                    tree -> current -> right = createTreeNode(key,value);
                    tree -> current -> right -> parent = tree -> current;
                    tree -> current = tree -> current -> right;
                    break;
                } 
                else tree -> current = tree -> current -> right;
            }
        }
    }while(tree -> current);
}

TreeNode * minimum(TreeNode * x){
    while(x){
        if(!(x -> left)) return x;
        else x = x -> left;
    }

    return NULL;
}


void removeNode(TreeMap * tree, TreeNode* node) {

    if( (node -> left == NULL) && (node -> right == NULL)){
        if (node -> parent -> left){
            node -> parent -> left = NULL;
        }
        if (node -> parent -> right){
            node -> parent -> right = NULL;
        }
    }

    if ((node -> left) && (node -> right == NULL)){
        node -> parent -> right = node -> left;
        node -> left -> parent = node -> parent;
    }

    if ((node -> left) && (node -> right)){
        TreeNode* auxTree = minimum(node -> right);
        node -> pair -> key = auxTree -> pair -> key;
        node -> pair -> value = auxTree -> pair -> value;
        auxTree = NULL;
    }

}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}

Pair * searchTreeMap(TreeMap * tree, void* key) {

    TreeNode * auxTree = (TreeNode*) malloc(sizeof(TreeNode));
    auxTree = tree -> root;
    tree -> current = auxTree;

    do{
        if(is_equal(tree, key, auxTree -> pair -> key) == 1){
            tree -> current = auxTree;
            return auxTree -> pair;
        }
        else{
            if(tree -> lower_than(key, auxTree-> pair ->key) == 1){
                auxTree = tree -> current -> left;
                tree -> current -> left = auxTree;
            }
            else{
                auxTree = tree -> current -> right;
                tree -> current = auxTree;
            }
        }
    }while (auxTree);
    
    return NULL;
}


Pair * upperBound(TreeMap * tree, void* key) {
    return NULL;
}

Pair * firstTreeMap(TreeMap * tree) { 
    return minimum(tree -> root) -> pair ;
}

Pair * nextTreeMap(TreeMap * tree) {
    return NULL;
}
