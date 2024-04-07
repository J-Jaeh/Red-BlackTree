#include "rbtree.h"

#include <stdlib.h>

/*
1. 센티넬 노드생성
2. 트리초기화 -> 트리의 포인터들이 센티넬노드를 지목하도록.
*/
rbtree *new_rbtree(void) {
  node_t *sentinel = (node_t*)calloc(1,sizeof(node_t));
  rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));

  sentinel->color =RBTREE_BLACK;
  p->nil = sentinel;
  p->root = sentinel;

  return p;
}

/* rotation
받아야할값 .. 일단 target 노드 .. 나는 부모로 올릴 노드를 받고싶은뎅 아닌가 ? 

*/
void right_rotation(rbtree *tree,node_t *x_node)
{

}

void left_rotation(rbtree *tree,node_t *x_node)
{   
  //대상노드의 오른쪽 즉 temp가 x_node 의 부모가 될예정이다. 
  node_t *temp = x_node -> right;
  
  //내릴대상의 오른쪽에  올릴 대상의 왼쪽 서브트리를 붙여준다
  x_node ->right = temp -> left;

  // 근데 올릴 대상의 왼쪽 서비트리가 nil노드가 아니라면 왼쪽 서브트리의 부모 바꿔줘야지~
  if (temp->left != tree->nil) temp->left->parent = x_node;
  
  //temp 의 부모는 지금  x 인데 x의 부모가 temp의 부모가되고 x의 부모는 temp가 되는것
  temp -> parent = x_node -> parent;

  /*
  x의 부모가 누군지 검증 + x가 왼쪽소속인지 오른쪽소속인지 
  근데 이걸 왜 temp의 부모까지 바꿔주고 하는지는 의문
  */
  if (x_node->parent == tree->nil) tree->root = temp; //tree의 root가 그전에는 x를 가리키고 있엇겠쥬
  else if (x_node->parent->left == x_node) x_node->parent->left = temp;
  else x_node->parent->right = temp;

  // temp 를 x의 부모만들기 .
  temp->left = x_node;
  x_node->parent = temp;
}

void delete_rbtree(rbtree *t) {
  // TODO: reclaim the tree nodes's memory
  free(t);
}

node_t *rbtree_insert(rbtree *t, const key_t key) {
  // TODO: implement insert
  return t->root;
}

node_t *rbtree_find(const rbtree *t, const key_t key) {
  // TODO: implement find
  return t->root;
}

node_t *rbtree_min(const rbtree *t) {
  // TODO: implement find
  return t->root;
}

node_t *rbtree_max(const rbtree *t) {
  // TODO: implement find
  return t->root;
}

int rbtree_erase(rbtree *t, node_t *p) {
  // TODO: implement erase
  return 0;
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
  // TODO: implement to_array
  return 0;
}
