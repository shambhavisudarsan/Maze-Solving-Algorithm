// module load cuda
// Connect to chpc kingspeak node - srun -M kingspeak --account=soc-gpu-kp --partition=soc-gpu-kp --nodes=1 --ntasks=1 --gres=gpu -t 4:00:00 --pty bash

#include <bits/stdc++.h>

// S: n m
// B - blocked nodes
// following B nodes are blocked
// Q: 1 1 3 4 - find shortest path
// A: Add node as blocked
// C: clear a blocked node
// E: end

bool check_valid(int n,int m, int x,int y,std::vector<std::vector<char>> &grid){
    if(x>=n || y>=m || x<0 || y<0 || grid[x][y]=='B') return false;
    else return true;
}

std::vector<std::vector<int>> bfs(int n,int m,std::vector<std::vector<char>> &grid, int sx,int sy,int tx,int ty){
    int dx[4] = {1,0,-1,0};
    int dy[4] = {0,1,0,-1};
    std::queue<std::pair<int,int>>queue_of_grid;
    std::vector<std::vector<bool>>visited;
    std::vector<std::vector<int>>distance;
    for(int i=0;i<n;i++){
        std::vector<bool>temp;
        std::vector<int>dist_temp;
        for(int j=0;j<m;j++){
            temp.push_back(false);
            dist_temp.push_back(0);
        }
        visited.push_back(temp);
        distance.push_back(dist_temp);
    }
    queue_of_grid.push(std::make_pair(sx,sy));
    visited[sx][sy] = true;
    distance[sx][sy] = 0;
    bool found = false;
    while(queue_of_grid.size() > 0){
        if (queue_of_grid.front().first==tx && queue_of_grid.front().second==ty){
            found = true;
            break;
        }
        int curr_x = queue_of_grid.front().first;
        int curr_y = queue_of_grid.front().second;
        queue_of_grid.pop();
        for(int i=0;i<4;i++){
            if(check_valid(n,m,curr_x+dx[i],curr_y+dy[i],grid) && !visited[curr_x+dx[i]][curr_y+dy[i]]){
                queue_of_grid.push(std::make_pair(curr_x+dx[i],curr_y+dy[i]));
                visited[curr_x+dx[i]][curr_y+dy[i]] = true;
                distance[curr_x+dx[i]][curr_y+dy[i]] = distance[curr_x][curr_y]+1;

            }
        }
    }
    if(!found)
        distance.clear();
    return distance;
}

int main(){
    int t;
    std::cin>>t;
    while(t--){
        int n,m,b;
        bool exit = false;
        std::cin>>n>>m;
        std::cin>>b;
        std::vector<std::vector<char>> grid;
        for(int i=0;i<n;i++){
            std::vector<char>temp;
            for(int j=0;j<m;j++){
                temp.push_back('U');
            }
            grid.push_back(temp);
        }
        // updating blocked nodes
        for(int i=0;i<b;i++){
            int x,y;
            std::cin>>x>>y;
            grid[x][y] = 'B';
        }
        // further queries handled (Q,E and C)
        std::cout<<"User queries: \n1) A x y where A determines add blockage and x,y are the coordinates of the block. \n2) C x y where C determines clear blockage and x,y are the coordinates of the block that will be removed.\n3) Q x y a b will return the shortest distance from x,y to a,b."<<"\n";
        char input;
        std::cin>>input;
        while(input!='E' && exit == false){
            if(input == 'Q'){
                int sx,sy,tx,ty;
                std::cin>>sx>>sy>>tx>>ty;
                std::vector<std::vector<int>> distance = bfs(n,m,grid,sx,sy,tx,ty);
                if(distance.size()==0)
                    std::cout<<"No path found from ("<<sx<<","<<sy<<") to ("<<tx<<","<<ty<<")"<<"\n";
                else
                    std::cout<<"Shortest Distance from ("<<sx<<","<<sy<<") to ("<<tx<<","<<ty<<")"<<" is : "<<distance[tx][ty]<<"\n";

                std::cin>>input;
            }
            else if(input == 'A'){
                int x,y;
                std::cin>>x>>y;
                grid[x][y]='B';
                std::cin>>input;
            }
            else if(input == 'C'){
                int x,y;
                std::cin>>x>>y;
                grid[x][y]='U';
                std::cin>>input;
            }
            else{
                exit = true;
                break;
            }
        }
    }
}
