#include <stdio.h>
#include <math.h>
#include <stdbool.h>

#define INNER_BOARD_LENGTH 145.0
#define OUTER_BOARD_LENGTH 45.0
#define MIN_INNER_BOARD_SPACING 5.0
#define MAX_INNER_BOARD_SPACING 15.0

int main(int argc, char *argv[]) {
    /* parse command line arguments */
    if (argc != 2) {
        fprintf(stderr, "usage: %s <wall length millimeter>\n", argv[0]);
        return 1;
    }

    double WALL_LENGTH;
    if (sscanf (argv[1], "%lf", &WALL_LENGTH) != 1) {
        fprintf(stderr, "error: not an integer");
        return 1;
    }

    printf("wall length: %lf\n", WALL_LENGTH);

    /* board_count is initialized to max amount of boards possible */
    int board_count = floor(WALL_LENGTH/INNER_BOARD_LENGTH), solution_count = 0;
    double total_inner_board_spacing, inner_board_spacing;
    for(;;) {
        if (board_count <= 1) {
            break;
        }

        /* calculate spacing between inner boards */
        total_inner_board_spacing = WALL_LENGTH-(INNER_BOARD_LENGTH*board_count);
        inner_board_spacing = total_inner_board_spacing/(board_count-1);

        /* if spacing fits requirements print solution */
        if (inner_board_spacing >= MIN_INNER_BOARD_SPACING && inner_board_spacing <= MAX_INNER_BOARD_SPACING) {
            printf("---\n");
            printf("board count: %d\n", board_count);
            printf("inner board spacing: %lf\n", inner_board_spacing);
            printf("total inner board spacing: %lf\n", total_inner_board_spacing);

            solution_count++;
        }

        board_count--;
    }

    if (solution_count > 0) {
        printf("---\n");
        printf("%d solutions found\n", solution_count);
    } else {
        fprintf(stderr, "error: no solution found\n");
    }

    return 0;
}
