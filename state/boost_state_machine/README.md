# State Machine with `boost::msm`
+ We implement the same example with the phone call simulation of the last example. (which is the handmade state machine with the enums and the map with the transitioning rules)
+ Boost has two state machine frameworks, but within the course, we only learn about one, which is `boost::msm` (boost meta state machine)
+ In `boost::msm` our states are described with objects (via inheritance), so we are able to associate more data and functionallity to them (instead of using just enums for it)
	- The downside of it is that we are bound to the `boost::msm` framework, which requires us to overload some functions
+ Introduction (more then what we have learned within our course): https://dieboostcppbibliotheken.de/boost.msm