#include <string>
#include <vector>
#include <cstring>
#include <iostream>
#include <sstream>
#include <functional>
#include <queue>
#include <cmath>
#include <algorithm>
#include <map>
#include <iterator>
#include <math.h>

using namespace std;

class Node
{ 
    public: 
    
    string name;
    vector<string> edges;
    int isleaf;
    vector<int> childs;
    
    Node(string n,vector<string> e, int il, vector<int> c) 
    { 
      name=n;
      edges=e;
      isleaf=il;
      childs=c;
    }
    
    vector<int> getChilds(){
        return childs;
    }
    
    vector<string> getEdges(){
        return edges;
    }
    
    int getIsLeaf(){
        return isleaf;
    }
    
    void printChilds(){
        int i;
        for(i=0;i<childs.size();i++){
            cout << "Father: "<< name << " childs: " << childs[i]<< "\n";
        }
    }
    
    void setChilds(vector<int> c){
        childs=c;
    }
    
    string getName(){
        return name;
    }
};

void printDataSet(vector<vector <string>> dataset){
    int i,j;
    for (int i = 0; i < dataset.size(); i++)
    {  
        cout << "Vector " << i << "\n";
        for (int j = 0; j < dataset[i].size(); j++){ 
          cout << " " << dataset[i][j];
          cout << endl;
        }
    }
}

void printvv(vector<vector <int>> dataset){
    int i,j;
    for (int i = 0; i < dataset.size(); i++)
    {  
        cout << "Vector " << i << "\n";
        for (int j = 0; j < dataset[i].size(); j++){
          cout << " " << dataset[i][j];
          cout << endl;
        }
    }
}

void printVector(vector<string> v){
  int i;
  int v_size=v.size();
  for(i=0;i<v_size;i++){
    cout << v[i] << "\n";
  }
}

vector<vector <string>> createDataSet(vector<string> d){
    int i=0,j=0,k=0;
    int tam=d.size();
    vector<vector <string>> dataset;
    string aux;
    for(i=0;i<tam;i++){
        int tll=d[i].length();
        for(j=0;j<tll;j++){
            if(d[i][j]!=','){
                aux+=d[i][j];
            }
            if(d[i][j]==',' || j==tll-1){
                if(i==0){
                    vector<string> a;
                    a.push_back(aux);
                    dataset.push_back(a);
                    aux="";
                }else{
                    dataset[k].push_back(aux);
                    aux="";
                    k++;
                }
            }
        }
        k=0;
    }
    return dataset;
}

string removeSpaces(string my_str)  
{
    my_str.erase(std::remove(my_str.begin(), my_str.end(), '\t'), my_str.end());
    return my_str; 
} 


vector<string> parseAttributes(vector<string> a){
    int i,j=0;
    int vector_size=a.size();
    vector<string>attributes;
    string aux;
    for(i=0;i<vector_size;i++){
        int string_length=a[i].length();
        while(a[i][j]!=' ' && a[i][j]!='{'){
            aux+=a[i][j];
            j++;
        }
        aux=removeSpaces(aux);
        attributes.push_back(aux);
        aux="";
        j=0;
    }
    return attributes;
}

vector<vector <string>> parseFeatures(vector<string> f){
    int i=0,j=0,vector_size=f.size();
    vector<vector <string>> features;
    string aux;
    for(i=0;i<vector_size;i++){
        int string_length=f[i].length();
        std::size_t found = f[i].find('{');
        vector<string> a;
        for(j=found;j<string_length;j++){
            if(f[i][j]!=',' && f[i][j]!='{' && f[i][j]!='}' && f[i][j]!=' '){
                aux+=f[i][j];
            }
            if(f[i][j]==',' || f[i][j]=='}'){
                    a.push_back(aux);
                    aux="";
            }
        }
        features.push_back(a);
    }
    return features;
}

float calculateEntropyDataset(vector<string> relation_attribute, vector<string> features){
    int i,features_size=features.size(),number_of_features,relation_size=relation_attribute.size();
    vector<int> times_features;
    float entropy=0;
    vector<float> entropy_elements;
    for(i=0;i<features_size;i++){
        number_of_features = std::count (relation_attribute.begin(), relation_attribute.end(), features[i]);
        if(number_of_features>0){
        times_features.push_back(number_of_features);
        float res=-(((float)number_of_features/(float)relation_size)*log2((float)number_of_features/(float)relation_size));
        entropy_elements.push_back(res);
        }
    }
    int e_s=entropy_elements.size();
    for(i=0;i<e_s;i++){
        entropy+=entropy_elements[i];
    }
    return entropy;
}


