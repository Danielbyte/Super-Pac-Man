#include "gameWorld.h"

GameWorld::GameWorld(){}

void GameWorld::loadMapFromFile()
{
    std::ifstream gameMapFile("../resources/gameMap.txt");
    int count = 0;
    std::string line;
    if(gameMapFile.is_open())
    {
        int tileId;
        while (std::getline(gameMapFile, line))
        {
            std::vector<std::string>row;
            std::istringstream iss(line);// Ignore spaces as they are just separators
            std::string tile;

            while (iss >> tile)
                  row.push_back(tile);//read each tile  
            
            if (!row.empty()) 
                gameMap.push_back(row);
                
            numberOfColumns = std::max(numberOfColumns, static_cast<int>(row.size()));
            ++numberOfRows;
        }
    }
    gameMapFile.close();
    placeFruits();
    placeKeys();
    placeLocks();
}

void GameWorld::placeFruits()
{
    std::shared_ptr<Fruit>fruit1 = std::make_shared<Fruit>();
    fruit1->setPosition(56.5f,152.5f);
    fruits.push_back(fruit1);

    std::shared_ptr<Fruit>fruit2 = std::make_shared<Fruit>();
    fruit2->setPosition(104.5f,152.5f);
    fruits.push_back(fruit2);

    std::shared_ptr<Fruit>fruit3 = std::make_shared<Fruit>();
    fruit3->setPosition(104.5f,200.5f);
    fruits.push_back(fruit3);

    std::shared_ptr<Fruit>fruit4 = std::make_shared<Fruit>();
    fruit4->setPosition(104.5f,248.5f);
    fruits.push_back(fruit4);

    std::shared_ptr<Fruit>fruit5 = std::make_shared<Fruit>();
    fruit5->setPosition(440.0f,345.0f);
    fruits.push_back(fruit5);

    std::shared_ptr<Fruit>fruit6 = std::make_shared<Fruit>();
    fruit6->setPosition(440.0f,392.0f);
    fruits.push_back(fruit6);

    std::shared_ptr<Fruit>fruit7 = std::make_shared<Fruit>();
    fruit7->setPosition(440.0f,152.5f);
    fruits.push_back(fruit7);

    std::shared_ptr<Fruit>fruit8 = std::make_shared<Fruit>();
    fruit8->setPosition(391.0f,152.5f);
    fruits.push_back(fruit8);

    std::shared_ptr<Fruit>fruit9 = std::make_shared<Fruit>();
    fruit9->setPosition(391.0f,200.5f);
    fruits.push_back(fruit9);

    std::shared_ptr<Fruit>fruit10 = std::make_shared<Fruit>();
    fruit10->setPosition(391.0f,248.5f);
    fruits.push_back(fruit10);

    std::shared_ptr<Fruit>fruit11 = std::make_shared<Fruit>();
    fruit11->setPosition(485.0f,248.5f);
    fruits.push_back(fruit11);

    std::shared_ptr<Fruit>fruit12 = std::make_shared<Fruit>();
    fruit12->setPosition(6.5f,249.5f);
    fruits.push_back(fruit12);

    std::shared_ptr<Fruit>fruit13 = std::make_shared<Fruit>();
    fruit13->setPosition(56.5f,345.0f);
    fruits.push_back(fruit13);

    std::shared_ptr<Fruit>fruit14 = std::make_shared<Fruit>();
    fruit14->setPosition(56.5f,392.0f);
    fruits.push_back(fruit14);

    std::shared_ptr<Fruit>fruit15 = std::make_shared<Fruit>();
    fruit15->setPosition(150.5f,536.0f);
    fruits.push_back(fruit15);

    std::shared_ptr<Fruit>fruit16 = std::make_shared<Fruit>();
    fruit16->setPosition(200.5f,536.0f);
    fruits.push_back(fruit16);

    std::shared_ptr<Fruit>fruit17 = std::make_shared<Fruit>();
    fruit17->setPosition(247.5f,536.0f);
    fruits.push_back(fruit17);

    std::shared_ptr<Fruit>fruit18 = std::make_shared<Fruit>();
    fruit18->setPosition(297.5f,536.0f);
    fruits.push_back(fruit18);

    std::shared_ptr<Fruit>fruit19 = std::make_shared<Fruit>();
    fruit19->setPosition(345.5f,536.0f);
    fruits.push_back(fruit19);

    std::shared_ptr<Fruit>fruit20 = std::make_shared<Fruit>();
    fruit20->setPosition(150.5f,55.5f);
    fruits.push_back(fruit20);

    std::shared_ptr<Fruit>fruit21 = std::make_shared<Fruit>();
    fruit21->setPosition(200.5f,55.5f);
    fruits.push_back(fruit21);

    std::shared_ptr<Fruit>fruit22 = std::make_shared<Fruit>();
    fruit22->setPosition(247.5f,55.5f);
    fruits.push_back(fruit22);

    std::shared_ptr<Fruit>fruit23 = std::make_shared<Fruit>();
    fruit23->setPosition(297.5f,55.5f);
    fruits.push_back(fruit23);

    std::shared_ptr<Fruit>fruit24 = std::make_shared<Fruit>();
    fruit24->setPosition(345.5f,55.5f);
    fruits.push_back(fruit24);

    std::shared_ptr<Fruit>fruit25 = std::make_shared<Fruit>();
    fruit25->setPosition(297.5f,345.0f);
    fruits.push_back(fruit25);

    std::shared_ptr<Fruit>fruit26 = std::make_shared<Fruit>();
    fruit26->setPosition(343.5f,392.0f);
    fruits.push_back(fruit26);

    std::shared_ptr<Fruit>fruit27 = std::make_shared<Fruit>();
    fruit27->setPosition(343.5f,440.5f);
    fruits.push_back(fruit27);

    std::shared_ptr<Fruit>fruit28 = std::make_shared<Fruit>();
    fruit28->setPosition(200.5f,345.0f);
    fruits.push_back(fruit28);

    std::shared_ptr<Fruit>fruit29 = std::make_shared<Fruit>();
    fruit29->setPosition(150.5f,392.0f);
    fruits.push_back(fruit29);

    std::shared_ptr<Fruit>fruit30 = std::make_shared<Fruit>();
    fruit30->setPosition(150.5f,440.5f);
    fruits.push_back(fruit30);

    std::shared_ptr<Fruit>fruit31 = std::make_shared<Fruit>();
    fruit31->setPosition(247.5f,440.5f);
    fruits.push_back(fruit31);

    std::shared_ptr<Fruit>superPellet1 = std::make_shared<Fruit>();
    superPellet1->setPosition(154.5f,345.5f);
    superPellet1->markAsSuperPellet();
    fruits.push_back(superPellet1);
    
    std::shared_ptr<Fruit>superPellet2 = std::make_shared<Fruit>();
    superPellet2->setPosition(440.0f,345.5f);
    superPellet2->markAsSuperPellet();
    fruits.push_back(superPellet2);

    std::shared_ptr<Fruit>superPellet3 = std::make_shared<Fruit>();
    superPellet3->setPosition(343.5f,345.0f);
    superPellet3->markAsSuperPellet();
    fruits.push_back(superPellet3);

    std::shared_ptr<Fruit>powerPellet1 = std::make_shared<Fruit>();
    powerPellet1->setPosition(57.0f,57.5f);
    powerPellet1->markAsPowerPellet();
    fruits.push_back(powerPellet1);

    std::shared_ptr<Fruit>powerPellet2 = std::make_shared<Fruit>();
    powerPellet2->setPosition(440.0f,56.0f);
    powerPellet2->markAsPowerPellet();
    fruits.push_back(powerPellet2);

    std::shared_ptr<Fruit>powerPellet3 = std::make_shared<Fruit>();
    powerPellet3->setPosition(56.0f,490.0f);
    powerPellet3->markAsPowerPellet();
    fruits.push_back(powerPellet3);

    std::shared_ptr<Fruit>powerPellet4 = std::make_shared<Fruit>();
    powerPellet4->setPosition(440.0f,490.0f);
    powerPellet4->markAsPowerPellet();
    fruits.push_back(powerPellet4);
}

