/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 19:37:31 by tlebon            #+#    #+#             */
/*   Updated: 2024/11/25 18:58:34 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Returns the path where we want to go with cd:
// HOME if ~ or nothing
// OLDPWD if -
// path is path
static char	*expand_path(t_env *s_env, char *path, int *print_pwd)
{
	char	*expanded_path;

	if (path == NULL || ft_strncmp(path, "~", ft_strlen(path)) == 0)
	{
		expanded_path = get_env_str(s_env, "HOME"); // Ajouter gestion erreur si HOME unset
		printf("Path found by get_env_str = %s\n", expanded_path);
	}
	else if (ft_strncmp(path, "-", 1) == 0)
	{
		expanded_path = get_env_str(s_env, "OLDPWD"); // Ajouter gestion erreur si OLDPWD unset
		*print_pwd = 1;
	}
	else
		expanded_path = path;
	return (expanded_path);
}

static int	path_exists(char *path)
{
	ft_putstr_fd("checking existence of:", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd("\n", 2);
	if (!opendir(path))
	{
		perror("opendir");
		return (0);
	}
	// Fermer le DIR
	return (1);
}

static int	cd_env_update(t_env **s_env, char *name, char *value, char ***env_pt)
{
	char	*tmp;
	
	if (!env_extractor(name, *s_env))
		return (0);
	tmp = ft_strjoin("=", value);	
	if (!tmp)
		return (2);
	update_env(s_env, name, tmp, env_pt);
	free(tmp);
	return (0);
}
// Check si il y a des subtilitees dans le comportement de cd dans bash
// Uses chdir to change the working directory to the path pointed to by path
// ttention SEGFAULT si OLDPWD est unset ???
// Attention SEGFAULT dans cas suivant : mkdir a --> cd a --> mkdir b --> cd b
// Si en etant dans b on supprime a : cd .. lance une erreur mais le 2eme appel a cd ..
// doit revenir effectivement en arriere soit au repertoire de base
int	exec_cd(char **cmd_tab, t_env **s_env, char ***env_pt)
{
	char	*path;
	char	*bfcd_cwd;
	int		print_pwd;

	print_pwd = 0;
	path = expand_path(*s_env, cmd_tab[1], &print_pwd);
	bfcd_cwd = getcwd(NULL, 0);
	if (chdir(path) != 0)
	{
		perror("cd");
		return (1);
	}
	path = getcwd(NULL, 0);
	if (!path) // A revoir pour renvoyer les bonnes erreurs
	{	
		perror("getcwd");
		return (2);
	}
	if (cd_env_update(s_env, "PWD", path, env_pt) != 0)
	{
		free(path);
		return (3);
	}
	free(path);
	if (cd_env_update(s_env, "OLDPWD", bfcd_cwd, env_pt) != 0)
		return (3);
	if (print_pwd)
		exec_pwd(*s_env);
	free(bfcd_cwd);
	return (0);
}
// Old not so working function
// int	exec_cd(char **cmd_tab, t_env **s_env, char ***env_pt)
// {
// 	char	*path;
// 	char	*old_pwd;
// 	int		print_pwd;

// 	print_pwd = 0;
// 	path = expand_path(*s_env, cmd_tab[1], &print_pwd);
// 	old_pwd = getcwd(NULL, 0);
// 	if (!old_pwd)
// 		perror("getcwd");
// 	if (chdir(path) != 0)
// 	{
// 		perror("cd");
// 		return (1);
// 	}
// 	path = getcwd(NULL, 0);
// 	if (!path) // A revoir pour renvoyer les bonnes erreurs
// 		return (2);
// 	if (cd_env_update(s_env, "PWD", path, env_pt) != 0)
// 	{
// 		free(path);
// 		return (3);
// 	}
// 	free(path);
// 	if (cd_env_update(s_env, "OLDPWD", old_pwd, env_pt) != 0)
// 		return (3);
// 	if (print_pwd)
// 		exec_pwd(*s_env);
// 	free(old_pwd);
// 	return (0);
// }




// Solution propose par chat gpt : Utiliser stat pour verifier si le dossier cible existe bien
// Voir ci dessous



// #include <stdio.h>
// #include <unistd.h>
// #include <errno.h>
// #include <string.h>
// #include <sys/stat.h>

// // Fonction qui vérifie si le répertoire existe réellement
// int directory_exists(const char *path) {
//     struct stat sb;
//     return (stat(path, &sb) == 0 && S_ISDIR(sb.st_mode));
// }

// int main() {
//     // Tente de changer de répertoire vers ".."
//     if (!directory_exists("..")) {
//         // Si le répertoire parent n'existe pas
//         fprintf(stderr, "bash: cd: ..: No such file or directory\n");
//         return 1;  // Retourne une erreur
//     }

//     // Si le répertoire existe, on effectue le changement de répertoire
//     if (chdir("..") == -1) {
//         // Si chdir échoue pour une autre raison
//         fprintf(stderr, "bash: cd: ..: %s\n", strerror(errno));
//         return 1;  // Retourne une erreur
//     }

//     // Si chdir réussit, on peut afficher le répertoire courant
//     char cwd[1024];
//     if (getcwd(cwd, sizeof(cwd)) != NULL) {
//         printf("Répertoire courant: %s\n", cwd);
//     } else {
//         perror("Erreur lors de l'obtention du répertoire courant");
//     }

//     return 0;
// }
