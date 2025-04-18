/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_fdf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 10:00:00 by user42            #+#    #+#             */
/*   Updated: 2025/04/16 10:00:00 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>

// Structure pour stocker les fichiers ouverts pour les suivre
typedef struct s_fd_tracker
{
    int     fd;
    char    *filename;
    int     line;
} t_fd_tracker;

#define MAX_TRACKED_FDS 100
t_fd_tracker g_tracked_fds[MAX_TRACKED_FDS];
int g_fd_count = 0;

// Fonction pour traquer l'ouverture d'un fichier
int track_open(const char *filename, int flags, int line)
{
    int fd = open(filename, flags);
    
    if (fd != -1 && g_fd_count < MAX_TRACKED_FDS)
    {
        g_tracked_fds[g_fd_count].fd = fd;
        g_tracked_fds[g_fd_count].filename = strdup(filename);
        g_tracked_fds[g_fd_count].line = line;
        g_fd_count++;
        printf("Ouverture du FD %d: %s (ligne %d)\n", fd, filename, line);
    }
    else if (fd == -1)
    {
        printf("ERREUR: Échec d'ouverture de %s (ligne %d): %s\n", 
               filename, line, strerror(errno));
    }
    
    return fd;
}

// Fonction pour traquer la fermeture d'un fichier
int track_close(int fd, int line)
{
    int result = close(fd);
    int found = 0;
    
    if (result == 0)
    {
        for (int i = 0; i < g_fd_count; i++)
        {
            if (g_tracked_fds[i].fd == fd)
            {
                printf("Fermeture du FD %d: %s (ligne %d)\n", 
                       fd, g_tracked_fds[i].filename, line);
                free(g_tracked_fds[i].filename);
                // Déplacer les éléments pour remplir le trou
                for (int j = i; j < g_fd_count - 1; j++)
                {
                    g_tracked_fds[j] = g_tracked_fds[j + 1];
                }
                g_fd_count--;
                found = 1;
                break;
            }
        }
        
        if (!found)
        {
            printf("ATTENTION: Fermeture d'un FD %d non tracké (ligne %d)\n", fd, line);
        }
    }
    else
    {
        printf("ERREUR: Échec de fermeture du FD %d (ligne %d): %s\n", 
               fd, line, strerror(errno));
    }
    
    return result;
}

// Macro pour simplifier l'appel à track_open et track_close
#define OPEN(filename, flags) track_open(filename, flags, __LINE__)
#define CLOSE(fd) track_close(fd, __LINE__)

// Rapport des FDs qui n'ont pas été fermés
void report_leaked_fds(void)
{
    if (g_fd_count > 0)
    {
        printf("\n=== FUITE DE DESCRIPTEURS DE FICHIERS DÉTECTÉE ===\n");
        for (int i = 0; i < g_fd_count; i++)
        {
            printf("FD %d non fermé: %s (ouvert à la ligne %d)\n", 
                   g_tracked_fds[i].fd, g_tracked_fds[i].filename, g_tracked_fds[i].line);
            // On ferme les FDs qui fuient pour éviter de vraies fuites
            close(g_tracked_fds[i].fd);
            free(g_tracked_fds[i].filename);
        }
        g_fd_count = 0;
    }
    else
    {
        printf("\n=== AUCUNE FUITE DE DESCRIPTEURS DE FICHIERS ===\n");
    }
}

// Fonction de test pour le parsing de lignes FDF
void test_line_parsing(const char *line)
{
    printf("\nTest de parsing pour: \"%s\"\n", line);
    
    // Simulation d'un split basique sur les espaces
    char *line_copy = strdup(line);
    if (!line_copy)
    {
        printf("ERREUR: Échec d'allocation mémoire\n");
        return;
    }
    
    int count = 0;
    char **tokens = NULL;
    char *token = strtok(line_copy, " \t");
    
    while (token)
    {
        char **temp = realloc(tokens, sizeof(char *) * (count + 1));
        if (!temp)
        {
            printf("ERREUR: Échec d'allocation mémoire pour les tokens\n");
            free(line_copy);
            for (int i = 0; i < count; i++)
                free(tokens[i]);
            free(tokens);
            return;
        }
        tokens = temp;
        tokens[count] = strdup(token);
        if (!tokens[count])
        {
            printf("ERREUR: Échec d'allocation mémoire pour token[%d]\n", count);
            free(line_copy);
            for (int i = 0; i < count; i++)
                free(tokens[i]);
            free(tokens);
            return;
        }
        count++;
        token = strtok(NULL, " \t");
    }
    
    printf("Nombre d'éléments après split: %d\n", count);
    printf("Éléments:\n");
    for (int i = 0; i < count; i++)
    {
        // Analyse de chaque token pour vérifier s'il contient une valeur valide
        char *value_str = tokens[i];
        char *color_str = NULL;
        
        // Recherche de la couleur (format '0xRRGGBB')
        char *color_sep = strchr(tokens[i], ',');
        if (color_sep)
        {
            *color_sep = '\0';  // Séparer la valeur et la couleur
            color_str = color_sep + 1;
        }
        
        // Conversion de la valeur
        char *endptr;
        long value = strtol(value_str, &endptr, 10);
        
        if (*endptr != '\0')
        {
            printf("  [%d]: \"%s\" - ERREUR: Valeur non valide\n", i, tokens[i]);
        }
        else if (color_str)
        {
            // Si une couleur est spécifiée, vérifier si elle est au format 0xRRGGBB
            if (strncmp(color_str, "0x", 2) == 0 && strlen(color_str) == 8)
            {
                // Tester la conversion hexadécimale
                long color = strtol(color_str, &endptr, 16);
                if (*endptr != '\0')
                {
                    printf("  [%d]: \"%s,%s\" - Valeur: %ld, Couleur: Format invalide\n", 
                           i, value_str, color_str, value);
                }
                else
                {
                    printf("  [%d]: \"%s,%s\" - Valeur: %ld, Couleur: 0x%06lX\n", 
                           i, value_str, color_str, value, color);
                }
            }
            else
            {
                printf("  [%d]: \"%s,%s\" - Valeur: %ld, Couleur: Format invalide\n", 
                       i, value_str, color_str, value);
            }
        }
        else
        {
            printf("  [%d]: \"%s\" - Valeur: %ld\n", i, tokens[i], value);
        }
    }
    
    // Libération de la mémoire
    for (int i = 0; i < count; i++)
        free(tokens[i]);
    free(tokens);
    free(line_copy);
}

// Test d'erreurs de fichier
void test_file_errors(void)
{
    printf("\n=== TEST DES ERREURS DE FICHIER ===\n");
    
    // Test avec un fichier qui n'existe pas
    int fd = OPEN("fichier_inexistant.fdf", O_RDONLY);
    if (fd != -1)
        CLOSE(fd);
    
    // Test avec un fichier sans droits d'accès
    FILE *tmp = fopen("test_no_access.fdf", "w");
    if (tmp)
    {
        fclose(tmp);
        chmod("test_no_access.fdf", 0000);  // Retire tous les droits
        fd = OPEN("test_no_access.fdf", O_RDONLY);
        if (fd != -1)
            CLOSE(fd);
        chmod("test_no_access.fdf", 0666);  // Restore permissions
        unlink("test_no_access.fdf");
    }
    
    // Test avec un répertoire au lieu d'un fichier
    fd = OPEN(".", O_RDONLY);
    if (fd != -1)
    {
        // Tester de lire un répertoire
        char buffer[10];
        ssize_t read_result = read(fd, buffer, sizeof(buffer));
        printf("Tentative de lecture d'un répertoire: %zd (%s)\n", 
               read_result, strerror(errno));
        CLOSE(fd);
    }
}

// Test avec un fichier FDF valide
void test_valid_fdf(void)
{
    printf("\n=== TEST AVEC UN FICHIER FDF VALIDE ===\n");
    
    // Créer un fichier FDF de test
    FILE *f = fopen("test_valid.fdf", "w");
    if (!f)
    {
        printf("ERREUR: Impossible de créer le fichier de test\n");
        return;
    }
    
    fprintf(f, "0 0 0 0 0\n");
    fprintf(f, "0 1 2 1 0\n");
    fprintf(f, "0 2,0xFF0000 4,0x00FF00 2 0\n");
    fprintf(f, "0 1 2 1 0\n");
    fprintf(f, "0 0 0 0 0\n");
    fclose(f);
    
    // Ouvrir et lire le fichier FDF
    int fd = OPEN("test_valid.fdf", O_RDONLY);
    if (fd == -1)
    {
        printf("ERREUR: Impossible d'ouvrir le fichier de test\n");
        return;
    }
    
    // Lire ligne par ligne
    char buffer[4096];
    ssize_t bytes_read;
    char *line_start = buffer;
    ssize_t total_read = 0;
    
    while ((bytes_read = read(fd, buffer + total_read, sizeof(buffer) - total_read - 1)) > 0)
    {
        total_read += bytes_read;
        buffer[total_read] = '\0';
        
        char *line_end;
        while ((line_end = strchr(line_start, '\n')) != NULL)
        {
            *line_end = '\0';
            test_line_parsing(line_start);
            line_start = line_end + 1;
        }
        
        // Si nous avons une ligne incomplète, déplacer les données restantes au début du buffer
        if (line_start < buffer + total_read)
        {
            memmove(buffer, line_start, buffer + total_read - line_start);
            total_read = buffer + total_read - line_start;
            line_start = buffer;
        }
        else
        {
            total_read = 0;
            line_start = buffer;
        }
    }
    
    // Traiter la dernière ligne si elle existe et n'a pas de '\n' final
    if (total_read > 0)
    {
        buffer[total_read] = '\0';
        test_line_parsing(buffer);
    }
    
    // Fermer le fichier
    CLOSE(fd);
    
    // Nettoyer le fichier de test
    unlink("test_valid.fdf");
}

// Test d'un fichier FDF mal formé
void test_malformed_fdf(void)
{
    printf("\n=== TEST AVEC UN FICHIER FDF MAL FORMÉ ===\n");
    
    // Créer un fichier FDF de test avec des erreurs
    FILE *f = fopen("test_malformed.fdf", "w");
    if (!f)
    {
        printf("ERREUR: Impossible de créer le fichier de test\n");
        return;
    }
    
    fprintf(f, "0 0 0 0 0\n");
    fprintf(f, "0 1 A 1 0\n");  // 'A' n'est pas un nombre
    fprintf(f, "0 2,0xFFFGHI 4 2 0\n");  // Couleur invalide
    fprintf(f, "0 1 2 1\n");  // Ligne incomplète
    fprintf(f, "0 0 0 0 0 10 20\n");  // Ligne trop longue
    fclose(f);
    
    // Ouvrir et lire le fichier FDF
    int fd = OPEN("test_malformed.fdf", O_RDONLY);
    if (fd == -1)
    {
        printf("ERREUR: Impossible d'ouvrir le fichier de test\n");
        return;
    }
    
    // Lire ligne par ligne
    char buffer[4096];
    ssize_t bytes_read;
    char *line_start = buffer;
    ssize_t total_read = 0;
    
    while ((bytes_read = read(fd, buffer + total_read, sizeof(buffer) - total_read - 1)) > 0)
    {
        total_read += bytes_read;
        buffer[total_read] = '\0';
        
        char *line_end;
        while ((line_end = strchr(line_start, '\n')) != NULL)
        {
            *line_end = '\0';
            test_line_parsing(line_start);
            line_start = line_end + 1;
        }
        
        // Si nous avons une ligne incomplète, déplacer les données restantes au début du buffer
        if (line_start < buffer + total_read)
        {
            memmove(buffer, line_start, buffer + total_read - line_start);
            total_read = buffer + total_read - line_start;
            line_start = buffer;
        }
        else
        {
            total_read = 0;
            line_start = buffer;
        }
    }
    
    // Traiter la dernière ligne si elle existe et n'a pas de '\n' final
    if (total_read > 0)
    {
        buffer[total_read] = '\0';
        test_line_parsing(buffer);
    }
    
    // "Oublier" de fermer le fichier intentionnellement pour tester la fuite

    // Nettoyer le fichier de test après le rapport de fuite
    unlink("test_malformed.fdf");
}

// Test d'oubli de fermeture intentionnel
void test_fd_leak(void)
{
    printf("\n=== TEST DE FUITE DE DESCRIPTEUR DE FICHIER ===\n");
    
    int fd1 = OPEN("/dev/null", O_RDONLY);
    int fd2 = OPEN("/dev/zero", O_RDONLY);
    
    // Fermer seulement le premier fichier
    if (fd1 != -1)
        CLOSE(fd1);
    
    // fd2 est intentionnellement laissé ouvert pour tester la détection de fuite
}

int main(void)
{
    printf("=== DÉBUT DES TESTS FDF ===\n\n");
    
    // Test des erreurs de fichier
    test_file_errors();
    
    // Test avec un fichier FDF valide
    test_valid_fdf();
    
    // Test avec un fichier FDF mal formé
    test_malformed_fdf();
    
    // Test de fuite de descripteur de fichier
    test_fd_leak();
    
    // Rapport des FDs qui n'ont pas été fermés
    report_leaked_fds();
    
    printf("\n=== FIN DES TESTS FDF ===\n");
    return 0;
}
