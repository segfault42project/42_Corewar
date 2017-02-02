/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 21:32:19 by qhonore           #+#    #+#             */
/*   Updated: 2017/02/02 18:07:06 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	exec_zjmp(t_env *e, t_process *proc)
{
	t_instruction	*inst;

	inst = &(proc->inst);
	if (valid_params(proc) && proc->carry)
	{
		proc->pc = (proc->pc + idx_address(inst->val[0])) % MEM_SIZE;
		if (e->verbose & SHOW_OPERATIONS)
			ft_printf("P%d | zjmp: %d(%d) OK (PC: %d)\n", e->cur_process + 1,\
							inst->val[0], idx_address(inst->val[0]), proc->pc);
	}
	else
	{
		proc->pc += 3;
		if (e->verbose & SHOW_OPERATIONS)
			ft_printf("P%d | zjmp: %d(%d) FAIL (PC: %d)\n", e->cur_process + 1,\
							inst->val[0], idx_address(inst->val[0]), proc->pc);
	}
}

void	exec_ldi(t_env *e, t_process *proc)
{
	uint8_t			reg;
	int32_t			src1;
	int32_t			src2;
	uint32_t		val;
	t_instruction	*inst;

	inst = &(proc->inst);
	if (valid_params(proc))
	{
		src1 = src_param(proc, 1, 0, 1);
		if (proc->inst.param[0] != T_IND)
			src1 = get_address(src1);
		src2 = get_address(src_param(proc, 1, 1, 1));
		val = get_mem_uint32(proc, ((src1 + src2) % IDX_MOD));
		reg = src_param(proc, 0, 2, 0);
		proc->carry = (!val ? 1 : 0);
		proc->reg[reg] = val;
		if (e->verbose & SHOW_OPERATIONS)
			ft_printf("P%d | ldi: %d -> r%d\n | load from %d + %d = %d (PC+IDX: %d)\n", e->cur_process + 1, val, reg + 1, src1, src2, src1 + src2, proc->pc + ((src1 + src2) % IDX_MOD));
	}
}

void	exec_sti(t_env *e, t_process *proc)
{
	uint32_t	reg;
	uint16_t	address;

	if (valid_params(proc))
	{

		reg = src_param(proc, 0, 0, 1);
		proc->carry = (!reg ? 1 : 0);
		address = src_param(proc, 0, 1, 1) + src_param(proc, 0, 2, 1);
		set_mem_uint32(proc, address % IDX_MOD, reg);
		if (e->verbose & SHOW_OPERATIONS)
			ft_printf("P%d | sti: r%d(%d) -> %d (PC+IDX: %d)\n\n",\
						e->cur_process + 1, src_param(proc, 0, 0, 0) + 1, reg,\
						address, proc->pc + (address % IDX_MOD));
	}
}

void	exec_fork(t_env *e, t_process *proc)
{
	uint16_t	pc;

	if (valid_params(proc))
	{
		pc = (proc->pc + src_param(proc, 1, 0, 0)) % MEM_SIZE;
		if (e->verbose & SHOW_OPERATIONS)
			ft_printf("P%d | fork: %d (PC+IDX: %d)\n", e->cur_process + 1,\
									mem_address(src_param(proc, 1, 0, 0)), pc);
		if (e->verbose & SHOW_PC_MOVES)
			pc_moves(proc, 3);
		proc->pc = (proc->pc + 3) % MEM_SIZE;
		init_instruction(&(proc->inst));
		fork_process(e, proc, pc);
	}
}
