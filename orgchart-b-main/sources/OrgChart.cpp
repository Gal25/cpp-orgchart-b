#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <queue>
// #include <stack>

using namespace std;

#include "OrgChart.hpp"
namespace ariel{
    string level_iterator_type = "level_order";
    string reverse_iterator_type= "reverse_order";
    string preorder_iterator_type= "preorder";



///////////////////// - the organization - ///////////////////////

    OrgChart::OrgChart(){
        this->root = nullptr;
        this->org=0;
    }
    
    // OrgChart::OrgChart(OrgChart &&other) noexcept{
    //     this->root= other.root;
    //     this->org = other.org;   
    // }
    
    // OrgChart&  OrgChart::operator=(OrgChart&& other) noexcept{
    //     this->root = other.root;
    //     other.root = nullptr;
    //     return *this; 
    //  }

    OrgChart::OrgChart(OrgChart &other){
        this->root = other.root;
        this->org = other.org;
    }

    OrgChart& OrgChart::operator=(const OrgChart& other){
        if(&other == this){
            return *this;
        }
        this->delOrg(this->root);
        this->root = new Node(other.root->name, other.root->subs);
        return *this; 
     }

    // add a root to the orgavization, if the root is not null - change the name of the root to the name of the new root.
    // if the root is null , creat a new node that is the root.
    OrgChart& OrgChart::add_root(string const &root2){
        if(root == nullptr){
            root = new Node(root2);
            this->org++;  
        }else{
            this->root->name = root2;
        }
        return *this;
    }

    //add subs to the root. first search the node that is the father of the other name. 
    // if the node is null that mean there is not a root like name1- throw exapcion 
    // else, creat a new node that is the chid of the root - name2 , and push back in the subs's vector of the root- name1.
    OrgChart& OrgChart::add_sub(string const &name1, string const &name2){
        if (name1.empty()){
            throw invalid_argument("the root is null");
        }
        if(this->org ==0){
            throw invalid_argument("there is not a root in org");
        }

        if (name2.empty()){
            throw invalid_argument("the names is null");
        }
        Node* temp = getNode(this->root,name1);
        if(temp == nullptr){
            throw invalid_argument("therent root");
        }
        Node * node_name2 = new Node {name2};
        temp->subs.push_back(node_name2);
        return *this;
    }

    //destractor
   OrgChart::~OrgChart(){
        this->delOrg(root);
    }

    //delete all the organiztion with recursive funstion that fass all over the level of the tree.
    // start with the root and over of the root's subs ans delete them.
    void OrgChart::delOrg(Node* root){
        if(root == nullptr){
            return;
            }
            for (size_t i = 0; i< root->subs.size(); i++){
                delOrg(root->subs.at(i));
                
            }
            delete root;
    }


  
    //get node- search the node of the org , with recursive function.
    // over the subs of the root and call the the function again with the sub.
    // if the name of the subs's vector is equal to the name that we search so done. 
    OrgChart::Node* OrgChart::getNode(Node* n,string const & name){
        if(n->name == name){
            return n;
        }
        for (size_t i = 0; i < n->subs.size(); i++){
            Node * res = this->getNode(n->subs[i], name);
                if (res != nullptr){
                    return res;
                }
             }
        
        return nullptr;
    }

    //level order - call to the constructor of the iterator with the root of the org and create a vector of level order.
     OrgChart::Iterator OrgChart::begin_level_order() const{
        if(this->org == 0){ 
            throw invalid_argument("the chart is empty");
        }
        return Iterator(level_iterator_type,this->root);
    }

    //end level order - call to the constructor of the iterator with nullptr becuase is the end of the vector
    OrgChart::Iterator OrgChart::end_level_order() const{
        if(this->org == 0){
            throw invalid_argument("the chart is empty");
        }
        return Iterator(level_iterator_type,nullptr);
    }

    //end reverse order - call to the constructor of the iterator with nullptr becuase is the end of the vector    
    OrgChart::Iterator OrgChart::reverse_order() const{
        if(this->org == 0){
            throw invalid_argument("the chart is empty");
        }
        return Iterator(reverse_iterator_type, nullptr);
    }

    //reverse order - call to the constructor of the iterator ans create a vector of reverse order.    
     OrgChart::Iterator OrgChart::begin_reverse_order()const{
        if(this->org == 0){
            throw invalid_argument("the chart is empty");
        }
        return Iterator(reverse_iterator_type, this->root);
    }

    //preorder order - call to the constructor of the iterator ans create a vector of preorder order.    
    OrgChart::Iterator OrgChart::begin_preorder() const{
           if(this->org == 0){
         throw invalid_argument("the chart is empty");
     }
        return Iterator(preorder_iterator_type, this->root);
    }

