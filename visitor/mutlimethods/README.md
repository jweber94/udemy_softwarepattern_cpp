# Multimethods
+ The idea is to have some kind of combine-`accept` method instead of a plain accept method
	- e.g. if we can not traverse all visitables via handing over the `this` pointer of the subordinate `accept` of the members of the visiable (like the `AdditionExpression` with its `left` and `right` expression pointer) for whatever reason
+ A multimethod approach is a separate _kind of_ visitor approach - we do not implement it directly as an addon to a classical visitor pattern!