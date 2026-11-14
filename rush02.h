
#ifndef RUSH02_H
# define RUSH02_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

typedef struct s_entry
{
	char	*key;
	char	*value;
}	t_entry;

typedef struct s_dict
{
	char	*text;
	t_entry	*entries;
	int		size;
	int		print;
	int		first;
}	t_dict;

int		ft_strlen(char *str);
int		ft_strcmp(char *s1, char *s2);
void	ft_putstr(char *str);
int		is_number(char *str);
char	*skip_zeros(char *str);
char	*read_file(char *path);
int		load_dict(t_dict *dict, char *path);
int		say_word(t_dict *dict, char *key);
int		say_digits(t_dict *dict, char a, char b);
int		say_scale(t_dict *dict, int zeros);
void	free_dict(t_dict *dict);
int		convert(t_dict *dict, char *nb);

#endif
