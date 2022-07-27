#include <stdio.h>
#include <math.h>
#include <stdbool.h>

#define INNER_BOARD_LENGTH 145.0
#define OUTER_BOARD_LENGTH 45.0
#define IDEAL_INNER_BOARD_SPACING 10.0

typedef struct {
    int board_count;
    double inner_board_spacing;
} solution;

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

    printf("wall length: %lf\n\n", WALL_LENGTH);

    /* board_count is initialized to max amount of boards possible */
    int board_count = floor(WALL_LENGTH/INNER_BOARD_LENGTH);
    double total_inner_board_spacing, inner_board_spacing;

    solution solution = {.inner_board_spacing = -1.0, .board_count = -1};
    for(;;) {
        if (board_count <= 1) {
            break;
        }

        /* calculate spacing between inner boards */
        total_inner_board_spacing = WALL_LENGTH-(INNER_BOARD_LENGTH*board_count);
        inner_board_spacing = total_inner_board_spacing/(board_count-1);

        /* if spacing is closer to ideal board spacing make it the active solution */
        if (fabs(inner_board_spacing-IDEAL_INNER_BOARD_SPACING) < fabs(solution.inner_board_spacing-IDEAL_INNER_BOARD_SPACING)) {
            if (inner_board_spacing < OUTER_BOARD_LENGTH) {
                solution.inner_board_spacing = inner_board_spacing;
                solution.board_count = board_count;
            }
        }

        board_count--;
    }

    if (solution.board_count == -1) {
        fprintf(stderr, "error: no solution found\n");
    } else {
        printf("best solution found:\n");
        printf("board count: %d\n", solution.board_count);
        printf("inner board spacing: %lf\n", solution.inner_board_spacing);
    }

    return 0;
}
