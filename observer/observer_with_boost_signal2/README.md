# Observer with Boost
+ By using an existing observer library like `boost::signals2` we only need to implement the observable according to the observable definition of the library. Then you can just use the library functionallity to add observers to your observable without implementing the observer functionallity as a template on your own
	- This can simplify your code
	- And you do not need to test your code (if the library that you use is sufficiently tested)
+ ***Be careful!*** Most observer libraries are not thread safe