//
//  data_to_plot.h
//  MAB
//
//  Created by Alex  Jennings on 7/3/14.
//  Copyright (c) 2014 ___Robotics___. All rights reserved.
//

#ifndef MAB_data_to_plot_h
#define MAB_data_to_plot_h

/// DOCUMENTATION:
/// @AJ

using namespace std;
#include <iostream>
#include<math.h>
#include<numeric>
#include<functional>
#define z 100

class statistics_library{ // a class containing statistical member functions devloped in the code below
    /// Programmer-user functions
public:
    void carriage_return();
    void take_value(double);
    void run_stats_library();
    
    /// Hidden from the programmer-user
private: 
    vector<double> single_stat_run;
    vector< vector<double> > master_table;
    
    vector<double> means;
    vector<double> medians;
    vector<double> stdevs;
    vector<double> running_means;
    vector<double> n_episode_running_means;
    void prep();
    void reset();
    
    void calc_means();
    void calc_medians();
    void calc_stdevs();
    void calc_running_means();
    void calculate_z_episode_running_means();
    void calculate_all_statistics();

    FILE* pFile;
    void push_to_file();
};

void statistics_library::take_value(double action_value){
    single_stat_run.push_back (action_value); //creates a vector that takes the action value for current episode
    /// @AJ
}

void statistics_library::carriage_return(
){
    master_table.push_back(single_stat_run); //adds vector take_value to another vector as a table (a row)
    single_stat_run.clear(); // clears the take_value vector for the next run
    /// @AJ
}


void statistics_library::calc_means(){
    int nmbr_runs = master_table.size();
    int nmbr_iterations = master_table.at(0).size();
    
    double total=0;
    double mean;
    vector <double> rows;
    for (int n=0; n<nmbr_runs; n++) {
        rows=(master_table.at(n)); // accesses each row of table (take_value vectors)
        for (int k=0; k<nmbr_iterations; k++){ // accesses each element of the take_value vector
            total+=rows.at(k); //sums the values in the take_value vector
        }
        mean=total/nmbr_iterations; //calculates the mean of
        means.push_back(mean); // creates a vector containing the mean of each run
        total = 0; /// @AJ
    }
    
    /// AJ
}

void statistics_library::calc_medians(){
    int nmbr_runs = master_table.size();
    int nmbr_iterations = master_table.at(0).size();
    int x;
    int w;
    double median;
    vector <double> rows;
    
    if(nmbr_iterations%2 == 1){ /// @AJ
    for (int n=0; n<nmbr_runs; n++) { // accesses each take_value vector in the table
        rows=(master_table.at(n));
        sort(rows.begin(),rows.end()); // sorts rows into ascending order
        x=nmbr_iterations/2;
        median=(rows.at(x)+rows.at(x+1))/2; // calculates the mean of the take_value vector
        medians.push_back(median); // creates a vector containing the median value of each run
    }
    }
    
    if(nmbr_iterations%2 == 0){
        for (int n=0; n<nmbr_runs; n++) {
        rows=(master_table.at(n));
        sort(rows.begin(),rows.end());
        w=(nmbr_iterations+1)/2;
        median=rows.at(w);
        medians.push_back(median);
        /// @AJ
    }
    }
}

void statistics_library::calc_stdevs(){
    int nmbr_runs = master_table.size();
    int nmbr_iterations = master_table.at(0).size();
    
    vector<double> means;
    vector<double> stdevs_comp;
    double N;                   // defines variables and vectors for intermediate calculations
    double u;
    double v;
    double y;
    double sum;
    double stdevs_total;
    vector <double> rows;
    for (int n=0; n<nmbr_runs; n++) { // accesses each take_value vector in the table
        rows=(master_table.at(n));
        u=means.at(n); // accesses the mean for each run or take_value vector
        for (int k=0; k<nmbr_iterations; k++){ // accesses each value of each take_value vector
            v=rows.at(k);                      // calculates "mean & reward_value difference" component
            y=pow(v-u,2);
            stdevs_comp.push_back(y);            // creates a vector containing the above component
        }
        sum=accumulate(stdevs_comp.begin(), stdevs_comp.end(), 0); // sums the component-containing vector
         N=1/(nmbr_iterations);
        stdevs_total=pow(N*sum,1/2);       // caclulates the standard deviation for each run
        stdevs.push_back(stdevs_total); // creates a vector containing standard dev. values of each run
    }

    
    // This is the url for the standard deviation formula used for this calculation:
        //www.mathsisfun.com/data/standard-deviation-formulas.html
    
}

