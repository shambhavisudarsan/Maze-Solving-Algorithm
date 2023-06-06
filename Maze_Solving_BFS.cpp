#include <bits/stdc++.h>
using namespace std;

// S: n m
// B - blocked nodes
// following B nodes are blocked
// Q: 1 1 3 4 - find shortest path
// A: Add node as blocked
// C: clear a blocked node
// E: end

bool check_valid(int n,int m, int x,int y,vector<vector<char>> &grid){
    if(x>=n || y>=m || x<0 || y<0 || grid[x][y]=='B') return false;
    else return true;
}

vector<vector<int>> bfs(int n,int m,vector<vector<char>> &grid, int sx,int sy,int tx,int ty){
    int dx[4] = {1,0,-1,0};
    int dy[4] = {0,1,0,-1};
    queue<pair<int,int>>queue_of_grid;
    vector<vector<bool>>visited;
    vector<vector<int>>distance;
    for(int i=0;i<n;i++){
        vector<bool>temp;
        vector<int>dist_temp;
        for(int j=0;j<m;j++){
            temp.push_back(false);
            dist_temp.push_back(0);
        }
        visited.push_back(temp);
        distance.push_back(dist_temp);
    }
    queue_of_grid.push(make_pair(sx,sy));
    visited[sx][sy] = true;
    distance[sx][sy] = 0;
    while(true){
        if (queue_of_grid.front().first==tx && queue_of_grid.front().second==ty) break;
        int curr_x = queue_of_grid.front().first;
        int curr_y = queue_of_grid.front().second;
        queue_of_grid.pop();
        for(int i=0;i<4;i++){
            if(check_valid(n,m,curr_x+dx[i],curr_y+dy[i],grid) && !visited[curr_x+dx[i]][curr_y+dy[i]]){
                queue_of_grid.push(make_pair(curr_x+dx[i],curr_y+dy[i]));
                visited[curr_x+dx[i]][curr_y+dy[i]] = true;
                distance[curr_x+dx[i]][curr_y+dy[i]] = distance[curr_x][curr_y]+1;

            }
        }
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cout<<grid[i][j]<<" ";
        }
        cout<<endl;
    }
    return distance;
}

int main(){
    int n,m,b;
    cout<<"Enter size of grid"<<endl;
    cin>>n>>m;
    cout<<"Enter number of blockages"<<endl;
    cin>>b;
    cout<<"Enter coordinates of blockages"<<endl;
    vector<vector<char>> grid;
    for(int i=0;i<n;i++){
        vector<char>temp;
        for(int j=0;j<m;j++){
            temp.push_back('U');
        }
        grid.push_back(temp);
    }
    // updating blocked nodes
    for(int i=0;i<b;i++){
        int x,y;
        cin>>x>>y;
        grid[x][y] = 'B';
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cout<<grid[i][j]<<" ";
        }
        cout<<endl;
    }
    // further queries handled (Q,E and C)
    char input;
    cin>>input;
    while(input!='E'){
        if(input == 'Q'){
            int sx,sy,tx,ty;
            cin>>sx>>sy>>tx>>ty;
            vector<vector<int>> distance = bfs(n,m,grid,sx,sy,tx,ty);
            cout<<"Shortest Distance from ("<<sx<<","<<sy<<")"<<" is : "<<distance[tx][ty]<<endl;
            cin>>input;
        }
        else if(input == 'A'){
            int x,y;
            cin>>x>>y;
            grid[x][y]='B';
            cin>>input;
        }
        else if(input == 'C'){
            int x,y;
            cin>>x>>y;
            grid[x][y]='U';
            cin>>input;
        }
        else{
            return 0;
        }
    }
}
