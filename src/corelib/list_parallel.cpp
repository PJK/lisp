#include "list_parallel.hpp"

std::shared_ptr<Value> ListParallel::eval(const StackFrame & ctx) {
	std::shared_ptr<Value> x1 = ctx.lookup(CORELIB_X1);
	typecheck(
			std::vector<ValueType> {ValueType::LIST},
			std::vector<ValueType> {x1->type()});
	std::shared_ptr<ListValue> lst = std::dynamic_pointer_cast<ListValue>(x1); 
	if (!lst->isRealList())
		throw LispException("This is a tuple, not a true list!");
	auto closures = collect(lst);
	std::vector<std::shared_ptr<Value>> results(closures.size());
	std::vector<std::thread> threads;
	for (int i = 0; i < closures.size(); i++) {
		threads.push_back(std::thread([&ctx, &closures, i, &results]() {
			StackFrame local_ctx(ctx);
			std::shared_ptr<ClosureValue> closure = closures.at(i);
			local_ctx.merge(closure->context());
			results.at(i) = closure->definition()->eval(local_ctx);
		}));
	}
	for(auto & thread : threads){
		thread.join();
	}
	return buildList(std::make_shared<ListNilValue>(), results);
}

std::vector<std::shared_ptr<ClosureValue>> ListParallel::collect(std::shared_ptr<ListValue> lst) {
	std::vector<std::shared_ptr<ClosureValue>> res;
	while (!lst->isNil()) {
		std::shared_ptr<ClosureValue> tmp = std::dynamic_pointer_cast<ClosureValue>(lst->car());
		if (tmp == nullptr)
			throw LispException("Only a nullary closure can be run!");
		res.push_back(tmp);
		lst = std::dynamic_pointer_cast<ListValue>(lst->cdr());
	}
	return res;
}

std::shared_ptr<ListValue> ListParallel::buildList(std::shared_ptr<ListValue> prev, std::vector<std::shared_ptr<Value>> & vals) {
	if (vals.empty())
		return prev;
	else {
		auto tmp = vals.back();
		vals.pop_back();
		return buildList(std::make_shared<ListValue>(tmp, prev), vals);
	}
}