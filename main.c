#include <stdio.h>
#define BSIZE 3
#define P1_C 'O'
#define P2_C 'X'
#define RED "\x1B[31m"
#define BLU "\x1B[34m"
#define RESET "\x1B[0m"

int print_board(char board[4][4]);
int change_board(int num, char icon, char board[4][4]);
int check_board(char board[4][4]);
int check_winner(char now[3]);

int main() {
  char board[BSIZE + 1][BSIZE + 1] = {{'0', '0', '0', '0'},
                                      {'0', '1', '2', '3'},
                                      {'0', '4', '5', '6'},
                                      {'0', '7', '8', '9'}};
  int p1, p2;
  while (1) {
    print_board(board);
    printf("P1의 차례: ");
    scanf("%d", &p1);
    change_board(p1, P1_C, board);
    if (check_board(board)) {
      print_board(board);
      break;
    };

    print_board(board);
    printf("P2의 차례: ");
    scanf("%d", &p2);
    change_board(p2, P2_C, board);
    if (check_board(board)) {
      print_board(board);
      break;
    };
  };
}
int change_board(int num, char icon, char board[4][4]) {
  int x, y;
  if (num <= 3) {
    x = 1;
    y = num;
  } else if (num <= 6) {
    x = 2;
    y = num - 3;
  } else if (num <= 9) {
    x = 3;
    y = num - 6;
  } else {
    printf("number is not in here: %d", num);
    return -1;
  }
  if (board[x][y] == P1_C || board[x][y] == P2_C)
    return -1;
  else {
    board[x][y] = icon;
    return 1;
  }
}
int print_board(char board[4][4]) {
  int i, j;
  for (i = 1; i <= 3; i++) {
    for (j = 1; j <= 3; j++) {
      if (board[i][j] == 'O') {
        printf("[%s%c%s]", RED, board[i][j], RESET);
      } else if (board[i][j] == 'X') {
        printf("[%s%c%s]", BLU, board[i][j], RESET);
      } else {
        printf("[%c]", board[i][j]);
      }
    }
    printf("\n");
  }
  printf("---------\n");
}
int check_board(char board[4][4]) {
  int i, j;

  char now[3] = {};
  for (i = 1; i <= 3; i++) {
    for (j = 1; j <= 3; j++) {
      now[j - 1] = board[i][j];
    }
    // printf("checking:%c,%c,%c\n", now[0], now[1], now[2]);
    if (check_winner(now) == 1) {
      return 1;
    };
  }
  for (i = 1; i <= 3; i++) {
    for (j = 1; j <= 3; j++) {
      now[j - 1] = board[j][i];
    }
    // printf("checking:%c,%c,%c\n", now[0], now[1], now[2]);
    if (check_winner(now) == 1) {
      return 1;
    };
  }
  now[0] = board[1][1];
  now[1] = board[2][2];
  now[2] = board[3][3];
  //   printf("checking:%c,%c,%c\n", now[0], now[1], now[2]);

  if (check_winner(now) == 1) {
    return 1;
  };
  now[0] = board[1][3];
  now[1] = board[2][2];
  now[2] = board[3][1];
  //   printf("checking:%c,%c,%c\n", now[0], now[1], now[2]);
  if (check_winner(now) == 1) {
    return 1;
  };
};
int check_winner(char now[3]) {
  char pos_o[3] = {'O', 'O', 'O'};
  char pos_x[3] = {'X', 'X', 'X'};
  if (now[0] == pos_o[0] && now[1] == pos_o[1] && now[2] == pos_o[2]) {
    printf("%sP1%s의 승리!\n", RED, RESET);
    return 1;
  }
  if (now[0] == pos_x[0] && now[1] == pos_x[1] && now[2] == pos_x[2]) {
    printf("%sP2%s의 승리!\n", BLU, RESET);
    return 1;
  }
  return 0;
}