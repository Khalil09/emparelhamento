#include<bits/stdc++.h>

using namespace std;

#define iv pair<int, vector<int>>

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
    profs[no].first = f;
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

int main(){
    int formacoes, prof, escola, preferecia;
    int esc[5];
    string teste;
    FILE *fp;

    Prof p(100);
    Escola e(50);

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

}