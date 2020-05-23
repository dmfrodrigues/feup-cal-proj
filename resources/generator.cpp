#include "Client.h"
#include "point.h"

#include <stdexcept> 
#include <vector>
#include <fstream>

using namespace std;

#define HOURS_TO_MICROS ((long long)(60)*60*1000000)
#define MIN_TO_MICROS ((long long)(60)*1000000)

long long large_rand(){
    long long r1 = rand();
    long long r2 = rand();
    return (r1 << 32) | r2;
}

void generator(int argc, const char *argv[]){

    if (argc != 4 && argc != 5) throw invalid_argument("invalid number of arguments");
    int n_res = atoi(argv[1]);
    long long start_time = atof(argv[2])*HOURS_TO_MICROS;
    long long end_time   = atof(argv[3])*HOURS_TO_MICROS;
    bool only_trainstation = (argc == 5 && string(argv[4]) == "-t");

    srand(time(NULL));

    //Read interesting nodes
    vector<point_t> nodes;
    ifstream ifs ("../map/processed/AMP.points");
    if (!ifs.is_open()) throw runtime_error("Could not open interesting nodes file");
    int ignore_first_line; ifs >> ignore_first_line;
    while(!ifs.eof()){
        point_t n;
        ifs >> n;
        nodes.push_back(n);
    }
    ifs.close();

    //List of names
    vector<string> names_list = {"Son","Man","Brandon","Fidel","Jc","Fabian","Dannie","Jerald","Hal","Doug","Maynard","Santos","Rigoberto","Franklyn","Howard","Dorian","Edgardo","Rogelio","Everette","Nicolas","Johnie","Jeffery","Carlos","Mickey","Moises","Brooks","Jay","Sean","Antony","Scottie","Felton","Alejandro","Antonia","Rudy","Nathanael","Rayford","Curt","Delmar","William","Denis","Anton","Antone","Osvaldo","Isaac","Freeman","Morton","Manuel","Samual","Sterling","Lewis","Liane","Alane","Rima","Magnolia","Valencia","An","Vicenta","Margene","Gia","Shery","Saran","Madge","Raeann","Buffy","Thalia","Hulda","Yuki","Lita","Venice","Easter","Sonya","Delois","Cleora","Sharri","Genie","Kyung","Petronila","Veta","Shawana","Adelia","Karine","Agnus","Inell","Ashton","Marian","Henriette","Cecelia","Tula","Arlean","Valarie","Talitha","Solange","Ila","Sara","Marline","Alexandria","Gaynelle","Patria","Jaclyn","Shauna","Josue","Yuk","Evette","Awilda","Berry","Linette","Ralph","Nathalie","Antony","Darci","Rhiannon","Rigoberto","Chrystal","Clarence","Clora","Genny","Renea","Maryam","Justine","Nada","Denisse","Matilda","Johnnie","Julee","Harriette","Carolann","Sharell","Bradley","Olinda","Leana","Belva","Jamila","Anna","Liane","Flavia","Deangelo","Loriann","Georgette","Latisha","Elias","Danita","Deborah","Shirlene","Simone","Alissa","Eleonor","Ethan","Elisabeth","Carrie","Debi","Louann","Carli","Collin","Scott","Hubert","Arcelia","Janell","Neal","Ida","Jazmine","Liberty","Geraldine","Greg","Clifford","Edna","Klara","Janae","Aisha","Laraine","Earnestine","Christinia","Ebonie","Gerardo","Genaro","Luis","Marcene","Hoa","Marg","Era","Virgie","Karri","Gilberte","Floria","Eda","Emilio","Jesica","Creola","Isadora","Logan","Moira","Kenda","Angelia","Theodora","Molly","Alpha","Rupert","Tod","Sherley","Chadwick","Na"};

    list<Client> clients;

    for (int i = 0 ; i < n_res ; ++i){
        Client temp(
            names_list.at(rand() % names_list.size()),
            rand() % 90000000 + 100000000,
            nodes.at(rand() % nodes.size()).getCoord(),
            start_time + large_rand() % (end_time - start_time), 
            (only_trainstation ? 0 : rand() % 2)
        );
        clients.push_back(temp);
    }

    cout << clients.size() << "\n";
    for(const Client &c: clients)
        cout << c << "\n";

}

int main(int argc, char *argv[]){   
    try{
        if(argc < 2) throw invalid_argument("at least one argument must be provided");
        generator(argc, const_cast<const char **>(argv));
    }
    catch(const invalid_argument &e){
        cout << "Caught exception: " << e.what() << "\n";
        cout << "Usage: ./generator NUMBER_CLIENTS TIME_START TIME_END\n";
    }
}