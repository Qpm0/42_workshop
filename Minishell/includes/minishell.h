/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpascu <rpascu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 17:14:16 by cmoreanu          #+#    #+#             */
/*   Updated: 2023/10/28 18:25:50 by rpascu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/******************************************************************************
*								INCLUDES								      *
******************************************************************************/

# include "libft.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

/******************************************************************************
*								DEFINES										  *
******************************************************************************/
# define PROMPT "Minishell>"
# define HEREDOC_NAME "/tmp/.miniheredoc"
# define SPACES 1
# define WORD 2
# define VAR 3
# define PIPE 4
# define INPUT 5
# define TRUNC 6
# define HEREDOC 7
# define APPEND 8
# define END 9
# define NORMAL 10
# define SQUOTE 11
# define DQUOTE 12
# define SUCCESS 0
# define FAILURE 1
# define CMD_NOT_FOUND 127
# define CMD_NOT_EXECUTABLE 126
# ifndef PATH_MAX
#  define PATH_MAX 4096
# endif

/******************************************************************************
*							GLOBAL VARIABLE								  	  *
******************************************************************************/
extern int				g_exit_code;

/******************************************************************************
*								STRUCTS										  *
******************************************************************************/
typedef struct s_token
{
	char				*str;
	char				*str_backup;
	bool				var_exists;
	int					type;
	int					status;
	bool				join;
	struct s_token		*prev;
	struct s_token		*next;
}						t_token;
typedef struct s_io_fds
{
	char				*inputfl;
	char				*outputfl;
	char				*heredoc_delimiter;
	bool				heredoc_quotes;
	int					fd_inp;
	int					fd_out;
	int					stdin_backup;
	int					stdout_backup;
}						t_io_fds;
typedef struct s_command
{
	char				*command;
	char				*path;
	char				**args;
	bool				pipe_output;
	int					*pipe_fd;
	t_io_fds			*io_fds;
	struct s_command	*next;
	struct s_command	*prev;
}						t_command;

typedef struct s_tools
{
	t_token				*token;
	char				*input_line;
	char				**env;
	char				*curr_dir;
	char				*curr_dir_old;
	t_command			*cmd;
	pid_t				pid;
}						t_tools;

/******************************************************************************
*								FUNCTIONS								      *
******************************************************************************/

/* ------------------------------- INT --------------------------------------*/

int						termios_change(bool echo_ctl_chr);
int						errmsg_cmd(char *detail, char *error_message,
							char *command, int error_nb);
int						fill_token_list(t_tools *tools, char *str);
int						create_token(int *i, char *str, int start,
							t_tools *tools);
int						check_quotes(int status, char *str, int i);
int						check_character(char *str, int i);
int						save_word(t_token **token_lst, char *str, int index,
							int start);
int						save_token(t_token **token_lst, char *str, int index,
							int type);
int						check_consecutives(t_token **token_lst);
int						check_if_var(t_token **token_lst);
int						var_expander(t_tools *tools, t_token **token_lst);
int						replace_var(t_token **token_node, char *var_value,
							int index);
int						handle_quotes(t_tools *tools);
int						count_len(char *str, int count, int i);
int						var_length(char *str);
int						remove_quotes(t_token **token_node);
int						fill_args(t_token **token_node, t_command *last_cmd);
int						add_args_normal_mode(t_token **token_node,
							t_command *last_cmd);
int						create_args_normal_mode(t_token **token_node,
							t_command *last_cmd);
int						add_args_echo_mode(t_token **token_node,
							t_command *last_cmd);
int						create_args_echo_mode(t_token **token_node,
							t_command *last_cmd);
int						count_args(t_token *temp);
int						env_var_count(char **env);
int						get_env_var_index(char **env, char *var);
int						env_builtin(t_tools *tools, char **args);
int						pwd_builtin(t_tools *tools, char **args);
int						echo_builtin(t_tools *tools, char **args);
int						export_builtin(t_tools *tools, char **args);
int						unset_builtin(t_tools *tools, char **args);
int						cd_builtin(t_tools *tools, char **args);
int						exit_builtin(t_tools *tools);
int						exit_check(t_tools *tools);
int						executor(t_tools *tools);
int						execute_command(t_tools *tools, t_command *cmd);
int						execute_builtin(t_tools *tools, t_command *cmd);
int						check_command_not_found(t_tools *tools, t_command *cmd);

