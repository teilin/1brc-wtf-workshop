#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <unordered_map>
using namespace std;

struct StationData {
  float minMeasurement;
  float maxMeasurement;
  float sum;
  int count;
  StationData()
      : maxMeasurement(numeric_limits<float>::lowest()),
        minMeasurement(numeric_limits<float>::max()),
        sum(0),
        count(0) {}
};

void parseLine(unordered_map<string, StationData> *results, const string *line);

int main(int argc, char *argv[]) {
  string filename = "sample.txt";
  if (argc > 1) filename = argv[1];
  cout << "Reading records from " << filename << endl;

  ifstream file(filename);
  string line;

  if (!file.is_open()) {
    cerr << "Could not open file " << filename << endl;
    return 1;
  }

  auto start = chrono::high_resolution_clock::now();
  unordered_map<string, StationData> results;
  while (getline(file, line)) {
    parseLine(&results, &line);
  }
  file.close();
  auto end = chrono::high_resolution_clock::now();

  int countMeasurements(0);
  for (const auto &pair : results) {
    countMeasurements += pair.second.count;
    float mean = pair.second.sum / pair.second.count;
    cout << pair.first << ";" << fixed << setprecision(1)
         << pair.second.minMeasurement << ";" << mean << ";"
         << pair.second.maxMeasurement << endl;
  }

  chrono::duration<double> elapsed = end - start;
  double total_seconds = elapsed.count();
  int minutes = static_cast<int>(total_seconds / 60);
  double seconds = total_seconds - (minutes * 60);

  cerr << "Read " << countMeasurements << " measurements in " << minutes << "m"
       << fixed << setprecision(3) << seconds << "s" << endl;
  return 0;
}

void parseLine(unordered_map<string, StationData> *results,
               const string *line) {
  stringstream ss(*line);
  string stationName, measurementStr;
  getline(ss, stationName, ';');
  getline(ss, measurementStr);
  float measurement = stof(measurementStr);

  StationData current = (*results)[stationName];
  current.sum += measurement;
  current.minMeasurement = min(current.minMeasurement, measurement);
  current.maxMeasurement = max(current.maxMeasurement, measurement);
  current.count += 1;
  (*results)[stationName] = current;
}
