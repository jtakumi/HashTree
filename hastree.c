/*  treebfs.c �񕪖؂̍ő�l��T���C�񕪖؂��m�[�h�𑖍�����v���O���� */
#include <stdio.h>
#include <stdlib.h>

typedef struct treex{
   int element;
   struct treex *left, *right;
}tree;

tree *root;

/* -----�@�ǉ��IQueue�Ŏg�p����z��C�J�E���^�̐ݒ� ----  */
#define N 8
tree *Queue[N];		            // tree�̃|�C���^�����邽�߂̃|�C���^�^�z��Queue[]��錾
int qentry = 0, qhead = 0;   //����搶�̎����ɍ��킹���C�������̖��̈ʒu

/* -----  �����Ɋ֐��̒�`��}�� ----- */

/* -----�ǉ��I enQueue�̏��� ----  */
void enQueue(tree* p) {
    if (p == NULL) {
        return;                 //�T���m�[�h�̎q�m�[�h���Ȃ��Ȃ�Βǉ������ɖ߂�D
    }
    Queue[qentry++]=p;			     //p��z����v�f�̍Ō���Ɋi�[����
      if (qentry == N)
      {
          qentry = 0;   		         //�z��������ς��܂Ŏg������z��̐擪�ɖ߂�
      }
      Queue[qentry] = NULL;			     //�I������p��NULL����������
}

/* -----�ǉ��I deQueue�̏��� ----  */
tree* deQueue (void){
   tree* rval;                //�|�C���^���߂�l�Ȃ̂Ń|�C���^�^�̊֐��Ƃ���D
   rval = Queue[qhead++];                   //���ɒT������m�[�h�̃A�h���X���i�[����ϐ�
   if (qhead == N){
      qhead = 0;
   }                           //�z�񂢂��ς��܂�qhead�𓮂�������z��̐擪��
   return rval;
}

/* �V�K�̖؂̃m�[�h�̃������̈���m�ۂ��āC�����ɒlval��������֐� */
tree *newnode(int val){
   tree *p;
   p = (tree *)malloc(sizeof(tree));
   p->element = val;
   p->left = NULL;             // �����̃m�[�h���� (NULL) �Ƃ���
   p->right= NULL;             // �E���̃m�[�h����(NULL) �Ƃ���
   return p;
}

/* �񕪖؂�����������F���[�g�m�[�h���쐬���l������֐� */
void initialize(int val){
   root = newnode(val);
}

/* �񕪖؂ɐV�����m�[�h��}�����Ēl������ċA�֐� */
void insert(int val, tree *p){
   if(val > p->element){
      if(p->right !=NULL) insert(val, p->right);
      else p->right = newnode(val);
   }else if (val < p->element){
      if(p->left != NULL) insert(val, p->left);
      else p->left = newnode(val);
   }else return;
}


/* �񕪖؂̒��̍ő�l�̃m�[�h��T���Ă��̃|�C���^��Ԃ��ċA�֐� */
tree *searchmax(tree *p){
   if(p->right==NULL) return p;
   else return searchmax(p->right);
}

/*  �O�������̍ċA�֐� */
void preorder(tree *p){
   if(p!=NULL){
      printf(" %d", p->element);                // 1. ���̃m�[�h�̒l��\��
      preorder(p->left);                        // 2. ���̃m�[�h�̍����̕����؂�O������
      preorder(p->right);                       // 3. ���̃m�[�h�̉E���̕����؂�O������
   }
}

/* �ԏ������̍ċA�֐� */
void inorder(tree *p){
   if(p!=NULL){
      inorder(p->left);                         // 1. ���̃m�[�h�̍����̕����؂��ԏ�����
      printf(" %d", p->element);                // 2. ���̃m�[�h�̒l��\��
      inorder(p->right);                        // 3. ���̃m�[�h�̉E���̕����؂��ԏ�����
   }
}

 /* �㏇�����̍ċA�֐� */
void postorder(tree *p){
   if(p!=NULL){
      postorder(p->left);                       // 1. ���̃m�[�h�̍����̕����؂��㏇����
      postorder(p->right);                      // 2. ���̃m�[�h�̉E���̕����؂��㏇����
      printf(" %d", p->element);                // 3. ���̃m�[�h�̒l��\��
   }
}

/* �ǉ��I�@���x���������̊֐� */
void traversal_bfs(tree *root){
   if (root != NULL){
       enQueue(root);		                          //�܂���root�̃A�h���X���L���[�ɓ����D
      while(1){
          tree *p= deQueue();			                  //���ɒT������A�h���X������Ă���p�Ƃ���
         if(p==NULL){                         //�I���̏����́H
            break;                              
         }
         printf(" %d", p->element);             //�K�⒆�̃m�[�h�̒l���v�����g
         enQueue(p->left);		                  	//�����q�m�[�h�̃A�h���X���L���[�ɒǉ�
         enQueue(p->right);			                //�E���q�m�[�h�̃A�h���X���L���[�ɒǉ�
      }
   }else{
      printf("root�̃A�h���X�����������悤�ł�\n");   //������̂���
      }
}

int main(void){
   int i, nums[]={ 4, 8, 10, 6, 5, 2, 7, 3, 9, 1 };
	
   initialize(nums[0]);
   for(i=1; i<10; i++) insert(nums[i], root);
   printf("�ő�l�F%d\n", searchmax(root)->element);    // �񕪖؂̒��̍ő�l�i��ԉE���j�̃m�[�h�T��
   printf("�O�������F"); preorder(root); printf("\n");  // �񕪖؂̑S�m�[�h��O������
   printf("�ԏ������F"); inorder(root); printf("\n");   // �񕪖؂̑S�m�[�h���ԏ�����
   printf("�㏇�����F"); postorder(root); printf("\n"); // �񕪖؂̑S�m�[�h���㏇����
   printf("���x��������"); traversal_bfs(root); printf("\n"); // �񕪖؂̑S�m�[�h�����x��������
   return 0;
}