#include <vector>
using namespace std;

class Board{
    private:
        int width, height, c1, c2, number_of_bombs;    

    public:
        Board(int height, int width, int number_of_bombs);
        
        vector<vector<bool>> lay_bombs(vector<vector<bool>> bombs);

        vector<vector<int>> initialize_numbers(vector<vector<bool>> bombs, vector<vector<int>> numbers);
        
        void draw_board(vector<vector<bool>> visited, vector<vector<int>> numbers, vector<vector<bool>> bombs);


        vector<int> set_coordinates();

        bool process_input(vector<vector<bool>>* visited, vector<vector<int>> numbers, vector<vector<bool>> bombs, vector<int> coordinates);

        void find_connected_zeros(vector<vector<int>>& numbers, vector<vector<bool>>** visited, int c1, int c2);

        bool check_if_won(vector<vector<bool>> visited, vector<vector<bool>>bombs);

        



};

