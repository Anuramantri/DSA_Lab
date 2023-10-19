#include <stdio.h>
// #include <assert.h>

//     NO = 0, /* No line */
//     RED = 1,
//     BLUE = 2
/*
 * The board records the colors of the lines.
 * board[0] = color of 12
 * board[1] = color of 13
 * ...
 * board[14] = color of 56
 */
typedef char board_t[15];
 
void print_board(board_t board) {
    for (int i = 0; i < 15; i++) {
        printf("%d ", board[i]);
    }
    printf("\n"); // Print a final newline for formatting
}
int sum_board(board_t board){
  int sum=0;
  for(int i=0;i<15;i++){
    sum+=board[i];
  }
  return sum;
}
int has_lost(board_t board, int player)
{
    int lost[20][3] = {{12,14,13}, {12,3,2}, {12,7,6}, {9,13,11}, {9,2,1}, {14,4,3}, {14,8,7}, {14,11,10}, {6,13,8}, {5,10,7}, {9,12,10}, {3,10,1}, {4,1,11}, {4,13,2}, {5,11,8}, {0,5,1}, {0,6,2}, {0,7,3}, {0,8,4}, {5,6,9}};
    
   
    for (int i = 0; i < 20; i++) {
        int j;
        for (j = 0; j < 3; j++) {
            if ( board[lost[i][j]] != player) {
              break;

            }
    
        }
        if (j == 3) {
          return 1; //  return 1 to indicate a valid move
        }
    }
 
    return 0;
}

int is_full(board_t board)
{   int sum=0;
    for (int i=0;i<15;i++){
        sum+=board[i];
    }
    if (sum==21){
        return 1;
    }
    return 0;
}

typedef struct {
    int player;
    int line; /* 0 for 12, 1 for 13, ..., 14 for 56. */
    int score; /* -1 for loss, 0 for draw, 1 for win. */
} move_t;

move_t best_move(board_t board, int player)
{ 
    move_t candidate;
    move_t response;
    candidate.player=player;
    candidate.score=-1;

    // ########## check if the sum of board is 21 meaning the last move is left so the t last player will definetly lose so directly return that player lost 
     if(sum_board(board)==21){
            candidate.score=3-player;
       return candidate;
     }
    for (int i=0;i<15;i++){


    // ########################### checking empty position on board and add the marker of the player
        if (board[i]==0){
            candidate.line=i;
            board[candidate.line]=player;
    //  ##################### checking if the current player has host if made that move
            if (has_lost(board,player)){
// ##### if lost clear that move n try another;
                board[i]=0;
             continue;
            }


            // #### checking the best move of another player and simulating it
            response=best_move(board,3-player);
            board[candidate.line]=0;
// ################ checking if player 2 lost it or not ir yes the then the current player has its best move other wise change the move;
            if (response.player!=response.score){
                candidate.score=player;
                board[candidate.line]=0;
             return candidate;
            }
          }
        }

        // ##### this says that current player has no other possible postion availbe to make without losing 
        candidate.score=3-player;
        board[candidate.line]=0;
        return candidate;
    


    }




int main()
{
            // 1  2  3  4  5  6  7  8   9  10  11  12  13  14  15
  board_t b = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0,  0,  0,  0,  0};
  int human; 
//  ##################################################/#
  printf("please enter your chosen colour(1 for RED and 2 for BLUE)\n ");
  scanf("%d", &human );

  int computer = 3-human;
  int move_human; 
  if (human==1){
    while(!is_full(b) && !has_lost(b, human) && !has_lost(b, computer)){
    printf("please enter your move\n");
    scanf("%d", &move_human);
    if (b[move_human-1]!=0){
        printf("enter valid move\n");
        continue;
    }
    b[move_human-1]= human;

    printf("current board condition\n");
    print_board(b);
    printf("computers move\n");
    b[(best_move(b, computer)).line] = computer;

    printf("current board condition\n");
    print_board(b);


    }
  }

if (human==2){
    int temp1;
    while(!is_full(b) && !has_lost(b, human) && !has_lost(b, computer)){
    printf("computers move\n");
    temp1=(best_move(b, computer)).line;
    b[temp1] = computer;
    
    printf("\n");
    printf("please enter your move\n");
    scanf("%d", &move_human);
    if (b[move_human-1]!=0){
        printf("enter valid move\n");
        b[temp1]=0;
        continue;
    }
    b[move_human-1]= human;

    printf("current board condition\n");
    print_board(b);
    }
}

if (has_lost(b,human)){
  printf("Your lose, try again\n");
}
else{
printf(" Congratulations! You won!\n");

}

  return 0;
}
