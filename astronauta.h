#ifndef ASTRONAUTA_H
#define ASTRONAUTA_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Astronauta {

    public:
    string CPF;
    string nome;
    int idade;
    bool vivo;
    bool disponivel;

    Astronauta(string cpf, int idade, string nome) {
        this->CPF = cpf;
        this->idade = idade;
        this->nome = nome;
        this->vivo = true;
        this->disponivel = true;
    }


    
};

class Voo {

    public:
    int codigo;
    vector<string> cpfsPassageiros;
    string estado;

    Voo(int c) {
        this->codigo = c;
        this->cpfsPassageiros = {};
        this->estado = "planejado";

    } 

    int cpfCadastrado(string cpf) {
        for(int i = 0; i < cpfsPassageiros.size(); i++) {
            if(cpfsPassageiros[i] == cpf) {
                return i;
            }
        } return -1;
    }
    

};

bool astronautaExiste(vector<Astronauta>& astronautas, string cpf) {
    for (int i = 0; i < astronautas.size(); i++) {

        if (astronautas[i].CPF == cpf) {
            return true;
        }
    } return false;
}

bool vooExiste(vector<Voo>& voos, int cod) {
    for (int i = 0; i < voos.size(); i++) {

        if (voos[i].codigo == cod) {
            return true;
        }
    } return false;
}

Astronauta& encontrarAstronauta(vector<Astronauta>& astronautas, string cpf) {
    for (int i = 0; i < astronautas.size(); i++) {

        if (astronautas[i].CPF == cpf) {
            return astronautas[i];
        }
    }
}

Voo& encontrarVoo(vector<Voo>& voos, int cod) {
    for (int i = 0; i < voos.size(); i++) {

        if (voos[i].codigo == cod) {
            return voos[i];
        }
    }
}

bool cadastrarAstronauta(vector<Astronauta>& astronautas, string cpf, int idade, string nome) {

    if (astronautaExiste(astronautas, cpf)) {
        cout << "Erro! CPF ja cadastrado." << endl;
        return false;
    }

    Astronauta a(cpf, idade, nome);
    astronautas.push_back(a);

    cout << "Astronauta " << nome << " cadastrado." << endl;
    return true;
}

bool cadastrarVoo(vector<Voo>& voos, int cod) {

    if (vooExiste(voos, cod)) {
        cout << "Erro! Codigo ja cadastrado." << endl;
        return false;
    }

    Voo v(cod);
    voos.push_back(v);

    cout << "Voo " << cod << " cadastrado." << endl;
    return true;
}

bool adicionarAstro(vector<Astronauta>& astronautas, string cpf, vector<Voo>& voos, int cod) {
    if (!astronautaExiste(astronautas, cpf)) {
        cout << "Erro! Astronauta nao cadastrado." << endl;
        return false;
    } if (!vooExiste(voos, cod)) {
        cout << "Erro! Voo nao cadastrado." << endl;
        return false;
    } 

    Voo& voo = encontrarVoo(voos, cod);

    if(voo.estado != "planejado") {
        cout << "Erro! Voo nao esta planejado." << endl;
        return false;
    } if(voo.cpfCadastrado(cpf) >= 0) {
        cout << "Erro! Astronauta ja cadastrado no voo." << endl;
        return false;
    }

    voo.cpfsPassageiros.push_back(cpf);
    return true;
}

bool removerAstro(vector<Astronauta>& astronautas, string cpf, vector<Voo>& voos, int cod) {
    if (!astronautaExiste(astronautas, cpf)) {
        cout << "Erro! Astronauta nao cadastrado." << endl;
        return false;
    } if (!vooExiste(voos, cod)) {
        cout << "Erro! Voo nao cadastrado." << endl;
        return false;
    } 

    Astronauta& astronauta = encontrarAstronauta(astronautas, cpf);
    Voo& voo = encontrarVoo(voos, cod);

    if(voo.estado != "planejado") {
        cout << "Erro! Voo nao esta planejado." << endl;
        return false;
    }
    if(voo.cpfCadastrado(cpf) < 0) {
        cout << "Erro! Astronauta nao esta cadastrado no voo." << endl;
        return false;
    }

    voo.cpfsPassageiros.erase(voo.cpfsPassageiros.begin() + voo.cpfCadastrado(cpf));
    return true;
}

