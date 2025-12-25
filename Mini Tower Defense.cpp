#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
class Enemy {
public:
    int health;
    int speed;
    int position;
    string type;
    Enemy(string t) {
        type = t;
        position = 0;
        if (t == "Normal") {
            health = 10;
            speed = 1;
        } else if (t == "Fast") {
            health = 6;
            speed = 2;
        } else if (t == "Tank") {
            health = 20;
            speed = 1;
        }
    }
    void move() {
        position += speed;
    }

    bool isDead() {
        return health <= 0;
    }
};
class Tower {
public:
    int damage;
    int range;
    int level;
    Tower() {
        damage = 4;
        range = 3;
        level = 1;
    }
    void upgrade() {
        level++;
        damage += 2;
        range++;
        cout << "Tower upgraded to level " << level << endl;
    }
    void attack(vector<Enemy>& enemies) {
        for (auto &e : enemies) {
            if (e.position <= range && !e.isDead()) {
                e.health -= damage;
                cout << "Tower hits " << e.type
                     << " enemy! Health left: " << e.health << endl;
                break;
            }
        }
    }
};
class Game {
private:
    vector<Enemy> enemies;
    Tower tower;
    int baseHealth;
    int wave;

public:
    Game() {
        baseHealth = 10;
        wave = 1;
    }

    void spawnWave() {
        cout << "\n Wave " << wave << " begins!\n";
        enemies.clear();
        enemies.push_back(Enemy("Normal"));
        enemies.push_back(Enemy("Fast"));
        if (wave >= 2)
            enemies.push_back(Enemy("Tank"));
    }

    void updateEnemies() {
        for (auto &e : enemies) {
            e.move();
            if (e.position >= 10 && !e.isDead()) {
                baseHealth--;
                e.health = 0;
                cout << "Enemy reached base! Base health: "
                     << baseHealth << endl;
            }
        }
    }
    void play() {
        while (baseHealth > 0 && wave <= 5)
 {            spawnWave();
            while (!enemies.empty()) {
                tower.attack(enemies);
                updateEnemies();
                enemies.erase(
                    remove_if(enemies.begin(), enemies.end(),
                              [](Enemy &e) { return e.isDead(); }),
                    enemies.end());
                cout << "Enemies remaining: " << enemies.size() << endl;
                if (enemies.empty())
                    break;
            }
            char choice;
            cout << "\nUpgrade tower? (y/n): ";
            cin >> choice;
            if (choice == 'y' || choice == 'Y')
                tower.upgrade();

            wave++;
        }
        cout << "\n GAME OVER! Base destroyed.\n";
    }
};
int main() {
    Game game;
    game.play();
    return 0;
}
