#include "ft_printf.h"

int	ft_print_hex(unsigned int n, const char format)
{
	int	len;

	len = 0;
	if (n >= 16)
	{
		len += ft_print_hex(n / 16, format);
		len += ft_print_hex(n % 16, format);
	}
	else
	{
		if (n <= 9)
			len += ft_print_char(n + '0');
		else
		{
			if (format == 'x')
				len += ft_print_char(n - 10 + 'a');
			if (format == 'X')
				len += ft_print_char(n - 10 + 'A');
		}
	}
	return (len);
}
