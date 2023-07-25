#include "main.h"

void print_buff(char buffer[], int *buf_index);

/**
 * _printf - Printf function
 * @format: format.
 * Return: Printed chars.
 */
int _printf(const char *format, ...)
{
	int i, printed = 0, printed_chars = 0;
	int flags, width, precision, size, buf_index = 0;
	va_list args;
	char buffer[BUFFSIZE];

	if (format == NULL)
		return (-1);

	va_start(args, format);

	for (i = 0; format && format[i] != '\0'; i++)
	{
		if (format[i] != '%')
		{
			buffer[buf_index++] = format[i];
			if (buf_index == BUFFSIZE)
				print_buff(buffer, &buf_index);
			/* write(1, &format[i], 1);*/
			printed_chars++;
		}
		else
		{
			print_buff(buffer, &buf_index);
			flags = get_flags(format, &i);
			width = get_width(format, &i, args);
			precision = get_precision(format, &i, args);
			size = get_size(format, &i);
			++i;
			printed = handle_print(format, &i, args, buffer,
				flags, width, precision, size);
			if (printed == -1)
				return (-1);
			printed_chars += printed;
		}
	}

	print_buff(buffer, &buf_index);

	va_end(args);

	return (printed_chars);
}

/**
 * print_buff - Prints the contents of the buffer if it exist
 * @buffer: Array of chars
 * @buf_index: Index at which to add next char, represents the length.
 */
void print_buff(char buffer[], int *buf_index)
{
	if (*buf_index > 0)
		write(1, &buffer[0], *buf_index);

	*buf_index = 0;
}
