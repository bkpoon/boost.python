#if !defined(BOOST_PP_IS_ITERATING)

// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.

# ifndef SIGNATURE_DWA20021121_HPP
#  define SIGNATURE_DWA20021121_HPP

#  include <boost/mpl/at.hpp>

#  include <boost/python/detail/preprocessor.hpp>
#  include <boost/preprocessor/iterate.hpp>
#  include <boost/preprocessor/iteration/local.hpp>

#  include <boost/python/type_id.hpp>

#  include <boost/python/detail/indirect_traits.hpp>

namespace boost { namespace python { namespace detail { 

struct signature_element
{
    char const* basename;
    bool lvalue;
};

template <unsigned> struct signature_arity;

#  define BOOST_PP_ITERATION_PARAMS_1                                            \
        (3, (0, BOOST_PYTHON_MAX_ARITY + 1, <boost/python/detail/signature.hpp>))
#  include BOOST_PP_ITERATE()

// A metafunction returning the base class used for signature<class F,
// class ConverterGenerators, class CallPolicies, class Sig>.
template <class Sig>
struct signature_base_select
{
    enum { arity = mpl::size<Sig>::value - 1 };
    typedef typename signature_arity<arity>::template impl<Sig> type;
};

template <class Sig>
struct signature
    : signature_base_select<Sig>::type
{
};

}}} // namespace boost::python::detail

# endif // SIGNATURE_DWA20021121_HPP

#else

# define N BOOST_PP_ITERATION()

template <>
struct signature_arity<N>
{
    template <class Sig>
    struct impl
    {
        static signature_element const* elements()
        {
            static signature_element const result[N+2] = {
                
# define BOOST_PP_LOCAL_MACRO(i)                                                            \
     {                                                                                      \
         type_id<BOOST_DEDUCED_TYPENAME mpl::at_c<Sig,i>::type>().name()                    \
       , is_reference_to_non_const<BOOST_DEDUCED_TYPENAME mpl::at_c<Sig,i>::type>::value    \
     },
                
# define BOOST_PP_LOCAL_LIMITS (0, N)
# include BOOST_PP_LOCAL_ITERATE()
                {0,0}
            };
            return result;
        }
    };
};

#endif // BOOST_PP_IS_ITERATING 

