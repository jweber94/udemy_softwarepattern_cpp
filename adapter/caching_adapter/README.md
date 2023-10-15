# Caching Adapter
+ A caching of the converted values from the given to the targeted API is useful to avoid unnecessary calculations
	- This is only reasonable if we do actual calculation. If the adapter consists only of a remapping, this might be a little overkill

## Implementation
+ In order to create hash values, we need to implement the `hash_value` function if we use `boost::hash<T>` for generating the keys for a map
	- Within the C++ standart for `std::unordered_map<Key, Value>`, we can just define a `hash_value` function that returns the hash value without rely on `boost::hash<T>`
		* See https://stackoverflow.com/questions/17016175/c-unordered-map-using-a-custom-class-type-as-the-key for details