void GameWorld::placeKeys()
{
    std::shared_ptr<Key>key1 = std::make_shared<Key>();
    key1->setPosition(16.5f,8.5f);
    key1->setLockIds(2, 3, 27);
    keys.push_back(key1);

    std::shared_ptr<Key>key2 = std::make_shared<Key>();
    key2->setPosition(496.5f,8.5f);
    key2->setLockIds(19, 20, 36);
    keys.push_back(key2);

    std::shared_ptr<Key>key3 = std::make_shared<Key>();
    key3->setPosition(16.5f,536.0f);
    key3->setLockIds(7, 8);
    keys.push_back(key3);

    std::shared_ptr<Key>key4 = std::make_shared<Key>();
    key4->setPosition(496.5f,536.0f);
    key4->setLockIds(9, 10);
    keys.push_back(key4);

    std::shared_ptr<Key>key5 = std::make_shared<Key>();
    key5->setPosition(111.0f,488.0f);
    key5->setLockIds(11, 12);
    keys.push_back(key5);

    std::shared_ptr<Key>key6 = std::make_shared<Key>();
    key6->setPosition(402.0f,488.0f);
    key6->setLockIds(13, 14);
    keys.push_back(key6);

    std::shared_ptr<Key>key7 = std::make_shared<Key>();
    key7->setPosition(496.5f,290.0f);
    key7->setLockIds(15, 16);
    keys.push_back(key7);

    std::shared_ptr<Key>key8 = std::make_shared<Key>();
    key8->setPosition(496.5f,206.5f);
    key8->setLockIds(17, 18, 37);
    keys.push_back(key8);

    std::shared_ptr<Key>key9 = std::make_shared<Key>();
    key9->setPosition(16.5f,206.5f);
    key9->setLockIds(5, 6);
    keys.push_back(key9);

    std::shared_ptr<Key>key10 = std::make_shared<Key>();
    key10->setPosition(402.0f,110.0f);
    key10->setLockIds(21, 22);
    keys.push_back(key10);

    std::shared_ptr<Key>key11 = std::make_shared<Key>();
    key11->setPosition(111.0f,110.0f);
    key11->setLockIds(1, 4);
    keys.push_back(key11);

    std::shared_ptr<Key>key12 = std::make_shared<Key>();
    key12->setPosition(255.0f,390.0f);
    key12->setLockIds(23, 24, 33);
    keys.push_back(key12);

    std::shared_ptr<Key>key13 = std::make_shared<Key>();
    key13->setPosition(16.5f,290.0f);
    key13->setLockIds(25, 26);
    keys.push_back(key13);

    std::shared_ptr<Key>key14 = std::make_shared<Key>();
    key14->setPosition(163.0f,290.0f);
    key14->setLockIds(29, 32, 34);
    keys.push_back(key14);
    
    std::shared_ptr<Key>key15 = std::make_shared<Key>();
    key15->setPosition(353.0f,290.0f);
    key15->setLockIds(30, 31, 35);
    keys.push_back(key15);
}

