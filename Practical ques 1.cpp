#include<iostream>
#include<stdlib.h>
#include<stack>

using namespace std;

class BSTNode
{
    public:
    BSTNode()
    {
        left = right = parent = 0;
        el=-1;
    }
    BSTNode(const int& e, BSTNode *p = 0, BSTNode *l = 0, BSTNode *r = 0)
    {
        el = e; left = l; right = r; parent = p;
        colour = false;
    }
    int el;
    bool colour;
    BSTNode *left, *right, *parent;
};

class BST
{
    public:
    BST()
    {
        root = 0;
    }

    ~BST()
    {
        clear();
    }

    void clear()
    {
        clear(root);
        root = 0;
    }

    bool isEmpty()
    {
        return root == 0;
    }

    int search(int& el)
    {
        return search(root,el);
    }

    void iterativePreorder();
    void iterativeInorder();
    void insert(int&);
    void insertfixup(BSTNode*);
    void deletefixup(BSTNode*);
    void leftrotate(BSTNode*);
    void rightrotate(BSTNode*);
    void findAndDeleteByCopying(int&);
    void deleteByCopying(BSTNode*&);

    protected:
    BSTNode* root;
    void clear(BSTNode*);
    int search(BSTNode*,int&);

    void visit(BSTNode* p)
    {
        if(p->el==-1)
            return;

        cout <<"\nElement: "<< p->el <<"\t Colour: ";

        if(p->colour)
            cout<<" Black";
        else 
            cout<<" Red";
    }
};

int BST::search(BSTNode* p,int& el)
{
    while (p != 0)
    {
        if (el == p->el)
        {
            cout<<"\n"<<p->el<<"colour : ";

            if(p->colour)
                cout<<" black";
            else
                cout<<" red";

            return 0;
        }
        else if (el < p->el)
            p = p->left;
        else
            p = p->right;
    }
    return -1;
}

void BST::iterativePreorder()
{
    stack<BSTNode*> travStack;
    BSTNode *p = root;
    if (p != 0)
    {
        travStack.push(p);
        while (!travStack.empty())
        {
            p = travStack.top();
            travStack.pop();
            visit(p);

            if (p->right != 0)
                travStack.push(p->right);

            if (p->left != 0)
                travStack.push(p->left);
        }
    }
}

void BST::insert(int& el)
{
    BSTNode *p = root, *prev = 0;
    while (p != 0)
    {
        prev = p;
        if (el < p->el)
            p = p->left;
        else
            p = p->right;
    }

    if (root == 0)
        p = root = new BSTNode(el);
    else if (el < prev->el)
        p = prev->left = new BSTNode(el,prev);
    else
        p = prev->right = new BSTNode(el,prev);

    insertfixup(p);
}

void BST::leftrotate(BSTNode* x)
{
    BSTNode* y=x->right;
    x->right=y->left;

    if(y->left!=0)
        (y->left)->parent=x;

    y->parent=x->parent;

    if(x->parent==0)
        root=y;
    else if(x==(x->parent)->left)
        (x->parent)->left=y;
    else
        (x->parent)->right=y;

    y->left=x;
    x->parent=y;
}

void BST::rightrotate(BSTNode* x)
{
    BSTNode* y=x->left;
    x->left=y->right;

    if(y->right!=0)
        (y->right)->parent=x;

    y->parent=x->parent;

    if(x->parent==0)
        root=y;
    else if(x==(x->parent)->right)
        (x->parent)->right=y;
    else
        (x->parent)->left=y;

    y->right=x;
    x->parent=y;
}
void BST::deletefixup(BSTNode* x)
{
    BSTNode* w;
    BSTNode* nil=new BSTNode();
    nil->colour=true;

    while(x!=root && x->colour)
    {
        if(x==(x->parent)->left)
        {
            w=((x->parent)->right)?((x->parent)->right):nil;
            if(!(w->colour))
            {
                w->colour=true;
                (x->parent)->colour=false;
                leftrotate(x->parent);
                w=((x->parent)->right)?((x->parent)->right):nil;
            }

            if((w->left)?(w->left)->colour:true && (w->right)?(w->right)->colour:true)
            {
                w->colour=false;
                x=x->parent;
            }
            else
            {
                if((w->right)?(w->right)->colour:true)
                {
                    if(w->left)
                        (w->left)->colour=true;

                    w->colour=false;
                    rightrotate(w);
                    w=((x->parent)->right)?((x->parent)->right):nil;
                }
                w->colour=(x->parent)->colour;
                (x->parent)->colour=true;
                if(w->right)
                    (w->right)->colour=true;

                leftrotate(x->parent);
                x=root;
            }
        }
        else
        {
            w=((x->parent)->left)?((x->parent)->left):nil;
            if(!(w->colour))
            {
                w->colour=true;
                (x->parent)->colour=false;
                rightrotate(x->parent);
                w=((x->parent)->left)?((x->parent)->left):nil;
            }

            if((w->left)?(w->left)->colour:true && (w->right)?(w->right)->colour:true)
            {
                w->colour=false;
                x=x->parent;
            }
            else
            {
                if((w->left)?(w->left)->colour:true)
                {
                    if(w->right)
                        (w->right)->colour=true;

                    w->colour=false;
                    leftrotate(w);
                    w=((x->parent)->left)?((x->parent)->left):nil;
                }
                w->colour=(x->parent)->colour;
                (x->parent)->colour=true;
                if(w->left)
                    (w->left)->colour=true;
                    
                rightrotate(x->parent);
                x=root;
            }
        }
    }
    x->colour=true;
}

