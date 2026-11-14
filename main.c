/*
El archivo ejecutor. Funciona con argumentos, asi que validamos las
2 formas diferntes de poder pasar la información por terminal
ej:
$> ./rush-02 42
$> ./rush-02 nuevo_diccionario 42
la forma de 3 argumentos es para el extra, que no esta por ahora
*/
#include "rush02.h"

int	main(int argc, char **argv)
{
	t_dict	dict;
	char	*path;
	char	*nb;

	if (argc < 2 || argc > 3 || !is_number(argv[argc - 1]))
	{
		ft_putstr("Error\n");
		return (1);
	}
	path = "numbers.dict";
	if (argc == 3)
		path = argv[1];
	nb = skip_zeros(argv[argc - 1]);
	if (!load_dict(&dict, path) || !convert(&dict, nb))
	{
		ft_putstr("Dict Error\n");
		free_dict(&dict);
		return (1);
	}
	free_dict(&dict);
	return (0);
}
