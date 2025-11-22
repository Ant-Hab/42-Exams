
  typedef struct  s_point
  {
    int           x;
    int           y;
  }               t_point;


void flood_fill(char **tab, t_point size, t_point begin)
{
    char target = tab[begin.y][begin.x];
    int row = begin.y;
    int col = begin.x;

    if (row < 0 || col < 0 || row >= size.y || col >= size.x)
        return;
    if (tab[row][col] == 'F' || tab[row][col] != target)
        return;

    tab[row][col] = 'F';

    t_point new_begin;

    new_begin = (t_point){col, row - 1}; flood_fill(tab, size, new_begin);
    new_begin = (t_point){col, row + 1}; flood_fill(tab, size, new_begin);
    new_begin = (t_point){col - 1, row}; flood_fill(tab, size, new_begin);
    new_begin = (t_point){col + 1, row}; flood_fill(tab, size, new_begin);
}
