#include "tree_lions.h"

#include <stdio.h>
#include <string.h>

#include "uTests.h"

int lut_array[4][4][4][4][2];

bool is_end (State_t first_state) {
    bool res = false;
    if ((0 == first_state.state[0]) && (0 == first_state.state[1]) && (3 == first_state.state[2]) &&
        (3 == first_state.state[3])) {
        res = true;
    }
    return res;
}

int danger_cnt = 0;
bool is_lethal (State_t first_state) {
    bool res = false;
    if ((first_state.state[1] < first_state.state[0]) && (0 < first_state.state[1])) {
#if 0
		printf("\n [!] danger case: %d danger [%d %d %d %d] on left ", danger_cnt,
				first_state.state[0], first_state.state[1], first_state.state[2],
				first_state.state[3]);
#endif
        res = true;
    }

    if ((0 < first_state.state[3]) && (first_state.state[3] < first_state.state[2])) {
#if 0
		printf("\n [!] danger case: %d danger [%d %d %d %d] on right", danger_cnt,
				first_state.state[0], first_state.state[1], first_state.state[2],
				first_state.state[3]);
#endif
        res = true;
    }

    if (true == res) {
        danger_cnt++;
    }

    return res;
}

char *node_color (bool state) {
    char *out_char = "green";
    if (true == state) {
        out_char = "red";
    } else {
        out_char = "green";
    }
    return out_char;
}

char *node_shape (State_t node_state) {
    char *out_char = "egg";
    if (DIR_RIGHT == node_state.state[4]) {
        out_char = "oval";
    }
    if (DIR_LEFT == node_state.state[4]) {
        out_char = "box";
    }

    return out_char;
}

static bool is_contain (State_t cur_state, int lion_num, int man_num) {
    bool res = false;
    if (DIR_LEFT == cur_state.state[4]) {
        if (man_num <= cur_state.state[1]) {
            if (lion_num <= cur_state.state[0]) {
                res = true;
            }
        }
    } else if (DIR_RIGHT == cur_state.state[4]) {
        printf ("\n[d] from right bridge <-	");
        if (man_num <= cur_state.state[3]) {
            if (lion_num <= cur_state.state[2]) {
                res = true;
            }
        }
    }
    return res;
}

void print_node (FILE *stream, State_t node_state) {
    if (stream) {

        if (DIR_LEFT == node_state.state[4]) {
            fprintf (stream, "\n subgraph cluster_left {");
        }
        if (DIR_RIGHT == node_state.state[4]) {
            fprintf (stream, "\n subgraph cluster_right {");
        }
        fprintf (stream, "\n L%d_M%d_L%d_M%d_B%d [color=%s, style=filled, shape=%s];", node_state.state[0],
                 node_state.state[1], node_state.state[2], node_state.state[3], node_state.state[4],
                 node_color (is_lethal (node_state)), node_shape (node_state));
        fprintf (stream, "\n  }");
    }
}

void print_node_stdout (State_t node_state) {

    printf ("\n L%d_M%d_L%d_M%d_B%d [color=%s, style=filled, shape=%s];", node_state.state[0], node_state.state[1],
            node_state.state[2], node_state.state[3], node_state.state[4], node_color (is_lethal (node_state)),
            node_shape (node_state));
}

static void print_transfer (FILE *stream, State_t first_state, State_t second_state, int man_num, int lion_num) {
    printf ("\n[d] %s():", __FUNCTION__);
    if (stream) {
        char dirr_str[55] = "<ERR>";

        print_node (stream, first_state);
        print_node (stream, second_state);

        fprintf (stream, "\n L%d_M%d_L%d_M%d_B%d", first_state.state[0], first_state.state[1], first_state.state[2],
                 first_state.state[3], first_state.state[4]);

        if ((0 == first_state.state[4]) && (1 == second_state.state[4])) {
            sprintf (dirr_str, " L->R ");
        }

        if ((1 == first_state.state[4]) && (0 == second_state.state[4])) {
            sprintf (dirr_str, " R->L ");
        }
        fprintf (stream, " -> ");
        fprintf (stream, " L%d_M%d_L%d_M%d_B%d ", second_state.state[0], second_state.state[1], second_state.state[2],
                 second_state.state[3], second_state.state[4]);
        fprintf (stream, "[ label=\"M%dL%d Dir%s\" ];", man_num, lion_num, dirr_str);
    }
}

