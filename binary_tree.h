#include<iostream>
#include<map>
#include<queue>
using namespace std;
class binarytreenode
{
    public:
    int data;
    binarytreenode* left;
    binarytreenode* right;
    binarytreenode(int data)
    {
        this->data= data;
        left=NULL;
        right=NULL;
    }

    ~binarytreenode()
    {
        delete left;
        delete right;
    }
};

#include<queue>
binarytreenode* takeinput()
{
    int rootdata;
    cout<<"enter the rootdata: ";
    cin>>rootdata;
    if(rootdata== -1)
    {
        return NULL;
    }
    binarytreenode* root= new binarytreenode(rootdata);
    queue<binarytreenode*> q;
    q.push(root);
    while(q.size()!=0)
    {
        binarytreenode* front= q.front();
        q.pop();
        int leftchilddata;
        cout<<"enter the left child data of "<<front->data<<": ";
        cin>>leftchilddata;
        if(leftchilddata!= -1)
        {
            binarytreenode* leftchild= new binarytreenode(leftchilddata);
            front->left= leftchild;
            q.push(leftchild);
        }
        int rightchilddata;
        cout<<"enter the right child data of "<<front->data<<": ";
        cin>>rightchilddata;
        if(rightchilddata!= -1)
        {
            binarytreenode* rightchild= new binarytreenode(rightchilddata);
            front->right= rightchild;
            q.push(rightchild);
        }
    }
    return root;
}

void printlevelwise(binarytreenode* root)
{
    if(root==NULL)
    {
        return;
    }
    queue<binarytreenode*> printtree;
    printtree.push(root);
    while(printtree.size()!=0)
    {
        binarytreenode* front= printtree.front();
        printtree.pop();
        cout<<front->data<<":";
        if(front->left!= NULL)
        {
            cout<<"L:"<<front->left->data<<",";
            printtree.push(front->left);
        }
        else
        {
            cout<<"L:"<<-1<<",";
        }

        if(front->right!= NULL)
        {
            cout<<"R:"<<front->right->data;
            printtree.push(front->right);
        }
        else
        {
            cout<<"R:"<<-1;
        }
        cout<<endl;
    }
}

int height(binarytreenode* root)
{
    if(root==NULL)
    {
        return 0;
    }
    int leftheight= height(root->left);
    int rightheight= height(root->right);
    return 1+ max(leftheight, rightheight);
}

int diameter(binarytreenode* root)
{
    if(root== NULL)
    {
        return 0;
    }
    int option1= height(root->left) + height(root->right);
    int option2= diameter(root->left);
    int option3= diameter(root->right);
    return max(option1, max(option2, option3));
}

