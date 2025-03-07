int is_map_closed(char **map)
{
    int i;
    int j;
    int height;
    int len;

    // Étape 1 : Calculer la hauteur de la carte (nombre de lignes)
    i = 0;
    while (map[i])
        i++;
    height = i;

    // Étape 2 : Examiner chaque ligne pour vérifier les bordures et les caractères
    for (i = 0; i < height; i++)
    {
        len = ft_strlen(map[i]); // Longueur de la ligne actuelle

        for (j = 0; j < len; j++)
        {
            // Si on est sur la bordure de la carte (haut, bas, gauche, droite)
            if (is_on_border(i, j, height, len))
            {
                // Vérifie si les bordures ne contiennent que des murs
                if (map[i][j] != '1')
                    return (0); // Si la bordure n'est pas fermée, retourne 0
            }
            else
            {
                // Vérifie si les caractères internes sont valides ('1', '0', espaces, etc.)
                if (!is_valid_map_char(map[i][j]))
                    return (0); // Si caractère inconnu, retourne 0

                // Vérifie si un espace ou un vide autour de '0' est mal fermé
                if (map[i][j] == '0' && has_invalid_surrounding(map, i, j))
                    return (0); // Retourne 0 si un '0' est mal entouré
            }
        }
    }
    return (1); // Si toutes les conditions sont respectées, la carte est fermée
}