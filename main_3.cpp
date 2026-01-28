#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <limits>

using namespace std;

struct Data {
    vector<double> data;
};

vector<Data> loadCSV(string filename) {
    vector<Data> dataset;
    ifstream file(filename);
    string line;

    if (!file.is_open()) {
        cout << "Cannot open file" << endl;
        return dataset;
    }

    while (getline(file, line)) {
        stringstream ss(line);
        string value;
        Data d;

        while (getline(ss, value, ',')) {
            d.data.push_back(stod(value));
        }
        dataset.push_back(d);
    }
    return dataset;
}

double calculatequery(vector<double>& dataset,vector<double>& query) {
    vector<double> result;
    double sum = 0;
    for (int i = 0; i < dataset.size(); i++) {
        double result_item = query[i]-dataset[i];
        sum = sum + (result_item)*(result_item);
    }
    return sqrt(sum);
}

vector<pair<double,int>> findknn(vector<Data>& dataset,vector<double>& query) {
    double INF = std::numeric_limits<double>::infinity();
    vector<pair<double,int>> result = {{INF,NULL},{INF,NULL},{INF,NULL}};

    for (int i = 0; i < dataset.size(); i++) {
        double result_item = calculatequery(dataset[i].data,query);
        if (result_item<result[0].first) {
            result[2].first = result[1].first;
            result[2].second = result[1].second;

            result[1].first = result[0].first;
            result[1].second = result[0].second;

            result[0].first = result_item;
            result[0].second = i;
        }
        else if (result_item<result[1].first) {
            result[2].first = result[1].first;
            result[2].second = result[1].second;

            result[1].first = result_item;
            result[1].second = i;
        }
        else if (result_item<result[2].first) {
            result[2].first = result_item;
            result[2].second = i;
        }
    }
    return result;
}

int main() {
    vector<Data> dataset = loadCSV("mbti.csv");
    vector<double> query = {32.0,32.0,27.0,36.0,29.0,31.0,28.0,23.0};
    vector<pair<double,int>> neighbors = findknn(dataset,query);

   for (int i = 0; i < neighbors.size(); i++) {
       cout << "weight = " << neighbors[i].first << " " << "index = " << neighbors[i].second << endl;
   }
    return 0;
}