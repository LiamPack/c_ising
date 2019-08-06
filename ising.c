#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define N 500
#define MAX_SWEEPS 250
#define FREQ 1
#define T 2.2691

int grid[N][N];

// initialize the board state to random 1s and 0s
void initialize_grid();

// decide whether or not to flip a single cell
void flip_cell(int x, int y);

// Sweep the grid NxN times
void full_sweep();

// output grid as a PPM "image"
void output_grid();

// Calculate the change in energy if grid[x][y] is flipped
float deltaU(int x, int y);

int main()
{
  srand(time(NULL));
  initialize_grid();

  for(int i = 0; i < MAX_SWEEPS; i++){
    full_sweep();
    if(i % FREQ == 0){
      output_grid();
    }
    //fprintf(stderr, "iteration %d\n", i);
  }

  return 0;
}


void initialize_grid(){
  for(int i = 0; i < N; i++){
    for(int j = 0; j < N; j++){
      grid[i][j] = rand() % 2 ? 1 : -1;
    }
  }
}

void full_sweep(){
  for(int step = 0; step < N*N; step++){
    int i = rand()%N;
    int j = rand()%N;
    flip_cell(i,j);
  }
}

void flip_cell(int i, int j){
  double random = (double)rand() / (double)RAND_MAX;
  double delta_energy = deltaU(i,j);
  if(delta_energy <= 0 || random < exp(-delta_energy/T)){
    grid[i][j] *= -1;
  }
}

void output_grid(){
  fprintf(stdout, "P6\n%zu %zu\n255\n", (size_t)N, (size_t)N);
  char num;
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      num =  grid[i][j] < 0 ? 255 : 0;
      fwrite(&num, 1,1, stdout);
      fwrite(&num, 1,1, stdout);
      fwrite(&num, 1,1, stdout);

    }
  }
  fflush(stdout);
}

float deltaU(int x, int y){
  double accum = grid[(x+(N-1)) % N][y] + grid[(x+1) % N][y] +
    grid[x][(y+(N-1))%N] + grid[x][(y+1)%N];

  return 2.0 * grid[x][y] * accum;
}
