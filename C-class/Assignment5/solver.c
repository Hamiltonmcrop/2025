#include "solver.h"

#define BUFFER_SIZE 50
#define MESSAGE_SIZE 100

void reverse(char *str)
{
	int l = 0;
	int r = strlen(str) - 1;
	while (l < r)
	{
		char temp = str[l];
		str[l] = str[r];
		str[r] = temp;
		l++;
		r--;
	}
}

void *solve(void *arg)
{
	solve_args *args = (solve_args *)arg;

	// Search horizontally
	for (int i = 0; i < args->subpuzzle_rows; i++)
	{
		for (int j = 0; j < args->subpuzzle_cols; j++)
		{
			char *word = (char *)malloc(args->subpuzzle_cols + 1);
			for (int k = 0; k < args->subpuzzle_cols - j && strlen(word) < args->max_len; k++)
			{
				word[k] = args->sub_puzzle[i][j + k];
				int len = strlen(word);
				if (len >= args->min_len && len <= args->max_len && search(*args->dict, word))
				{
					char *message = malloc(MESSAGE_SIZE * sizeof(char));
					sprintf(message, "%s\t%d\t%d:%d\t%d:%d\n", word, args->t_id, i + 1, i + 1, j + 1, j + k + 1);
					if (args->sorted)
					{
						pthread_mutex_lock(args->bst_mutex);
						bst_insert(args->bst_root, message);
						pthread_mutex_unlock(args->bst_mutex);
					}
					else
					{
						printf("%s", message);
						free(message);
					}
				}
				// Check backwards
				reverse(word);
				if (len >= args->min_len && len <= args->max_len && search(*args->dict, word))
				{
					char *message = malloc(MESSAGE_SIZE * sizeof(char));
					sprintf(message, "%s\t%d\t%d:%d\t%d:%d\n", word, args->t_id, i + 1, i + 1, j + k + 1, j + 1);
					if (args->sorted)
					{
						pthread_mutex_lock(args->bst_mutex);
						bst_insert(args->bst_root, message);
						pthread_mutex_unlock(args->bst_mutex);
					}
					else
					{
						printf("%s", message);
						free(message);
					}
				}
				// Revert to normal order
				reverse(word);
			}
			free(word);
		}
	}

	// Search vertically
	for (int i = 0; i < args->subpuzzle_rows; i++)
	{
		for (int j = 0; j < args->subpuzzle_cols; j++)
		{
			char *word = (char *)malloc(args->subpuzzle_rows + 1);
			for (int k = 0; k < args->subpuzzle_rows - i && strlen(word) < args->max_len; k++)
			{
				word[k] = args->sub_puzzle[i + k][j];
				int len = strlen(word);
				if (len >= args->min_len && len <= args->max_len && search(*args->dict, word))
				{
					char *message = malloc(MESSAGE_SIZE * sizeof(char));
					sprintf(message, "%s\t%d\t%d:%d\t%d:%d\n", word, args->t_id, i + 1, i + k + 1, j + 1, j + 1);
					if (args->sorted)
					{
						pthread_mutex_lock(args->bst_mutex);
						bst_insert(args->bst_root, message);
						pthread_mutex_unlock(args->bst_mutex);
					}
					else
					{
						printf("%s", message);
						free(message);
					}
				}
				// Check backwards
				reverse(word);
				if (len >= args->min_len && len <= args->max_len && search(*args->dict, word))
				{
					word[k] = args->sub_puzzle[i + k][j];
					int len = strlen(word);
					if (len >= args->min_len && len <= args->max_len && search(*args->dict, word))
					{
						char *message = malloc(MESSAGE_SIZE * sizeof(char));
						sprintf(message, "%s\t%d\t%d:%d\t%d:%d\n", word, args->t_id, i + k + 1, i + 1, j + 1, j + 1);
						if (args->sorted)
						{
							pthread_mutex_lock(args->bst_mutex);
							bst_insert(args->bst_root, message);
							pthread_mutex_unlock(args->bst_mutex);
						}
						else
						{
							printf("%s", message);
							free(message);
						}
					}
				}
				// Revert to normal order
				reverse(word);
			}
			free(word);
		}
	}

	// Search diagonally
	for (int i = 0; i < args->subpuzzle_rows; i++)
	{
		for (int j = 0; j < args->subpuzzle_cols; j++)
		{
			// Diagonal pointing down
			char *word_down = (char *)malloc(args->subpuzzle_cols + 1);
			// Diagonal pointing up
			char *word_up = (char *)malloc(args->subpuzzle_cols + 1);

			// Diagonal down
			for (int k = 0; k < args->subpuzzle_rows - i && k < args->subpuzzle_cols - j && strlen(word_down) < args->max_len; k++)
			{
				word_down[k] = args->sub_puzzle[i + k][j + k];
				int len = strlen(word_down);
				if (len >= args->min_len && len <= args->max_len && search(*args->dict, word_down))
				{
					char *message = malloc(MESSAGE_SIZE * sizeof(char));
					sprintf(message, "%s\t%d\t%d:%d\t%d:%d\n", word_down, args->t_id, i + 1, i + k + 1, j + 1, j + k + 1);
					if (args->sorted)
					{
						pthread_mutex_lock(args->bst_mutex);
						bst_insert(args->bst_root, message);
						pthread_mutex_unlock(args->bst_mutex);
					}
					else
					{
						printf("%s", message);
						free(message);
					}
				}
				// Check backwards
				reverse(word_down);
				if (len >= args->min_len && len <= args->max_len && search(*args->dict, word_down))
				{
					char *message = malloc(MESSAGE_SIZE * sizeof(char));
					sprintf(message, "%s\t%d\t%d:%d\t%d:%d\n", word_down, args->t_id, i + k + 1, i + 1, j + k + 1, j + 1);
					if (args->sorted)
					{
						pthread_mutex_lock(args->bst_mutex);
						bst_insert(args->bst_root, message);
						pthread_mutex_unlock(args->bst_mutex);
					}
					else
					{
						printf("%s", message);
						free(message);
					}
				}
				// Revert to normal order
				reverse(word_down);
			}

			// Diagonal up
			for (int k = 0; k < i + 1 && k < args->subpuzzle_cols - j && strlen(word_up) < args->max_len; k++)
			{
				word_up[k] = args->sub_puzzle[i - k][j + k];
				int len = strlen(word_up);
				if (len >= args->min_len && len <= args->max_len && search(*args->dict, word_up))
				{
					char *message = malloc(MESSAGE_SIZE * sizeof(char));
					sprintf(message, "%s\t%d\t%d:%d\t%d:%d\n", word_up, args->t_id, i + 1, i - k + 1, j + 1, j + k + 1);
					if (args->sorted)
					{
						pthread_mutex_lock(args->bst_mutex);
						bst_insert(args->bst_root, message);
						pthread_mutex_unlock(args->bst_mutex);
					}
					else
					{
						printf("%s", message);
						free(message);
					}
				}
				// Check backwards
				reverse(word_up);
				if (len >= args->min_len && len <= args->max_len && search(*args->dict, word_up))
				{
					char *message = malloc(MESSAGE_SIZE * sizeof(char));
					sprintf(message, "%s\t%d\t%d:%d\t%d:%d\n", word_up, args->t_id, i - k + 1, i + 1, j + k + 1, j + 1);
					if (args->sorted)
					{
						pthread_mutex_lock(args->bst_mutex);
						bst_insert(args->bst_root, message);
						pthread_mutex_unlock(args->bst_mutex);
					}
					else
					{
						printf("%s", message);
						free(message);
					}
				}
				// Revert to normal order
				reverse(word_up);
			}

			free(word_down);
			free(word_up);
		}
	}

	pthread_exit(NULL);
}

