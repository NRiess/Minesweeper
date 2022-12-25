#include <iostream>
#include <string>

#include "Board.cpp"

using namespace std;


int main(){
    int width, height, number_of_bombs;
    bool lost, won = false;

    /*
    cout<<"Please type in the height and the width of the boared."<<endl;
    cin>>height;
    cin>>width;
    cin>>number_of_bombs;
*/
    width = 5;
    height = 5;
    number_of_bombs = 10;

    vector<vector<bool>> bombs(height, vector<bool>(width,false));
    vector<vector<bool>> visited(height, vector<bool>(width,false));
    vector<vector<int>> numbers(height, vector<int>(width,0));
    vector<int> coordinates;
    
    Board b(height, width, number_of_bombs);
    
    bombs = b.lay_bombs(bombs);
    numbers = b.initialize_numbers(bombs, numbers);
    b.draw_board(visited, numbers, bombs);

    while(!lost && !won){
        coordinates = b.set_coordinates();
        lost = b.process_input(&visited, numbers, bombs, coordinates);
        b.draw_board(visited, numbers, bombs);
        won = b.check_if_won(visited, bombs);
    }
    if(lost){
        cout<<"You lost!"<<endl;
    }
    if(won){
        cout<<"You won!"<<endl;
    }

    cout<<"Done!"<<endl;

    




    return 0;
}