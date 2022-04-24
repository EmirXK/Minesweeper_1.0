#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#define SIZE 7
#define BOMB 9

// github.com/EmirXK
// warning, spaghetti code ahead.

void print_matrix(int game_matrix[SIZE][SIZE]) {
	int i,j;
	int k=0;
	printf("\n    ");
	for (i=0;i<SIZE;i++) {
		while (k<SIZE) {
			printf("%d ",k);
			k++;
			if (k==SIZE) {
				printf("\n");
				k=0;
				break;
			}
		}
		while (k<SIZE*3/2) {
			printf("- ");
			k++;
			if (k==SIZE*3/2) {
				printf("\n");
				break;
			}
		}
		printf("%d | ",i);
		for (j=0;j<SIZE;j++) {
			if (game_matrix[i][j] == BOMB) {
				printf("B ");
			}
			else
				printf("%d ",game_matrix[i][j]);
		}
		printf("\n");
	}
}

int bomb_count(int game_matrix[SIZE][SIZE]) {
	int i,j;
	int counter = 0;
	for (i=0;i<SIZE;i++) {
		for (j=0;j<SIZE;j++) {
			if (game_matrix[i][j] == BOMB) {
				counter++;
			}
		}
	}
	printf("Bombs: %d\n",counter);
	return counter;
}

int main() {
	int game_matrix[SIZE][SIZE] = {0};
	int play_area[SIZE+2][SIZE+2] = {0};
	int control_matrix[SIZE][SIZE] = {0};
	srand(time(0));
	int i;
	int j;
	int a;
	int b;
	int x,y;
	int loop;
	

	for (i=0;i<SIZE+2;i++) {
		for (j=0;j<SIZE+2;j++) {
			for (a=1;a<SIZE+1;a++) {
				for (b=1;b<SIZE+1;b++) {
					play_area[a][b] = 1;
				}
			}
//			printf("%d ",play_area[i][j]);
		}
//		printf("\n");
	}
	for (loop=0;loop<SIZE*4/3 ;loop++) {
		re_bomb:
		a = rand() %SIZE;
		b = rand() %SIZE;
		if (game_matrix[a][b] == BOMB) {
			goto re_bomb;
		}
		else {
			game_matrix[a][b] = BOMB;
		}
	}
//	print_matrix(game_matrix);
	int bombcount = bomb_count(game_matrix);
	
	for (i=0;i<SIZE;i++) {
		for (j=0;j<SIZE;j++) {
			if (game_matrix[i][j] == BOMB) {
				for (a=i-1;a<i+2;a++) {
					for (b=j-1;b<j+2;b++) {
						if (play_area[a+1][b+1] != 0) {
							if (game_matrix[a][b] != BOMB) {
								game_matrix[a][b] += 1;
							}
						}
					}
				}
			}
		}
	}
//	print_matrix(game_matrix);
	int k;
	i=0;
	int temp, temp2;
	int o,p;
	
	int win = SIZE*SIZE - bombcount;
	printf("Clear fields required to win: %d\n",win);
	int check_win = 0;
	while (1) {
		k=0;
		printf("\n    ");
		for (i=0;i<SIZE;i++) {
			while (k<SIZE) {
				printf("%d ",k);
				k++;
				if (k==SIZE) {
					printf("\n");
					k=0;
					break;
				}
			}
			while (k<SIZE*3/2) {
				printf("- ");
				k++;
				if (k==SIZE*3/2) {
					printf("\n");
					break;
				}
			}
			printf("%d | ",i);
			for (j=0;j<SIZE;j++) {
				if (control_matrix[i][j] == 0) {
					printf("X ");
				}
				if (control_matrix[i][j] == 1) {
					printf("%d ",game_matrix[i][j]);
				}
			}
			printf("\n");
		}
		invalid_input:
		printf("\nUser Input(x y) : ");
		scanf("%d %d",&x,&y);
		if (x >= SIZE || y >= SIZE || x < 0 || y < 0) {
			printf("Invalid input\n");
			goto invalid_input;
		}
		if (control_matrix[x][y] == 1) {
			printf("Invalid input\n");
			goto invalid_input;
		}
		if (game_matrix[x][y] == BOMB) {
			print_matrix(game_matrix);
			printf("\nYou hit a bomb, game over.");
			break;
		}
		if (game_matrix[x][y] != 0) {
			control_matrix[x][y] = 1;
		}
		if (game_matrix[x][y] == 0) {
			for (i=0;i<SIZE;i++) {
				for (j=0;j<SIZE;j++) {
					if (game_matrix[x][y] == 0) {
						loop_index:
						control_matrix[x][y] = 1;
						for (a=x-1;a<x+2;a++) {
							for (b=y-1;b<y+2;b++) {
								if (play_area[a+1][b+1] != 0 ) {
									if (game_matrix[a][b] == 0) {
										if (control_matrix[a][b] == 0) {
											control_matrix[a][b] = 1;
											temp = a;
											temp2 = b;
											x = temp;
											y = temp2;
											goto loop_index;
										}
									}
								}
							}
						}
					}
				}
			}
		}
		for (i=0;i<SIZE;i++) {
			for (j=0;j<SIZE;j++) {
				if (game_matrix[i][j] == 0) {
					if (control_matrix[i][j] == 1) {
						for (a=i-1;a<i+2;a++) {
							for (b=j-1;b<j+2;b++) {
								if (play_area[a+1][b+1] != 0) {
									control_matrix[a][b] = 1;
								}
							}
						}
					}
				}
			}
		}
		check_win = 0;
		for (i=0;i<SIZE;i++) {
			for (j=0;j<SIZE;j++) {
				if (control_matrix[i][j] == 1)
					check_win++;
			}
		}
		if (check_win == win) {
			printf("\nYou Win\n");
			break;
		}
		system("cls"); // Thank you Tarik GOAT
		
		/*
		printf("check_win: %d\n",check_win);
		for (i=0;i<SIZE;i++) {
			for (j=0;j<SIZE;j++) {
				printf("%d ",control_matrix[i][j]);
			}
			printf("\n");
		}
		*/
		
	}
	
	getch();
	return 0;
}