static State_t proc_input (State_t first_state, int man_num, int lion_num) {
    printf ("\n[d] %s(): move M%d L%d", __FUNCTION__, man_num, lion_num);
    State_t out_state;
    print_node_stdout (first_state);
    memcpy (&out_state, &first_state, sizeof (State_t));
    int boat_capacity = 0;
    out_state.state[0] = first_state.state[0];
    out_state.state[1] = first_state.state[1];
    out_state.state[2] = first_state.state[2];
    out_state.state[3] = first_state.state[3];
    out_state.state[4] = first_state.state[4];
    bool res = false;
    res = is_contain (first_state, lion_num, man_num);
    if (false == res) {
        printf ("\n[d] impossible transfer");
        return out_state;
    }

    if (0 == lion_num) {
        if (0 == man_num) {
            if (DIR_LEFT == first_state.state[4]) {
                out_state.state[4] = DIR_RIGHT;
            } else if (DIR_RIGHT == first_state.state[4]) {
                out_state.state[4] = DIR_LEFT;
            }
            return out_state;
        }
    }
    if (DIR_LEFT == first_state.state[4]) {
        printf ("\n[d] from left bridge ->");

        if ((man_num <= out_state.state[1]) && (0 < man_num)) {
            out_state.state[1] -= man_num;
            out_state.state[3] += man_num;
            boat_capacity += man_num;
            out_state.state[4] = DIR_RIGHT;
        }

        if ((lion_num <= out_state.state[0]) && (0 < lion_num)) {
            out_state.state[0] -= lion_num;
            out_state.state[2] += lion_num;
            boat_capacity += lion_num;
            out_state.state[4] = DIR_RIGHT;
        }
    } else if (DIR_RIGHT == first_state.state[4]) {
        printf ("\n[d] from right bridge <-	");
        if ((man_num <= out_state.state[3]) && (0 < man_num)) {
            printf ("\n[d] enough man");
            out_state.state[3] -= man_num;
            out_state.state[1] += man_num;
            boat_capacity += man_num;
            out_state.state[4] = DIR_LEFT;
        }

        if ((lion_num <= out_state.state[2]) && (0 < lion_num)) {
            printf ("\n[d] enough oins");
            out_state.state[2] -= lion_num;
            out_state.state[0] += lion_num;
            boat_capacity += lion_num;
            out_state.state[4] = DIR_LEFT;
        }
    }
    if (2 < boat_capacity) {
        printf ("\n [e] boat is overveigt");
    }

    return out_state;
}

bool print_state (State_t first_state) {
    bool res = true;
    printf ("\n[");
    printf (" %d", first_state.state[0]);
    printf (" %d |", first_state.state[1]);
    printf (" %d", first_state.state[2]);
    printf (" %d ", first_state.state[3]);
    printf (" %s", first_state.state[4] ? "right" : "left");

    res = is_lethal (first_state);
    if (true == res) {
        printf (" danger");
    }
    printf ("] ");
    return res;
}
// L1_M3_L2_M0_B1
// M1L1 Dir R->L
// L2_M3_L1_M0_B0
bool test_lion_man_task_1l1m (void) {
    printf ("\n[d] %s():", __FUNCTION__);
    State_t first_state;
    State_t second_state;
    first_state.state[0] = 1;
    first_state.state[1] = 3;
    first_state.state[2] = 2;
    first_state.state[3] = 0;
    first_state.state[4] = 1;
    second_state = proc_input (first_state, 1, 1); // ML

    EXPECT_EQ (1, second_state.state[0]);
    EXPECT_EQ (3, second_state.state[1]);
    EXPECT_EQ (2, second_state.state[2]);
    EXPECT_EQ (0, second_state.state[3]);
    EXPECT_EQ (1, second_state.state[4]);

    return true;
}

