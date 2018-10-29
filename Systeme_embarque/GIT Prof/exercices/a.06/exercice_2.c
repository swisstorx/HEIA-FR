/**
 * Programmation C: Fonctions
 * solution de l'exercice 2
 */

int global_program_definition = 10;
extern int global_module_declaration;

static int global_module = 11;

static int fnct(
        const int * arg_par_reference,
        int arg_par_valeur
        )
{
    static int var_remanente = 12;
    int var_local_fonction = *arg_par_reference + 13;
    {
        int var_local_bloc = arg_par_valeur + 14;
        var_remanente += var_local_bloc;
    }

    return var_remanente  + var_local_fonction;
}

int main() 
{
    int a1 = global_program_definition + global_module + 15;
    return fnct(&a1, 10);
}