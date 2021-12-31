/*  treebfs.c 二分木の最大値を探索，二分木をノードを走査するプログラム */
#include <stdio.h>
#include <stdlib.h>

typedef struct treex{
   int element;
   struct treex *left, *right;
}tree;

tree *root;

/* -----　追加！Queueで使用する配列，カウンタの設定 ----  */
#define N 8
tree *Queue[N];		            // treeのポインタを入れるためのポインタ型配列Queue[]を宣言
int qentry = 0, qhead = 0;   //荻野先生の資料に合わせた，資料中の矢印の位置

/* -----  ここに関数の定義を挿入 ----- */

/* -----追加！ enQueueの処理 ----  */
void enQueue(tree* p) {
    if (p == NULL) {
        return;                 //探索ノードの子ノードがないならば追加せずに戻る．
    }
    Queue[qentry++]=p;			     //pを配列内要素の最後尾に格納する
      if (qentry == N)
      {
          qentry = 0;   		         //配列をいっぱいまで使ったら配列の先頭に戻る
      }
      Queue[qentry] = NULL;			     //終了判定用のNULLを書き込む
}

/* -----追加！ deQueueの処理 ----  */
tree* deQueue (void){
   tree* rval;                //ポインタが戻り値なのでポインタ型の関数とする．
   rval = Queue[qhead++];                   //次に探索するノードのアドレスを格納する変数
   if (qhead == N){
      qhead = 0;
   }                           //配列いっぱいまでqheadを動かしたら配列の先頭へ
   return rval;
}

/* 新規の木のノードのメモリ領域を確保して，そこに値valを代入する関数 */
tree *newnode(int val){
   tree *p;
   p = (tree *)malloc(sizeof(tree));
   p->element = val;
   p->left = NULL;             // 左下のノードを空 (NULL) とする
   p->right= NULL;             // 右下のノードを空(NULL) とする
   return p;
}

/* 二分木を初期化する：ルートノードを作成し値を入れる関数 */
void initialize(int val){
   root = newnode(val);
}

/* 二分木に新しいノードを挿入して値を入れる再帰関数 */
void insert(int val, tree *p){
   if(val > p->element){
      if(p->right !=NULL) insert(val, p->right);
      else p->right = newnode(val);
   }else if (val < p->element){
      if(p->left != NULL) insert(val, p->left);
      else p->left = newnode(val);
   }else return;
}


/* 二分木の中の最大値のノードを探してそのポインタを返す再帰関数 */
tree *searchmax(tree *p){
   if(p->right==NULL) return p;
   else return searchmax(p->right);
}

/*  前順走査の再帰関数 */
void preorder(tree *p){
   if(p!=NULL){
      printf(" %d", p->element);                // 1. そのノードの値を表示
      preorder(p->left);                        // 2. そのノードの左側の部分木を前順走査
      preorder(p->right);                       // 3. そのノードの右側の部分木を前順走査
   }
}

/* 間順走査の再帰関数 */
void inorder(tree *p){
   if(p!=NULL){
      inorder(p->left);                         // 1. そのノードの左側の部分木を間順走査
      printf(" %d", p->element);                // 2. そのノードの値を表示
      inorder(p->right);                        // 3. そのノードの右側の部分木を間順走査
   }
}

 /* 後順走査の再帰関数 */
void postorder(tree *p){
   if(p!=NULL){
      postorder(p->left);                       // 1. そのノードの左側の部分木を後順走査
      postorder(p->right);                      // 2. そのノードの右側の部分木を後順走査
      printf(" %d", p->element);                // 3. そのノードの値を表示
   }
}

/* 追加！　レベル順走査の関数 */
void traversal_bfs(tree *root){
   if (root != NULL){
       enQueue(root);		                          //まずはrootのアドレスをキューに入れる．
      while(1){
          tree *p= deQueue();			                  //次に探索するアドレスを取ってきてpとする
         if(p==NULL){                         //終了の条件は？
            break;                              
         }
         printf(" %d", p->element);             //訪問中のノードの値をプリント
         enQueue(p->left);		                  	//左側子ノードのアドレスをキューに追加
         enQueue(p->right);			                //右側子ノードのアドレスをキューに追加
      }
   }else{
      printf("rootのアドレスがおかしいようです\n");   //万が一のため
      }
}

int main(void){
   int i, nums[]={ 4, 8, 10, 6, 5, 2, 7, 3, 9, 1 };
	
   initialize(nums[0]);
   for(i=1; i<10; i++) insert(nums[i], root);
   printf("最大値：%d\n", searchmax(root)->element);    // 二分木の中の最大値（一番右下）のノード探索
   printf("前順走査："); preorder(root); printf("\n");  // 二分木の全ノードを前順走査
   printf("間順走査："); inorder(root); printf("\n");   // 二分木の全ノードを間順走査
   printf("後順走査："); postorder(root); printf("\n"); // 二分木の全ノードを後順走査
   printf("レベル順走査"); traversal_bfs(root); printf("\n"); // 二分木の全ノードをレベル順走査
   return 0;
}