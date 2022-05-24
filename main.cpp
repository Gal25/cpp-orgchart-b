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
      .add_sub("Gal", "Noy")         // Now the CTO is subordinate to the CEO
      .add_sub("Gal", "Romi")         // Now the CFO is subordinate to the CEO
      .add_sub("Noy", "Michal")         // Now the COO is subordinate to the CEO
      .add_sub("Romi", "Shani") // Now the VP Software is subordinate to the CTO
      .add_sub("Romi", "Liza");      // Now the VP_BI is subordinate to the COO

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