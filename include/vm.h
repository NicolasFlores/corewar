/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/10 11:41:05 by nflores           #+#    #+#             */
/*   Updated: 2016/05/27 14:23:44 by nflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include "../libftprintf/ft_printf.h"
# include "../libftprintf/libft.h"
# include "op.h"
# include <fcntl.h>

typedef struct			s_reg
{
	int					size;
	int					value;
}						t_reg;

typedef struct			s_champ
{
	char				*name;
	char				*comment;
	char				*prog;
	int					pc;
	int					carry;
	int					num;
	int					total_size;
	int					prog_size;
	t_reg				reg[REG_NUMBER];
}						t_champ;

typedef struct			s_champ_list
{
	t_champ				*champ;
	struct s_champ_list	*next;
}						t_champ_list;

typedef struct			s_opt
{
	int					set;
	int					opt_d;
	int					opt_n;
	int					n_d;
	int					n_n;
}						t_opt;

typedef struct			s_mem
{
	char				oct;
	int					n;
	int					champ_own;
	int					champ_wr;
	struct s_mem		*next;
	struct s_mem		*prev;
}						t_mem;

typedef struct			s_vm
{
	t_mem				*mem;
	t_champ_list		*champ_list;
	int					ctd;
	int					cycles;
	int					check;
	int					live;
	int					last_live;
	int					proc;
}						t_vm;

typedef struct			s_param
{
	t_reg				*reg;
	int					dir;
	int					ind;
}						t_param;

typedef struct			s_param_list
{
	t_param				*param;
	struct s_param_list	*next;
}						t_param_list;

typedef struct			s_proc
{
	t_champ				*champ;
	t_param_list		*par_list;
	int					pc;
	int					live;
	int					size;
	int					exec;
}						t_proc;

typedef enum			e_partype
{
	NUL,
	REG,
	DIR,
	DIRI,
	IND
}						t_partype;

int						get_opt(t_opt **opt, int argc, char **argv);
int						check_arg(char **buf, char *arg);
t_champ_list			*ft_champ_lstnew(t_champ *new);
void					ft_champ_lstadd(t_champ_list **lst, t_champ_list *new);
int						ft_champ_lstsize(t_champ_list *lst);
t_champ					*ft_newchamp(char *name, char *comment, int t_size,
									int pr_size);
void					init_champ(char **argv, int i,
								t_champ_list **champ_list, t_opt *opt);
void					ft_print_contest(t_champ_list *champ_list);
void					ft_meminit(t_mem **mem, int size);
void					ft_gameinit(t_mem **mem, t_champ_list *lst,
									int nb_champ);
t_vm					*init_vm(t_mem *mem, t_champ_list *lst);
void					ft_game(t_vm *vm, t_champ_list *champ_list);
int						ft_live(t_vm **vm, t_param_list *lst, int codage,
								t_proc **proc);
int						ft_ld(t_vm **vm, t_param_list *lst, int codage,
							t_proc **proc);
int						ft_st(t_vm **vm, t_param_list *lst, int codage,
							t_proc **proc);
int						ft_add(t_vm **vm, t_param_list *lst, int codage,
							t_proc **proc);
int						ft_sub(t_vm **vm, t_param_list *lst, int codage,
							t_proc **proc);
int						ft_and(t_vm **vm, t_param_list *lst, int codage,
							t_proc **proc);
int						ft_or(t_vm **vm, t_param_list *lst, int codage,
							t_proc **proc);
int						ft_xor(t_vm **vm, t_param_list *lst, int codage,
							t_proc **proc);
int						ft_zjmp(t_vm **vm, t_param_list *lst, int codage,
								t_proc **proc);
int						ft_ldi(t_vm **vm, t_param_list *lst, int codage,
							t_proc **proc);
int						ft_sti(t_vm **vm, t_param_list *lst, int codage,
							t_proc **proc);
int						ft_fork(t_vm **vm, t_param_list *lst, int codage,
								t_proc **proc);
int						ft_lld(t_vm **vm, t_param_list *lst, int codage,
							t_proc **proc);
int						ft_lldi(t_vm **vm, t_param_list *lst, int codage,
								t_proc **proc);
int						ft_lfork(t_vm **vm, t_param_list *lst,
								int codage, t_proc **proc);
int						ft_aff(t_vm **vm, t_param_list *lst, int codage,
							t_proc **proc);
int						read_value(t_mem *mem, int addr, int size);
void					write_value(t_mem **mem, int value, int addr, t_champ *champ);
int						is_opcode(char oct);
int						nb_param(int opc);
t_partype				param_type(char oct, int num, int opc);
int						param_size(t_partype par);
int						nb_cycles(int opc);
void					set_param(t_mem *mem, t_param *param, t_partype par,
								t_proc *proc);
t_param					*init_param(void);
void					reset_param(t_param_list **lst);
t_param_list			*ft_param_lstnew(void);
void					ft_param_lstadd(t_param_list **lst, t_param_list *new);
void					ft_free_parlst(t_param_list **lst);

//debug

void	ft_print_mem(t_mem *mem);

#endif