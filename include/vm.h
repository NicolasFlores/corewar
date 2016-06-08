/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/10 11:41:05 by nflores           #+#    #+#             */
/*   Updated: 2016/05/30 15:48:02 by nflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

/*
** include
*/

# include "../libftprintf/ft_printf.h"
# include "../libftprintf/libft.h"
# include <fcntl.h>

/*
** define
*/

# define IND_SIZE				2
# define REG_SIZE				4
# define DIR_SIZE				REG_SIZE

# define REG_CODE				1
# define DIR_CODE				2
# define IND_CODE				3

# define MAX_ARGS_NUMBER		4
# define MAX_PLAYERS			4
# define MEM_SIZE				(4*1024)
# define IDX_MOD				(MEM_SIZE / 8)
# define CHAMP_MAX_SIZE			(MEM_SIZE / 6)

# define COMMENT_CHAR			'#'
# define LABEL_CHAR				':'
# define DIRECT_CHAR			'%'
# define SEPARATOR_CHAR			','

# define LABEL_CHARS			"abcdefghijklmnopqrstuvwxyz_0123456789"

# define NAME_CMD_STRING		".name"
# define COMMENT_CMD_STRING		".comment"

# define REG_NUMBER				16

# define CYCLE_TO_DIE			1536
# define CYCLE_DELTA			50
# define NBR_LIVE				21
# define MAX_CHECKS				10

# define T_REG					1
# define T_DIR					2
# define T_IND					4
# define T_LAB					8
# define PROG_NAME_LENGTH		(128)
# define COMMENT_LENGTH			(2048)
# define COREWAR_EXEC_MAGIC		0xea83f3

/*
** struct
*/

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
	int					num;
	int					total_size;
	int					prog_size;
	int					reg[REG_NUMBER];
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
	int					cdelta;
	int					cycles;
	int					check;
	int					live;
	int					last_live;
	int					proc;
}						t_vm;

typedef enum			e_partype
{
	NUL,
	REG,
	DIR,
	DIRI,
	IND
}						t_partype;

typedef struct			s_param
{
	int					*reg;
	int					dir;
	short				diri;
	short				ind;
	t_partype			par;
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
	t_partype			par;
	int					num;
	int					pc;
	int					prevpc;
	int					live;
	int					exec;
	int					opc;
	int					wex;
	int					codage;
	int					carry;
	int					reg[REG_NUMBER];
}						t_proc;

typedef struct			s_proc_list
{
	t_proc				*proc;
	struct s_proc_list	*next;
}						t_proc_list;

/*
** function
*/

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
void					ft_game(t_vm *vm, t_champ_list *champ_list, t_opt *opt);
void					get_opc(t_proc_list **lst, t_vm *vm);
void					exec_opc(t_proc_list **lst, t_proc_list **exec_proc,
								t_vm *vm);
void					ft_win(t_vm *vm, t_opt *opt, t_champ_list *champ_list);
void					ft_carry(int val, t_proc **proc);
int						ft_index_value(t_mem *mem, int val, int size, char dir);
void					ft_set_addrind(t_mem *mem, int addr, int *reg);
int						ft_index_value_add(int val);
void					*ft_live(t_vm **vm, t_param_list *lst, t_proc **proc);
void					*ft_ld(t_vm **vm, t_param_list *lst, t_proc **proc);
void					*ft_st(t_vm **vm, t_param_list *lst, t_proc **proc);
void					*ft_add(t_vm **vm, t_param_list *lst, t_proc **proc);
void					*ft_sub(t_vm **vm, t_param_list *lst, t_proc **proc);
void					*ft_and(t_vm **vm, t_param_list *lst, t_proc **proc);
void					*ft_or(t_vm **vm, t_param_list *lst, t_proc **proc);
void					*ft_xor(t_vm **vm, t_param_list *lst, t_proc **proc);
void					*ft_zjmp(t_vm **vm, t_param_list *lst, t_proc **proc);
void					*ft_ldi(t_vm **vm, t_param_list *lst, t_proc **proc);
void					*ft_sti(t_vm **vm, t_param_list *lst, t_proc **proc);
void					*ft_fork(t_vm **vm, t_param_list *lst, t_proc **proc);
void					*ft_lld(t_vm **vm, t_param_list *lst, t_proc **proc);
void					*ft_lldi(t_vm **vm, t_param_list *lst, t_proc **proc);
void					*ft_lfork(t_vm **vm, t_param_list *lst,
								t_proc **proc);
void					*ft_aff(t_vm **vm, t_param_list *lst, t_proc **proc);
int						read_value(t_mem *mem, int addr, int size);
void					write_value(t_mem **mem, int value, int addr,
									t_champ *champ);
int						is_opcode(char oct);
int						nb_param(int opc);
t_partype				param_type(char oct, int num, int opc);
int						param_size(t_partype par);
int						nb_cycles(int opc);
void					set_param(t_mem *mem, t_param *param, t_partype par,
								t_proc *proc);
int						ft_param_erase(t_mem *mem, t_proc *proc);
int						ft_codage_erase(t_mem *mem, t_proc *proc);
int						ft_codage_valid(int opc, char codage);
t_param					*init_param(void);
void					reset_param(t_param_list **lst);
t_param_list			*ft_param_lstnew(void);
void					ft_param_lstadd(t_param_list **lst, t_param_list *new);
void					ft_free_parlst(t_param_list **lst);
t_proc					*init_proc(t_champ *champ, int n);
void					kill_proc(t_vm **vm, t_proc_list **exec_proc);
t_proc_list				*ft_proc_lstnew(t_proc *proc);
void					ft_proc_lstadd(t_proc_list **lst, t_proc_list *new);
void					ft_proc_lstaddend(t_proc_list **lst, t_proc_list *new);
void					ft_remove_proc(t_proc_list **lst, int n);
int						ft_proc_lstsize(t_proc_list *lst);

void					ft_print_mem(t_mem *mem);


#endif
