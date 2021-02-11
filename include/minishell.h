/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 19:56:18 by mvan-eyn          #+#    #+#             */
/*   Updated: 2021/01/31 19:39:40 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../utils/libft/include/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include <sys/types.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>
# include <limits.h>
# include <unistd.h>
# include <fcntl.h>

# define MAX_LLONG "9223372036854775807"
# define MAX_LLONG_NEG "9223372036854775808"

typedef struct	s_data
{
	t_list	*tokens;
	t_list	*full_env;
	int		is_colon;
	int		has_been_trad;
	int		is_pipe;
	int		is_redir;
	int		was_pipe;
	int		stdout_cpy;
	int		stdin_cpy;
	int		is_input;
	int		is_no_path;
	pid_t	pid1;
	pid_t	pid2;
	char	*env_after_egal;
	char	*new_str;
	char	*parsed_var;
	char	*token;
	char	*pipeline;
	char	*redir_line;
	char	*line;
	char	*perm_all;
	char	*perm_owner;
	char	*perm_octal;
	char	**token_array;
	char	**bin_array;
	char	**env_array;
}				t_data;

/*
*** PARSING
*/

char			*ft_program(char *line, t_data *data);
char			*ft_parser(char *line, t_data *data);
char			*add_sq(char *token, char *line, int *i);
char			*add_dq(char *str, char *line, int *i);
int				check_pipes(char *line);
int				check_redirection(char *line);
int				count_redirection_right(char *line);
int				count_redirection_left(char *line);
int				ft_increment(int *i, char *line, char c);
char			*ft_parse_pipe(t_data *data, char *line, int i, char *token);
char			*get_before_semicolon(char *line);
int				ft_check_surround_2(char *token, int pos);
int				check_line(char *line);
int				check_semicolon_pipe(char *line);

/*
*** TRADUCTION
*/

void			ft_traduction(t_data *data);
char			*handle_dollar(t_data *data, char *token);
char			*ft_parse_token(char *token, int *i);
int				check_sq_right(char *token, int pos);
int				check_sq_left(char *token, int pos);
int				check_dq_right(char *token, int pos);
int				check_dq_left(char *token, int pos);
char			*handle_quotes(char *token);
char			*handle_backslash(char *token);
char			*handle_tilde(t_data *data, char *token);
int				ft_check_surround(char *token, int pos);
char			*check_space_dq(char *env_after_egal, char *token,
					int pos, int len);
char			*check_and_add(char *env_after_egal, int pos, int len,
					char *token);
char			*ft_parse_token(char *token, int *i);

/*
*** BUILTINS
*/

int				cmd_dispatch(t_data *data);
int				ft_echo(t_data *index);
int				ft_cd(t_data *data);
int				ft_pwd(t_data *data);
int				ft_env(t_data *data);
void			save_shlvl(t_data *data, int lvl);
int				ft_export(t_data *data);
char			*get_str_to_print(t_list *temp_env, char *str_to_print, int *i);
int				check_if_valid(char *token);
int				check_entry(t_data *data, char *token);
int				ft_unset(t_data *data);
int				ft_exit(t_data *data);
int				ft_bin(t_data *data);

/*
*** PATH
*/

int				ft_path(t_data *data, char *path);
int				check_if_bin(char *token);
char			*fill_temp(t_data *data, t_list *temp_token, char *temp, int i);
int				check_slash_path(char *token);
int				check_if_bin(char *token);
void			set_errno(int status);
char			*is_no_path(char **path_array);
void			bin_end(t_data *data, char *temp);
int				ft_execve(t_data *data, char *path_bin, char **token_array,
	char **env_array);
char			**path_sub_bin(t_data *data, char *token);
char			**fill_token_array(t_list *token);
char			**fill_array_env(t_data *data);

/*
*** PIPE
*/

int				ft_pipe(t_data *data, char *str);
int				ft_pipe_bin(t_data *data, char *path_bin,
					char **token_array, char **env_array);

/*
*** REDIRECTION
*/

int				ft_redir(t_data *data);
int				dispatch_redir(char *token);
int				delete_redir_tokens(t_data *data, char *token);
char			*isolate_file_name(t_data *data);
char			*check_redir_line(char *redir_line);
int				ft_delete_and_free(t_data *data, t_list *temp_token);
void			ft_manage_dup(int fd, t_data *data);
int				ft_fd_create(t_list *token_file_name, t_data *data);
int				ft_error_delete(t_data *data, int i, t_list *token_file_name);
int				check_perm(struct stat infos);

/*
*** ERRORS
*/

int				ft_errors(t_data *data, int code);
int				ft_errors_export(char *error);
int				ft_error_export(char *token);
int				ft_errors_unset(char *token);
int				ft_error_exit(t_data *data, int status);
int				ft_errors_cd(t_data *data, int code);
int				ft_errors_path(char *token, char *path);
int				ft_errors_directory(char *token);
int				ft_errors_line(char c);
int				ft_errors_line2(char *line);
int				ft_errors_dispatch(t_data *data, int code, char *str);
int				error_no_such_file(char *str);
int				error_redir(void);
char			*ft_error_eof(char c, char *new_str);

/*
*** FREE
*/

void			free_array(char **array);
void			free_list(t_data *data);
void			free_env(t_data *data);
char			*free_return_null(char *line);
void			free_perm(char *perm_all, char *perm_owner, char *perm_octal);
void			free_bin(char **bin_array, char **token_array,
					char **env_array);
void			free_norme(t_data *data, char *temp);

/*
*** SIGNALS
*/

void			ft_signal(int sig_code, void *ptr);
void			ft_signal_2(int sig_code, void *ptr);

/*
*** TOOLS
*/

char			*add_char(char *str, char c);
void			save_env_lst(t_data *data, char **envp);
char			*get_env_after_egal(char *env_line);
int				check_int_valid(char *nbr);
char			*parse_nbr(char *nbr);
int				is_numeric(char *str);
char			*remove_last_space(char *str);
char			*check_backslash(char *env_after_egal);
int				count_words(char *str);
char			*change_to_octal(int dec);
void			save_underscore(t_data *data, char *token);
int				is_empty_str(char *str);
char			*get_value_env(t_data *data, char *var);
char			*ft_strjoin_free(char *s1, char *s2);
char			*ft_strjoin_free_all(char *s1, char *s2);
int				is_before(char *token, int pos, char c);
char			*add_char_split(char *str, char c);
int				ft_free_int(char *parsed_nbr, int i);
int				ft_is_neg(int is_neg, char *nbr);
int				check_int_valid(char *nbr);

/*
*** TEST
*/

int				ft_test(t_data *data, char *line);
void			print_list(t_list *list);

#endif
