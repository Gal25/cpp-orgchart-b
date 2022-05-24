#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <queue>
#include <stack>
#include <list>

#pragma once
using namespace std;

namespace ariel{


    class OrgChart {

        ///////////////////// - The Node - ///////////////////////
        struct Node{
            public:
            string name;
            vector<Node*> subs;
            Node(string name1): name(move(name1)), subs(0){}
            Node(string name2, vector<Node*> sub): name(move(name2)), subs(move(sub)){}
        };
        ///////////////////// - The organization - ///////////////////////
        private:
            Node* root;
            int org;

        public:

        ///////////////////// - The Iterator - ///////////////////////

        class Iterator{
            public:
            size_t curr;
            vector<Node*> vec;
            Iterator();

            Iterator(string const & type, Node* node);
            void putInIter(string const &iterator_type, Node* node);
         

            string& operator*() const;

            string* operator->() const;

            Iterator& operator++();

            Iterator operator++(int);
              	

            bool operator==(const Iterator& other) const;
            bool operator!=(const Iterator& other) const;
        };

            OrgChart();
            OrgChart(OrgChart &other); // copy constructor
            OrgChart(OrgChart &&other) = default; 
            OrgChart& operator=(OrgChart&& other) = default;
            OrgChart& operator=(const OrgChart& other); // placement operator
            Node* getRoot();


            void delOrg(Node * root);

            ~OrgChart(); // destructor
            OrgChart& add_root(string const &root2);

            OrgChart& add_sub(string const & name1, string const &name2);


            Iterator begin_level_order()const;

            Iterator end_level_order() const;


            Iterator reverse_order() const;

            Iterator begin_reverse_order()const;

            Iterator begin_preorder() const;

            Iterator end_preorder() const;

           Iterator end() const;
        
            Iterator begin() const;
            
            friend ostream& operator<<(ostream& os,const OrgChart &chart);

            Node* getNode(Node* n,string const & name);
        
    };
    

}
