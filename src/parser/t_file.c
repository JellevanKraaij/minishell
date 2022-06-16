#include "minishell.h"
#include "parser.h"
#include "libft.h"

t_file *init_file(void)
{
	t_file *ret;

	ret = null_exit(malloc(sizeof(t_file)));
	ret->name = NULL;
	ret->flag = -1;
	return (ret);
}
t_file *destroy_file(t_file *file)
{
	free(file->name);
	free(file);
	return(NULL);
}

t_file *create_file(char *name, t_fileflags flag)
{
	t_file *ret;

	ret = init_file();
	ret->name = name;
	ret->flag = flag;
	return (ret);
}