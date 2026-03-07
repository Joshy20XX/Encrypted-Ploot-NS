/**
 * A ploot class file to handle all the ploots we dragged in our program
 */
#ifndef PLOOT_H
#define PLOOT_H

#include <iostream>
#include <string>
#include <map>

class Ploot {
    private:
        int normal;
        int poison;
        int fire;
        int devil;
        int whimsy;
        int parasitic;
        int bunny;
        int rat;
        int scary;
        int gloom;
        std::string name;
        int age;
        int kills;
        std::string origin;
        bool shiny;
        std::string timestamp; //Get the time of the generated ploot
        std::string sounds; //Sounds
        std::string sparkle; //Texture effect file path
        std::string sound_call;
        std::string sound_collection_complete;
        std::string sound_collection_walk;
        std::string sound_death;
        std::string sound_hit;
        std::string sound_panic;
        std::string sound_rare;
        std::string sound_thrown;
        std::map<std::string, std::string> ploot_dict; 

    //Ploot Constructor with default values
    public: 
        Ploot(); //Construct the ploot with the default values
        void info(); //Print the ploot info

        //Pass in our ploot text file and our dictionary
        void parsePloot(std::ifstream& ploot_stream);

        //Get and set our ploot stats
        std::string getName(); 
        std::string setName(std::string newname);

        std::string getOrigin();
        std::string setOrigin(std::string origin_place);

        int getAge();
        int setAge(std::string newage);

        int getNormal();
        int setNormal(std::string new_normal);

        int getPoison();
        int setPoison(std::string poison);
        
        int getFire();
        int setFire(std::string fire_lvl);

        int getDevil();
        int setDevil(std::string devil);

        int getWhimsy();
        int setWhimsy(std::string whimsy);

        int getParasitic();
        int setParasitic(std::string parasitic);

        int getBunny();
        int setBunny(std::string bunny);

        int getRat();
        int setRat(std::string rat);

        int getGloom();
        int setGloom(std::string gloom);

        int getScary();
        int setScary(std::string how_scary);

        int getKills();
        int setKills(std::string n_kills); //double kill, TRIPLE KILL, SLAUGTHER FRENZY

        bool getShiny();
        bool setShiny(std::string is_shiny);

        std::string getTimestamp();
        std::string setTimestamp(std::string get_timestamp);


        std::string getSounds();
        std::string setSounds(std::string b64_sounds);

        std::string getSparkle();
        std::string setSparkle(std::string b64_sparkle);

        std::string getSoundCall();
        std::string setSoundCall(std::string sound_call);

        std::string getSoundCollectionComplete();
        std::string setSoundCollectionComplete(std::string sound_collection_complete);

        std::string getDeathSound();
        std::string setDeathSound(std::string death_sound);

        std::string getHitSound();
        std::string setHitSound(std::string hit_sound);

        std::string getPanicSound();
        std::string setPanicSound(std::string panic_sound);

        std::string getRareSound();
        std::string setRareSound(std::string rare_sound);

        std::string getThrownSound();
        std::string setThrownSound(std::string thrown_sound);
};
#endif