/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   environment.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-kra/tosinga           <jvan-kra/to      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/04 17:45:14 by jvan-kra/     #+#    #+#                 */
/*   Updated: 2022/10/04 17:45:14 by jvan-kra/     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

# define ENV_SEP	"="

char	*ft_getenv(const char *name);
char	**ft_getenviron(void);
char	**ft_getenviron_value(void);
void	ft_setenviron(char **environ);
void	ft_setenv(const char *name, const char *value, int overwrite);
void	ft_unsetenv(const char *name);

#endif
