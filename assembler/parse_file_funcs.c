#include "asm.h"

void		skip_name_comment(size_t	*count,  char (*contents)[])
{
	size_t 		k;

	k = 0;
	while(k != 4)
	{
		if ((*contents)[(*count)] == '"')
			k++;
		(*count)++;
	}
	while ((*contents)[(*count)] && (*contents)[(*count)] != '\n')
		(*count)++;
}

void		ft_zero_what_left(t_binfile *bin, size_t	*count,  char (*contents)[])
{
	while ((*count) < bin->arg_length)
	{
		(*contents)[(*count)] = '\0';
		(*count)++;
	}
}

int		ft_whitespaces(int c)
{
	if ((c > 8 && c < 14) || c == 32)
		return (1);
	return (0);
}


void		clean_name_comment(t_binfile *bin, char (*contents)[])
{
	size_t		i;
	
	size_t		len;
	size_t		k;
	
	i = 0;
	k = 0;
	len = 0;
	while (i < bin->arg_length)//(i < bin->arg_length)
	{

		if (ft_strncmp(&(*contents)[i], ".name", 5) == 0 ||\
			ft_strncmp(&(*contents)[i], ".comment", 8) == 0)
		{
			len = 0;
			//printf("1==>%c<==1\n", (*contents)[i]);
			while((*contents)[i] && (*contents)[i] != '\n')
			{
				len++;
				i++;
			}
		}
		ft_memmove(&(*contents)[k], &(*contents)[i], len);
		k++;
		i++;
	}
	ft_zero_what_left(bin, &k, contents);
}



void		clean_spaces(t_binfile *bin, char (*contents)[])
{
	bin->arg_length = bin->arg_length;
	(*contents)[0] = (*contents)[0];
	size_t		i;

	size_t		len;
	size_t		k;

	k = 0;

	
	len = 0;

	i = 0;

	// while((*contents)[i])
	// {
	// 	if (ft_whitespaces((*contents)[i]) && (*contents)[i] != '\n')
	// 	{
	// 		// printf("okoko\n");
	// 		len = 0;
	// 		while(ft_whitespaces((*contents)[i]) && (*contents)[i] != '\n')
	// 		{
	// 			len++;
	// 			i++;
	// 		}
			

	// 	}
	// 	ft_memmove(&(*contents)[k], &(*contents)[i], len);
	// 	k++;
	// 	i++;
	// }



	// k = 0;

	
	// len = 0;

	// i = 0;

	// while((*contents)[i])
	// {
	// 	if (i == 0 && (*contents)[i])
	// 	{
	// 		while((*contents)[i] != '\n')
	// 			i++;
	// 	}
	// 	if ((*contents)[i] == '\n' && (*contents)[i + 1] == '\n')
	// 	{
	// 		// printf("okoko\n");
	// 		// len = 0;
	// 		// while((*contents)[i] == '\n' )
	// 		// {
	// 		// 	len++;
	// 		// 	i++;
	// 		// }
	// 		ft_memmove(&(*contents)[i], &(*contents)[i + 1], 1);
	// 	}
		
	// 	// k++;
	// 	i++;
	// }


	//ft_zero_what_left(bin, &k, contents);

	// void	ft_space(char (*f)[], int len)
	// {
	// 	int i;
	// 	int j;

	// 	i = -1;
	// 	j = 0;
	// 	while ((*f)[++i])
	// 	{
	// 		while ((*f)[i] != '\n' && ft_isspace((*f)[i]))
	// 			++i;
	// 		if (j > 0 && (*f)[j - 1] != '\n' && i > 0 && ft_isspace((*f)[i - 1]))
	// 			(*f)[j++] = ' ';
	// 		if ((*f)[i] && ((*f)[i] == '\n' || !ft_isspace((*f)[i])))
	// 			(*f)[j++] = (*f)[i];
	// 	}
	// 	while (j < len)
	// 		(*f)[j++] = '\0';
	// }
}

void 		parse_file(t_binfile *bin, char (*contents)[]) //cleaning from  comments and extra lines
{
	size_t		i;

	size_t		len;
	size_t		k;

	k = 0;

	
	len = 0;

	i = 0;
	
	//printf("here\n");
	//skip_name_comment(&i, contents);

	k = 0;
	while (i < bin->arg_length)//(i < bin->arg_length)
	{
		if ((*contents)[i] == '#')
		{
			len = 0;
			//printf("1==>%c<==1\n", (*contents)[i]);
			while((*contents)[i] && (*contents)[i] != '\n')
			{
				len++;
				i++;
			}
		}
		ft_memmove(&(*contents)[k], &(*contents)[i], len);
		k++;
		i++;
	}
	ft_zero_what_left(bin, &k, contents);
	clean_spaces(bin, contents);

	i = 0;
	k = 0;
	len = 0;
	// while ((*contents)[i] == '\n')
	// 	i++;
	// while ((*contents)[i])//(i < bin->arg_length)
	// {
		
	// }
	//ft_zero_what_left(bin, &k, contents);




		// int i;
		// int j;

		// i = 0;
		// j = 0;
		// while ((*f)[i])
		// {
		// 	if (i == 0)
		// 		while ((*f)[i] == '\n')
		// 			++i;
		// 	if ((*f)[i] == '\n')
		// 		while ((*f)[i + 1] == '\n')
		// 			++i;
		// 	if (!(*f)[i])
		// 		return ;
		// 	(*f)[j++] = (*f)[i++];
		// }
		// while (j < len)
		// 	(*f)[j++] = '\0';

	//skip_name_comment(&i, contents);
	// printf("yooo [[%lu]]", k);
	// printf("[%s]<+=======\n", contents);
}