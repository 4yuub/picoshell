/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakhoudr <yakhoudr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 14:46:58 by yakhoudr          #+#    #+#             */
/*   Updated: 2022/08/03 14:46:58 by yakhoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void execute_pipe(t_pipe_node *_pipe, t_env *env_list)
{
	int	fd[2];
	int	pid;

	if (pipe(fd) < 0)
	{
		perror("pipe");
		exit(1);
	}
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		exit(1);
	}
	if (pid == 0)
	{
		dup2(fd[1], 1);
		close(fd[1]);
		close(fd[0]);
		execute_tree(_pipe->left, env_list);
		exit(1);
	}
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		exit(1);
	}
	if (pid == 0)
	{
		dup2(fd[0], 0);
		close(fd[1]);
		close(fd[0]);
		execute_tree(_pipe->right, env_list);
		exit(1);
	}
	close(fd[1]);
	close(fd[0]);
	waitpid(-1, NULL, 0);
	waitpid(-1, NULL, 0);
}

void apply_redirections(t_redir_node *redir, int *flag)
{
	int fd;

	if (redir->type == EXEC)
		return ;
	apply_redirections((t_redir_node *) redir->sub, flag);
	printf("applied redirection\n");
	if (!*flag)
		return ;
	if (redir->type == HERDOC)
	{
		dup2(redir->fd, 0);
		close(redir->fd);
		return ;
	}
	fd = open(redir->tok->value, redir->flag, 0644);
	if (fd < 0)
	{
		*flag = 0;
		perror(redir->tok->value);
		return ;
	}
	if (redir->type == LESS)
		dup2(fd, 0);
	else
		dup2(fd, 1);
}

t_exec_node	*get_cmd(t_redir_node *node)
{
	while (node->type != EXEC)
	{
		node = (t_redir_node *) node->sub;
	}
	return ((t_exec_node *) node);
}

void execute_redir(t_redir_node *node, t_env *env_list)
{
	t_exec_node *cmd;
	int					flag;

	flag = 1;
	apply_redirections(node, &flag);
	printf("applied redirection\n");
	cmd = NULL;
	if (flag)
		cmd = get_cmd(node);
	execute_tree((t_cmd_tree *) cmd, env_list);
}

int	is_builtin(char *cmd)
{
	if (!strmpd)
}

void	execute_exec(t_exec_node *cmd, t_env *env_list) 
{
	int		i;
	int		id;
	char	**cmd_list;

	cmd_list = malloc(sizeof(char *) * (cmd->args_count + 2));
	cmd_list[0] = cmd->tcmd->value; // get path
	i = 1;
	while (cmd->targs)
	{
		cmd_list[i++] = cmd->targs->value;
		cmd->targs = cmd->targs->next;
	}
	cmd_list[i] = NULL;
	(void) env_list;
	if (!is_builtin(cmd_list[0])) {
		id = fork();
		if (id == 0)
			execvp(*cmd_list, cmd_list);
		else
			wait(NULL);
	}
}

void	execute_tree(t_cmd_tree *tree, t_env *env_list)
{
	if (!tree)
		return ;
	if (tree->type == ORR)
	{
		execute_tree(((t_or_node *)tree)->left, env_list);
		if (g_minishell.exit_status != 0)
			execute_tree(((t_or_node *)tree)->right, env_list);
	}
	else if (tree->type == ANDD)
	{
		execute_tree(((t_and_node *)tree)->left, env_list);
		if (g_minishell.exit_status == 0)
			execute_tree(((t_and_node *)tree)->right, env_list);
	}
	else if (tree->type == PI)
	{
		execute_pipe((t_pipe_node *)tree, env_list);
	}
	else if (tree->type == REDIR)
	{
		execute_redir((t_redir_node *)tree, env_list);
	}
	else if (tree->type == EXEC)
	{
		execute_exec((t_exec_node*)tree, env_list);
	}
}