void GameWorld::placeLocks()
{
    std::shared_ptr<Lock>lock1 = std::make_shared<Lock>();
    lock1->setPosition(56.5f,146.0f);
    lock1->setLockType(LockType::Horizontal);
    lock1->setLockId(1);
    locks.push_back(lock1);

    std::shared_ptr<Lock>lock2 = std::make_shared<Lock>();
    lock2->setPosition(56.5f,93.0f);
    lock2->setLockType(LockType::Horizontal);
    lock2->setLockId(2);
    locks.push_back(lock2);

    std::shared_ptr<Lock>lock3 = std::make_shared<Lock>();
    lock3->setPosition(56.5f,48.0f);
    lock3->setLockType(LockType::Horizontal);
    lock3->setLockId(3);
    locks.push_back(lock3);

    std::shared_ptr<Lock>lock4 = std::make_shared<Lock>();
    lock4->setPosition(56.5f,190.0f);
    lock4->setLockType(LockType::Horizontal);
    lock4->setLockId(4);
    locks.push_back(lock4);

    std::shared_ptr<Lock>lock5 = std::make_shared<Lock>();
    lock5->setPosition(140.0f,240.0f);
    lock5->setLockType(LockType::Vertical);
    lock5->setLockId(5);
    locks.push_back(lock5);

    std::shared_ptr<Lock>lock6 = std::make_shared<Lock>();
    lock6->setPosition(98.5f,240.0f);
    lock6->setLockType(LockType::Vertical);
    lock6->setLockId(6);
    locks.push_back(lock6);

    std::shared_ptr<Lock>lock7 = std::make_shared<Lock>();
    lock7->setPosition(56.5f,336.5f);
    lock7->setLockType(LockType::Horizontal);
    lock7->setLockId(7);
    locks.push_back(lock7);

    std::shared_ptr<Lock>lock8 = std::make_shared<Lock>();
    lock8->setPosition(56.5f,429.0f);
    lock8->setLockType(LockType::Horizontal);
    lock8->setLockId(8);
    locks.push_back(lock8);

    std::shared_ptr<Lock>lock9 = std::make_shared<Lock>();
    lock9->setPosition(56.5f,480.0f);
    lock9->setLockType(LockType::Horizontal);
    lock9->setLockId(9);
    locks.push_back(lock9);
    
    std::shared_ptr<Lock>lock10 = std::make_shared<Lock>();
    lock10->setPosition(56.5f,525.0f);
    lock10->setLockType(LockType::Horizontal);
    lock10->setLockId(10);
    locks.push_back(lock10);

    std::shared_ptr<Lock>lock11 = std::make_shared<Lock>();
    lock11->setPosition(145.0f,536.0f);
    lock11->setLockType(LockType::Vertical);
    lock11->setLockId(11);
    locks.push_back(lock11);

    std::shared_ptr<Lock>lock12 = std::make_shared<Lock>();
    lock12->setPosition(380.5f,536.0f);
    lock12->setLockType(LockType::Vertical);
    lock12->setLockId(12);
    locks.push_back(lock12);

    std::shared_ptr<Lock>lock13 = std::make_shared<Lock>();
    lock13->setPosition(433.5f,525.0f);
    lock13->setLockType(LockType::Horizontal);
    lock13->setLockId(13);
    locks.push_back(lock13);

    std::shared_ptr<Lock>lock14 = std::make_shared<Lock>();
    lock14->setPosition(433.5f,480.0f);
    lock14->setLockType(LockType::Horizontal);
    lock14->setLockId(14);
    locks.push_back(lock14);

    std::shared_ptr<Lock>lock15 = std::make_shared<Lock>();
    lock15->setPosition(433.5f,429.0f);
    lock15->setLockType(LockType::Horizontal);
    lock15->setLockId(15);
    locks.push_back(lock15);

    std::shared_ptr<Lock>lock16 = std::make_shared<Lock>();
    lock16->setPosition(433.5f,336.5f);
    lock16->setLockType(LockType::Horizontal);
    lock16->setLockId(16);
    locks.push_back(lock16);

    std::shared_ptr<Lock>lock17 = std::make_shared<Lock>();
    lock17->setPosition(433.5f,189.0f);
    lock17->setLockType(LockType::Horizontal);
    lock17->setLockId(17);
    locks.push_back(lock17);

    std::shared_ptr<Lock>lock18 = std::make_shared<Lock>();
    lock18->setPosition(433.5f,146.0f);
    lock18->setLockType(LockType::Horizontal);
    lock18->setLockId(18);
    locks.push_back(lock18);

    std::shared_ptr<Lock>lock19 = std::make_shared<Lock>();
    lock19->setPosition(433.5f,93.0f);
    lock19->setLockType(LockType::Horizontal);
    lock19->setLockId(19);
    locks.push_back(lock19);

    std::shared_ptr<Lock>lock20 = std::make_shared<Lock>();
    lock20->setPosition(433.5f,48.0f);
    lock20->setLockType(LockType::Horizontal);
    lock20->setLockId(20);
    locks.push_back(lock20);

    std::shared_ptr<Lock>lock21 = std::make_shared<Lock>();
    lock21->setPosition(481.0f,248.0f);
    lock21->setLockType(LockType::Vertical);
    lock21->setLockId(21);
    locks.push_back(lock21);

    std::shared_ptr<Lock>lock22 = std::make_shared<Lock>();
    lock22->setPosition(524.0f,248.0f);
    lock22->setLockType(LockType::Vertical);
    lock22->setLockId(22);
    locks.push_back(lock22);

    std::shared_ptr<Lock>lock23 = std::make_shared<Lock>();
    lock23->setPosition(2.5f,248.0f);
    lock23->setLockType(LockType::Vertical);
    lock23->setLockId(23);
    locks.push_back(lock23);

    std::shared_ptr<Lock>lock24 = std::make_shared<Lock>();
    lock24->setPosition(45.0f,248.0f);
    lock24->setLockType(LockType::Vertical);
    lock24->setLockId(24);
    locks.push_back(lock24);

    std::shared_ptr<Lock>lock25 = std::make_shared<Lock>();
    lock25->setPosition(145.0f,56.5f);
    lock25->setLockType(LockType::Vertical);
    lock25->setLockId(25);
    locks.push_back(lock25);

    std::shared_ptr<Lock>lock26 = std::make_shared<Lock>();
    lock26->setPosition(381.0f,54.5f);
    lock26->setLockType(LockType::Vertical);
    lock26->setLockId(26);
    locks.push_back(lock26);

    std::shared_ptr<Lock>lock27 = std::make_shared<Lock>();
    lock27->setPosition(247.0f,51.0f);
    lock27->setLockType(LockType::Horizontal);
    lock27->setLockId(27);
    locks.push_back(lock27);

    std::shared_ptr<Lock>lock28 = std::make_shared<Lock>();
    lock28->setPosition(247.0f,143.8f);
    lock28->setLockType(LockType::Horizontal);
    lock28->setToGhostHouseLock();
    lock28->setLockId(28);
    locks.push_back(lock28);

    std::shared_ptr<Lock>lock29 = std::make_shared<Lock>();
    lock29->setPosition(152.0f,334.0f);
    lock29->setLockId(29);
    lock29->setLockType(LockType::Horizontal);
    locks.push_back(lock29);

    std::shared_ptr<Lock>lock30 = std::make_shared<Lock>();
    lock30->setPosition(337.0f,334.0f);
    lock30->setLockType(LockType::Horizontal);
    lock30->setLockId(30);
    locks.push_back(lock30);

    std::shared_ptr<Lock>lock31 = std::make_shared<Lock>();
    lock31->setPosition(337.0f,477.0f);
    lock31->setLockType(LockType::Horizontal);
    lock31->setLockId(31);
    locks.push_back(lock31);

    std::shared_ptr<Lock>lock32 = std::make_shared<Lock>();
    lock32->setPosition(152.5f,477.0f);
    lock32->setLockType(LockType::Horizontal);
    lock32->setLockId(32);
    locks.push_back(lock32);

    std::shared_ptr<Lock>lock33 = std::make_shared<Lock>();
    lock33->setPosition(247.0f,477.0f);
    lock33->setLockType(LockType::Horizontal);
    lock33->setLockId(33);
    locks.push_back(lock33);

    std::shared_ptr<Lock>lock34 = std::make_shared<Lock>();
    lock34->setPosition(237.0f,344.0f);
    lock34->setLockType(LockType::Vertical);
    lock34->setLockId(34);
    locks.push_back(lock34);

    std::shared_ptr<Lock>lock35 = std::make_shared<Lock>();
    lock35->setPosition(289.0f,344.0f);
    lock35->setLockType(LockType::Vertical);
    lock35->setLockId(35);
    locks.push_back(lock35);

    std::shared_ptr<Lock>lock36 = std::make_shared<Lock>();
    lock36->setPosition(385.0f,245.0f);
    lock36->setLockType(LockType::Vertical);
    lock36->setLockId(36);
    locks.push_back(lock36);

    std::shared_ptr<Lock>lock37 = std::make_shared<Lock>();
    lock37->setPosition(428.0f,245.0f);
    lock37->setLockType(LockType::Vertical);
    lock37->setLockId(37);
    locks.push_back(lock37);
}

