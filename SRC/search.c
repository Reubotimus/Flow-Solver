#include "search.h"
#include "options.h"
#include "queues.h"
#include "extensions.h"

//////////////////////////////////////////////////////////////////////
// Initialize Maximum number of nodes allowed, given a MB bound
void initialize_search( size_t* max_nodes,
			const game_info_t* info,
			const game_state_t* init_state );

void initialize_search( size_t* max_nodes,
			const game_info_t* info,
			const game_state_t* init_state ){

	*max_nodes = g_options.search_max_nodes;
	if (! (*max_nodes) ) {
		*max_nodes = floor( g_options.search_max_mb * MEGABYTE /
				   sizeof(tree_node_t) );
	}

	if (!g_options.display_quiet) {
		
		printf("\n************************************************"
		       "\n*               Initializing Search            *\n");

		
		printf("* Will search up to %'zu nodes (%'.2f MB) \n",
		       *max_nodes, *max_nodes*(double)sizeof(tree_node_t)/MEGABYTE);
  
		printf("* Num Free cells at start is %'d\n\n",
		       init_state->num_free);

		printf("* Initial State:\n");
		game_print(info, init_state);

		printf ("*************************************************\n\n");

	}

}

//////////////////////////////////////////////////////////////////////
// Check if node contains a state with:
//    a) no free cell
//    b) all colors connected by a path

int is_solved(tree_node_t* node, const game_info_t* info){
	if ( node->state.num_free == 0 && 
	     node->state.completed == (1 << info->num_colors) - 1 ) {

		return 1;
					
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////
// Animate sequence of moves up to node

void report_solution( const tree_node_t* node, const game_info_t* info ){

		assert(node);

		printf("Number of moves=%'g, Free cells=%'d\n",
		       node->cost_to_node,
		       node->state.num_free);
		
		printf("\n");
		game_print(info, &node->state);
		
		animate_solution(info, node);
		delay_seconds(1.0);
}

int game_dijkstra_search(const game_info_t* info,
                const game_state_t* init_state,
                double* elapsed_out,
                size_t* nodes_out,
                game_state_t* final_state) {



	// Max_nodes that fit in memory
	size_t max_nodes;

	printf(" %d ", init_state->num_free);
	
	initialize_search( &max_nodes, info, init_state );

	//Create Root node (uncomment code below)
	tree_node_t* root = node_create(NULL, info, init_state);

	//Create Priority Queue
	heapq_t pq = heapq_create(max_nodes);

	int result = SEARCH_IN_PROGRESS;
	const tree_node_t* solution_node = NULL;

	//Record the timestamp search starts
	double start = now();

	//Enqueue root
	heapq_enqueue(&pq, root);

	
	
	//While no solution found
	while (result == SEARCH_IN_PROGRESS) {
		
		if (heapq_empty(&pq)) {
			result = SEARCH_UNREACHABLE;
			break;
		}

		//Remove node from Queue, in order to generate its successors
		tree_node_t *node = heapq_deque(&pq);

		// gets next color
		int color = game_next_move_color(info, &node->state);

		// explores colors 4 directions
		for (int dir = DIR_LEFT; dir <= DIR_DOWN; dir++) {
			
			//if (color == -1) break;

			// skips direction if the move is not possible
			if (!game_can_move(info, &(node->state), color, dir)) continue;

			// create new state with move in that direction
			game_state_t new_state = node->state;
			game_make_move(info, &new_state, color, dir);
			

			// checks if the node can be queued
			if (pq.count == pq.capacity) {
				result = SEARCH_FULL;
				break;
			}

			// Remove node if new position creates a deadend (uncomment code below)
			if(g_options.node_check_deadends && game_check_deadends(info, &(new_state))){
				continue;
			}

			// since it is a valid state, creates a new node
			tree_node_t *new_node;
			new_node = node_create(node, info, &new_state);

			//Check if game is solved (uncomment code below)
			if ( is_solved(new_node, info) ) {          
				result = SEARCH_SUCCESS;
				solution_node = new_node;
				*final_state = solution_node->state;
				free(new_node);
				break;     
			}

			// adds new node to the queue
			heapq_enqueue(&pq, new_node);
		}
		free(node);
		// checks if solution is reachable
		//
	}
	/**
	 * END OF FILL IN CODE SECTION
	 */
				
	//Get Stats
	double elapsed = now() - start;
	if (elapsed_out) { *elapsed_out = elapsed; }
	if (nodes_out)   { *nodes_out = heapq_count(&pq); }

	//Report soultion
	if( result == SEARCH_SUCCESS
	    && g_options.display_animate
	    && !g_options.display_quiet )
		report_solution( solution_node, info );

	//Report next node in Queue
	if (result == SEARCH_FULL && g_options.display_diagnostics) {
		
		printf("here's the lowest cost thing on the queue:\n");		
		node_diagnostics(info, heapq_peek(&pq));				
	}
	
	// frees all nodes in priority queue
	while (!heapq_empty(&pq)){
		free(heapq_deque(&pq));
	}
	heapq_destroy(&pq);

	return result;

  
}

