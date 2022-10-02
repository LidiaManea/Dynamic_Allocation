 #include <stdio.h> 
 #include <stdlib.h> 
 #include <string.h> 
 #define M 10007 
  
 //elibereaza memoria unei matrice 
 void eliberare_mat(int **matrice, int linii); 
 //interschimba 2 pointeri 
 void intersch_int(int *a, int *b); 
 //realoca memoria unei matrice 
 void realoc_mat(int **matrice, int **lin, int **col, int indice); 
 //aloca memoria unei matrice cu linii si coloane date 
 int **alocare_mat(int lin, int col); 
 //stergerea unei matrice cu un index dat 
 void sterg_mat(int **matrice, int **lin, int **col, int ind, int indice); 
 //suma elemntelor unei matrice cu index dat 
 int suma_elem_mat(int ***matrice, int n, int m, int ind); 
 //citeste o matrice de la tastatura 
 int **citire_matrice(int **lin, int **col, int indice); 
 //afisarea dimensiunilor matricei 
 void afis_dim_mat(int *lin, int *col, int indice); 
 //afiseaza o matrice 
 void afis_mat(int ***matrice, int *lin, int *col, int indice); 
 //formeaza o matrice din linii si coloane date de la tastatura 
 int **redimen_mat(int **matrice, int *lin, int *col); 
 //inmultirea a 2 matrice 
 int *inm_mat(int **mat, int *lin, int *col, int indice, int i1, int i2); 
 //sortarea matricelor dupa suma elementelor 
 void sortare_mat(int ***matrice, int *lin, int *col, int indice); 
 //transpusa unei matrice 
 void transpun_mat(int ***mat, int *lin, int *col, int ind); 
  
 int mod(int nr) 
 {        if (nr < 0) 
                 return nr % M + M; 
         else 
                 return nr % M; 
 } 
  
 void eliberare_mat(int **matrice, int linii) 
 { 
         for (int i = 0; i < linii; ++i) 
                 free(matrice[i]); 
         free(matrice); 
 } 
  
 void intersch_int(int *a, int *b) 
 { 
         int aux = *a; 
         *a = *b; 
         *b = aux; 
 } 
  
 int suma_elem_mat(int ***matrice, int n, int m, int ind) 
 { 
         int i, j, s = 0; 
         for (i = 0; i < n; ++i) 
                 for (j = 0; j < m; ++j) { 
                         s = mod(s); 
                         s += mod(matrice[ind][i][j]); 
                         s = mod(s); 
                 } 
         return mod(s); 
 } 
  
 void sterg_mat(int **matrice, int **lin, int **col, int ind, int indice) 
 { 
         int i; 
         eliberare_mat((*matrice)[ind], (*lin)[ind]); //se elibereaza memoria 
         for (i = ind; i < indice - 1; ++i) { 
                 (*matrice)[i] = (*matrice)[i + 1]; 
                 (*lin)[i] = (*lin)[i + 1]; 
                 (*col)[i] = (*col)[i + 1]; 
         } 
 } 
  
 void realoc_mat(int **matrice, int **lin, int **col, int indice) 
 { 
         if (indice == 0) { 
                 matrice = (int *)malloc(1 * sizeof(int *)); 
                 *lin = (int *)malloc(1 * sizeof(int)); 
                 *col = (int *)malloc(1 * sizeof(int)); 
         } else { 
                 matrice = (int *)realloc(*matrice, (indice + 1) * sizeof(int *)); 
                 *lin = (int *)realloc(*lin, (indice + 1) * sizeof(int)); 
                 *col = (int *)realloc(*col, (indice + 1) * sizeof(int)); 
         } 
 } 
  
 int **alocare_mat(int lin, int col) 
 {        int i; 
         int *mat = (int *)malloc(lin * sizeof(int *)); 
         if (!mat) 
                 return 0; 
         for (i = 0; i < lin; i++) { 
                 mat[i] = (int *)malloc(col * sizeof(int)); 
                 if (!mat[i]) { 
                         eliberare_mat(mat, i); 
                         return 0; 
                 } 
         } 
         return mat; 
 } 
  
 int **citire_matrice(int **lin, int **col, int indice) 
 { 
         int m, n, i, j; 
         scanf("%d%d", &n, &m); 
         (*lin)[indice] = n; 
         (*col)[indice] = m; 
         int **matrice = alocare_mat(n, m); 
         for (i = 0; i < n; ++i) 
                 for (j = 0; j < m; ++j) 
                         scanf("%d", &matrice[i][j]); 
         return matrice; 
 } 
  
 void afis_dim_mat(int *lin, int *col, int indice) 
 { 
         int ind; 
         scanf("%d", &ind); 
         if (ind >= indice || ind <= -1) 
                 printf("No matrix with the given index\n"); 
         else 
                 printf("%d %d\n", lin[ind], col[ind]); 
 } 
  
 void afis_mat(int ***matrice, int *lin, int *col, int indice) 
 { 
         int ind, i, j; 
         scanf("%d", &ind); 
         if (ind >= indice || ind <= -1) { 
                 printf("No matrix with the given index\n"); 
         } else { 
                 for (i = 0; i < lin[ind]; ++i) { 
                         for (j = 0; j < col[ind]; ++j) 
                                 printf("%d ", matrice[ind][i][j]); 
                         printf("\n"); 
                 } 
         } 
 } 
  
 int **redimen_mat(int **matrice, int *lin, int *col) 
 { 
         int linii, coloane, i, j; 
         int *v_linii, *v_coloane; 
         scanf("%d", &linii); 
         v_linii = (int *)malloc(linii * sizeof(int)); 
         for (i = 0; i < linii; ++i) 
                 scanf("%d", &v_linii[i]); //vectorul cu numarul liniilor 
         scanf("%d", &coloane); 
         v_coloane = (int *)malloc(coloane * sizeof(int)); 
         for (i = 0; i < coloane; ++i) 
                 scanf("%d", &v_coloane[i]); //vectorul cu numarul coloanelor 
         int *aux; //cvectorul ontine elementele matricei nou construite 
         aux = (int *)malloc((linii * coloane) * sizeof(int)); 
         int p = 0; 
         for (i = 0; i < linii; ++i) 
                 for (j = 0; j < coloane; ++j) 
                         aux[p++] = matrice[v_linii[i]][v_coloane[j]]; 
         for (i = linii; i < *lin; ++i) 
                 free(matrice[i]); 
         for (i = 0; i < linii; ++i) 
                 matrice[i] = (int *)realloc(matrice[i], coloane * sizeof(int)); 
         p = 0; 
         for (i = 0; i < linii; ++i) 
                 for (j = 0; j < coloane; ++j) 
                         matrice[i][j] = aux[p++]; 
         free(aux); 
         free(v_linii); 
         free(v_coloane); 
         *lin = linii; 
         *col = coloane; 
         return matrice; 
 } 
  
 int *inm_mat(int **mat, int *lin, int *col, int indice, int i1, int i2) 
 {        int i, j, k, aux; 
         int **mat_noua = alocare_mat(lin[i1], col[i2]); 
         for (i = 0; i < lin[i1]; ++i) 
                 for (j = 0; j < col[i2]; ++j) { 
                         mat_noua[i][j] = 0; 
                         for (k = 0; k < col[i1]; ++k) { 
                                 aux = 0; 
                                 aux = mod(mat[i1][i][k]); 
                                 aux *= mod(mat[i2][k][j]); 
                                 aux = mod(aux); 
                                 mat_noua[i][j] += aux; 
                                 mat_noua[i][j] = mod(mat_noua[i][j]); 
                         } 
                         mat_noua[i][j] = mod(mat_noua[i][j]); 
                 } 
         lin[indice] = lin[i1]; 
         col[indice] = col[i2]; 
         return mat_noua; 
 } 
  
 void sortare_mat(int ***matrice, int *lin, int *col, int indice) 
 { 
         int i, j; 
         int *s = (int *)malloc(indice * sizeof(int)); 
         for (i = 0; i < indice; ++i) 
                 s[i] = suma_elem_mat(matrice, lin[i], col[i], i); 
         for (i = 0; i < indice - 1; ++i) { 
                 for (j = i + 1; j < indice; ++j) 
                         if (s[i] > s[j]) { 
                                 int **mat_schimb = matrice[i]; 
                                 matrice[i] = matrice[j]; 
                                 matrice[j] = mat_schimb; 
                                 intersch_int(&lin[i], &lin[j]); 
                                 intersch_int(&col[i], &col[j]); 
                                 intersch_int(&s[i], &s[j]); 
                         } 
         } 
         free(s); 
 } 
  
 void transpun_mat(int ***mat, int *lin, int *col, int indice) 
 { 
         int ind, i, j; 
         scanf("%d", &ind); 
         if (ind >= indice || ind <= -1) { 
                 printf("No matrix with the given index\n"); 
         } else { 
                 int x = sizeof(int); 
                 int y = sizeof(int *); 
                 int tmp = lin[ind]; 
                 if (col[ind] > lin[ind]) { 
                         mat[ind] = (int **)realloc(mat[ind], col[ind] * y); 
                         for (i = lin[ind]; i < col[ind]; ++i) 
                                 mat[ind][i] = (int *)malloc(col[ind] * x); 
                         tmp = col[ind]; 
                 } 
                 if (col[ind] < lin[ind]) { 
                         for (i = 0; i < lin[ind]; ++i) 
                                 mat[ind][i] = (int *)realloc(mat[ind][i], lin[ind] * x); 
                         tmp = lin[ind]; 
                 } 
                 //tmp este maximul dintre numarul de linii si coloane 
                 //pentru a vedea memoria optima ce trebuie alocata 
                 for (i = 0; i < tmp - 1; ++i) 
                         for (j = i + 1; j < tmp; ++j) { 
                                 int aux = mat[ind][i][j]; 
                                 mat[ind][i][j] = mat[ind][j][i]; 
                                 mat[ind][j][i] = aux; 
                         } 
                 if (col[ind] < lin[ind]) { 
                         for (i = col[ind]; i < lin[ind]; ++i) 
                                 free(mat[ind][i]); 
                 } 
                 int aux = col[ind]; 
                 col[ind] = lin[ind]; 
                 lin[ind] = aux; 
         } 
 } 
  
 int main(void) 
 { 
         int ***matrice, *lin, *col, indice = 0, ind; 
         char comanda, stop = 1; 
         int i1, i2; 
         while (stop) { //daca inputul este Q, stop devine 0 si se iese din while 
                 scanf(" %c", &comanda); 
                 switch (comanda) { 
                 case 'L': 
                         realoc_mat(&matrice, &lin, &col, indice); 
                         matrice[indice] = citire_matrice(&lin, &col, indice); 
                         ++indice; //creste numarul de matrice din memorie 
                         break; 
                 case 'D': 
                         afis_dim_mat(lin, col, indice); 
                         break; 
                 case 'P': 
                         afis_mat(matrice, lin, col, indice); 
                         break; 
                 case 'O': 
                         sortare_mat(matrice, lin, col, indice); 
                         break; 
                 case 'M': 
                         scanf("%d%d", &i1, &i2); 
                         if (i1 >= indice || i2 >= indice || i1 <= -1 || i2 <= -1) { 
                                 printf("No matrix with the given index\n"); 
                         } else if (col[i1] != lin[i2]) { 
                                 printf("Cannot perform matrix multiplication\n"); 
                         } else { 
                                 realoc_mat(&matrice, &lin, &col, indice); 
                                 matrice[indice] = inm_mat(matrice, lin, col, indice, i1, i2); 
                                 indice++; 
                         } 
                         break; 
                 case 'T': 
                         transpun_mat(matrice, lin, col, indice); 
                         break; 
                 case 'C': 
                         scanf("%d", &ind); 
                         if (ind >= indice || ind <= -1) 
                                 printf("No matrix with the given index\n"); 
                         else 
                                 matrice[ind] = redimen_mat(matrice[ind], &lin[ind], &col[ind]); 
                         break; 
                 case 'F': 
                         scanf("%d", &ind); 
                         if (ind >= indice || ind <= -1) { 
                                 printf("No matrix with the given index\n"); 
                         } else { 
                                 sterg_mat(&matrice, &lin, &col, ind, indice); 
                                 indice--; 
                                 if (indice > 0) { 
                                         realoc_mat(&matrice, &lin, &col, indice); 
                                 } else { 
                                         free(matrice); 
                                         free(lin); 
                                         free(col); 
                                 } 
                         } 
                         break; 
                 case 'Q': 
                         if (indice > 0) { 
                                 for (int i = 0; i < indice; i++) { 
                                         for (int j = 0; j < lin[i]; j++) 
                                                 free(matrice[i][j]); 
                                         free(matrice[i]); 
                                 } 
                                 free(matrice); 
                                 free(lin); free(col); 
                         } 
                         stop = 0; 
                         break; 
                 case '\n': 
                         break; 
                 default: 
                         if (comanda >= 'A' && comanda <= 'Z') 
                                 printf("Unrecognized command\n"); 
                         break; 
                         } 
                 } 
         return 0; 
 }
