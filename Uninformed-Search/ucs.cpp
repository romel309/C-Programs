#include <string>
#include <vector>
#include <cstring>
#include <iostream>
#include <sstream>
#include <functional>
#include <queue>
#include <cmath>
#include <algorithm>

using namespace std;

/*
• n.STATE: the state in the state space to which the node corresponds;
• n.PARENT: the node in the search tree that generated this node;
• n.ACTION: the action that was applied to the parent to generate the node;
• n.PATH-COST: the cost, traditionally denoted by g(n), of the path from the initial state
to the node, as indicated by the parent pointers.

function CHILD-NODE(problem, parent , action) returns a node
return a node with
STATE = problem.RESULT(parent.STATE, action),
PARENT = parent, ACTION = action,
PATH-COST = parent.PATH-COST + problem.STEP-COST(parent.STATE, action)
*/

class Node
{ 
    public: 
    
    int cost;
    vector<string> state;
    string action;
    Node* parent;
    
    Node(){}
    
    Node(int newc,vector<string> news)
    {
      cost=newc;
      state=news;
    } 
    
    Node(int newcost, vector<string> newstate, string newaction, Node* newparent) 
    { 
        cost = newcost; 
        state = newstate;
        action = newaction;
        parent = newparent;
    } 
    
    int getTotalCost(){
      return parent->cost + cost;
    }
    
};

int compareStates(vector<string> a , vector<string> b){
  int equal=0,i;
  for(i=0;i<a.size();i++){
    if(b[i][0]!='X'){
      if  (a[i]!=b[i]){
        equal=1;
      }
    }
  }
  return equal;
}

void printStack(vector<string> stacks){
  int i;
  for(i=0;i<stacks.size();i++){
    cout << stacks[i] << "\n";
  }
}

vector<Node> expand (vector<string> state, Node root, int height){
  int i,j,costo;
  string newstate,formato;
  vector<string> childstates;
  vector<Node> child_nodes;
  Node *parent;
  parent=&root;
  for (i=0;i<state.size();i++){
      for(j=0;j<state.size();j++){
        if(i!=j && height>=state[i].length() && state[i]!=""){
          childstates=state;
          newstate+=state[i][(state[i].length())-1];
          childstates[j]+=newstate;
          childstates[i].erase(childstates[i].begin()+(state[i].length()-1));
          newstate="";
          costo = abs(i-j)+1+parent->cost;
          ostringstream oss;
          oss << parent->action << " " << "("<<i<<","<<" "<<j<<");";
          formato = oss.str();
          Node node(costo,childstates,formato,parent);
          child_nodes.push_back(node);
        }
      }
  }
  return child_nodes;
}

vector<string> parse(string state){
    int i=0,j=0;
    string stack;
    vector<string> lines;
    for (i=0;i<state.length();i++){
      if (i > 0 ){
        if (state[i-1] == '(' && state[i] == ')'){
          lines.push_back("");
        }
      }
      if (state[i] == '(' && state[i+1]!=')'){
          j=i;
          while(state[j]!=')'){
            if (state[j]!=',' && state[j]!='(' && state[j]!=' '){
              stack+=state[j];
            }
            j++;
          }
          lines.push_back(stack);
          stack="";
      }
      if(state[i]=='X'){
        lines.push_back("X");
      }
    }
    return lines;
}

bool operator<(const Node& a, const Node& b) {
  return a.cost > b.cost;
}

void ucs(Node padre, int height, vector<string> goalstate){
  priority_queue<Node> nodesToCheck;
  vector<Node> explored;
  string res;
  int i,j=0,visited=0;
  nodesToCheck.push(padre);
  while(compareStates(nodesToCheck.top().state,goalstate)!=0){
      if(nodesToCheck.empty()){
        cout << "No solution found";
      }
      else{
        vector<Node> child_nodes;
        visited=0;
        for(j=0;j<explored.size();j++){
          if(nodesToCheck.top().state == explored[j].state){
            visited=1;
          }
        }
        if(visited==0){
          child_nodes=expand(nodesToCheck.top().state,nodesToCheck.top(), height);
          for(i=0;i<child_nodes.size();i++){
                nodesToCheck.push(child_nodes[i]);
          } 
        }
        j++;
        //cout << j;
      }
      explored.push_back(nodesToCheck.top());
      nodesToCheck.pop(); 
  }
  //cout << j << "\n";
  res = nodesToCheck.top().action;
  res.erase(res.begin()+(res.length()-1));
  res.erase(res.begin()+0);
  cout << nodesToCheck.top().cost << "\n";
  cout << res;
}



int main()
{
    int number,i,j;
    string line;
    vector<string>lines,estado_inicial,estado_final,resultado;
    
    cin >> number;
  
    while(getline(cin, line)) {
      lines.push_back(line);
    }

    if (number<=0){
      cout << "No solution found";
      return 0;
    }
    
    estado_inicial = parse(lines[1]);
    estado_final = parse(lines[2]);
    
    for(i=0;i<estado_final.size();i++){
      if(estado_final[i].length()> number ){
        cout << "No solution found";
        return 0;
      }
    }
    
    Node padre(0,estado_inicial);
    
    ucs(padre,number,estado_final);

    return 0;
}