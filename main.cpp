/* 
 * File:   main.cpp
 * Author: Sona
 *
 * Created on January 23, 2014, 9:13 PM
 */

#include <cstdlib>
#include<iostream>
#include<string>
#include<math.h>

using namespace std;

/*
 * 
 */
struct Node{
    int x;
    Node *left;
    Node *right;
    Node *parent;
};
class BST{
    
    
public:
    Node* prev;
    Node* temp;
    Node* temp1;
    Node* temp2;
    bool search(int key,Node* leaf){
        bool val;
        if(key<leaf->x){
            if(leaf->left!=NULL)
                search(key,leaf->left);
            else
            {   
                cout<<"Not Found        "<<key<<endl;
                return false;
            }
        }
        else if (key>leaf->x){
            if(leaf->right!=NULL)
                search(key,leaf->right);
            else
                {   
                cout<<"Not Found        "<<key<<endl;
                return false;
            }
        }
        else
            return true;
        
    }
    void insert(int key,Node* leaf){
        if(key < leaf->x){
            if (leaf->left != NULL)
                insert(key,leaf->left);
            else{
                leaf->left=new Node;
                leaf->left->x=key;
                leaf->left->left=NULL;
                leaf->left->right=NULL;
            }
 
        }//<val 
        else{
            if (leaf->right != NULL)
                insert(key,leaf->right);
            else{
                leaf->right=new Node;
                leaf->right->x=key;
                leaf->right->left=NULL;
                leaf->right->right=NULL;
                }
        
          }//>val
    }//insert
    int sizeNode(Node* leaf){
        if(leaf==NULL)
            return 0;
        else
        {
            return (sizeNode(leaf->left)+1+sizeNode(leaf->right));
        }
    }
    int depth(Node* leaf){
        if(leaf==NULL)
            return 0;
        else
        {
            int left,right;
            left=sizeNode(leaf->left);
            right=sizeNode(leaf->right);
            if(left>right)
            return left;
            else 
                return right;
        }
        
    }
    void print(Node* leaf){
        //in order traversal
        if (leaf){
            print(leaf->left);
            cout<<leaf->x<<endl;
            print(leaf->right);
        }               
    }
    Node* searchnode(int key, Node* leaf){
        if(key<leaf->x){
            if(leaf->left!=NULL)
            {
                prev=leaf;
                search(key,leaf->left);
               
            }
            else
            {   
                cout<<"Not Found        "<<key<<endl;
                return NULL;
            }
        }
        else if (key>leaf->x){
            if(leaf->right!=NULL)
            {
                prev=leaf;
                search(key,leaf->right);
                
            }
            else
                {   
                cout<<"Not Found        "<<key<<endl;
                return NULL;
            }
        }
        else
            return prev;
    }
    void reverse(Node* leaf){
        if(leaf==NULL)
            return;
        else
        {
            reverse(leaf->left);
            reverse(leaf->right);
            temp=leaf->left;
            leaf->left=leaf->right;
            leaf->right=temp;
            
        }
    }
    void delet(int key,Node* leaf){
        int found;
        //search node
        while(leaf!=NULL){
            if(leaf->x==key)
            {
              found=1;
              break;
            }
            else{
                prev=leaf;
                if(key<leaf->x)
                {
                    leaf=leaf->left;                    
                }
                else
                {
                    leaf=leaf->right;
                }
            }
        }
        if(found==1)
        {
            
        // 3 cases
        // leaf has no child // 
            if(leaf->left==NULL && leaf->right==NULL){
            if(prev->left==leaf)
                prev->left=NULL;
            else
                prev->right=NULL;
            delete leaf;
        }
        
        // leaf has one child//
        // left child
            else if (leaf->right==NULL && leaf->left!=NULL){
                if(prev->left==leaf)      
                    prev->left=leaf->left;
                else
                    prev->right=leaf->left;
                delete leaf;            
        }
        // right child
            else if (leaf->right!=NULL && leaf->left==NULL){
                if(prev->left==leaf)      
                    prev->left=leaf->right;
                else
                    prev->right=leaf->right;
                delete leaf;            
        }
        //leaf has two children//
            else if (leaf->right!=NULL && leaf->left!=NULL){
                temp=leaf->right;
              //if right child of current node has no child
                if(temp->right==NULL && temp->left==NULL){
                    leaf->x=temp->x;
                    delete temp;
                    leaf->right=NULL;
                }
              //if right child of current node has one or two child/children
                else if (leaf->right->left!=NULL){
                    temp1=leaf->right;
                    temp2=leaf->right->left;
                    while(temp1->left!=NULL){
                        temp2=temp1;
                        temp1=temp1->left;
                    }
                    leaf->x=temp1->x;
                    delete temp1;
                    temp2->left=NULL;                        
                }
              //if right child of current node has only right child
                else{
                    leaf->x=temp->x;
                    leaf->right=temp->right;
                    delete temp;
                }
            }
            return;
        }// if node found
        else
        {
            cout<<"Node not found"<<endl;
            return;
        }
        
    }
    void rootPath(Node* leaf,int stack[],int len){
        if(leaf==NULL)
            return;
        stack[len]=leaf->x;
        len++;
       if(leaf->left==NULL && leaf->right==NULL){
           cout<<"print new path"<<endl;
            for(int i=0;i<len;i++){
                cout<<stack[i]<<endl;
            }
            cout<<"======"<<endl;
            return;
        }
        else{
            rootPath(leaf->left,stack,len);
            rootPath(leaf->right,stack,len);
        }
            
        
    }
    Node* LCA(Node* leaf,int node1,int node2){
        if(leaf==NULL)
            return NULL;
        if(leaf->x>node1 && leaf->x>node2){
            LCA(leaf->left,node1,node2);
        }
        else if(leaf->x<node1&&leaf->x<node2){
            LCA(leaf->right,node1,node2);
        }
        else if(leaf->x<node1&&leaf->x>node2 || leaf->x==node1 || leaf->x==node2){
            cout<<"LCA: "<<leaf->x<<endl;;
            return leaf;
        }
    }
};
int main() {
    BST b;
    Node *root;
    Node *leaf;
    Node *temp;
    Node *prev;
    int found;
    temp=new Node;
    int range1,key,root1,func,flag;
    cout<<"Enter a random seed for binary tree is to be formed"<<endl;
    cin>>range1;
    cout<<"Enter the root for binary tree is to be formed"<<endl;
    cin>>root1;
    //create root
    root=new Node;
    root->parent=NULL;
    root->x=root1;
    root->left=NULL;
    root->right=NULL;
    leaf=root;
    //create tree of unique values
    for(int i=0;i<10;i++){
           range1=rand()%100;
           cout<<range1<<endl;
           while(leaf!=NULL){
            if(leaf->x==range1)
            {
              found=1;
              break;
            }
            else{
                prev=leaf;
                if(range1<leaf->x)
                {
                    leaf=leaf->left;                    
                }
                else
                {
                    leaf=leaf->right;
                }
            }
        }// check if already present
           if(found!=1)
            b.insert(range1,root);   
           else
               i--;
             } 
    leaf=root;
    cout<<"Inorder Trav"<<endl;
    b.print(leaf);
    cout<<"End"<<endl;
    func=1;
    while (true)
    {
    cout<<"Enter the function to be performed \n1: Insert Node \n"
            "2: Search Node \n3: Delete Node \n 4. Print tree \n5. Size of tree \n6. Depth of tree\n"
            "7. Mirror of Tree\n8. Print all path from root to leaf\n"
            "9.Least Common Ancestor\n0. exit"<<endl;
    cin>>func;
    if (func==0)
        break;
    switch(func){
        case 1: {
            cout<<"enter the node to be inserted"<<endl;
            cin>>key;
            leaf=root;
            b.insert(key,leaf);
            leaf=root;
            cout<<"Inorder Trav"<<endl;
            b.print(leaf);
            cout<<"End"<<endl;
            break;
        }
        case 2:{
            cout<<"enter the node to be searched"<<endl;
            cin>>key;
            leaf=root;
//            bool found;
//            found=b.search(key,leaf);
//           cout<<"Found?         "<<boolalpha<<found<<endl;
             if (b.search(key,leaf)) {
                cout <<key<<  " is found" << endl;
                }
            else {
                  cout << key << " not found" << endl;
                }
            break;
            
        }
        case 3:{
            cout<<"enter the node to be deleted"<<endl;
            cin>>key;
            leaf=root;
            b.delet(key,leaf);
            leaf=root;
            cout<<"Inorder Trav after deletion"<<endl;
            b.print(leaf);
            cout<<"End"<<endl;
            break;
        }
        case 5:{
            leaf=root;
            int size=0;
            size=b.sizeNode(leaf);
            cout<<"The size of tree is: "<<size<<endl;
            break;
            
        }
        case 6:{
            leaf=root;
            int size=0;
            size=b.depth(leaf);
            cout<<"The depth of tree is: "<<size<<endl;
            break;
            
        }
        case 7:{
            leaf=root;
            b.reverse(leaf);
            leaf=root;
            cout<<"Inorder Trav after deletion"<<endl;
            b.print(leaf);
            cout<<"End"<<endl;
            break;
        }
        case 8:{
            int stack[100];
            leaf=root;
            b.rootPath(leaf,stack,0);
            break;
        }
        case 9:{
            int node1,node2,temp;
            cout<<"Enter Node 1"<<endl;
            cin>>node1;
            cout<<"Enter Node 2"<<endl;
            cin>>node2;
            //make node 1 greater for ease
            if (node1<node2){
                temp=node1;
                node1=node2;
                node2=temp;
            }
            Node* tmp;
            tmp=b.LCA(leaf,node1,node2);
            cout<<"LCA: "<<tmp->x<<endl;
            break;
        }
    }  
    }
    
    return 0;
}

