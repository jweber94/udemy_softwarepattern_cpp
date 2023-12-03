#include <iostream>

// Property base
template <typename T>
class Property {
private:
    T value;

    // Applikationsspezifische Logik beim Setzen des Werts
    void setInternal(T newVal) {
        std::cout << "Setting property with additional logic\n";
        value = newVal;
    }

protected:
    // Virtuelle Methode für die Überprüfung beim Setzen
    virtual bool checkSet(const T& newValue) const {
        // Hier könnten spezifische Überprüfungen implementiert werden
        return true; // Standardmäßig immer erlaubt
    }

public:
    Property(T initialValue) : value(initialValue) {}

    // Setter mit zusätzlicher Logik und Überprüfung
    T operator=(T newVal) {
        if (checkSet(newVal)) {
            setInternal(newVal);
        }
        else {
            std::cout << "Setting property failed due to checkSet condition\n";
        }
        return value;
    }

    // Getter mit zusätzlicher Logik
    operator T() const {
        std::cout << "Getting property with additional logic\n";
        return value;
    }
};

// property differenciation
class Temperature : public Property<double> {
protected:
    // Spezifische Überprüfung für Temperature
    bool checkSet(const double& newValue) const override {
        return newValue >= -273.15; // Temperaturen dürfen nicht unter dem absoluten Nullpunkt liegen
    }

public:
    Temperature(double initialValue) : Property<double>(initialValue) {}
};

// usage of the property
class WeatherSimulation {
public:
    WeatherSimulation(double initTemp) :
        m_tmp{initTemp}
    {}

    Temperature m_tmp;
};


int main() {
    Temperature roomTemperature(20.0);

    // Verwendung des Property Proxys mit zusätzlicher Logik und Überprüfung
    std::cout << "Current temperature: " << static_cast<double>(roomTemperature) << " °C\n";

    roomTemperature = 68.0;  // Hier findet der Setter mit zusätzlicher Logik und Überprüfung statt

    roomTemperature = -300.0;  // Hier wird die Überprüfung ausgelöst

    WeatherSimulation sim(42.42);
    sim.m_tmp = 24.24;

    return 0;
}
