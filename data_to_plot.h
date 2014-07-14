//
//  data_to_plot.h
//  MAB
//
//  Created by Alex  Jennings on 7/3/14.
//  Copyright (c) 2014 ___Robotics___. All rights reserved.
//

#ifndef MAB_data_to_plot_h
#define MAB_data_to_plot_h
// Coding goes here...

/// DOCUMENTATION:
/// AJ

using namespace std;
#include <iostream>
#include<math.h>
#include<numeric>
#include<functional>

class statistics_library{ // a class containing statistical member functions devloped in the code below
    void carriage_return(vector<double>);
    void take_value(double);
    
    vector<double> single_stat_run;
    vector< vector<double> > master_table;
    
    vector<double> means;
    vector<double> medians;
    vector<double> stdevs;
    vector<double> running_means;
    void clear_all();
    
    void calc_means(int,int);
    void calc_medians(int,int);
    void calc_stdevs(int,int);
    void calc_running_means(int,int);
    
    FILE* pFILE;
    void push_to_file(vector<double>);
};

void statistics_library::take_value(double action_value){
    vector<double> value_taken;
    value_taken.push_back (action_value); //creates a vector that takes the action value for current episode
    /// AJ
}

void statistics_library::carriage_return(vector<double> take_value){
     master_table.push_back(take_value); //adds vector take_value to another vector as a table (a row)
    take_value.clear(); // clears the take_value vector for the next run
    
    /// AJ
}


void statistics_library::calc_means(int nmbr_runs, int nmbr_iterations){
    double total=0;
    vector<double> means;
    double mean;
    vector <double> rows;
    for (int n=0; n<nmbr_runs; n++) {
        rows=(master_table.at(n)); // accesses each row of table (take_value vectors)
        for (int k=0; k<nmbr_iterations; k++){ // accesses each element of the take_value vector
            total+=rows.at(k); //sums the values in the take_value vector
        }
        mean=total/nmbr_iterations; //calculates the mean of
         means.push_back(mean); // creates a vector containing the mean of each run
    }
    
    /// AJ
}

void statistics_library::calc_medians(int nmbr_runs, int nmbr_iterations){
    vector<double> medians;
    int x;
    double median;
    vector <double> rows;
    for (int n=0; n<nmbr_runs; n++) { // accesses each take_value vector in the table
        rows=(master_table.at(n));
        sort(rows.begin(),rows.end()); // sorts rows into ascending order
        x=nmbr_iterations/2;
        median=(rows.at(x)+rows.at(x+1))/2; // calculates the mean of the take_value vector
        medians.push_back(median); // creates a vector containing the median value of each run
    }
    
    /// AJ
}

void statistics_library::calc_stdevs(int nmbr_runs,int nmbr_iterations){
    vector<double> means;
    vector<double> stdevs_v1;
    vector<double> stdevs_v2;
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
            stdevs_v1.push_back(y);            // creates a vector conatining the above component
        }
        sum=accumulate(stdevs_v1.begin(), stdevs_v1.end(), 0); // sums the component containing vector
         N=1/(nmbr_iterations);
        stdevs_total=pow(N*sum,1/2);       // calulates the standard deviation for each run
        stdevs_v2.push_back(stdevs_total); // creates a vector containing standard dev. values of each run
    }

    /// AJ
    
    // This is the url for the standard deviation formula used for this calculation:
        //www.mathsisfun.com/data/standard-deviation-formulas.html
    
}

void statistics_library::calc_running_means(int nmbr_runs, int nmbr_iterations){
        double c=0;
        vector<double> running_avgs;
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
            running_avgs.push_back(running_avg); // creates a vector containing the running avg. of each run
        }

    /// AJ
}

void statistics_library::push_to_file(calc_running_means){
    FILE * pFile;
    pFile = fopen ("MAB.txt","wt");
    fprintf (pFile, "calc_running_means");
    fclose (pFile);
    /// AJ
}


#endif