void BST::insertfixup(BSTNode* z)
{
    BSTNode* y;
    BSTNode* inil=new BSTNode();
    inil->colour=true;
    while((z->parent)!=0 && ((z->parent)->parent)!=0 && !((z->parent)->colour))
    {
        if(z->parent==((z->parent)->parent)->left)
        {
            y=(((z->parent)->parent)->right)?(((z->parent)->parent)->right):inil;
            if(!(y->colour))
            {
                (z->parent)->colour=true;
                y->colour=true;
                ((z->parent)->parent)->colour=false;
                z=(z->parent)->parent;
            }
            else
            {
                if(z==(z->parent)->right)
                {
                    z=z->parent;
                    leftrotate(z);
                }
                (z->parent)->colour=true;
                ((z->parent)->parent)->colour=false;
                rightrotate((z->parent)->parent);
            }
        }
        else
        {
            y=(((z->parent)->parent)->left)?(((z->parent)->parent)->left):inil;
            if(!(y->colour))
            {
                (z->parent)->colour=true;
                y->colour=true;
                ((z->parent)->parent)->colour=false;
                z=(z->parent)->parent;
            }
            else
            {
                if(z==(z->parent)->left)
                {
                    z=z->parent;
                    rightrotate(z);
                }
                cout<<"\n colour ";
                (z->parent)->colour=true;
                ((z->parent)->parent)->colour=false;
                leftrotate((z->parent)->parent);
            }
        }
    }
    root->colour=true;
}

void BST::findAndDeleteByCopying(int& el)
{
    BSTNode *node = root, *prev = 0;
    while (node != 0)
    {
        if (node->el == el)
            break;

        prev = node;

        if (el < node->el)
            node = node->left;
        else
            node = node->right;
    }

    if (node != 0 && node->el == el)
    {
        if (node == root)
            deleteByCopying(root);
        else if (prev->left == node)
            deleteByCopying(prev->left);
        else
            deleteByCopying(prev->right);
    }
    else if (root != 0)
        cout << "Element is not in the tree\n";
    else
        cout << "The tree is empty\n";
}
void BST::deleteByCopying(BSTNode*& node)
{
    bool check,check2;
    BSTNode *previous, *tmp = node,*par=node->parent;
    BSTNode *cnil=new BSTNode();
    cnil->colour=true;
    cnil->parent=par;

    if (node->right == 0)
    {
        node = node->left;
        check=false;
    }
    else if (node->left == 0)
    {
        node = node->right;
        check=false;
    }
    else
    {
        tmp = node->left;
        previous = node;
        while (tmp->right != 0)
        {
            previous = tmp;
            tmp = tmp->right;
        }

        node->el = tmp->el;
        node->colour = tmp->colour;

        if(tmp->left)
            (tmp->left)->parent=previous;
        else
            cnil->parent=previous;
            
        if (previous == node)
        {
            previous ->left = tmp->left;
            check=true;
            check2=false;
        }
        else
        {
            previous ->right = tmp->left;
            check=true;
            check2=true;
        }
    }

    if(tmp->colour)
    {
        if(!check)
        {
            if(!node)
                node=cnil;

            node->parent=par;
            deletefixup(node);

            if(par && par->left==cnil)
                par->left=0;
            else if(par && par->right==cnil)
                par->right=0;
        }
        else if(check2)
        {
            if(!previous->right)
                previous->right=cnil;

            deletefixup(previous->right);

            if(previous->right==cnil)
                previous->right=0;
        }
        else
        {
            if(!previous->left)
                previous->left=cnil;

            deletefixup(previous->left);

            if(previous->left==cnil)
                previous->left=0;
        }
    }
    delete cnil;
    delete tmp;
}

void BST::clear(BSTNode * p)
{
    if(p!=0)
    {
        clear(p->left);
        clear(p->right);
        delete p;
    }
}

void BST::iterativeInorder()
{
    stack<BSTNode*> travStack;
    BSTNode *p = root;
    while (p != 0)
    {
        while (p != 0)
        {
            if (p->right)
            travStack.push(p->right);
            travStack.push(p);
            p = p->left;
        }

        p = travStack.top();
        travStack.pop();

        while (!travStack.empty() && p->right == 0)
        {
            visit(p);
            p = travStack.top();
            travStack.pop();
        }

        visit(p);

        if (!travStack.empty())
        {
            p = travStack.top();
            travStack.pop();
        }
        else
            p = 0;
    }
}

int main()
{
    BST t1;
    int dtchoice;
    do
    {
        int x;
        system("cls");
        cout<<"\nMENU \n1.Insertion.\n2.Deletion.\n3.Search a number.\n4.Display its preorder and inorder transversals.\n5.Exit.\n \n Enter your choice:\t";
        cin>>dtchoice;

        switch(dtchoice)
        {
            case 1: system("cls");
                        cout<<"\nEnter the number to be inserted in the tree-\n";
                        cin>>x;
                        t1.insert(x);
                        break;

            case 2: system("cls");
                        cout<<"\nEnter the number to be deleted-\n";
                        cin>>x;
                        t1.findAndDeleteByCopying(x);
                        system("pause");
                        break;

            case 3: system("cls");
                        if(t1.isEmpty())
                        cout<<"\nTree is empty.\n";
                        else{
                            cout<<"\nEnter the number to be searched-\n";

                        cin>>x;
                        int a=t1.search(x);
                        if(a==-1)
                            cout<<"\nNumber is not present.";}

                        system("pause");
                        break;

            case 4: system("cls");
                        if(t1.isEmpty())
                            cout<<"\nTree is empty.\n";
                        else{
                            cout<<"\nPreorder:\n";

                        t1.iterativePreorder();
                        cout<<"\nInorder:\n";
                        t1.iterativeInorder();}
                        system("pause");
                        break;

            case 5: system("cls");
                        exit(0);
                        break;

            default:system("cls");
                cout<<"Enter correct choice.";
            }
    }while(true);
    return 0;
}

