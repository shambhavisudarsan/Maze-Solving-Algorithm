#include <bits/stdc++.h>

std::vector<std::vector<int>> initializeVectorOfVectors(int n,int m,int val){
    std::vector<std::vector<int>>vector_of_vectors;
    for(int i=0;i<=n;i++){
        std::vector<int>temp;
        for(int j=0;j<=m;j++){
            temp.push_back(val);
        }
        vector_of_vectors.push_back(temp);
    }
    return vector_of_vectors;
}
bool horizontalBreaking(std::string direction, int i,int j ,int n,int m, std::vector<std::vector<char>> &grid){
    if(direction == "->"){
        if(i+1<=n && j-1>=0){
            if (grid[i+1][j-1] == 'B' && grid[i+1][j] == 'U' && grid[i][j-1] == 'U') return true;
        }
        if(i-1>=1 && j-1>=0){
            if(grid[i-1][j-1] == 'B' && grid[i][j-1] == 'U' && grid[i-1][j] == 'U') return true;
        }
        if(j-1 == m) return true;
        else return false;
    }
    else if(direction == "<-"){
        if(i+1<=n && j+1<=m+1){
            if (grid[i+1][j+1] == 'B' && grid[i+1][j] == 'U' && grid[i][j+1] == 'U') return true;
        }
        if(i-1>=1 && j+1<=m+1){
            if(grid[i-1][j+1] == 'B' && grid[i][j+1] == 'U' && grid[i-1][j] == 'U')  return true;
        }
        if(j == 0) return true;
        else return false;
    }
    else return false;
}
int tableLookup(int p,int ny,int i,int n,int m,std::string direction, std::vector<std::vector<int>>satellite_horizontal, std::vector<std::vector<int>>successor_horizontal, std::vector<std::vector<char>>grid){
    if(successor_horizontal[i][p] != -1){
        if(direction == "->" && satellite_horizontal[i][successor_horizontal[i][p]] <= p){
            return successor_horizontal[i][p];
        }
        if(direction == "<-" && satellite_horizontal[i][successor_horizontal[i][p]] >= p){
            return successor_horizontal[i][p];
        }
    }
    successor_horizontal[i][p] = ny;
    if(ny>=1 && ny<=m){
        if(horizontalBreaking(direction,i,ny,n,m,grid)){
            return ny;
        }
        else if(direction == "->" && ((ny-1>=1 && grid[i][ny] == 'B' && grid[i][ny-1] == 'U') || (ny == 0 && grid[i][ny] == 'B'))){
            return ny;
        }
        else if(direction == "<-" && ((ny+1<=m && grid[i][ny] == 'B' && grid[i][ny+1] == 'U') || (ny == m && grid[i][ny] == 'B'))){
            return ny;
        }
        if(direction == "->"){
            successor_horizontal[i][p] = tableLookup(ny,ny+1,i,n,m,direction,satellite_horizontal,successor_horizontal,grid);
        }
        else{
            successor_horizontal[i][p] = tableLookup(ny,ny-1,i,n,m,direction,satellite_horizontal,successor_horizontal,grid);
        }
    }
    return successor_horizontal[i][p];
}

std::vector<std::vector<int>> satelliteTable(std::string direction,int n,int m,std::vector<std::vector<char>> &grid){
    std::vector<std::vector<int>>satellite_table = initializeVectorOfVectors(n,m+2,-1);
    int previous_breaking_node = 1;
    if(direction == "->"){
        for(int i=1;i<=n;i++){
            previous_breaking_node = 1;
            for(int j=1;j<=m+1;j++){
                if(horizontalBreaking("->",i,j,n,m,grid)){
                    satellite_table[i][j] = previous_breaking_node;
                    previous_breaking_node = j;
                }
                else if(grid[i][j] == 'B' && grid[i][j-1] == 'U'){
                    satellite_table[i][j] = previous_breaking_node;
                }
                else if(grid[i][j] == 'U' && grid[i][j-1] == 'B'){
                    previous_breaking_node = j;
                }
            }
        }
    }
    else if(direction == "<-"){
        for(int i=1;i<=n;i++){
            previous_breaking_node = m;
            for(int j=m;j>=0;j--){
                if(horizontalBreaking("<-",i,j,n,m,grid)){
                    satellite_table[i][j] = previous_breaking_node;
                    previous_breaking_node = j;
                }
                else if(grid[i][j] == 'B' && grid[i][j+1] == 'U'){
                    satellite_table[i][j] = previous_breaking_node;
                }
                else if(grid[i][j] == 'U' && grid[i][j+1] == 'B'){
                    previous_breaking_node = j;
                }
            }
        }
    }
    return satellite_table;
}

int main(){
    int t,n,m,x,y,b;

    /* Number of Test Cases */
    std::cin>>t;

    /* For each test case, input n and m */
    while(t--){
        std::cin>>n>>m;

        /* Grid Initialization with U*/
        std::vector<std::vector<char>>grid;

        for(int i=0;i<=n;i++){
            std::vector<char>temp;
            for(int j=0;j<=m;j++){
                temp.push_back('U');
            }
            grid.push_back(temp);
        }

        /* Number of blockages */
        std::cin>>b;

        /* Blockages */
        for(int i=0;i<b;i++){
            std::cin>>x>>y;
            grid[x][y] = 'B';
        }

        /* Initializing satellite vector*/
        std::vector<std::vector<int>>satellite_horizontal_right = satelliteTable("->",n,m,grid);
        std::vector<std::vector<int>>satellite_horizontal_left = satelliteTable("<-",n,m,grid);
        std::vector<std::vector<int>>successor_horizontal_right = initializeVectorOfVectors(n,m,-1);
        std::vector<std::vector<int>>successor_horizontal_left = initializeVectorOfVectors(n,m,-1);

        for(int i=1;i<=n;i++){
            for(int j=0;j<=m;j++){
                std::cout<<satellite_horizontal_left[i][j]<<" ";
            }
            std::cout<<'\n';
        }
        std::cout<<'\n';
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m+1;j++){
                std::cout<<satellite_horizontal_right[i][j]<<" ";
            }
            std::cout<<'\n';
        }


        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                successor_horizontal_right[i][j] = tableLookup(j,j+1,i,n,m,"->",satellite_horizontal_right,successor_horizontal_right,grid);
            }
        }
        for(int i=1;i<=n;i++){
            for(int j=m;j>=1;j--){
                successor_horizontal_left[i][j] = tableLookup(j,j-1,i,n,m,"<-",satellite_horizontal_left,successor_horizontal_left,grid);
            }
        }

        std::cout<<'\n';
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                std::cout<<successor_horizontal_right[i][j]<<" ";
            }
            std::cout<<'\n';
        }
        std::cout<<'\n';
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                std::cout<<successor_horizontal_left[i][j]<<" ";
            }
            std::cout<<'\n';
        }

        // std::cout<<tableLookup(1,2,1,3,n,m,"->",satellite_horizontal_right,successor_horizontal_right,grid);
    }
}