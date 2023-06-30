#include "CheckEnd.h"

#include <fstream>
#include <nlohmann/json.hpp>

#include "../../headers/Context.h"
#include "../scenes/GameScene.h"
#include "../scenes/Menu.h"

void CheckEnd::start() {}
void CheckEnd::update() {}
void CheckEnd::fixedUpdate() {
    auto scene = reinterpret_cast<GameScene *>(gameObject->m_pScene);
    if(scene->m_leftField->m_dontPlay && scene->m_rightField->m_dontPlay){
        std::ifstream f("../game/game_data/leaders.json");

        std::ifstream f_player_name_r("../game/game_data/player.json");
        nlohmann::json player_name_j = nlohmann::json::parse(f_player_name_r);
        std::string m_playerName = player_name_j["name"];
        f_player_name_r.close();

        nlohmann::json json = nlohmann::json::parse(f);

        nlohmann::json q;
        bool write = false;

        for (auto &it : json) {
            nlohmann::json data;

            data["name"] = it["name"];
            if(it["name"] == m_playerName){

                if(it["score"] < scene->m_score){
                    data["score"] = scene->m_score;
                }
                else{
                    data["score"] = it["score"];
                }
                write = true;
            }
            else{
                data["score"] = it["score"];
            }
            q.push_back(data);
        }
        if(!write){
            nlohmann::json w;
            w["name"] = m_playerName;
            w["score"] = scene->m_score;
            q.push_back(w);
        }

        std::sort(q.begin(), q.end(), [](auto t1, auto t2){
            if(t1["score"] > t2["score"]){
                return true;
            }
            else{
                return false;
            }
        });
        if(q.size() > 5){
            q.erase(q.begin()+5, q.end());
        }

        f.close();
        std::ofstream f_w("../game/game_data/leaders.json");
        f_w << std::setw(4) << q;
        f_w.close();


        std::ofstream f_w_2("../game/game_data/player_levels.json");
        f_w_2 << "[ ]";

        auto context = scene->getContext();
        if(scene->m_menu) {
            scene->m_menu->updateLeaders();
            return dynamic_cast<Window *>(context->getWindow())
                ->setCurrentScene(scene->m_menu);
        }

    }
}
