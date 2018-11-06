#include "corewar.h"

void processes_add(t_proc *parent_process, unsigned char *map, t_cycle *main_cycle, int index)
{
	t_proc *tmp;

	t_proc *tail;
	int j;

	j = 0;
	tmp = NULL;
	tail = parent_process;
	(*main_cycle).processes++;
	while (tail->next)
		tail = tail->next;
	tmp = (t_proc *)malloc(sizeof(t_proc));
	tmp->id = (*main_cycle).processes - 1;
	tmp->name = (*parent_process).name;
	tmp->current_position = index;
	tmp->carry = (*parent_process).carry;
	if ((*parent_process).parent_nbr == -1)
		tmp->parent_nbr = (*parent_process).id;
	else
		tmp->parent_nbr = (*parent_process).parent_nbr;
	tmp->if_live = 1;
	tmp->cmd = map[tmp->current_position];
	(*main_cycle).indexes[index][0] = tmp->parent_nbr + 1;
	(*main_cycle).indexes[index][1] = 1;
	if (tmp->cmd >= 1 && tmp->cmd <= 16)
		tmp->cycles_wait = op_tab[tmp->cmd - 1].cycles_wait;
	else
		tmp->cycles_wait = 1;
	tmp->last_live_cycle = 0;
	tmp->child_proc_lives = 0;
	tmp->next = NULL;
	clear_argv_arr(tmp);
	while (j < REG_NUMBER)
	{
		tmp->regs[j] = (*parent_process).regs[j];
		j++;
	}
	tail->next = tmp;
}

int find_arg_index(t_proc *processes, int target)
{
	int i;

	i = 0;
	while(i < 3 && (*processes).argv[i][0] != target)
		i++;
	return (i);
}

void check_if_lives(t_proc *head_proc, t_cycle *main_cycle)
{
	while (head_proc)
	{
		if ((*head_proc).last_live_cycle < (*main_cycle).cycles - (*main_cycle).cycle_die)
		{
			(*head_proc).if_live = 0;
			(*main_cycle).processes--;
		}
		if ((*head_proc).last_live_cycle > (*main_cycle).current_winner)
		{
			(*main_cycle).current_winner = (*head_proc).last_live_cycle;
			if ((*head_proc).parent_nbr == -1)
				(*main_cycle).winner_id = (*head_proc).id;
			else
				(*main_cycle).winner_id = (*head_proc).parent_nbr;
			(*main_cycle).winner_name = (*head_proc).name;
		}
		head_proc = head_proc->next;
	}
}

void fill_start_map_id(t_cycle *main_cycle, header_t bots[4], t_flags *params)
{
	unsigned int i;
	unsigned int j;
	unsigned int k;

	i = 0;
	j = 0;
	k = 0;
	while (i < MEM_SIZE)
	{

		(*main_cycle).indexes[i][0] = 0;
		(*main_cycle).indexes[i][1] = 0;
		i++;
	}
	i = 0;
	while (i < MEM_SIZE && j < (*params).bots_quantity)
	{
		if (i == bots[j].start_index)
		{
			(*main_cycle).indexes[i][1] = 1;
			k = 0;
			while (k < bots[j].prog_size)
			{
				(*main_cycle).indexes[i][0] = j + 1;
				i++;
				k++;
			}
			j++;
		}
		i++;
	}
}

void vm_cycle(unsigned char *map, t_flags *params, header_t bots[4])
{
	int i;
	t_cycle main_cycle;
	t_proc *processes;
	int id_counter;
	WINDOW *win;

	win = NULL;
	i = 0;
	processes = NULL;
	id_counter = 0;
	main_cycle_init(&main_cycle, params);
	fill_start_map_id(&main_cycle, bots, params);
	processes = processes_init(params, bots, map);
	main_cycle.head_proc = processes;
	if ((*params).ncurses == 1)
		visual_init(&win);
	while (main_cycle.cycle_die > 0 && main_cycle.processes > 0)
	{
		i = 0;
		processes = main_cycle.head_proc;
		if ((*params).ncurses == 1)
			map_to_screen(map, &main_cycle, params, main_cycle.head_proc, win);
		while (i < main_cycle.prev_processes && processes)
		{
			if ((*processes).if_live && (*processes).cmd >= 1 && (*processes).cmd <= 16)
			{
				if (op_tab[map[(*processes).current_position] - 1].codage)
				{
					id_counter = (*processes).current_position + 1;
					take_args(map[id_counter], processes);
					get_args_values(processes, map, &id_counter);
				}
				else
				{
					id_counter = (*processes).current_position;
					(*processes).argv[0][0] = DIR_CODE;
					get_arg_vals[(*processes).argv[0][0] - 1](processes, map, 0, &id_counter);
				}
				if ((*processes).cycles_wait == 1)
				{
					instruct[(*processes).cmd - 1](main_cycle.head_proc, i, &main_cycle, map);
					if ((*processes).cmd != 9 || ((*processes).cmd == 9 && (*processes).carry == 0))
					{
						main_cycle.indexes[(*processes).current_position][1] = 0;
						(*processes).current_position = id_counter + 1;
					}
					(*processes).current_position %= MEM_SIZE;
					(*processes).cmd = map[(*processes).current_position];
					if ((*processes).cmd >= 1 && (*processes).cmd <= 16)
						(*processes).cycles_wait = op_tab[(*processes).cmd - 1].cycles_wait;
					else
						(*processes).cycles_wait = 1;
					if ((*processes).parent_nbr == -1)
						main_cycle.indexes[(*processes).current_position][0] = i + 1;
					else
						main_cycle.indexes[(*processes).current_position][0] = (*processes).parent_nbr + 1;
					main_cycle.indexes[(*processes).current_position][1] = 1;
				}
				else
					(*processes).cycles_wait--;
				clear_argv_arr(processes);
			}
			else
			{
				main_cycle.indexes[(*processes).current_position][1] = 0;
				(*processes).current_position++;
				(*processes).current_position %= MEM_SIZE;
				(*processes).cmd = map[(*processes).current_position];
				if ((*processes).cmd >= 1 && (*processes).cmd <= 16)
					(*processes).cycles_wait = op_tab[(*processes).cmd - 1].cycles_wait;
				else
					(*processes).cycles_wait = 1;
				if ((*processes).parent_nbr == -1)
					main_cycle.indexes[(*processes).current_position][0] = i + 1;
				else
					main_cycle.indexes[(*processes).current_position][0] = (*processes).parent_nbr + 1;
				main_cycle.indexes[(*processes).current_position][1] = 1;
			}			
			if ((*processes).child_proc_lives > NBR_LIVE)
			{
				(*processes).child_proc_lives = 0;
				main_cycle.cycle_die -= CYCLE_DELTA;
			}
			processes = processes->next;
			i++;
		}
		main_cycle.prev_processes = main_cycle.processes;
		if (main_cycle.cycles != 0 && main_cycle.cycles % main_cycle.cycle_die == 0)
		{
			check_if_lives(main_cycle.head_proc, &main_cycle);
			main_cycle.checks_if_die++;
			if (main_cycle.checks_if_die == MAX_CHECKS)
			{
				main_cycle.checks_if_die = 0;
				if (main_cycle.cycle_die == main_cycle.prev_cycle_die)
					main_cycle.cycle_die -= CYCLE_DELTA;
				main_cycle.prev_cycle_die = main_cycle.cycle_die;
			}
		}
		usleep((useconds_t)((int)1000000 / main_cycle.second_limit));
		main_cycle.cycles++;
	}
	print_winner(win, main_cycle);
	if ((*params).ncurses == 1)
		endwin();
	ft_printf("we exited main cycle\n");

}