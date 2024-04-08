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
void right_rotation(rbtree *tree,node_t *y_node)
{
  node_t *temp = y_node -> left;

  y_node -> left = temp -> right;

  if (temp -> right != tree -> nil) temp->right->parent = y_node;

  temp -> parent = y_node -> parent;

  if (y_node->parent == tree->nil) tree->root =temp;
  else if (y_node->parent->left == y_node) y_node->parent->left = temp;
  else y_node->parent->right = temp;

  temp -> right = y_node;
  y_node->parent = temp;
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

// 재귀로 구현해도 할만할듯!
void rbtree_insert_fixup(rbtree *tree, node_t *new_node)
{
  while(new_node -> parent -> color == RBTREE_RED)
  {
    // 부모가 할아버지 왼쪽일경우
    if (new_node -> parent == new_node -> parent -> parent-> left)
    {
      node_t *uncle = new_node -> parent -> parent -> right;
      // 부모와 삼촌이 색이 같은 Red일 경우
      if (uncle->color==RBTREE_RED)
      {
        //부모,삼촌 / 할아버지 컬러체인지
        new_node->parent->color = RBTREE_BLACK;
        uncle -> color = RBTREE_BLACK;
        new_node->parent->parent->color = RBTREE_RED;
        //할어버지 검증돌리러감 -> 회전균형까지마치고 확인
        new_node = new_node->parent->parent;
      }else if (new_node == new_node -> parent ->right)
      {
        new_node = new_node -> parent;
        left_rotation(tree,new_node);
      }
      new_node -> parent -> color = RBTREE_BLACK;
      new_node -> parent -> parent -> color = RBTREE_RED;
      right_rotation(tree,new_node->parent->parent);
    }else// mirror case 
    {
      node_t *uncle = new_node -> parent -> parent -> left;
      if (uncle->color == RBTREE_RED)
      {
        new_node->parent->color = RBTREE_BLACK;
        uncle -> color = RBTREE_BLACK;
        new_node->parent->parent->color = RBTREE_RED;

        new_node=new_node->parent->parent;
      }else if (new_node == new_node -> parent -> left)
      {
        new_node = new_node -> parent;
        right_rotation(tree,new_node);
      }
      new_node -> parent -> color = RBTREE_BLACK;
      new_node -> parent -> parent -> color = RBTREE_RED;
      left_rotation(tree,new_node->parent->parent);
    }  
  }
  tree->root->color = RBTREE_BLACK;
}


/*
삽입후 rbtree 규칙을 깨는 경우 벨런싱 작업을 해줘야함
1. root 노드가 RED로 되는경우 
2. 삽입한곳의 부모가 RED 인경우
---
- 삽입과정중 중복key 검사해야함. 중복key 검사통과해야지 calloc 할당 => x 중복키 삽입가능임
-- 중복키가 나온다면 오른쪽으로 보내줘서 크기 검사시켜야 중위순회때 잘나올듯? 
*/
node_t *rbtree_insert(rbtree *t, const key_t key) {
  node_t *temp_parent = t->nil;
  node_t *search_leaf = t->root;
  //nil 까지 들어가서 그전에 나온 부모가 삽입위치임
  while (search_leaf != t->nil)
  {
      temp_parent=search_leaf;
      if (key < search_leaf->key) // 삽입값이 현재 키값보다 작으면 
      {
        search_leaf = search_leaf -> left;
      }else // 같거나 크면 오른쪽으로감 !
      {
        search_leaf = search_leaf -> right;
      }
  }
  // 삽입위치 찾음
  node_t *new_node = (node_t*)calloc(1,sizeof(node_t));
  new_node -> parent = temp_parent;

  if (temp_parent == t->nil)
  {
    t->root = new_node;
  }else if (key < temp_parent->key)
  {
    temp_parent->left = new_node;
  }else
  {
    temp_parent->right = new_node;
  }
  new_node -> key = key;
  new_node -> color = RBTREE_RED;
  new_node -> left = t->nil;
  new_node -> right = t->nil;

  //보정작업 함수 호출
  rbtree_insert_fixup(t,new_node);
  return new_node;
}

node_t *rbtree_find(const rbtree *t, const key_t key) {
  node_t *search_node = t->root;

  while(search_node != t->nil)
  {
    if(search_node->key == key) return search_node;
    else if (search_node -> key < key) search_node = search_node -> right;
    else search_node = search_node -> left;
  }

  return NULL;
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
