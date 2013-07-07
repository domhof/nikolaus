/*
 * nikolaus.c
 *
 *  Created on: Jul 6, 2013
 *      Author: Dominik Hofer <me@dominikhofer.com>
 */

#include <stdio.h>
#include <string.h>

typedef enum {false, true} bool;
typedef bool AdjMatrix[5][5];
typedef int Node;

void print_house(AdjMatrix adj_mat) {
    printf("  O  \n");
    printf(" %c %c \n", (adj_mat[2][4]) ? '/' : ' ', (adj_mat[3][4]) ? '\\' : ' ');
    printf("O%c%c%cO\n", (adj_mat[2][3]) ? '-' : ' ', (adj_mat[2][3]) ? '-' : ' ', (adj_mat[2][3]) ? '-' : ' ');
    printf("%c%c %c%c\n", (adj_mat[0][2]) ? '|' : ' ', (adj_mat[1][2]) ? '\\' : ' ', (adj_mat[0][3]) ? '/' : ' ', (adj_mat[1][3]) ? '|' : ' ');

    char middle = ' ';
    if (adj_mat[0][3] && adj_mat[1][2]) middle = 'X';
    else if (adj_mat[0][3])  middle = '/';
    else if (adj_mat[1][2])  middle = '\\';

    printf("%c %c %c\n", (adj_mat[0][2]) ? '|' : ' ', middle, (adj_mat[1][3]) ? '|' : ' ');
    printf("%c%c %c%c\n", (adj_mat[0][2]) ? '|' : ' ', (adj_mat[0][3]) ? '/' : ' ', (adj_mat[1][2]) ? '\\' : ' ', (adj_mat[1][3]) ? '|' : ' ');
    printf("O%c%c%cO\n", (adj_mat[0][1]) ? '-' : ' ', (adj_mat[0][1]) ? '-' : ' ', (adj_mat[0][1]) ? '-' : ' ');
}

void remove_edge(AdjMatrix mat, Node current, Node next) {
    mat[current][next] = false;
    mat[next][current] = false;
}

void add_edge(AdjMatrix mat, Node current, Node next) {
    mat[current][next] = true;
    mat[next][current] = true;
}

bool compare_adj_mat(AdjMatrix mat_a, AdjMatrix mat_b) {
    if (0 == memcmp(mat_a, mat_b, sizeof(AdjMatrix))) return true;
    else return false;
}

void copy_adj_matrix(AdjMatrix from, AdjMatrix to) {
    memcpy(to, from, sizeof(AdjMatrix));
}

void print_fail(AdjMatrix adj_mat) {
    static AdjMatrix fail[500];
    static int pos = 0;

    for (int i = 0; i < 500; i++) {
        if (compare_adj_mat(fail[i], adj_mat)) return;
    }
    copy_adj_matrix(adj_mat, fail[pos++]);

    printf("\n\nNr. %d:\n\n", pos);
    print_house(adj_mat);
}

void walk(AdjMatrix adj_mat, Node current, AdjMatrix adj_mat_used_edges, int step) {
    bool fail = true;

    for (Node next = 0; next < 5; next++) {
        if (adj_mat[current][next] && !adj_mat_used_edges[current][next]) {
            fail = false;
            add_edge(adj_mat_used_edges, current, next);
            walk(adj_mat, next, adj_mat_used_edges, step + 1);
            remove_edge(adj_mat_used_edges, current, next);
        }
    }

    if (fail && step < 8) {
        print_fail(adj_mat_used_edges);
    }
}

int main(int argc, char *argv[]) {
    AdjMatrix adj_mat = {   { 0, 1, 1, 1, 0 },
                            { 1, 0, 1, 1, 0 },
                            { 1, 1, 0, 1, 1 },
                            { 1, 1, 1, 0, 1 },
                            { 0, 0, 1, 1, 0 } };

    AdjMatrix empty_mat = { { 0, 0, 0, 0, 0 },
                            { 0, 0, 0, 0, 0 },
                            { 0, 0, 0, 0, 0 },
                            { 0, 0, 0, 0, 0 },
                            { 0, 0, 0, 0, 0 } };

    for (Node start = 0; start < 5; start++) {
        walk(adj_mat, start, empty_mat, 0);
    }

    return 0;
}
