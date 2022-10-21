#include "tp.h"
int main(int argc, char **argv) {
  double t1,t2,tr=0;
  //Recebe o tempo desde 1970 até o inicio do programa
  t1=tempo();
  int opt;
  char *input = NULL;
  char *output = NULL;
  while((opt = getopt(argc, argv, "i:o:"))!=-1){
    switch (opt){
      case 'i':
        input = optarg; 
        break;
      case 'o':
        output = optarg;
        break;
      default:
        return -1;
     }
  }
  //chama a função lerArquivo para ler o grafo no arquivo e encontrar uma solução
	lerArquivo(input,output); 
  //Recebe o tempo desde 1970 até o fim do programa
  t2=tempo();
  //Subtrai os tempos obtidos
  tr=t2-t1;
  printf("Tempos:%f ms\n",tr );
  struct rusage r_usage;
  getrusage(RUSAGE_SELF,&r_usage);//tempo de usuário e de sistema
  printf("Usuario = %ld.%06ldms,Sistema = %ld.%06ldms\n",r_usage.ru_utime.tv_sec,r_usage.ru_utime.tv_usec,r_usage.ru_stime.tv_sec, r_usage.ru_stime.tv_usec);
  return 0;
   }


