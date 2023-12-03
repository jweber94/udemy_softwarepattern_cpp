# Virtual Proxy
+ A virtual proxy is an object that delivers a valid API of the underlying class/object, even if the underlying object itself is not created yet
+ A virtual proxy is sometimes also called _lazy proxy_, because mostly the initialization of the underlying object is only done if we actually access the method.
+ Mostly, virtual proxys are used if you have memory intense objects like images or other big chunks of data that otherwise are might initialized without the need of haveing them created.

## Virtual vs Lazy Proxy
+ While the lazy proxy is only responsible for initializing underlying objects on demand/usage, the virtual proxy does this as well as enhancing the initialization process itself or enhance the method calls on the underlying objects
+ Lazy proxies are mainly used if the underlying object is expensive to create (memory or compute wise)
+ Example for the lazy proxy is the following:
```
class HeavyObject {
    // ... teure Initialisierung
};

class LazyProxy {
private:
    std::shared_ptr<HeavyObject> heavyObject;

public:
    void performOperation() {
        if (!heavyObject) {
            heavyObject = std::make_shared<HeavyObject>();
        }
        // Führe Operation mit heavyObject durch
    }
};

```
+ An example for the virtual proxy is the following:
```
class BaseObject {
public:
    virtual void performOperation() = 0;
    virtual ~BaseObject() = default;
};

class RealObject : public BaseObject {
public:
    void performOperation() override {
        // Echte Implementierung
    }
};

class VirtualProxy : public BaseObject {
private:
    std::unique_ptr<RealObject> realObject;

public:
    void performOperation() override {
        if (!realObject) {
            realObject = std::make_unique<RealObject>();
        }
        // Zusätzliche Logik vor oder nach dem Aufruf der realen Operation
        realObject->performOperation();
    }
};

```