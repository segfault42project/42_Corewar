/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <lfabbro@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/16 17:30:39 by lfabbro           #+#    #+#             */
/*   Updated: 2017/01/28 20:27:12 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		check_opcode(t_process *proc, uint8_t opcode)
{
	t_instruction	*inst;

	inst = &(proc->inst);
	if (opcode >= 1 && opcode <= OPS_NUMBER)
	{
		inst->opcode = opcode;
		if (get_op(opcode).carry)
			(inst->i)++;
		return (1);
	}
	init_instruction(inst);
	return (0);
}

void		check_players_inst(t_env *e)
{
	t_process	*p;

	e->cur_process = e->nb_process;
	while (--(e->cur_process) >= 0)
	{
		p = &(e->process[e->cur_process]);
		// if (e->player[p->player_id].alive)
		// {
			if (p->inst.n_cycle == -1)
			{
				if (!check_opcode(p, get_mem_uint8(p, p->inst.i)))
					p->pc = (p->pc + 1) % MEM_SIZE;
				else if (!check_ocp(p, get_mem_uint8(p, p->inst.i)))
					p->inst.bad_ocp = 1;
			}
			if (!(p->inst.n_cycle))
				exec_instruction(e, p);
			else if (p->inst.n_cycle > 0)
				(p->inst.n_cycle)--;
		// }
	}
}

void		time_to_die(t_env *e)
{
	uint32_t	i;

	e->cur_die = 0;
	i = -1;
	e->alives = 0;
	e->check++;
	while (++i < e->nb_player)
	{
		if (!(e->player[i].live))
		{
			if (e->verbose & SHOW_DEATHS)
				ft_printf("Player %d is {:red}dead{:eoc}\n", i + 1);
			e->player[i].alive = 0;
		}
		else
			e->alives++;
		e->player[i].live = 0;
		if (e->lives > NBR_LIVE || e->check == MAX_CHECKS)
		{
			e->cycle_die -= CYCLE_DELTA;
			e->check = 0;
			if (e->verbose & SHOW_CYCLES)
				ft_printf("New cycle to die: %d\n", e->cycle_die);
		}
	}
	e->lives = 0;
	if (!e->alives || e->cycle_die <= 0)
		e->run = 0;
}

static void	run(t_env *e)
{
	e->run = 1;
	while (e->run)
	{
		e->cycle++;
		e->cur_die++;
		if (e->verbose & SHOW_CYCLES)
			ft_printf("Current cycle: %d (%d / %d)\n", e->cycle,\
													e->cur_die, e->cycle_die);
		check_players_inst(e);
		if (e->cur_die == e->cycle_die)
			time_to_die(e);
		if (e->dump && e->cycle == e->dump)
		{
			dump_memory(e);
			break ;
		}
	}
}

void	init_players(t_env *e)
{
	uint32_t	i;
	uint32_t	j;

	i = -1;
	while (++i < e->nb_player)
	{
		e->player[i].alive = 1;
		e->player[i].live = 0;
		j = -1;
		while (++j < e->player[i].header.prog_size)
		{
			g_mem[e->process[i].start + j] = e->player[i].op[j];
			g_color[e->process[i].start + j] = i + 1;
		}
	}
}

static int	init_vm(t_env *e, int argc, char **argv)
{
	uint8_t	fd[MAX_PLAYERS];

	if ((e->nb_player = ft_parse(e, argc, argv, fd)) < 1)
		return (0);
	e->nb_process = e->nb_player;
	if (ft_load(fd, e))
		return (0);
	if (!(e->process = (t_process*)malloc(sizeof(t_process) * e->nb_process)))
		return (0);
		init_processes(e);
	init_players(e);
	return (1);
}

int			main(int argc, char **argv)
{
	t_env	e;

	if (argc < 2)
		return (-1);
	init_env(&e);
	init_memory();
	if (!(init_vm(&e, argc, argv)))
		return (-1);//free
	run(&e);
}
//../ressources/corewar/asm ../ressources/corewar/test2.s && cp ../ressources/corewar/test2.cor . && ./corewar -v 31 test2.cor -d 300
//./corewar -v 4 test2.cor

// 0b 68 01 00 0f 00 01 06 64 01 00 00 00 00 01 01 00 00 00 01 09 ff fb
//sti 68(REG|DIR|DIR) -> 0b 68 01 00 0f 00 01
//ld D0(IND|REG) 90(D4|REG) -> 02 D0 00 10 05
//st 70(REG|IND) 50(REG|REG) -> 03 70 01 00 23
//add 54(REG|REG|REG) -> 04 54 01 02 03
//sub 54(REG|REG|REG) -> 05 54 01 02 03
//and A4(D4|D4|REG) -> 06 A4 FF FF FF FF 00 FF 00 0F 05
//or A4(D4|D4|REG) -> 07 A4 FF FF FF FF 00 FF 00 0F 05
//xor A4(D4|D4|REG) -> 08 A4 FF FF FF FF 00 FF 00 0F 05