bool test_lion_man_task_l0m0 (void) {
    printf ("\n[d] %s():", __FUNCTION__);
    State_t first_state;
    State_t second_state;
    first_state.state[0] = 1;
    first_state.state[1] = 3;
    first_state.state[2] = 2;
    first_state.state[3] = 0;
    first_state.state[4] = 1;
    second_state = proc_input (first_state, 0, 0); // ML

    EXPECT_EQ (1, second_state.state[0]);
    EXPECT_EQ (3, second_state.state[1]);
    EXPECT_EQ (2, second_state.state[2]);
    EXPECT_EQ (0, second_state.state[3]);
    EXPECT_EQ (0, second_state.state[4]);

    return true;
}

// L1_M3_L2_M0_B1
// M2L0 Dir R->L
// L1_M3_L2_M0_B0
bool test_lion_man_task_2m (void) {
    printf ("\n[d] %s():", __FUNCTION__);
    State_t first_state;
    State_t second_state;
    first_state.state[0] = 1;
    first_state.state[1] = 3;
    first_state.state[2] = 2;
    first_state.state[3] = 0;
    first_state.state[4] = 1;
    second_state = proc_input (first_state, 2, 0); // mm

    EXPECT_EQ (1, second_state.state[0]);
    EXPECT_EQ (3, second_state.state[1]);
    EXPECT_EQ (2, second_state.state[2]);
    EXPECT_EQ (0, second_state.state[3]);
    EXPECT_EQ (1, second_state.state[4]);

    return true;
}

bool test_lion_man_task (void) {
    printf ("\n[d] %s():", __FUNCTION__);
    EXPECT_TRUE (test_lion_man_task_l0m0 ());
    EXPECT_TRUE (test_lion_man_task_1l1m ());
    EXPECT_TRUE (test_lion_man_task_2m ());

    State_t first_state;
    State_t second_state;
    first_state.state[0] = 3;
    first_state.state[1] = 3;
    first_state.state[2] = 0;
    first_state.state[3] = 0;
    first_state.state[4] = 0;
    second_state = proc_input (first_state, 2, 0); // mm
    if (DIR_RIGHT != second_state.state[4]) {
        return false;
    }
    if (1 != second_state.state[1]) {
        return false;
    }
    if (2 != second_state.state[3]) {
        return false;
    }

    return true;
}

static bool list_variants (State_t first_state, FILE *fileDot) {
    printf ("\n[d] %s(): addr of main 0x%p", __FUNCTION__, list_variants);
    if (0 == lut_array[first_state.state[0]][first_state.state[1]][first_state.state[2]][first_state.state[3]]
                      [first_state.state[4]]) {
        lut_array[first_state.state[0]][first_state.state[1]][first_state.state[2]][first_state.state[3]]
                 [first_state.state[4]] = 1;
    } else {
        return false;
    }

    bool res;
    res = is_end (first_state);
    if (true == res) {
        return true;
    }

    res = is_lethal (first_state);
    State_t temp_state;
    if (true == res) {
        return false;
    }

    temp_state = proc_input (first_state, 2, 0); // mm
    if (0 != memcmp (&temp_state, &first_state, sizeof (State_t))) {
        print_transfer (fileDot, first_state, temp_state, 2, 0);
        res = list_variants (temp_state, fileDot);
        if (true == res) {
            return true;
        }
    }

#if 0
	temp_state = proc_input(first_state, 0, 2);        //LL
	if (0 != memcmp(&temp_state, &first_state, sizeof(State_t))) {
		print_transfer(fileDot, first_state, temp_state, 0, 2);
		res = list_variants(temp_state, fileDot);
		if (true == res) {
			return true;
		}
	}
#endif

    temp_state = proc_input (first_state, 1, 0); // m
    if (0 != memcmp (&temp_state, &first_state, sizeof (State_t))) {
        print_transfer (fileDot, first_state, temp_state, 1, 0);
        res = list_variants (temp_state, fileDot);
        if (true == res) {
            return true;
        }
    }

    temp_state = proc_input (first_state, 1, 1); // LM
    if (0 != memcmp (&temp_state, &first_state, sizeof (State_t))) {
        print_transfer (fileDot, first_state, temp_state, 1, 1);
        res = list_variants (temp_state, fileDot);
        if (true == res) {
            return true;
        }
    }
#ifdef EMPTY_ALLOWED
    temp_state = proc_input (first_state, 0, 0); // LM
    if (0 != memcmp (&temp_state, &first_state, sizeof (State_t))) {
        print_transfer (fileDot, first_state, temp_state, 0, 0);
        res = list_variants (temp_state, fileDot);
        if (true == res) {
            return true;
        }
    }
#endif

    return false;
}

