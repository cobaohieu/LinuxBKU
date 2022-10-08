#include <iostream>
#include <fstream>
using namespace std;
#include <cstdio>
#include <unistd.h>
#include <cstdlib>
#include<vector>
#include <sys/wait.h>
#include <sstream>
int num_movies = 1682;

void process_file_by_child(string input_file, string output_file){
	// Create and open a text file
	std::vector<std::vector<double>> reading_vector;
	reading_vector.resize(num_movies);
	
	
    ifstream MyInputFile(input_file);
    string line;
    while (getline (MyInputFile, line)) {
        int e_idx = 0;
        std::stringstream stream_tp(line);	
        int user_index, item_index;
        double rating;
        string token;
         while(getline(stream_tp, token, '\t')){
             switch (e_idx) {
                case 0:{
                    user_index = stoi(token) - 1;
                    break; 
                } 
                case 1:{
                    item_index = stoi(token) - 1;
                    break;
                }
                case 2:{		
                    rating = stoi(token) * 1.0; // stoi for ml-10k, netflix, ml-10m, and stod for ml-20m
                    break;
                }	
                default:{
                    break;                        
                }	
            }
            e_idx++;		
        }
        if (e_idx == 4){
            reading_vector[item_index].push_back(rating);
        }
    }
    
    MyInputFile.close();
    /// Compute and write average from the reading_vector to output file
	int movie_idx = 0;
	ofstream MyOutputFile(output_file);

	for(std::vector<double> ratings_for_movie : reading_vector){
	    double total_rating = 0.0;
	    for(double rating: ratings_for_movie){
	        total_rating += rating;
	    }
	    double avg_rating = (ratings_for_movie.size() == 0) ? 0 : total_rating / ratings_for_movie.size();
	    
	    // Print the result to output file
	    MyOutputFile << movie_idx << "\t" << avg_rating << '\n';
	    
	    movie_idx++;
	}
	MyOutputFile.close();
}

void process_file_by_parent(string input_file1, string input_file2, string output_file){
	// Create and open a text file
	
	std::vector<double> average_vector;
	average_vector.resize(num_movies);
    ifstream MyInputFile1(input_file1);
    string line;
    
    
    while (getline (MyInputFile1, line)) {
        int e_idx = 0;
        std::stringstream stream_tp(line);	
        int item_index=0;
        double avg_rating;
        string token;
         while(getline(stream_tp, token, '\t')){
             switch (e_idx) {
                case 0:{
                    item_index = stoi(token);
                    break; 
                } 
                case 1:{
                    avg_rating = stoi(token) * 1.0;
                    break;
                }
                default:{
                    break;                        
                }
            }
            e_idx++;		
        }
        if (e_idx == 2){
            average_vector[item_index] = avg_rating;
        }
    }
    MyInputFile1.close();
    
    ifstream MyInputFile2(input_file2);
    while (getline (MyInputFile2, line)) {
        int e_idx = 0;
        std::stringstream stream_tp(line);	
        int item_index;
        double avg_rating;
        string token;
         while(getline(stream_tp, token, '\t')){
             switch (e_idx) {
                case 0:{
                    item_index = stoi(token);
                    break; 
                } 
                case 1:{
                    avg_rating = stoi(token) - 1;
                    break;
                }
            }
            e_idx++;		
        }
        if (e_idx == 2){
            average_vector[item_index] = (average_vector[item_index] + avg_rating)/2;
        }
    }
    
    MyInputFile2.close();
    /// Compute and write average from the reading_vector to output file
	int movie_idx = 0;
	ofstream MyOutputFile(output_file);
	for(double avg_rating : average_vector){
	    // Print the result to output file
	    MyOutputFile << movie_idx << "\t" << avg_rating << '\n';
	    
	    movie_idx++;
	}
	
	MyOutputFile.close();
}



// int main() {
	
//     return 0;
    
  
// }