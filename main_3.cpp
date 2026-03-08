#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>

using namespace std;

struct Data {
    vector<double> values;
    string type;
    string nick;
};

vector<Data> loadCSV(const string& filename) {
    vector<Data> dataset;
    ifstream file(filename);

    if (!file.is_open()) {
        cout << "Cannot open file\n";
        return dataset;
    }

    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        string value;
        Data d;

        for (int i = 0; i < 8; i++) {
            getline(ss, value, ',');
            d.values.push_back(stod(value));
        }

        getline(ss, d.type, ',');
        getline(ss, d.nick);

        dataset.push_back(d);
    }

    return dataset;
}

double calculateDistance(const vector<double>& data, const vector<double>& query) {
    double sum = 0;

    for (size_t i = 0; i < data.size(); i++) {
        double diff = query[i] - data[i];
        sum += diff * diff;
    }

    return sqrt(sum);
}

string findNewType(const vector<Data>& dataset, const vector<pair<double,int>>& nearest) {

    string t1 = dataset[nearest[0].second].type;
    string t2 = dataset[nearest[1].second].type;
    string t3 = dataset[nearest[2].second].type;

    string type;

    for (int i = 0; i < 4; i++) {

        if (t1[i] == t2[i] || t1[i] == t3[i])
            type += t1[i];

        else if (t2[i] == t1[i] || t2[i] == t3[i])
            type += t2[i];

        else
            type += t1[i];
    }

    return type;
}

int partition(vector<pair<double,int>>& arr, int l, int r) {

    double pivot = arr[r].first;
    int i = l;

    for (int j = l; j < r; j++) {

        if (arr[j].first <= pivot) {
            swap(arr[i], arr[j]);
            i++;
        }
    }

    swap(arr[i], arr[r]);
    return i;
}

void quickselect(vector<pair<double,int>>& arr,int l, int r, int k) {

    if (l >= r) return;

    int pivotIdx = l + rand() % (r - l + 1);
    swap(arr[pivotIdx], arr[r]);

    int p = partition(arr, l, r);

    if (p == k)
        return;
    else if (p > k)
        quickselect(arr, l, p - 1, k);
    else
        quickselect(arr, p + 1, r, k);
}

vector<pair<double,int>> findNearest(vector<pair<double,int>>& data, int k) {

    if (k >= data.size())
        return data;

    quickselect(data, 0, data.size() - 1, k - 1);

    return vector<pair<double,int>>(data.begin(), data.begin() + k);
}

vector<pair<double,int>> findKNN(const vector<Data>& dataset, const vector<double>& query) {

    vector<pair<double,int>> distances;

    for (size_t i = 0; i < dataset.size(); i++) {

        double dist = calculateDistance(dataset[i].values, query);

        distances.push_back({dist, (int)i});
    }

    return findNearest(distances, 3);
}

int main() {

    vector<Data> dataset = loadCSV("mbti.csv");

    vector<double> query = {
        24.8,33.0,30.0,39.0,
        27.0,35.0,31.0,28.0
    };

    vector<pair<double,int>> neighbors = findKNN(dataset, query);

    for (size_t i = 0; i < neighbors.size(); i++) {

        int idx = neighbors[i].second;

        cout << "#"<< i + 1
             << " nearest : "
             << dataset[idx].nick
             << " distance = "
             << neighbors[i].first
             << endl;
    }

    string newType = findNewType(dataset, neighbors);

    cout << "Predicted Type: " << newType << endl;
}