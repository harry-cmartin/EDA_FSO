#include <stdlib.h>

typedef int Key;

typedef struct {
  Key key;
  int value;
} Item;

#define key(A) ((A).key)
#define lessKey(A, B) ((A) < (B))
#define less(A, B) (lessKey(key(A), key(B)))

typedef struct Node {
  Node *left, *right;
  Item item;
} Node;

Node *inserir(Node *root, Item item) {
  if (root == NULL) {
    
    Node *newNode = malloc(sizeof(Node));
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->item = item;

    return root;
  }

  if (less(root->item, item)) {
    root->right = inserir(root->right, item);
  } else if (less(item, root->item)) {
    root->left = inserir(root->left, item);
  } else {
    root->item = item;
  }

  return root;
}

Node *buscar(Node *root, Key k) {
  if (root == NULL) {
    return NULL;
  }

  Key actualKey = key(root->item);

  if (lessKey(actualKey, k)) {
    return buscar(root->right, k);
  } else if (lessKey(k, actualKey)) {
    return buscar(root->left, k);
  } else {
    return root;
  }
}







Node *minNode(Node *root) {
  if (root->left == NULL) {
    return root;
  }

  return minNode(root->left);
}

Node *deleteMinNode(Node *root) {
  if (root->left == NULL) {
    return root->right;
  }

  root->left = deleteMinNode(root->left);
  return root;
}

Node *deleteNode(Node *root, Key k) {
  if (root == NULL) {
    return NULL;
  }

  Key actualKey = key(root->item);

  if (lessKey(actualKey, k)) {
    root->right = deleteNode(root->right, k);
  } else if (lessKey(k, actualKey)) {
    root->left = deleteNode(root->left, k);
  } else {
    if (root->left == NULL) {
      Node *aux = root->right;
      free(root);
      return aux;
    }

    if (root->right == NULL) {
      Node *aux = root->left;
      free(root); 
      return aux;
    }

    Node *aux = root;
    root = minNode(aux->right);
    root->left = aux->left;
    root->right = deleteMinNode(aux->right);
    free(aux);
  }

  return root;
}