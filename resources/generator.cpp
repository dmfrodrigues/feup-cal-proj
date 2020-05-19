#include "InterestingNode.h"
#include "Client.h"

#include <stdexcept> 
#include <vector>
#include <fstream>

void generator(int argc, const char *argv[]){

    if (argc != 3) throw std::invalid_argument("invalid number of arguments");
    std::string interesting_path = argv[1];
    int n_res = atoi(argv[2]);

    srand(time(NULL));

    //Read interesting nodes
    std::vector<InterestingNode> nodes;
    std::ifstream ifs (interesting_path);
    if (!ifs.is_open()) throw std::runtime_error("Could not open interesting nodes file");
    while(!ifs.eof()){
        InterestingNode n;
        ifs >> n;
        nodes.push_back(n);
    }
    ifs.close();

    //List of names
    std::vector<std::string> names_list = {"Son","Man","Brandon","Fidel","Jc","Fabian","Dannie","Jerald","Hal","Doug","Maynard","Santos","Rigoberto","Franklyn","Howard","Dorian","Edgardo","Rogelio","Everette","Nicolas","Johnie","Jeffery","Carlos","Mickey","Moises","Brooks","Jay","Sean","Antony","Scottie","Felton","Alejandro","Antonia","Rudy","Nathanael","Rayford","Curt","Delmar","William","Denis","Anton","Antone","Osvaldo","Isaac","Freeman","Morton","Manuel","Samual","Sterling","Lewis","Liane","Alane","Rima","Magnolia","Valencia","An","Vicenta","Margene","Gia","Shery","Saran","Madge","Raeann","Buffy","Thalia","Hulda","Yuki","Lita","Venice","Easter","Sonya","Delois","Cleora","Sharri","Genie","Kyung","Petronila","Veta","Shawana","Adelia","Karine","Agnus","Inell","Ashton","Marian","Henriette","Cecelia","Tula","Arlean","Valarie","Talitha","Solange","Ila","Sara","Marline","Alexandria","Gaynelle","Patria","Jaclyn","Shauna","Josue","Yuk","Evette","Awilda","Berry","Linette","Ralph","Nathalie","Antony","Darci","Rhiannon","Rigoberto","Chrystal","Clarence","Clora","Genny","Renea","Maryam","Justine","Nada","Denisse","Matilda","Johnnie","Julee","Harriette","Carolann","Sharell","Bradley","Olinda","Leana","Belva","Jamila","Anna","Liane","Flavia","Deangelo","Loriann","Georgette","Latisha","Elias","Danita","Deborah","Shirlene","Simone","Alissa","Eleonor","Ethan","Elisabeth","Carrie","Debi","Louann","Carli","Collin","Scott","Hubert","Arcelia","Janell","Neal","Ida","Jazmine","Liberty","Geraldine","Greg","Clifford","Edna","Klara","Janae","Aisha","Laraine","Earnestine","Christinia","Ebonie","Gerardo","Genaro","Luis","Marcene","Hoa","Marg","Era","Virgie","Karri","Gilberte","Floria","Eda","Emilio","Jesica","Creola","Isadora","Logan","Moira","Kenda","Angelia","Theodora","Molly","Alpha","Rupert","Tod","Sherley","Chadwick","Na"};

    //Write random client
    std::string output_filename = "clients_" + std::to_string(rand() % 99999 + 999) + ".txt";
    std::ofstream ofs (output_filename);
    if (!ofs.is_open()) throw std::runtime_error("Could not open output file");

    for (int i = 0 ; i < n_res ; ++i){
        Client temp(names_list.at(rand() % names_list.size()), rand() % 1000000000 + 111111111, rand() % 11 + 1, nodes.at(rand() % nodes.size()), rand() % 86400000000, rand() % 2);
        ofs << temp << std::endl;
    }
    ofs.close();
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