    //end preorder order - call to the constructor of the iterator with nullptr becuase is the end of the vector
    OrgChart::Iterator OrgChart::end_preorder() const{
           if(this->org == 0){
         throw invalid_argument("the chart is empty");
     }
        return Iterator(preorder_iterator_type, nullptr);
    }

    //end of the iterator- retrun the end of level order= null
    OrgChart::Iterator OrgChart::end() const{
        return end_level_order();
    }
    //begin of the iterator - return the vector of level order
    OrgChart::Iterator OrgChart::begin() const{
        return begin_level_order();
    }

    ///////////////////// - The Iterator - ///////////////////////

    //defult constructor
    OrgChart::Iterator:: Iterator(): curr(0){}

    //constructor- fill the vector of the iterator depending on the type of the order.
    //call the function that fill the vector and in the end full nullptr for the end iterator
    OrgChart::Iterator::Iterator(string const & type, Node* node) : curr(0){
        if(node == nullptr){
            this->vec.push_back(nullptr);
            return;
        }
        putInIter(type,node);
        this->vec.push_back(nullptr);
                
    }

    //fill the vector of the iterator depending on the type of the order.
    void OrgChart::Iterator::putInIter(string const &iterator_type, Node* node){
        if(node == nullptr){
            throw invalid_argument("empty tree");
        }

        //level order - Define a data structure of a queue.
        // First, insert the root (depending on the sending of the iterator type).
        // As long as the queue is not empty, insert the locator node of the iterator and remove it from the queue,
        // and so go through and put the children of the node in the queue queue and so on.
        // So that finally inside the vector there will be the nodes in the order of the levels of the tree.
        if(iterator_type == level_iterator_type){
            queue<Node*> order;
            order.push(node);
            while(!order.empty()){
                for (int i=0; i< order.size(); i++){
                    Node* curr = order.front();
                    order.pop();
                    this->vec.push_back(curr);
                    unsigned long size = curr->subs.size();
                    for(unsigned long j =0 ; j <size; j++){
                        order.push(curr->subs.at(j));
                    }
                }
            }     
        }


        //Define queue and list data structures. As long as the queue is not empty,
        // do it according to the level order (see above).
        // But here you put a list in the queue from the end and go upside down on the children of the root - 
        //from right to left and put in the queue list.           
        if(iterator_type == reverse_iterator_type){
            list<Node*> list;
            queue<Node*> queue;
            queue.push(node);
            while(!queue.empty()){
                Node* curr= queue.front();
                queue.pop();
                list.push_back(curr);
                unsigned long size = curr->subs.size()-1;
                for( int i= (int)size; i >= 0; i--){
                    queue.push(curr->subs.at((unsigned long) i));
                }
            }
            while (!list.empty()){
                Node * n= list.back();
                vec.push_back(n);
                list.pop_back();
            }
        }
            
        //Define a data structure of a stack.
        // First take the root, and take out the top of the stack and put in a vector of the iterator.
        // Go through all the children of the same root from the end to the beginning because we want the top of the stack,
        // to have the leftmost son so that we can go from left to right on the boys and so on on the grandchildren.
        if(iterator_type==preorder_iterator_type){
            stack<Node*> order;
            order.push(node);
            while(!order.empty()){
                Node* curr = order.top();
                order.pop();
                this->vec.push_back(curr);
                unsigned long size = curr->subs.size()-1;
                for(int i= (int)size;i>=0; i-- ){
                    order.push(curr->subs.at((unsigned long)i));
                }               
            }
        }  
    }

    //Override of operatror *
    string& OrgChart::Iterator::operator*() const {
		return vec[curr]->name;
	}

    //Override of operator ->
    string* OrgChart::Iterator::operator->() const {
		return &(vec[curr]->name);
	}

    //Override of operator ++
    OrgChart::Iterator& OrgChart::Iterator::operator++(){
        curr++;
        return *this; 
    }

    //Override of operator ++(int)
    OrgChart::Iterator OrgChart::Iterator::operator++(int){
        Iterator temp = *this;
        curr++;
        return temp; 
    }
              	
    //Override of operator ==
    bool OrgChart::Iterator::operator==(const Iterator& other) const {
		return (vec[curr] == other.vec[other.curr]);
	}

    //Override of operator !=
    bool OrgChart::Iterator::operator!=(const Iterator& other) const {
		return !(vec[curr] == other.vec[other.curr]);
	}

    //Override the output
    ostream& operator<<(ostream& os,const OrgChart &chart){
        return os;
    }

}