void statistics_library::calc_running_means(){
    int nmbr_runs = master_table.size();
    int nmbr_iterations = master_table.at(0).size();
        double c=0;
        double running_avg;
        vector <double> rows;
        double N=0;
    
        for (int n=0; n<nmbr_runs; n++) {
            rows=(master_table.at(n)); // accesses each row of table (take_value vectors)
            for (int k=0; k<nmbr_iterations; k++){ // accesses each element of the take_value vector
                c++;
                N+=rows.at(k);
                running_avg=N/c; // calculates the running average for each take_value vector
            }
            running_means.push_back(running_avg); // creates a vector containing the running avg. of each run
        }
    /// @AJ
}

void statistics_library:: calculate_z_episode_running_means(){
    int nmbr_runs = master_table.size();
    int nmbr_iterations = master_table.at(0).size();
    int a =0;
    double c=0;
    double running_avg=0;
    vector <double> rows;
    double N=0;
    double M=0;
    
    
    for (int h=0; h<nmbr_runs; h++) {
        rows=(master_table.at(h)); // accesses each row of table (take_value vectors)
        for (int k=0; k<z; k++){ // accesses each element of the take_value vector
            c++;
            N+=rows.at(k);
            running_avg=N/c; // calculates the running average for each take_value vector
            }
        
        
        for (int m=z; m<nmbr_iterations; m++){
            a=m-1;
            M=running_avg;
            running_avg=M-rows.at(m-1)/a+rows.at(m)/a;
        }
        }
        n_episode_running_means.push_back(running_avg); // creates a vector containing the running avg. of each run
    }
    /// @AJ



    /// @AJ running means with a certain length of memory. The one from above does 1:nmbr_iterations. This one should do (nmbr_iterations-n):nmbr_iterations


void statistics_library:: calculate_all_statistics(){
    calc_means();
    calc_medians();
    calc_stdevs();
    calc_running_means();
    calculate_z_episode_running_means();
    
    
    /// @AJ have this function execute all the other statistics functions!
}

void statistics_library::prep(){
    
    single_stat_run.clear();
    means.clear();
    medians.clear();
    stdevs.clear();
    running_means.clear();
    
    
    /// @AJ Clears all the vectors associated with this class, but not the master table.
}

void statistics_library::reset(){
    
    single_stat_run.clear();
    means.clear();
    medians.clear();
    stdevs.clear();
    running_means.clear();
    master_table.clear();
    
    /// @AJ Clears all the vectors associated with this class, including the master table.
}

void statistics_library::push_to_file(){
    /// Run function calculate_all_statistics() first.
    int nmbr_iterations = master_table.at(0).size();
    pFile = fopen ("MAB.txt","wt");
    for(int i=0; i<nmbr_iterations; i++){
        fprintf (pFile, "%.4f\t", means.at(i));
    }
    fprintf (pFile, "\b \b\n");
    for(int i=0; i<nmbr_iterations; i++){
        fprintf (pFile, "%.4f\t", medians.at(i));
    }
    fprintf (pFile, "\b \b\n");
    for(int i=0; i<nmbr_iterations; i++){
        fprintf (pFile, "%.4f\t", stdevs.at(i));
    }
    fprintf (pFile, "\b \b\n");
    for(int i=0; i<nmbr_iterations; i++){
        fprintf (pFile, "%.4f\t", running_means.at(i));
    }
    fprintf (pFile, "\b \b\n");
    for(int i=0; i<nmbr_iterations; i++){
        fprintf (pFile, "%.4f\t", n_episode_running_means.at(i));
    }
    fclose (pFile);
    /// @AJ
}

//<<<<<<< HEAD
/*=======
void statistics_library::run_stats_library(){
    prep();
    calculate_all_statistics(n);
    push_to_file();
    // reset();
}
>>>>>>> FETCH_HEAD*/

#endif