float calculateEntropyAttribute(vector<string> attribute, vector<string> relation_attribute, vector<string> features, vector<string> relation_feature, float entropy_dataset, int number_of_elements_relation){
    int i,j,k=0,a_s=attribute.size(), f_s=features.size(), r_s=relation_attribute.size(), rf_s=relation_feature.size();
    int number_of_features;
    vector<int> times_features;
    float entropy=0;
    for(i=0;i<f_s;i++){
        number_of_features = std::count (attribute.begin(), attribute.end(), features[i]);
        times_features.push_back(number_of_features);
    }
    vector<vector<int>> list_of_encounters;
    for(i=0;i<f_s;i++){
        int n=0;
        vector<int> a;
        list_of_encounters.push_back(a);
        for(j=0;j<rf_s;j++){
            for(k=0;k<a_s;k++){
                if(attribute[k]==features[i] && relation_attribute[k]==relation_feature[j]){
                    n++;
                }
            }
            list_of_encounters[i].push_back(n);
            n=0;
        }
    }
    int lofs=list_of_encounters.size();
    vector <float> entropies;
    k=0;
    for(i=0;i<lofs;i++){
        int vlofs=list_of_encounters[i].size();
        for(j=0;j<vlofs;j++){
            if(list_of_encounters[i][j]!=0){
                entropy+=-(((float)list_of_encounters[i][j]/(float)times_features[k])*log2((float)list_of_encounters[i][j]/(float)times_features[k]));
            }
        }
        entropies.push_back(entropy);
        k++;
        entropy=0;
    }
    int tfs=times_features.size();
    float en=0;
    for(i=0;i<tfs;i++){
        en+=((float)times_features[i]/(float)a_s)*entropies[i];
    }
    return en;
}

int biggerOne(vector<float> info_gain){
    int i, bigger=0, ifs=info_gain.size();
    float current=info_gain[0];
    for(i=1;i<ifs;i++){
        if(current<info_gain[i]){
            bigger=i;
            current=info_gain[i];
        }
    }
    return bigger;
}


vector<vector <string>> elminateFeatureDataset(vector<vector <string>> dataset, string feature, int elegido){
    int i,j,k;
    vector<vector <string>> aux;
    int ds=dataset[elegido].size();
    for(i=0;i<dataset.size();i++){
        vector<string>a;
        aux.push_back(a);
    }
    for(i=0;i<ds;i++){
        if(dataset[elegido][i]== feature){
          for(k=0;k<dataset.size();k++){
              aux[k].push_back(dataset[k][i]);
          }
        }
    }
    return aux;
}

void createTree(string relation,vector<string> attributes,vector<vector <string>> dataset, vector<vector <string>> features,string spaces, vector<Node> *ptree, vector<int> *childs){
    int i,d_s=dataset.size(),f_s=features.size(),a_s=attributes.size();
    float entropy_dataset=calculateEntropyDataset(dataset[d_s-1], features[f_s-1]);
    float entropy=0;
    vector<float> entropies,info_gain;
    for(i=0;i<a_s-1;i++){
        int number_relation_elements=features[f_s-1].size();
        entropy=calculateEntropyAttribute(dataset[i], dataset[d_s-1], features[i],features[f_s-1], entropy_dataset, number_relation_elements);
        info_gain.push_back(entropy_dataset-entropy);
    }
    int chosen_one=biggerOne(info_gain);
    if(entropy_dataset>0){
        vector<int> a;
        ptree->push_back(Node(attributes[chosen_one],features[chosen_one],0,a));
        int size_tree=ptree->size();
        vector<int> ch;
        vector<int> *c=&ch;
        if(size_tree!=1){
            childs->push_back(size_tree-1);
        }
        for(i=0;i<features[chosen_one].size();i++){
            //cout << spaces <<attributes[chosen_one] << ": " << features[chosen_one][i] << "\n";
            vector<vector <string>> attribute_dataset=elminateFeatureDataset(dataset,features[chosen_one][i],chosen_one);
            createTree(relation, attributes, attribute_dataset, features, spaces+"  ", ptree, c);
        }
        vector<Node> &vr = *ptree;
        vr[size_tree-1].setChilds(ch);
    }
    else{
        vector<string> edge;
        vector<int> ch;
        ptree->push_back(Node(dataset[d_s-1][0],edge,1,ch));
        int size_tree=ptree->size();
        childs->push_back(size_tree-1);
        //cout << spaces<<"ANSWER: " <<dataset[d_s-1][0] << "\n";
    }
    
}

void printTree(string spaces, Node padre, vector<Node>tree){
  int i,j;
  if(padre.getIsLeaf()==0){
      vector<string> e = padre.getEdges();
      for(i=0;i<e.size();i++){
          cout << spaces << padre.getName() << ": " << e[i] << "\n";
          vector<int> pos=padre.getChilds();
          printTree(spaces+"  ", tree[pos[i]], tree);
      }
  }
  else if(padre.getIsLeaf()==1){
      cout << spaces<<"ANSWER: " << padre.getName() << "\n";
  }
} 

int main()
{
    int i;
    vector<string>data,unparsed_attributes,attributes;
    vector<vector <string>> dataset,features;
    vector<Node> tree;
    vector<Node> *ptree=&tree;
    vector<int> childs;
    vector<int> *ch=&childs;
    string line,relation,spaces="";
    
    while(getline(cin, line)) {
      if(line.substr(0,9) == "@relation"){
            int t=line.length();
            relation=line.substr(10,t);
      }
      else if(line.substr(0,10) == "@attribute"){
            int t=line.length();
            unparsed_attributes.push_back(line.substr(11));
      }
      else if(line!="" && line!="@data" && line.substr(0,1)!="%"){
          data.push_back(line);
      }
    }
    
    attributes=parseAttributes(unparsed_attributes);
    features=parseFeatures(unparsed_attributes);
    dataset=createDataSet(data);
    
    createTree(relation,attributes,dataset,features,spaces, ptree, ch);
    
    printTree("", tree[0], tree);
    
    return 0;   
}