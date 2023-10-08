# Dependency Inversion Container with Singleton

## Prerequisites
+ We use `boost::di` in this example which is part of the boost experimental library.
    - That means, that the API might not be stable or badly documented
    - Here is the documentation of [`boost::di`](https://boost-ext.github.io/di/index.html)
        * You can also read about how to do proper dependency injection and about anti-pattern in dependency injection

## Application of a DI-Framework
+ A Dependency Injection Framwork allows us to define objects with a specific lifetime
+ That means the construction of an instance is done by the framework, which is then responsible to manage the existance of the object during its lifetime
    - We define an object by the DI-framework as a singleton and the framework is responsible to hold the instance as a single instance that exists as long as the application runs
        * That means we do not need to implement any singleton code. We can just implement a class and let the framework make a singleton out of it