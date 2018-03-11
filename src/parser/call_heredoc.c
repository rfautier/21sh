#include "parser.h"

static int size_str(t_vari var, char *original)
{
	int nb;

	nb = 0;
	while (original[var.i] && (original[var.i] != ' ' && original[var.i] != '\t'))
	{
		var.i++;
		nb++;
	}
	return (nb);
}


void	call_heredoc(t_vari var, char *original)
{
	int size;
	char *str;
	int o;
	char *tmp = NULL;
	char *path_file;
	int fd;

	o = 0;
	size = size_str(var, original);
	str = malloc(sizeof(char) * size + 1);
	printf("heredoc i = %d\n", var.i);
	while (original[var.i] && (original[var.i] != ' ' && original[var.i] != '\t'))
	{
		str[o] = original[var.i];
		var.i++;
		o++;
	}
	str[o] = '\0';
	printf("str = %s\n", str);
	//tmp = read_command("heredoc>", NULL, 1);
	tmp = "lol";
	printf("tmp = %s\n", tmp);
	path_file = ft_strjoin("/tmp/heredoc", ft_itoa(var.heredoc));
	printf("path_file = %s\n", path_file);
	if ((fd = open(path_file,  O_RDWR | O_CREAT | O_EXCL | O_APPEND, 0777)) == -1)
	{
		printf("FILE EXIST\n");
		if ((fd = open(path_file, O_WRONLY | O_TRUNC, 0777)) == -1)
		{
			printf("Echap\n");
			exit(0);
		}
		close(fd);
		if ((fd = open(path_file,  O_RDWR | O_APPEND, 0777)) == -1)
			exit(0);
	}
	printf("c creer !\n");
	free(path_file);
	while (ft_strcmp(str, tmp) != 0)
	{
		printf("tmp2 = %s\n", tmp);
		ft_fprintf(fd, tmp);
		tmp = "yo";
		//tmp = read_command("heredoc>", NULL, 1);		
		//free(tmp);
	}
	free(str);
	close(fd);
	printf("finish !\n");
}