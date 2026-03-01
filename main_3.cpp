#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>

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

string checkType (vector<double>& query) {
    string type;
    if (query[0] > query[1]) type = "E";
    else type = "I";

    if (query[2] > query[3]) type += "S";
    else type += "N";

    if (query[4] > query[5]) type += "T";
    else type += "F";

    if (query[6] > query[7]) type += "J";
    else type += "P";

    return type;
}

string findNewType(vector<Data>& dataset,vector<pair<double,int>> nearest) {
    string t1 = checkType(dataset[nearest[0].second].data);
    string t2 = checkType(dataset[nearest[1].second].data);
    string t3 = checkType(dataset[nearest[2].second].data);
    string type;

    for (int i = 0; i < 4; i++) {
        if (t1[i] == t2[i] || t1[i] == t3[i])
            type += t1[i];
        else if (t2[i] == t1[i] || t2[i] == t3[i])
            type += t2[i];
    }
    return type;
}

int partition(vector<pair<double,int>>& a, int l, int r) {
    double pivot = a[r].first;
    int i = l;

    for (int j = l; j < r; j++) {
        if (a[j].first <= pivot) {
            swap(a[i], a[j]);
            i++;
        }
    }
    swap(a[i], a[r]);
    return i;
}

void quickselect(vector<pair<double,int>>& a, int l, int r, int k) {
    if (l >= r) return;

    int pivotIdx = l + rand() % (r - l + 1);
    swap(a[pivotIdx], a[r]);

    int p = partition(a, l, r);

    if (p == k) return;
    else if (p > k)
        quickselect(a, l, p - 1, k);
    else
        quickselect(a, p + 1, r, k);
}


vector<pair<double,int>> findNearest(vector<pair<double,int>>& dataset,int k) {
    if (k >= dataset.size()) return dataset;
    quickselect(dataset, 0, dataset.size()-1, k-1);
    return vector<pair<double,int>>(dataset.begin(), dataset.begin()+k);

}

vector<pair<double,int>> findknn(vector<Data>& dataset,vector<double>& query) {
    vector<pair<double,int>> calData;
    for (int i = 0; i < dataset.size(); i++) {
        double result_item = calculatequery(dataset[i].data,query);
        calData.push_back(make_pair(result_item,i));
    }
    return findNearest(calData,3);
}

int main() {
    vector<Data> dataset = loadCSV("mbti.csv");
    vector<double> query = {32.0,32.0,27.0,36.0,29.0,31.0,28.0,23.0};
    vector<pair<double,int>> neighbors = findknn(dataset,query);

   for (int i = 0; i < neighbors.size(); i++) {
       cout << "weight = " << neighbors[i].first << " " << "index = " << neighbors[i].second << endl;
   }
    string newType = findNewType(dataset, neighbors);
    cout << newType << endl;
    return 0;
}