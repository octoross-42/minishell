/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 03:09:25 by octoross          #+#    #+#             */
/*   Updated: 2024/10/06 03:09:25 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H

# define SIGNALS_H

extern int	g_sig;

# define NO_SIG 0
# define SIG_QUIT 1
# define SIG_INT 2

int		ft_exit_status(int status);
void	ft_input_signals(int sig);
void	ft_exec_signals(int sig);
void	ft_here_doc_signals(int sig);
void 	ft_setup_signals(void (*ft_handle_sig)(int));

#endif
