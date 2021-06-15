#include <iostream>
#include "PageRank.h"
#include <vector>
#include <numeric>
#include <math.h>

/* 
*	makeA(int num, double damping)
*	Description: adjust adj matrix
*	input: num -- dimention of matrix to be set and stored
*	       damping -- damping factor
*	return: 
*	effect: modified adjmatrix according to damping factor, set num of the pagerank obj
*/
void PageRank::makeA(int num, double damping) {
    this->num = num;//store num
    //resize adj matrix
    //A.resize(num,vector<double>(num));

    //use damping factor to generate the require extra factor
    double d_factor = (1-damping)/num;

    //adjust adj matrix according to pagerank alg
    for(int i = 0; i < num; i++){
        double sum = 0;
        for(int j = 0; j < num; j++){
            sum += A[j][i];
        }     
        if(sum == 0){
            //double z = 1/this->num;
            for(int j = 0; j < num; j++){
                A[j][i] = 1/(double)num;
            }              
        } else {
            for(int j = 0; j < num; j++){
                A[j][i] = (A[j][i]/sum)*damping+d_factor;
            }             
        }
    }
}

/* 
*	rank(vector<double> initial, int time, bool normalize)
*	Description: apply pagerank
*	input: initial -- starting vector
*	       time -- time of iteration
*	       normalize -- perform normalize when true
*	return: the result vector
*/
vector<double> PageRank::rank(vector<double> initial, int time, bool normalize) {
    //vectors which stores the intermediate result
    vector<double> temp = initial;
    vector<double> newtemp = initial;
    for(int t = 0; t < time; t++){
        for(int i = 0; i < num; i++){
            //initialize the vector
            newtemp[i] = 0;
            //calculate product of adjmatrix and vector 
            for(int j = 0; j < num; j++){
                newtemp[i] += A[i][j] * temp[j];

                if(normalize) {
                    double sum = 0;
                    //perform norm 2 normalize
                    for(std::vector<double>::iterator it = newtemp.begin(); it != newtemp.end(); ++it)
                        sum += (*it)*(*it);
                    double normalize = sqrt(sum);

                    for(int n = 0; n < num; n++){
                        newtemp[n] = newtemp[n] / normalize;
                    }
                }

            }     
        }
        temp = newtemp;
    }
    //store result in the pagerank obj
    pr_result = temp;
    return temp;
}

/* 
*	top_airport(int num)
*	Description: figure out the top num important airport
*	input: num -- top NUM important airport
*	return: the vector contains id of the top num important airport
*	effect: print the id of the top num important airport
*/
vector<int> PageRank::top_airport(int num){
    vector<int> airport;
    vector<double> largest;
    largest.resize(num);
    airport.resize(num);

    int position = 0;

    //figure out the index of the important airport in the pagerank result vector
    for(int i = 0; i < num; i++){
        double max = 0;
        for(auto it = pr_result.begin(); it != pr_result.end(); ++it){
            if(*it > max){
                bool flag = true;
                //check if the current airport is already on the list of the important airport
                for(auto temp = largest.begin(); temp != largest.end(); ++temp){
                    if(*temp == *it) {
                        flag = false;
                        break;
                    }
                }
                if(flag)
                    max = *it;
            }
        }
        largest[position] = (max);
        position++;
    }

    position = 0;
    //using the index and the name_list to find out the relating airport id
    for(int i = 0; i < num; i++){
        int count = 0;
        for(auto it = pr_result.begin(); it != pr_result.end(); ++it){
            if(largest[i] == *it){
                airport[position] = (name_list[count]);
                position++;
            }
            count++;
        }
    }

    //print the id
    cout<<"top "; 
    cout<<num; 
    cout<<" important airport\n"; 
    for(int i = 0; i < num; i++){
        cout<<airport[i];
        cout<<"\n";
    }
    return airport;
}

/* 
*	initial_vector()
*	Description: generate the starting vector
*	input: 
*	return: the starting vector for pagerank
*	effect:
*/
vector<double> PageRank::initial_vector(){
    vector<double> initial;
    initial.resize(this->num);
    for(int i = 0; i < this->num; i++){
        initial[i] = rand();
    }
    return initial;
}

/* 
*	print_adjmatrix()
*	Description: print the adj matrix
*	input: 
*	return: 
*	effect: print the adj matrix. column and row are labeled
*/
void PageRank::print_adjmatrix(){
    cout<<"adj matrix"<<endl;
    cout<<"      ";
    for(int i = 0; i < this->num; i++){
        cout<<this->name_list[i];
        cout<<"           ";
    }
    cout<<"\n";
    for(int i = 0; i < this->num; i++){
        cout<<this->name_list[i];
        cout<<"  ";
        for(int j = 0; j < this->num; j++){
            cout<<this->A[i][j];
            cout<<"  ";
        } 
        cout<<"\n";
    }
    cout<<"\n";
}

/* 
*	print_result()
*	Description: print the result vector
*	input: 
*	return: 
*	effect: print the result vector. airport ids are also labeled
*/
void PageRank::print_result(){
    cout<<"page rank result\n"; 
    cout<<" ID      value\n"; 
    for(int i = 0; i < this->num; i++){
        cout<<this->name_list[i];
        cout<<" ";
        cout<<this->pr_result[i];
        cout<<"\n";
    }
    cout<<"\n";
}