//
State_t stataTable[NUM_OF_STATES][4] = {0};

bool init_look_up_table (FILE *fileDot) {
    printf ("\n[d] %s(): addr of main 0x%p", __FUNCTION__, run_tree_lions);
    int llione = 0;
    bool res = false;
    int rlione = 0;
    int lman = 0;
    int rman = 0;
    int cnt = 0;
    for (llione = 0; llione < 4; llione++) {
        for (lman = 0; lman < 4; lman++) {
            for (rlione = 0; rlione < 4; rlione++) {
                for (rman = 0; rman < 4; rman++) {
                    int animals = llione + rlione + rlione + rman;
                    if ((6 == animals) && (llione < 3) && (lman) && (rlione < 3) && (rman < 3)) {

                        stataTable[cnt][0].state[0] = llione;
                        stataTable[cnt][0].state[1] = lman;
                        stataTable[cnt][0].state[2] = rlione;
                        stataTable[cnt][0].state[3] = rman;
                        stataTable[cnt][IN_M] = proc_input (stataTable[cnt][0], 1, 0);  // m
                        stataTable[cnt][IN_ML] = proc_input (stataTable[cnt][0], 1, 1); // ml
                        stataTable[cnt][IN_MM] = proc_input (stataTable[cnt][0], 2, 0); // mm
#if 0
						if (fileDot) {
					    	print_transfer(fileDot, stataTable[cnt][0], stataTable[cnt][IN_M],  1, 0);
					    	print_transfer(fileDot, stataTable[cnt][0], stataTable[cnt][IN_ML], 1, 1);
					    	print_transfer(fileDot, stataTable[cnt][0], stataTable[cnt][IN_MM], 2, 0);
						}
#endif
                    }
                    lut_array[llione][lman][rlione][rman][0] = 0;
                    lut_array[llione][lman][rlione][rman][1] = 0;
                }
            }
        }
    }
    return res;
}

bool run_tree_lions (void) {
    printf ("\n[d] %s(): addr of main 0x%p", __FUNCTION__, run_tree_lions);
    bool res = false;
    FILE *fileDot = fopen ("shore_states.dot", "w");
    if (NULL != fileDot) {
        printf ("\n[d] file opened");

        fprintf (fileDot, "\ndigraph G {");

        fprintf (fileDot, "\n rankdir=LR;");
        printf ("\n[d] fprintf done");
        State_t init_st;
        init_st.state[0] = 3;
        init_st.state[1] = 3;
        init_st.state[2] = 0;
        init_st.state[3] = 0;
        init_st.state[4] = DIR_LEFT; // boat on the left shore
        danger_cnt = 0;
        init_look_up_table (fileDot);
        // init_state_table();

        res = list_variants (init_st, fileDot);

        fprintf (fileDot, "\n}");
        fclose (fileDot);
    }

    return res;
}
