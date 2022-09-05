#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

# define ENV_SEP	"="

char	*ft_getenv(const char *name);
char	**ft_getenviron(void);
void	ft_setenviron(char **environ);
void	ft_setenv(const char *name, const char *value, int overwrite);
void	ft_unsetenv(const char *name);

#endif
