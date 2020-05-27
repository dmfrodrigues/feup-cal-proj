#include "input_generator.h"

long long large_rand(){
    long long r1 = rand();
    long long r2 = rand();
    return (r1 << 32) | r2;
}

InputGenerator::InputGenerator(string points_relative_path_, string output_path_, int n_res_, long long start_time_, long long end_time_, bool only_trainstation_){
    this->points_relative_path = points_relative_path_;
    this->output_path = output_path_;
    this->n_res = n_res_;
    this->start_time = start_time_;
    this->end_time = end_time_;
    this->only_trainstation = only_trainstation_;
}

void InputGenerator::run(){
    //srand(time(NULL));

    //Read interesting nodes
    vector<point_t> nodes;
    ifstream ifs (points_relative_path);
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

    std::ofstream ofs; ofs.exceptions(std::iostream::failbit | std::iostream::badbit);
    try{
        ofs.open(output_path);
    } catch(...){
        std::cerr << "errno=" << errno << std::endl;
    }
    ofs << clients.size() << "\n";
    for(const Client &c: clients)
        ofs << c << "\n";
    ofs.close();
}

string InputGenerator::getOutputPath() const{
    return output_path;
}