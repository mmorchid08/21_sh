#include "ft_readline.h"

void	ft_free_line(t_line **head)
{
	t_line *tmp;

	while (*head)
	{
		ft_free_table(&((*head)->com.args));
		ft_free_var(&((*head)->com.var));
		ft_strdel(&((*head)->com.param));
		if ((*head)->path)
			ft_strdel(&((*head)->path));
		tmp = (*head)->next;
		free(*head);
		*head = tmp;
	}
}

void	ft_free_table(char ***table)
{
	int i;

	i = -1;
	while ((*table)[++i])
		free((*table)[i]);
	free((*table));
}

void	ft_exec_exit(void)
{
	if (g_env.current_pid > 0)
		kill(g_env.current_pid, 0);
	else if (g_env.running_proc && g_env.current_pid == 0)
		exit(0);
	ft_free_env();
	exit(0);
}