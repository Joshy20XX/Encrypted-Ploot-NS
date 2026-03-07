#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <sstream>

#include "ploot.h"

Ploot::Ploot() {
    name = "";
    age = 0;
    normal = 0;
    poison = 0;
    fire = 0;
    devil = 0;
    whimsy = 0;
    parasitic = 0;
    bunny = 0;
    rat = 0;
    gloom = 0;
    scary = 0;
    age = 0;
    kills = 0;
    shiny = false;
    timestamp = "";
    sounds = "";
    sparkle = "";
    sound_call = "";
    sound_collection_complete = "";
    sound_death = "";
    sound_hit = "";
    sound_panic = "";
    sound_rare = "";
    sound_thrown = "";
    std::map<std::string, std::string> ploot_dict; 
}

std::string Ploot::getName() {
    return name;
}

std::string Ploot::setName(std::string newname) {
    this->name = newname;
    return name;
}

int Ploot::getAge() {
    return age;
}

int Ploot::setAge(std::string newage) {
    
    this->age = std::stoi(newage);
    return age;
}

int Ploot::getKills() {return kills;}
int Ploot::setKills(std::string n_kills) {

    this->kills = std::stoi(n_kills);
    return kills;
}

int Ploot::getNormal() {return normal;}
int Ploot::setNormal(std::string normal_lvl) {

    this->normal = std::stoi(normal_lvl);
    return normal;
}

int Ploot::getPoison() {return poison;}
int Ploot::setPoison(std::string poison_lvl) {

    this->poison = std::stoi(poison_lvl);
    return poison;
}

int Ploot::getFire() {return fire;}
int Ploot::setFire(std::string fire_lvl) {

    this->fire = std::stoi(fire_lvl);
    return fire;
}

int Ploot::getDevil() {return devil;}
int Ploot::setDevil(std::string devil_lvl) {

    this->devil = std::stoi(devil_lvl);
    return devil;
}

int Ploot::getWhimsy() {return whimsy;}
int Ploot::setWhimsy(std::string whimsy_lvl) {

    this->whimsy = std::stoi(whimsy_lvl);
    return whimsy;
}

int Ploot::getParasitic() {return whimsy;}
int Ploot::setParasitic(std::string parasitic_lvl) {

    this->parasitic = std::stoi(parasitic_lvl);
    return parasitic;
}

int Ploot::getBunny() {return bunny;}
int Ploot::setBunny(std::string bunny_lvl) {

    this->bunny = std::stoi(bunny_lvl);
    return bunny;
}

int Ploot::getRat() {return rat;}
int Ploot::setRat(std::string rat_lvl) {

    this->rat = std::stoi(rat_lvl);
    return rat;
}

int Ploot::getScary() {return scary;}
int Ploot::setScary(std::string scary_lvl) {

    this->scary = std::stoi(scary_lvl);
    return scary;
}

int Ploot::getGloom() {return gloom;}
int Ploot::setGloom(std::string gloom_lvl) {

    this->gloom = std::stoi(gloom_lvl);
    return gloom;
}

std::string Ploot::getOrigin() {return origin;}
std::string Ploot::setOrigin(std::string origin_place) {

    this->origin = origin_place;
    return origin;
}

std::string Ploot::getTimestamp() {return timestamp;}
std::string Ploot::setTimestamp(std::string get_timestamp) {
    this->timestamp = get_timestamp;
    return timestamp;
}

bool Ploot::getShiny() {return shiny;}
bool Ploot::setShiny(std::string is_shiny) {
    //Convert our boolean string into an actual boolean
    bool isit_shiny;
    std::istringstream(is_shiny) >> std::boolalpha >> isit_shiny;
    this->shiny = isit_shiny;

    return shiny;
}

std::string Ploot::getSounds() {return sounds;}

std::string Ploot::setSounds(std::string b64_sounds) {
    this->sounds = b64_sounds;
    return sounds;
}

std::string Ploot::getSparkle() {return sparkle;}

std::string Ploot::setSparkle(std::string b64_sparkle) {
    this->sparkle = b64_sparkle;
    return sparkle;
};

