/*****************************************************************************/
/*
* Exercise 3: population evolution
*			  example of cities in France			
*
* Intelligent Systems Lab Session
*
/*****************************************************************************/

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#include "tsp_utils.h"
#include "chromosome.h"
#include "population.h"

int n_cities=0;
City city[MAX_N_CITIES];

/*****************************************************************************/
int main(int argc,char ** argv){
	FILE *out;
	int generation;
	Population pop;
	double best_fitness, fitness;
	char filename[] = "exercise3.txt";
	double mutation_rate = 0.1;
	int population_size = 100;
	double selection_rate = 0.5;
	int e;
	int i;

	/* open a file to print the results during the iterations */
	if(fopen_s(&out,filename,"w") != 0) {
		printf("* Error opening file %s\n",filename);
		getchar(); exit(1);
	}

	/* initialize cities */
	tsp_read_cities("..\\..\\..\\data\\france.txt");
	tsp_init_plots();

	/* BEGIN IMPLEMENTATION */
	for (i = 1; i < 7; i++) { 
	switch(i) {
			case 1:
				mutation_rate = 0.01;
				population_size = 100;
				break;
			case 2:
				mutation_rate = 0.1;
				population_size = 100;
				break;
			case 3:
				mutation_rate = 0.5;
				population_size = 100;
				break;
			case 4:
				mutation_rate = 0.1;
				population_size = 10;
				break;
			case 5:
				mutation_rate = 0.1;
				population_size = 50;
				break;
			case 6:
				mutation_rate = 0.1;
				population_size = 100;
				break;
			case 7:
				mutation_rate = 0.1;
				population_size = 500;
				break;
		}
	}
	/* END IMPLEMENTATION */
		

		printf("Mutation rate: %2.3f, Population size: %d\n",mutation_rate,population_size);
		fprintf(out,"Mutation rate: %2.3f, Population size: %d\n",mutation_rate,population_size);


		/* Initialize population with random chromosomes: */
		for (i = 0; i < 3; i++) {
			population_random(&pop,population_size);

			best_fitness = 1000000000.;
			for(generation=0; generation<=500; generation++) {

				population_mutation(&pop,mutation_rate);

				population_crossover(&pop,population_size);

				population_selection(&pop,(int)(selection_rate*(double)population_size));
				/* the population is now sorted, so that chromosome[0] is the best one */

				/* keep population if fitness has improved */
				fitness = pop.chromosome[0].fitness;
				if(best_fitness > fitness) {
					best_fitness = fitness;
					tsp_plot_route("..\\..\\..\\data\\france.ppm",pop.chromosome[0].gene,
					tsp_round_trip_length(pop.chromosome[0].gene),
											generation);
					fprintf(out,"Generation: %4d, population size: %d, Round-trip length: %5.3f, best %5.3f\n",
					generation,population_size,tsp_round_trip_length(pop.chromosome[0].gene),best_fitness);
				}
				printf("Generation: %4d, population size: %d, Round-trip length: %5.3f, best %5.3f\n",
				generation,population_size,tsp_round_trip_length(pop.chromosome[0].gene),best_fitness);
			}
		}
	printf("Finished. Press the Enter key to exit...\n");
	getchar(); // wait until user presses a key
	return 0;
}