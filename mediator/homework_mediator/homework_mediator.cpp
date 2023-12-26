#include <iostream>
#include <vector>

struct IParticipant {
    virtual void say(int value) = 0;
    virtual void addValue(int valToAdd) = 0;
};

struct Mediator {
    std::vector<IParticipant*> participants;
    Mediator() = default;
    void broadcast(int value, IParticipant* sender) {
        for (auto p : participants) {
            if (sender != p) { // broadcast to all but not to the sender himself
                p->addValue(value);
            }
        }
    }
};

struct Participant : IParticipant
{
    int value{ 0 };
    Mediator& mediator;

    Participant(Mediator& mediator) : mediator(mediator)
    {
        mediator.participants.push_back(this);
    }

    void say(int value) override
    {
        mediator.broadcast(value, this);
    }

    void addValue(int valToAdd) override {
        value += valToAdd;
    }
};

int main() {
    Mediator med;
    Participant p1(med);
    Participant p2(med);

    p1.say(3);
    std::cout << "p1.value is " << p1.value << ", p2.value is " << p2.value << "; expecting (0, 3) as the correct result" << std::endl;
    p2.say(2);
    std::cout << "p1.value is " << p1.value << ", p2.value is " << p2.value << "; expecting (2, 3) as the correct result" << std::endl;
    
    return 0;
}