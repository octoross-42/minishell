/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 22:03:46 by octoross          #+#    #+#             */
/*   Updated: 2024/10/05 22:03:46 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERR_H

# define ERR_H

# define STATUS_OK 0
# define STATUS_PROG 1
# define STATUS_REDIR 1
# define STATUS_BUILDIN 1
# define STATUS_SYNTAX 2
# define STATUS_FORK 71
# define STATUS_CHDIR 71
# define STATUS_DUP 71
# define STATUS_DUP2 71
# define STATUS_PIPE 71
# define STATUS_OPEN 66
# define STATUS_CMD 126
# define STATUS_EXECVE 127
# define STATUS_MALLOC 137

# define ERR_MALLOC "malloc failed : %s\n"
# define ERR_REDIR "ambiguous redirection\n"
# define ERR_HERE_DOC "warning: here-document delimited by end-of-file \
(wanted `%s')\n"
# define ERR_FAIL "%s failed\n"
# define ERR_FORK "fork failed\n"
# define ERR_PIPE "Pipe failed\n"
# define ERR_DUP "dup failed\n"
# define ERR_DUP2 "dup2 failed\n"
# define ERR_CMD "%s: command not found\n"
# define ERR_EXPAND "%s not expanded : malloc failed\n"
# define ERR_ENV "Warning : No env retrieved\n"
# define ERR_PARSING_ENV "Error : env is badly parsed\n"
# define ERR_PROG "Bad programming happenned :(\n"
# define ERR_TOKEN "bad tokens\n"
# define ERR_HISTORY "could not load history\n"
# define ERR_HISTORY_WRITE "warning : cannot save history for next session\n"

# define ERR_TMA "%s: too many arguments\n"
# define ERR_CD "cd: specify a path\n"

#endif