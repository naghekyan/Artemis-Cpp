#include "windows.h" 
#include "Artemis/Artemis.h"


class VelocityComponent : public artemis::Component {
public:
    float velocityX;
    float velocityY;

    VelocityComponent(float velocityX, float velocityY)
    {
        this->velocityX = velocityX;
        this->velocityY = velocityY;
    }

    virtual VelocityComponent* clone()
    {
        return new VelocityComponent(*this);
    }
};

class PositionComponent : public artemis::Component
{

public:
    float posX;
    float posY;

    PositionComponent(float posX, float posY)
    {
        this->posX = posX;
        this->posY = posY;
    }

    virtual PositionComponent* clone()
    {
        return new PositionComponent(*this);
    }
};


class MovementSystem : public artemis::EntityProcessingSystem {
private:
    artemis::ComponentMapper<VelocityComponent> velocityMapper;
    artemis::ComponentMapper<PositionComponent> positionMapper;

public:
    MovementSystem() {
        addComponentType<VelocityComponent>();
        addComponentType<PositionComponent>();
    };

    virtual void initialize() {
        velocityMapper.init(*world);
        positionMapper.init(*world);
    };

    virtual void processEntity(artemis::Entity &e) {
        positionMapper.get(e)->posX += velocityMapper.get(e)->velocityX * world->getDelta();
        positionMapper.get(e)->posY += velocityMapper.get(e)->velocityY * world->getDelta();
    };

};


int main(int argc, char **argv) {

    artemis::World world;
    artemis::SystemManager * sm = world.getSystemManager();
    MovementSystem * movementsys = (MovementSystem*)sm->setSystem(new MovementSystem());
    artemis::EntityManager * em = world.getEntityManager();

    sm->initializeAll();


    artemis::Entity & player = em->create();

    player.addComponent(new PositionComponent(0.0, 0.0));
    player.addComponent(new VelocityComponent(2, 4));


    int i = 0;

    while(true){

        world.loopStart();
        world.setDelta(0.005f);
        movementsys->process();

        PositionComponent * comp = player.getComponent<PositionComponent>();
        if (comp != NULL)
        {
            std::cout << "X:"<< comp->posX << std::endl;
            std::cout << "Y:"<< comp->posY << std::endl;
        }

        Sleep(500);

        if (i == 10)
        {
            std::cout << "----------- Stop moving! -----------" << std::endl;
            player.removeComponent<VelocityComponent>();
        }
        else if (i == 20)
        {
            std::cout << "----------- Move! -----------" << std::endl;
            player.addComponent(new VelocityComponent(2, 4));
        }
        ++i;
    }

    return 0;
}

