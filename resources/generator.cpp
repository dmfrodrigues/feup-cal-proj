#include "Client.h"
#include "point.h"

#include <stdexcept> 
#include <vector>
#include <fstream>

#define HOURS_TO_MICROS ((long long)(60)*60*1000000)
#define MIN_TO_MICROS ((long long)(60)*1000000)
#define START_TIME (8*HOURS_TO_MICROS)
#define END_TIME (8*HOURS_TO_MICROS + 20*MIN_TO_MICROS)

void generator(int argc, const char *argv[]){

    if (argc != 2) throw std::invalid_argument("invalid number of arguments");
    int n_res = atoi(argv[1]);

    srand(time(NULL));

    //Read interesting nodes
    std::vector<point_t> nodes;
    std::ifstream ifs ("../map/processed/AMP.points");
    if (!ifs.is_open()) throw std::runtime_error("Could not open interesting nodes file");
    int ignore_first_line; ifs >> ignore_first_line;
    while(!ifs.eof()){
        point_t n;
        ifs >> n;
        nodes.push_back(n);
    }
    ifs.close();

    //List of names
    std::vector<std::string> names_list = {"Son","Man","Brandon","Fidel","Jc","Fabian","Dannie","Jerald","Hal","Doug","Maynard","Santos","Rigoberto","Franklyn","Howard","Dorian","Edgardo","Rogelio","Everette","Nicolas","Johnie","Jeffery","Carlos","Mickey","Moises","Brooks","Jay","Sean","Antony","Scottie","Felton","Alejandro","Antonia","Rudy","Nathanael","Rayford","Curt","Delmar","William","Denis","Anton","Antone","Osvaldo","Isaac","Freeman","Morton","Manuel","Samual","Sterling","Lewis","Liane","Alane","Rima","Magnolia","Valencia","An","Vicenta","Margene","Gia","Shery","Saran","Madge","Raeann","Buffy","Thalia","Hulda","Yuki","Lita","Venice","Easter","Sonya","Delois","Cleora","Sharri","Genie","Kyung","Petronila","Veta","Shawana","Adelia","Karine","Agnus","Inell","Ashton","Marian","Henriette","Cecelia","Tula","Arlean","Valarie","Talitha","Solange","Ila","Sara","Marline","Alexandria","Gaynelle","Patria","Jaclyn","Shauna","Josue","Yuk","Evette","Awilda","Berry","Linette","Ralph","Nathalie","Antony","Darci","Rhiannon","Rigoberto","Chrystal","Clarence","Clora","Genny","Renea","Maryam","Justine","Nada","Denisse","Matilda","Johnnie","Julee","Harriette","Carolann","Sharell","Bradley","Olinda","Leana","Belva","Jamila","Anna","Liane","Flavia","Deangelo","Loriann","Georgette","Latisha","Elias","Danita","Deborah","Shirlene","Simone","Alissa","Eleonor","Ethan","Elisabeth","Carrie","Debi","Louann","Carli","Collin","Scott","Hubert","Arcelia","Janell","Neal","Ida","Jazmine","Liberty","Geraldine","Greg","Clifford","Edna","Klara","Janae","Aisha","Laraine","Earnestine","Christinia","Ebonie","Gerardo","Genaro","Luis","Marcene","Hoa","Marg","Era","Virgie","Karri","Gilberte","Floria","Eda","Emilio","Jesica","Creola","Isadora","Logan","Moira","Kenda","Angelia","Theodora","Molly","Alpha","Rupert","Tod","Sherley","Chadwick","Na"};

    //Write random client
    std::string output_filename = "clients_" + std::to_string(rand() % 99999 + 999) + ".clients";
    std::ofstream ofs (output_filename);
    if (!ofs.is_open()) throw std::runtime_error("Could not create output file");

    std::list<Client> clients;

    for (int i = 0 ; i < n_res ; ++i){
        Client temp(
            names_list.at(rand() % names_list.size()),
            rand() % 90000000 + 100000000,
            nodes.at(rand() % nodes.size()).getCoord(),
            START_TIME + rand() % (END_TIME - START_TIME), 
            rand() % 2
        );
        clients.push_back(temp);
    }

    ofs << clients.size() << "\n";
    for(const Client &c: clients)
        ofs << c << "\n";

}

int main(int argc, char *argv[]){   
    try{
        if(argc < 2) throw std::invalid_argument("at least one argument must be provided");
        generator(argc, const_cast<const char **>(argv));
    }
    catch(const std::invalid_argument &e){
        std::cout << "Caught exception: " << e.what() << "\n";
        std::cout << "Usage: ./generator INTERESTING_PATH nres\n";
    }
}