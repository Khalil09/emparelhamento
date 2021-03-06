//João Gabriel Lima Neves 150131992
// seu nome e matricula Khalil
#include <bits/stdc++.h>

using namespace std;

#define iv pair<int, vector<int>>
#define it pair<int, int>



class Prof{
    private:
        vector<iv> profs;
    public:
        Prof(int size);
        void add_aresta(int no1, int no2);
        void add_formacao(int no, int f);
        void print();
        iv& operator[](int  index);
};

Prof::Prof(int size){
    for(int i = 0; i < size; i++){
       iv a;
       profs.push_back(a);
    }
}

iv& Prof::operator[](int index){
    if (index > profs.size() || index < 0)
        throw std::out_of_range("Index out of range");
    return profs[index];
}

void Prof::add_formacao(int no, int f){
    profs[no-1].first = f;
}

void Prof::add_aresta(int no1, int no2){
    profs[no1-1].second.push_back(no2-1);
}

void Prof::print(){
    for(int i = 0; i < 100; i++){
        cout << i << " == " << profs[i].first << endl;
            cout << "  |--> ";
        for(int j = 0; j < 5; j++){
            cout << " | " << profs[i].second[j];
        }
        cout << endl;
    }
}

class Escola{
    private:
        vector<int> escolas;
    public:
        Escola(int size);
        void add_preferencia(int no, int pre);
        void print();
        int& operator[](int  index);

};

Escola::Escola(int size){
    for(int i = 0; i < size; i++){
        escolas.push_back(0);
    }
}

int& Escola::operator[](int index){
    if (index > escolas.size() || index < 0)
    throw std::out_of_range("Index out of range");
    return escolas[index];
}

void Escola::print(){
    for(int i = 0; i < 50; i++){
        cout << i << " -> " << escolas[i] << endl;
    }
}

void Escola::add_preferencia(int no, int pre){
    escolas[no-1] = pre;
}

class Emparelho{
    private:
        int professor_livre(int alocado[100]);
        vector<it> em;
    public:
        Emparelho(int size);
        void emparelha(Escola e, Prof p);
        void print();
        it& operator[](int index);    
};

Emparelho::Emparelho(int size){
    for(int i = 0; i < size; i++){
        it a;
        a.first = -1;
        a.second = -1;
        em.push_back(a);
    }
}

int Emparelho::professor_livre(int alocado[100]){
    for(int i = 0; i < 100; i++){
        if(alocado[i] == 0){
            return i;
        }
    }
    return -1;
}

void Emparelho::emparelha(Escola e, Prof p){
    int alocado[100];
    int j, k, achou;
    for(int i = 0; i < 100 ; i++){
        alocado[i] = 0;
    }
    while(professor_livre(alocado) != -1){
        j = professor_livre(alocado);
        achou = 0;
        k = 0;
        while(achou == 0){
            if(e[p[j].second[k]] <= p[j].first){    
                if(em[p[j].second[k]].first == -1 || em[p[j].second[k]].second == -1){
                    if(em[p[j].second[k]].first == -1){
                        em[p[j].second[k]].first = j;
                    }
                    else{
                        em[p[j].second[k]].second = j;
                    }
                    achou = 1;
                    alocado[j] = 1;
                }
                else{
                    if(p[em[p[j].second[k]].first].first <= p[em[p[j].second[k]].second].first ){
                        if(p[em[p[j].second[k]].first].first < p[j].first){
                            alocado[em[p[j].second[k]].first] = 0;
                            em[p[j].second[k]].first = j;
                            alocado[j] = 1;
                            achou = 1;
                        }    
                    }
                    else{
                        if(p[em[p[j].second[k]].second].first < p[j].first){
                            alocado[em[p[j].second[k]].second] = 0;
                            em[p[j].second[k]].second = j;
                            alocado[j] = 1;
                            achou = 1;
                        }    
                    }
                }
            }    
            k++;
            if(k == 5 && achou == 0){
                for(int l = 0; l < 50; l++){
                    if(em[l].first == -1){
                        em[l].first = j;
                        alocado[j] = 1;
                        achou = 1;
                        break;
                    }
                    else{
                        if(em[l].second == -1){
                            em[l].second = j;
                            alocado[j] = 1;
                            achou = 1;
                            break;
                        }
                    }        
                }
            }
        }
    }
}

it& Emparelho::operator[](int index){
    if(index > em.size() || index < 0)
        throw std::out_of_range("Index out of range");
    return em[index];
}

void Emparelho::print(){
    for(int i = 0; i < 50; i++){
        cout <<"Escola-"<< i + 1 << "---> professor"<< em[i].first + 1 <<" professor"<< em[i].second + 1 << endl;
    }
}

int main(){
    int formacoes, prof, escola, preferecia;
    int esc[5];
    string teste;
    FILE *fp;

    Prof p(100);
    Escola e(50);
    Emparelho em(50);

    fp = fopen("professores.txt", "r");

    while(fscanf(fp, "(P%d, %d): (E%d, E%d, E%d, E%d, E%d)\n",
                 &prof,
                 &formacoes,
                 &esc[0],
                 &esc[1],
                 &esc[2],
                 &esc[3],
                 &esc[4]) != EOF)
    {
        p.add_formacao(prof, formacoes);
        for(int i = 0; i < 5; i++){
            p.add_aresta(prof, esc[i]);
        }
    }

    p.print();

    fclose(fp);

    fp = fopen("escolas.txt", "r");

    while(fscanf(fp, "(E%d):(%d)\n", &escola, &preferecia) != EOF)
    {
        e.add_preferencia(escola, preferecia);
    }

    fclose(fp);

    e.print();
    em.emparelha(e,p);
    em.print();
}