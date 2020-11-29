//
//  main.cpp
//  mnk_lab4
//
//  Created by MacBook on 11/29/20.
//

#include <iostream>
#include <math.h>
#include <fstream>
#include <vector>

using namespace::std;
#define eps 0.001

void matrixInsert(vector<double> &x, vector<double> &y){
    double count = 0;
    for(int i = 0; i < 10; i++){
        x[i] = count;
        count += 0.1;
    }
    y = {0.957, 0.969, 0.976, 0.978, 0.975, 0.968, 0.954, 0.939, 0.918, 0.894};
}

vector<double> sle(vector<vector <double>> a, vector <double> y, int n) {
    vector<double> x(n);
    double max;
    int k, index;
    k = 0;
    while (k < n) {
        max = abs(a[k][k]);
        index = k;
        for (int i = k + 1; i < n; i++) {
            if (abs(a[i][k]) > max) {
                max = abs(a[i][k]);
                index = i;
            }
        }
        if (max < eps) {
            x.clear();
            return x;
        }
        for (int j = 0; j < n; j++) {
            swap(a[k][j], a[index][j]);
        }
        swap(y[k], y[index]);

        for (int i = k; i < n; i++) {
            double res = a[i][k];
            if (abs(res) < eps) continue;
            for (int j = 0; j < n; j++)
                a[i][j] /= res;
            y[i] /= res;
            if (i == k) continue;
            for (int j = 0; j < n; j++) {
                a[i][j] -= a[k][j];
            }
            y[i] -= y[k];
        }
        k++;
    }
    for (k = n - 1; k >= 0; k--) {
        x[k] = y[k];
        for (int i = 0; i < k; i++)
            y[i] = y[i] - a[i][k] * x[k];
    }
  return x;
}

void mnk(vector<double> x, vector<double> y, int m, int N){
    vector<double> powerX(2*m);
    vector<vector<double> > sumX(m, vector<double>(m));
    vector<double> praw(m);
    double count;
    for(int i = 0; i < 2 * m; i++){
        count = 0;
        for(int j = 0; j < N; j++){
            count += pow(x[j], i);
        }
        powerX[i] = count;
    }
    
    for(int i = 0; i < m ; i++){
        for(int j = 0; j < m ; j++){
            sumX[i][j] = powerX[i + j];
        }
    }
    
    for(int i = 0; i < m ; i++){
        count = 0;
        for(int j = 0; j < N; j++){
            count += x[j] * pow(y[j], j);
        }
    }
    vector<double> a = sle(sumX, praw, m );
    count = 0;
    for(int i = 0; i < N; i++){
        double count2 = y[i];
        for(int j = 0; j < m ; j++){
            count2 -= a[j] * pow(x[j], j + 1);
        }
        count += count2;
    }
    double result = sqrt((1.0/(N - m))* count);
    cout << result;
}

int main(int argc, const char * argv[]) {
    
    vector<double> x(10);
    vector<double> y(10);
    matrixInsert(x, y);
    mnk(x, y, 2, 10);
//    cout << "yo";
    return 0;
}
