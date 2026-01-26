#include <algorithm>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <ranges>

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

vector<int> findknn(vector<Data>& dataset,vector<double>& query, int k) {
    vector<pair<double,int>> result;
    vector<int> neighbors;
    for (int i = 0; i < dataset.size(); i++) {
        double result_item = calculatequery(dataset[i].data,query);
        result.push_back({result_item,i});
    }
    sort(result.begin(), result.end());
    for (int i = 0; i < k; i++) {
        neighbors.push_back(result[i].second);
    }
    return neighbors;
}

int main() {
    vector<Data> dataset = loadCSV("mbti.csv");
    vector<double> query = {32.0,32.0,27.0,36.0,29.0,31.0,28.0,23.0};
    vector<int> neighbors = findknn(dataset,query,3);

    for (int idx : neighbors) {
        cout << "Index: " << idx << endl;
    }
    return 0;
}