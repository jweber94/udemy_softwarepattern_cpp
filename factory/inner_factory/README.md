# Inner Factory
+ The inner factory is a good alternative in order to not break the open close principle but still use a separate class for construction instances of the class that we want to create
+ The idea is:
    - Put the factory into the public section of the class that should be instanciated by the factory
    - Therefore, the factory can access all (private) members of the class that should be instanciated by the factory
+ Therefore we enforce the user of the class to use the factory and cluster them logically together