#include<bits/stdc++.h>
using namespace std;

set<pair<int,int>> qpoints;
int getSide(pair<int, int> p1, pair<int, int> p2, pair<int, int> p) {
    return  ((p2.first - p1.first) * (p.second - p1.second) - (p2.second - p1.second) * (p.first - p1.first) ) > 0 ? 1 : -1;
}

int getDistance(pair<int, int> p1, pair<int, int> p2, pair<int, int> p) {
    return abs((p2.first - p1.first) * (p.second - p1.second) - (p2.second - p1.second) * (p.first - p1.first) );
}

void quickHull(pair<int,int> p1, pair<int,int> p2, int side , vector<pair<int,int>> &points){

    // cout<<"in"<<endl;
    pair<int,int> maxpoint ;
    pair<int,int> checkpair = {INT_MIN, INT_MIN};

    maxpoint = checkpair;

    int maxDis = INT_MIN;

    for (int i = 0; i < points.size(); i++) {
        if (getSide(p1, p2, points[i]) == side) {
            int dist = getDistance(p1, p2, points[i]);
            if (dist > maxDis) {
                maxDis = dist;
                maxpoint = points[i];
            }
        }
    }

    if ( maxpoint == checkpair){
        return;
    } 
    
    qpoints.insert(maxpoint);
    qpoints.insert(p1); qpoints.insert(p2);
    quickHull(p1, maxpoint, (-1)*(getSide(p1,maxpoint,p2)) , points);
    quickHull( maxpoint,p2, (-1)*(getSide(maxpoint,p2,p1)) , points);
}

int main(){

        int n; cin>>n;
        vector<pair<int,int>> p(n);
        srand(static_cast<unsigned>(time(nullptr)));
        for (int i = 0; i < n; ++i)
        {
            int a = rand()%100;
            int b = rand()%100;
            int snum = rand()%2;

            if(snum)
                p[i] = {-1*a,b};
            else p[i] = {b,a};     
        }


        cout<<"point===="<<endl;
        cout<<"x = [";
        for(int i=0; i<n ; i++){
            cout<<p[i].first<<",";
        }
        cout<<"]"<<endl;
        cout<<"y = [";
        for(int i=0; i<n ; i++){
            cout<<p[i].second<<",";
        }
        cout<<"]"<<endl;

    ofstream inputFile("input_points.txt");
    for (int i = 0; i < n; i++) {
        inputFile << p[i].first << "," << p[i].second << endl;
    }
    inputFile.close();



    pair<int,int> minp, maxp;
    minp=maxp = p[0];


auto start = chrono::high_resolution_clock::now();

for (int i = 0; i < p.size(); i++) {
    if (minp.first > p[i].first || (minp.first == p[i].first && minp.second > p[i].second)) {
        minp = p[i];
    }
    if (maxp.first < p[i].first || (maxp.first == p[i].first && maxp.second < p[i].second)) {
        maxp = p[i];
    }
}

    map<pair<int,int>,int> pSide;

    for(int i=0; i<p.size(); i++){
        pSide[p[i]] = getSide(minp, maxp, p[i]);
    }

    cout<<"qickhull points"<<endl;
    quickHull(minp, maxp, -1, p);
    quickHull(minp,maxp,1,p);
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);

        set<pair<double,pair<int,int>>> anglep;
        anglep.insert({INT_MIN,minp});

        for(auto i: qpoints){
            if(minp.first==i.first && minp.second == i.second) continue;

            double dist = ((double)(minp.second - i.second)/(minp.first - i.first));
            anglep.insert({dist,i});

        }
        cout<<"X= [";
        for(auto i: anglep){
            cout<<i.second.first<<",";
        }
        cout<<"]"<<endl;
        cout<<"Y= [";
        for(auto i: anglep){
            cout<<i.second.second<<",";
        }
        cout<<"]"<<endl;

    ofstream quickHullFile("quickhull_points.txt");
    for (auto i : anglep) {
        quickHullFile << i.second.first << "," << i.second.second << endl;
    }
    quickHullFile.close();
    cout << "Time taken by QuickHull: " << duration.count() << " microSeconds" << endl;
    return 0;
}