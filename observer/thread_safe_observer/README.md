# Thread Safe Observer
+ To make the Observable class thread safe is not much big of a deal, just do some `std::scoped_lock<std::mutex>` in it

## Reentrency Problem
+ Since the `Observable` class does not have control over the callback that is defined by the observer, we can end up in a deadlock
	- E.g. by unsubscribing within the observer callback after we received an event from the Observable that indicates for us to be no longer interested in events from the Observable
		* See the example code for an example of this

### Avoiding the reentrency problem
+ To avoid the reentrency problem, we can not lock within the unsubscribe method of our observable
	- This can be achived by using lock free programming or to have more sophisticated mechanisms of locking
+ In our example we just set the entry within the subscriber list to `nullptr` and check for them within the `notfiy` function and then skip them for the notification.
	- In a real world example we could implement a watchdog thread that removes `nullptr`s on a cyclic basis or to use a `unique_lock` and remove them by traversing the observer list at the end of the notfiy function and delete them if you detect a `nullptr`
	- We could also use a `std::recursive_mutex` instead of a `std::mutex`
## Locking Mechanisms
+ `std::scoped_lock<std::mutex> lck`:
	- Can handle multiple mutexes at one. That means you can lock multiple mutexes at once without worring about the order that they got locked
	- scoped_lock locks all mutexes that you hand over at once and checks for possible deadlocks in case the handed over mutexes would generate a deadlock - therefor it is convenient to use if you need to lock multiple deadlocks in your application
+ `std::unique_lock<std::mutex> lck`:
	- Locking of just one mutex
	- Has more control over the mutex. For example you can release the mutex without going out of scope (like it is in case of the scoped_lock)
	- Used on more complex settings where you need to control over the locking
+ `std::lock_guard<std::mutex> lck`:
	- Is basically a unique_lock with less functionallity and therefor easier to use 