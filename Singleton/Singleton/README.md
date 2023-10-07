# Normal Singleton and its problems
+ Because our test is dependend on the `capitals.txt` database, we are not able to unit test the SingletonRecordFinder struct. We have written an integration test that depends on a _production_ database
    - Therefore, all code that uses the singleton is not unit testable!