void print_buffer(char **sub_puzzle, int subpuzzle_rows, int subpuzzle_cols)
{
	// this function is used for printing the content of each buffer cell.
	// do NOT call this function anywhere in your final submission.
	printf("%d by %d\n", subpuzzle_rows, subpuzzle_cols);
	for (int i = 0; i < subpuzzle_rows; i++)
		for (int j = 0; j < subpuzzle_cols; j++)
			printf("%c%s", sub_puzzle[i][j], j == subpuzzle_cols - 1 ? "\n" : "");
}

// Function reads file descriptor and inserts words into hashset.
// It returns 1 if error, else 0.
int read_dictionary(hashset *h, FILE *dictionary_file)
{
	char word[BUFFER_SIZE];

	while (fgets(word, BUFFER_SIZE, dictionary_file) != NULL)
	{
		word[strcspn(word, "\n")] = '\0';
		insert(h, word);
	}

	if (ferror(dictionary_file))
	{
		perror("Error reading file");
		return 1;
	}

	return 0;
}

int main(int argc, char **argv)
{
	if (argc < 11)
		error("Fatal Error. Usage: solve -dict dict.txt -input puzzle1mb.txt -size 1000 -nbuffer 64 -len 4:7 [-s]", 1);
	int puzzle_size = 0, buf_cells = 0, i = 0, j, fd, min_len = 0, max_len = 0, sorted = 0, buf_dimension;
	char *filename = NULL;
	FILE *dictionary_file;
	char ***buffer;
	while (++i < argc)
	{
		if (argv[i][0] != '-')
			error("Fatal Error. Invalid CLA", 2);
		if (!strcmp(argv[i], "-size"))
		{
			puzzle_size = atoi(argv[++i]);
			if (puzzle_size < 15 || puzzle_size > 46340)
				error("Fatal Error. Illegal value passed after -size", 3);
		}
		else if (!strcmp(argv[i], "-nbuffer"))
		{
			buf_cells = atoi(argv[++i]);
			if (buf_cells != 1 && buf_cells != 4 && buf_cells != 16 && buf_cells != 64)
				error("Fatal Error. Illegal value passed after -nbuffer", 4);
			buf_dimension = (int)sqrt(MEM_LIMIT / buf_cells);
			// buf_cells = 1 -> buf_dimension = 8000
			// buf_cells = 4 -> buf_dimension = 4000
			// buf_cells = 16 -> buf_dimension = 2000
			// buf_cells = 64 -> buf_dimension = 1000
		}
		else if (!strcmp(argv[i], "-input"))
		{
			filename = strdup(argv[++i]);
			fd = open(filename, O_RDONLY, 0);
			if (fd < 0)
				error("Fatal Error. Illegal value passed after -input", 5);
		}
		else if (!strcmp(argv[i], "-dict"))
		{
			dictionary_file = fopen(argv[++i], "r");
			if (!dictionary_file)
				error("Fatal Error. Illegal value passed after -dict", 6);
		}
		else if (!strcmp(argv[i], "-len"))
		{
			char *min_max = strdup(argv[++i]);
			char *max_str;
			if (strrchr(min_max, ':') != (max_str = strchr(min_max, ':')) || !strchr(min_max, ':'))
				error("Fatal Error. Illegal value passed after -len", 7);
			max_len = atoi(max_str + 1);
			min_max[max_str - min_max] = '\0';
			min_len = atoi(min_max);
			if (min_len < 3 || max_len > 14 || min_len > max_len)
				error("Fatal Error. Illegal value passed after -len", 7);
		}
		else if (!strcmp(argv[i], "-s"))
			sorted = 1;
		else
		{
			error("Fatal Error. Usage: solve -dict dict.txt -input puzzle1mb.txt -size 1000 -nbuffer 64 -len 4:7 [-s]", 1);
			break;
		}
	}

	// Read and move all words from dictionary_file to a new hash table (hashset)
	hashset dict = set_init();
	if (read_dictionary(&dict, dictionary_file)) // if error, exit
		return 1;

	// Create BST root
	tnode **bst_root = (tnode **)malloc(sizeof(tnode *));
	*bst_root = NULL;
	pthread_mutex_t bst_mutex;
	pthread_mutex_init(&bst_mutex, NULL);

	// Print headings
	printf("word\tTID\tLnSpan\tColSpan\n");

	// allocate 64MB of buffer in the heap
	// buffer is a 3D array
	// on the outermost dimension, we have buf_cells elements
	// each element is given to one consumer thread
	// each element is going to store a (square-shape) sub-puzzle
	// each element is a square-shape 2D array of characters
	// dimension of this square-shape array is buf_dimension by buf_dimension
	buffer = (char ***)malloc(buf_cells * sizeof(char **));
	for (i = 0; i < buf_cells; i++)
	{
		buffer[i] = (char **)malloc(buf_dimension * sizeof(char *));
		for (j = 0; j < buf_dimension; j++)
			buffer[i][j] = (char *)malloc(buf_dimension);
	}
	int buf_index = 0;
	pthread_t t_id[buf_cells];
	for (i = 0; i < buf_cells; i++)
		t_id[i] = NULL;
	for (int row = 0; row + max_len - 1 < puzzle_size; row += (buf_dimension - max_len + 1))
	{
		int subpuzzle_rows = (row + buf_dimension <= puzzle_size) ? buf_dimension : puzzle_size - row;
		for (int column = 0; column + max_len - 1 < puzzle_size; column += (buf_dimension - max_len + 1))
		{
			long start = (long)row * (puzzle_size + 1) + column;
			lseek(fd, start, SEEK_SET);
			int subpuzzle_cols = (column + buf_dimension <= puzzle_size) ? buf_dimension : puzzle_size - column;
			if (t_id[buf_index])					 // if there is a busy consumer/solver,
				pthread_join(t_id[buf_index], NULL); // wait for it to finish the job before manipulating the buffer[buffer_index]
			for (i = 0; i < subpuzzle_rows; i++)
			{
				int n_read = read(fd, buffer[buf_index][i], subpuzzle_cols);
				if (n_read < subpuzzle_cols)
					error("Fatal Error. Bad read from input file", 10);
				if (subpuzzle_cols < buf_dimension)
					buffer[buf_index][i][subpuzzle_cols] = '\0';
				lseek(fd, puzzle_size - subpuzzle_cols + 1, SEEK_CUR);
			}
			if (subpuzzle_rows < buf_dimension)
				buffer[buf_index][subpuzzle_rows] = NULL;

			solve_args *args = (solve_args *)malloc(sizeof(solve_args));
			args->t_id = buf_index;
			args->dict = &dict;
			args->bst_root = bst_root;
			args->bst_mutex = &bst_mutex;
			args->sub_puzzle = buffer[buf_index];
			args->subpuzzle_rows = subpuzzle_rows;
			args->subpuzzle_cols = subpuzzle_cols;
			args->min_len = min_len;
			args->max_len = max_len;
			args->sorted = sorted;
			pthread_create(t_id + buf_index, NULL, solve, args);
			buf_index = (buf_index == buf_cells - 1) ? 0 : buf_index + 1;
		}
	}
	for (i = 0; i < buf_cells; i++)
		if (t_id[i])
			pthread_join(t_id[i], NULL);

	if (sorted)
		inorder_print(*bst_root);
}