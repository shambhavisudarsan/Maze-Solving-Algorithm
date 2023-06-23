#include <bits/stdc++.h>
using namespace std;


/*
Compile your program with the optimization flag -O2 or -O3 enabled

generate some queries for large benchmarks you have created from the map website

    target at least three large maps
    for each map, generate at least 1000 pairs of queries and map modifiers
    test your ui-route implementation on these benchmarks

start to research GPU algorithms for your ui-route implementation

*/
int main() {
   int t = 1;
   cout<<t<<"\n";
   while (t--)
   {
      long long n = rand()%(2048)+1;
      long long m = rand()%(2048)+1;
      cout<<n<<" "<<m<<"\n";
      long long b = rand()%(n*m/20) - 2;
      cout<<b<<"\n";
      vector<pair<long long,long long>>blockage;
      deque<pair<long long,long long>>block;
      deque<pair<long long,long long>>unblock;
      for(int i=1;i<=n;i++){
         for(int j=1;j<=m;j++){
            blockage.push_back(make_pair(i,j));
         }
      }
      random_shuffle(blockage.begin(), blockage.end());
      for(int i=0;i<b;i++){
         cout<<blockage[i].first<<" "<<blockage[i].second<<"\n";
         block.push_back(make_pair(blockage[i].first,blockage[i].second));
      }
      for(int i=b;i<n*m;i++){
         unblock.push_back(make_pair(blockage[i].first,blockage[i].second));
      }
      long long queries = rand()%500+1;
      while(queries--){
         int choice = rand()%3 +1;
         if (choice == 2 && unblock.size() <= 2) choice = 3;
         if(choice == 1){
            random_shuffle(unblock.begin(), unblock.end());
            cout<<"Q "<<unblock[0].first<<" "<<unblock[0].second<<" "<<unblock[1].first<<" "<<unblock[1].second<<"\n";
         }
         else if(choice == 2){
            // block
            // if size of block array == n*m-2 then cant add block
            random_shuffle(unblock.begin(), unblock.end());
            cout<<"A "<<unblock[0].first<<" "<<unblock[0].second<<"\n";
            block.push_back(unblock[0]);
            unblock.pop_front();
         }
         else{
            random_shuffle(block.begin(), block.end());
            cout<<"C "<<block[0].first<<" "<<block[0].second<<"\n";
            unblock.push_back(block[0]);
            block.pop_front();
         }
      }
      cout<<"E"<<"\n";
   }
   

}