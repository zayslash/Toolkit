#include <iostream>
#include <vector>
#include <set>
#include <string>
using namespace std;

template <typename T>
string set2string(const std::set<T>& a)
{
    if (a.size() != 0) {
         string s;
    
         for (auto const& e : a)
        {
            s += to_string(e);
            s += ',';
        }
        
        s.pop_back();
        return s;
   }
   return "";
}

template <typename T>
std::set<T> getUnion(const std::set<T>& a, const std::set<T>& b)
{
  std::set<T> result = a;
  result.insert(b.begin(), b.end());
  return result;
}

template <class T, class CMP = std::less<T>, class ALLOC = std::allocator<T> >
std::set<T, CMP, ALLOC>& operator *= (
  std::set<T, CMP, ALLOC> &s1, const std::set<T, CMP, ALLOC> &s2)
{
  auto iter1 = s1.begin();
  for (auto iter2 = s2.begin(); iter1 != s1.end() && iter2 != s2.end();) {
    if (*iter1 < *iter2) iter1 = s1.erase(iter1);
    else {
      if (!(*iter2 < *iter1)) ++iter1;
      ++iter2;
    }
  }
  while (iter1 != s1.end()) iter1 = s1.erase(iter1);
  return s1;
}

void printVec(const std::vector<string>& S)
{
    for (string const&i : S)
    {
        std::cout << i << '|';
    }
    cout << endl;

}

void printSet(const std::set<int>& S)
{

    for (int const&i : S)
    {
        std::cout << i << ' ';
    }
    cout << endl;

}

vector<string> findImage(std::vector<set<int> > groupOF)
 {
    std::vector<string> result;
    std::set<int> svec;
    std::set<int> belong;

    bool found;
    for(int r=0; r < groupOF.size() ; r++){
    	svec = groupOF[r];
    	belong = groupOF[r];
    	found = false;
    	
       for (int i = r+1; i< groupOF.size(); i++) {
    	set<int> v = groupOF[i];
            
            belong*=v;
    
    	if (belong.size() > 0 ){
                    svec = getUnion(svec, v);
    		found = true;
    		belong = svec;
    		groupOF[i] = {};
    	}
    	else{
    		belong = groupOF[r];
    	}
    	
       }
    
       if(!found){
    	//cout <<"at index r"<< r << "group but all alone: ";
         	//cout << set2string(groupOF[r]) << endl;
    	result.push_back(set2string(groupOF[r]));
  
       }
      else{
    	//cout <<"at index r"<< r << "REAL GP: ";
    	//printSet(svec);
    	result.push_back(set2string(svec));
    	continue;
     }
    	
    }
    

   return result;
}

vector<int> getPosInOneD(vector<vector<int>> grid){
    vector <int> seen;
    for (int i = 0 ; i < grid.size(); i++){
        for (int u = 0 ;  u < grid.size(); u++ ){
            if(grid[i][u] == 1){
                seen.push_back(int(i * grid.size() + u));  
            }
        }
    }
   return seen; 
}

vector<string> getGroups(vector<int> grid, int SIZE){
   string groups;
    vector <string> groupsOf;
    vector<set<int>> FinalGroup;
   
  //-----------------------------------------------------
  int number;
   
   vector<int>::iterator it  ;
    for (int i = 0 ; i < grid.size(); i++){
       for (int u = 0; u < grid.size(); u++){
         
       if(grid[u] == grid[i] - SIZE){
          groups += to_string(grid[u]) + " "; }

       for(int edge = 0 ; edge <=(SIZE*SIZE) - SIZE; edge=edge+SIZE){  

        if(grid[u] ==  grid[i] - 1 && grid[u] != edge){
          groups += to_string(grid[u]) + " ";} 
       }

        if(grid[u] ==  grid[i] + SIZE){
          groups += to_string(grid[u]) + " ";}

     for(int edge = SIZE -1 ; edge <= SIZE*SIZE; edge=edge+SIZE){  
       if(grid[u] ==  grid[i] + 1 && grid[u] != edge){
          groups += to_string(grid[u]) + " ";
        } 
     }

      }
       groups += to_string( grid[i]) + " |";
    }
   
    
  //------------------------------------------------------------------------------
    string word = "";
    string num = "";
    for(int i =0 ;i < groups.length(); i++){
       set<int> emp{};
       if (groups[i] == '|'){

          for(int u = 0 ; u < word.length(); u++){
            
            if((word[u]) == ' '){
            emp.insert(stoi(num));
            num = "";
            }
            num += word[u];
          }
           
           FinalGroup.push_back(emp);
           emp = {};
            word = "";
            continue;
        }
        
        word +=  groups[i];
       
    }
   return findImage(FinalGroup);  
}

int main() {
  
 vector<vector<int>> arrayT = {{0,1,0,0},{1,0,0,1},{0,0,1,1},{0,0,1,1}};

 vector<vector<int>> arrayY = {{0,1,0,1},{1,0,0,1},{0,0,1,1},{0,0,1,1}};

vector<string>image1 =getGroups(getPosInOneD(arrayT),4);
vector<string>image2 =getGroups(getPosInOneD(arrayY),4);
int count = 0;

for(int i =0; i < image1.size(); i++){
 for(int u =0; u < image2.size(); u++){
   if(image1[i] == image2[u] && image1[i] != "" && image2[i] != ""){
     count++;
   }
  
}
}

printVec(image1);
cout << "\n";
printVec(image2);
cout << count;
int SIZE = 4;

for(int edge =  0 ; edge <= (SIZE*SIZE) - SIZE; edge=edge+SIZE){  

cout << edge << "\n";
}
}