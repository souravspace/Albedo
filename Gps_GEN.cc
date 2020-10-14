#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <mpi.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <unistd.h>
#define GetCurrentDir getcwd

using namespace std;


void writeGpsFile(char *filename, int zenangle, int min_eninx, int max_eninx, int interval_eninx, long nph)
{
FILE *fgps=fopen(filename,"w") ;
fprintf(fgps,"/gun/zenith %i \n\
/control/alias minph_indx %i \n\
/control/alias maxph_indx %i \n\
/control/alias intervalph_indx %i \n\
/control/alias nphoton %ld \n\
/control/loop vis.mac indx_energy {minph_indx} {maxph_indx} {intervalph_indx} \n",
zenangle,\
min_eninx,\
max_eninx,\
interval_eninx,\
nph 
);

fclose(fgps);
return;
}



int main (int argc, char **argv)
{

int zenitangle, min_en_inx, max_en_inx, interval_en_inx, numph ;

zenitangle = 10 ;
min_en_inx = 1 ;
max_en_inx = 10 ;
interval_en_inx = 1 ;
numph = 1000 ;

char builddir[300];
char sourcedir[300];
char outdir[300];

char DIR[FILENAME_MAX] ;
GetCurrentDir(DIR,FILENAME_MAX);

sprintf(sourcedir,"%s/%s",DIR,"Ionosphere");
sprintf(builddir,"%s/%s",DIR,"Ionosphere_build");
sprintf(outdir,"%s/%s",DIR,"Ionosphere_out");

//==============================================================================================

int size, rank;

MPI_Init(&argc, &argv);
MPI_Comm_size(MPI_COMM_WORLD, &size);
MPI_Comm_rank(MPI_COMM_WORLD, &rank);


char RUN_STR[40];
char cp_command[1000];
char cd_command[1000];
char rm_command[1000];
char gps_fnam[1000];
char verbose_fnam[1000];
char pwd[50] = "pwd";
char run_command[2000] ;


sprintf(RUN_STR,"atmosbuild%i", rank) ;
sprintf(rm_command,"rm -r %s/%s",outdir,RUN_STR);
sprintf(cp_command,"cp -r %s %s/%s",builddir,outdir,RUN_STR);
sprintf(cd_command,"cd %s/%s; %s",outdir,RUN_STR,pwd);
sprintf(run_command,"%s; ./Ion input.mac", cd_command);

system(rm_command);
system(cp_command);
system(run_command);


//============================================================================================


MPI_Finalize();

return 0;
}


