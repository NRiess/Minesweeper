#include "Board.hpp"
#include <iostream>
using namespace std;

Board::Board(int h, int w, int num_of_bombs){
    width = w;
    height = h;
    number_of_bombs = num_of_bombs;
}

vector<vector<bool>> Board::lay_bombs(vector<vector<bool>> bombs){
    
    int count_bombs = 0; 
    while(count_bombs<number_of_bombs){
        int y_bomb = rand() % height;
        int x_bomb = rand() % width;
        if(bombs[y_bomb][x_bomb]==false){
            bombs[y_bomb][x_bomb]=true;
            count_bombs++;
        } 
    }
    return bombs;
}

vector<vector<int>> Board::initialize_numbers(vector<vector<bool>> bombs, vector<vector<int>> numbers){
    for(int x=0;x<width;x++){
        for(int y=0;y<height;y++){
            if(!bombs[y][x]){
                for(int x_diff=-1;x_diff<=1;x_diff++){
                    for(int y_diff=-1;y_diff<=1;y_diff++){
                        int pos_x = x+x_diff;
                        int pos_y = y+y_diff;
                        if(pos_x>=0 && pos_x<width && pos_y>=0 && pos_y<height && bombs[pos_y][pos_x] && !(x==pos_x && y==pos_y)){
                            numbers[y][x]++;
                        }
                    }
                }
            }
        }
    }
    return numbers;
}

void Board::draw_board(vector<vector<bool>> visited, vector<vector<int>> numbers, vector<vector<bool>> bombs){
    cout<<"  ";
    for(int i=0;i<width;i++){
        cout<<" ";
    }
    cout<<"x";
    for(int i=0;i<width;i++){
        cout<<" ";
    }
    cout<<"\n   ";
    for(int i=0;i<width;i++){
        cout<<i<<" ";
    }
    cout<<"\n";
    cout<<"   ";
    for(int i=0;i<2*width-1;i++){
        cout<<"-";
    }

    for(int h=0;h<height;h++){
        if (h==height/2){
            cout<<"\ny"<<h<<"|";
        }
        else{
            cout<<"\n "<<h<<"|";
        }
        for(int w=0;w<width;w++){
            if (visited[h][w]){
                if(!bombs[h][w]){
                    cout<<numbers[h][w];
                }
                else{
                    cout<<"x";
                }
                if(w<width-1){
                    cout<<" ";
                }
            }
            else{
                cout<<" "<<" ";
            }
        }
        cout<<"|";
        
    }
    cout<<"\n   ";
    for(int i=0;i<2*width-1;i++){
        cout<<"-";
    }
    cout<<"\n ";
}


vector<int> Board::set_coordinates(){
    cout<<"Please type in the y coordinate: ";
    cin>>c1;
    cout<<"\nPlease type in the x coordinate: ";
    cin>>c2;
    cout<<"\n";
    vector<int> coordinates={c1,c2};
    return coordinates;
}

bool Board::process_input(vector<vector<bool>>* visited, vector<vector<int>> numbers, vector<vector<bool>> bombs, vector<int> coordinates){
    int c1 = coordinates[0];
    int c2 = coordinates[1];
    (*visited).at(c1).at(c2)=true;
    if(bombs[c1][c2]){
        for (int h=0;h<height;h++){
            for (int w=0;w<width;w++){
                if(bombs[h][w]){
                    (*visited).at(h).at(w)=true;
                }
                
            }
        }
        return true;
    }
    if(numbers[c1][c2]==0){
        find_connected_zeros(numbers, &visited, c1, c2); //*visited
    }
    return false;
}




void Board::find_connected_zeros(vector<vector<int>>& numbers, vector<vector<bool>>** visited, int c1, int c2){   //vector<vector<bool>> visited

    //visited current location
    (**visited).at(c1).at(c2) = true;
    //define vector of all directions 
    vector<pair<int, int>> shifts = {{-1,-1}, {-1, 0}, {-1, 1}, 
                                     { 0,-1},          { 0, 1},
                                     { 1,-1}, { 1, 0}, { 1, 1}};
    //shift current position by all directions
    for(int i=0; i<shifts.size();i++){
        int pos_y = c1+shifts[i].first;
        int pos_x = c2+shifts[i].second;
        // check if position is valid, criterium for search is fullfilled and location was not visited so far
        if(pos_y>=0 && pos_x>=0 && pos_y<height && pos_x<width && numbers[pos_y][pos_x]==0 && !(**visited).at(pos_y).at(pos_x)){
            find_connected_zeros(numbers, visited, pos_y, pos_x);
        }
    }

}

bool Board::check_if_won(vector<vector<bool>> visited, vector<vector<bool>>bombs){
    for(int h=0;h<height;h++){
        for(int w=0;w<width;w++){
            if(visited[h][w]!=bombs[h][w]){
                continue;
            }
            else{
                return false;
            }
        }
    }
    return true;
}
