#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <vector>
#include "./sources/OrgChart.hpp"

using namespace std;
using namespace ariel;

int main(){
    OrgChart organization;

    organization.add_root("Gal")
      .add_sub("Gal", "Noy")         
      .add_sub("Gal", "Romi")         
      .add_sub("Noy", "Michal")        
      .add_sub("Romi", "Shani")        
      .add_sub("Romi", "Liza");      

    cout << organization << endl;
    cout <<"Level Order:"<<endl;
    for (auto it = organization.begin_level_order(); it != organization.end_level_order(); ++it){
            cout << (*it) << " " ;
    }
    cout << endl;

    cout <<"Reverse Order:"<<endl;
    for (auto it = organization.begin_reverse_order(); it != organization.reverse_order(); ++it){
        cout << (*it) << " " ;
    }

    cout << endl;
    cout <<"Preorder Order:"<<endl;
    for (auto it=organization.begin_preorder(); it!=organization.end_preorder(); ++it) {
        cout << (*it) << " " ;
    }

    cout << endl;


}