bool lancarVoo(vector<Astronauta>& astronautas, vector<Voo>& voos, int cod) {
    if (!vooExiste(voos, cod)) {
        cout << "Erro! Voo nao cadastrado." << endl;
        return false;
    } 
    Voo& voo = encontrarVoo(voos, cod);
    if(voo.estado != "planejado") {
        cout << "Erro! Voo nao esta planejado." << endl;
        return false;
    } if(voo.cpfsPassageiros.size() < 1) {
        cout << "Erro! Voo sem astronautas." << endl;
        return false;
    } for(int i = 0; i < voo.cpfsPassageiros.size(); i++) {
        Astronauta& astronauta = encontrarAstronauta(astronautas, voo.cpfsPassageiros[i]);
        if(!astronauta.vivo) {
            cout << "Erro! Astronauta " << astronauta.nome << " morto." << endl;
            return false;
        } if(!astronauta.disponivel) {
            cout << "Erro! Astronauta " << astronauta.nome << " indisponível." << endl;
            return false;
        }
    }

    voo.estado = "em curso";
    for(int i = 0; i < voo.cpfsPassageiros.size(); i++) {
        Astronauta& astronauta = encontrarAstronauta(astronautas, voo.cpfsPassageiros[i]);
        astronauta.disponivel = false;
    } 
    return true;
}

bool explodirVoo(vector<Astronauta>& astronautas, vector<Voo>& voos, int cod) {
    if (!vooExiste(voos, cod)) {
        cout << "Erro! Voo nao cadastrado." << endl;
        return false;
    } 
    Voo& voo = encontrarVoo(voos, cod);
    if(voo.estado != "em curso") {
        cout << "Erro! Voo nao esta em curso." << endl;
        return false;
    }

    voo.estado = "finalizado com explosao";
    for(int i = 0; i < voo.cpfsPassageiros.size(); i++) {
        Astronauta& astronauta = encontrarAstronauta(astronautas, voo.cpfsPassageiros[i]);
        astronauta.disponivel = false;
        astronauta.vivo = false;
    } 
    return true;
}

bool finalizarVoo(vector<Astronauta>& astronautas, vector<Voo>& voos, int cod) {
    if (!vooExiste(voos, cod)) {
        cout << "Erro! Voo nao cadastrado." << endl;
        return false;
    } 
    Voo& voo = encontrarVoo(voos, cod);
    if(voo.estado != "em curso") {
        cout << "Erro! Voo nao esta em curso." << endl;
        return false;
    }

    voo.estado = "finalizado com sucesso";
    for(int i = 0; i < voo.cpfsPassageiros.size(); i++) {
        Astronauta& astronauta = encontrarAstronauta(astronautas, voo.cpfsPassageiros[i]);
        astronauta.disponivel = true;
    } 
    return true;
}

void listarVoos(vector<Astronauta>& astronautas, vector<Voo>& voos) {
    const vector<string> estados = {"planejado", "em curso", "finalizado com sucesso", "finalizado com explosao"};
    for(int i = 0; i < estados.size(); i++) {
        cout << "========= voos " << estados[i] << " =========" << endl;
        for(int j = 0; j < voos.size(); j++) {
            if(voos[j].estado == estados[i]) {
                cout << "Codigo: " << voos[j].codigo << endl;
                cout << "Estado: " << voos[j].estado << endl;
                cout << "Astronautas: " << endl;
                for(int i = 0; i < voos[j].cpfsPassageiros.size(); i++) {
                    Astronauta& astronauta = encontrarAstronauta(astronautas, voos[j].cpfsPassageiros[i]);
                    cout << i + 1 << ". " <<  astronauta.nome << " (" << astronauta.CPF << ")" << endl;
                }
                cout << endl; 
            }
        }
        cout << endl;
    }
}

void listarMortos(vector<Astronauta>& astronautas, vector<Voo>& voos) {
    cout << "Lista - astronautas mortos" << endl;
    cout << endl;
    for(int i = 0; i < astronautas.size(); i++) {
        Astronauta& a = astronautas[i];
        if(!a.vivo) {
            cout << "Nome: " << a.nome << endl;
            cout << "CPF: " << a.CPF << endl;
            cout << "Voos: ";
            for(int j = 0; j < voos.size(); j++) {
                if(voos[j].cpfCadastrado(a.CPF) >= 0) {
                    cout << voos[j].codigo << " ";
                }
            } cout << endl;
        }
        cout << endl;
    } 
}



#endif