int	ft_env(t_infos *infos, t_exec *exec)
{
	t_env	*tmp;

	tmp = infos->env;
	if (exec->cmd_array[1])
	{
		ft_putstr_fd("pouetsh: env: too many arguments", 2);
		sig_global = EXIT_FAILURE;
		return (EXIT_FAILURE);
	}
	while (tmp)
	{
		if (env->key)
		{
			
		}
	}
}