/* ---------------------------- CHAR ----------------------------------------*/

char					*recover_val(t_token *token, char *str, t_tools *tools);
char					*identify_var(char *str);
char					*var_expander_heredoc(t_tools *tools, char *str);
char					*replace_str_heredoc(char *str, char *var_value,
							int index);
char					*get_new_token_string(char *oldstr, char *var_value,
							int newstr_size, int index);
char					*join_vars(t_token **token_node);
char					**copy_in_new_tab(int len, char **new_tab,
							t_command *last_cmd, t_token *tmp);
char					*get_relative_path(char *file_to_open);
char					*get_env_var_value(char **env, char *var);
char					*get_cmd_path(t_tools *tools, char *cmd);

/* ------------------------------ VOID --------------------------------------*/

void					init_io(t_command *cmd);
void					exit_minishell(t_tools *tools, int exno);
void					errmsg(char *errmsg, char *detail, int quotes);
void					free_tools(t_tools *tools, bool clear_history);
void					close_fds(t_command *cmds, bool close_backups);
void					free_io(t_io_fds *io);
void					free_ptr(void *ptr);
void					free_str_array(char **array);
void					lst_add_back_token(t_token **cmdlist,
							t_token *new_node);
void					lstdelone_token(t_token *lst, void (*del)(void *));
void					lstclear_token(t_token **lst, void (*del)(void *));
void					copy_var_value(char *new_str, char *var_value, int *j);
void					copy_var_value(char *new_str, char *var_value, int *j);
void					create_commands(t_tools *tools, t_token *token);
void					create_word(t_command **cmd, t_token **token_lst);
void					remove_empty_var_args(t_token **tokens);
void					lst_add_back_cmd(t_command **cmdlist,
							t_command *new_node);
void					lst_delone_cmd(t_command *lst, void (*del)(void *));
void					lst_clear_cmd(t_command **lst, void (*del)(void *));
void					create_trunc(t_command **last_cmd, t_token **token_lst);
void					create_input(t_command **last_cmd, t_token **token_lst);
void					create_append(t_command **last_cmd,
							t_token **token_lst);
void					create_heredoc(t_tools *tools, t_command **last_cmd,
							t_token **token_lst);
void					create_pipe(t_command **cmd, t_token **token_lst);
void					ignore_sigquit(void);
void					set_signals(void);
void					close_pipe_fds(t_command *cmds, t_command *skip_cmd);

/* ----------------------------- BOOL ---------------------------------------*/

bool					parse_line(t_tools *tools);
bool					is_var_compliant(char c);
bool					init_tools(t_tools *tools, char **env);
bool					quotes_in_string(char *str);
bool					remove_old_file_ref(t_io_fds *io, bool inputfl);
bool					fill_heredoc(t_tools *tools, t_io_fds *io, int fd);
bool					is_valid_env_var_key(char *var);
bool					set_env_var(t_tools *tools, char *key, char *value);
bool					remove_env_var(t_tools *tools, int idx);
bool					cmd_is_dir(char *cmd);
bool					create_pipes(t_tools *tools);
bool					set_pipe_fds(t_command *cmds, t_command *curr_cmd);
bool					check_inputfl_outputfl(t_io_fds *io);
bool					redirect_io(t_io_fds *io);
bool					restore_io(t_io_fds *io);
bool					get_heredoc(t_tools *tools, t_io_fds *io);

/* ----------------------------- T_COMMANDS ---------------------------------*/

t_command				*lst_new_cmd(bool value);
t_command				*lst_last_cmd(t_command *cmd);
t_command				*lst_first_cmd(t_command *cmd);
t_token					*lst_new_token(char *str, char *str_backup, int type,
							int status);
t_token					*insert_lst_between(t_token **head, t_token *to_del,
							t_token *insert);

#endif
