#include "minitalk.h"

void	ft_handler(int sig, siginfo_t *siginfo, void *vooo)
{
	static int	bit;
	static int	i;
    pid_t   client_pid;

    (void)vooo;
    client_pid = siginfo->si_pid;
	if (sig == SIGUSR1)
		i |= (1 << bit);
	bit++;
	if (bit == 8)
	{
		ft_printf("%c", i);
        if (i == '\0')
			kill(client_pid, SIGUSR1);
		bit = 0;
		i = 0;
	}
}

int	main(int argc, char **argv)
{
    struct sigaction	sa;
	(void)argv;

	if (argc != 1)
		return (1);
    sa.sa_sigaction = ft_handler;
	sa.sa_flags = SA_SIGINFO;
	ft_printf("The server PID : %d\n", getpid());
	while (argc == 1)
	{
		sigaction(SIGUSR1, &sa, NULL);
        sigaction(SIGUSR2, &sa, NULL);
		pause ();
	}
	return (0);
}