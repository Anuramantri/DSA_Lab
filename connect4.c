/* Implement connect 4 on a 5 (columns) x 4 (rows) board. */
/* Board:
        0   1   2   3   4
    0
    1
    2
    3                       */
#include <stdio.h>
#include <assert.h>

enum
{
    EMPTY = 0,
    RED,
    BLUE,
};

typedef char board_t[4][5];
typedef char player_t;

void init_board(board_t board)
{
    for (int row = 0; row < 4; ++row)
    {
        for (int col = 0; col < 5; ++col)
        {
            board[row][col] = EMPTY;
        }
    }
}

int has_won(board_t board, player_t player)
{
    for (int c = 0; c < 5; c++)
    {
        for (int r = 0; r < 4; r++)
        {
            if (board[r][c] != player)
                goto next_column;
        }
        return 1;
    next_column:;
    }

    for (int r = 0; r < 4; r++)
    {
        for (int c = 0; c < 2; c++)
        {
            if (board[r][c] == player && board[r][c + 1] == player &&
                board[r][c + 2] == player && board[r][c + 3] == player)
                return 1; // Found a winning row
        }
    }

    if (board[3][0] == player && board[2][1] == player && board[1][2] == player && board[0][3] == player)
        return 1;
    if (board[3][1] == player && board[2][2] == player && board[1][3] == player && board[0][4] == player)
        return 1;
    if (board[3][4] == player && board[2][3] == player && board[1][2] == player && board[0][1] == player)
        return 1;
    if (board[3][3] == player && board[2][2] == player && board[1][1] == player && board[0][0] == player)
        return 1;


    return 0;
}

int is_full(board_t board)
{
    for (int r = 0; r < 4; r++)
    {
        for (int c = 0; c < 5; c++)
        {
            if (board[r][c] == EMPTY)
                return 0;
        }
    }
    return 1;
}

typedef struct
{
    int col;

    int score;
} move_t;



int gravity(board_t board, player_t player,int col){
    for(int r=3;r>=0;r--){
        if(board[r][col]==EMPTY)
            return r;
    }
    return -1;
}

void print_board(board_t board)
{
    for (int row = 0; row < 4; ++row)
    {
        for (int col = 0; col < 5; ++col)
        {
            printf("%d ", board[row][col]);
        }
        printf("\n");
    }
    printf("\n");
}


move_t best_move(board_t board, player_t player)
{   
    move_t response;
    move_t candidate;
    int no_candidate = 1;

    assert(!is_full(board));
    assert(!has_won(board, player));
    assert(!has_won(board, 3-player));

   
    for (int c = 0; c < 5; ++c)
    {          int r=gravity(board,player,c);
               if(r!=-1){
                board[r][c]=player;
                if (has_won(board, player))
                {   
                    board[r][c] = EMPTY;
                    candidate = (move_t){.col = c,  .score = 1};
                    
                    return candidate;
                }board[r][c] = EMPTY;}
                
            }
        
        for (int c = 0; c < 5; ++c)
        {
            int r=gravity(board,player,c);
            if(r!=-1){
                board[r][c] = player;
                if (is_full(board))
                {
                    board[r][c] = EMPTY;
                    candidate = (move_t){.col = c, .score = 0};
                    
                    return candidate;
                }
                response = best_move(board, 3-player);
                board[r][c] = EMPTY;
                if (response.score == -1)
                {
                    candidate = (move_t){.col = c, .score = 1};
                    
                    return candidate;
                }
                else if (response.score == 0)
                {
                    candidate = (move_t){.col = c, .score = 0};
                    no_candidate = 0;
                }
                else
                {
                    if (no_candidate==1)
                    {
                        candidate = (move_t){.col = c, .score = -1};
                        no_candidate = 0;
                    }
                }
            }
        }
    
    return candidate;
}

int is_empty(board_t board){
    for(int r=0;r<4;r++){
        for(int c=0;c<5;c++){
            if(board[r][c]!=0)
            return 0;
        }
    }
    return 1;
}

int main()
{
    board_t board;//={{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,2,0,0}};
    init_board(board);
    printf("Choose red(1) or blue(2): ");
    int c;
    scanf("%d",&c);
    player_t player;
    if(c==1)
        player = RED;
    else if(c==2)
        player = BLUE;
    else
        printf("Invalid choice");
    move_t response;
    int col;
    player_t current=RED;
    
    while (1)
    {   print_board(board);
        if (current == player)
        {
            printf("Enter column(0-4): ");
            scanf("%d", &col);
            int r=gravity(board,current,col);
            if(r==-1)
            printf("Column is full");
            else
            board[r][col]=current;
            
        }
        else
        {   if(is_empty(board))
                board[3][2]=current;
            else{
            response = best_move(board, current);
            int r=gravity(board,current,response.col);
            if(r!=-1)
            board[r][response.col] = current;}
        }
        if (has_won(board, current))
        {
            print_board(board);
            printf("\n%d is the winner", current);
            break;
        }
        else if (is_full(board))
        {
            printf("Draw\n");
            print_board(board);
            break;
        }
        current = 3-current;
    }
    /* Your game play logic. */
    /* The user should have the option to select red or blue player. */
    return 0;
}
