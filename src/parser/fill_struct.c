#include "ft_sh.h"

void		fill_parser(t_parser *parser, char *original)
{
	int i;
	int o;
	int z;
	int b;
	int boite;
	char stock;
	int j;

	j = 0;
	b = 0;
	z = 0;
	o = 0;
	i = 0;
//	printf("ici fill_parser\n");
	while (original[i])
	{
		while ((original[i] == ' ' || original[i] == '\t') && original[i])
			i++;
		while (original[i] && original[i] != ';' && original[i] != '|')
		{
			while ((original[i] == ' ' || original[i] == '\t') && original[i])
				i++;
			if (original[i] == '\0')
				break;
			while ((original[i] != ' ' && original[i] != '\t' &&
			original[i] != ';' && original[i] != '|') && original[i])
			{
				boite = redirections3(&i, original);
				while ((original[i] == ' ' || original[i] == '\t') && original[i])
					i++;
				stock = checkquote(&i, &o, original);
				if (stock == 'k')
					break;
				if (z >= 0) //sale + gere pas les guillemets
				{
					parser[b].cmd[j][o] = original[i];
				}
				i++;
				o++;
			}
			if (z >= 0 && o != 0)
			{
				parser[b].cmd[j][o] = '\0';
				j++;
			}
			if (original[i] == '\0' || original[i] == ';' || original[i] == '|')
				break ;
			o = 0;
			z++;
		}
		if ((z > 1 || (z == 1 && original[i] == '\0')) && j)
			parser[b].argument[j] = NULL;
		j = 0;
		z = 0;
		if (original[i] == '\0')
			break ;
		if (original[i] == '|')
		{
//			printf("Ya un pipe\n"); //Faut un truc apres
			i++;
			while ((original[i] == ' ' || original[i] == '\t') && original[i])
				i++;
		}
		else
			i++;
		while ((original[i] == ' ' || original[i] == '\t') && original[i])
			i++;
		b++;
	}
//	printf("End\n");
}