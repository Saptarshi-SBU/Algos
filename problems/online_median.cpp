/*----------------------------------------------------------------------------

  Online Median Find Algorithm

------------------------------------------------------------------------------*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Median_Find_Algorithm {
    
        vector<int> vmax_;
        vector<int> vmin_;
    
    public :
    
        Median_Find_Algorithm() {}
       ~Median_Find_Algorithm() {}
   
        struct func {
                func() {}
               ~func() {}    
                bool operator() (int& a, int& b) const {
                    return a < b;
                } 
        };
        
        struct func1 {
                func1() {}
               ~func1() {}    
                bool operator() (int& a, int& b) const {
                    return a > b;
                } 
        };
   
        int get_median(void) const {
            
            int smax = vmax_.size();
            int smin = vmin_.size();
            
            if (!smax)
                return -1;
                
            if (!smin)
                return vmax_.at(0); 
                
            int m1 = vmax_.at(0);
            int m2 = vmin_.at(0);
            
            if (smax == smin)
                return (m1 + m2)/2;
            else
                return (smax > smin) ? m1 : m2;
        }
        
        
        void insert(int data) {
            
            if (!vmax_.size() || data < vmax_.at(0)) {
                vmax_.push_back(data);
                push_heap(vmax_.begin(), vmax_.end());
            } else {
                vmin_.push_back(data);
                push_heap(vmin_.begin(), vmin_.end(), func1());
            }
            
            balance_heaps();
        }
        
        void insert_heap(int data) {
            
            vmax_.push_back(data);
            push_heap(vmax_.begin(), vmax_.end(), func1());
        }
        
        void remove_heap(void) {
            
            pop_heap(vmax_.begin(), vmax_.end(), func1());
            cout << vmax_.back() << "  " ;
            vmax_.pop_back();
        }
        
        void balance_heaps() {
            
            int smax = vmax_.size();
            int smin = vmin_.size();    
            
            int imb_factor = abs(smax- smin);
           
            
            if (imb_factor <= 1)
                return;
            
            int i = 0;
            
            if (smax > smin) {
                for (i = imb_factor; i > imb_factor/2; i--) {
                    pop_heap(vmax_.begin(), vmax_.end());
                    int p = vmax_.back();
                    vmax_.pop_back();
                    vmin_.push_back(p);
                    cout << p << endl;
                    push_heap(vmin_.begin(), vmin_.end(), func1());
                }             
            } else {
                for (i = imb_factor; i > imb_factor/2; i--) {
                    pop_heap(vmin_.begin(), vmin_.end(), func1());
                    int p = vmin_.back();
                    vmin_.pop_back();
                    vmax_.push_back(p);
                    push_heap(vmax_.begin(), vmax_.end());
                }
            }
            
          //  cout << "vmax_" << vmax_.size() << " ";
          //  cout << "vmin_" << vmin_.size() << endl;
        } 
        
        void print(void) {
            
            for (auto i : vmax_)
                cout << i << " ";
            cout << endl;
            
              for (auto i : vmin_)
                cout << i << " ";
            cout << endl;
            
        }
};
      
int main(void) {
    
    Median_Find_Algorithm *m = new Median_Find_Algorithm();
    vector<int> v= {1,2,3,4,5,6,7,8,9,10, 11, 12, 13};
    
    for (auto i : v) {
        m->insert(i);
    }
    cout << m->get_median() << endl;
    return 0;   
}    