  
    #include<iostream>
    using namespace std; 
      
      
    #define MAX_SIZE 100  
      
      
      
    int keys[] = {5,7,3,2,9,4,8,1,10,6};  
      
    typedef struct AVLNode{  
      
        int data;    
        int bf;  //平衡因子    
        struct AVLNode *lchild;    
        struct AVLNode *rchild;    
      
    }AVLNode;  
      
    AVLNode* SetAVLNode(int data){  
        AVLNode* root = new AVLNode;  
        root->bf = 0;  
        root->data = data;  
        root->lchild = NULL;  
        root->rchild = NULL;  
        return root;  
    }  
      
    void printDataInfo(int i){  
        cout << i << " ";  
    }  
      
      
    AVLNode* LL_Rotate( AVLNode *a ){//LL(顺时针)型调整   
      
        if (a == NULL){  
            return NULL;  
        }  
      
        AVLNode *b = a->lchild;//b指向a的左子树根结点    
        a->lchild = b->rchild; //b的右子树挂在a的左子树上    
        b->rchild = a;  
      
        a->bf = b->bf = 0;  
        return b;  
    }       
    AVLNode* RR_Rotate( AVLNode *a ){ //RR(逆时针)型调整    
        if (a == NULL){  
            return NULL;  
        }  
      
        AVLNode *b = a->rchild;//b指向a的右子树根结点    
        a->rchild = b->lchild; //b的左子树挂在a的右子树上    
        b->lchild = a;  
      
        a->bf = b->bf = 0;  
        return b;  
      
    }      
    AVLNode* LR_Rotate( AVLNode *a ){//LR(先逆后顺)型调整   
        if (a == NULL){  
            return NULL;  
        }  
        AVLNode *b = a->lchild;//b指向a的左子树根结点    
        AVLNode *c = b->rchild;//c指向b的右子树的根节点  
      
        a->lchild = c->rchild;  
        b->rchild = c->lchild;  
      
        c->lchild = a;  
        c->rchild = b;  
      
        if (c->bf == 1){  
            a->bf = -1;  
            b->bf = 0;  
        } else if (c->bf == -1){  
            a->bf = 0;    
            b->bf = 1;   
        } else {  
            b->bf = a->bf = 0;    
        }  
        c ->bf = 0;  
      
        return c;  
      
    }        
    AVLNode* RL_Rotate( AVLNode *a ){//RL(先顺后逆)型调整    
        if (a == NULL){  
            return NULL;  
        }  
      
        AVLNode *b, *c;    
        b = a->rchild;    
        c = b->lchild;    
        a->rchild = c->lchild;    
        b->lchild = c->rchild;    
        c->lchild = a;    
        c->rchild = b;    
      
        //调整平衡因子    
        if( c->bf == 1 ) {    
            a->bf = 0;    
            b->bf = -1;    
        } else if( c->bf == -1 ) {    
            a->bf = 1;    
            b->bf = 0;    
        } else  {    
            a->bf = b->bf = 0;    
        }    
        c->bf = 0;    
        return c;    
    }      
      
    /************************************************************************/  
    /* 1、找到要插入的位置，同时找到平衡因子为1的结点，因为这个结点修改之后肯定最先变为2 
    2、从平衡因子不为0的结点到插入结点，开始修改平衡因子 
    3、找到平衡因子大于等于2的根节点修改即可。 
    4、修改头结点的指针 
    */  
    /************************************************************************/  
    void insertAVL(AVLNode **root,int data){  
        AVLNode *f, *a, *b, *p, *q;  
      
        AVLNode *s = SetAVLNode(data);  
        //printDataInfo(data);  
        //头结点  
        if ((*root) == NULL){  
            (*root) = s;  
            return;  
        }  
        a=p=(*root) ;     /* a指向离s最近且平衡因子不为0的结点 */  
      
        f=q=NULL ;      /*   f指向a的父结点,q指向p父结点  */   
      
      
        //寻找插入点位置及最小不平衡树的子树    
        while( p != NULL ) {    
            if( p->data == s->data ){  
                //AVL中已经存在关键字    
                return;    
            }  
      
            if( p->bf != 0 ){   //寻找最小不平衡子树   
                a = p;    
                f = q;    
            }    
            q = p;  //q指向p父结点   
            if( s->data < p->data ){  
                p = p->lchild;   
            }else {  
                p = p->rchild;    
            }  
        }    
      
        if( s->data < q->data ){  
            q->lchild = s;   
        }  else  {     //将结点*s插入到合适的位置上去    
            q->rchild = s;    
        }  
      
        p = a; //从不为0 的结点开始修改   
        while( p != s ){    //插入结点后修改相应的平衡因子    
      
            if( s->data < p->data ) {   
      
                p->bf++;    
                p = p->lchild;    
            } else {  
      
                p->bf--;    
                p = p->rchild;    
            }    
        }    
        if( a->bf > -2 && a->bf < 2 ) {//插入结点后没有破坏平衡树    
            return;    
        }   
        if( a->bf == 2 ){   
      
            b = a->lchild;    
            if( b->bf == 1 )           //结点插在*a的左孩子的左子树中    
                p = LL_Rotate( a );    //LL型调整    
            else                       //结点插在*a的左孩子的右子树中    
                p = LR_Rotate( a );    //LR型调整    
        } else {  
            b = a->rchild;    
            if( b->bf == 1 )          //结点插在*a的右孩子的左子树中    
                p = RL_Rotate( a );   //RL型调整    
            else                      //结点插在*a的右孩子的右子树中    
                p = RR_Rotate( a );   //RR型调整    
        }    
        if( f == NULL )               //原*a是AVL树的根    
            (*root) = p;    
        else if( f->lchild == a )     //将新子树链到原结点*a的双亲结点上    
            f->lchild = p;    
        else     
            f->rchild = p;    
    }  
      
    AVLNode* createAVL(){  
        int i = 0;  
        AVLNode *root = NULL;  
        int e;
        cout << "请输入(int)数据,0为结束:";
        cin >> e;
        while (e != 0) //将0作为接受标志
        {
            insertAVL(&root, e); 
            cout << "请输入(int)数据,0为结束:"; 
            cin >> e;
        }  
        return root;  
      
    }  
      
      
    void inOrderTraverseAVL(AVLNode* root){  
        AVLNode* stack[MAX_SIZE];  
        int top = -1;  
      
        AVLNode* p = root;  
        while(p != NULL || top> -1){  
            while ( p!= NULL){  
                stack[++top] = p;  
                p = p->lchild;  
            }  
      
            p = stack[top--];  
            printDataInfo(p->data);  
            p = p->rchild;  
        }  
      
    }  
void  PreOrderTraverseAVL(AVLNode* root)
{
    if(root)
    {
        cout << root->data << " ";
        PreOrderTraverseAVL(root->lchild);
        PreOrderTraverseAVL(root->rchild);
    }
}
void PostOrderTraverseAVL(AVLNode *root)
{
    if(root)
    {
        PostOrderTraverseAVL(root->lchild);
        PostOrderTraverseAVL(root->rchild);
        cout << root->data << " ";
    }
}
      
    int main(){  
        AVLNode* root = createAVL();  
        cout << "中序遍历:";
        inOrderTraverseAVL(root);
        cout << endl;
        cout << "先序遍历:";
        PreOrderTraverseAVL(root);
        cout << endl;
        cout << "后序遍历:";
        PostOrderTraverseAVL(root);
        cout << endl;
      return 0;
    }  