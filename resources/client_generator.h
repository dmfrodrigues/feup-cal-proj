#ifndef GENERATOR_H_INCLUDED
#define GENERATOR_H_INCLUDED

#include "InterestingNode.h"

#include <vector>
#include <fstream>

class Generator {
public:
    static int run(std::string interesting_path, int n_res){
        srand(time(NULL));

        //Read interesting nodes
        std::vector<InterestingNode> nodes;
        std::ifstream ifs (interesting_path);
        if (!ifs.is_open()) return 1;
        while(!ifs.eof()){
            InterestingNode n;
            ifs >> n;
            nodes.push_back(n);
        }
        ifs.close();

        //List of names
        std::vector<std::string> names_list = {"Son","Man","Brandon","Fidel","Jc","Fabian","Dannie","Jerald","Hal","Doug","Maynard","Santos","Rigoberto","Franklyn","Howard","Dorian","Edgardo","Rogelio","Everette","Nicolas","Johnie","Jeffery","Carlos","Mickey","Moises","Brooks","Jay","Sean","Antony","Scottie","Felton","Alejandro","Antonia","Rudy","Nathanael","Rayford","Curt","Delmar","William","Denis","Anton","Antone","Osvaldo","Isaac","Freeman","Morton","Manuel","Samual","Sterling","Lewis","Liane","Alane","Rima","Magnolia","Valencia","An","Vicenta","Margene","Gia","Shery","Saran","Madge","Raeann","Buffy","Thalia","Hulda","Yuki","Lita","Venice","Easter","Sonya","Delois","Cleora","Sharri","Genie","Kyung","Petronila","Veta","Shawana","Adelia","Karine","Agnus","Inell","Ashton","Marian","Henriette","Cecelia","Tula","Arlean","Valarie","Talitha","Solange","Ila","Sara","Marline","Alexandria","Gaynelle","Patria","Jaclyn","Shauna","Josue","Yuk","Evette","Awilda","Berry","Linette","Ralph","Nathalie","Antony","Darci","Rhiannon","Rigoberto","Chrystal","Clarence","Clora","Genny","Renea","Maryam","Justine","Nada","Denisse","Matilda","Johnnie","Julee","Harriette","Carolann","Sharell","Bradley","Olinda","Leana","Belva","Jamila","Anna","Liane","Flavia","Deangelo","Loriann","Georgette","Latisha","Elias","Danita","Deborah","Shirlene","Simone","Alissa","Eleonor","Ethan","Elisabeth","Carrie","Debi","Louann","Carli","Collin","Scott","Hubert","Arcelia","Janell","Neal","Ida","Jazmine","Liberty","Geraldine","Greg","Clifford","Edna","Klara","Janae","Aisha","Laraine","Earnestine","Christinia","Ebonie","Gerardo","Genaro","Luis","Marcene","Hoa","Marg","Era","Virgie","Karri","Gilberte","Floria","Eda","Emilio","Jesica","Creola","Isadora","Logan","Moira","Kenda","Angelia","Theodora","Molly","Alpha","Rupert","Tod","Sherley","Chadwick","Na"};

        //Write random client
        std::string output_filename = std::to_string(rand() % 99999 + 999) + ".txt";
        std::ofstream ofs (output_filename);
        if (!ofs.open()) return 1;

        for (size_t i = 0 ; i < n_res ; ++i){
            Client temp(names_list.at(rand() % names_list.size()), rand() % 1000000000 + 111111111, rand() % 11 + 1, nodes.at(rand() % nodes.size()), rand() % 86400000000, rand() % 2);
            ofs << temp << std::endl;
        }
        ofs.close();

        return 0;
    }
};

#endif //GENERATOR_H_INCLUDEDS