void GameWorld::createStar(std::vector<std::shared_ptr<Fruit>>& fruits)
{
    //Delete star after a certain time elapse
    for(auto& fruit : fruits)
    {
        auto isStar = fruit->getIsStar();
        auto lifetime = fruit->getLifeTime();
        if (isStar && lifetime >= 7.0f)
        {
            fruit->markForDeletion();
        }
    }

    auto time = star_creation_watch.elapsedTime();
    if (time >= 15.0f)
    {
        placeStar(fruits);
        restartStarCreationWatch();
    }
}

void GameWorld::placeStar(std::vector<std::shared_ptr<Fruit>>& fruits)
{
    auto star = std::make_shared<Fruit>();
    star->setPosition(249.0f, 297.0f);
    star->markAsStar();
    fruits.push_back(star);
}

void GameWorld::restartStarCreationWatch()
{
    star_creation_watch.restartTimer();
}

int GameWorld::getNumberOfColumns() const
{
    return numberOfColumns;
}

int GameWorld::getNumberOfRows() const
{
    return numberOfRows;
}

std::vector<std::vector<std::string>> GameWorld::gameMap = {};//Static member variables are accessed at class level
std::vector<std::shared_ptr<Fruit>> GameWorld::fruits = {};
std::vector<std::shared_ptr<Key>> GameWorld::keys = {};
std::vector<std::shared_ptr<Lock>> GameWorld::locks = {};

int GameWorld::numberOfColumns = 0;

int GameWorld::numberOfRows = 0;

const std::vector<std::vector<std::string>>& GameWorld::getGameMap()
{
    return gameMap;
}

std::vector<std::shared_ptr<Fruit>>& GameWorld::getMazeFruits()
{
    return fruits;
}

std::vector<std::shared_ptr<Key>>& GameWorld::getMazeKeys()
{
    return keys;
}

std::vector<std::shared_ptr<Lock>>& GameWorld::getMazeLocks()
{
    return locks;
}