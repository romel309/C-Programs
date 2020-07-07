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
#include <ctime>    
#include <cstdlib>  

using namespace std;

void printVector(vector<double> v){
  int i;
  int v_size=v.size();
  for(i=0;i<v_size;i++){
    cout << v[i] << "\n";
  }
}

void printWeights(vector<vector <double>> dataset){
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

vector<double> parseLine(string a){
    int i,j;
    vector<double> va;
    string n="";
    int la=a.length();
    for(i=0;i<la;i++){
        if(a[i]!=',' && a[i]!=' '){
          n+=a[i];   
        }
        if(a[i]==',' || i==la-1){
            std::string::size_type sz;
            double number = std::stod (n,&sz);
            va.push_back(number);
            n="";
        }
    }
    return va;
}

vector<double> randomWeights(int dimension){
    vector<double> weights;
    int i;
    for(i=0;i<dimension;i++){
        int r = (rand() % 99) + 0;
        double wr=(double)r/100;
        weights.push_back(wr);
    }
    return weights;
}

double bias=1;
int convergence=0;

vector<double> perceptorTraining(vector<double> training_examples, int dimension, vector<double> weight){
    int i=0;
    double learning_rate=0.2;
    double sum=0;
    for(i=0;i<dimension;i++){
       sum+=training_examples[i]*weight[i];
    }
    sum=sum+bias;
    //cout << "Suma es: "<< sum << "\n";
    double activation;
    if(sum<0){
      activation=0;
    } 
    else{
       activation=1;
    }
    for(i=0;i<dimension;i++){
       weight[i]=weight[i]+((training_examples[dimension]-activation)*learning_rate*training_examples[i]);
    }
    double error= training_examples[dimension]-activation;
    if(error==0){
       convergence++;
    }else{
       bias=bias+(learning_rate*error);
    }
    //cout << convergence << "\n";
    //cout << "los pesos son" << "\n";
    //printVector(weight);
    return weight;
}


void perceptorTest(vector<double> test_examples,  vector<double> weight, int dimension){
   int i;
   double sum=0;
   for(i=0;i<dimension;i++){
       sum+=test_examples[i]*weight[i];
   }
   sum=sum+bias;
   //cout << "Suma es: "<< sum << "\n";
   double activation;
   if(sum<0){
       activation=0;
   } 
   else{
       activation=1;
   }
   cout <<activation << "\n";
}

int main(){
    srand (time(NULL));
    int i,j=0,dimension,size_training_set,size_test_set;
    vector<vector<double>> training_examples,test_examples;
    vector<string> b;
    string line;
    cin >> dimension;
    //cout << "Dimension: " <<dimension <<"\n";
    cin >> size_training_set;
    //cout << "Tamaño training set: " <<size_training_set <<"\n";
    cin >> size_test_set;
    //cout << "Tamaño de la test set: " <<size_test_set <<"\n";
    i=3;
    while(getline(cin, line)){
      if(i<(4+size_training_set) && line.length()>0){
         //cout << "Linea es training: "<< line << "\n"; 
         vector<double> a; 
         a=parseLine(line);
         training_examples.push_back(a);
      }
      else if(line.length()>0){
         //cout << "Linea es test: "<< line << "\n"; 
         vector<double> a; 
         a=parseLine(line);
         test_examples.push_back(a);
      }
      i++;
    }
    //vector<vector<double>> weights;
    vector<double> random_weights;
    //cout << "randomWeights: " << "\n";
    random_weights=randomWeights(dimension);
    //printVector(random_weights);
    while(convergence<size_training_set && j<10000){
        convergence=0;
        for(i=0;i<size_training_set;i++){
            //cout << "Iteracion: " << i << "\n";
            random_weights=perceptorTraining(training_examples[i],dimension,random_weights);
        }
        j++;
    }
    //cout << "Pesos finales: " << "\n";
    //printVector(random_weights);
    
    if(j>=10000){
        cout << "no solution found";
    }
    else{
        for(i=0;i<size_test_set;i++){
            perceptorTest(test_examples[i],random_weights,dimension);
        }
    }
    
    //cout << "Bias: " <<bias << "\n";
    return 0;
}