bool isBalanced(binarytreenode* root)
{
    if(root==NULL)
    {
        return true;
    }
    int leftheight= height(root->left);
    int rightheight= height(root->right);
    if ((leftheight - rightheight)>1 || (leftheight- rightheight) < -1 )
    {
        return false;
    }

    bool leftans= isBalanced(root->left);
    bool rightans= isBalanced(root->right);
    if(leftans == true && rightans==true)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void preorder(binarytreenode* root)
{
    if(root==NULL)
    {
        return;
    }
    cout<<root->data<<' ';
    preorder(root->left);
    preorder(root->right);
}

void postorder(binarytreenode* root)
{
    if(root==NULL)
    {
        return;
    }
    postorder(root->left);
    postorder(root->right);
    cout<<root->data<<' ';
}

void mirror(binarytreenode* root)
{
    if(root==NULL)
    {
        return;
    }
    mirror(root->left);
    mirror(root->right);
    if(root->left!= NULL && root->right!=NULL)
    {
        binarytreenode* temp= root->left;
        root->left=root->right;
        root->right=temp;
    }
    else if(root->left==NULL)
    {
        root->left= root->right;
        root->right=NULL;
    }
    else if(root->right==NULL)
    {
        root->right=root->left;
        root->left=NULL;
    }
}

bool helper(binarytreenode* root1, binarytreenode* root2)
{
    if(root1==NULL && root2==NULL)
     {
         return true;
     }

     if((root1==NULL && root2!=NULL) || (root1!=NULL && root2==NULL))
     {
        return false;
     }

     if(root1!=NULL && root2!= NULL)
     {
         if(root1->data != root2->data)
         {
             return false;
         }
     }

     bool leftsubtree= helper(root1->left, root2->left);
     bool rightsubtree= helper(root1->right, root2->right);
     if(leftsubtree && rightsubtree)
     {
         return true;
     }
     else
     {
         return false;
     }
}

bool isIdentical(binarytreenode* root1, binarytreenode* root2)
{
    return helper(root1, root2);
}

bool symmetric_helper(binarytreenode* root1, binarytreenode* root2)
{
    if(root1==NULL && root2==NULL)
     {
         return true;
     }

     if(root1== NULL || root2==NULL)
     {
         return false;
     }

     if(root1!=NULL && root2!= NULL)
     {
         if(root1->data != root2->data)
         {
             return false;
         }
     }
     bool leftans= symmetric_helper(root1->left, root2->right);
     bool rightans= symmetric_helper(root1->right, root2->left);
     if(leftans && rightans)
     {
         return true;
     }
     else
     {
         return false;
     }
}

bool isSymmetric(binarytreenode* root)
{
    if(root==NULL)
    {
        return false;
    }
    return symmetric_helper(root->left, root->right);
}

int numnodes(binarytreenode* root)
{
    if(root== NULL)
    {
        return 0;
    }
    return 1+ numnodes(root->left)+ numnodes(root->right);
}

int leafnodes(binarytreenode* root)
{
    if(root==NULL)
    {
        return 0;
    }
    if(root->left== NULL && root->right== NULL)
    {
        return 1;
    }
    int leftans= leafnodes(root->left);
    int rightans= leafnodes(root->right);
    return leftans+ rightans;
}

int LCA(binarytreenode* root, int a, int b)
{
    if(root==NULL)
    {
        return -1;
    }
    if(a==root->data || b==root->data)
    {
        return root->data;
    }
    int leftans= LCA(root->left, a,b);
    int rightans= LCA(root->right, a,b);
    if(leftans != -1 && rightans==-1)
    {
        return leftans;
    }
    else if(rightans!=-1 && leftans==-1)
    {
        return rightans;
    }
    else if(leftans!=-1 && rightans!=-1)
    {
        return root->data;
    }
    else
    {
        return -1;
    }
}

void helper(binarytreenode* root, map<int,int>& parentMap, map<int,int>& ourmap)
 {
     if(root==NULL)
     {
         return;
     }
     int currLevel=0;
     queue<binarytreenode*> q;
     q.push(root);
     q.push(NULL);
     parentMap[root->data]= -1;
     ourmap[root->data]= 0;
     while(!q.empty())
     {
         binarytreenode* front= q.front();
         q.pop();
         if(front== NULL)
         {
             currLevel++;
             if(q.size()!=0)
             {
                 q.push(NULL);
             }
             continue;
         }

         if(front->left != NULL)
         {
             currLevel++;
             ourmap[front->left->data]= currLevel;
             parentMap[front->left->data]= front->data;
             q.push(front->left);
             currLevel--;
         }

         if(front->right != NULL)
         {
             currLevel++;
             ourmap[front->right->data]= currLevel;
             parentMap[front->right->data]= front->data;
             q.push(front->right);
             currLevel--;
         }
     }
 }

vector<int> cousins(binarytreenode* root, int node)
{
    map<int, int> parentMap;
    map<int, int> ourmap;
    helper(root, parentMap, ourmap);
    vector<int> output;

    int nodeLevel= ourmap[node];
    int nodeParent= parentMap[node];

    for(auto it: ourmap)
    {
        if(it.second == nodeLevel && parentMap[it.first] != nodeParent)
        {
            output.push_back(it.first);
        }
    }
    return output;
}
