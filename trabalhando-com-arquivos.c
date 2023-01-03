#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct data
{
   int dia;
   int mes;
   int ano;
};
struct cadastro
{
   char        nome[50];
   float       salario;
   struct data admis;
   char        depart[50];
};

void fun(struct cadastro *cad, int n, char *out)
{
   struct cadastro temp;              //Estrutura temporária para usar na comparação

   for (int i = 0; i < n; i++)        //Varre todo o array
   {
      for (int j = i + 1; j < n; j++) //Varre o array com os nomes que vem depois
      {
         /* Exemplo (genérico), pra ficar mais claro:
          * Se s1=amante e s2=amanda
          * Então strcmp(s1,s2) retorna "f - d"
          * em ascii (decimal), f=116 e d=100
          * logo, "f - d" = 16        */
         if (strcmp(cad[i].nome, cad[j].nome) > 0)
         {
            temp   = cad[i];
            cad[i] = cad[j];
            cad[j] = temp;
         }
      }
   }
   FILE *fh = fopen(out, "w");

   for (int i = 0; i < n; i++)
   {
      fprintf(fh, "%s\n%.2f\n%.2d/%.2d/%.4d\n%s\n", cad[i].nome, cad[i].salario, cad[i].admis.dia, cad[i].admis.mes, cad[i].admis.ano, cad[i].depart);
   }
   fclose(fh);
}

void dep(struct cadastro *cad, int n, char *setor)
{
   struct cadastro temp;
   int             s = 0;
   struct cadastro set[n];

   for (int i = 0; i < n; i++)
   {
      if (strcmp(cad[i].depart, setor) == 0)
      {
         set[s] = cad[i];
         s++;
      }
   }
   for (int i = 0; i < s; i++)
   {
      for (int j = i + 1; j < s; j++)
      {
         if (strcmp(set[i].nome, set[j].nome) > 0)
         {
            temp   = set[i];
            set[i] = set[j];
            set[j] = temp;
         }
      }
      printf("%s\n%.2f\n%.2d/%.2d/%.4d\n%s\n", set[i].nome, set[i].salario, set[i].admis.dia, set[i].admis.mes, set[i].admis.ano, set[i].depart);
   }
}

void antigo(struct cadastro *cad, int n)
{
   struct cadastro menor;

   menor = cad[0];
   for (int i = 1; i < n; i++)
   {
      if (cad[i].admis.ano < menor.admis.ano)
      {
         menor = cad[i];
      }
      if (cad[i].admis.ano == menor.admis.ano)
      {
         if (cad[i].admis.mes < menor.admis.mes)
         {
            menor = cad[i];
         }
         if (cad[i].admis.mes == menor.admis.mes)
         {
            if (cad[i].admis.dia < menor.admis.dia)
            {
               menor = cad[i];
            }
         }
      }
   }
   printf("%s\n%.2f\n%.2d/%.2d/%.4d\n%s\n", menor.nome, menor.salario, menor.admis.dia, menor.admis.mes, menor.admis.ano, menor.depart);
}

void antigo_dep(struct cadastro *cad, int n, char *setor)
{
   struct cadastro menor;
   int             s = 0;
   struct cadastro set[n];

   for (int i = 0; i < n; i++)
   {
      if (strcmp(cad[i].depart, setor) == 0)
      {
         set[s] = cad[i];
         s++;
      }
   }
   menor = set[0];
   for (int i = 1; i < n; i++)
   {
      if (strcmp(cad[i].depart, setor) == 0)
      {
         if (cad[i].admis.ano < menor.admis.ano)
         {
            menor = cad[i];
         }
         if (cad[i].admis.ano == menor.admis.ano)
         {
            if (cad[i].admis.mes < menor.admis.mes)
            {
               menor = cad[i];
            }
            if (cad[i].admis.mes == menor.admis.mes)
            {
               if (cad[i].admis.dia < menor.admis.dia)
               {
                  menor = cad[i];
               }
            }
         }
      }
   }
   printf("%s\n%.2f\n%.2d/%.2d/%.4d\n%s\n", menor.nome, menor.salario, menor.admis.dia, menor.admis.mes, menor.admis.ano, menor.depart);
}

void media(struct cadastro *cad, int n)
{
   float soma = 0;

   for (int i = 0; i < n; i++)
   {
      soma += cad[i].salario;
   }
   printf("%.2f\n", soma / (float)n);
}

void media_dep(struct cadastro *cad, int n, char *setor)
{
   int             s    = 0;
   double          soma = 0;
   struct cadastro set[n];

   for (int i = 0; i < n; i++)
   {
      if (strcmp(cad[i].depart, setor) == 0)
      {
         set[s] = cad[i];
         s++;
      }
   }

   for (int i = 0; i < s; i++)
   {
      soma += set[i].salario;
   }
   printf("%.2f\n", soma / (double)s);
}

int main(int argc, char *argv[])
{
   FILE *fh = fopen(argv[1], "r");

   if (fh == NULL)
   {
      exit(1);
   }

   int q;

   fscanf(fh, "%d", &q);
   fgetc(fh);
   struct cadastro cad[q];

   for (int i = 0; i < q; i++)
   {
      fgets(cad[i].nome, 50, fh);
      cad[i].nome[strlen(cad[i].nome) - 1] = '\0';
      fscanf(fh, "%f", &cad[i].salario);
      fgetc(fh);
      fscanf(fh, "%d/%d/%d", &cad[i].admis.dia, &cad[i].admis.mes, &cad[i].admis.ano);
      fgetc(fh);
      fgets(cad[i].depart, 50, fh);
      cad[i].depart[strlen(cad[i].depart) - 1] = '\0';
   }
   fclose(fh);

   if (strcmp(argv[2], "1") == 0)
   {
      fun(cad, q, argv[3]);
   }
   if (strcmp(argv[2], "2") == 0)
   {
      dep(cad, q, argv[3]);
   }
   if (strcmp(argv[2], "3") == 0)
   {
      antigo(cad, q);
   }
   if (strcmp(argv[2], "4") == 0)
   {
      antigo_dep(cad, q, argv[3]);
   }
   if (strcmp(argv[2], "5") == 0)
   {
      media(cad, q);
   }
   if (strcmp(argv[2], "6") == 0)
   {
      media_dep(cad, q, argv[3]);
   }
   return(0);
}