std::string getSoundCall(std::string sound_call) {return sound_call;}

std::string Ploot::setSoundCall(std::string sound_call) {
    this->sound_call = sound_call;
    return sound_call;
};

std::string Ploot::getSoundCollectionComplete() {return sound_collection_complete;}

std::string Ploot::setSoundCollectionComplete(std::string sound_collection_complete) {
    this->sound_collection_complete = sound_collection_complete;
    return sound_collection_complete;
};

std::string Ploot::getDeathSound() {return sound_death;}

std::string Ploot::setDeathSound(std::string death_sound) {
    this->sound_death = death_sound;
    return sound_death;
};

std::string Ploot::getHitSound() {return sound_hit;}

std::string Ploot::setHitSound(std::string hit_sound) {
    this->sound_hit = hit_sound;
    return sound_hit;
};

std::string Ploot::getPanicSound() {return sound_panic;}

std::string Ploot::setPanicSound(std::string panic_sound) {
    this->sound_panic = panic_sound;
    return sound_panic;
};

std::string Ploot::getRareSound() {return sound_rare;}
std::string Ploot::setRareSound(std::string rare_sound) {
    this->sound_rare = rare_sound;
    return sound_rare;
};

std::string Ploot::getThrownSound() {return sound_thrown;}
std::string Ploot::setThrownSound(std::string thrown_sound) {
    this->sound_thrown = thrown_sound;
    return thrown_sound;
};


void Ploot::info() {
    std::cout << "Ploot info:\n Name: " << name 
    << "\n Age: " << age 
    << "\n Kills: " << kills 
    << "\n Normal: " << normal 
    << "\n Poison: " << poison 
    << "\n Fire: " << fire 
    << "\n Devil: " << devil 
    << "\n Whimsy: " << whimsy 
    << "\n Parasitic: " << parasitic 
    << "\n Bunny: " << bunny 
    << "\n Rat: " << rat 
    << "\n Scary: " << scary 
    << "\n Gloom: " << gloom 
    << "\n Origin: " << origin 
    << "\n Shiny: " << shiny
    << "\n Time stamp: " << timestamp
    << "\n" << std::endl;
}

//We want to create the ploot file on load but for now im just parsing stuff from the text file.
void Ploot::parsePloot(std::ifstream& ploot_stream) {
    //Open a file stream for the ploot file

    //Containers for our values and for looping for each line
    std::string variable, value;
    std::string line;

    if(ploot_stream.is_open()) {
        while (std::getline(ploot_stream, line)) {
            //Parsing stringstream into pairs for data flow
            std::pair<std::string, std::string> sub;

            //Create a stringstream and for each line, separate the ploot parameter and its value
            std::stringstream pss(line);
            std::getline(pss, variable, ':');
            sub.first = variable;
            std::getline(pss, value);
            sub.second = value;

            //Send that data over to a ploot hashmap (a dictionary)
            ploot_dict[sub.first] = sub.second;
        }
    }

    //Dbug
    /*auto item = ploot_dict.find("age");
    if (item != ploot_dict.end()) {
        std::cout << "Found it: " << item->second << std::endl;
    } else {
        std::cout << "Not found" << std::endl;
    }    
    for (auto i=ploot_dict.begin(); i != ploot_dict.end(); ++i) {
        std::cout << i->first << i->second << std::endl;
    }*/
    setName(ploot_dict["name"]);
    setAge(ploot_dict["age"]);
    setKills(ploot_dict["kills"]);
    setNormal(ploot_dict["normal"]);
    setPoison(ploot_dict["poison"]);
    setFire(ploot_dict["fire"]);
    setDevil(ploot_dict["devil"]);
    setWhimsy(ploot_dict["whimsy"]);
    setParasitic(ploot_dict["parasitic"]);
    setBunny(ploot_dict["bunny"]);
    setRat(ploot_dict["rat"]);
    setScary(ploot_dict["scary"]);
    setGloom(ploot_dict["rat"]);
    setOrigin(ploot_dict["origin"]);
    setShiny(ploot_dict["shiny"]);
    setTimestamp(ploot_dict["Time Stamp"]);

    return;
}