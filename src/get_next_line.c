#include "get_next_line.h"

int	init_get_next_line(struct gnl *ctx, char const *filename)
{
	ctx->remaining.buf = NULL;
	ctx->remaining.size = 0;
	return open(filename, O_RDONLY);
}

int	process_remaining(struct gnl *ctx, char **line)
{
	char	*newline = strnchr(ctx->remaining.buf, ctx->remaining.size);

	if (newline) {
		size_t	size = newline - ctx->remaining.buf;
		*line = strndup(ctx->remaining.buf, size);
		if (!line)
			return 1;
		return 0;
	}
}

char	*get_next_line(struct gnl *ctx)
{
	char	*line = NULL;
	int	ret;

	if (ctx->remaining.buf)
		ret = process_remaining(ctx, &line);
	if (ret == 0)
		return line;
	if (ret == 1)
		return NULL;
}
