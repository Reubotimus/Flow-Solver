#include "extensions.h"
#include "options.h"

//////////////////////////////////////////////////////////////////////
// For sorting colors

int color_features_compare(const void* vptr_a, const void* vptr_b) {

	const color_features_t* a = (const color_features_t*)vptr_a;
	const color_features_t* b = (const color_features_t*)vptr_b;

	int u = cmp(a->user_index, b->user_index);
	if (u) { return u; }

	int w = cmp(a->wall_dist[0], b->wall_dist[0]);
	if (w) { return w; }

	int g = -cmp(a->wall_dist[1], b->wall_dist[1]);
	if (g) { return g; }

	return -cmp(a->min_dist, b->min_dist);

}

//////////////////////////////////////////////////////////////////////
// Place the game colors into a set order

void game_order_colors(game_info_t* info,
                       game_state_t* state) {

	if (g_options.order_random) {
    
		srand(now() * 1e6);
    
		for (size_t i=info->num_colors-1; i>0; --i) {
			size_t j = rand() % (i+1);
			int tmp = info->color_order[i];
			info->color_order[i] = info->color_order[j];
			info->color_order[j] = tmp;
		}

	} else { // not random

		color_features_t cf[MAX_COLORS];
		memset(cf, 0, sizeof(cf));

		for (size_t color=0; color<info->num_colors; ++color) {
			cf[color].index = color;
			cf[color].user_index = MAX_COLORS;
		}
    

		for (size_t color=0; color<info->num_colors; ++color) {
			
			int x[2], y[2];
			
			for (int i=0; i<2; ++i) {
				pos_get_coords(state->pos[color], x+i, y+i);
				cf[color].wall_dist[i] = get_wall_dist(info, x[i], y[i]);
			}

			int dx = abs(x[1]-x[0]);
			int dy = abs(y[1]-y[0]);
			
			cf[color].min_dist = dx + dy;
			
		

		}


		qsort(cf, info->num_colors, sizeof(color_features_t),
		      color_features_compare);

		for (size_t i=0; i<info->num_colors; ++i) {
			info->color_order[i] = cf[i].index;
		}
    
	}

	if (!g_options.display_quiet) {

		printf("\n************************************************"
		       "\n*               Branching Order                *\n");
		if (g_options.order_most_constrained) {
			printf("* Will choose color by most constrained\n");
		} else {
			printf("* Will choose colors in order: ");
			for (size_t i=0; i<info->num_colors; ++i) {
				int color = info->color_order[i];
				printf("%s", color_name_str(info, color));
			}
			printf("\n");
		}
		printf ("*************************************************\n\n");

	}

}


static int is_surrounded(const game_info_t* info, const game_state_t* state, int x, int y) {
	pos_t pos = pos_from_coords(x, y);
	
	if (!(state->cells[pos] == TYPE_FREE || 
		  state->cells[pos] == TYPE_INIT || 
		  state->cells[pos] == TYPE_GOAL)) return 0;
	
	int num_free = 0;

	if (state->cells[pos] == TYPE_INIT || state->cells[pos] == TYPE_GOAL) {
		for (int color = 0; color < info->num_colors; color++) {
			// checks if the pos is a started start or finished finished
			if (pos == info->init_pos[color] && pos != state->pos[color]) return 0;
			if (pos == info->goal_pos[color] && (state->completed & (1 << color))) return 0;
			// checks if the pos is an unstarted start or unfinished finish
			if (pos == info->init_pos[color] && pos == state->pos[color]) num_free++;
			if (pos == info->goal_pos[color] && pos != state->pos[color]) num_free++;
		}
	}

	// checks in each direction if a flow is able to enter
	for (int dir = DIR_LEFT; dir <= DIR_DOWN; dir++) {
		pos_t offset_pos = pos_offset_pos(info, pos, dir);
		// if it is not a valid pos, it is a wall => not free
		if(offset_pos != INVALID_POS) {

			if (state->cells[offset_pos] == TYPE_FREE) {
				num_free++;
				continue;
			}

			// checks if the offset square is a head or goal
			for (int color = 0; color < info->num_colors; color++) {
				if (state->completed & (1 << color)) continue;
				if (offset_pos == state->pos[color] || offset_pos == info->goal_pos[color]) num_free++;
			}
		}
	}

	/*
	if (num_free <= 1 && (state->cells[pos] == TYPE_INIT || state->cells[pos] == TYPE_GOAL)) {
		printf("(%d,%d)\n",x,y);
		printf("cell state = %d\n", state->cells[pos]);
		game_print(info, state);

	}*/
	return num_free <= 1;
}

//////////////////////////////////////////////////////////////////////
// Check for dead-end regions of freespace where there is no way to
// put an active path into and out of it. Any freespace node which
// has only one free neighbor represents such a dead end. For the
// purposes of this check, cur and goal positions count as "free".

int game_check_deadends(const game_info_t* info,
                        const game_state_t* state) {
	
	int x, y;
	pos_get_coords(state->pos[state->last_color], &x, &y);
	

	for (int x_offset = -1; x_offset <= 1; x_offset++) {
		for (int y_offset = -1; y_offset <= 1; y_offset++) {
			
			if (x_offset == y_offset && y_offset == 0) continue;
			
			if (coords_valid(info, x + x_offset, y + y_offset) && 
					is_surrounded(info, state, x + x_offset, y + y_offset)) {
				return 1;

			}
		}
	}

	for (int x_offset = -2; x_offset <= 2; x_offset += 2) {
		for (int y_offset = -2; y_offset <= 2; y_offset += 2) {
			
			if (x_offset == y_offset && y_offset == 0) continue;

			// skips corners since they are not needed
			if (!(x_offset == 0 || y_offset == 0)) continue;
			
			if (coords_valid(info, x + x_offset, y + y_offset) && 
					is_surrounded(info, state, x + x_offset, y + y_offset)) {
				return 1;
			}
		}
	}

	return 0;

}
                                         

