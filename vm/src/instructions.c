/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 21:32:19 by qhonore           #+#    #+#             */
/*   Updated: 2017/01/27 21:36:18 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	exec_live(t_env *e, t_process *proc)
{
	uint32_t	val;

	val = src_param(proc, 0, 0, 0);
	if (e->verbose & SHOW_OPERATIONS)
		ft_printf("P%d | live: %d\n", e->cur_process + 1, val);
	if (val >= 1 && val <= e->nb_player)
	{
		e->player[val - 1].live += 1;
		if (e->verbose & SHOW_LIVE)
			ft_printf("Player %d is {:green}alive{:eoc}\n", val);
	}
}

void	exec_ld(t_env *e, t_process *proc)
{
	uint8_t			reg;
	uint32_t		val;
	t_instruction	*inst;

	inst = &(proc->inst);
	if (valid_params(proc))
	{
		val = src_param(proc, 1, 0, 0);
		reg = src_param(proc, 0, 1, 0);
		proc->carry = (!val ? 1 : 0);
		proc->reg[reg] = val;
		if (e->verbose & SHOW_OPERATIONS)
			ft_printf("P%d | ld: %d -> r%d\n",\
											e->cur_process + 1, val, reg + 1);
	}
}

void	exec_st(t_env *e, t_process *proc)
{
	uint32_t		val;
	uint16_t		dest;
	t_instruction	*inst;

	inst = &(proc->inst);
	if (valid_params(proc))
	{
		val = src_param(proc, 0, 0, 1);
		dest = src_param(proc, 1, 1, 0);
		proc->carry = (!val ? 1 : 0);
		if (inst->param[1] == T_IND)
		{
			set_mem_uint32(proc, inst->val[1] % IDX_MOD, val);
			if (e->verbose & SHOW_OPERATIONS)
				ft_printf("P%d | st: r%d(%d) -> %d\n", e->cur_process + 1,\
									inst->val[0], val, inst->val[1] % IDX_MOD);
		}
		else if (inst->param[1] == T_REG)
		{
			proc->reg[dest] = val;
			if (e->verbose & SHOW_OPERATIONS)
				ft_printf("P%d | st: r%d(%d) -> r%d\n", e->cur_process + 1,\
									inst->val[0], val, dest + 1);
		}
	}
}

void	exec_add(t_env *e, t_process *proc)
{
	uint8_t			reg;
	uint32_t		val;
	t_instruction	*inst;

	inst = &(proc->inst);
	if (valid_params(proc))
	{
		reg = src_param(proc, 0, 2, 0);
		val = src_param(proc, 0, 0, 1) + src_param(proc, 0, 1, 1);
		proc->carry = (!val ? 1 : 0);
		proc->reg[reg] = val;
		if (e->verbose & SHOW_OPERATIONS)
			ft_printf("P%d | add: r%d + r%d = (%d) -> r%d\n",\
				e->cur_process + 1, inst->val[0], inst->val[1], val, reg + 1);
	}
}