/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 21:32:19 by qhonore           #+#    #+#             */
/*   Updated: 2017/01/27 21:39:15 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	exec_lld(t_env *e, t_process *proc)
{
	uint8_t			reg;
	uint32_t		val;
	t_instruction	*inst;

	inst = &(proc->inst);
	if (valid_params(proc))
	{
		val = src_param(proc, 0, 0, 0);
		reg = src_param(proc, 0, 1, 0);
		proc->carry = (!val ? 1 : 0);
		proc->reg[reg] = val;
		if (e->verbose & SHOW_OPERATIONS)
			ft_printf("P%d | ld: %d -> r%d\n",\
											e->cur_process + 1, val, reg + 1);
	}
}

void	exec_lldi(t_env *e, t_process *proc)
{
	uint8_t			reg;
	uint16_t		address;
	uint32_t		val;
	t_instruction	*inst;

	inst = &(proc->inst);
	if (valid_params(proc))
	{
		address = src_param(proc, 0, 0, 1) + src_param(proc, 0, 1, 1);
		val = get_mem_uint32(proc, address);
		reg = src_param(proc, 0, 2, 0);
		proc->carry = (!val ? 1 : 0);
		proc->reg[reg] = val;
		if (e->verbose & SHOW_OPERATIONS)
			ft_printf("P%d | ldi: %d -> r%d\n", e->cur_process + 1,\
																val, reg + 1);
	}
}

void	exec_lfork(t_env *e, t_process *proc)
{
	uint16_t	pc;

	if (valid_params(proc))
	{
		pc = (proc->pc + src_param(proc, 0, 0, 0)) % MEM_SIZE;
		proc->pc = (proc->pc + 3) % MEM_SIZE;
		init_instruction(&(proc->inst));
		fork_process(e, proc, pc);
		if (e->verbose & SHOW_OPERATIONS)
			ft_printf("P%d | lfork: %d (PC+IDX: %d)\n", e->cur_process + 1,\
														proc->inst.val[0], pc);
	}
}

void	exec_aff(t_env *e, t_process *proc)
{
	uint32_t	val;

	// printf("Exec aff\n");
	(void)e;
	if (valid_params(proc))
	{
		val = src_param(proc, 0, 0, 1);
		proc->carry = (!val ? 1 : 0);
		//A faire
		// printf("Exec aff ok\n");
	}
}