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

class statistics_library{
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
    void calc_stdevs();
    void calc_running_means();
    
    FILE* pFILE;
    void push_to_file();
};

void statistics_library::take_value(double action_value){
    vector<double> value_taken;
    value_taken.push_back (action_value);
    /// AJ
}

void statistics_library::carriage_return(vector<double> take_value){
     master_table.push_back(take_value);
    take_value.clear();
    
    /// AJ
}


}

void statistics_library::calc_means(int nmbr_runs, int nmbr_iterations){
    double total=0;
    vector<double> means;
    double mean;
    for (int n=0; n<nmbr_runs; n++) {
        vector <double> rows;
        rows=(master_table.at(n));
        for (int k=0; k<nmbr_iterations; k++){
            total+=rows.at(k);
        }
        mean=total/nmbr_iterations;
         means.push_back(mean);
    }
    /// AJ
}

void statistics_library::calc_medians(int nmbr_runs, int nmbr_iterations){
    vector<double> medians;
    int x;
    double median;
    for (int n=0; n<nmbr_runs; n++) {
        vector <double> rows;
        rows=(master_table.at(n));
        sort(rows.begin(),rows.end());
        x=nmbr_iterations/2;
        median=(rows.at(x)+rows.at(x+1))/2;
        medians.push_back(median);
    }
    
    /// AJ
}

void calc_stdevs(){
    /// AJ
    
}

void calc_running_means(){
    /// AJ
}

void push_to_file(){
    /// AJ
}

// Define class, stats_lib
//  class stats_lib{
//     Define the vector-building function, recieve_score
//      double recieve_score (double rwrd_val)
//          {vector<double> pulled_rwrd
//          pulled_rwrd.push_back(rwrd_val)
//      } end function
//     Define function, table-buidling function carriage_return
//      double carriage_return (pulled_rwrd)
//          {vector<vector<double> > stats_table [THIS IS A TABLE (VECTOR OF VECTORS)]
//
//      } end function
//Define function, stats_ops
// double stats_ops (


#endif
