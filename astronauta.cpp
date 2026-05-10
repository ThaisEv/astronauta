#include <iostream>
#include <string>
#include <vector>

#include "astronauta.h"

using namespace std;


int main() {
    vector<Astronauta> astronautas;
    vector<Voo> voos;
    string comando;

    while (cin >> comando) {
        if (comando == "FIM") {
            break; 
        }
        if (comando == "CADASTRAR_ASTRONAUTA") {
            string cpf, nome;
            int idade;
            cin >> cpf >> idade;
            getline(cin >> ws, nome);
            
            cadastrarAstronauta(astronautas, cpf, idade, nome);
        }
        if (comando == "CADASTRAR_VOO") {
            int cod;
            cin >> cod;
            
            cadastrarVoo(voos, cod);
        }
        if (comando == "ADICIONAR_ASTRONAUTA") {
            string cpf;
            int cod;
            cin >> cpf >> cod;
            
            adicionarAstro(astronautas, cpf, voos, cod);
        }
        if (comando == "REMOVER_ASTRONAUTA") {
            string cpf;
            int cod;
            cin >> cpf >> cod;
            
            removerAstro(astronautas, cpf, voos, cod);
        }
        if (comando == "LANCAR_VOO") {
            int cod;
            cin >> cod;
            
            lancarVoo(astronautas, voos, cod);
        }
        if (comando == "EXPLODIR_VOO") {
            int cod;
            cin >> cod;
            
            explodirVoo(astronautas, voos, cod);
        }
        if (comando == "FINALIZAR_VOO") {
            int cod;
            cin >> cod;
            
            finalizarVoo(astronautas, voos, cod);
        }
        if (comando == "LISTAR_VOOS") {            
            listarVoos(astronautas, voos);
        }
        if (comando == "LISTAR_MORTOS") {            
            listarMortos(astronautas, voos);
        }
    }

    return 0;
}