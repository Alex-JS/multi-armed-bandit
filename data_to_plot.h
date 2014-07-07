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

class statistics_library{
    void carriage_return();
    void take_value(double);
    
    vector<double> single_stat_run;
    vector< vector<double> > master_table;
    
    vector<double> means;
    vector<double> medians;
    vector<double> stdevs;
    vector<double> running_means;
    void clear_all();
    
    void calc_means();
    void calc_medians();
    void calc_stdevs();
    void calc_running_means();
    
    FILE* pFILE;
    void push_to_file();
};

void clear_all(){
    /// AJ
}

void carriage_return(){
    /// AJ
}

void take_value(double val){
    /// AJ
}

void calc_means(){
    /// AJ
}

void calc_medians(){
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

#endif
