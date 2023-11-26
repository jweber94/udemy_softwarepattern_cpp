# Flyweight
+ *The flyweight is a structural design pattern that is used to do memory space optimization!*
	- The aim is to avoid redundancy when storing data in the RAM
+ ***A flyweight is a space optimization technique that lets us use less memory by storing externally the data associated with similar objects***
	- Store data externally and reference to this data when you need it

## Aim
+ Store common data externally and just refer to this chunk of data on demand
	- e.g. a static map with a key and the actual data as its value. The application operates just on the pointers instead of the data
+ Alternativly you can store data within a chunk of memory and safe attributes that are associated with a subset of the data within range objects
	- These range objects don't use actual data but checks if an element/the subset is within the range and then apply the attributes to them that are set active on the range object