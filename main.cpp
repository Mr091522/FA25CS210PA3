//
// Created by Manju Muralidharan on 11/22/25.
//

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

// Directions for DFS (students must use these)
int dr[4] = {-1, 0, 1, 0};
int dc[4] = {0, 1, 0, -1};

// ----------------------------------------------------------
// DO NOT MODIFY: Maze generation
// ----------------------------------------------------------
void generateMaze(vector<vector<int>>& maze, int N, int M) {
    srand(time(0));

    for (int r = 0; r < N; r++) {
        for (int c = 0; c < M; c++) {
            int roll = rand() % 100;
            maze[r][c] = (roll < 70) ? 0 : 1;   // 0 = open, 1 = wall
        }
    }
}

// ----------------------------------------------------------
// DO NOT MODIFY: Choose a random boundary cell that is open
// ----------------------------------------------------------
pair<int,int> chooseBoundaryCell(const vector<vector<int>>& maze) {
    int N = maze.size();
    int M = maze[0].size();

    while (true) {
        int side = rand() % 4;
        int r, c;

        if (side == 0) {          // top row
            r = 0;
            c = rand() % M;
        } else if (side == 1) {   // bottom row
            r = N - 1;
            c = rand() % M;
        } else if (side == 2) {   // left column
            r = rand() % N;
            c = 0;
        } else {                  // right column
            r = rand() % N;
            c = M - 1;
        }

        if (maze[r][c] == 0) {
            return {r, c};
        }
    }
}

// ----------------------------------------------------------
// DO NOT MODIFY: Print the maze with S and E markers
// ----------------------------------------------------------
void printMaze(const vector<vector<int>>& maze,
               int ent_r, int ent_c,
               int exit_r, int exit_c)
{
    int N = maze.size();
    int M = maze[0].size();

    cout << "\nMaze:\n";
    for (int r = 0; r < N; r++) {
        for (int c = 0; c < M; c++) {
            if (r == ent_r && c == ent_c) {
                cout << "S ";
            } else if (r == exit_r && c == exit_c) {
                cout << "E ";
            } else {
                cout << maze[r][c] << " ";
            }
        }
        cout << "\n";
    }
}

// ----------------------------------------------------------
// DO NOT MODIFY: Print the reconstructed path
// Students must fill parent[][] correctly during DFS
// ----------------------------------------------------------
void printPath(pair<int,int> exitcell,
               const vector<vector<int>>& parent_r,
               const vector<vector<int>>& parent_c,
               int ent_r, int ent_c)
{
    int r = exitcell.first;
    int c = exitcell.second;

    vector<pair<int,int>> path;

    // Walk backward from exit to entrance
    while (!(r == ent_r && c == ent_c)) {
        path.push_back({r, c});
        int pr = parent_r[r][c];
        int pc = parent_c[r][c];
        r = pr;
        c = pc;
    }
    path.push_back({ent_r, ent_c});

    cout << "\nPath from entrance to exit:\n";
    for (int i = path.size() - 1; i >= 0; i--) {
        cout << "(" << path[i].first << ", " << path[i].second << ")\n";
    }
}

// ----------------------------------------------------------
// STUDENTS IMPLEMENT DFS HERE
// Add arguments, return type, and logic
// ----------------------------------------------------------
  bool dfs(int r, int c, //added
      const vector<vector<int>>& maze, //added
      vector<vector<bool>>& visited, //added
      vector<vector<int>>& parent_r, //added
      vector<vector<int>>& parent_c, //added
      int exit_r, int exit_c) //added
{
    //this will help with the maze and its dimensions and boundaries
    int N = maze.size(); // This is the rows
    int M = maze[0].size(); // This is the colums

    if (r < 0 || r >= N || c < 0 || c >= M) {
        return false ;
    }
    if (maze[r][c] == 1) {
        return false ;
    }
    // Your code here... this code will check the bounds if the r or c fall out of range then it will say so
    if (visited [r][c]) {
        return false ;
    }
        // this will now check the wall now if the wall is (1) it will not move into
        visited [r][c] = true;
        // This will see what has already been visited, it will check as stated before to stop and avoid infinite loops
        if (r == exit_r && c == exit_c) {
            //this will make sure it is marked as visited this will help so it wont be revisted

            return true;
        }
        //This will check if everything worked properly and check if we exit the maze
        if (r == exit_r && c == exit_c) {
            return true;
        }
        //This piece of code will go thorugh 4 neighboring directions usigng dr dc will make sure movment is right
        // 0: Up, 1:right, 2:down 3: left
        for (int k = 0; k < 4; k++) {
            int nr = r + dr[k]; // this is row
            int nc = c + dc[k];// this is colloum

            if (nr < 0 || nr >= N || nc < 0 || nc >= M) {
                continue;
            }
            //this is the neighbor wall
            if (maze[nr][nc] == 1) {
                continue;
            }
            //neighbor visit
            if (visited[nr][nc]) {
                continue;
            }

            //this will make sure the parent is noticed so thatit can reconsutrct the paths later
            parent_r[nr][nc] = r;
            parent_c[nr][nc] = c;

            //It will add an recursive call if right it will show
            if (dfs(nr, nc, maze, visited, parent_r, parent_c, exit_r, exit_c)) {
                return true;
            }
        }
        // If all four directions fail then it will retun to the backtrack
        return false;

    }


    // ----------------------------------------------------------
    // MAIN PROGRAM (students add DFS calls and logic)
    // ----------------------------------------------------------
    int main() {
        int N, M;

        cout << "Enter maze dimensions N M: ";
        cin >> N >> M;

        vector<vector<int>> maze(N, vector<int>(M));
        generateMaze(maze, N, M);

        // Pick entrance and exit
        pair<int,int> entrance = chooseBoundaryCell(maze);
        pair<int,int> exitcell = chooseBoundaryCell(maze);

        while (exitcell == entrance) {
            exitcell = chooseBoundaryCell(maze);
        }

        int ent_r = entrance.first;
        int ent_c = entrance.second;
        int exit_r = exitcell.first;
        int exit_c = exitcell.second;

        // Display the maze
        printMaze(maze, ent_r, ent_c, exit_r, exit_c);

        // Students must use these
        vector<vector<bool>> visited(N, vector<bool>(M, false));
        vector<vector<int>> parent_r(N, vector<int>(M, -1));
        vector<vector<int>> parent_c(N, vector<int>(M, -1));

        // ------------------------------------------------------
        // STUDENT WORK:
        // Call your DFS, track visited, and fill parent_r and parent_c
        // ------------------------------------------------------
        // wokr on this
        parent_r[ent_r][ent_c] = ent_r;
        parent_c[ent_r][ent_c] = ent_c;

        //will run the dfs from the start
        //the dfs will explre and fill visted [][]
        // will fill the parents of c and r see for valid steps

        bool found = dfs(ent_r, ent_c, maze, visited, parent_r, parent_c, exit_r, exit_c);

        // ------------------------------------------------------
        // STUDENT WORK:
        // If found, print the path
        // ------------------------------------------------------
        if (found) {
            printPath(exitcell, parent_r, parent_c, ent_r, ent_c);
        } else {
            cout << "\nNo path exists.\n";
        }

        return 0;
    }