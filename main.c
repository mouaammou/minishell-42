/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 00:10:16 by mouaammo          #+#    #+#             */
/*   Updated: 2023/07/04 18:14:48 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execution(t_list_env *m_export,
	t_voidlst *commands, t_list_env *new_env)
{
	char	*tty;
	int		fd;

	if (ttyname(0))
		ft_pipe(&m_export, commands, &new_env);
	else
	{
		tty = ttyname(1);
		fd = open(tty, O_RDONLY);
		dup2(fd, 0);
	}
}

void	signals(void)
{
	signal(SIGINT, &handle_interrupt);
	signal(SIGQUIT, &handle_interrupt);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGUSR1, &handler);
}

void	init_global(void)
{
	g_global_exit.flag = 1;
	g_global_exit.heredoc = 0;
	rl_catch_signals = 0;
	g_global_exit.exit = 0;
}

void	minishell(t_list_env *m_export,
	t_voidlst *commands, t_list_env *new_env)
{
	t_list		*head;
	char		*cmd;

	while (1)
	{		
		init_global();
		head = NULL;
		signals();
		cmd = readline("\033[6;32mminishell>> \033[0m");
		if (!cmd)
		{
			write(1, "exit\n", 5);
			exit(g_global_exit.exit_status);
		}
		signal(SIGINT, &handle_interrupt);
		if (cmd != NULL && *cmd != '\0')
			add_history(cmd);
		commands = tokenizer_and_grammar(cmd, head, new_env);
		if (!commands)
			continue ;
		commands = parse_to_args(commands);
		execution(m_export, commands, new_env);
		free_commands(commands);
	}
}

int	main(int ac, char **av, char **env)
{
	t_list_env	*new_env;
	t_list_env	*m_export;
	t_voidlst	*commands;

	(void)ac;
	(void)av;
	commands = NULL;
	new_env = get_env(env);
	m_export = env_dup(new_env);
	sort_list(m_export);
	init_glob(&g_global_exit);
	minishell(m_export, commands, new_env);
	free_envs(m_export, commands, new_env);
	return (0);
}
// export test="file1 file2" >hey >$test
