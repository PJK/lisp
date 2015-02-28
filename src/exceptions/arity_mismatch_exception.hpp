#ifndef _ARITY_MISMATCH_EXCEPTION_HPP
#define _ARITY_MISMATCH_EXCEPTION_HPP
 
class ArityMismatchException : public LispException {
	public:
		ArityMismatchException(int expected, int got) : 
			_expected(expected), _got(got) {}
		virtual void explain(std::ostream & out) {
			out << "ERROR: Arity mismatch, expected " << _expected << " argument(s), got " << _got << std::endl;
		}
	private:
		int _expected, _got;
};
 
#endif