/* A BFS solution to Martin Gardner's Up it Up (https://www.youtube.com/watch?v=N_GbBjvU068&t=1s)*/

#include <cstdio>
#include <vector>
#include <array>
#include <algorithm>
#include <tuple>
#include "queue.hpp"

struct board {
    int e[3][3];
};

enum move { L = 1, R = 2, U = 3, D = 4 };

int ord(const board& b)
{   
    int p = 1;
    int i = 0;
    int d;
    
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            d=b.e[row][col];
            i += d * p;
            p *= 7;
        }
    }
    return i;
    }


void print_board(const board& b)
{
    for (int r = 0; r < 3; ++r) {
        for (int c = 0; c < 3; ++c) {
            printf("%d ", b.e[r][c]);
        }
        printf("\n");
    }
    printf("\n");
}


std::tuple<int, int> find_space(const board& b)
{
    for (int r = 0; r < 3; ++r)
        {for (int c = 0; c < 3; ++c)
            {if (b.e[r][c] == 0) 
            return { r, c };
            }}
        assert(0);
}

int turn_side(int side, int turn) {
    
    switch (turn) {
        case U:
            switch (side) {
                case 1: side = 3; break;
                case 2: side = 5; break;
                case 3: side = 2; break;
                case 4: side = 3; break;
                case 5: side = 1; break;
                case 6: side = 3; break;
            }
            break;  
        case D:
            
            switch (side) {
                case 1: side = 5; break;
                case 2: side = 3; break;
                case 3: side = 1; break;
                case 4: side = 5; break;
                case 5: side = 2; break;
                case 6: side = 5; break;
            }
            break;
        case R:
            
            switch (side) {
                case 1: side = 4; break;
                case 2: side = 6; break;
                case 3: side = 4; break;
                case 4: side = 2; break;
                case 5: side = 4; break;
                case 6: side = 1; break;
            }
            break;
        case L:
        
            switch (side) {
                case 1: side = 6; break;
                case 2: side = 4; break;
                case 3: side = 6; break;
                case 4: side = 1; break;
                case 5: side = 6; break;
                case 6: side = 2; break;
                
            }
            break;
    }
    return side;
}

board up(const board& b)
{   int r, c;
    std::tie(r, c) = find_space(b);
    if (r == 0) return b;
    board o = b;
    int side= turn_side(o.e[r-1][c],U);
    o.e[r-1][c]=0;
    o.e[r][c]=side;
    return o;
}

board down(const board& b)
{
int r, c;
    std::tie(r, c) = find_space(b);    if (r == 2) return b;
    board o = b;
    int side= turn_side(o.e[r+1][c],D);
    o.e[r+1][c]=0;
    o.e[r][c]=side;
    return o;
}

board left(const board& b)
{
int r, c;
    std::tie(r, c) = find_space(b);    if (c == 0) return b;
    board o = b;
    int side= turn_side(o.e[r][c-1],L);
    o.e[r][c-1]=0;
    o.e[r][c]=side;
    return o;
}

board right(const board& b)
{
int r, c;
    std::tie(r, c) = find_space(b);    if (c == 2) return b;
    board o = b;
    int side= turn_side(o.e[r][c+1],R);
    o.e[r][c+1]=0;
    o.e[r][c]=side;
    return o;
}

bool is_same(const board& a, const board &b)
{
    for (int r = 0; r < 3; ++r)
        for (int c = 0; c < 3; ++c)
            if (a.e[r][c] != b.e[r][c]) return false;

    return true;
}

#define SIZE 40353607

std::vector<int> solve(const board& src, const board& dest)
{   
    Queue <board, SIZE> q = createQueue<board, SIZE>();
    std::vector<board> parent;
    parent.reserve(SIZE);

    std::vector<int> visited;
    visited.reserve(SIZE);
    
    q.enqueue(src);
    visited[ord(src)] = 5;
    
    while (!q.isEmpty()) {
        board u = q.dequeue();
        if (is_same(u, dest)) {
            
            std::vector<int> moves;
            board c = u;
            int o = ord(c);
            while (!is_same(c, src)) {
                moves.push_back(visited[o]);
                c = parent[o];
                o = ord(c);
            }
            std::reverse(moves.begin(), moves.end());
            return moves;
        }

        board a = up(u);
        board b = down(u);
        board c = left(u);
        board d = right(u);

        int aord = ord(a);
        int bord = ord(b);
        int cord = ord(c);
        int dord = ord(d);

        if (!visited[aord]) {
            visited[aord] = U;
            parent[aord] = u;
            q.enqueue(a);
        }
        if (!visited[bord]) {
            visited[bord] = D;
            parent[bord] = u;
            q.enqueue(b);
        }
        if (!visited[cord]) {
            visited[cord] = L;
            parent[cord] = u;
            q.enqueue(c);
        }
        if (!visited[dord]) {
            visited[dord] = R;
            parent[dord] = u;
            q.enqueue(d);
        }
    }
    printf("Unsolvable board");
    std::vector<int> moves;
    return moves;
}

void print_moves(const std::vector<int>& moves)
{
    for (auto m: moves) {
        switch (m) {
        case L: printf("L "); break;
        case R: printf("R "); break;
        case U: printf("U "); break;
        case D: printf("D "); break;
        default: printf("N"); break;
        }
    }
    printf("\n");
}

int main()
{   printf("Enter your board: \n");
    // START SIDE = 1, EMPTY SPACE = 0, DESTINATION SIDE = 2 ;
    board src;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            scanf("%d",&src.e[i][j]);     
        }
    }
    print_board(src);
    board dst = {{
        {2, 2, 2},
        {2, 0, 2},
        {2, 2, 2}
    }};

    auto moves = solve(src, dst);
    printf("The moves are: ");
    print_moves(moves);

    return 0;
}
