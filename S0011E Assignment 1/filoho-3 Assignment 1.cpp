#include <iostream>
#include <chrono>
#include <vector>
#include "Code/GameEntity/GameEntity.h"
#include "Code/GameEntity/GameEntitySubClasses/Agent.h"
#include "Code/Managers/EntityManager.h"
#include "Code/Managers/MessageManager.h"


int main()
{
    int cycles = 0;

    typedef std::chrono::high_resolution_clock Clock;
    auto latestUpdate = Clock::now();
    auto currentTime = latestUpdate;
    int interval = 2000; //Update interval
    float timeModifier = 1.0f; //Change to speed up time, 1.0f is real time
    Agent* testAgent = new Agent(1);
    Agent* testAgent2 = new Agent(2);
    testAgent2->energy = 10;

    Agent* testAgent3 = new Agent(3);
    testAgent3->energy = 50;

    Agent* testAgent0 = new Agent(0);
    testAgent0->energy = 70;

    std::vector<std::shared_ptr<Agent*>> agents;
    agents.push_back(std::make_shared<Agent*>(testAgent0));
    agents.push_back(std::make_shared<Agent*>(testAgent));
    agents.push_back(std::make_shared<Agent*>(testAgent2));
    agents.push_back(std::make_shared<Agent*>(testAgent3));

    std::cout << "Enter time modifier (1 is real time), one cycle is "<<interval <<" milliseconds: ";
    std::string input;
    std::cin >> input;
    try {
        int i = stoi(input);
        timeModifier = i;
    }
    catch (std::invalid_argument) {
        std::cout << "INVALID ARGUMENT, modifier set to 1\n";
        timeModifier = 1.0f;
    }

    while (true) {
        std::chrono::duration < float> durationSinceLastUpdate = currentTime - latestUpdate;
        std::chrono::milliseconds duration = std::chrono::duration_cast<std::chrono::milliseconds>(durationSinceLastUpdate);
        
        //Ensure that agents only update every "interval" number of milliseconds apart
        if (duration.count()*timeModifier >= interval) {
            latestUpdate = Clock::now();
            for (int i = 0; i < agents.size(); i++) {
                Agent* temp = *agents[i].get();
                temp->Update();

                //Remove any dead agents
                if (temp->active == false) {
                    agents.erase(agents.begin() + i);
                    if (agents.size() == 0) {
                        std::cout << "All agents have died. They survived for " << cycles << " cycles.\n";
                        system("pause");
                        return false;
                    }
                }
            }
            MessageManager::Instance()->DispatchQueuedMessages();
            cycles += 1;
        }

        currentTime = Clock::now();
    }
}
